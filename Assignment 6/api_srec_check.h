/**
 * @file api_srec_check.h
 * @author HauLD3
 * @brief This module provides APIs to check one single record from a S-record file.
 * @date 2021-07-21
 *
 */

#ifndef _API_SREC_CHECK_
#define _API_SREC_CHECK_

/*******************************************************************************
* API
******************************************************************************/

/**
 * @brief Check whether the record begins with 'S' and a number '0' to '9'.
 *
 * @param record Pointer to the buffer that store content of the record.
 * @return true if the record passed the check.
 * @return false if the record failed the check.
 */
bool SREC_Check_S_Format(char* record);


/**
 * @brief Check whether all the characters is hexa character '0' to 'F'.
 *
 * @param record Pointer to the buffer that store content of the record.
 * @return true if the record passed the check.
 * @return false if the record failed the check.
 */
bool SREC_Check_Hexa_Format(char* record);


/**
 * @brief Check whether the actual number of bytes is equal to bytecount.
 *
 * @param record Pointer to the buffer that store content of the record.
 * @return true if the record passed the check.
 * @return false if the record failed the check.
 */
bool SREC_Check_ByteCount(char* record);


/**
 * @brief Check whether the actual checksum is equal to checksum byte.
 *
 * @param record Pointer to the buffer that store content of the record.
 * @return true if the record passed the check.
 * @return false if the record failed the check.
 */
bool SREC_Check_Checksum(char* record);

/**
 * @brief Check if S5 must have exactly 10 characters and S6 must have exactly 12 characters,
 *        Or else its address size is invalid.
 *        Applied only for S5 or S6 record.
 *
 * @param record Pointer to the buffer that store content of the record.
 * @return true Pointer to the buffer that store content of the record.
 * @return false if the record failed the check.
 */
bool SREC_Check_S5_S6_Format(char* record);

/**
 * @brief Check whether the actual number-of-data-record is equal to the data-record-count in S5 or S6.
 *        Applied only for S5 or S6 record.
 *
 * @param record Pointer to the buffer that store content of the record.
 * @return true Pointer to the buffer that store content of the record.
 * @return false if the record failed the check.
 */
bool SREC_Check_S5_S6_Count(char* record, uint32_t data_record_count);

#endif /* _API_SREC_CHECK_ */
