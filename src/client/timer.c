#include <assert.h>

#include "timer.h"

#define MAX_TIMERS 100
static int timer_current = 0;

struct timer {
	int loops;
	float base;
	float time;
	bool active;
	timer_callback cb;
	void *arg;
};

static struct timer timers[MAX_TIMERS];

void
timer_init(float time, int loops, timer_callback cb, void *arg)
{
	struct timer *t = &timers[timer_current++];
	if (t->active)
		assert(0 && "overriding active timer!");

	if (timer_current == MAX_TIMERS)
		timer_current = 0;

	t->active = true;
	t->base = time;
	t->time = 0;
	t->loops = loops;
	t->cb = cb;
	t->arg = arg;
}

static void
timer_process(struct timer *t, float time)
{
	t->time += time;
	if (t->time >= t->base) {
		if (t->loops)
			t->time = 0;
		if (t->loops != 0 && t->loops != -1)
			t->loops--;

		if (t->cb(t->arg) == false || t->loops == 0) {
			t->active = 0;
		}
	}
}

void
timer_process_all(float time)
{
	struct timer *t;

	for (int i = 0; i < MAX_TIMERS; ++i) {
		t = &timers[i];
		if (t->active)
			timer_process(t, time);
	}
}
