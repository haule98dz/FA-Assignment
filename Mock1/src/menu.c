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
    menu_context_directory = 1,
    menu_context_file = 2
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

static menu_context_t s_menu_context = menu_context_directory;

/*******************************************************************************
* Prototypes
******************************************************************************/

/**
 * @brief Print list of entry
 *
 * @param entry_list Head of the list
 */
static menu_context_t menu_show_directory();

/**
 * @brief Print file content in hexa format
 *
 * @param buff Buffer data
 * @param size Size of buffer data
 */
static menu_context_t menu_show_file(uint8_t *buff, uint32_t size);

/**
 * @brief Print error
 *
 * @param error_code Error code
 */
static void menu_print_error(fatfs_error_code_t error_code);

/*******************************************************************************
* Static functions
******************************************************************************/

static menu_error_code_t menu_show_directory()
{
    menu_error_code_t retVal;
    static fatfs_entry_struct_t *sp_list_head = NULL;
    fatfs_entry_struct_t *entry = sp_list_head;
    uint16_t index;
    uint32_t user_option;

    /* Read directory list */
    retVal = fatfs_read_dir((*selected_entry)->first_cluster, sp_list_head);

    /* Print directory list */
    system("cls");
    printf("Option   Name     Type     File size   Modified   \n");
    for (index = 1; NULL != entry; index++)
    {
        printf("   %-5d   ", index);
        printf("%-20s", entry->name);
        if (0x2E != entry->name[0])
        {
            if (entry->is_subdir)
            {
                printf("%-10s", "Folder");
            }
            else
            {
                printf("%-10s", entry->extension);
                printf("%-8d bytes", entry->size);
            }
            printf("    %02d/%02d/%04d %02d:%02d\n", entry->modified_time.day, entry->modified_time.month, entry->modified_time.year, entry->modified_time.hour, entry->modified_time.minute);
        }
        entry = entry->next;
    }

    /* Get user's option */
    printf("\nEnter an option (enter 0 to exit): ");
    retVal = menu_error_code_invalid_option;
    if (0 != scanf("%u", &user_option))
    {
        if (0 < user_option)
        {
            for (index = 1, entry = sp_list_head; index != user_option && NULL != entry; index++)
            {
                entry = entry->next;
            }
            if (NULL != entry)
            {
                retVal = menu_error_code_success;
                *selected_entry = entry;
                if (entry->is_subdir)
                {
                    s_menu_context = menu_context_directory;
                }
                else
                {
                    s_menu_context = menu_context_file;
                }
            }
        }
        else
        {
            retVal = menu_error_code_success;
            s_menu_context = menu_exit;
        }
    }

    return retVal;
}

static menu_error_code_t menu_show_file(fatfs_entry_struct_t *selected_entry)
{
    menu_error_code_t retVal;
    uint32_t index;
    static uint8_t *sp_file_buffer = NULL;


    /* Read file */
    retVal = fatfs_read_file(selected_entry->first_cluster, &sp_file_buffer, selected_entry->rounded_size);

    if (error_code_success == retVal)
    {
        /* Print file */
        system("cls");
        for (index = 0; index < selected_entry->rounded_size; index++)
        {
            printf("%x", sp_file_buffer[index]);
        }

        /* Get user's option */
        printf("\nEnter 1 to return to subdirectory, enter 0 to exit: ");
        if (0 != scanf("%u", &user_option))
        {
            switch (user_option)
            {
                case 0:
                    s_menu_context = menu_exit;
                    break;
                case 1:
                    s_menu_context = menu_context_directory;
                    break;
                default:
                    retVal = menu_error_code_invalid_option;
                    break;
            }
        }
        else
        {
            retVal = menu_error_code_invalid_option;
        }
    }

    return retVal;
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
    int8_t file_path[261];
    fatfs_entry_struct_t *user_selection = NULL;
    bool stop = false;

    printf("Enter file path: ");
    /* Get file name */
    if (0 != scanf("%[^\n]", &file_path[0]))
    {
        /* Init FAT */
        error_code = fatfs_init(&file_path[0]);
        if (error_code_success == error_code)
        {
            /* Read root directory */
            error_code = fatfs_read_dir(&user_option);
        }
    }
    else
    {
        error_code = menu_error_code_get_file_name_failed;
    }

    if (error_code_success == error_code)
    {
        while (!stop)
        {
            switch (s_menu_context)
            {
                case menu_context_directory:
                    error_code = menu_show_directory(&user_selection);
                    break;
                case menu_context_file:
                    error_code = menu_show_file(user_selection);
                    break;
                case menu_exit:
                    stop = true;
                    break;
            }
        }
    }

    if (error_code_success == error_code)
    {
        error_code = fatfs_deinit();
    }

    if (error_code_success != error_code)
    {
        menu_print_error(error_code);
    }
}
