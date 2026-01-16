#ifndef DRV_FLASH_H
#define DRV_FLASH_H

#include <flashdb.h>
#include "board.h"

#ifdef __cplusplus
extern "C" {
#endif

fdb_err_t flashdb_init(void);
fdb_err_t flashdb_read(FLASHDB_KEY_INDEX const index);
fdb_err_t flashdb_write(FLASHDB_KEY_INDEX const index);
fdb_err_t flashdb_key_register(FLASHDB_KEY_INDEX const index, char *key, void *value, size_t value_len);
fdb_err_t flashdb_key_delete(FLASHDB_KEY_INDEX const index);

#ifdef __cplusplus
}
#endif

#endif /* DRV_FLASH_H */
