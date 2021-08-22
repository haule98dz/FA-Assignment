/**
 * @brief A program to browse FAT file system.
 *
 */

 /*******************************************************************************
  * Includes
  ******************************************************************************/

#include <stdint.h>
#include <conio.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "fatfs.h"
#include "menu.h"

  /*******************************************************************************
   * Define
   ******************************************************************************/

typedef enum
{
    menu_exit = 0,
    menu_context_initiate_fat = 1,
    menu_context_directory = 2,
    menu_context_file = 3
} menu_context_t;

typedef enum
{
    menu_error_code_success = 0,
    menu_error_code_get_file_name_failed = 10,
    menu_error_code_invalid_option = 11
} menu_error_code_t;

/*******************************************************************************
* Variable
******************************************************************************/

/* Variable to switch between contexts */
static menu_context_t s_menu_context = menu_context_initiate_fat;

/* Pointer head of linked list */
static fatfs_entry_struct_t* sp_dir_list = NULL;

/* File data buffer */
static uint8_t* sp_file_buffer = NULL;

/* Buffer size */
static uint32_t s_buffer_size = 0;

/*******************************************************************************
* Prototypes
******************************************************************************/

/**
 * @brief Get FAT image file path from keyboard, then initiate FAT
 *
 * @return menu_error_code_t Error code
 */
static menu_error_code_t menu_initiate_fat();

/**
 * @brief Print directory, then get user's input
 *
 * @return menu_error_code_t Error code
 */
static menu_error_code_t menu_show_directory();

/**
 * @brief Print file content in hexa format, then get user's input
 *
 *
 * @return menu_error_code_t Error code
 */
static menu_error_code_t menu_show_file();

/**
 * @brief Print error
 *
 * @param error_code Error code
 */
static void menu_print_error(fatfs_error_code_t error_code);

/*******************************************************************************
* Static functions
******************************************************************************/

static menu_error_code_t menu_initiate_fat()
{
    menu_error_code_t error_code = menu_error_code_get_file_name_failed;
    int8_t file_path[261];

    system("cls");
    printf("Enter file path: ");
    /* Get file name */
    fflush(stdin);
    if (0 != scanf("%[^\n]", &file_path[0]))
    {
        /* Init FAT */
        error_code = fatfs_init(&file_path[0]);
    }

    if (error_code_success == error_code)
    {
        /* Read root directory */
        error_code = fatfs_read_dir(0, &sp_dir_list);
        if (error_code_success == error_code)
        {
            s_menu_context = menu_context_directory;
        }
    }

    if (error_code_success != error_code)
    {
        s_menu_context = menu_exit;
        menu_print_error(error_code);
    }

    return error_code;
}

static menu_error_code_t menu_show_directory()
{
    menu_error_code_t error_code;
    fatfs_entry_struct_t* entry = sp_dir_list;
    uint16_t index;
    uint32_t user_option;

    /* Print directory */
    system("cls");
    printf(" Option       Name             Type           File size         Modified date and time\n");
    printf("-----------------------------------------------------------------------------------------\n");
    for (index = 1; NULL != entry; index++)
    {
        printf("   %-5d   ", index);
        printf("%-20s ", entry->name);
        if (0x2E != entry->name[0])
        {
            if (entry->is_subdir)
            {
                printf("%-10s             ", "Folder");
            }
            else
            {
                printf("%-10s", entry->extension);
                printf("%7d bytes", entry->size);
            }
            printf("            %02d/%02d/%04d %02d:%02d", entry->modified_time.day, entry->modified_time.month, entry->modified_time.year, entry->modified_time.hour, entry->modified_time.minute);
        }
        putchar('\n');
        entry = entry->next;
    }

    /* Process user's option */
    error_code = menu_error_code_invalid_option;
    while (menu_error_code_success != error_code)
    {
        printf("\nEnter an option (enter 0 to exit): ");
        fflush(stdin);
        if (0 != scanf("%u%*c", &user_option))
        {
            if (0 < user_option)
            {
                for (index = 1, entry = sp_dir_list; index != user_option && NULL != entry; index++)
                {
                    entry = entry->next;
                }
                if (NULL != entry)
                {
                    error_code = menu_error_code_success;
                    if (entry->is_subdir)
                    {
                        error_code = fatfs_read_dir(entry->first_cluster, &sp_dir_list);
                        s_menu_context = menu_context_directory;
                    }
                    else
                    {
                        s_buffer_size = entry->size;
                        sp_file_buffer = (uint8_t*)malloc(entry->rounded_size);
                        error_code = fatfs_read_file(entry->first_cluster, &sp_file_buffer, entry->rounded_size);
                        s_menu_context = menu_context_file;
                    }
                }
            }
            else
            {
                error_code = menu_error_code_success;
                s_menu_context = menu_context_initiate_fat;
            }
        }
        if (error_code_success != error_code)
        {
            menu_print_error(error_code);
        }
    }

    return error_code;
}

static menu_error_code_t menu_show_file()
{
    menu_error_code_t error_code = menu_error_code_invalid_option;
    uint32_t index;
    uint32_t user_option;

    /* Print file */
    system("cls");
    for (index = 0; index < s_buffer_size; index++)
    {
        printf("%x", sp_file_buffer[index]);
    }
    free(sp_file_buffer);

    printf("\n\nDone printing %u bytes.", s_buffer_size);
    /* Process user's option */
    while (menu_error_code_success != error_code)
    {
        printf("\nEnter 1 to return to subdirectory, enter 0 to exit: ");
        fflush(stdin);
        if (0 != scanf("%u%*c", &user_option))
        {
            switch (user_option)
            {
                case 0:
                    error_code = menu_error_code_success;
                    s_menu_context = menu_context_initiate_fat;
                    break;
                case 1:
                    error_code = menu_error_code_success;
                    s_menu_context = menu_context_directory;
                    break;
                default:
                    break;
            }
        }
        if (error_code_success != error_code)
        {
            menu_print_error(error_code);
        }
    }

    return error_code;
}

static void menu_print_error(fatfs_error_code_t error_code)
{
    switch (error_code)
    {
        case error_code_init_failed:
            printf("Error: failed to initiate FAT file system");
            break;
        case error_code_read_dir_failed:
            printf("Error: failed to read directory");
            break;
        case error_code_read_file_failed:
            printf("Error: failed to read file");
            break;
        case error_code_deinit_failed:
            printf("Error: failed to deinit");
            break;
        case menu_error_code_get_file_name_failed:
            printf("Error: failed to get file name");
            break;
        case menu_error_code_invalid_option:
            printf("Error: input option is invalid");
            break;
        default:
            break;
    }
}

/*******************************************************************************
* Public functions
******************************************************************************/

void menu(void)
{
    fatfs_error_code_t error_code;
    bool stop = false;

    while (!stop)
    {
        switch (s_menu_context)
        {
            case menu_context_initiate_fat:
                error_code = menu_initiate_fat();
                break;
            case menu_context_directory:
                error_code = menu_show_directory();
                break;
            case menu_context_file:
                error_code = menu_show_file();
                break;
            case menu_exit:
                stop = true;
                break;
            default:
                break;
        }
        if (stop && error_code_init_failed != error_code)
        {
            error_code = fatfs_deinit();
            if (error_code_success != error_code)
            {
                menu_print_error(error_code);
            }
        }
    }
}
