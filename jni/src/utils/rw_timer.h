#ifndef __RW_TIMER_H__
#define __RW_TIMER_H__

#include <list>
#include <string>

#include "rw_timer_task.h"

class RwTimer
{
public:
    RwTimer() {}
    ~RwTimer() {}

    bool add_task( const timer_task_t &timer_task);
    bool delete_task(const std::string &name);
    bool update_task_time(const std::string &name, std::int64_t time);
    void tasks_proc();

private:
    bool check_task_name(const std::string &name);

private:
    std::list<timer_task_t> m_tasks;
};

#endif
