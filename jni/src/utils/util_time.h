#ifndef __UTIL_TIME_H__
#define __UTIL_TIME_H__

#include <cstdint> // std::int64_t
#include <mutex>
#include <time.h> // time_t
#include <atomic>

#define MMD_DEBUG  1 // 调试开关

/************************************************** macro **************************************************/
#if MMD_DEBUG
/* define for performace statistics */
/* NOTE: make sure you init these three vars as local vars or global vars */
#define TIMER_INIT(modulename) \
    int64_t time_##modulename = 0;\
    int64_t time_##modulename##_sum = 0;\
    int64_t time_##modulename##_count = 0

#define TIMER_STATIC_INIT(modulename) \
    static int64_t time_##modulename = 0;\
    static int64_t time_##modulename##_sum = 0;\
    static int64_t time_##modulename##_count = 0

#define EXTERN_TIMER_INIT(modulename) \
    extern int64_t time_##modulename;\
    extern int64_t time_##modulename##_sum;\
    extern int64_t time_##modulename##_count

#define TIMER_BGN(modulename) \
{\
    time_##modulename = UtilTime::getMilliSecond();\
}

#define TIMER_END(modulename) \
{\
    time_##modulename##_count++;\
    time_##modulename##_sum += (UtilTime::getMilliSecond() - time_##modulename);\
}

#define TIMER_SHOW(modulename) \
{\
    if (time_##modulename##_count > 0)\
    {\
        LOG_D("avg module "#modulename" time:%.2fms \n",\
            time_##modulename##_sum / (1.0 * time_##modulename##_count));\
    }\
}

#define TIMER_SHOW_FREQ(modulename, freq) \
{\
    if ((time_##modulename##_count > 0) && (0 == time_##modulename##_count % (freq)))\
    {\
        LOG_D("avg module "#modulename" time:%.2fms \n",\
            time_##modulename##_sum / (1.0 * time_##modulename##_count));\
        time_##modulename##_count = 0;\
        time_##modulename##_sum = 0;\
    }\
}

#define TIMER_FPS_SHOW(modulename) \
{\
    if (time_##modulename##_sum > 0)\
    {\
        LOG_D("module "#modulename" fps:%.2f\n",\
            (time_##modulename##_count * 1000.0) / time_##modulename##_sum);\
    }\
}

#define TIMER_FPS_SHOW_SLOW(modulename, freq) \
{\
    if ((time_##modulename##_sum > 0) && (0 == time_##modulename##_count % (freq)))\
    {\
        LOG_D("module "#modulename" fps:%.2f\n",\
            (time_##modulename##_count * 1000.0) / time_##modulename##_sum);\
        time_##modulename##_count = 0;\
        time_##modulename##_sum = 0;\
    }\
}

#else
#define TIMER_INIT(modulename) 
#define TIMER_BGN(modulename) 
#define TIMER_END(modulename) 
#define TIMER_SHOW(modulename) 
#define TIMER_SHOW_FREQ(modulename, freq) 
#define TIMER_FPS_SHOW(modulename) 
#define TIMER_FPS_SHOW_SLOW(modulename, freq)
#endif

class UtilTime
{
public:
    static std::string getTimeString();
    static std::string getTimeString_v2();

    static std::int64_t getMicroSecond(void);
    static std::int64_t getMilliSecond(void);
    static std::int64_t getSecond(void);
    static void sleep(std::int64_t milliseconds); // 单位: 毫秒

private:
    UtilTime() {}
    ~UtilTime() {}
};

#endif

