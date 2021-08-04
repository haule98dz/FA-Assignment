/**
 * @brief A program to browse FAT file system.
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
#include "read_file.h"

/*******************************************************************************
* Prototypes
******************************************************************************/

/**
 * @brief Print list of entry
 *
 * @param entry_list Head of the list
 */
void readfile_print_entry_list(fatfs_entry_struct_t *entry_list);

/**
 * @brief Print error
 *
 * @param error_code Error code
 */
void readfile_print_error(fatfs_error_code_t error_code);

/**
 * @brief Print file content in hexa format
 *
 * @param buff Buffer data
 * @param size Size of buffer data
 */
void readfile_print_file(uint8_t *buff, uint32_t size);

/*******************************************************************************
* Static functions
******************************************************************************/

void readfile_print_entry_list(fatfs_entry_struct_t *entry_list)
{

    fatfs_entry_struct_t *entry = entry_list;
    uint8_t day;
    uint8_t month;
    uint16_t year;
    uint8_t hour;
    uint8_t minute;

    system("cls");
    printf("   Option    Name     Type     Modified      File size\n");
    while (NULL != entry)
    {
        printf(" %-6d", entry->index);
        printf("%-24s", entry->name);
        if (entry->is_subdir)
        {
            printf("%-10s", "subdir");
            printf("    %02d/%02d/%4d %02d:%02d    ", day, month, year, hour, minute);
        }
        else
        {
            printf("%-10s", entry->extension);
            day = entry->modified_time.day;
            month = entry->modified_time.month;
            year = entry->modified_time.year;
            hour = entry->modified_time.hour;
            minute = entry->modified_time.minute;
            printf("  %02d/%02d/%4d %02d:%02d  ", day, month, year, hour, minute);
            printf("%-8d kByte", entry->file_size);
        }
        putchar('\n');
        entry = entry->next;
    }
}

void readfile_print_file(uint8_t *buff, uint32_t size)
{

    uint32_t index;

    system("cls");
    for (index = 0; index < size; index++)
    {
        printf("%x", buff[index]);
    }
}

void readfile_print_error(fatfs_error_code_t error_code)
{
    switch (error_code)
    {
    case error_code_open_failed:
        printf("Error: failed to open FAT file system");
        break;
    case error_code_read_boot_failed:
        printf("Error: failed to read parameters from boot sector");
        break;
    case error_code_invalid_entry_index:
        printf("Error: invalid input option");
        break;
    case error_code_invalid_entry:
        printf("Error: entry is invalid");
        break;
    case error_code_close_failed:
        printf("Error: failed to close file system");
        break;
    }
}

/*******************************************************************************
* Public functions
******************************************************************************/

void readfile_exec(void)
{

    fatfs_error_code_t error_code;
    int8_t file_path[261];
    fatfs_entry_struct_t *entry_list_head = NULL;
    fatfs_entry_struct_t *entry = NULL;
    uint32_t input;
    uint16_t index;
    uint8_t *file_buffer;
    uint32_t file_size;

    printf("Enter file path: ");
    if (fgets(&file_path[0], 260, stdin))
    {
        file_path[strlen(file_path) - 1] = '\0';                  /* Remove \n character */
        error_code = fatfs_init(&file_path[0], &entry_list_head); /* Init FAT */
        /* Print root directory */
        if (error_code_success == error_code)
        {
            readfile_print_entry_list(entry_list_head);
        }
        else
        {
            readfile_print_error(error_code);
        }
    }
    else
    {
        error_code = error_code_open_failed;
    }

    if (error_code_success == error_code)
    {
        do
        {
            printf("\nEnter an option (enter 0 to exit): ");
            fflush(stdin);
            if (0 != scanf("%u%*c", &input))
            {
                if (input > 0)
                {
                    entry = entry_list_head;
                    error_code = error_code_invalid_entry_index;
                    while (NULL != entry)
                    {
                        if (input == entry->index)
                        {
                            error_code = error_code_success;
                            break;
                        }
                        else
                        {
                            entry = entry->next;
                        }
                    }

                    if (error_code_success == error_code)
                    {
                        if (entry->is_subdir)
                        {
                            error_code = fatfs_open_dir(entry, &entry_list_head);
                            if (error_code_success == error_code)
                            {
                                readfile_print_entry_list(entry_list_head);
                            }
                        }
                        else
                        {
                            error_code = fatfs_open_file(entry, &file_buffer, &file_size);
                            if (error_code_success == error_code)
                            {
                                readfile_print_file(file_buffer, file_size);
                                printf("\n\nDone. Press any key to close file...");
                                getch();
                                readfile_print_entry_list(entry_list_head);
                            }
                        }
                    }

                    if (error_code_success != error_code)
                    {
                        readfile_print_error(error_code);
                    }
                }
            }
            else
            {
                readfile_print_error(error_code_invalid_entry_index);
            }
        } while (input > 0);

        error_code = fatfs_deinit();
        if (error_code_success != error_code)
        {
            readfile_print_error(error_code);
        }
    }
}
