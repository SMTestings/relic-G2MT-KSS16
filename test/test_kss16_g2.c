/*
 * RELIC is an Efficient LIbrary for Cryptography
 * Copyright (c) 2010 RELIC Authors
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
 * Tests for the subgroup membership of G2 on KSS16 curve.
 *
 * @ingroup test
 */

#include <stdio.h>

#include "relic.h"
#include "relic_test.h"

static int validity2kss(void) {
	int code = RLC_ERR;
	g2_t a;

	g2_null(a);

	RLC_TRY {
		g2_new(a);

		TEST_CASE("validity test with new method (for KSS16 curves) is correct") {
			g2_set_infty(a);
			TEST_ASSERT(!g2_is_valid_kss16(a), end);
			g2_rand(a);
			TEST_ASSERT(g2_is_valid_kss16(a), end);
		}
		TEST_END;

		TEST_CASE("blinding with new method (for KSS16 curves) is consistent") {
			g2_rand(a);
			g2_blind(a, a);
			g2_norm(a, a);
			TEST_ASSERT(g2_is_valid_kss16(a), end);
		} TEST_END;
	}
	RLC_CATCH_ANY {
		RLC_ERROR(end);
	}
	code = RLC_OK;
  end:
	g2_free(a);
	return code;
}

int test2(void) {

	util_banner("Arithmetic:", 1);
    if (validity2kss() != RLC_OK) {
		return RLC_ERR;
	}

	return RLC_OK;
}

int main(void) {
	if (core_init() != RLC_OK) {
		core_clean();
		return 1;
	}

	util_banner("Tests for the PC module:", 0);

	if (pc_param_set_any() != RLC_OK) {
		RLC_THROW(ERR_NO_CURVE);
		core_clean();
		return 0;
	}

	pc_param_print();

    util_banner("Group G_2:", 0);
	if (test2() != RLC_OK) {
		core_clean();
		return 1;
	}


	util_banner("All tests have passed.\n", 0);

	core_clean();
	return 0;
}
