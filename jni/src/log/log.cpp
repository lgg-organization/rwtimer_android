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
 * �� �� ��  : zLog.zLogPrint_debug
 * �� �� ��  : ������
 * ��������  : 2015��11��28��
 * ��������  : ���Դ�ӡ
 * �������  : const char *filename  �ļ���
               const char *func      ������
               const char *format    ��ʽ
               ...                   ����
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

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

