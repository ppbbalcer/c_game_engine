#ifndef TIMER_H
#define TIMER_H

#include <stdbool.h>

typedef bool (*timer_callback)(void *arg);

void timer_init(float time, int loops, timer_callback cb, void *arg);

void timer_process_all(float time);

#endif /* TIMER_H */
