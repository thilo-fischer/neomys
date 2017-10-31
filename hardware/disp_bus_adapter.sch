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
Sheet 12 13
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L CONN_02X10 P54
U 1 1 594BF735
P 4750 2950
F 0 "P54" H 4750 3500 50  0000 C CNN
F 1 "CONN_02X10" V 4750 2950 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x10_Pitch2.54mm_SMD" H 4750 1750 50  0001 C CNN
F 3 "" H 4750 1750 50  0000 C CNN
	1    4750 2950
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X06 P53
U 1 1 594C0B67
P 5500 3250
F 0 "P53" H 5500 3600 50  0000 C CNN
F 1 "CONN_01X06" V 5600 3250 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x03_Pitch2.54mm" H 5500 3250 50  0001 C CNN
F 3 "" H 5500 3250 50  0000 C CNN
	1    5500 3250
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X06 P56
U 1 1 594C2E69
P 5500 2550
F 0 "P56" H 5500 2900 50  0000 C CNN
F 1 "CONN_01X06" V 5600 2550 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x03_Pitch2.54mm" H 5500 2550 50  0001 C CNN
F 3 "" H 5500 2550 50  0000 C CNN
	1    5500 2550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR034
U 1 1 59526B77
P 4750 3550
F 0 "#PWR034" H 4750 3300 50  0001 C CNN
F 1 "GND" H 4750 3400 50  0000 C CNN
F 2 "" H 4750 3550 50  0000 C CNN
F 3 "" H 4750 3550 50  0000 C CNN
	1    4750 3550
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR035
U 1 1 59526E88
P 4500 2500
F 0 "#PWR035" H 4500 2350 50  0001 C CNN
F 1 "VDD" H 4500 2650 50  0000 C CNN
F 2 "" H 4500 2500 50  0000 C CNN
F 3 "" H 4500 2500 50  0000 C CNN
	1    4500 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 3400 4500 3500
Wire Wire Line
	4500 3500 4750 3500
Wire Wire Line
	4750 2400 4750 3550
Wire Wire Line
	4750 2400 5000 2400
Wire Wire Line
	5000 2300 5000 2500
Connection ~ 4750 3500
Wire Wire Line
	5000 3100 5300 3100
Wire Wire Line
	5000 3200 5300 3200
Wire Wire Line
	5000 3300 5300 3300
Wire Wire Line
	5300 3400 5300 3350
Wire Wire Line
	5300 3350 4500 3350
Wire Wire Line
	4500 3350 4500 3300
Wire Wire Line
	5300 3500 5250 3500
Wire Wire Line
	5250 3500 5250 3250
Wire Wire Line
	5250 3250 4500 3250
Wire Wire Line
	4500 3250 4500 3200
Wire Wire Line
	5300 3000 5300 3050
Wire Wire Line
	5300 3050 4750 3050
Connection ~ 4750 3050
Wire Wire Line
	5300 2300 5000 2300
Connection ~ 5000 2400
Wire Wire Line
	5000 2600 5050 2600
Wire Wire Line
	5050 2600 5050 2400
Wire Wire Line
	5050 2400 5300 2400
Wire Wire Line
	5000 2700 5100 2700
Wire Wire Line
	5100 2700 5100 2500
Wire Wire Line
	5100 2500 5300 2500
Wire Wire Line
	5000 2800 5150 2800
Wire Wire Line
	5150 2800 5150 2600
Wire Wire Line
	5150 2600 5300 2600
Wire Wire Line
	5000 2900 5200 2900
Wire Wire Line
	5200 2900 5200 2700
Wire Wire Line
	5200 2700 5300 2700
Wire Wire Line
	5000 3000 5250 3000
Wire Wire Line
	5250 3000 5250 2800
Wire Wire Line
	5250 2800 5300 2800
$Comp
L VDD #PWR036
U 1 1 5952842B
P 5100 3550
F 0 "#PWR036" H 5100 3400 50  0001 C CNN
F 1 "VDD" H 5100 3700 50  0000 C CNN
F 2 "" H 5100 3550 50  0000 C CNN
F 3 "" H 5100 3550 50  0000 C CNN
	1    5100 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 3400 5000 3550
Wire Wire Line
	5000 3550 5100 3550
$EndSCHEMATC
