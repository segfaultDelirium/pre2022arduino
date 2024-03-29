''******************************************
''*  ColorPAL Sensor Demo Program          *
''*                                        *
''*  Author: Phil Pilgrim, Daniel Harris   *
''*  See end of file for terms of use.     *
''******************************************

{{

  Wiring Diagram for the Propeller BOE


  --- VGA Output Hookup ---

  VGA        Propeller Pin
 Header         Header

   R1  ───────  P15
   R0  ───────  P14
   G1  ───────  P13
   G0  ───────  P12
   B1  ───────  P11
   B0  ───────  P10
   H   ───────  P9
   V   ───────  P8
                                                                     ┌──────────────┐
                                                                     │              │
                                                                     │   ColorPAL   │
                                       Servo Extension Cable         │    Sensor    │
                            ========================================│              │
                                                                    │              │
                                                                    │              │
                   │ │      │ │      │ │                             │              │
  Propeller BOE    │ │      │ │      │ │                             └──────────────┘
  Servo Headers   P14│     P16│     P18│                                      
                    P15      P17      P19



  Connect a servo extension cable between the ColorPAL and P16 on the Propeller BOEs servo port.
  Make sure you connect the servo extension cable correctly, observing proper orientation/polarity.
  For this cable and sensor, white is data, red is power (+5v), and black is GND.
  
                    
}}                                                                            
                                                                              
CON                                                                           

  'Setup the system clock settings
  _clkmode      = xtal1 + pll16x     
  _xinfreq      = 5_000_000
  

  CPAL_PIN      = 16                 'Serial I/O pin to which the ColorPAL is connected.

  VGA_BASE_PIN  = 8

  PC_BAUD       = 115_200

  

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
   
   
   
OBJ

  cpal  : "ColorPAL"                 'Object for ColorPAL.
  pc    : "Parallax Serial Terminal" 'Object for PC serial I/O.
  vga   : "VGA_Text"

VAR

  long  red, green, blue             'NOTE: keep these three variables contiguous.

  long  colorPalStarted


PUB Start | temp

  pc.Start(PC_BAUD)                    'Get PC I/O set up.
  vga.Start(VGA_BASE_PIN)
  
  vga.Out(VGA_CLRSCR)

  
  repeat

    '======================== Sample the Color PAL sensor =======================
    SampleColorPal


    '=================== Print raw data to the serial terminal ==================
    pc.Home
    pc.Str(string("=== ColorPAL Demo ==="))
    pc.NewLine

    pc.Str(string("Raw Red Value:   "))
    pc.Dec(red)
    pc.Chars(" ", 5)
    pc.NewLine

    pc.Str(string("Raw Green Value: "))
    pc.Dec(green)
    pc.Chars(" ", 5)
    pc.NewLine

    pc.Str(string("Raw Blue Value:  "))
    pc.Dec(blue)
    pc.Chars(" ", 5)
    pc.NewLine



    '============== Print raw data to the VGA screen, and change the text colors ==================

    'pack the current color sample into a format that the video driver can use for the background and text color.
    temp := (((red>>6) & %11)<<4) | (((green>>6) & %11)<<2) | (((blue>>6) & %11)<<0)
    
    byte[@sampleColorPallet]   := !temp                 'set foreground text color, inverted from background color
    byte[@sampleColorPallet+1] := temp                  'set background text color

    vga.SetColors(@sampleColorPallet)


    vga.Out(VGA_HOME)
    vga.Str(string("     === ColorPAL Demo ==="))
    vga.Out(VGA_CRLF)

    vga.Str(string("Raw Red Value:   "))
    vga.Dec(red)
    repeat 5
      vga.Out(" ")
    vga.Out(VGA_CRLF)

    vga.Str(string("Raw Green Value: "))
    vga.Dec(green)
    repeat 5
      vga.Out(" ")
    vga.Out(VGA_CRLF)

    vga.Str(string("Raw Blue Value:  "))
    vga.Dec(blue)
    repeat 5
      vga.Out(" ")
    vga.Out(VGA_CRLF)


    vga.Out(VGA_CRLF)
    vga.Str(string("     ...Sample Characters..."))
    vga.Out(VGA_CRLF)

    'Print all available characters to the VGA screen as a sample.
    repeat temp from 16 to 255
      vga.Out(temp)

    

PUB SampleColorPal

  if colorPalStarted == false
    cpal.Start(CPAL_PIN) 'Start up the ColorPAL.
    colorPalStarted := true
    
  longmove(@red, cpal.getRGB, 3)    'Get color values.


DAT


'we only really use the top 2 bytes, but the rest is needed by the video driver
sampleColorPallet       byte    0[16]


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
  