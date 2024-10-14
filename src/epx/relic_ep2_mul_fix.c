/*
 * RELIC is an Efficient LIbrary for Cryptography
 * Copyright (c) 2012 RELIC Authors
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
 * Implementation of fixed point multiplication on a prime elliptic curve over
 * a quadratic extension field.
 *
 * @ingroup epx
 */

#include "relic_core.h"

/*============================================================================*/
/* Private definitions                                                        */
/*============================================================================*/

#if EP_FIX == LWNAF || !defined(STRIP)

/**
 * Multiplies a binary elliptic curve point by an integer using the w-NAF
 * method.
 *
 * @param[out] r 				- the result.
 * @param[in] p					- the point to multiply.
 * @param[in] k					- the integer.
 */
static void ep2_mul_fix_plain(ep2_t r, const ep2_t *table, const bn_t k) {
	int8_t naf[2 * RLC_FP_BITS + 1], *t;
	size_t len;
	int n;

	if (bn_is_zero(k)) {
		ep2_set_infty(r);
		return;
	}

	/* Compute the w-TNAF representation of k. */
	len = 2 * RLC_FP_BITS + 1;
	bn_rec_naf(naf, &len, k, RLC_DEPTH);

	t = naf + len - 1;
	ep2_set_infty(r);
	for (int i = len - 1; i >= 0; i--, t--) {
		ep2_dbl(r, r);

		n = *t;
		if (n > 0) {
			ep2_add(r, r, table[n / 2]);
		}
		if (n < 0) {
			ep2_sub(r, r, table[-n / 2]);
		}
	}
	/* Convert r to affine coordinates. */
	ep2_norm(r, r);
	if (bn_sign(k) == RLC_NEG) {
		ep2_neg(r, r);
	}
}

#endif /* EP_FIX == LWNAF */

/*============================================================================*/
/* Public definitions                                                         */
/*============================================================================*/

#if EP_FIX == BASIC || !defined(STRIP)

void ep2_mul_pre_basic(ep2_t *t, const ep2_t p) {
	bn_t n;

	bn_null(n);

	RLC_TRY {
		bn_new(n);

		ep2_curve_get_ord(n);

		ep2_copy(t[0], p);
		for (int i = 1; i < bn_bits(n); i++) {
			ep2_dbl(t[i], t[i - 1]);
		}
	}
	RLC_CATCH_ANY {
		RLC_THROW(ERR_CAUGHT);
	}
	RLC_FINALLY {
		bn_free(n);
	}
}

void ep2_mul_fix_basic(ep2_t r, const ep2_t *t, const bn_t k) {
	bn_t n, _k;

	if (bn_is_zero(k)) {
		ep2_set_infty(r);
		return;
	}

	bn_null(n);
	bn_null(_k);

	RLC_TRY {
		bn_new(n);
		bn_new(_k);

		ep2_curve_get_ord(n);
		bn_mod(_k, k, n);

		ep2_set_infty(r);
		for (int i = 0; i < bn_bits(_k); i++) {
			if (bn_get_bit(_k, i)) {
				ep2_add(r, r, t[i]);
			}
		}
		ep2_norm(r, r);
	} RLC_CATCH_ANY {
		RLC_THROW(ERR_CAUGHT);
	} RLC_FINALLY {
		bn_free(n);
		bn_free(_k);
	}
}

#endif

#if EP_FIX == COMBS || !defined(STRIP)

void ep2_mul_pre_combs(ep2_t *t, const ep2_t p) {
	int i, j, l;
	bn_t n;

	bn_null(n);

	RLC_TRY {
		bn_new(n);

		ep2_curve_get_ord(n);
		l = bn_bits(n);
		l = ((l % RLC_DEPTH) == 0 ? (l / RLC_DEPTH) : (l / RLC_DEPTH) + 1);

		ep2_set_infty(t[0]);

		ep2_copy(t[1], p);
		for (j = 1; j < RLC_DEPTH; j++) {
			ep2_dbl(t[1 << j], t[1 << (j - 1)]);
			for (i = 1; i < l; i++) {
				ep2_dbl(t[1 << j], t[1 << j]);
			}
#if defined(EP_MIXED)
			ep2_norm(t[1 << j], t[1 << j]);
#endif
			for (i = 1; i < (1 << j); i++) {
				ep2_add(t[(1 << j) + i], t[i], t[1 << j]);
			}
		}
#if defined(EP_MIXED)
		for (i = 1; i < RLC_EP_TABLE_COMBS; i++) {
			ep2_norm(t[i], t[i]);
		}
#endif
	}
	RLC_CATCH_ANY {
		RLC_THROW(ERR_CAUGHT);
	}
	RLC_FINALLY {
		bn_free(n);
	}
}

void ep2_mul_fix_combs(ep2_t r, const ep2_t *t, const bn_t k) {
	int i, j, l, w, n0, p0, p1;
	bn_t n, _k;

	if (bn_is_zero(k)) {
		ep2_set_infty(r);
		return;
	}

	bn_null(n);
	bn_null(_k);

	RLC_TRY {
		bn_new(n);
		bn_new(_k);

		ep2_curve_get_ord(n);
		l = bn_bits(n);
		l = ((l % RLC_DEPTH) == 0 ? (l / RLC_DEPTH) : (l / RLC_DEPTH) + 1);

		bn_mod(_k, k, n);
		n0 = bn_bits(_k);

		p0 = (RLC_DEPTH) * l - 1;

		w = 0;
		p1 = p0--;
		for (j = RLC_DEPTH - 1; j >= 0; j--, p1 -= l) {
			w = w << 1;
			if (p1 < n0 && bn_get_bit(_k, p1)) {
				w = w | 1;
			}
		}
		ep2_copy(r, t[w]);

		for (i = l - 2; i >= 0; i--) {
			ep2_dbl(r, r);

			w = 0;
			p1 = p0--;
			for (j = RLC_DEPTH - 1; j >= 0; j--, p1 -= l) {
				w = w << 1;
				if (p1 < n0 && bn_get_bit(_k, p1)) {
					w = w | 1;
				}
			}
			if (w > 0) {
				ep2_add(r, r, t[w]);
			}
		}
		ep2_norm(r, r);
	}
	RLC_CATCH_ANY {
		RLC_THROW(ERR_CAUGHT);
	}
	RLC_FINALLY {
		bn_free(n);
		bn_free(_k);
	}
}

#endif

#if EP_FIX == COMBD || !defined(STRIP)

void ep2_mul_pre_combd(ep2_t *t, const ep2_t p) {
	int i, j, d, e;
	bn_t n;

	bn_null(n);

	RLC_TRY {
		bn_new(n);

		ep2_curve_get_ord(n);
		d = bn_bits(n);
		d = ((d % RLC_DEPTH) == 0 ? (d / RLC_DEPTH) : (d / RLC_DEPTH) + 1);
		e = (d % 2 == 0 ? (d / 2) : (d / 2) + 1);

		ep2_set_infty(t[0]);
		ep2_copy(t[1], p);
		for (j = 1; j < RLC_DEPTH; j++) {
			ep2_dbl(t[1 << j], t[1 << (j - 1)]);
			for (i = 1; i < d; i++) {
				ep2_dbl(t[1 << j], t[1 << j]);
			}
#if defined(EP_MIXED)
			ep2_norm(t[1 << j], t[1 << j]);
#endif
			for (i = 1; i < (1 << j); i++) {
				ep2_add(t[(1 << j) + i], t[i], t[1 << j]);
			}
		}
		ep2_set_infty(t[1 << RLC_DEPTH]);
		for (j = 1; j < (1 << RLC_DEPTH); j++) {
			ep2_dbl(t[(1 << RLC_DEPTH) + j], t[j]);
			for (i = 1; i < e; i++) {
				ep2_dbl(t[(1 << RLC_DEPTH) + j], t[(1 << RLC_DEPTH) + j]);
			}
		}
#if defined(EP_MIXED)
		for (i = 1; i < RLC_EP_TABLE_COMBD; i++) {
			ep2_norm(t[i], t[i]);
		}
#endif
	}
	RLC_CATCH_ANY {
		RLC_THROW(ERR_CAUGHT);
	}
	RLC_FINALLY {
		bn_free(n);
	}
}

void ep2_mul_fix_combd(ep2_t r, const ep2_t *t, const bn_t k) {
	int i, j, d, e, w0, w1, n0, p0, p1;
	bn_t n, _k;

	if (bn_is_zero(k)) {
		ep2_set_infty(r);
		return;
	}

	bn_null(n);
	bn_null(_k);

	RLC_TRY {
		bn_new(n);
		bn_new(_k);

		ep2_curve_get_ord(n);
		d = bn_bits(n);
		d = ((d % RLC_DEPTH) == 0 ? (d / RLC_DEPTH) : (d / RLC_DEPTH) + 1);
		e = (d % 2 == 0 ? (d / 2) : (d / 2) + 1);

		ep2_set_infty(r);
		bn_mod(_k, k, n);
		n0 = bn_bits(_k);

		p1 = (e - 1) + (RLC_DEPTH - 1) * d;
		for (i = e - 1; i >= 0; i--) {
			ep2_dbl(r, r);

			w0 = 0;
			p0 = p1;
			for (j = RLC_DEPTH - 1; j >= 0; j--, p0 -= d) {
				w0 = w0 << 1;
				if (p0 < n0 && bn_get_bit(_k, p0)) {
					w0 = w0 | 1;
				}
			}

			w1 = 0;
			p0 = p1-- + e;
			for (j = RLC_DEPTH - 1; j >= 0; j--, p0 -= d) {
				w1 = w1 << 1;
				if (i + e < d && p0 < n0 && bn_get_bit(_k, p0)) {
					w1 = w1 | 1;
				}
			}

			ep2_add(r, r, t[w0]);
			ep2_add(r, r, t[(1 << RLC_DEPTH) + w1]);
		}
		ep2_norm(r, r);
	}
	RLC_CATCH_ANY {
		RLC_THROW(ERR_CAUGHT);
	}
	RLC_FINALLY {
		bn_free(n);
		bn_free(_k);
	}
}

#endif

#if EP_FIX == LWNAF || !defined(STRIP)

void ep2_mul_pre_lwnaf(ep2_t *t, const ep2_t p) {
	ep2_tab(t, p, RLC_DEPTH);
}

void ep2_mul_fix_lwnaf(ep2_t r, const ep2_t *t, const bn_t k) {
	bn_t n, _k;

	if (bn_is_zero(k)) {
		ep2_set_infty(r);
		return;
	}

	bn_null(n);
	bn_null(_k);

	RLC_TRY {
		bn_new(n);
		bn_new(_k);

		ep2_curve_get_ord(n);
		bn_mod(_k, k, n);
		ep2_mul_fix_plain(r, t, _k);
	} RLC_CATCH_ANY {
		RLC_THROW(ERR_CAUGHT);
	} RLC_FINALLY {
		bn_free(n);
		bn_free(_k);
	}
}

#endif
