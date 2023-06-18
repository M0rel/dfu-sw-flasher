#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <string.h>

#define LOG_TAG         "dfu_sw_flash"
#define VERBOSITY_LIMIT 2

#define FILE_NAME_NO_PATH(filepath)                                             \
        strrchr((filepath), '/') ? strrchr((filepath), '/') + 1 : (filepath)

enum verbosity {
        LOG_DISABLE = 0,
        LOG_ERROR   = 1,
        LOG_INFO    = 2,
        LOG_DBG     = 3
};

#define log(verbosity, msg, fmt, ...)                                           \
        do {                                                                    \
                log_write(verbosity, "[%s:%s:%d] %s" fmt, LOG_TAG,              \
                          FILE_NAME_NO_PATH(__FILE__), __LINE__, msg,           \
                          ## __VA_ARGS__);                                      \
        } while (0)

#define log_err(fmt, ...)       log(LOG_ERROR, "Err: ", fmt, ## __VA_ARGS__)
#define log_info(fmt, ...)      log(LOG_INFO, "Info: ", fmt, ## __VA_ARGS__)
#define log_dbg(fmt, ...)       log(LOG_DBG, "Dbg: ", fmt, ## __VA_ARGS__)

void log_write(int verbosity, const char *fmt, ...);

#endif /* __LOGGER_H__ */
