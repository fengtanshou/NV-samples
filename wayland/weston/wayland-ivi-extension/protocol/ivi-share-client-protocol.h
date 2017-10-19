/* Generated by wayland-scanner 1.11.0 */

#ifndef IVI_SHARE_CLIENT_PROTOCOL_H
#define IVI_SHARE_CLIENT_PROTOCOL_H

#include <stdint.h>
#include <stddef.h>
#include "wayland-client.h"

#ifdef  __cplusplus
extern "C" {
#endif

/**
 * @page page_ivi_share The ivi_share protocol
 * @section page_ifaces_ivi_share Interfaces
 * - @subpage page_iface_ivi_share - get handle to manipulate ivi_surface
 * - @subpage page_iface_ivi_share_surface - extension interface for sharing a ivi_surface
 * @section page_copyright_ivi_share Copyright
 * <pre>
 *
 * Copyright (c) 2012 Advanced Driver Information Technology.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * </pre>
 */
struct ivi_share;
struct ivi_share_surface;

/**
 * @page page_iface_ivi_share ivi_share
 * @section page_iface_ivi_share_desc Description
 *
 * get handle ID to manipulate shared ivi_surface. The host ivi application
 * can get trigger of update of the ivi_surface from client to draw it in host's
 * content. Additionally the interface allows host ivi application to send
 * transformed input coordinates to client because the coordinate is transformed
 * outside of compositor.
 * @section page_iface_ivi_share_api API
 * See @ref iface_ivi_share.
 */
/**
 * @defgroup iface_ivi_share The ivi_share interface
 *
 * get handle ID to manipulate shared ivi_surface. The host ivi application
 * can get trigger of update of the ivi_surface from client to draw it in host's
 * content. Additionally the interface allows host ivi application to send
 * transformed input coordinates to client because the coordinate is transformed
 * outside of compositor.
 */
extern const struct wl_interface ivi_share_interface;
/**
 * @page page_iface_ivi_share_surface ivi_share_surface
 * @section page_iface_ivi_share_surface_desc Description
 *
 * @section page_iface_ivi_share_surface_api API
 * See @ref iface_ivi_share_surface.
 */
/**
 * @defgroup iface_ivi_share_surface The ivi_share_surface interface
 *
 */
extern const struct wl_interface ivi_share_surface_interface;

#define IVI_SHARE_GET_IVI_SHARE_SURFACE	0

/**
 * @ingroup iface_ivi_share
 */
#define IVI_SHARE_GET_IVI_SHARE_SURFACE_SINCE_VERSION	1

/** @ingroup iface_ivi_share */
static inline void
ivi_share_set_user_data(struct ivi_share *ivi_share, void *user_data)
{
	wl_proxy_set_user_data((struct wl_proxy *) ivi_share, user_data);
}

/** @ingroup iface_ivi_share */
static inline void *
ivi_share_get_user_data(struct ivi_share *ivi_share)
{
	return wl_proxy_get_user_data((struct wl_proxy *) ivi_share);
}

static inline uint32_t
ivi_share_get_version(struct ivi_share *ivi_share)
{
	return wl_proxy_get_version((struct wl_proxy *) ivi_share);
}

/** @ingroup iface_ivi_share */
static inline void
ivi_share_destroy(struct ivi_share *ivi_share)
{
	wl_proxy_destroy((struct wl_proxy *) ivi_share);
}

/**
 * @ingroup iface_ivi_share
 */
static inline struct ivi_share_surface *
ivi_share_get_ivi_share_surface(struct ivi_share *ivi_share, uint32_t surface_id)
{
	struct wl_proxy *id;

	id = wl_proxy_marshal_constructor((struct wl_proxy *) ivi_share,
			 IVI_SHARE_GET_IVI_SHARE_SURFACE, &ivi_share_surface_interface, NULL, surface_id);

	return (struct ivi_share_surface *) id;
}

#ifndef IVI_SHARE_SURFACE_TYPE_ENUM
#define IVI_SHARE_SURFACE_TYPE_ENUM
/**
 * @ingroup iface_ivi_share_surface
 * name type
 *
 * The ivi-share is dependent on an architecture how to share graphic
 * buffer inter processes. This informs Host ivi_application which way shall
 * be used in its own system. The most popular way is gbm now.
 */
enum ivi_share_surface_type {
	IVI_SHARE_SURFACE_TYPE_GBM = 0,
	IVI_SHARE_SURFACE_TYPE_UNKNOWN = 1,
};
#endif /* IVI_SHARE_SURFACE_TYPE_ENUM */

#ifndef IVI_SHARE_SURFACE_FORMAT_ENUM
#define IVI_SHARE_SURFACE_FORMAT_ENUM
/**
 * @ingroup iface_ivi_share_surface
 * share surface format
 */
enum ivi_share_surface_format {
	IVI_SHARE_SURFACE_FORMAT_ARGB8888 = 0,
	IVI_SHARE_SURFACE_FORMAT_XRGB8888 = 1,
	IVI_SHARE_SURFACE_FORMAT_UNKNOWN = 2,
};
#endif /* IVI_SHARE_SURFACE_FORMAT_ENUM */

#ifndef IVI_SHARE_SURFACE_INPUT_CAPS_ENUM
#define IVI_SHARE_SURFACE_INPUT_CAPS_ENUM
/**
 * @ingroup iface_ivi_share_surface
 * input capability bitmask
 */
enum ivi_share_surface_input_caps {
	/**
	 * Shared surface can receive a pointer event
	 */
	IVI_SHARE_SURFACE_INPUT_CAPS_POINTER = 1,
	/**
	 * Shared surface can receive a keyboard event
	 */
	IVI_SHARE_SURFACE_INPUT_CAPS_KEYBOARD = 2,
	/**
	 * Shared surface can receive a touch event
	 */
	IVI_SHARE_SURFACE_INPUT_CAPS_TOUCH = 4,
};
#endif /* IVI_SHARE_SURFACE_INPUT_CAPS_ENUM */

#ifndef IVI_SHARE_SURFACE_SHARE_SURFACE_STATE_ENUM
#define IVI_SHARE_SURFACE_SHARE_SURFACE_STATE_ENUM
/**
 * @ingroup iface_ivi_share_surface
 * state of shared surface
 */
enum ivi_share_surface_share_surface_state {
	/**
	 * the surface which shared is not exist
	 */
	IVI_SHARE_SURFACE_SHARE_SURFACE_STATE_NOT_EXIST = 1,
	/**
	 * the surface which shared has been destroyed
	 */
	IVI_SHARE_SURFACE_SHARE_SURFACE_STATE_DESTROYED = 2,
	/**
	 * the surface is unsited for share
	 */
	IVI_SHARE_SURFACE_SHARE_SURFACE_STATE_INVALID_SURFACE = 3,
};
#endif /* IVI_SHARE_SURFACE_SHARE_SURFACE_STATE_ENUM */

/**
 * @ingroup iface_ivi_share_surface
 * @struct ivi_share_surface_listener
 */
struct ivi_share_surface_listener {
	/**
	 * damage
	 *
	 * Notify if shared ivi_surface is updated in client.
	 */
	void (*damage)(void *data,
		       struct ivi_share_surface *ivi_share_surface,
		       uint32_t name);
	/**
	 * configuration of share surface
	 *
	 * 
	 */
	void (*configure)(void *data,
			  struct ivi_share_surface *ivi_share_surface,
			  uint32_t type,
			  uint32_t width,
			  uint32_t height,
			  uint32_t stride,
			  uint32_t format);
	/**
	 * seat capabilities of shared surface
	 *
	 * 
	 */
	void (*input_capabilities)(void *data,
				   struct ivi_share_surface *ivi_share_surface,
				   uint32_t capabilities);
	/**
	 * state of shared surface
	 *
	 * 
	 */
	void (*share_surface_state)(void *data,
				    struct ivi_share_surface *ivi_share_surface,
				    uint32_t state);
};

/**
 * @ingroup ivi_share_surface_iface
 */
static inline int
ivi_share_surface_add_listener(struct ivi_share_surface *ivi_share_surface,
			       const struct ivi_share_surface_listener *listener, void *data)
{
	return wl_proxy_add_listener((struct wl_proxy *) ivi_share_surface,
				     (void (**)(void)) listener, data);
}

#define IVI_SHARE_SURFACE_DESTROY	0
#define IVI_SHARE_SURFACE_REDIRECT_TOUCH_DOWN	1
#define IVI_SHARE_SURFACE_REDIRECT_TOUCH_UP	2
#define IVI_SHARE_SURFACE_REDIRECT_TOUCH_MOTION	3
#define IVI_SHARE_SURFACE_REDIRECT_TOUCH_FRAME	4
#define IVI_SHARE_SURFACE_REDIRECT_TOUCH_CANCEL	5

/**
 * @ingroup iface_ivi_share_surface
 */
#define IVI_SHARE_SURFACE_DESTROY_SINCE_VERSION	1
/**
 * @ingroup iface_ivi_share_surface
 */
#define IVI_SHARE_SURFACE_REDIRECT_TOUCH_DOWN_SINCE_VERSION	1
/**
 * @ingroup iface_ivi_share_surface
 */
#define IVI_SHARE_SURFACE_REDIRECT_TOUCH_UP_SINCE_VERSION	1
/**
 * @ingroup iface_ivi_share_surface
 */
#define IVI_SHARE_SURFACE_REDIRECT_TOUCH_MOTION_SINCE_VERSION	1
/**
 * @ingroup iface_ivi_share_surface
 */
#define IVI_SHARE_SURFACE_REDIRECT_TOUCH_FRAME_SINCE_VERSION	1
/**
 * @ingroup iface_ivi_share_surface
 */
#define IVI_SHARE_SURFACE_REDIRECT_TOUCH_CANCEL_SINCE_VERSION	1

/** @ingroup iface_ivi_share_surface */
static inline void
ivi_share_surface_set_user_data(struct ivi_share_surface *ivi_share_surface, void *user_data)
{
	wl_proxy_set_user_data((struct wl_proxy *) ivi_share_surface, user_data);
}

/** @ingroup iface_ivi_share_surface */
static inline void *
ivi_share_surface_get_user_data(struct ivi_share_surface *ivi_share_surface)
{
	return wl_proxy_get_user_data((struct wl_proxy *) ivi_share_surface);
}

static inline uint32_t
ivi_share_surface_get_version(struct ivi_share_surface *ivi_share_surface)
{
	return wl_proxy_get_version((struct wl_proxy *) ivi_share_surface);
}

/**
 * @ingroup iface_ivi_share_surface
 *
 * Deletes the surface and invalidates its object ID.
 */
static inline void
ivi_share_surface_destroy(struct ivi_share_surface *ivi_share_surface)
{
	wl_proxy_marshal((struct wl_proxy *) ivi_share_surface,
			 IVI_SHARE_SURFACE_DESTROY);

	wl_proxy_destroy((struct wl_proxy *) ivi_share_surface);
}

/**
 * @ingroup iface_ivi_share_surface
 */
static inline void
ivi_share_surface_redirect_touch_down(struct ivi_share_surface *ivi_share_surface, uint32_t serial, int32_t id, wl_fixed_t x, wl_fixed_t y)
{
	wl_proxy_marshal((struct wl_proxy *) ivi_share_surface,
			 IVI_SHARE_SURFACE_REDIRECT_TOUCH_DOWN, serial, id, x, y);
}

/**
 * @ingroup iface_ivi_share_surface
 */
static inline void
ivi_share_surface_redirect_touch_up(struct ivi_share_surface *ivi_share_surface, uint32_t serial, int32_t id)
{
	wl_proxy_marshal((struct wl_proxy *) ivi_share_surface,
			 IVI_SHARE_SURFACE_REDIRECT_TOUCH_UP, serial, id);
}

/**
 * @ingroup iface_ivi_share_surface
 */
static inline void
ivi_share_surface_redirect_touch_motion(struct ivi_share_surface *ivi_share_surface, int32_t id, wl_fixed_t x, wl_fixed_t y)
{
	wl_proxy_marshal((struct wl_proxy *) ivi_share_surface,
			 IVI_SHARE_SURFACE_REDIRECT_TOUCH_MOTION, id, x, y);
}

/**
 * @ingroup iface_ivi_share_surface
 */
static inline void
ivi_share_surface_redirect_touch_frame(struct ivi_share_surface *ivi_share_surface)
{
	wl_proxy_marshal((struct wl_proxy *) ivi_share_surface,
			 IVI_SHARE_SURFACE_REDIRECT_TOUCH_FRAME);
}

/**
 * @ingroup iface_ivi_share_surface
 */
static inline void
ivi_share_surface_redirect_touch_cancel(struct ivi_share_surface *ivi_share_surface)
{
	wl_proxy_marshal((struct wl_proxy *) ivi_share_surface,
			 IVI_SHARE_SURFACE_REDIRECT_TOUCH_CANCEL);
}

#ifdef  __cplusplus
}
#endif

#endif