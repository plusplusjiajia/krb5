/* -*- mode: c; c-basic-offset: 4; indent-tabs-mode: nil -*- */
/*
 * These routines check and fix parity of encryption keys for the DES
 * algorithm.
 *
 * They are a replacement for routines in key_parity.c, that don't require
 * the table building that they do.
 *
 * Mark Eichin -- Cygnus Support
 */

#include "crypto_int.h"

/*
 * des_fixup_key_parity: Forces odd parity per byte; parity is bits
 *                       8,16,...64 in des order, implies 0, 8, 16, ...
 *                       vax order.
 */
#define smask(step) ((1<<step)-1)
#define pstep(x,step) (((x)&smask(step))^(((x)>>step)&smask(step)))
#define parity_char(x) pstep(pstep(pstep((x),4),2),1)

void
mit_des_fixup_key_parity(unsigned char *key)
{
    unsigned int i;
    for (i = 0; i < 8; i++) {
        key[i] &= 0xfe;
        key[i] |= 1^parity_char(key[i]);
    }
}