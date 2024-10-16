#include <io.h>
#include <interrupt.h>
#include <millis.h>

volatile unsigned long timer1_millis;
volatile unsigned long timer2_millis;

interrupt [TIM1_COMPA] void timer1_compa_isr(void)
{
  timer1_millis++;
}

interrupt [TIM2_COMPA] void timer2_compa_isr(void)
{
  timer2_millis++;
}

void init_millis(unsigned long f_cpu)
{
  unsigned long ctc_match_overflow;

  ctc_match_overflow = ((f_cpu / 1000) / 8 - 1);

  // Calculate the compare match value for a 1ms interval
  TCCR1B |= (1 << WGM12) | (1 << CS11);

  // Set the compare match value (high byte first, then low byte)
  OCR1AH = (ctc_match_overflow >> 8);
  OCR1AL = ctc_match_overflow;

  // Enable the compare match interrupt
  TIMSK1 |= (1 << OCIE1A);
}

void init_millis_secondary(unsigned long f_cpu)
{
    unsigned long ctc_match_overflow;
	
	// Calculate the compare match value for a 1ms interval (with prescaler 64)
    ctc_match_overflow = ((f_cpu / 1000) / 64 - 1);
	
	// Set Timer2 to CTC mode
    TCCR2A = 0;
    TCCR2A |= (1 << WGM21);
	
	// Set prescaler to 64
    TCCR2B = 0;
    TCCR2B |= (1 << CS22);

    // Set compare match value
    OCR2A = ctc_match_overflow & 0xFF;

    // Enable the compare match interrupt
    TIMSK2 |= (1 << OCIE2A);
}

unsigned long millis(void)
{
    unsigned long millis_return;

    // Disable interrupts to ensure atomic read operation
    cli();
    millis_return = timer1_millis;
    sei(); // Re-enable interrupts

    return millis_return;
}

unsigned long millis_secondary(void)
{
    unsigned long millis_return;

    cli();
    millis_return = timer2_millis;
    sei();

    return millis_return;
}

void reset_millis(void)
{
    cli();
    timer1_millis = 0;
    sei();
}

void reset_millis_secondary(void)
{
    cli();
    timer2_millis = 0;
    sei();
}
