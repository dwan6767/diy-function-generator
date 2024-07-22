 Function Generator using 555 timer,  lm358 op amp , Arduino and oled screen for signal.
I will share the schematic of this . 
Basically I generated 555 timer in astable mode to generate square wave . then a rc low pass filter to generate triangle wave then another to generate sine wave . i have also added an op amp to control the gain . 
arduino connections 
5v power to oled 
gnd 
scl to A5
SDA to A4
Draw backs
1) square wave is perfect but as the triangle and sine have dc offset . i forgot to add decoupling capacitors
2) although I have set op amp for gain control without decoupling caps it is kinda useless for signal seeing
3) Arduino has limits in terms of sampling frequency . so very high frequency signal cannot be seen . due to its ADC conversation time  . 16mhz clock is divided by 2 ten times . roughly around 9600 . so according to Nyquist Shannon sampling theorem max 4.8khz we can see.  although chatgpt helped me create a better code to see this . it has limited  ADC resolution to decrease conversion time 
4) created with the help of chatgpt
5) i have not yet shown the full schematic of it i am gonna give it soon
improvements needed

