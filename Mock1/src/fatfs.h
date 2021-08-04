/**
 * @brief Provides APIs to browse FAT File System.
 */

#ifndef _FATFS_
#define _FATFS_

/*******************************************************************************
* Definitions
******************************************************************************/

typedef enum
{
    error_code_success = 0,
    error_code_init_failed = 1,
    error_code_read_file_failed = 2,
    error_code_read_dir_failed = 3,
    error_code_deinit_failed = 4
} fatfs_error_code_t;

#if (__GNU__)
    #define FATFS_PACK __attribute__((packed))
#else
    #define FATFS_PACK
#endif

typedef struct
{
    uint8_t bytes_per_sector[2];           /* 0x00B */
    uint8_t sectors_per_cluster;           /* 0x00D */
    uint8_t count_reserved_sectors[2];     /* 0x00E */
    uint8_t number_of_fat_table;           /* 0x010 */
    uint8_t max_root_entries[2];           /* 0x011 */
    uint8_t total_sectors[2];              /* 0x013 */
    uint8_t media_descriptor;              /* 0x015 */
    uint8_t sectors_per_fat_table[2];      /* 0x016 */
    uint8_t physical_sectors_per_track[2]; /* 0x018 */
    uint8_t number_of_heads_for_disks[2];  /* 0x01A */
    uint8_t count_of_hidden_sectors[4];    /* 0x01C */
    uint8_t large_total_sectors[4];        /* 0x020 */
} FATFS_PACK fatfs_bios_parameter_block_struct_t;

typedef struct
{
    uint8_t physical_drive_number;      /* 0x024 */
    uint8_t reserved;                   /* 0x025 */
    uint8_t extended_boot_signature;    /* 0x026 */
    uint8_t volume_id[4];               /* 0x027 */
    uint8_t partition_volume_label[11]; /* 0x02B */
    uint8_t bitmask_system_type[8];     /* 0x036 */
} FATFS_PACK fatfs_fat12_fat16_extended_bpb_struct_t;

typedef struct
{
    uint8_t sectors_per_fat_table[4];         /* 0x024 */
    uint8_t drive_description[2];             /* 0x028 */
    uint8_t version[2];                       /* 0x02A */
    uint8_t root_dir_start_cluster[4];        /* 0x02C */
    uint8_t fs_info_start_sector[2];          /* 0x030 */
    uint8_t boot_sector_copy_start_sector[2]; /* 0x032 */
    uint8_t reserved[12];                     /* 0x034 */
    uint8_t physical_drive_number;            /* 0x040 */
    uint8_t for_various_purposes;             /* 0x041 */
    uint8_t extended_boot_signature;          /* 0x042 */
    uint8_t volume_id[4];                     /* 0x043 */
    uint8_t volume_label[11];                 /* 0x047 */
    uint8_t bitmask_system_type[8];           /* 0x052 */
} FATFS_PACK fatfs_fat32_extended_bpb_struct_t;

typedef union
{
    fatfs_fat12_fat16_extended_bpb_struct_t fat12_fat16_extended_bpb;
    fatfs_fat32_extended_bpb_struct_t fat32_extended_bpb;
} fatfs_extended_bpb_union_t;

typedef struct
{
    uint8_t jump_instruction[3];              /* 0x000 */
    int8_t oem_name[8];                       /* 0x003 */
    fatfs_bios_parameter_block_struct_t bpb;  /* 0x00B */
    fatfs_extended_bpb_union_t extended_bpb;/* 0x024 */
    uint8_t specific_boot_code[419]; /* 0x05A */
    uint8_t physical_drive_number;            /* 0x1FD */
    uint8_t boot_sector_signature[2];         /* 0x1FE */
} FATFS_PACK fatfs_boot_sector_struct_t;

typedef struct
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
} fatfs_time_struct_t;

typedef struct _entry
{
    fatfs_time_struct_t created_time;
    fatfs_time_struct_t modified_time;
    int8_t name[256];
    int8_t extension[4];
    uint32_t first_cluster;
    uint32_t size;
    uint32_t rounded_size;
    bool is_subdir;

    struct _entry *next;
} fatfs_entry_struct_t;

/*******************************************************************************
* API
******************************************************************************/

/**
 * @brief initiate FAT
 *
 * @param file_path File path
 * @return fatfs_error_code_t error code
 */
fatfs_error_code_t fatfs_init(int8_t *file_path);

/**
 * @brief Open a subdirectory
 *
 * @param first_cluster First cluster of entry data
 * @param entry_list Output: Pointer to the header of entry list
 * @return fatfs_error_code_t Error code
 */
fatfs_error_code_t fatfs_read_dir(uint32_t first_cluster, fatfs_entry_struct_t **entry_list);

/**
 * @brief Read a file
 *
 * @param first_cluster First cluster of entry data
 * @param file_buff_ptr Output: file data buffer
 * @param size Output: Size of file data buffer
 * @return fatfs_error_code_t Error code
 */
fatfs_error_code_t fatfs_read_file(uint32_t first_cluster, uint8_t **file_buff_ptr, uint32_t size);

/**
 * @brief FAT deinit: Close file, free dynamic memory
 *
 * @return fatfs_error_code_t Error code
 */
fatfs_error_code_t fatfs_deinit(void);

#endif /* _FATFS_ */
