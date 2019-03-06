#ifndef __RW_TIMER_TASK_H__
#define __RW_TIMER_TASK_H__

#include <stdint.h>
#include <string>
#include <functional>   // std::bind

#include "util_time.h"

// 定时器类: 用在已创建的线程中。
typedef enum
{
    TASK_TYPE_ALWAYS    = 0, // 一直执行
    TASK_TYPE_MULTI     = 1, // 执行多次
}task_type_t;

typedef struct 
{
    std::string m_name;     // 定时器名称
    std::uint64_t m_gap;    // 单位: 毫秒, 间隔时长
    std::uint64_t m_time;   // 单位: 毫秒, 上次执行时间

    task_type_t m_task_type; //
    int m_task_count; // 执行次数，类型为TASK_TYPE_MULTI，该值有效
    std::function<void()> m_task;
}timer_task_t;

// 万能函数包裹器
template<typename callable, class... arguments>
std::function<typename std::result_of<callable(arguments...)>::type()> 
make_function(
    callable&& func, arguments&&... args)
{
    return std::bind(std::forward<callable>(func), std::forward<arguments>(args)...);
}

// 支持任意类型函数，包括类成员函数等。
template<typename callable, class... arguments>
void make_timer_task(timer_task_t &timer_task,
    const std::string &name, 
    task_type_t task_type, int task_count, std::uint64_t gap, std::uint64_t delay,
    callable&& func, arguments&&... args)
{
    timer_task.m_name = name;
    timer_task.m_gap = gap;
    timer_task.m_time = UtilTime::getMilliSecond() + delay;
    timer_task.m_task_type = task_type;
    timer_task.m_task_count = task_count;
    //timer_task.m_task = std::bind<void>(std::forward<callable>(func), std::forward<arguments>(args)...);
    timer_task.m_task = make_function(std::forward<callable>(func), std::forward<arguments>(args)...);
    return;
}
#endif