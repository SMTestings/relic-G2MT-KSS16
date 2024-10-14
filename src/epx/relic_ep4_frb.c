/*
 * RELIC is an Efficient LIbrary for Cryptography
 * Copyright (c) 2021 RELIC Authors
 *
 * This file is part of RELIC. RELIC is legal property of its developers,
 * whose names are not listed here. Please refer to the COPYRIGHT file
 * for contact information.
 *
 * RELIC is free software; you can redistribute it and/or modify it under the
 * terms of the version 2.1 (or later) of the GNU Lesser General Public License
 * as published by the Free Software Foundation; or version 2.0 of the Apache
 * License as published by the Apache Software Foundation. See the LICENSE files
 * for more details.
 *
 * RELIC is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the LICENSE files for more details.
 *
 * You should have received a copy of the GNU Lesser General Public or the
 * Apache License along with RELIC. If not, see <https://www.gnu.org/licenses/>
 * or <https://www.apache.org/licenses/>.
 */

/**
 * @file
 *
 * Implementation of frobenius action on prime elliptic curves over a quartic
 * extension field.
 *
 * @ingroup epx
 */

#include "relic_core.h"

/*============================================================================*/
/* Public definitions                                                         */
/*============================================================================*/

void ep4_frb(ep4_t r, const ep4_t p, int i) {
	ep4_copy(r, p);
	for (; i > 0; i--) {
		fp4_frb(r->x, r->x, 1);
		fp4_frb(r->y, r->y, 1);
		fp4_frb(r->z, r->z, 1);
		fp4_mul_frb(r->x, r->x, 1, 2);
		fp4_mul_frb(r->y, r->y, 1, 3);
	}
}

void ep4_tau(ep4_t r, const ep4_t p){
	ep4_t s;
	ep4_null(s);
	ep4_new(s);

	ep4_frb(s,p,1);
	fp4_neg(r->x, s->x);
	fp4_neg(r->y,s->y);
	fp4_copy(r->z,s->z);
	for(int i=0;i<2;i++) for(int j=0;j<2;j++) fp_mul(r->y[i][j],r->y[i][j],ep_curve_get_beta());
	ep4_dbl(r,r);
	ep4_sub(r,r,s);

	ep4_free(s);
}