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
Sheet 11 13
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
L CONN_01X08 P51
U 1 1 594A301A
P 6450 2150
F 0 "P51" H 6450 2600 50  0000 C CNN
F 1 "CONN_01X08" V 6550 2150 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x08_Pitch2.54mm" H 6450 2150 50  0001 C CNN
F 3 "" H 6450 2150 50  0000 C CNN
	1    6450 2150
	0    -1   -1   0   
$EndComp
$Comp
L CONN_02X08 P52
U 1 1 594A3085
P 6450 2750
F 0 "P52" H 6450 3200 50  0000 C CNN
F 1 "CONN_02X08" V 6450 2750 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x08_Pitch2.54mm_SMD" H 6450 1550 50  0001 C CNN
F 3 "" H 6450 1550 50  0000 C CNN
	1    6450 2750
	0    -1   1    0   
$EndComp
$Comp
L CONN_02X08 P50
U 1 1 594A30D2
P 6450 1300
F 0 "P50" H 6450 1750 50  0000 C CNN
F 1 "CONN_02X08" V 6450 1300 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x08_Pitch2.54mm" H 6450 100 50  0001 C CNN
F 3 "" H 6450 100 50  0000 C CNN
	1    6450 1300
	0    -1   1    0   
$EndComp
$Comp
L CONN_02X03 P48
U 1 1 594A313D
P 6300 3750
F 0 "P48" H 6300 3950 50  0000 C CNN
F 1 "CONN_02X03" H 6300 3550 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Angled_2x03_Pitch2.54mm" H 6300 2550 50  0001 C CNN
F 3 "" H 6300 2550 50  0000 C CNN
	1    6300 3750
	0    -1   1    0   
$EndComp
$Comp
L GND #PWR033
U 1 1 594A33E6
P 6800 3100
F 0 "#PWR033" H 6800 2850 50  0001 C CNN
F 1 "GND" H 6800 2950 50  0000 C CNN
F 2 "" H 6800 3100 50  0000 C CNN
F 3 "" H 6800 3100 50  0000 C CNN
	1    6800 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6800 3000 6800 3100
Wire Wire Line
	6100 2350 6100 2500
Wire Wire Line
	6200 2350 6200 2500
Wire Wire Line
	6300 2350 6300 2500
Wire Wire Line
	6400 2350 6400 2500
Wire Wire Line
	6500 2350 6500 2500
Wire Wire Line
	6600 2350 6600 2500
Wire Wire Line
	6700 2350 6700 2500
Wire Wire Line
	6800 2350 6800 2500
Wire Wire Line
	6100 1050 6050 1050
Wire Wire Line
	6050 1050 6050 2450
Wire Wire Line
	6050 2450 6100 2450
Connection ~ 6100 2450
Wire Wire Line
	6200 1050 6150 1050
Wire Wire Line
	6150 1050 6150 2450
Wire Wire Line
	6150 2450 6200 2450
Connection ~ 6200 2450
Wire Wire Line
	6300 1050 6250 1050
Wire Wire Line
	6250 1050 6250 2450
Wire Wire Line
	6250 2450 6300 2450
Connection ~ 6300 2450
Wire Wire Line
	6400 1050 6350 1050
Wire Wire Line
	6350 1050 6350 2450
Wire Wire Line
	6350 2450 6400 2450
Connection ~ 6400 2450
Wire Wire Line
	6500 1050 6450 1050
Wire Wire Line
	6450 1050 6450 2450
Wire Wire Line
	6450 2450 6500 2450
Connection ~ 6500 2450
Wire Wire Line
	6600 1050 6550 1050
Wire Wire Line
	6550 1050 6550 2450
Wire Wire Line
	6550 2450 6600 2450
Connection ~ 6600 2450
Wire Wire Line
	6700 1050 6650 1050
Wire Wire Line
	6650 1050 6650 2450
Wire Wire Line
	6650 2450 6700 2450
Connection ~ 6700 2450
Wire Wire Line
	6800 1050 6750 1050
Wire Wire Line
	6750 1050 6750 2450
Wire Wire Line
	6750 2450 6800 2450
Connection ~ 6800 2450
Wire Wire Line
	6100 1550 5950 1550
Wire Wire Line
	5950 1550 5950 3500
Wire Wire Line
	5950 3000 6100 3000
Wire Wire Line
	6200 1550 6200 1600
Wire Wire Line
	6200 1600 5900 1600
Wire Wire Line
	5900 1600 5900 4000
Wire Wire Line
	5900 3050 6200 3050
Wire Wire Line
	6200 3050 6200 3000
Wire Wire Line
	6300 1550 6300 1650
Wire Wire Line
	6300 1650 5850 1650
Wire Wire Line
	5850 1650 5850 3450
Wire Wire Line
	5850 3100 6300 3100
Wire Wire Line
	6300 3100 6300 3000
Wire Wire Line
	6400 1550 6400 1700
Wire Wire Line
	6400 1700 5800 1700
Wire Wire Line
	5800 1700 5800 4050
Wire Wire Line
	5800 3150 6400 3150
Wire Wire Line
	6400 3150 6400 3000
Wire Wire Line
	6500 1550 6500 1750
Wire Wire Line
	6500 1750 5750 1750
Wire Wire Line
	5750 1750 5750 3400
Wire Wire Line
	5750 3200 6500 3200
Wire Wire Line
	6500 3200 6500 3000
Wire Wire Line
	6600 1550 6600 1800
Wire Wire Line
	6600 1800 5700 1800
Wire Wire Line
	5700 1800 5700 3250
Wire Wire Line
	5700 3250 6600 3250
Wire Wire Line
	6600 3250 6600 3000
Wire Wire Line
	6700 1550 6700 1850
Wire Wire Line
	6700 1850 5650 1850
Wire Wire Line
	5650 1850 5650 3300
Wire Wire Line
	5650 3300 6700 3300
Wire Wire Line
	6700 3300 6700 3000
Wire Wire Line
	6800 3050 6900 3050
Wire Wire Line
	6900 1550 6900 4000
Wire Wire Line
	6900 1550 6800 1550
Connection ~ 6800 3050
Wire Wire Line
	5950 3500 6200 3500
Connection ~ 5950 3000
Wire Wire Line
	5900 4000 6200 4000
Connection ~ 5900 3050
Wire Wire Line
	5850 3450 6300 3450
Wire Wire Line
	6300 3450 6300 3500
Connection ~ 5850 3100
Wire Wire Line
	5800 4050 6300 4050
Wire Wire Line
	6300 4050 6300 4000
Connection ~ 5800 3150
Wire Wire Line
	5750 3400 6400 3400
Wire Wire Line
	6400 3400 6400 3500
Connection ~ 5750 3200
Wire Wire Line
	6900 4000 6400 4000
Connection ~ 6900 3050
$EndSCHEMATC
