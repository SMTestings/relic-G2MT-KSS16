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
 * Benchmarks for Pairing-Based Cryptography.
 *
 * @ingroup bench
 */

#include <stdio.h>

#include "relic.h"
#include "relic_bench.h"
/**/
static void util2(void) {
	g2_t p, q;
	uint8_t bin[16 * RLC_PC_BYTES + 1];
	int l;

	g2_null(p);
	g2_null(q);

	g2_new(p);
	g2_new(q);

    g2_rand(p);
    g2_rand(q);

	BENCH_RUN("g2_is_valid") {
		BENCH_ADD(g2_is_valid(p));
	}
	BENCH_END;

	BENCH_RUN("g2_is_valid_kss16") {
		BENCH_ADD(g2_is_valid_kss16(p));
	}
	BENCH_END;

	g2_free(p)
	g2_free(q);
}

int main(void) {
	if (core_init() != RLC_OK) {
		core_clean();
		return 1;
	}

	conf_print();
	util_banner("Benchmarks for the PC module:", 0);

	if (pc_param_set_any() != RLC_OK) {
		RLC_THROW(ERR_NO_CURVE);
		core_clean();
		return 0;
	}

	pc_param_print();

    util_banner("Group G_2:", 0);
	util_banner("Utilities:", 1);
	util2();

    core_clean();
	return 0;
}