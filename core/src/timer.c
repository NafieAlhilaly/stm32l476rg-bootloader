#include "timer.h"
#include "system.h"

void timer_setup(timer_t* timer, uint64_t wait_time, bool auto_reset){
    timer->wait_time = wait_time;
    timer->target_time = get_ticks() + wait_time;
    timer->auto_reset = auto_reset;
}
bool timer_has_elapsed(timer_t* timer){
    volatile uint64_t current_time = get_ticks();
    bool has_elapsed = (current_time >= timer->target_time);
    
    if (has_elapsed && timer->auto_reset) {
        uint64_t drift = current_time - timer->target_time;
        timer->target_time = (current_time + timer->wait_time) - drift;
    }
    return has_elapsed;
}
void timer_reset(timer_t* timer){
    timer_setup(timer, timer->wait_time, timer->auto_reset);
}