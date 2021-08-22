/**
 * @file SREC_Parser.c
 * @author HauLD3
 * @brief This is the S-record parser program.
 *        It checks and prints out all the errors.
 *        If no error is encounted, all data will be print.
 *        It uses APIs from api_srec_check.h
 *
 * @date 2021-07-21
 *
 */

/*******************************************************************************
* Includes
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "SREC_Parser.h"
#include "api_srec_check.h"

/*******************************************************************************
* Definitions
******************************************************************************/

enum SREC_ErrorCode_enum_t
{
    NO_ERROR,
    ERROR_S_TYPE,       /* First character is not 'S' or type is not a number */
    ERROR_HEXA_FORMAT,  /* Contain non-hexa character */
    ERROR_BYTE_COUNT,   /* Wrong byte count */
    ERROR_CHECK_SUM,    /* Wrong checksum */
    ERROR_S5_S6_FORMAT, /* Wrong number of bytes at record S5 (or S6) */
    ERROR_S5_S6_COUNT   /* Wrong number of data records at record S5 (or S6) */
};

/*******************************************************************************
* Prototypes
******************************************************************************/

/**
 * @brief Check S-record file to find errors, print out all the errors.
 *
 * @param srec_file The S-record file to check
 * @return true If the S-record file has no error
 * @return false If the S-record file has at least one error
 */
static bool Check_SREC_File(FILE *srec_file);

/**
 * @brief Print address and data of all data records (S1, S2, S3).
 *        The address and data come directly from the text in the record, no conversion is operated.
 *
 * @param srec_file
 */
static void Print_SREC_Data(FILE *srec_file);

/**
 * @brief Print out the error base on error code.
 *
 * @param error_code Error code
 * @param record_number record number
 */
static void Print_Error(enum SREC_ErrorCode_enum_t error_code, uint32_t record_number);

/*******************************************************************************
* Codes API
******************************************************************************/

void SREC_Parser(void)
{

    char file_name[256];
    int file_name_length;
    FILE *srec_file = NULL;
    char user_response;   /* This char is used to get user's response whether they want to continue or not */
    bool flag_run = true; /* Set this to false to exit the program (because exit() is not allowed) */

    do
    {
        system("cls");
        printf("----S RECORD PARSER PROGRAM----\n");
        printf("Please enter file name (with full location):\n");

        /* Read until encounter \n, then read and discard the \n */
        fflush(stdin);
        scanf("%[^\n]%*c", file_name);

        srec_file = fopen(file_name, "r");
        if (srec_file == NULL)
        {
            printf(file_name);
            perror("Failed to open file");
        }
        else
        {
            printf("File opened successfully. Start parsing...\n\n");
            if (Check_SREC_File(srec_file))
            {
                printf("\nNo error, start printing data:\n");
                Print_SREC_Data(srec_file);
                printf("\nDone.");
            }
            else
            {
                printf("\nAs the record is error, no data will be printed.\n");
            }
        }

        fclose(srec_file);

        /* This loop continues until get 'y' or 'n' from user */
        do
        {
            printf("\nDo you want to continue with another SREC file? (y/n): ");
            fflush(stdin);
            user_response = getchar();
            if (user_response == 'n')
            {
                flag_run = false;
            }
        } while (flag_run && user_response != 'y');

    } while (flag_run);
}

/*******************************************************************************
* Codes static
******************************************************************************/

static bool Check_SREC_File(FILE *srec_file)
{

    bool no_error = true;           /* The return value */
    char buffer_record[516];        /* Buffer string for a record */
    uint32_t record_number = 0;     /* Total number of records */
    uint32_t count_data_record = 0; /* Number of records that is S1, S2 or S3 */
    char s_type;

    rewind(srec_file);
    while (fgets(buffer_record, 516, srec_file) != NULL)
    {
        buffer_record[strlen(buffer_record) - 1] = '\0'; /* Remove the newline character */
        record_number++;
        s_type = (char)buffer_record[1];

        if (s_type >= '1' && s_type <= '3')
        {
            /* Count data record */
            count_data_record++;
        }

        /* check record */
        if (!SREC_Check_S_Format(buffer_record))
        {
            Print_Error(ERROR_S_TYPE, record_number);
            no_error = false;
        }
        else if (!SREC_Check_Hexa_Format(buffer_record))
        {
            Print_Error(ERROR_HEXA_FORMAT, record_number);
            no_error = false;
        }
        else if (!SREC_Check_ByteCount(buffer_record))
        {
            Print_Error(ERROR_BYTE_COUNT, record_number);
            no_error = false;
        }
        else if (!SREC_Check_Checksum(buffer_record))
        {
            Print_Error(ERROR_CHECK_SUM, record_number);
            no_error = false;
        }

        if (s_type == '5' || s_type == '6')
        {
            if (!SREC_Check_S5_S6_Format(buffer_record))
            {
                Print_Error(ERROR_S5_S6_FORMAT, record_number);
                no_error = false;
            }

            if (no_error) /* Including all error checking results */
            {
                if (!SREC_Check_S5_S6_Count(buffer_record, count_data_record))
                {
                    Print_Error(ERROR_S5_S6_COUNT, record_number);
                    no_error = false;
                }
            }
        }
    }
    rewind(srec_file);

    return no_error;
}

static void Print_SREC_Data(FILE *srec_file)
{

    char buffer_record[516]; /* Buffer string for a record (Max size of a record in SREC is 514 bytes plus 1 newline and 1 termination character) */
    uint8_t address_end = 0; /* The position where the address field ends (index of first character of data field) */
    uint16_t data_end = 0;   /* The position where the data field ends */
    uint16_t index = 0;
    bool is_data_record = false; /* record is S1, S2 or S3 */

    /* Print out address and data if the record is S1, S2 or S3 */
    rewind(srec_file);
    while (fgets(buffer_record, 516, srec_file) != NULL)
    {
        is_data_record = true;

        switch (buffer_record[1])
        {
        case '1':
            address_end = 8;
            break;
        case '2':
            address_end = 10;
            break;
        case '3':
            address_end = 12;
            break;
        default:
            is_data_record = false;
            break;
        }

        if (is_data_record)
        {
            /* print address */
            printf("0x");
            for (index = 4; index < address_end; index++)
            {
                putchar(buffer_record[index]);
            }

            /* print data */
            printf("     ");
            data_end = strlen(buffer_record) - 3;
            for (index = address_end; index < data_end; index += 2)
            {
                putchar(buffer_record[index]);
                putchar(buffer_record[index + 1]);
                putchar(' ');
            }
            putchar('\n');
        }
    }
    rewind(srec_file);
}

static void Print_Error(enum SREC_ErrorCode_enum_t error_code, uint32_t record_number)
{
    printf("Error in record %d: ", record_number);
    switch (error_code)
    {
    case ERROR_S_TYPE:
        printf("Wrong S-type syntax");
        break;
    case ERROR_HEXA_FORMAT:
        printf("Contains non-hexa character(s)");
        break;
    case ERROR_BYTE_COUNT:
        printf("Wrong byte count");
        break;
    case ERROR_CHECK_SUM:
        printf("Wrong checksum");
        break;
    case ERROR_S5_S6_FORMAT:
        printf("Wrong size of address in S5 or S6");
        break;
    case ERROR_S5_S6_COUNT:
        printf("Wrong number of data records in S5 or S6");
        break;
    }
    printf(".\n");
}
