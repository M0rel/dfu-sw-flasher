#ifndef __DFU_USB_H__
#define __DFU_USB_H__

#include <libusb-1.0/libusb.h>

#include "logger.h"
#include "dfu_usb_error.h"

typedef struct dfu_usb_dev {
        libusb_context *ctx;
} dfu_usb_dev_st_t;

dfu_usb_error_t dfu_usb_library_init(void);
void dfu_usb_library_deinit(void);

#endif /* __DFU_USB_H__ */
