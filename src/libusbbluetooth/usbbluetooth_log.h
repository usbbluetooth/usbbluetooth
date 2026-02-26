#ifndef _H_USBBLUETOOTH_LOG_
#define _H_USBBLUETOOTH_LOG_

#include "usbbluetooth_api.h"

typedef enum
{
    USBBLUETOOTH_LOG_NONE = 0,
    USBBLUETOOTH_LOG_ERROR = 1,
    USBBLUETOOTH_LOG_WARN = 2,
    USBBLUETOOTH_LOG_INFO = 3,
    USBBLUETOOTH_LOG_DEBUG = 4
} usbbluetooth_log_level_t;

void USBBLUETOOTH_CALL usbbluetooth_log_set_level(usbbluetooth_log_level_t level);

void usbbluetooth_log(usbbluetooth_log_level_t level, const char *fmt, ...);

#define usbbluetooth_log_error(...) usbbluetooth_log(USBBLUETOOTH_LOG_ERROR, __VA_ARGS__)
#define usbbluetooth_log_warn(...) usbbluetooth_log(USBBLUETOOTH_LOG_WARN, __VA_ARGS__)
#define usbbluetooth_log_info(...) usbbluetooth_log(USBBLUETOOTH_LOG_INFO, __VA_ARGS__)
#define usbbluetooth_log_debug(...) usbbluetooth_log(USBBLUETOOTH_LOG_DEBUG, __VA_ARGS__)

#endif
