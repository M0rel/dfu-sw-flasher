#include <stdio.h>

#include "dfu_usb.h"
#include "dfu_usb_error.h"

dfu_usb_lib_ctx_st_t dfu_usb_lib_ctx = {0};

dfu_usb_error_t dfu_usb_library_init(void)
{
        int err = LIBUSB_SUCCESS;

        err = libusb_init(&dfu_usb_lib_ctx.libusb_ctx);
        if (LIBUSB_SUCCESS != err) {
                log_err("Failed to initialize USB library. Error: %s\n",
                        libusb_strerror(err));

                return DFU_USB_INITIALIZATION_FAILED;
        }

        log_dbg("USB library initialized\n");

        return DFU_USB_SUCCESS;
}

void dfu_usb_library_deinit(void)
{
        libusb_exit(dfu_usb_lib_ctx.libusb_ctx);

        log_dbg("USB library de-initialized\n");
}
