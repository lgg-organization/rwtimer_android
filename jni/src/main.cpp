#include <stdio.h>
#include <stdlib.h>

#include "log.h"
#include "rw_timer.h"

class TimerTest {
public:
    TimerTest() {}
    ~TimerTest() {}

    void heart_beat() {
        LOG_D("t0 = %d", m_t0);
    }
    
public:
    uint32_t m_t0 = 0;
};

int main(int argc, char* argv[])
{
    TimerTest tt;
    RwTimer timer;

    timer_task_t timer_task;
    make_timer_task(timer_task, "heart_beat_task", TASK_TYPE_ALWAYS, 0, 1*1000, 0, 
        &TimerTest::heart_beat, &tt);
    timer.add_task(timer_task);

    while(1) {
        TIMER_INIT(time_example);
        TIMER_BGN(time_example);
        
        timer.tasks_proc();
        TIMER_END(time_example);
        //TIMER_SHOW(time_example);

        UtilTime::sleep(10);
        tt.m_t0 += 1;
    }

    LOG_D("done!!");
    return 0;
}

