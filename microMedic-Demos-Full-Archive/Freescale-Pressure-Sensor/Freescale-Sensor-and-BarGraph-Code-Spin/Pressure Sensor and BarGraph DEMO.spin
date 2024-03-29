{{

Pressure Sensor and BarGraph DEMO.spin

Program Date: 1/4/2013
Version:      1.0

Description:

This program reads voltage values from the Propeller BOE's ADC and prints the raw value to
the Parallax Serial Terminal program running on your PC.  The program also uses a cog to
show a linear representation of the pressure sensed on a 10-segment LED bar graph.



                           Propeller BOE Wiring Diagram


=== Pressure Sensor Pin Connections ===   
                                                   
                         +5v                       
                                                  
                          │                        
          ┌─────────────┐ │                        
          │             │ │                        
          │   MPX5010   │ │                         
          │             │ │                         
          └─┬─┬─┬─┬─┬─┬─┘ │                         
      Pin 1 │ │ │ x x x   │                        
    AD0 ───┘ │ └─────────┘                        
                                                  
             GND



=== LED Bar Graph Pin Connections ===
                                     
     P0 ──────┐                 
     P1 ──────┫                 
     P2 ──────┫                 
     P3 ──────┫                 
     P4 ──────┫                 
     P5 ──────┫                 
     P6 ──────┫                 
     P7 ──────┫                             
     P8 ──────┫                                                                    
     P9 ──────┫                 
          220Ω     │                 
                   │                 
                     GND             



}}

CON

  'let the compiler know which crystal and PLL settings to use
  _xinfreq = 5_000_000
  _clkmode = xtal1 + pll16x

  INPUT         = false         'bit pattern is all 0s
  OUTPUT        = true          'bit pattern is all 1s

  PC_BAUD       = 115_200       'PC serial terminal's baud rate
  
  ADC_CH0       = 1 << 0
  ADC_CH1       = 1 << 1
  ADC_CH2       = 1 << 2
  ADC_CH3       = 1 << 3
  ADC_ALL       = ADC_CH0 + ADC_CH1 + ADC_CH2 + ADC_CH3

  'LED Bar graph pin definitions
  BAR_GRAPH_0   = 0
  BAR_GRAPH_1   = 1
  BAR_GRAPH_2   = 2
  BAR_GRAPH_3   = 3
  BAR_GRAPH_4   = 4
  BAR_GRAPH_5   = 5
  BAR_GRAPH_6   = 6
  BAR_GRAPH_7   = 7
  BAR_GRAPH_8   = 8
  BAR_GRAPH_9   = 9

OBJ

  adc   :       "PropBOE ADC"                           'Requires 1 cog
  pc    :       "Parallax Serial Terminal"              'Requires 1 cog

VAR

  'Globally accessible variables, shared by all cogs
  long pressure

  long cogStack[20]

PUB Go | rawReading

  'Start other objects
  pc.Start(PC_BAUD)
  adc.Start(ADC_CH0)

  'Launch additional cogs
  cognew(RunBarGraph, @cogStack)

  repeat

    rawReading := adc.In(0)                             'Get the reading from channel 0 on the ADC.

    pressure := rawReading / 25                         'Scale the raw reading to be displayed on the LED bar graph.
                                                        'Note that this scaled reading does not correspond with a particular
                                                        'unit of pressure such as mmH2O, mmHg, kPa, or PSI.  Check the sensor's
                                                        'datasheet (MPX5010DP) for the mV/mmH2O conversion value if you want an
                                                        'absolute reading in a particular unit of pressure.
                                                        '
                                                        'The global variable "pressure" is shared between this cog and the cog
                                                        'that is controlling the LED bar graph.

    '===== Print to the PC serial terminal =====
    pc.Home
    pc.Str(string("=== Pressure Sensor Test ==="))
    pc.NewLine
    pc.NewLine

    pc.Str(string("Raw ADC Value: "))
    pc.dec(rawReading)
    pc.Chars(" ", 5)
    pc.NewLine

    waitcnt(cnt + clkfreq/20)                           'wait for ~1/20th seconds so as not to flood the computer's serial port with data.



PUB RunBarGraph | i

  dira[BAR_GRAPH_9..BAR_GRAPH_0] := OUTPUT              'set range of pins to output
                                                        '(this works in this case because the pins are consecutive)

  
  repeat

    outa[BAR_GRAPH_9..BAR_GRAPH_0] := 1<<pressure - 1   'Continually set the value of the scaled pressure to the LED bar graph pins.
                                                        'Do a little bitwise manipulation to make the LEDs look nice.


DAT

{{
┌──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
│                                                   TERMS OF USE: MIT License                                                  │                                                            
├──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┤
│Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation    │ 
│files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy,    │
│modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software│
│is furnished to do so, subject to the following conditions:                                                                   │
│                                                                                                                              │
│The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.│
│                                                                                                                              │
│THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE          │
│WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR         │
│COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,   │
│ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                         │
└──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
}}