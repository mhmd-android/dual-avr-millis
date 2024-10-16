#ifndef _MILLIS_H_
#define _MILLIS_H_

#include <interrupt.h>

extern volatile unsigned long timer1_millis;
extern volatile unsigned long timer2_millis;

interrupt [TIM1_COMPA] void timer1_compa_isr(void);
interrupt [TIM2_COMPA] void timer2_compa_isr(void);
void init_millis(unsigned long f_cpu);
void init_millis_secondary(unsigned long f_cpu);
unsigned long millis(void);
unsigned long millis_secondary(void);
void reset_millis(void);
void reset_millis_secondary(void);

#endif
