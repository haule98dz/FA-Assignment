/**
 * @file read_file.h
 * @author HauLD3
 * @brief A program to browse FAT12 disk.
 *
 */

/*******************************************************************************
* Includes
******************************************************************************/

#include <stdbool.h>
#include <stdint.h>
#include "fat12.h"
#include "read_file.h"

/*******************************************************************************
* Codes API
******************************************************************************/

void read_file_exec(void)
{
    fat12_init();
    fat12_open_root();
}
