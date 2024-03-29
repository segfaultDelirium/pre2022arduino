{{

  File:                   LM34 Temperature Sensor DEMO.spin
  Date:                   January 4, 2013
  Author[s]:              Daniel Harris
  Company:                Parallax Inc.

  Description:

  This is a simple demonstration of the LM34 temperature sensor.  This program uses
  the Propeller BOE's onboard ADC to read the temperature sensor.  The raw ADC value
  and calculated temperature are displayed on both the Parallax Serial Terminal and
  a VGA monitor if it is connected.



}}

CON

  _xinfreq = 5_000_000
  _clkmode = xtal1 + pll16x


  PC_BAUD       = 115_200

  ADC_CH0       = 1 << 0
  ADC_CH1       = 1 << 1
  ADC_CH2       = 1 << 2
  ADC_CH3       = 1 << 3
  ADC_ALL       = ADC_CH0 + ADC_CH1 + ADC_CH2 + ADC_CH3

  F_ADC_1TICK   = 5.0/1024.0                            'the voltage value of a single ADC tick =(MAX_VOLTS - MIN_VOLTS)/RANGE
  F_LM34_RES    = 0.01                                  '.01 volts per degree F, resolution of the sensor


  VGA_BASE_PIN  = 8  

'' VGA Output a character
''
''     $00 = clear screen
''     $01 = home
''     $08 = backspace
''     $09 = tab (8 spaces per)
''     $0A = set X position (X value follows)
''     $0B = set Y position (Y value follows)
''     $0C = set color (color number follows)
''     $0D = cariage return + line feed
''  others = printable characters

   VGA_CLRSCR   = $00
   VGA_HOME     = $01
   VGA_BS       = $08
   VGA_TAB      = $09
   VGA_SET_X    = $0A
   VGA_SET_Y    = $0B
   VGA_SET_CLR  = $0C
   VGA_CRLF     = $0D

  
{{

             Wiring Diagram for the Propeller BOE


 --- VGA Output Hookup ---             --- LM34 Sensor Hookup ---                                 
                                        ┌───────┐                                                 
  VGA        Propeller Pin              │       │                                                 
 Header         Header                  │  LM34 │       <--- Looking at the flat face of the sensor 
                                        │       │                                                   
   R1  ───────  P15                    └─┬─┬─┬─┘                                                   
   R0  ───────  P14                      │ │ │                                                     
   G1  ───────  P13                      │ │ └─  GND                                               
   G0  ───────  P12                      │ └───  AD0                                               
   B1  ───────  P11                      └─────  +5V                                               
   B0  ───────  P10                                                                                                  
   H   ───────  P9       
   V   ───────  P8
   
}}

OBJ

  adc   :       "PropBOE ADC"
  pc    :       "Parallax Serial Terminal"
  fmath :       "FloatMath"
  fs    :       "FloatString"
  vga   :       "VGA_Text"
  
VAR

  long  temperatureSample

PUB Go | rawReading, fSample

  pc.Start(PC_BAUD)
  adc.Start(ADC_CH0)
  vga.Start(VGA_BASE_PIN)
  
  vga.Out(VGA_CLRSCR)

  
  fs.SetPrecision(3)                                    '
  

  repeat

    rawReading := adc.In(0)                             'Read Channel 0 of the ADC
    fSample := fmath.FFloat(rawReading)                 'Convert the reading into IEEE 754 single precision floating point notation
    fSample := fmath.FMul(fSample, F_ADC_1TICK)         'Do a floating point multiply (adc reading * the voltage value of a single ADC tick)
    fSample := fmath.FDiv(fSample, F_LM34_RES)          'Do a floating point divide (the voltage supplied by the sensor / the resolution per degree)

    
    '================= Print the calculated data to the serial terminal ==================
  
    pc.Home

    pc.Str(string("=== LM34 Temperature Sensor Test ==="))
    pc.NewLine
    pc.NewLine

    pc.Str(string("Raw ADC Reading: "))
    pc.Dec(rawReading)
    pc.Chars(" ", 5)
    pc.NewLine

    pc.Str(string("Calculated Temperature: "))
    pc.Str(fs.FloatToString(fSample))                   'Since a floating point number is not represented the same as a decimal number,
                                                        'we have to convert it to a string to be displayed.
    pc.Char(" ")
    pc.Char("F")                                        'Add the Fahrenheit unit notation.
    pc.Chars(" ", 5)
    pc.NewLine


    '============== Print raw data to the VGA screen ==================

    vga.Out(VGA_HOME)
    vga.Str(string(" === LM34 Temp Sensor Test ==="))
    vga.Out(VGA_CRLF)
    vga.Out(VGA_CRLF)    

    vga.Str(string("Raw ADC Reading: "))
    vga.Dec(rawReading)
    repeat 5
      vga.Out(" ")
    vga.Out(VGA_CRLF)

    vga.Str(string("Calculated Temperature: "))
    vga.Str(fs.FloatToString(fSample))
    vga.Str(string(" F"))
    repeat 5
      vga.Out(" ")
    vga.Out(VGA_CRLF)


    waitcnt(cnt + clkfreq/35)                           'Pause for 1/35th of a second so as not to flood the serial port with data.


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