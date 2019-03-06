#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>
#include <string>

#include "util_time.h"

#define DEBUG_BUFFER_MAX_LENGTH (1024)
#ifndef LOG_TAG
#define  LOG_TAG  "TIMER_TEST"
#endif

/*****************************************************************************
 * 函 数 名  : zLog.zLogPrint_debug
 * 负 责 人  : 刘春龙
 * 创建日期  : 2015年11月28日
 * 函数功能  : 调试打印
 * 输入参数  : const char *filename  文件名
               const char *func      函数名
               const char *format    格式
               ...                   参数
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
int zLogPrint_debug(const char *filename, const char *func, int line, const char *format, ...)
{
    char buffer[DEBUG_BUFFER_MAX_LENGTH + 1] = { 0 };

    // filename example: D:/workspace/develop/Software/source/md_noScreen/jni/../zVideoThread.cpp
    char * sub_filename =  strrchr(filename, '/');
    int size = snprintf(buffer, DEBUG_BUFFER_MAX_LENGTH, "%s, %lld ms, %s, %s, %d: ", 
        UtilTime::getTimeString().c_str(), 
        (UtilTime::getMilliSecond()),
        (NULL != sub_filename ? (sub_filename + 1) : filename), 
        (NULL != func ? func : ""), line);

    va_list arg;
    va_start(arg, format);
    (void)vsnprintf(buffer + size, DEBUG_BUFFER_MAX_LENGTH - size, format, arg);
    va_end(arg);

    //printf("%s", buffer);
    __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, "%s\n", buffer);
    return 0;
}

