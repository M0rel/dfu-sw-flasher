#include <stdio.h>

#include "dfu_usb.h"

dfu_usb_lib_ctx_st_t dfu_usb_lib_ctx = {0};

static
dfu_usb_error_t get_usb_interface_alt_settings(dfu_usb_lib_ctx_st_t *ctx,
        const struct libusb_interface *usb_intrf)
{
        const struct libusb_interface_descriptor *intrf_altsettings = NULL;
        int i = 0;
        
        if (NULL == ctx || NULL == usb_intrf) {
                log_err("Invalid input: ctx = %p, usb_intrf = %p\n");

                return DFU_USB_INVALID_VALUE;
        }

        log_dbg("Alternative settings count [%d]\n", usb_intrf->num_altsetting);

        for (i = 0; i < usb_intrf->num_altsetting; i++) {
                intrf_altsettings = &usb_intrf->altsetting[i];
                if (NULL == intrf_altsettings) {
                        log_err("Invalid pointer: intrf_altsetting = %p\n");

                        return DFU_USB_INVALID_VALUE;
                }

                if (IF_CLASS_APP_SPEC == intrf_altsettings->bInterfaceClass &&
                    IF_SUB_CLASS_DFU == intrf_altsettings->bInterfaceSubClass) {
                        log_info("Found DFU\n");
                }
        }

        return DFU_USB_SUCCESS;
}

static
dfu_usb_error_t get_usb_interface_settings(dfu_usb_lib_ctx_st_t *ctx,
        struct libusb_config_descriptor *cfg)
{
        dfu_usb_error_t rc = DFU_USB_SUCCESS;
        const struct libusb_interface *usb_intrf = NULL;
        int i = 0;

        if (NULL == ctx || NULL == cfg) {
                log_err("Invalid input: ctx = %p, cfg = %p\n");

                return DFU_USB_INVALID_VALUE;
        }

        for (i = 0; i < cfg->bNumInterfaces; i++) {
                usb_intrf = &cfg->interface[i];
                if (NULL == usb_intrf) {
                        log_err("Invalid pointer: usb_intrf = %p\n", usb_intrf);

                        return DFU_USB_INVALID_VALUE;
                }

                log_dbg("Obtaining alternative settings for a interface [%d]\n",
                        i);

                rc = get_usb_interface_alt_settings(ctx, usb_intrf);
                if (DFU_USB_SUCCESS != rc) {
                        log_err("Failed to get USB interface alternative "
                                "settings. Error: %s", dfu_usb_err2str(rc));

                        return rc;
                }
        }

        return DFU_USB_SUCCESS;
}

static
dfu_usb_error_t get_cfg_desc_settings(dfu_usb_lib_ctx_st_t *ctx,
        libusb_device *usb_dev, struct libusb_device_descriptor *desc)
{
        dfu_usb_error_t rc = DFU_USB_SUCCESS;
        int err = LIBUSB_SUCCESS;
        struct libusb_config_descriptor *cfg = NULL;
        int i = 0;

        if (NULL == ctx || NULL == usb_dev || NULL == desc) {
                log_err("Invalid input: ctx = %p, usb_dev = %p, desc = %p\n");

                return DFU_USB_INVALID_VALUE;
        }

        log_dbg("Configurations count: [%d]\n", desc->bNumConfigurations);

        for (i = 0; i < desc->bNumConfigurations; i++) {
                err = libusb_get_config_descriptor(usb_dev, i, &cfg);
                if (LIBUSB_SUCCESS != err) {
                        log_err("Failed to get device descriptor. Error: %s\n",
                                libusb_strerror(err));

                        rc = DFU_USB_LIBUSB_FAILED;

                        goto get_cfg_descriptor_exit;
                }

                rc = get_usb_interface_settings(ctx, cfg);
                if (DFU_USB_SUCCESS != rc) {
                        log_err("Failed to get USB interface settings. "
                                "Error: %s\n", dfu_usb_err2str(rc));

                        goto get_cfg_descriptor_exit;
                }
        }

get_cfg_descriptor_exit:
        libusb_free_config_descriptor(cfg);

        return rc;
}

static
dfu_usb_error_t get_device_desc_settings(dfu_usb_lib_ctx_st_t *ctx,
        libusb_device *usb_dev)
{
        dfu_usb_error_t rc = DFU_USB_SUCCESS;
        int err = LIBUSB_SUCCESS;
        struct libusb_device_descriptor desc = {0};

        if (NULL == ctx || NULL == usb_dev) {
                log_err("Invalid input: ctx = %p, usb_dev = %p\n",
                        ctx, usb_dev);

                return DFU_USB_INVALID_VALUE;
        }

        err = libusb_get_device_descriptor(usb_dev, &desc);
        if (LIBUSB_SUCCESS != err) {
                log_err("Failed to get device descriptor. Error: %s\n",
                        libusb_strerror(err));

                return DFU_USB_LIBUSB_FAILED;
        }

        rc = get_cfg_desc_settings(ctx, usb_dev, &desc);
        if (DFU_USB_SUCCESS != rc) {
                log_err(". Error: %s\n",
                        dfu_usb_err2str(rc));

                return rc;
        }

        return DFU_USB_SUCCESS;
}

dfu_usb_error_t dfu_usb_get_attached_devices(void)
{
        dfu_usb_error_t rc = DFU_USB_SUCCESS;
        int err = LIBUSB_SUCCESS;
        libusb_device **usb_devices_list = NULL;
        size_t devices_cnt = 0;
        int i = 0;

        /* Returns device cnt or any error */
        devices_cnt = libusb_get_device_list(NULL, &usb_devices_list);
        err = devices_cnt;
        if (LIBUSB_SUCCESS > err) {
                log_err("Failed to get attached USB device count. Error: %s\n",
                        libusb_strerror(err));

                return DFU_USB_LIBUSB_FAILED;
        }

        for (i = 0; i < devices_cnt; i++) {
                log_dbg("Obtaining settings for a device: [%d]\n", i);

                rc = get_device_desc_settings(&dfu_usb_lib_ctx,
                                              usb_devices_list[i]);
                if (DFU_USB_SUCCESS != rc) {
                        log_err("Failed to get device descriptor settings. "
                                "Error: %s\n", dfu_usb_err2str(rc));

                        goto get_attached_devices_exit;
                }
        }

        log_info("Attached USB devices count: [%d]\n", devices_cnt);

get_attached_devices_exit:
        libusb_free_device_list(usb_devices_list, 1);

        return 0;
}

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
