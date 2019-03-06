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
 * 函 数 名  : zBaseUtil.getMicroSecond
 * 负 责 人  : 刘春龙
 * 创建日期  : 2015年11月12日
 * 函数功能  : 获取微秒值 -- 1/1000000秒
 * 输入参数  : void
 * 输出参数  : 无
 * 返 回 值  : std
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
std::int64_t UtilTime::getMicroSecond(void)
{
    struct timespec ts = {0, 0};   
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (std::int64_t)ts.tv_sec * 1000000 + ts.tv_nsec/1000;
}

/*****************************************************************************
 * 函 数 名  : UtilTime.getMilliSecond
 * 负 责 人  : 刘春龙
 * 创建日期  : 2015年12月03日
 * 函数功能  : 获取毫秒值 -- 1/1000秒
 * 输入参数  : void
 * 输出参数  : 无
 * 返 回 值  : std
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
std::int64_t UtilTime::getMilliSecond(void)
{
    struct timespec ts = {0, 0};
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (std::int64_t)ts.tv_sec * 1000 + ts.tv_nsec/1000000;
}

/*****************************************************************************
 * 函 数 名  : UtilTime.getSecond
 * 负 责 人  : 刘春龙
 * 创建日期  : 2015年12月03日
 * 函数功能  : 获取系统启动到当前的秒值 -- 单位:秒
 * 输入参数  : void
 * 输出参数  : 无
 * 返 回 值  : std
 * 调用关系  : 
 * 其    它  : 

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

