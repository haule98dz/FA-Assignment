/**
 * @brief Hardware Abstraction Layer
 */

#ifndef _HAL_
#define _HAL_

/*******************************************************************************
* API
******************************************************************************/

/**
 * @brief Open FAT image file
 *
 * @return true If open successfully
 * @return false If open failed
 */
bool kmc_open(int8_t* filePath);

/**
 * @brief Updade sector size (number of bytes per sector)
 *
 * @param sector_size New value of sector size
 * @return true If input is valid sector size
 * @return false If input is invalid sector size
 */
bool kmc_update_sector_size(uint32_t sector_size);

/**
 * @brief Read a sectors, store data in buffer
 *
 * @param index Index of the sector
 * @param buff Buffer array to store data
 * @return int32_t Number of bytes read
 */
int32_t kmc_read_sector(uint32_t index, uint8_t *buff);

/**
 * @brief Read multiple sectors, store data in buffer
 *
 * @param index Index of the starting sector
 * @param num Number of sectors to read
 * @param buff Buffer array to store data
 * @return int32_t Number of bytes read
 */
int32_t kmc_read_multi_sector(uint32_t index, uint32_t num, uint8_t *buff);

/**
 * @brief Close FAT image file
 *
 * @return true If close successfully
 * @return false If close failed
 */
bool kmc_close(void);

#endif /* _HAL_ */
