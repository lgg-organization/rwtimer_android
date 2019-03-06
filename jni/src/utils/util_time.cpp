#include <thread>
#include "util_time.h"

std::string UtilTime::getTimeString()
{
    auto tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    struct tm* ptm = localtime(&tt);
    char date[128] = { 0 };
    sprintf(date, "%d-%02d-%02d_%02d-%02d-%02d",
        (int)ptm->tm_year + 1900, (int)ptm->tm_mon + 1, (int)ptm->tm_mday,
        (int)ptm->tm_hour, (int)ptm->tm_min, (int)ptm->tm_sec);
    return std::string(date);
}

std::string UtilTime::getTimeString_v2()
{
    auto tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    struct tm* ptm = localtime(&tt);
    char date[128] = { 0 };
    sprintf(date, "%d%02d%02d%02d%02d%02d",
        (int)ptm->tm_year + 1900, (int)ptm->tm_mon + 1, (int)ptm->tm_mday,
        (int)ptm->tm_hour, (int)ptm->tm_min, (int)ptm->tm_sec);
    return std::string(date);
}

/*****************************************************************************
 * �� �� ��  : zBaseUtil.getMicroSecond
 * �� �� ��  : ������
 * ��������  : 2015��11��12��
 * ��������  : ��ȡ΢��ֵ -- 1/1000000��
 * �������  : void
 * �������  : ��
 * �� �� ֵ  : std
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
std::int64_t UtilTime::getMicroSecond(void)
{
    struct timespec ts = {0, 0};   
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (std::int64_t)ts.tv_sec * 1000000 + ts.tv_nsec/1000;
}

/*****************************************************************************
 * �� �� ��  : UtilTime.getMilliSecond
 * �� �� ��  : ������
 * ��������  : 2015��12��03��
 * ��������  : ��ȡ����ֵ -- 1/1000��
 * �������  : void
 * �������  : ��
 * �� �� ֵ  : std
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
std::int64_t UtilTime::getMilliSecond(void)
{
    struct timespec ts = {0, 0};
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (std::int64_t)ts.tv_sec * 1000 + ts.tv_nsec/1000000;
}

/*****************************************************************************
 * �� �� ��  : UtilTime.getSecond
 * �� �� ��  : ������
 * ��������  : 2015��12��03��
 * ��������  : ��ȡϵͳ��������ǰ����ֵ -- ��λ:��
 * �������  : void
 * �������  : ��
 * �� �� ֵ  : std
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
std::int64_t UtilTime::getSecond(void)
{
    struct timespec ts = {0, 0};
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (std::int64_t)ts.tv_sec;
}

void UtilTime::sleep(std::int64_t milliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    return;
}

