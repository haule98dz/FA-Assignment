/**
 * @brief Hardware Abstraction Layer
 */

/*******************************************************************************
* Includes
******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "HAL.h"

/*******************************************************************************
* Definitions
******************************************************************************/

#define KMC_DEFAULT_SECTOR_SIZE (512U)

/*******************************************************************************
* Variables
******************************************************************************/

static FILE *s_kmc_file = NULL;
static uint32_t s_kmc_sector_size = KMC_DEFAULT_SECTOR_SIZE;

/*******************************************************************************
* Public functions
******************************************************************************/

bool kmc_open(int8_t *file_path)
{
    bool retVal = false;

    s_kmc_file = fopen(file_path, "rb");
    if (NULL != s_kmc_file)
    {
        retVal = true;
        s_kmc_sector_size = KMC_DEFAULT_SECTOR_SIZE;
    }

    return retVal;
}

bool kmc_update_sector_size(uint32_t sector_size)
{
    bool retVal = false;

    if (0 == sector_size % KMC_DEFAULT_SECTOR_SIZE)
    {
        s_kmc_sector_size = sector_size;
    }

    return retVal;
}

int32_t kmc_read_sector(uint32_t index, uint8_t *buff)
{
    int32_t retVal = -1;
    uint32_t position_in_file = index * s_kmc_sector_size;

    if (0 == fseek(s_kmc_file, position_in_file, SEEK_SET))
    {
        retVal = (int32_t)fread(buff, sizeof(uint8_t), s_kmc_sector_size, s_kmc_file);
    }

    return retVal;
}

int32_t kmc_read_multi_sector(uint32_t index, uint32_t num, uint8_t *buff)
{
    int32_t retVal = -1;
    uint32_t position_in_file = index * s_kmc_sector_size;
    uint32_t number_of_byte = num * s_kmc_sector_size;

    if (0 == fseek(s_kmc_file, position_in_file, SEEK_SET))
    {
        retVal = (uint32_t)fread(buff, sizeof(uint8_t), num * s_kmc_sector_size, s_kmc_file);
    }

    return retVal;
}

bool kmc_close(void)
{
    bool retVal = true;

    if (0 != fclose(s_kmc_file))
    {
        retVal = false;
    }

    return retVal;
}
