# dual-avr-millis
This library provides a dual-timer system for millisecond counting on tested ATmega328P microcontrollers. It utilizes both Timer1 and Timer2 to offer two independent millisecond counters.

## Files

- `millis.c`: Main implementation file
- `millis.h`: Header file with function declarations

## Usage

1. Include the header file in your project:
   ```c
   #include "millis.h"
   ```

2. Initialize the timers in your `main()` function:
   ```c
   init_millis(F_CPU);  // For Timer1
   init_millis_secondary(F_CPU);  // For Timer2
   ```

3. Use the millisecond functions as needed:
   ```c
   unsigned long time1 = millis();  // Get time from Timer1
   unsigned long time2 = millis_secondary();  // Get time from Timer2
   ```

4. Reset timers if necessary:
   ```c
   reset_millis();  // Reset Timer1
   reset_millis_secondary();  // Reset Timer2
   ```

## Functions

- `init_millis(unsigned long f_cpu)`: Initialize Timer1
- `init_millis_secondary(unsigned long f_cpu)`: Initialize Timer2
- `millis()`: Get milliseconds from Timer1
- `millis_secondary()`: Get milliseconds from Timer2
- `reset_millis()`: Reset Timer1 counter
- `reset_millis_secondary()`: Reset Timer2 counter
