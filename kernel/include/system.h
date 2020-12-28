#ifndef SYSTEM_H
#define SYSTEM_H

#include "stdint.h"

typedef volatile uint32_t reg32_rw_t;
typedef volatile const uint32_t reg32_ro_t;
typedef volatile uint32_t reg32_wo_t;

typedef volatile uint64_t reg64_rw_t;
typedef volatile const uint64_t reg64_ro_t;

#define MMIO_BASE 0x3F000000
#define GPIO_BASE       ( MMIO_BASE + 0x200000 )
#define MAILBOX0_BASE    ( MMIO_BASE + 0xB880 )
/* NOTE: Can this be detected automagically? */
#define SYSFREQ 		250000000

#endif
