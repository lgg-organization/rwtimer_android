#include "rw_timer.h"
#include "util_time.h"
#include "log.h"

bool RwTimer::check_task_name(const std::string &name)
{
    for (auto iter= m_tasks.begin(); iter != m_tasks.end(); iter++)
    {
        if (0 == name.compare(iter->m_name))
        {
            LOG_D("task name has been added!! name= %s\n", name.c_str());
            return false;
        }
    }
    return true;
}

bool RwTimer::add_task( const timer_task_t &timer_task)
{
    LOG_D("task name: %s", timer_task.m_name.c_str());
    if (    timer_task.m_name.empty()
        ||  !check_task_name( timer_task.m_name))
    {
        return false;
    }

    m_tasks.push_back(timer_task);
    return true;
}

bool RwTimer::delete_task(const std::string &name)
{
    bool ret = false;

    auto iter = m_tasks.begin();
    while (iter != m_tasks.end())
    {
        if (0 == name.compare(iter->m_name))
        {
            iter = m_tasks.erase(iter);
            LOG_D("delete_task: name= %s\n", name.c_str());
            ret = true;
        }else ++iter;
    }
    return ret;
}

// 更新任务执行时间: 提前或延长，下一次任务执行。
bool RwTimer::update_task_time(
    const std::string &name, std::int64_t time)
{
    for (auto iter= m_tasks.begin(); iter != m_tasks.end(); iter++)
    {
        if (0 == name.compare(iter->m_name))
        {
            iter->m_time = time;
            return true;
        }
    }
    return false;
}

/*****************************************************************************
 * 函 数 名  : RwTimer.tasks_proc
 * 负 责 人  : 刘春龙
 * 创建日期  : 2017年8月31日
 * 函数功能  : 执行所有的定时任务
               注意: 定时任务中，不能调用add_task等接口。否则，造成循环嵌套。
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : void
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
void RwTimer::tasks_proc()
{
    std::uint64_t curr_time = UtilTime::getMilliSecond();

    auto iter = m_tasks.begin();
    while (iter != m_tasks.end())
    {
        if ((curr_time - iter->m_time) >= iter->m_gap)
        {
            iter->m_task();
            iter->m_time = curr_time;

            if (    TASK_TYPE_MULTI == iter->m_task_type
                &&  (0 == (--iter->m_task_count)))
            {
                iter = m_tasks.erase(iter);
            }
            else ++iter;
        }else ++iter;
    }
    return;
}

