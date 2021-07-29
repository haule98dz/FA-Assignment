/**
 * @brief Provides APIs to browse FAT File System.
 */

#ifndef _FATFS_
#define _FATFS_

/*******************************************************************************
* API
******************************************************************************/

/**
 * @brief Initiate FAT12 parameters: Read BPB, calculate the positions of 4 regions in fat12 disk
 *
 * @return true if initiate successfully
 * @return false if initiate failed
 */
bool fatfs_init(void);

#endif /* _FAT12_ */
