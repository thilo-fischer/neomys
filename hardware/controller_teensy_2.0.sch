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
Sheet 5 10
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
L TEENSY2.0 U3
U 1 1 568E5EF6
P 3100 1600
F 0 "U3" V 3550 1350 60  0000 C CNN
F 1 "TEENSY2.0" V 3550 950 60  0000 C CNN
F 2 "cherry:TEENSY_2.0" H 3100 1600 60  0001 C CNN
F 3 "" H 3100 1600 60  0000 C CNN
	1    3100 1600
	1    0    0    -1  
$EndComp
$Comp
L CONN_02X03 P7
U 1 1 568E5F94
P 2050 1750
F 0 "P7" H 2050 1950 50  0000 C CNN
F 1 "CONN_02X03" H 2050 1550 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x03_Pitch2.54mm" H 2050 550 50  0001 C CNN
F 3 "" H 2050 550 50  0000 C CNN
	1    2050 1750
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X01 P8
U 1 1 568E619F
P 2550 2550
F 0 "P8" H 2550 2650 50  0000 C CNN
F 1 "CONN_01X01" V 2650 2550 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01_Pitch2.54mm" H 2550 2550 50  0001 C CNN
F 3 "" H 2550 2550 50  0000 C CNN
	1    2550 2550
	-1   0    0    1   
$EndComp
Wire Wire Line
	1750 1850 1800 1850
Wire Wire Line
	4200 1450 4200 1650
Wire Wire Line
	2300 1450 2300 1650
Wire Wire Line
	2900 1750 2850 1750
Wire Wire Line
	2850 1750 2850 2200
Wire Wire Line
	2850 2200 1600 2200
Wire Wire Line
	1600 2200 1600 1650
Wire Wire Line
	1600 1650 1800 1650
Wire Wire Line
	2900 1850 2300 1850
Wire Wire Line
	2900 1950 2800 1950
Wire Wire Line
	2800 1950 2800 2150
Wire Wire Line
	2800 2150 1650 2150
Wire Wire Line
	1650 2150 1650 1750
Wire Wire Line
	1650 1750 1800 1750
Wire Wire Line
	2350 2050 2900 2050
Wire Wire Line
	2350 1750 2300 1750
Wire Wire Line
	4200 2650 4400 2650
Wire Wire Line
	4200 2450 4600 2450
Wire Wire Line
	4200 2350 4400 2350
Wire Wire Line
	2900 2550 2750 2550
Wire Wire Line
	4900 1450 4900 1700
Connection ~ 4200 1450
Wire Wire Line
	4550 2250 4900 2250
Connection ~ 4550 1450
Wire Wire Line
	4550 2800 4900 2800
Connection ~ 4550 2250
Wire Wire Line
	4400 2350 4400 1900
Wire Wire Line
	4400 1900 4600 1900
Wire Wire Line
	4400 2650 4400 3000
Wire Wire Line
	4400 3000 4600 3000
Wire Wire Line
	5500 2550 5500 2650
$Comp
L R R1
U 1 1 568E6663
P 5650 2350
F 0 "R1" V 5730 2350 50  0000 C CNN
F 1 "R" V 5650 2350 50  0000 C CNN
F 2 "Discret:R4" V 5580 2350 50  0001 C CNN
F 3 "" H 5650 2350 50  0000 C CNN
	1    5650 2350
	0    1    1    0   
$EndComp
$Comp
L R R2
U 1 1 568E6714
P 5650 2550
F 0 "R2" V 5730 2550 50  0000 C CNN
F 1 "R" V 5650 2550 50  0000 C CNN
F 2 "Discret:R4" V 5580 2550 50  0001 C CNN
F 3 "" H 5650 2550 50  0000 C CNN
	1    5650 2550
	0    1    1    0   
$EndComp
$Comp
L R R3
U 1 1 568E673F
P 5650 2750
F 0 "R3" V 5730 2750 50  0000 C CNN
F 1 "R" V 5650 2750 50  0000 C CNN
F 2 "Discret:R4" V 5580 2750 50  0001 C CNN
F 3 "" H 5650 2750 50  0000 C CNN
	1    5650 2750
	0    1    1    0   
$EndComp
Text HLabel 2050 1450 0    60   BiDi ~ 0
PNL_BUS_OUT
Wire Wire Line
	5500 2100 4900 2100
Wire Wire Line
	5500 2650 4900 2650
Wire Wire Line
	5500 3200 4900 3200
$Comp
L LED_RCBG D25
U 1 1 56954CBA
P 6150 2550
F 0 "D25" H 6150 2900 50  0000 C CNN
F 1 "LED_RCBG" H 6150 2200 50  0000 C CNN
F 2 "LEDs:LED-RGB-5MM_Common_Cathode" H 6150 2500 50  0001 C CNN
F 3 "" H 6150 2500 50  0000 C CNN
	1    6150 2550
	-1   0    0    1   
$EndComp
Wire Wire Line
	5800 2350 5850 2350
Wire Wire Line
	5800 2550 5850 2550
Wire Wire Line
	5800 2750 5850 2750
Wire Wire Line
	5500 2100 5500 2350
Wire Wire Line
	5500 2750 5500 3200
$Comp
L CONN_02X03 P31
U 1 1 56956886
P 6150 3250
F 0 "P31" H 6150 3450 50  0000 C CNN
F 1 "CONN_02X03" H 6150 3050 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x03_Pitch2.54mm" H 6150 2050 50  0001 C CNN
F 3 "" H 6150 2050 50  0000 C CNN
	1    6150 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 3250 6400 3250
Connection ~ 6450 2550
Wire Wire Line
	5850 2750 5850 3350
Wire Wire Line
	5850 3350 5900 3350
Wire Wire Line
	5900 3350 5900 3550
Wire Wire Line
	5900 3550 6550 3550
Wire Wire Line
	6550 3550 6550 3150
Wire Wire Line
	6550 3150 6400 3150
Wire Wire Line
	5850 2350 5850 2450
Wire Wire Line
	5850 2450 5900 2450
Wire Wire Line
	5900 2450 5900 3150
Wire Wire Line
	5850 2550 5850 2650
Wire Wire Line
	5850 2650 5950 2650
Wire Wire Line
	5950 2650 5950 3000
Wire Wire Line
	5950 3000 6500 3000
Wire Wire Line
	6500 3000 6500 3350
Wire Wire Line
	6500 3350 6400 3350
Wire Wire Line
	6450 3300 5900 3300
Wire Wire Line
	5900 3300 5900 3250
Connection ~ 6450 3250
Wire Wire Line
	2350 1750 2350 2050
Wire Wire Line
	2300 1450 4900 1450
$Comp
L R R4
U 1 1 5696397A
P 2500 1800
F 0 "R4" V 2580 1800 50  0000 C CNN
F 1 "R" V 2500 1800 50  0000 C CNN
F 2 "Discret:R4" V 2430 1800 50  0001 C CNN
F 3 "" H 2500 1800 50  0000 C CNN
	1    2500 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 1950 2500 2050
Connection ~ 2500 2050
Wire Wire Line
	2500 1650 2500 1450
Connection ~ 2500 1450
$Comp
L GND #PWR024
U 1 1 59327E72
P 3550 3250
F 0 "#PWR024" H 3550 3000 50  0001 C CNN
F 1 "GND" H 3550 3100 50  0000 C CNN
F 2 "" H 3550 3250 50  0000 C CNN
F 3 "" H 3550 3250 50  0000 C CNN
	1    3550 3250
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR025
U 1 1 59327E9E
P 3350 3250
F 0 "#PWR025" H 3350 3100 50  0001 C CNN
F 1 "VDD" H 3350 3400 50  0000 C CNN
F 2 "" H 3350 3250 50  0000 C CNN
F 3 "" H 3350 3250 50  0000 C CNN
	1    3350 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3450 3250 3350 3250
Wire Wire Line
	3550 3000 3550 3250
$Comp
L VDD #PWR026
U 1 1 593280EB
P 2300 1450
F 0 "#PWR026" H 2300 1300 50  0001 C CNN
F 1 "VDD" H 2300 1600 50  0000 C CNN
F 2 "" H 2300 1450 50  0000 C CNN
F 3 "" H 2300 1450 50  0000 C CNN
	1    2300 1450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR027
U 1 1 5932813E
P 1750 1900
F 0 "#PWR027" H 1750 1650 50  0001 C CNN
F 1 "GND" H 1750 1750 50  0000 C CNN
F 2 "" H 1750 1900 50  0000 C CNN
F 3 "" H 1750 1900 50  0000 C CNN
	1    1750 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 1850 1750 1900
$Comp
L GND #PWR028
U 1 1 59328247
P 2750 1650
F 0 "#PWR028" H 2750 1400 50  0001 C CNN
F 1 "GND" H 2750 1500 50  0000 C CNN
F 2 "" H 2750 1650 50  0000 C CNN
F 3 "" H 2750 1650 50  0000 C CNN
	1    2750 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 1650 2750 1650
Wire Wire Line
	4550 2800 4550 1450
Wire Wire Line
	6450 2550 6450 3300
$Comp
L GND #PWR029
U 1 1 59328486
P 6650 2550
F 0 "#PWR029" H 6650 2300 50  0001 C CNN
F 1 "GND" H 6650 2400 50  0000 C CNN
F 2 "" H 6650 2550 50  0000 C CNN
F 3 "" H 6650 2550 50  0000 C CNN
	1    6650 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 2550 6650 2550
$Comp
L Q_NPN_CBE Q3
U 1 1 59328675
P 4800 3000
F 0 "Q3" H 5100 3050 50  0000 R CNN
F 1 "Q_NPN_CBE" H 5400 2950 50  0000 R CNN
F 2 "TO_SOT_Packages_THT:TO-92_Inline_Narrow_Oval" H 5000 3100 50  0001 C CNN
F 3 "" H 4800 3000 50  0000 C CNN
	1    4800 3000
	1    0    0    -1  
$EndComp
$Comp
L Q_NPN_CBE Q1
U 1 1 593286E4
P 4800 1900
F 0 "Q1" H 5100 1950 50  0000 R CNN
F 1 "Q_NPN_CBE" H 5400 1850 50  0000 R CNN
F 2 "TO_SOT_Packages_THT:TO-92_Inline_Narrow_Oval" H 5000 2000 50  0001 C CNN
F 3 "" H 4800 1900 50  0000 C CNN
	1    4800 1900
	1    0    0    -1  
$EndComp
$Comp
L Q_NPN_CBE Q2
U 1 1 5932875D
P 4800 2450
F 0 "Q2" H 5100 2500 50  0000 R CNN
F 1 "Q_NPN_CBE" H 5400 2400 50  0000 R CNN
F 2 "TO_SOT_Packages_THT:TO-92_Inline_Narrow_Oval" H 5000 2550 50  0001 C CNN
F 3 "" H 4800 2450 50  0000 C CNN
	1    4800 2450
	1    0    0    -1  
$EndComp
$EndSCHEMATC
