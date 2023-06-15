#include <stdio.h>

#include "dfu_usb_error.h"

char error_str[MAX_ERR_STR_SIZE] = {0};

static
void update_err_str(const char *str, size_t *err_cnt)
{
        if (NULL == str || NULL == err_cnt) {
                return;
        }

        if (*err_cnt > 0) {
                strcat(error_str, ERROR_SEPARATOR);
        }

        strcat(error_str, str);

        (*err_cnt)++;
}

char *dfu_usb_err2str(dfu_usb_error_t error_code)
{
        size_t err_cnt = 0;

        if (DFU_USB_SUCCESS == error_code) {
                return DFU_USB_SUCCESS_STR;
        }

        memset(error_str, 0, sizeof(error_str));

        if (IS_ERROR_PRESSENT(DFU_USB_INVALID_VALUE, error_code)) {
                update_err_str(DFU_USB_INVALID_VALUE_STR, &err_cnt);
        }
        if (IS_ERROR_PRESSENT(DFU_USB_INITIALIZATION_FAILED, error_code)) {
                update_err_str(DFU_USB_INITIALIZATION_FAILED_STR, &err_cnt);
        }

        return error_str;
}
