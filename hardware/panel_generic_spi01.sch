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
Sheet 2 4
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
L 4051 MUX_ROW1
U 1 1 56895BF2
P 4200 2850
F 0 "MUX_ROW1" H 4300 2850 50  0000 C CNN
F 1 "4051" H 4300 2650 50  0000 C CNN
F 2 "Housings_DIP:DIP-16_W7.62mm_LongPads" H 4200 2850 60  0001 C CNN
F 3 "" H 4200 2850 60  0000 C CNN
	1    4200 2850
	-1   0    0    -1  
$EndComp
$Comp
L 4051 MUX_COL1
U 1 1 56895C86
P 7750 2850
F 0 "MUX_COL1" H 7850 2850 50  0000 C CNN
F 1 "4051" H 7850 2650 50  0000 C CNN
F 2 "Housings_DIP:DIP-16_W7.62mm_LongPads" H 7750 2850 60  0001 C CNN
F 3 "" H 7750 2850 60  0000 C CNN
	1    7750 2850
	1    0    0    -1  
$EndComp
$Comp
L 4024 U2
U 1 1 56896034
P 5250 4350
F 0 "U2" H 5450 4800 60  0000 C CNN
F 1 "4024" H 5650 3950 60  0000 C CNN
F 2 "Housings_DIP:DIP-14_W7.62mm_LongPads" H 5250 4350 60  0001 C CNN
F 3 "" H 5250 4350 60  0000 C CNN
	1    5250 4350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR8
U 1 1 56896772
P 7700 3650
F 0 "#PWR8" H 7700 3400 50  0001 C CNN
F 1 "GND" H 7700 3500 50  0000 C CNN
F 2 "" H 7700 3650 50  0000 C CNN
F 3 "" H 7700 3650 50  0000 C CNN
	1    7700 3650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR6
U 1 1 5689678D
P 4250 3650
F 0 "#PWR6" H 4250 3400 50  0001 C CNN
F 1 "GND" H 4250 3500 50  0000 C CNN
F 2 "" H 4250 3650 50  0000 C CNN
F 3 "" H 4250 3650 50  0000 C CNN
	1    4250 3650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR7
U 1 1 568967E3
P 5250 4700
F 0 "#PWR7" H 5250 4450 50  0001 C CNN
F 1 "GND" H 5250 4550 50  0000 C CNN
F 2 "" H 5250 4700 50  0000 C CNN
F 3 "" H 5250 4700 50  0000 C CNN
	1    5250 4700
	1    0    0    -1  
$EndComp
$Comp
L CONN_02X08 P4
U 1 1 5689688B
P 5950 2600
F 0 "P4" H 5950 3050 50  0000 C CNN
F 1 "CONN_02X08" V 5950 2600 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x08" H 5950 1400 50  0001 C CNN
F 3 "" H 5950 1400 50  0000 C CNN
	1    5950 2600
	1    0    0    1   
$EndComp
$Comp
L D D8
U 1 1 56896B3A
P 6050 2050
F 0 "D8" H 6050 2150 50  0000 C CNN
F 1 "D" H 6050 1950 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM15mm" H 6050 2050 50  0001 C CNN
F 3 "" H 6050 2050 50  0000 C CNN
	1    6050 2050
	1    0    0    -1  
$EndComp
$Comp
L D D1
U 1 1 56896BA9
P 6050 1350
F 0 "D1" H 6050 1450 50  0000 C CNN
F 1 "D" H 6050 1250 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM15mm" H 6050 1350 50  0001 C CNN
F 3 "" H 6050 1350 50  0000 C CNN
	1    6050 1350
	1    0    0    -1  
$EndComp
$Comp
L D D2
U 1 1 56896C1C
P 6050 1450
F 0 "D2" H 6050 1550 50  0000 C CNN
F 1 "D" H 6050 1350 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM15mm" H 6050 1450 50  0001 C CNN
F 3 "" H 6050 1450 50  0000 C CNN
	1    6050 1450
	1    0    0    -1  
$EndComp
$Comp
L D D3
U 1 1 56896C22
P 6050 1550
F 0 "D3" H 6050 1650 50  0000 C CNN
F 1 "D" H 6050 1450 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM15mm" H 6050 1550 50  0001 C CNN
F 3 "" H 6050 1550 50  0000 C CNN
	1    6050 1550
	1    0    0    -1  
$EndComp
$Comp
L D D4
U 1 1 56896D5A
P 6050 1650
F 0 "D4" H 6050 1750 50  0000 C CNN
F 1 "D" H 6050 1550 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM15mm" H 6050 1650 50  0001 C CNN
F 3 "" H 6050 1650 50  0000 C CNN
	1    6050 1650
	1    0    0    -1  
$EndComp
$Comp
L D D5
U 1 1 56896D60
P 6050 1750
F 0 "D5" H 6050 1850 50  0000 C CNN
F 1 "D" H 6050 1650 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM15mm" H 6050 1750 50  0001 C CNN
F 3 "" H 6050 1750 50  0000 C CNN
	1    6050 1750
	1    0    0    -1  
$EndComp
$Comp
L D D6
U 1 1 56896D66
P 6050 1850
F 0 "D6" H 6050 1950 50  0000 C CNN
F 1 "D" H 6050 1750 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM15mm" H 6050 1850 50  0001 C CNN
F 3 "" H 6050 1850 50  0000 C CNN
	1    6050 1850
	1    0    0    -1  
$EndComp
$Comp
L D D7
U 1 1 56896D6C
P 6050 1950
F 0 "D7" H 6050 2050 50  0000 C CNN
F 1 "D" H 6050 1850 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM15mm" H 6050 1950 50  0001 C CNN
F 3 "" H 6050 1950 50  0000 C CNN
	1    6050 1950
	1    0    0    -1  
$EndComp
$Comp
L CONN_02X07 PNL_ID1
U 1 1 56897052
P 5550 1650
F 0 "PNL_ID1" H 5550 2050 50  0000 C CNN
F 1 "CONN_02X07" V 5550 1650 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x07" H 5550 450 50  0001 C CNN
F 3 "" H 5550 450 50  0000 C CNN
	1    5550 1650
	1    0    0    -1  
$EndComp
$Comp
L CONN_02X03 P5
U 1 1 56897986
P 8100 1450
F 0 "P5" H 8100 1650 50  0000 C CNN
F 1 "CONN_02X03" H 8100 1250 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x03" H 8100 250 50  0001 C CNN
F 3 "" H 8100 250 50  0000 C CNN
	1    8100 1450
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR10
U 1 1 56897A47
P 8450 1250
F 0 "#PWR10" H 8450 1100 50  0001 C CNN
F 1 "VDD" H 8450 1400 50  0000 C CNN
F 2 "" H 8450 1250 50  0000 C CNN
F 3 "" H 8450 1250 50  0000 C CNN
	1    8450 1250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR9
U 1 1 56897BC9
P 7750 1650
F 0 "#PWR9" H 7750 1400 50  0001 C CNN
F 1 "GND" H 7750 1500 50  0000 C CNN
F 2 "" H 7750 1650 50  0000 C CNN
F 3 "" H 7750 1650 50  0000 C CNN
	1    7750 1650
	1    0    0    -1  
$EndComp
$Comp
L CONN_02X03 P3
U 1 1 56897D13
P 3850 1400
F 0 "P3" H 3850 1600 50  0000 C CNN
F 1 "CONN_02X03" H 3850 1200 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x03" H 3850 200 50  0001 C CNN
F 3 "" H 3850 200 50  0000 C CNN
	1    3850 1400
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR4
U 1 1 56897D19
P 4200 1200
F 0 "#PWR4" H 4200 1050 50  0001 C CNN
F 1 "VDD" H 4200 1350 50  0000 C CNN
F 2 "" H 4200 1200 50  0000 C CNN
F 3 "" H 4200 1200 50  0000 C CNN
	1    4200 1200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR3
U 1 1 56897D21
P 3500 1600
F 0 "#PWR3" H 3500 1350 50  0001 C CNN
F 1 "GND" H 3500 1450 50  0000 C CNN
F 2 "" H 3500 1600 50  0000 C CNN
F 3 "" H 3500 1600 50  0000 C CNN
	1    3500 1600
	1    0    0    -1  
$EndComp
Text HLabel 6050 3050 2    60   BiDi ~ 0
KSW_BUS
Text HLabel 3350 1300 0    60   Input ~ 0
PNL_BUS_IN
Text HLabel 8550 1350 2    60   Output ~ 0
PNL_BUS_OUT
$Comp
L 4053 U1
U 1 1 5689A5DE
P 4200 5750
F 0 "U1" H 4300 5750 50  0000 C CNN
F 1 "4053" H 4300 5550 50  0000 C CNN
F 2 "Housings_DIP:DIP-16_W7.62mm_LongPads" H 4200 5750 60  0001 C CNN
F 3 "" H 4200 5750 60  0000 C CNN
	1    4200 5750
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR5
U 1 1 5689B16D
P 4200 6550
F 0 "#PWR5" H 4200 6300 50  0001 C CNN
F 1 "GND" H 4200 6400 50  0000 C CNN
F 2 "" H 4200 6550 50  0000 C CNN
F 3 "" H 4200 6550 50  0000 C CNN
	1    4200 6550
	1    0    0    -1  
$EndComp
$Comp
L 4094N IC1
U 1 1 568AC82C
P 1900 3750
F 0 "IC1" H 1500 4375 50  0000 L BNN
F 1 "4094N" H 1500 3050 50  0000 L BNN
F 2 "Housings_DIP:DIP-16_W7.62mm_LongPads" H 1900 3900 50  0001 C CNN
F 3 "" H 1900 3750 60  0000 C CNN
	1    1900 3750
	-1   0    0    -1  
$EndComp
$Comp
L 4094N IC2
U 1 1 568ACD3D
P 1900 5250
F 0 "IC2" H 1500 5875 50  0000 L BNN
F 1 "4094N" H 1500 4550 50  0000 L BNN
F 2 "Housings_DIP:DIP-16_W7.62mm_LongPads" H 1900 5400 50  0001 C CNN
F 3 "" H 1900 5250 60  0000 C CNN
	1    1900 5250
	-1   0    0    -1  
$EndComp
$Comp
L VDD #PWR2
U 1 1 568AD8C3
P 2700 2750
F 0 "#PWR2" H 2700 2600 50  0001 C CNN
F 1 "VDD" H 2700 2900 50  0000 C CNN
F 2 "" H 2700 2750 50  0000 C CNN
F 3 "" H 2700 2750 50  0000 C CNN
	1    2700 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 4000 5800 3250
Wire Wire Line
	5800 3250 4900 3250
Wire Wire Line
	4900 3350 5900 3350
Wire Wire Line
	5900 3350 5900 4100
Wire Wire Line
	5900 4100 5800 4100
Wire Wire Line
	5800 4200 6000 4200
Wire Wire Line
	6000 4200 6000 3450
Wire Wire Line
	6000 3450 4900 3450
Wire Wire Line
	5800 4300 6100 4300
Wire Wire Line
	6100 4300 6100 3250
Wire Wire Line
	6100 3250 7050 3250
Wire Wire Line
	5800 4400 6200 4400
Wire Wire Line
	6200 4400 6200 3350
Wire Wire Line
	6200 3350 7050 3350
Wire Wire Line
	7050 3450 6300 3450
Wire Wire Line
	6300 3450 6300 4500
Wire Wire Line
	6300 4500 5800 4500
Wire Wire Line
	4900 3150 5000 3150
Wire Wire Line
	5000 3600 5000 3150
Wire Wire Line
	3500 3600 5000 3600
Wire Wire Line
	3500 2250 3500 3600
Wire Wire Line
	7050 3150 6950 3150
Wire Wire Line
	6950 3150 6950 3600
Wire Wire Line
	6950 3600 8450 3600
Wire Wire Line
	8450 3600 8450 3350
Wire Wire Line
	7700 3650 7700 3600
Connection ~ 7700 3600
Wire Wire Line
	4250 3650 4250 3600
Connection ~ 4250 3600
Wire Wire Line
	5250 4650 5250 4700
Connection ~ 3500 3350
Wire Wire Line
	4900 2250 5700 2250
Wire Wire Line
	4900 2350 5700 2350
Wire Wire Line
	4900 2450 5700 2450
Wire Wire Line
	4900 2550 5700 2550
Wire Wire Line
	4900 2650 5700 2650
Wire Wire Line
	4900 2750 5700 2750
Wire Wire Line
	4900 2850 5700 2850
Wire Wire Line
	6200 2250 7050 2250
Wire Wire Line
	6200 2350 7050 2350
Wire Wire Line
	6200 2450 7050 2450
Wire Wire Line
	6200 2550 7050 2550
Wire Wire Line
	6200 2650 7050 2650
Wire Wire Line
	6200 2750 7050 2750
Wire Wire Line
	6200 2850 7050 2850
Wire Wire Line
	6200 2950 7050 2950
Wire Wire Line
	5100 2950 4900 2950
Wire Wire Line
	5100 1450 5300 1450
Connection ~ 5100 1450
Connection ~ 5100 1550
Wire Wire Line
	5100 1550 5300 1550
Wire Wire Line
	5100 1650 5300 1650
Connection ~ 5100 1650
Wire Wire Line
	5100 1750 5300 1750
Connection ~ 5100 1750
Wire Wire Line
	5100 1850 5300 1850
Connection ~ 5100 1850
Wire Wire Line
	5100 1950 5300 1950
Connection ~ 5100 1950
Wire Wire Line
	5800 1350 5900 1350
Wire Wire Line
	5800 1450 5900 1450
Wire Wire Line
	5800 1550 5900 1550
Wire Wire Line
	5800 1650 5900 1650
Wire Wire Line
	5800 1750 5900 1750
Wire Wire Line
	5800 1850 5900 1850
Wire Wire Line
	5800 1950 5900 1950
Wire Wire Line
	8450 1250 8450 1350
Wire Wire Line
	8450 1350 8350 1350
Wire Wire Line
	7450 1550 7850 1550
Wire Wire Line
	7750 1550 7750 1650
Wire Wire Line
	4200 1200 4200 1300
Wire Wire Line
	4200 1300 4100 1300
Wire Wire Line
	3600 1500 3500 1500
Wire Wire Line
	3500 1500 3500 1600
Connection ~ 6350 2850
Connection ~ 6450 2750
Connection ~ 6550 2650
Connection ~ 6650 2550
Connection ~ 6750 2450
Connection ~ 6850 2350
Wire Wire Line
	6350 2850 6350 1950
Wire Wire Line
	6350 1950 6200 1950
Wire Wire Line
	6450 2750 6450 1850
Wire Wire Line
	6450 1850 6200 1850
Wire Wire Line
	6550 2650 6550 1750
Wire Wire Line
	6550 1750 6200 1750
Wire Wire Line
	6650 2550 6650 1650
Wire Wire Line
	6650 1650 6200 1650
Wire Wire Line
	6750 1550 6750 2450
Wire Wire Line
	6750 1550 6200 1550
Wire Wire Line
	6850 2350 6850 1450
Wire Wire Line
	6850 1450 6200 1450
Wire Wire Line
	6200 1350 6950 1350
Wire Wire Line
	6950 1350 6950 2250
Connection ~ 6950 2250
Wire Wire Line
	5100 1350 5100 2950
Wire Wire Line
	5100 1350 5300 1350
Wire Wire Line
	5900 2050 5100 2050
Connection ~ 5100 2050
Wire Wire Line
	6200 2050 6250 2050
Wire Wire Line
	6250 2050 6250 2950
Connection ~ 6250 2950
Wire Wire Line
	4100 1500 4200 1500
Wire Wire Line
	4200 1500 4200 1950
Wire Wire Line
	4200 1950 3350 1950
Wire Wire Line
	3350 1950 3350 5150
Wire Wire Line
	3600 1400 3250 1400
Wire Wire Line
	3250 950  3250 4300
Wire Wire Line
	3250 4300 4700 4300
Wire Wire Line
	3250 950  7750 950 
Wire Wire Line
	7750 950  7750 1450
Wire Wire Line
	7750 1450 7850 1450
Connection ~ 3250 1400
Wire Wire Line
	3350 5150 3500 5150
Wire Wire Line
	4900 5150 5000 5150
Wire Wire Line
	5000 4950 5000 5150
Wire Wire Line
	2500 4950 5000 4950
Wire Wire Line
	4600 4950 4600 4150
Wire Wire Line
	4600 4150 4700 4150
Wire Wire Line
	5800 4600 5900 4600
Wire Wire Line
	5900 4600 5900 6900
Wire Wire Line
	4900 6150 5900 6150
Wire Wire Line
	4900 6050 5050 6050
Wire Wire Line
	5050 6500 5050 6050
Wire Wire Line
	3500 6500 5050 6500
Wire Wire Line
	3500 6500 3500 6250
Wire Wire Line
	4200 6500 4200 6550
Connection ~ 4200 6500
Wire Wire Line
	4900 5250 8800 5250
Wire Wire Line
	8800 5250 8800 1550
Wire Wire Line
	8800 1550 8350 1550
Wire Wire Line
	4100 1400 4250 1400
Wire Wire Line
	4250 1400 4250 2000
Wire Wire Line
	4250 2000 3400 2000
Wire Wire Line
	3400 2000 3400 5450
Wire Wire Line
	3400 5450 3500 5450
Wire Wire Line
	4950 6150 4950 6250
Wire Wire Line
	4950 6250 4900 6250
Connection ~ 4950 6150
Wire Wire Line
	4900 5450 8600 5450
Wire Wire Line
	8600 5450 8600 2250
Wire Wire Line
	8600 2250 8450 2250
Wire Wire Line
	4900 5550 8900 5550
Wire Wire Line
	8900 5550 8900 1450
Wire Wire Line
	8900 1450 8350 1450
Wire Wire Line
	3600 1300 3600 850 
Wire Wire Line
	2800 850  7850 850 
Wire Wire Line
	7850 850  7850 1350
Wire Wire Line
	1400 4150 1300 4150
Wire Wire Line
	1300 4150 1300 4450
Wire Wire Line
	1300 4450 2550 4450
Wire Wire Line
	2550 4450 2550 4850
Wire Wire Line
	2550 4850 2500 4850
Connection ~ 4600 4950
Wire Wire Line
	2500 3450 3000 3450
Wire Wire Line
	3000 3450 3000 4950
Connection ~ 3000 4950
Wire Wire Line
	2900 6900 5900 6900
Wire Wire Line
	2900 3250 2900 6900
Wire Wire Line
	2900 3250 2500 3250
Connection ~ 5900 6150
Wire Wire Line
	2900 4750 2500 4750
Connection ~ 2900 4750
Wire Wire Line
	2800 850  2800 3350
Wire Wire Line
	2800 3350 2500 3350
Connection ~ 3600 850 
Wire Wire Line
	2700 2750 2700 5050
Wire Wire Line
	2700 3550 2500 3550
Wire Wire Line
	2700 5050 2500 5050
Connection ~ 2700 3550
$Comp
L CONN_02X10 P6
U 1 1 568AE13A
P 900 3600
F 0 "P6" H 900 4150 50  0000 C CNN
F 1 "CONN_02X10" V 900 3600 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x10" H 900 2400 50  0001 C CNN
F 3 "" H 900 2400 50  0000 C CNN
	1    900  3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	650  2900 2700 2900
Wire Wire Line
	650  2900 650  3150
Connection ~ 2700 2900
Wire Wire Line
	1400 3250 1150 3250
Wire Wire Line
	1400 3350 1150 3350
Wire Wire Line
	1400 3450 1150 3450
Wire Wire Line
	1400 3550 1150 3550
Wire Wire Line
	1400 3650 1150 3650
Wire Wire Line
	1400 3750 1150 3750
Wire Wire Line
	1400 3850 1150 3850
Wire Wire Line
	1400 3950 1150 3950
Wire Wire Line
	1150 4050 1300 4050
Wire Wire Line
	1300 4050 1300 2900
Connection ~ 1300 2900
Wire Wire Line
	600  4750 1400 4750
Wire Wire Line
	650  3950 600  3950
Wire Wire Line
	550  4850 1400 4850
Wire Wire Line
	650  3850 550  3850
Wire Wire Line
	500  4950 1400 4950
Wire Wire Line
	650  3750 500  3750
Wire Wire Line
	450  5050 1400 5050
Wire Wire Line
	650  3650 450  3650
Wire Wire Line
	400  5150 1400 5150
Wire Wire Line
	650  3550 400  3550
Wire Wire Line
	350  5250 1400 5250
Wire Wire Line
	650  3450 350  3450
Wire Wire Line
	300  5350 1400 5350
Wire Wire Line
	600  3950 600  4750
Wire Wire Line
	550  3850 550  4850
Wire Wire Line
	500  3750 500  4950
Wire Wire Line
	450  3650 450  5050
Wire Wire Line
	400  3550 400  5150
Wire Wire Line
	350  3450 350  5250
Wire Wire Line
	650  3350 300  3350
Wire Wire Line
	300  3350 300  5350
Wire Wire Line
	650  3250 250  3250
Wire Wire Line
	250  3250 250  5450
Wire Wire Line
	250  5450 1400 5450
$Comp
L GND #PWR1
U 1 1 568AFDDA
P 950 4500
F 0 "#PWR1" H 950 4250 50  0001 C CNN
F 1 "GND" H 950 4350 50  0000 C CNN
F 2 "" H 950 4500 50  0000 C CNN
F 3 "" H 950 4500 50  0000 C CNN
	1    950  4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	650  4050 650  4500
Wire Wire Line
	650  4500 2600 4500
Wire Wire Line
	1200 4500 1200 3150
Wire Wire Line
	1200 3150 1150 3150
Connection ~ 950  4500
$Comp
L 4094N IC1
U 2 1 568B55D1
P 2400 4000
F 0 "IC1" H 2000 4625 50  0000 L BNN
F 1 "4094N" H 2000 3300 50  0000 L BNN
F 2 "40xx-DIL16" H 2400 4150 50  0001 C CNN
F 3 "" H 2400 4000 60  0000 C CNN
	2    2400 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 4500 2400 4300
Connection ~ 1200 4500
Wire Wire Line
	2400 2900 2400 3700
Connection ~ 2400 2900
$Comp
L 4094N IC2
U 2 1 568B61D6
P 2600 4000
F 0 "IC2" H 2200 4625 50  0000 L BNN
F 1 "4094N" H 2200 3300 50  0000 L BNN
F 2 "40xx-DIL16" H 2600 4150 50  0001 C CNN
F 3 "" H 2600 4000 60  0000 C CNN
	2    2600 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 2900 2600 3700
Connection ~ 2600 2900
Wire Wire Line
	2600 4500 2600 4300
Connection ~ 2400 4500
$Comp
L VDD #PWR?
U 1 1 568B704F
P 5250 3900
F 0 "#PWR?" H 5250 3750 50  0001 C CNN
F 1 "VDD" H 5250 4050 50  0000 C CNN
F 2 "" H 5250 3900 50  0000 C CNN
F 3 "" H 5250 3900 50  0000 C CNN
	1    5250 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 3900 5250 3950
$Comp
L VSS #PWR?
U 1 1 568B78AE
P 7450 1550
F 0 "#PWR?" H 7450 1400 50  0001 C CNN
F 1 "VSS" H 7450 1700 50  0000 C CNN
F 2 "" H 7450 1550 50  0000 C CNN
F 3 "" H 7450 1550 50  0000 C CNN
	1    7450 1550
	1    0    0    -1  
$EndComp
Connection ~ 7750 1550
$EndSCHEMATC
