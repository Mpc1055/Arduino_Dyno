close all
clear all
clc

bit16 = 2^16; %LARGEST NUMBER A 16BIT REGISTER CAN HOLD 

clck = 1/16000000; %16mhz processor
ps = 64; %prescaler
scaled_clk = clck * ps;

Period = 50 *10^-3; % Time Period 50ms

Ts = Period / scaled_clk %number of scaled ticks in designated period

Tcnt = (bit16-1)- Ts
Clk_tck = Period/clck;  %number of clock ticks per timer period(50ms)




