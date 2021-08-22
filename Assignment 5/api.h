#ifndef _API_
#define _API_

/*******************************************************************************
* Definitions
******************************************************************************/

/* Error codes to be returned */
typedef enum
{
    NO_ERROR,
    ERROR_INPUT_INVALID_POSITION,
    ERROR_INPUT_POSITION_HAD_VALUE,
    ERROR_INVALID_VALUE,
    ERROR_INPUT_VALUE_EXISTS,
    ERROR_DELETE_NON_EXISTING_VALUE
} api_errorcode_enum_t;

/*******************************************************************************
* API
******************************************************************************/

/*
* @brief Put a value into array at specified position
* @param index Position to put value in
* @param value Value to be put in position index
* @return Error code: api_errorcode_enum_t
*/
uint8_t api_input(uint8_t index, uint8_t value);

/*
* @brief Delete a value from array
* @param value Value to be deleted
* @return Error code: api_errorcode_enum_t
*/
uint8_t api_delete(uint8_t value);

/*
* @brief Print array in unsorted order
*/
void api_print_unsorted(void);

/*
* @brief Print array in sorted order
*/
void api_print_sorted(void);

#endif /* _API_ */
