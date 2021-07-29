/**
 * @brief Provides APIs to browse FAT disks. This module works with HAL.
 */

/*******************************************************************************
* Includes
******************************************************************************/

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "HAL.h"
#include "fatfs.h"

/*******************************************************************************
* Definitions
******************************************************************************/

#define fatfs_read_uint16(buff, offset) (((uint16_t)(buff[offset + 1]) << 8) | (buff[offset]))

#define fatfs_read_uint32(buff, offset) (((uint32_t)(buff[offset + 3]) << 24) | ((uint32_t)(buff[offset + 2]) << 16) | ((uint32_t)(buff[offset + 1]) << 8) | (buff[offset]))

typedef struct
{
    /* Boot sector*/

    uint8_t jump_instruction[3];
    uint8_t oem_name[8];

    /* BIOS Parameter Block*/

    uint8_t bpb_bytes_per_sector[2];       /* 0x00B */
    uint8_t bpb_sectors_per_cluster;       /* 0x00D */
    uint8_t bpb_count_reserved_sectors[2]; /* 0x00E */
    uint8_t bpb_number_of_fat_table;       /* 0x010 */
    uint8_t bpb_max_root_entries[2];       /* 0x011 */
    uint8_t bpb_total_sectors[2];          /* 0x013 */
    uint8_t bpb_media_descriptor;          /* 0x015 */
    uint8_t bpb_sectors_per_fat_table[2];  /* 0x016 */

    uint8_t bpb_physical_sectors_per_track[2]; /* 0x018 */
    uint8_t bpb_number_of_heads_for_disks[2];  /* 0x01A */
    uint8_t bpb_physical_drive_number;         /* 0x018 */
    uint8_t bpb_boot_sector_signature[2];      /* 0x01A */
    uint8_t bpb_count_of_hidden_sectors[4];    /* 0x01C */
    uint8_t bpb_large_total_sectors[4];        /* 0x020 */

    /* Extended BIOS Parameter Block*/

    uint8_t bpb_physical_drive_number;      /* 0x024 */
    uint8_t bpb_reserved;                   /* 0x025 */
    uint8_t bpb_extended_boot_signature;    /* 0x026 */
    uint8_t bpb_volume_id[4];               /* 0x027 */
    uint8_t bpb_partition_volume_label[11]; /* 0x02B */
    uint8_t bpb_file_system_type[8];        /* 0x036 */

    /* Boot sector*/

    uint8_t specific_boot_code[447];
    uint8_t physical_drive_number; /* 0x1FD */
    uint8_t boot_sector_signature  /* 0x1FE */

} fatfs_boot_sector_struct_t;

typedef struct
{
    fatfs_boot_sector_struct_t s_fatfs_boot_sector;

    uint16_t sector_size;
    uint16_t cluster_size;

    uint32_t reserved_index;
    uint32_t fat_index;
    uint32_t root_index; /* FAT12/16 only */
    uint32_t data_index;

} fatfs_info_struct_t;

typedef struct
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
} fatfs_date_time_struct_t;

typedef struct
{
    fatfs_date_time_struct_t created_date_time;
    fatfs_date_time_struct_t modified_date_time;
    char *name;
    char extension[4];
    uint32_t first_cluster;
    uint32_t file_size;
} fatfs_entry_struct_t;

typedef enum
{
    entry_is_normal,
    entry_is_long_file_name,
    entry_is_deleted,
    entry_is_hidden,
    entry_is_the_last
} fatfs_entry_status;

/*******************************************************************************
* Prototypes
******************************************************************************/

/**
 * @brief Parse an entry in a sector buffer
 *
 * @param buff Sector buffer
 * @param index Position of entry in sector
 * @param entry Pointer to struct variable that store the entry
 * @return true if parse successfully
 * @return false if parse failed
*/
static fatfs_entry_status fatfs_parse_entry(uint8_t *buff, fatfs_entry_struct_t *entry);

/**
 * @brief  Parse date and time sequence in Dictionary Entry into struct
 *
 * @param time_sequence 16-bits time sequence
 * @param date_sequence 16-bits date sequence
 * @param date_time Pointer to the struct variable that is used to store the date and time
 * @return true if parse successfully
 * @return false if parse failed
 */
static bool fatfs_parse_date_time(uint16_t time_sequence, uint16_t date_sequence, fatfs_date_time_struct_t *date_time);

/*******************************************************************************
* Variables
******************************************************************************/

static fatfs_info_struct_t fatfs_info;


/*******************************************************************************
* Static functions
******************************************************************************/

static fatfs_entry_status fatfs_parse_entry(uint8_t *buff, fatfs_entry_struct_t *entry)
{

    fatfs_entry_status retVal;
    int8_t index = 0;
    uint16_t time_sequence;
    uint16_t date_sequence;
    bool padding_removed = false;


    if (0x0F == buff[0x0B])
    {
        /* Entry is Long File Name Entry */
        retVal = entry_is_long_file_name;


    } else 
        /* Entry is Normal Entry */

        /* Get first byte */
        entry->first_byte = buff[offset];
        if (entry->first_byte != 0x00)
        {
            /* Get file name */
            index = 7;
            /* Remove trailing padding space */
            while (index >= 0 && buff[offset + index] == ' ')
            {
                index--;
            }
            entry->name[index + 1] = '\0';
            /* Get file name */
            for (; index >= 0; index--)
            {
                entry->name[index] = buff[offset + index];
            }

            if (entry->first_byte != 0x2E) /* if first byte is not a Dot value */
            {
                /* Get file extension */
                for (index = 0; index < 3; index++)
                {
                    entry->extension[index] = buff[offset + index + 0x08];
                }
                entry->extension[3] = '\0';
                /* Get created date and time */
                time_sequence = read_uint16_from_buffer(buff, offset + 0x0E);
                date_sequence = read_uint16_from_buffer(buff, offset + 0x10);
                fat12_parse_date_time(time_sequence, date_sequence, &(entry->created_date_time));

                /* Get last modified date and time */
                time_sequence = read_uint16_from_buffer(buff, offset + 0x16);
                date_sequence = read_uint16_from_buffer(buff, offset + 0x18);
                fat12_parse_date_time(time_sequence, date_sequence, &(entry->last_modified_date_time));
            }
            /* Get first cluster */
            entry->first_cluster = read_uint16_from_buffer(buff, offset + 0x1A);
            /* Get file size */
            entry->file_size = read_uint32_from_buffer(buff, offset + 0x1C);
        }
    }

    return retVal;
}

static bool fat12_parse_date_time(uint16_t time_sequence, uint16_t date_sequence, fatfs_date_time_struct_t *date_time)
{

    /* Parse time */
    date_time->minute = (uint8_t)((time_sequence >> 5) & 0x003F);
    date_time->hour = (uint8_t)(time_sequence >> 11);

    /* Parse date */
    date_time->day = (uint8_t)(date_sequence & 0x001F);
    date_time->month = (uint8_t)((date_sequence >> 5) & 0x000F);
    date_time->year = (date_sequence >> 9) + 1980;

    return true; /* Assuming no error in image file */
}

static void fat12_print_entry(fatfs_entry_struct_t *entry, uint16_t index)
{

    uint8_t day = entry->last_modified_date_time.day;
    uint8_t month = entry->last_modified_date_time.month;
    uint16_t year = entry->last_modified_date_time.year;
    uint8_t hour = entry->last_modified_date_time.hour;
    uint8_t minute = entry->last_modified_date_time.minute;

    printf("  %d", index);
    printf("%14s", entry->name);
    if (entry->file_size != 0)
    {
        printf(".%s", entry->extension);
        printf("%5d/%d/%d %d:%d", day, month, year, hour, minute);
        printf("%8d kByte", entry->file_size);
    }
    else
    {
        printf("%9d/%d/%d %d:%d", day, month, year, hour, minute);
    }

    putchar('\n');
}


/*******************************************************************************
* Public functions
******************************************************************************/

bool fat12_init(void)
{

    uint8_t boot_sector_buff[NUMBER_OF_BYTES_PER_SECTOR];
    int32_t byte_read = 0;
    bool retVal = false;

    if (kmc_open())
    {
        byte_read = kmc_read_sector(0, boot_sector_buff);
        if (byte_read == NUMBER_OF_BYTES_PER_SECTOR)
        {
            retVal = true;

            /* Read BIOS Parameter Block */
            g_FAT12_BPB.bytes_per_sector = read_uint16_from_buffer(boot_sector_buff, OFFSET_BYTES_PER_SECTOR);
            g_FAT12_BPB.sectors_per_cluster = read_uint8_from_buffer(boot_sector_buff, OFFSET_SECTORS_PER_CLUSTER);
            g_FAT12_BPB.count_reserved_sectors = read_uint16_from_buffer(boot_sector_buff, OFFSET_COUNT_RESERVED_SECTORS);
            g_FAT12_BPB.number_of_FAT = read_uint8_from_buffer(boot_sector_buff, OFFSET_NUMBER_OF_FAT);
            g_FAT12_BPB.number_of_root_entries = read_uint16_from_buffer(boot_sector_buff, OFFSET_NUMBER_OF_ROOT_ENTRIES);
            g_FAT12_BPB.total_sectors = read_uint16_from_buffer(boot_sector_buff, OFFSET_TOTAL_SECTORS);
            g_FAT12_BPB.media_descriptor = read_uint8_from_buffer(boot_sector_buff, OFFSET_MEDIA_DESCRIPTOR);
            g_FAT12_BPB.sectors_per_FAT = read_uint16_from_buffer(boot_sector_buff, OFFSET_SECTOR_PER_FAT);

            /* Calculate index of regions */
            g_FAT12_region_index.reserved = 0U;
            g_FAT12_region_index.fat = g_FAT12_BPB.count_reserved_sectors;
            g_FAT12_region_index.root = g_FAT12_region_index.fat + g_FAT12_BPB.number_of_FAT * g_FAT12_BPB.sectors_per_FAT;
            g_FAT12_region_index.data = g_FAT12_region_index.root + (g_FAT12_BPB.number_of_root_entries * 32) / g_FAT12_BPB.bytes_per_sector;
        }
    }

    return retVal;
}

uint16_t fat12_open_root(void)
{

    uint16_t retVal = 0;
    uint8_t sector_buff[NUMBER_OF_BYTES_PER_SECTOR];
    int32_t byte_read = 0;
    fatfs_entry_struct_t entry;
    uint16_t count_entries = 0;
    uint16_t count_sector = 0;
    uint16_t offset = 0;
    bool no_more_entry = false;
    uint16_t sectors_in_root = (uint16_t)((g_FAT12_BPB.number_of_root_entries * 32) / g_FAT12_BPB.bytes_per_sector);

    for (count_sector = 0; !no_more_entry && count_sector < sectors_in_root; count_sector++)
    {
        byte_read = kmc_read_sector(g_FAT12_region_index.root + count_sector, sector_buff);
        for (offset = 0; !no_more_entry && offset < byte_read; offset += 32)
        {

            if (fat12_parse_entry(sector_buff, offset, &entry))
            {
                if (entry.first_byte == 0x00)
                {
                    no_more_entry = true;
                }
                else
                {
                    count_entries++;
                    fat12_print_entry(&entry, count_entries);
                }
            }
        }
    }
    retVal = count_entries;

    return retVal;
}
