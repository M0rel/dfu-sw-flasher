#include <stdio.h>
#include <stdarg.h>
#include <getopt.h>
#include <errno.h>

#include "dfu_usb_api.h"

int main(int argc, char **argv)
{
        dfu_usb_error_t rc = DFU_USB_SUCCESS;
        int ch = 0;

        static struct option longopts[] = {
                {"help", no_argument, NULL, 'h'},
                {NULL, 0, NULL, 0} // The last element must be all zeros.
        };

        while ((ch = getopt_long(argc, argv, "h", longopts, NULL)) != -1) {
                switch (ch) {
                case 'h':
                        break;
                case '?':
                default:
                        return EINVAL;
                }
        }

        rc = dfu_usb_library_init();
        if (DFU_USB_SUCCESS != rc) {
                printf("Failed to initialize DFU USB library. Error: %s\n",
                        dfu_usb_err2str(rc));

                return EINVAL;
        }

        dfu_usb_get_attached_devices();

        dfu_usb_library_deinit();

        return 0;
}
