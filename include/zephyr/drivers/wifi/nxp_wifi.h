/*
 * Copyright 2024-2025 NXP
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_INCLUDE_DRIVERS_WIFI_NXP_WIFI_H_
#define ZEPHYR_INCLUDE_DRIVERS_WIFI_NXP_WIFI_H_

#include <zephyr/kernel.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(CONFIG_NXP_WIFI_ASYNC_OPS)

/**
 * @brief Callback type for async WiFi init completion
 *
 * @param status 0 on success, negative errno on failure
 * @param user_data User data passed to nxp_wifi_init_async()
 */
typedef void (*nxp_wifi_init_cb_t)(int status, void *user_data);

/**
 * @brief Trigger async WiFi initialization
 *
 * Starts WiFi hardware initialization in the background worker thread.
 * The WiFi interface will be brought up automatically when initialization
 * completes successfully.
 *
 * This function returns immediately. Use the callback to be notified when
 * init completes, or call nxp_wifi_init_wait() to block until ready.
 *
 * @param cb Optional callback to invoke when init completes (may be NULL)
 * @param user_data Optional user data to pass to callback
 *
 * @return 0 on success (init queued), -EALREADY if already initialized,
 *         -EBUSY if queue is full
 */
int nxp_wifi_init_async(nxp_wifi_init_cb_t cb, void *user_data);

/**
 * @brief Wait for WiFi initialization to complete
 *
 * Blocks the calling thread until WiFi hardware initialization is complete.
 * This is useful for applications that need synchronous init behavior.
 *
 * @param timeout Maximum time to wait, or K_FOREVER
 *
 * @return 0 on success, -EAGAIN if WiFi not initialized and not in progress,
 *         -ETIMEDOUT if timeout expired, negative errno on init failure
 */
int nxp_wifi_init_wait(k_timeout_t timeout);

/**
 * @brief Check if WiFi is ready for operations
 *
 * @return true if WiFi is initialized and ready, false otherwise
 */
bool nxp_wifi_is_ready(void);

#else /* !CONFIG_NXP_WIFI_ASYNC_OPS */

/* Stub implementations when async ops is disabled */
typedef void (*nxp_wifi_init_cb_t)(int status, void *user_data);

static inline int nxp_wifi_init_async(nxp_wifi_init_cb_t cb, void *user_data)
{
	ARG_UNUSED(cb);
	ARG_UNUSED(user_data);
	return 0;
}

static inline int nxp_wifi_init_wait(k_timeout_t timeout)
{
	ARG_UNUSED(timeout);
	return 0;
}

static inline bool nxp_wifi_is_ready(void)
{
	return true;
}

#endif /* CONFIG_NXP_WIFI_ASYNC_OPS */

#ifdef __cplusplus
}
#endif

#endif /* ZEPHYR_INCLUDE_DRIVERS_WIFI_NXP_WIFI_H_ */
