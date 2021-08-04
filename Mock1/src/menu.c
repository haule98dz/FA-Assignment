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
    menu_directory = 1,
    menu_file = 2
} menu_navigate_t;

typedef enum
{
    menu_error_code_get_file_name_failed = 5,
    menu_error_code_invalid_option = 6
} menu_error_code_t;

/*******************************************************************************
* Variable
******************************************************************************/


/*******************************************************************************
* Prototypes
******************************************************************************/

/**
 * @brief Print list of entry
 *
 * @param entry_list Head of the list
 */
static void menu_print_directory(fatfs_entry_struct_t *entry_list);

/**
 * @brief Print error
 *
 * @param error_code Error code
 */
static void menu_print_error(fatfs_error_code_t error_code);

/**
 * @brief Print file content in hexa format
 *
 * @param buff Buffer data
 * @param size Size of buffer data
 */
static void menu_print_file(uint8_t *buff, uint32_t size);

/*******************************************************************************
* Static functions
******************************************************************************/

static void menu_print_directory(fatfs_entry_struct_t *entry_list)
{
    fatfs_entry_struct_t *entry = entry_list;
    uint16_t user_option = 1;

    printf("Option   Name     Type     File size   Modified   \n");
    for (user_option = 1; NULL != entry; user_option++)
    {
        printf("   %-5d   ", user_option);
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
}

static void menu_print_file(uint8_t *buff, uint32_t size)
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
    fatfs_entry_struct_t *list_head = NULL;
    fatfs_entry_struct_t *entry;
    uint32_t input = 1;
    uint16_t index;
    uint8_t *file_buffer;

    printf("Enter file path: ");
    /* Get file name */
    if (0 != scanf("%[^\n]", &file_path[0]))
    {
        /* Init FAT */
        error_code = fatfs_init(&file_path[0]);
        if (error_code_success == error_code)
        {
            /* Read root directory */
            error_code = fatfs_read_dir(0, &list_head);
            if (error_code_success == error_code)
            {
                /* Print root directory */
                menu_print_directory(list_head);
            }
        }
    }
    else
    {
        error_code = menu_error_code_get_file_name_failed;
    }

    if (error_code_success == error_code)
    {
        do
        {
            switch ()
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
                        /* Read file */
                        file_buffer = (uint8_t *)malloc(entry->rounded_size);
                        if (NULL != file_buffer)
                        {
                            error_code = fatfs_read_file(entry->first_cluster, &file_buffer, entry->rounded_size);
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
        } while (input > 0);
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
