# Shift Register and 1-digt 7 segment display

In this experiment I was playing with ESP8266 capabilities to work with external devices like 
1-digit 7 segment display (5161AH).

This display module has 10 pins (2 for GND) where 8 of the pins are for powering a single segment (including dot in right down corner). At the same time ESP8266 doesn't have enough digital outputs to use more than one of such displays, especially when you want to involve more external devices for I/O activity in your project.

That's a good application of [shift regsters](https://en.wikipedia.org/wiki/Shift_register).
This simple device allows you to manipulate state of multiple outputs (8 in our case) using only 3 digital pins on ESP8266.

Work principle is very simple:
1. Set LATCH pin to low
2. Send byte representing register output pins configuration using impulses to DATA and CLOCK pins (see detials in the link above)
3. Set LATCH pin high to make register set output pins according to the configuration byte
4. Viola!

Here's simple connections diagram used in the experiment:
```

 +3.3V
o-----+----------------------------------+
      |                                  |
      |                                  |
+-----+-------------+           +---------+---------------+         +---------------------+
|                   |           |       (10,16)           |         |                     |
|                   |           |                         |         |                     |
|   == ESP8266 ==   |           |      == 74HC595N ==     |         | == 1 DIGIT DSPLY == |
|                   |           |                       Q1|-------->|a                    |
|                 D1|---------->|14 (SER/DATA)          Q2|-------->|b                    |
|                 D2|---------->|12 (RCLK/LATCH)        Q3|-------->|c                    |
|    GND          D5|---------->|11 (SRCLK/CLOCK)       Q4|-------->|d                    |
+-------------------+           |                       Q5|-------->|e                    |
      |                         |                       Q6|-------->|f                    |
      |                         |     (8,13)            Q7|-------->|g      GND           |
      |                         +-------+-----------------+         +---------------------+
 -    |                                 |                                    |
o-----+---------------------------------+------------------------------------+
```
