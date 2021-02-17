/* SPDX-License-Identifier: GPL-2.0-only
 *
 * linux/drivers/gpu/drm/samsung/exynos_drm_hibernation.h
 *
 * Copyright (c) 2020 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Headef file for Display Hibernation Feature.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __EXYNOS_DRM_HIBERNATION__
#define __EXYNOS_DRM_HIBERNATION__

#include <linux/types.h>
#include <linux/mutex.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/io.h>

struct decon_device;
struct dsim_device;
struct exynos_hibernation;
struct writeback_device;

struct exynos_hibernation_funcs {
	void (*enter)(struct exynos_hibernation *hiber);
	int (*exit)(struct exynos_hibernation *hiber);
	bool (*check)(struct exynos_hibernation *hiber);
};

struct exynos_hibernation {
	atomic_t block_cnt;
	/* register to check whether camera is operating or not */
	void __iomem *cam_op_reg;
	struct mutex lock;
	struct kthread_delayed_work dwork;
	struct decon_device *decon;
	struct dsim_device *dsim;
	struct writeback_device *wb;
	const struct exynos_hibernation_funcs *funcs;
	bool enabled;
};

bool hibernation_block_exit(struct exynos_hibernation *hiber);
void hibernation_unblock_enter(struct exynos_hibernation *hiber);
struct exynos_hibernation *
exynos_hibernation_register(struct decon_device *decon);
void exynos_hibernation_destroy(struct exynos_hibernation *hiber);

#endif /* __EXYNOS_DRM_HIBERNATION__ */
