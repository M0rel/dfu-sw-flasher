
#ifndef __DFU_USB_API_H__
#define __DFU_USB_API_H__

#include "dfu_usb_error.h"

dfu_usb_error_t dfu_usb_library_init(void);
void dfu_usb_library_deinit(void);

#endif /* __DFU_USB_API_H__ */
