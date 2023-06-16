#ifndef __DFU_USB_H__
#define __DFU_USB_H__

#include <libusb-1.0/libusb.h>

#include "logger.h"
#include "dfu_usb_error.h"

typedef struct dfu_usb_lib_ctx {
        libusb_context *libusb_ctx;
} dfu_usb_lib_ctx_st_t;

dfu_usb_error_t dfu_usb_library_init(void);
void dfu_usb_library_deinit(void);

#endif /* __DFU_USB_H__ */
