#ifndef __DFU_USB_ERROR_H__
#define __DFU_USB_ERROR_H__

#include <string.h>

#define TO_ERROR(bit)                   (u_int32_t)(1 << bit)
#define IS_ERROR_PRESSENT(error, code)  (error & code)

#define ERROR_SEPARATOR                 ", "

#define DFU_USB_SUCCESS_STR                                                     \
        "Operation finished with success"

#define DFU_USB_INVALID_VALUE_STR                                               \
        "Invalid parameter specified"

#define DFU_USB_INITIALIZATION_FAILED_STR                                       \
        "Initialization failed"

#define MAX_ERR_STR_SIZE        (sizeof(DFU_USB_SUCCESS_STR) +                  \
                                 sizeof(ERROR_SEPARATOR) +                      \
                                 sizeof(DFU_USB_INVALID_VALUE_STR) +            \
                                 sizeof(ERROR_SEPARATOR) +                      \
                                 sizeof(DFU_USB_INITIALIZATION_FAILED_STR) +    \
                                 sizeof(ERROR_SEPARATOR) +                      \
                                 sizeof("\0"))

typedef enum dfu_usb_error {
        DFU_USB_SUCCESS               = 0x0,
        DFU_USB_INVALID_VALUE         = TO_ERROR(1),
        DFU_USB_INITIALIZATION_FAILED = TO_ERROR(2),
} dfu_usb_error_t;

char *dfu_usb_err2str(dfu_usb_error_t error_code);

#endif /* __DFU_USB_ERROR_H__ */
