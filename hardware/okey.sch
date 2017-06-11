EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:Gajda_cmosieee
LIBS:Gajda_ttlieee
LIBS:40xx
LIBS:cherry
LIBS:okey-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 10
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 5400 3850 500  2500
U 56894DB6
F0 "Cherry-MX switches Column 5x" 60
F1 "cherry-mx_5_vertical_generic.sch" 60
F2 "KSW_BUS" B L 5400 4100 60 
$EndSheet
$Sheet
S 5400 2950 1500 500 
U 56894E17
F0 "Cherry-MX Switches Row 3x up to 8x " 60
F1 "cherry-mx_3to8_horizotal_generic.sch" 60
F2 "KSW_BUS" B L 5400 3200 60 
$EndSheet
$Sheet
S 5400 700  2300 1750
U 568E4808
F0 "Panel Generic SPI01" 60
F1 "panel_generic_spi01.sch" 60
F2 "KSW_BUS" B R 7700 1300 60 
F3 "PNL_BUS_IN" I L 5400 1000 60 
F4 "PNL_BUS_OUT" O R 7700 1000 60 
$EndSheet
$Sheet
S 2400 700  1800 800 
U 568E5EC3
F0 "Controller" 60
F1 "controller_teensy_2.0.sch" 60
F2 "PNL_BUS_OUT" B R 4200 1000 60 
$EndSheet
Wire Bus Line
	4200 1000 5400 1000
Wire Bus Line
	7700 1300 7900 1300
Wire Bus Line
	7900 1300 7900 3200
Wire Bus Line
	7900 2700 5100 2700
Wire Bus Line
	5100 2700 5100 4100
Wire Bus Line
	5100 3200 5400 3200
Wire Bus Line
	5100 4100 5400 4100
$Sheet
S 8200 2950 2800 500 
U 5694930E
F0 "Extra Buttons" 60
F1 "extrabtns.sch" 60
$EndSheet
Wire Bus Line
	7100 3200 8200 3200
$Sheet
S 7300 3850 500  2500
U 56950D46
F0 "Cherry-MX switches Column with two 1.25 keys" 60
F1 "cherry-mx_3+2_vertical_generic.sch" 60
F2 "KSW_BUS" B L 7300 4100 60 
$EndSheet
Wire Bus Line
	7100 3200 7100 4100
Wire Bus Line
	7100 4100 7300 4100
$Sheet
S 2800 3850 500  2500
U 58E03C59
F0 "Cherry-MX switches 3+2xCol Rows 1-5" 60
F1 "cherry-mx_3+2_vertical_row1to5.sch" 60
$EndSheet
$Sheet
S 700  3850 500  2500
U 58E03FE3
F0 "Cherry-MX switches 5xCol Rows 1-5" 60
F1 "cherry-mx_5_vertical_row1to5.sch" 60
$EndSheet
$Sheet
S 8200 2050 2800 500 
U 593D29A0
F0 "Extra Buttons Row 6 and 7 small" 60
F1 "extrabtns_row6+7_small.sch" 60
$EndSheet
Wire Bus Line
	7900 2300 8200 2300
$EndSCHEMATC
