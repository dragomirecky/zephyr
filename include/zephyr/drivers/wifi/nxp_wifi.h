/*
 * Copyright 2024 NXP
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_INCLUDE_DRIVERS_WIFI_NXP_WIFI_H_
#define ZEPHYR_INCLUDE_DRIVERS_WIFI_NXP_WIFI_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Start deferred WiFi initialization
 *
 * When CONFIG_NXP_WIFI_DEFERRED_INIT is enabled, this function triggers
 * WiFi hardware initialization in a background workqueue. The WiFi interface
 * will be brought up automatically when initialization completes.
 *
 * @return 0 on success, negative errno on failure
 */
#if defined(CONFIG_NXP_WIFI_DEFERRED_INIT)
int nxp_wifi_deferred_init(void);
#else
static inline int nxp_wifi_deferred_init(void)
{
	return 0;
}
#endif

#ifdef __cplusplus
}
#endif

#endif /* ZEPHYR_INCLUDE_DRIVERS_WIFI_NXP_WIFI_H_ */
