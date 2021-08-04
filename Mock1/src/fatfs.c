/**
 * @brief Provides APIs to browse FAT disks. This module works with HAL.
 */

 /*******************************************************************************
 * Includes
 ******************************************************************************/

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "HAL.h"
#include "fatfs.h"

 /*******************************************************************************
 * Definitions
 ******************************************************************************/

#define FATFS_READ_UINT16(buff)    (((uint16_t)((buff)[1]) << 8) | ((buff)[0]))
#define FATFS_READ_UINT32(buff)    (((uint32_t)((buff)[3]) << 24) | ((uint32_t)((buff)[2]) << 16) | ((uint32_t)((buff)[1]) << 8) | ((buff)[0]))

 /* Masks for converting time and date of entries */

#define FATFS_ENTRY_SECOND_MASK    (0x1FU)
#define FATFS_ENTRY_SECOND_SHIFT    (0U)
#define FATFS_ENTRY_GET_SECOND(x)    ((uint8_t) (2 * ((((uint16_t)(x)) & FATFS_ENTRY_SECOND_MASK) >> FATFS_ENTRY_SECOND_SHIFT)))

#define FATFS_ENTRY_MINUTE_MASK    (0x7E0U)
#define FATFS_ENTRY_MINUTE_SHIFT    (5U)
#define FATFS_ENTRY_GET_MINUTE(x)    ((uint8_t)((((uint16_t)(x)) & FATFS_ENTRY_MINUTE_MASK) >> FATFS_ENTRY_MINUTE_SHIFT))

#define FATFS_ENTRY_HOUR_MASK    (0xF800U)
#define FATFS_ENTRY_HOUR_SHIFT    (11U)
#define FATFS_ENTRY_GET_HOUR(x)    ((uint8_t)((((uint16_t)(x)) & FATFS_ENTRY_HOUR_MASK) >> FATFS_ENTRY_HOUR_SHIFT))

#define FATFS_ENTRY_DAY_MASK    (0x1FU)
#define FATFS_ENTRY_DAY_SHIFT    (0U)
#define FATFS_ENTRY_GET_DAY(x)    ((uint8_t)((((uint16_t)(x)) & FATFS_ENTRY_DAY_MASK) >> FATFS_ENTRY_DAY_SHIFT))

#define FATFS_ENTRY_MONTH_MASK    (0x1E0U)
#define FATFS_ENTRY_MONTH_SHIFT    (5U)
#define FATFS_ENTRY_GET_MONTH(x)    ((uint8_t)((((uint16_t)(x)) & FATFS_ENTRY_MONTH_MASK) >> FATFS_ENTRY_MONTH_SHIFT))

#define FATFS_ENTRY_YEAR_MASK    (0xFE00U)
#define FATFS_ENTRY_YEAR_SHIFT    (9U)
#define FATFS_ENTRY_GET_YEAR(x)    ((uint16_t)(1980 + ((((uint16_t)(x)) & FATFS_ENTRY_YEAR_MASK) >> FATFS_ENTRY_YEAR_SHIFT)))

typedef enum
{
    eof_fat12 = 0xFF8,
    eof_fat16 = 0xFFF8,
    eof_fat32 = 0x0FFFFFF8
} fatfs_eof_t; /* Indicate FAT type, also first cluster of EOF region */

typedef struct
{
    fatfs_boot_sector_struct_t boot_sector;
    fatfs_eof_t eof;
    uint16_t sector_size;
    uint16_t cluster_size;
    uint32_t fat_index;  /* index sector of File Allocation Table region */
    uint32_t root_index; /* for FAT12/16 only, in case FAT32, this equal index sector of data region */
    uint32_t data_index; /* index sector of data region */
} fatfs_info_struct_t;

typedef enum
{
    entry_offset_short_file_name = 0x00,
    entry_offset_short_extension = 0x08,
    entry_offset_file_attributes = 0x0B,
    entry_offset_user_attributes = 0x0C,
    entry_offset_created_time_ms = 0x0D,
    entry_offset_created_time = 0x0E,
    entry_offset_created_date = 0x10,
    entry_offset_last_access_date = 0x12,
    entry_offset_access_right = 0x14,
    entry_offset_modified_time = 0x16,
    entry_offset_modified_date = 0x18,
    entry_offset_first_cluster = 0x1A,
    entry_offset_file_size = 0x1C
} fatfs_entry_offset_t;

typedef enum
{
    bitmask_read_only = 0x01,
    bitmask_hidden = 0x02,
    bitmask_system = 0x04,
    bitmask_volume_label = 0x08,
    bitmask_subdirectory = 0x10,
    bitmask_archive = 0x20,
    bitmask_device = 0x40,
    bitmask_reserve = 0x80
} fatfs_file_attribute_bitmask_t;

typedef enum
{
    entry_is_normal = 0,
    entry_is_long_file_name = 1,
    entry_is_deleted = 2,
    entry_is_hidden = 3,
    entry_is_eof = 4
} fatfs_entry_status_t;

typedef enum
{
    cluster_type_data = 0,       /* 0x002 - 0xFEF    0x0002 - 0xFFEF    0x?0000002 - 0x?FFFFFEF */
    cluster_type_reserve = 1,    /* 0xFF0 - 0xFF5    0xFFF0 - 0xFFF5    0x?FFFFFF0 - 0x?FFFFFF5 */
    cluster_type_not_used = 2,   /* 0xFF6    0xFFF6    0x?FFFFFF6 */
    cluster_type_bad_sector = 3, /* 0xFF7    0xFFF7    0x?FFFFFF7 */
    cluster_type_eof = 4         /* 0xFF8 - 0xFFF    0xFFF8 - 0xFFFF    0x?FFFFFF8 - 0x?FFFFFFF */
} fatfs_cluster_type_t;

/*******************************************************************************
* Prototypes
******************************************************************************/

static bool fatfs_get_next_cluster(uint32_t* current_cluster);

/**
 * @brief Parse an entry, push to entry list if it's a normal entry
 *
 * @param buff Binary buffer
 * @return fatfs_entry_status_t Entry status
*/
static fatfs_entry_status_t fatfs_parse_entry(uint8_t* buff);

/**
 * @brief add entry into entry list
 *
 * @param entry The entry to add into list
 */
static void fatfs_update_entry_list(fatfs_entry_struct_t* entry);

/**
 * @brief Free entry list
 */
static void fatfs_free_entry_list(void);

/*******************************************************************************
* Variables
******************************************************************************/

/* FAT file system information */
static fatfs_info_struct_t s_fatfs_info;

/* Head pointer of entry list */
static fatfs_entry_struct_t* sp_fatfs_entry_head = NULL;

/* Tail pointer of entry list */
static fatfs_entry_struct_t* sp_fatfs_entry_tail = NULL;

/*******************************************************************************
* Static functions
******************************************************************************/

static void fatfs_update_entry_list(fatfs_entry_struct_t* entry)
{
    fatfs_entry_struct_t* current_entry = sp_fatfs_entry_head;

    if (sp_fatfs_entry_head == NULL)
    {
        sp_fatfs_entry_head = entry;
        sp_fatfs_entry_tail = entry;
    }
    else
    {
        sp_fatfs_entry_tail->next = entry;
        sp_fatfs_entry_tail = entry;
    }
}

static fatfs_entry_status_t fatfs_parse_entry(uint8_t* buff)
{
    fatfs_entry_status_t retVal = entry_is_normal;
    fatfs_entry_struct_t* entry;
    uint16_t time_binary;
    uint16_t date_binary;
    static int8_t s_long_file_name[256];
    static uint16_t s_long_file_name_len = 0;
    int8_t index = 0;

    if (0x0F == buff[entry_offset_file_attributes])
    {
        retVal = entry_is_long_file_name;

        if (0 != buff[0] | 0x40) /* if this entry is "the last logical LFN entry" */
        {
            s_long_file_name_len = 0;
        }

        /* Copy 16-bits characters in LFN entry to 8-bits characters in s_long_file_name buffer */
        for (index = 0; index < 10; index += 2, s_long_file_name_len++)
        {
            s_long_file_name[s_long_file_name_len] = buff[0x01 + index];
        }

        for (index = 0; index < 12; index += 2, s_long_file_name_len++)
        {
            s_long_file_name[s_long_file_name_len] = buff[0x0E + index];
        }

        for (index = 0; index < 4; index += 2, s_long_file_name_len++)
        {
            s_long_file_name[s_long_file_name_len] = buff[0x1C + index];
        }

        s_long_file_name_len += 26;

        /* Remove padding spaces */
        while (s_long_file_name[s_long_file_name_len - 1] == ' ')
        {
            s_long_file_name_len--;
        }

        s_long_file_name[s_long_file_name_len] = '\0';
    }
    else if (0 == buff[0])
    {
        retVal = entry_is_eof;
    }
    else if (0xE5 == buff[0])
    {
        retVal = entry_is_deleted;
    }
    else if (0 != bitmask_hidden & buff[entry_offset_file_attributes])
    {
        retVal = entry_is_hidden;
    }
    else
    {
        retVal = entry_is_normal;
        entry = (fatfs_entry_struct_t*)malloc(sizeof(fatfs_entry_struct_t));

        /* Idicate that file is a subdirectory or a file */
        if ((bitmask_subdirectory & buff[entry_offset_file_attributes]) != 0)
        {
            entry->is_subdir = true;
        }
        else
        {
            entry->is_subdir = false;
        }

        /* Get file extension */
        for (index = 0; index < 3; index++)
        {
            entry->extension[index] = buff[entry_offset_short_extension + index];
        }

        entry->extension[3] = '\0';

        /* Get file name */
        if (s_long_file_name_len > 0)
        {
            for (index = 0; index < s_long_file_name_len; index++)
            {
                entry->name[index] = s_long_file_name[index];
            }

            entry->name[s_long_file_name_len] = '\0';
            s_long_file_name_len = 0;
        }
        else
        {
            /* Ignore padding spaces in file name */
            for (entry->name[8] = '\0', index = 7; index >= 0 && buff[index] == ' '; index--)
            {
                entry->name[index] = '\0';
            }

            /* Get file name */
            for (; index >= 0; index--)
            {
                entry->name[index] = buff[entry_offset_short_file_name + index];
            }
        }

        /* Get created date and time */
        time_binary = FATFS_READ_UINT16(&buff[entry_offset_created_time]);
        date_binary = FATFS_READ_UINT16(&buff[entry_offset_created_date]);

        entry->created_time.minute = FATFS_ENTRY_GET_MINUTE(time_binary);
        entry->created_time.hour = FATFS_ENTRY_GET_HOUR(time_binary);

        entry->created_time.day = FATFS_ENTRY_GET_DAY(date_binary);
        entry->created_time.month = FATFS_ENTRY_GET_MONTH(date_binary);
        entry->created_time.year = FATFS_ENTRY_GET_YEAR(date_binary);

        /* Get last modified date and time */
        time_binary = FATFS_READ_UINT16(&buff[entry_offset_modified_time]);
        date_binary = FATFS_READ_UINT16(&buff[entry_offset_modified_date]);

        entry->modified_time.minute = FATFS_ENTRY_GET_MINUTE(time_binary);
        entry->modified_time.hour = FATFS_ENTRY_GET_HOUR(time_binary);

        entry->modified_time.day = FATFS_ENTRY_GET_DAY(date_binary);
        entry->modified_time.month = FATFS_ENTRY_GET_MONTH(date_binary);
        entry->modified_time.year = FATFS_ENTRY_GET_YEAR(date_binary);

        /* Get first cluster */
        if (eof_fat32 == s_fatfs_info.eof)
        {
            /* High two bytes at 0x14 */
            entry->first_cluster = (uint32_t)FATFS_READ_UINT16(&buff[0x14]);
            entry->first_cluster <<= 16;
            /* Low two bytes at 0x1A */
            entry->first_cluster |= FATFS_READ_UINT16(&buff[0x1A]);
        }
        else
        {
            entry->first_cluster = FATFS_READ_UINT16(&buff[entry_offset_first_cluster]);
        }

        /* Get file size */
        entry->size = FATFS_READ_UINT32(&buff[entry_offset_file_size]);

        /* Round up file size */
        entry->rounded_size = ((entry->size + s_fatfs_info.sector_size - 1) / s_fatfs_info.sector_size) * s_fatfs_info.sector_size;

        /* Add entry to list */
        entry->next = NULL;
        fatfs_update_entry_list(entry);
    }

    return retVal;
}

static void fatfs_free_entry_list(void)
{
    fatfs_entry_struct_t* entry = NULL;

    while (sp_fatfs_entry_head != NULL)
    {
        entry = sp_fatfs_entry_head->next;
        free(sp_fatfs_entry_head);
        sp_fatfs_entry_head = entry;
    }

    sp_fatfs_entry_tail = NULL;
}

static bool fatfs_get_next_cluster(uint32_t* current_cluster)
{
    uint32_t retVal = false;
    uint32_t index_sector_in_table = 0;
    uint32_t index_byte_in_sector = 0;
    uint8_t* buff = NULL;
    int32_t bytes_read;

    buff = (uint8_t*)malloc(2 * s_fatfs_info.sector_size);
    switch (s_fatfs_info.eof)
    {
        case eof_fat12:
            index_sector_in_table = (3 * (*current_cluster) / 2) / s_fatfs_info.sector_size;
            index_byte_in_sector = (3 * (*current_cluster) / 2) % s_fatfs_info.sector_size;
            buff = (uint8_t*)malloc(2 * s_fatfs_info.sector_size);
            if (NULL != buff)
            {
                bytes_read = kmc_read_multi_sector(index_sector_in_table + s_fatfs_info.fat_index, 2, buff);
                if (2 * s_fatfs_info.sector_size == bytes_read)
                {
                    retVal = true;
                    if (0 == (3 * (*current_cluster)) % 2)
                    {
                        (*current_cluster) = buff[index_byte_in_sector + 1] & 0x0F; /* high half-byte */
                        (*current_cluster) <<= 8;
                        (*current_cluster) |= buff[index_byte_in_sector]; /* low full-byte */
                    }
                    else
                    {
                        (*current_cluster) = buff[index_byte_in_sector + 1]; /* high full-byte */
                        (*current_cluster) <<= 4;
                        (*current_cluster) |= (buff[index_byte_in_sector] >> 4); /* low half byte */
                    }
                }
            }
            break;

        case eof_fat16:
            index_sector_in_table = 2 * (*current_cluster) / s_fatfs_info.sector_size;
            index_byte_in_sector = (2 * (*current_cluster)) % s_fatfs_info.sector_size;
            if (NULL != buff)
            {
                bytes_read = kmc_read_multi_sector(index_sector_in_table + s_fatfs_info.fat_index, 2, buff);
                if (2 * s_fatfs_info.sector_size == bytes_read)
                {
                    retVal = true;
                    (*current_cluster) = FATFS_READ_UINT16(&buff[index_byte_in_sector]);
                }
            }
            break;

        case eof_fat32:
            index_sector_in_table = 4 * (*current_cluster) / s_fatfs_info.sector_size;
            index_byte_in_sector = (4 * (*current_cluster)) % s_fatfs_info.sector_size;
            if (NULL != buff)
            {
                bytes_read = kmc_read_multi_sector(index_sector_in_table + s_fatfs_info.fat_index, 2, buff);
                if (bytes_read == 2 * s_fatfs_info.sector_size)
                {
                    retVal = true;
                    (*current_cluster) = FATFS_READ_UINT32(&buff[index_byte_in_sector]);
                }
            }
            break;

        default:
            break;
    }
    free(buff);

    return retVal;
}

static fatfs_cluster_type_t fatfs_check_cluster(uint32_t cluster_index)
{
    fatfs_cluster_type_t retVal;

    /* If cluster is EOF (in FAT table, cluster 0 and 1 are also treated as EOF) */
    if (cluster_index >= s_fatfs_info.eof || 0 == cluster_index || 1 == cluster_index)
    {
        retVal = cluster_type_eof;
    }
    else
    {
        switch (s_fatfs_info.eof)
        {
            case eof_fat12:
                if (cluster_index >= 0x002 && cluster_index <= 0xFEF)
                {
                    retVal = cluster_type_data;
                }
                else if (cluster_index >= 0xFF0 && cluster_index <= 0xFF5)
                {
                    retVal = cluster_type_reserve;
                }
                else if (0xFF6 == cluster_index)
                {
                    retVal = cluster_type_not_used;
                }
                else
                {
                    retVal = cluster_type_bad_sector;
                }

                break;

            case eof_fat16:
                if (cluster_index >= 0x0002 && cluster_index <= 0xFFEF)
                {
                    retVal = cluster_type_data;
                }
                else if (cluster_index >= 0xFFF0 && cluster_index <= 0xFFF5)
                {
                    retVal = cluster_type_reserve;
                }
                else if (0xFFF6 == cluster_index)
                {
                    retVal = cluster_type_not_used;
                }
                else
                {
                    retVal = cluster_type_bad_sector;
                }

                break;

            case eof_fat32:
                if (cluster_index >= 0x00000002 && cluster_index <= 0xFFFFFFEF)
                {
                    retVal = cluster_type_data;
                }
                else if (cluster_index >= 0x0FFFFFF0 && cluster_index <= 0x0FFFFFF5)
                {
                    retVal = cluster_type_reserve;
                }
                else if (0x0FFFFFF6 == cluster_index)
                {
                    retVal = cluster_type_not_used;
                }
                else
                {
                    retVal = cluster_type_bad_sector;
                }

                break;

            default:
                break;
        }
    }

    return retVal;
}

/*******************************************************************************
* Public functions
******************************************************************************/

fatfs_error_code_t fatfs_init(int8_t* file_path)
{
    fatfs_error_code_t retVal = error_code_init_failed;
    int32_t bytes_read = 0;
    uint16_t bpb_sectors_per_fat_table;

    if (kmc_open(file_path))
    {
        /* Read boot sector */
        bytes_read = kmc_read_sector(0, (uint8_t*)&(s_fatfs_info.boot_sector));

        if (512 == bytes_read)
        {
            retVal = error_code_success;
            /* Identify FAT type */
            bpb_sectors_per_fat_table = FATFS_READ_UINT16(s_fatfs_info.boot_sector.bpb.sectors_per_fat_table);
            if (0 == bpb_sectors_per_fat_table) /* FAT32 sets this to 0 and uses the 32-bit value at offset 0x024 instead. */
            {
                s_fatfs_info.eof = eof_fat32;
                bpb_sectors_per_fat_table = FATFS_READ_UINT32(s_fatfs_info.boot_sector.extended_bpb.fat32_extended_bpb.sectors_per_fat_table);
            }
            else if (12 >= bpb_sectors_per_fat_table) /* FAT12: 1 to 12 sectors per copy of FAT */
            {
                s_fatfs_info.eof = eof_fat12;
            }
            else
            {
                s_fatfs_info.eof = eof_fat16; /* FAT16: 16 to 256 sectors per copy of FAT */
            }

            /* Parse others FAT information */
            s_fatfs_info.sector_size = FATFS_READ_UINT16(s_fatfs_info.boot_sector.bpb.bytes_per_sector);
            s_fatfs_info.cluster_size = s_fatfs_info.boot_sector.bpb.sectors_per_cluster;
            s_fatfs_info.fat_index = FATFS_READ_UINT16(s_fatfs_info.boot_sector.bpb.count_reserved_sectors);

            if (eof_fat32 == s_fatfs_info.eof)
            {
                s_fatfs_info.data_index = s_fatfs_info.fat_index + bpb_sectors_per_fat_table * s_fatfs_info.boot_sector.bpb.number_of_fat_table;
            }
            else
            {
                s_fatfs_info.root_index = s_fatfs_info.fat_index + bpb_sectors_per_fat_table * s_fatfs_info.boot_sector.bpb.number_of_fat_table;
                s_fatfs_info.data_index = s_fatfs_info.root_index + (FATFS_READ_UINT16(s_fatfs_info.boot_sector.bpb.max_root_entries) * 32) / s_fatfs_info.sector_size;
            }
        }
    }

    return retVal;
}

fatfs_error_code_t fatfs_read_dir(uint32_t first_cluster, fatfs_entry_struct_t** entry_list)
{
    fatfs_error_code_t retVal = error_code_read_dir_failed;
    uint8_t* buff = NULL;
    int32_t bytes_read = 0;
    uint8_t sectors_to_read = 0;
    uint32_t current_cluster = first_cluster;
    uint16_t offset = 0;
    fatfs_entry_status_t entry_status = entry_is_normal;

    fatfs_free_entry_list();

    if (0 == first_cluster && eof_fat32 == s_fatfs_info.eof)
    {
        /* If reading root directory of FAT32, update root region (get from ) */
        current_cluster = FATFS_READ_UINT32(s_fatfs_info.boot_sector.extended_bpb.fat32_extended_bpb.root_dir_start_cluster);
    }

    if (0 == first_cluster && eof_fat32 != s_fatfs_info.eof)
    {
        /* Reading from FAT12/16 root region */
        sectors_to_read = s_fatfs_info.data_index - s_fatfs_info.root_index;
        buff = (uint8_t*)malloc(sectors_to_read * s_fatfs_info.sector_size);
        if (NULL != buff)
        {
            retVal = error_code_success;
            bytes_read = kmc_read_multi_sector(s_fatfs_info.root_index, sectors_to_read, buff);
            for (offset = 0; entry_is_eof != entry_status && offset < bytes_read; offset += 32)
            {
                entry_status = fatfs_parse_entry(&buff[offset]);
            }
        }
    }
    else
    {
        /* Reading directory from data region */
        sectors_to_read = s_fatfs_info.cluster_size;
        buff = (uint8_t*)malloc(sectors_to_read * s_fatfs_info.sector_size);

        if (NULL != buff)
        {
            bytes_read = kmc_read_multi_sector(s_fatfs_info.data_index + (current_cluster - 2) * s_fatfs_info.cluster_size, sectors_to_read, buff);
            retVal = error_code_success;
            do
            {
                if (cluster_type_eof == fatfs_check_cluster(current_cluster))
                {
                    retVal = error_code_read_dir_failed;
                }
                else
                {
                    for (offset = 0; entry_is_eof != entry_status && offset < bytes_read; offset += 32)
                    {
                        entry_status = fatfs_parse_entry(&buff[offset]);
                    }
                    if (!fatfs_get_next_cluster(&current_cluster)) // error encountered
                    {
                        retVal = error_code_read_dir_failed;
                    }
                }
            } while (entry_is_eof != entry_status && error_code_success == retVal);

            free(buff);
        }
    }

    if (error_code_success == retVal)
    {
        *entry_list = sp_fatfs_entry_head;
    }

    return retVal;
}

fatfs_error_code_t fatfs_read_file(uint32_t first_cluster, uint8_t** file_buff, uint32_t size)
{
    fatfs_error_code_t retVal = error_code_success;
    uint8_t* cluster_buff = NULL;
    uint32_t current_cluster = first_cluster;
    int32_t bytes_read = 0;

    if (0 != size)
    {
        while (cluster_type_eof != fatfs_check_cluster(current_cluster) && error_code_success == retVal)
        {
            bytes_read += kmc_read_multi_sector(s_fatfs_info.data_index + (current_cluster - 2) * s_fatfs_info.cluster_size, s_fatfs_info.cluster_size, &((*file_buff)[bytes_read]));
            if (bytes_read > size || !fatfs_get_next_cluster(&current_cluster))
            {
                retVal = error_code_read_file_failed;
            }
        }
    }

    return retVal;
}

fatfs_error_code_t fatfs_deinit(void)
{
    fatfs_error_code_t retVal = error_code_success;

    if (kmc_close())
    {
        fatfs_free_entry_list();
    }
    else
    {
        retVal = error_code_deinit_failed;
    }

    return retVal;
}
