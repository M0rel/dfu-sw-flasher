#ifndef __DFU_USB_H__
#define __DFU_USB_H__

#include <libusb-1.0/libusb.h>

#include "list.h"

#include "logger.h"
#include "dfu_usb_error.h"
#include "dfu_usb_api.h"

typedef enum interface_class {
        IF_CLASS_APP_SPEC = 0xFE
} interface_class_t;

typedef enum interface_sub_class {
        IF_SUB_CLASS_DFU = 1
} interface_sub_class_t;

typedef struct dfu_usb_dev {
        uint16_t         vendor_id;
        uint16_t         product_id;
        uint8_t          configuration_id;
        uint8_t          interface_id;
        uint8_t          altsetting_id;
        struct list_node node;
} dfu_usb_dev_st_t;

typedef struct dfu_usb_lib_ctx {
        struct dfu_usb_dev dfu_dev;
        libusb_context     *libusb_ctx;
} dfu_usb_lib_ctx_st_t;

#endif /* __DFU_USB_H__ */
