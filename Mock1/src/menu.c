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
    menu_context_exit = 0,
    menu_context_directory = 1,
    menu_context_file = 2
} menu_context_t;

typedef enum
{
    menu_error_code_get_file_name_failed = 5,
    menu_error_code_invalid_option = 6
} menu_error_code_t;

/*******************************************************************************
* Variable
******************************************************************************/

static menu_context_t s_context = menu_context_directory;
static fatfs_entry_struct_t *s_list_head = NULL;
static uint8_t *s_file_buffer = NULL;
static uint32_t s_file_size;

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
    fatfs_entry_struct_t *entry = s_list_head;
    uint16_t index = 1;
    uint32_t user_option;

    /* Print directory list */
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
    retVal = menu_error_code_invalid_option;
    printf("\nEnter an option (enter 0 to exit): ");
    if (0 != scanf("%u", &user_option))
    {
        if (0 < user_option)
        {
            for (index = 1, entry = s_list_head; index != user_option && NULL != entry; index++)
            {
                entry = entry->next;
            }
            if (NULL != entry)
            {
                if (entry->is_subdir)
                {
                    retVal = fatfs_read_dir(entry->first_cluster, &s_list_head);
                }
                else
                {
                    /* Read file */
                    s_file_buffer = (uint8_t *)malloc(entry->rounded_size);
                    if (NULL != s_file_buffer)
                    {
                        retVal = fatfs_read_file(entry->first_cluster, &s_file_buffer, entry->rounded_size);
                    }
                }
            }
        }
    }

    return retVal;
}

static menu_context_t menu_show_file()
{
    uint32_t index;

    for (index = 0; index < size; index++)
    {
        printf("%x", buff[index]);
    }
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
    fatfs_error_code_t error_code = menu_error_code_invalid_option;
    int8_t file_path[261];
    fatfs_entry_struct_t *entry;
    uint16_t index = 1;
    bool exit_menu = false;

    printf("Enter file path: ");
    /* Get file name */
    if (0 != scanf("%[^\n]", &file_path[0]))
    {
        /* Init FAT */
        error_code = fatfs_init(&file_path[0]);
        if (error_code_success == error_code)
        {
            /* Read root directory */
            error_code = fatfs_read_dir(0, &s_list_head);
        }
    }
    else
    {
        error_code = menu_error_code_get_file_name_failed;
    }

    if (error_code_success == error_code)
    {
        while (!exit_menu)
        {
            switch (context)
            {
                case menu_context_directory:
                    error_code = menu_print_directory();
                    break;
                case menu_context_file:
                    error_code = menu_print_directory();
                    break;
                case menu_context_exit:
                    exit_menu = false;
                    break;
            }
            /* Get user option */
            printf("\nEnter an option (enter 0 to exit): ");
            fflush(stdin);
            if (0 != scanf("%u", &input) && 0 != input)
            {
                for (index = 1, entry = list_head; index != input && NULL != entry; index++)
                {
                    entry = entry->next;
                }
                if (NULL != entry)
                {
                    if (entry->is_subdir)
                    {
                        /* Read directory */
                        error_code = fatfs_read_dir(entry->first_cluster, &list_head);
                        if (error_code_success == error_code)
                        {
                            /* Print directory */
                            system("cls");
                            menu_print_directory(list_head);
                        }
                    }
                    else
                    {

                        if (error_code_success == error_code)
                        {
                            /* Print file */
                            system("cls");
                            menu_print_file(file_buffer, entry->rounded_size);
                            printf("\n\nDone. Press any key to close file...\n");
                            getch();
                            system("cls");
                            /* print current directory */
                            menu_print_directory(list_head);
                        }
                        free(file_buffer);
                    }
                }
            }
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
