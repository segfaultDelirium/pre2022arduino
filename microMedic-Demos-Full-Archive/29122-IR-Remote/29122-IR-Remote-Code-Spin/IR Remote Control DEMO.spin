{{

IR Remote Control DEMO.spin

Program Date: 12/26/2012
Version:      1.2

Description:

This program reads IR codes sent to an infrared receiver via Sony TV remote control and prints the code to the PC's serial terminal.
Data is encoded in variable length high pulse widths. Shorter lengths of time that the pulse is high represents a zero while
longer lengths of time represent a one.  

}}
CON

  _clkmode = xtal1 + pll16x
  _clkfreq = 80_000_000

  IR_PIN        = 0
  PC_BAUD       = 115_200

  CODE_TIMEOUT  = 25_000
  THRESHOLD_CNT = 25

  'key code constant definitions for Parallax Universal Remote (#020-00001), Sony program code 605.
  IR_POWER      = $012B
  
  IR_1_KEY      = $0101
  IR_2_KEY      = $0103
  IR_3_KEY      = $0105
  IR_4_KEY      = $0107
  IR_5_KEY      = $0109
  IR_6_KEY      = $010B
  IR_7_KEY      = $010D
  IR_8_KEY      = $010F
  IR_9_KEY      = $0111
  IR_0_KEY      = $0113

  IR_UP         = $0121
  IR_DOWN       = $0123
  IR_LEFT       = $0127
  IR_RIGHT      = $0125
  IR_MUTE       = $0129
  
  IR_ENTER      = $0117
  IR_PREV_CH    = $0177

{{
=== IR Reciver Connection Diagram ===

                     +5v
                      
                ┌───┐ │
                │ o │ │
                └┬┬┬┘ │
                 ││└──┘
            220Ω │
          P0 ───┘│  
                  │
                  
}} 
VAR



OBJ

  pc    :      "Parallax Serial Terminal"     'uncomment to see debug output on the serial port

PUB Go | code

  
  pc.start(PC_BAUD)
  pc.clear 
  
  repeat                                   'main loop                                                 
    code := Get_IR_Code(IR_PIN, THRESHOLD_CNT)

    if code > 0
      pc.hex(code,4)
      pc.char(" ")
      pc.bin(code,32)
      pc.char(13)



PUB Get_IR_Code(pin, threshold) | temp, i
''
''  Parameters:
''  Pin = the IO pin which the IR receiver is connected to
''  Threshold = the number of pulse width counts that distinguishes between a 0 and 1, empircally determined
''
''  Returns:
''    -1 if the method timed out waiting for a pulse or the value of the code received.
''
''  Example call: newCode := Get_IR_Code(0, 25)
''  Expected outcome: if a code is being received, save the code received on pin 0 into the "newCode" variable
''
  
                          
  dira[pin]~                                            'set pin to input

  'zero out uninitialized variables
  i~
  result~

  if Wait_On_State(pin, 1, CODE_TIMEOUT) < 0            'is there a code to receive
    return -1                                           '  no code to receive, so bail
    
  repeat                                                'build the code loop
    Wait_On_State(pin, 1, CODE_TIMEOUT)                 'we dont care about the the high pulses, so just wait till they are out of the way

    temp := Wait_On_State(pin, 0, CODE_TIMEOUT)         'measure the low pulse length and save in temp
    if temp > 0
      result |= ((temp > threshold)&1) << i++           'build the code here, bit by bit
    else
      quit                                              'done, bail
  
pri Wait_On_State(pin, state, timeout) | future_cnt                                                                                                


  result~                       'clear the counter
  future_cnt :=  cnt + (constant(_clkfreq/1_000_000)*timeout)      'take note of some time in the future, timeout should be in microseconds (x10^-6)
  repeat while ina[pin] == (state & 1)
    result++                    'count the number of iterations that the pin was in the state
    if cnt > future_cnt         'check for timeout
      result~~                  'if we timed out, invalidate the count
      quit                      'we timed out, bail with a -1


pri Pause(duration)

  'This function pauses program execution for approximately [duration] micro seconds
  'so 1_000_000 would be approximately one second.  Doesnt account for instruction
  'execution time overhead.

  if duration < 381
    duration := 381             'lower bound limit. anything lower than this, we
                                'have to wait until the counter comes back around,
                                'which is MUCH longer than [duration].
  waitcnt(((clkfreq / 1_000_000) * duration) + cnt)


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