/**
 * @file api_srec_check.c
 * @author HauLD3
 * @brief This module provides APIs to check one single record from a S-record file.
 * @date 2021-07-21
 *
 */

/*******************************************************************************
* Includes
******************************************************************************/

#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include "api_srec_check.h"

/*******************************************************************************
* Prototypes
******************************************************************************/

/**
 * @brief Convert 2 hexa character to a uint8_t number.
 *
 * @param char_high The hex char that represents the most significant 4 bits.
 * @param char_low The hex char that represents the least significant 4 bits.
 * @return uint8_t Result of the conversion.
 */
static uint8_t HexChar_To_Byte(char char_high, char char_low);

/**
 * @brief Convert 1 hexa character to a uint8_t number.
 *        This function is called 2 times in 'HexChar_To_Byte' function.
 *
 * @param hex_char The hex char that represents the hexa value.
 * @return uint8_t Result of the conversion.
 */
static uint8_t HexChar_To_HexDigit(char hex_char);

/**
 * @brief Detect whether a character is a valid hexa character.
 *        This function is an inline function.
 *
 * @param ch Input character.
 * @return true if the character is a valid hexa character.
 * @return false if the character is not a valid hexa character.
 */
static inline bool Is_HexChar(char ch);

/**
 * @brief Get value of address in record.
 *        This function is called when checking S5, S6.
 * @param record Pointer to the buffer that store content of the record.
 * @return uint32_t Address in integer.
 */
static uint32_t Get_Address(char *record);

/*******************************************************************************
* Codes API
******************************************************************************/

bool SREC_Check_S_Format(char *record)
{

    bool retVal = true;

    if (record[0] != 'S' || record[1] < '0' || record[1] > '9')
    {
        retVal = false;
    }

    return retVal;
}

bool SREC_Check_Hexa_Format(char *record)
{

    bool retVal = true;
    uint32_t i;
    uint16_t record_len = 0;

    record_len = strlen(record);
    for (i = 2; i < record_len && retVal == true; i++)
    {
        if (!Is_HexChar(record[i]))
        {
            retVal = false;
        }
    }

    return retVal;
}

bool SREC_Check_ByteCount(char *record)
{

    bool retVal = true;
    uint8_t bytecount = 0;   /* The byte count in s record */
    uint16_t char_count = 0; /* The number of characters after byte count, must equal 2 times the bytecount*/

    bytecount = HexChar_To_Byte(record[2], record[3]);
    char_count = strlen(record) - 4; /* exclude 2 chars of s type and 2 chars of bytecount */

    /* number of chars must be even, and number of bytes must equal bytecount */
    if (char_count % 2 != 0 || char_count / 2 != bytecount)
    {
        retVal = false;
    }

    return retVal;
}

bool SREC_Check_Checksum(char *record)
{

    uint8_t checksum = 0;            /* The checksum byte in the record */
    uint8_t checksum_calculated = 0; /* The actual checksum that is calculated from record */
    uint16_t sum = 0;                /* Sum of the bytes */
    uint16_t checksum_position;      /* Position where the checksum byte is located */
    uint16_t index = 0;

    checksum_position = strlen(record) - 2;
    for (index = 2; index < checksum_position; index += 2)
    {
        sum += HexChar_To_Byte(record[index], record[index + 1]);
    }
    checksum_calculated = ~((uint8_t)sum);
    checksum = HexChar_To_Byte(record[checksum_position], record[checksum_position + 1]);

    return (checksum_calculated == checksum);
}

bool SREC_Check_S5_S6_Format(char* record)
{
    bool retVal = true;
    char type;
    uint16_t len;

    type = record[1];
    len = strlen(record);

    if (type == '5')
    {
        retVal = (len == 10);
    }
    else if (type == '6')
    {
        retVal = (len == 12);
    }

    return retVal;
}

bool SREC_Check_S5_S6_Count(char *record, uint32_t data_line_count)
{
    return (data_line_count == Get_Address(record));
}

/*******************************************************************************
* Codes static
******************************************************************************/

static uint32_t Get_Address(char *record)
{

    uint32_t retVal = 0;
    uint8_t buffer[4]; /* Store up to 4 bytes of address field */

    switch (record[1])
    {
    case '3':
    case '7':
        /* 32 bit address */
        buffer[3] = HexChar_To_Byte(record[4], record[5]);
        buffer[2] = HexChar_To_Byte(record[6], record[7]);
        buffer[1] = HexChar_To_Byte(record[8], record[9]);
        buffer[0] = HexChar_To_Byte(record[10], record[11]);
        retVal = buffer[3];
        retVal <<= 8;
        retVal |= buffer[2];
        retVal <<= 8;
        retVal |= buffer[1];
        retVal <<= 8;
        retVal |= buffer[0];
        break;
    case '2':
    case '6':
    case '8':
        /* 24 bit address */
        buffer[2] = HexChar_To_Byte(record[4], record[5]);
        buffer[1] = HexChar_To_Byte(record[6], record[7]);
        buffer[0] = HexChar_To_Byte(record[8], record[9]);
        retVal = buffer[2];
        retVal <<= 8;
        retVal |= buffer[1];
        retVal <<= 8;
        retVal |= buffer[0];
        break;
    default:
        /* 16 bit address */
        buffer[1] = HexChar_To_Byte(record[4], record[5]);
        buffer[0] = HexChar_To_Byte(record[6], record[7]);
        retVal = buffer[1];
        retVal <<= 8;
        retVal |= buffer[0];
        break;
    }

    return retVal;
}

static uint8_t HexChar_To_Byte(char char_high, char char_low)
{

    uint8_t hex_high;
    uint8_t hex_low;

    hex_high = HexChar_To_HexDigit(char_high);
    hex_low = HexChar_To_HexDigit(char_low);

    return (uint8_t)((hex_high << 4) | hex_low);
}

static uint8_t HexChar_To_HexDigit(char hex_char)
{
    uint8_t hex_digit = 0;

    if (hex_char >= '0' && hex_char <= '9')
    {
        hex_digit = (uint8_t)(hex_char - '0');
    }
    else if (hex_char >= 'A' && hex_char <= 'F')
    {
        hex_digit = (uint8_t)(hex_char - 'A' + 10);
    }
    else if (hex_char >= 'a' && hex_char <= 'f')
    {
        hex_digit = (uint8_t)(hex_char - 'a' + 10);
    }

    return hex_digit;
}

static inline bool Is_HexChar(char ch)
{
    return ((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F'));
}
