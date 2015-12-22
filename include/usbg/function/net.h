/*
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 */

#ifndef USBG_FUNCTION_NET__
#define USBG_FUNCTION_NET__

#include <usbg/usbg.h>

#include <malloc.h>

struct usbg_f_net;
typedef struct usbg_f_net usbg_f_net;

struct usbg_f_net_attrs {
	struct ether_addr dev_addr;
	struct ether_addr host_addr;
	const char *ifname;
	int qmult;
};

enum usbg_f_net_attr {
	USBG_F_NET_ATTR_MIN = 0,
	USBG_F_NET_DEV_ADDR = USBG_F_NET_ATTR_MIN,
	USBG_F_NET_HOST_ADDR,
	USBG_F_NET_IFNAME,
	USBG_F_NET_QMULT,
	USBG_F_NET_ATTR_MAX
};

union usbg_f_net_attr_val {
	struct ether_addr dev_addr;
	struct ether_addr host_addr;
	const char *ifname;
	int qmult;
};

/**
 * @brief Cast from generic function to net function
 * @param[in] f function to be converted to net funciton.
 *         Should be one of types:
 *         ecm, subset, ncm, eem, rndis
 * @return Converted net function or NULL if function hasn't suitable type
 */
usbg_f_net *usbg_to_net_function(usbg_function *f);

/**
 * @brief Cast form net function to generic one
 * @param[in] nf function to be converted to generic one
 * @return Generic usbg function
 */
usbg_function *usbg_from_net_function(usbg_f_net *nf);

/**
 * @brief Get attributes of given net function
 * @param[in] nf Pointer to net function
 * @param[out] attrs Structure to be filled with data
 * @return 0 on success usbg_error if error occurred.
 */
int usbg_f_net_get_attrs(usbg_f_net *nf, struct usbg_f_net_attrs *attrs);

/**
 * @brief Set attributes of given net function
 * @param[in] nf Pointer to net function
 * @param[in] attrs to be set
 * @return 0 on success usbg_error if error occurred.
 */
int usbg_f_net_set_attrs(usbg_f_net *nf,
			 const struct usbg_f_net_attrs *attrs);

/**
 * @brief Cleanup attributes structure after usage
 * @param[in] attrs to be cleaned up
 */
static inline void usbg_f_net_cleanup_attrs(struct usbg_f_net_attrs *attrs)
{
	if (attrs) {
		free((char *)attrs->ifname);
		attrs->ifname = NULL;
	}
}

/**
 * @brief Get the value of single attribute
 * @param[in] nf Pointer to net function
 * @param[in] attr Code of attribute which value should be taken
 * @param[out] val Current value of this attribute
 * @return 0 on success usbg_error if error occurred.
 */
int usbg_f_net_get_attr_val(usbg_f_net *nf, enum usbg_f_net_attr attr,
			    union usbg_f_net_attr_val *val);

/**
 * @brief Set the value of single attribute
 * @param[in] nf Pointer to net function
 * @param[in] attr Code of attribute which value should be set
 * @param[in] val Value of attribute which should be set
 * @return 0 on success usbg_error if error occurred.
 */
int usbg_f_net_set_attr_val(usbg_f_net *nf, enum usbg_f_net_attr attr,
			    const union usbg_f_net_attr_val val);

/**
 * @brief Get the value of device side MAC address
 * @param[in] nf Pointer to net function
 * @param[out] val Current value of this attribute
 * @return 0 on success usbg_error if error occurred.
 */
static inline int usbg_f_net_get_dev_addr(usbg_f_net *nf,
					  struct ether_addr *addr)
{
	return usbg_f_net_get_attr_val(nf, USBG_F_NET_DEV_ADDR,
				       (union usbg_f_net_attr_val *)addr);
}

/**
 * @brief Set the value of device side MAC address
 * @param[in] nf Pointer to net function
 * @param[out] val Value of attribute which should be set
 * @return 0 on success usbg_error if error occurred.
 */
static inline int usbg_f_net_set_dev_addr(usbg_f_net *nf,
			     const struct ether_addr *addr)
{
	return usbg_f_net_set_attr_val(nf, USBG_F_NET_DEV_ADDR,
				       (union usbg_f_net_attr_val)*addr);
}

/**
 * @brief Get the value of host side MAC address
 * @param[in] nf Pointer to net function
 * @param[out] val Current value of this attribute
 * @return 0 on success usbg_error if error occurred.
 */
static inline int usbg_f_net_get_host_addr(usbg_f_net *nf,
					   struct ether_addr *addr)
{
	return usbg_f_net_get_attr_val(nf, USBG_F_NET_HOST_ADDR,
				       (union usbg_f_net_attr_val *)addr);
}

/**
 * @brief Set the value of device side MAC address
 * @param[in] nf Pointer to net function
 * @param[in] val Value of attribute which should be set
 * @return 0 on success usbg_error if error occurred.
 */
static inline int usbg_f_net_set_host_addr(usbg_f_net *nf,
					   const struct ether_addr *addr)
{
	return usbg_f_net_set_attr_val(nf, USBG_F_NET_HOST_ADDR,
				       (union usbg_f_net_attr_val)*addr);
}

/**
 * @brief Get the value of interface name associated with this function
 *         into newly allocated storage
 * @param[in] nf Pointer to net function
 * @param[out] ifname Newly allocated string containing name of interface
 * @return 0 on success usbg_error if error occurred.
 * @note returned ifname should be free() by caller
 */
static inline int usbg_f_net_get_ifname(usbg_f_net *nf, char **ifname)
{
	return usbg_f_net_get_attr_val(nf, USBG_F_NET_IFNAME,
				       (union usbg_f_net_attr_val *)ifname);
}

/**
 * @brief Get the value of interface name associated with this function
 *         into user buffer
 * @param[in] nf Pointer to net function
 * @param[out] buf Place where ifname should be stored
 * @param[in] len Size of buffer
 * @return Number of bytes placed into buf (excluding '\0') or the number of
 *         characters which would have been written to the buffer if enough
 *         space had been available. (just like snprintf() family). This may
 *         also return negative error code from usbg_error.
 */
int usbg_f_net_get_ifname_s(usbg_f_net *nf, char *buf, int len);

/**
 * @brief Get the value of request queue length multiplier
 * @param[in] nf Pointer to net function
 * @param[out] qmult Current multiplier of queue len
 * @return 0 on success usbg_error if error occurred.
 */
static inline int usbg_f_net_get_qmult(usbg_f_net *nf, int *qmult)
{
	return usbg_f_net_get_attr_val(nf, USBG_F_NET_QMULT,
				       (union usbg_f_net_attr_val *)qmult);
}

/**
 * @brief Set the value of request queue length multiplier
 * @param[in] nf Pointer to net function
 * @param[in] qmult Multiplier of queue len which should be set
 * @return 0 on success usbg_error if error occurred.
 */
static inline int usbg_f_net_set_qmult(usbg_f_net *nf, int qmult)
{
	return usbg_f_net_set_attr_val(nf, USBG_F_NET_QMULT,
				       (union usbg_f_net_attr_val)qmult);
}

#endif /* USBG_FUNCTION_NET__ */