/*
 * Copyright (c) 2020, Armink, <armink.ztl@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _FAL_CFG_H_
#define _FAL_CFG_H_

#define FAL_DEBUG 0
#define FAL_PART_HAS_TABLE_CFG

/* ===================== Flash device Configuration ========================= */
extern struct fal_flash_dev nor_flash0;

/* the flash write granularity, unit: bit
 * only support 1(nor flash)/ 8(stm32f2/f4)/ 32(stm32f1)/ 64(stm32f7)/ 128(stm32h5) */
#define FDB_WRITE_GRAN        1        /* @note you must define it for a value */

/* flash device table */
#define FAL_FLASH_DEV_TABLE     \
{                               \
    &nor_flash0,                \
}

/* ====================== Partition Configuration ========================== */
#ifdef FAL_PART_HAS_TABLE_CFG
/* partition table */
#define FAL_PART_TABLE                                                                                              \
{                                                                                                                   \
    {FAL_PART_MAGIC_WORD,         "bl",    "norflash0",         0,  128*1024, 0}, /* Bootloader: 128K */            \
    {FAL_PART_MAGIC_WORD,        "app",    "norflash0",  128*1024, 2048*1024, 0}, /* Application: 2048K */          \
    {FAL_PART_MAGIC_WORD, "app_backup",    "norflash0", 2176*1024, 1024*1024, 0}, /* Application Backup: 1024K */   \
    {FAL_PART_MAGIC_WORD,   "kv_param",    "norflash0", 3200*1024, 2048*1024, 0}, /* kv_param: 2048K */             \
    /* ...  more partition norflash0 max size: 8192K */ \
}
#endif /* FAL_PART_HAS_TABLE_CFG */

/* PRINTF NOT USED */
#define FAL_PRINTF(...)              /* nothing */

#endif /* _FAL_CFG_H_ */
