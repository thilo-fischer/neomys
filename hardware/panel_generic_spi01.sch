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
Sheet 4 11
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
AR Path="/56894D4D/56895BF2" Ref="MUX_ROW1"  Part="1" 
AR Path="/568E4808/56895BF2" Ref="MUX_ROW1"  Part="1" 
F 0 "MUX_ROW1" H 4300 2850 50  0000 C CNN
F 1 "4051" H 4300 2650 50  0000 C CNN
F 2 "Housings_SSOP:SOP-16_4.4x10.4mm_Pitch1.27mm" H 4200 2850 60  0001 C CNN
F 3 "" H 4200 2850 60  0000 C CNN
	1    4200 2850
	-1   0    0    -1  
$EndComp
$Comp
L 4051 MUX_COL1
U 1 1 56895C86
P 7750 2850
AR Path="/56894D4D/56895C86" Ref="MUX_COL1"  Part="1" 
AR Path="/568E4808/56895C86" Ref="MUX_COL1"  Part="1" 
F 0 "MUX_COL1" H 7850 2850 50  0000 C CNN
F 1 "4051" H 7850 2650 50  0000 C CNN
F 2 "Housings_SSOP:SOP-16_4.4x10.4mm_Pitch1.27mm" H 7750 2850 60  0001 C CNN
F 3 "" H 7750 2850 60  0000 C CNN
	1    7750 2850
	1    0    0    -1  
$EndComp
$Comp
L 4024 U2
U 1 1 56896034
P 5250 4350
AR Path="/56894D4D/56896034" Ref="U2"  Part="1" 
AR Path="/568E4808/56896034" Ref="U2"  Part="1" 
F 0 "U2" H 5450 4800 60  0000 C CNN
F 1 "4024" H 5650 3950 60  0000 C CNN
F 2 "Housings_SOIC:SOIC-14_3.9x8.7mm_Pitch1.27mm" H 5250 4350 60  0001 C CNN
F 3 "" H 5250 4350 60  0000 C CNN
	1    5250 4350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR10
U 1 1 56896772
P 7700 3650
AR Path="/56894D4D/56896772" Ref="#PWR10"  Part="1" 
AR Path="/568E4808/56896772" Ref="#PWR01"  Part="1" 
F 0 "#PWR01" H 7700 3400 50  0001 C CNN
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
AR Path="/56894D4D/5689678D" Ref="#PWR6"  Part="1" 
AR Path="/568E4808/5689678D" Ref="#PWR02"  Part="1" 
F 0 "#PWR02" H 4250 3400 50  0001 C CNN
F 1 "GND" H 4250 3500 50  0000 C CNN
F 2 "" H 4250 3650 50  0000 C CNN
F 3 "" H 4250 3650 50  0000 C CNN
	1    4250 3650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR8
U 1 1 568967E3
P 5250 4700
AR Path="/56894D4D/568967E3" Ref="#PWR8"  Part="1" 
AR Path="/568E4808/568967E3" Ref="#PWR03"  Part="1" 
F 0 "#PWR03" H 5250 4450 50  0001 C CNN
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
AR Path="/56894D4D/5689688B" Ref="P4"  Part="1" 
AR Path="/568E4808/5689688B" Ref="P4"  Part="1" 
F 0 "P4" H 5950 3050 50  0000 C CNN
F 1 "CONN_02X08" V 5950 2600 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x08_Pitch2.54mm" H 5950 1400 50  0001 C CNN
F 3 "" H 5950 1400 50  0000 C CNN
	1    5950 2600
	-1   0    0    -1  
$EndComp
$Comp
L D D8
U 1 1 56896B3A
P 6050 2050
AR Path="/56894D4D/56896B3A" Ref="D8"  Part="1" 
AR Path="/568E4808/56896B3A" Ref="D8"  Part="1" 
F 0 "D8" H 6050 2150 50  0000 C CNN
F 1 "D" H 6050 1950 50  0000 C CNN
F 2 "Discret:D5" H 6050 2050 50  0001 C CNN
F 3 "" H 6050 2050 50  0000 C CNN
	1    6050 2050
	1    0    0    -1  
$EndComp
$Comp
L D D1
U 1 1 56896BA9
P 6050 1350
AR Path="/56894D4D/56896BA9" Ref="D1"  Part="1" 
AR Path="/568E4808/56896BA9" Ref="D1"  Part="1" 
F 0 "D1" H 6050 1450 50  0000 C CNN
F 1 "D" H 6050 1250 50  0000 C CNN
F 2 "Discret:D3" H 6050 1350 50  0001 C CNN
F 3 "" H 6050 1350 50  0000 C CNN
	1    6050 1350
	1    0    0    -1  
$EndComp
$Comp
L D D2
U 1 1 56896C1C
P 6050 1450
AR Path="/56894D4D/56896C1C" Ref="D2"  Part="1" 
AR Path="/568E4808/56896C1C" Ref="D2"  Part="1" 
F 0 "D2" H 6050 1550 50  0000 C CNN
F 1 "D" H 6050 1350 50  0000 C CNN
F 2 "Discret:D3" H 6050 1450 50  0001 C CNN
F 3 "" H 6050 1450 50  0000 C CNN
	1    6050 1450
	1    0    0    -1  
$EndComp
$Comp
L D D3
U 1 1 56896C22
P 6050 1550
AR Path="/56894D4D/56896C22" Ref="D3"  Part="1" 
AR Path="/568E4808/56896C22" Ref="D3"  Part="1" 
F 0 "D3" H 6050 1650 50  0000 C CNN
F 1 "D" H 6050 1450 50  0000 C CNN
F 2 "Discret:D3" H 6050 1550 50  0001 C CNN
F 3 "" H 6050 1550 50  0000 C CNN
	1    6050 1550
	1    0    0    -1  
$EndComp
$Comp
L D D4
U 1 1 56896D5A
P 6050 1650
AR Path="/56894D4D/56896D5A" Ref="D4"  Part="1" 
AR Path="/568E4808/56896D5A" Ref="D4"  Part="1" 
F 0 "D4" H 6050 1750 50  0000 C CNN
F 1 "D" H 6050 1550 50  0000 C CNN
F 2 "Discret:D3" H 6050 1650 50  0001 C CNN
F 3 "" H 6050 1650 50  0000 C CNN
	1    6050 1650
	1    0    0    -1  
$EndComp
$Comp
L D D5
U 1 1 56896D60
P 6050 1750
AR Path="/56894D4D/56896D60" Ref="D5"  Part="1" 
AR Path="/568E4808/56896D60" Ref="D5"  Part="1" 
F 0 "D5" H 6050 1850 50  0000 C CNN
F 1 "D" H 6050 1650 50  0000 C CNN
F 2 "Discret:D3" H 6050 1750 50  0001 C CNN
F 3 "" H 6050 1750 50  0000 C CNN
	1    6050 1750
	1    0    0    -1  
$EndComp
$Comp
L D D6
U 1 1 56896D66
P 6050 1850
AR Path="/56894D4D/56896D66" Ref="D6"  Part="1" 
AR Path="/568E4808/56896D66" Ref="D6"  Part="1" 
F 0 "D6" H 6050 1950 50  0000 C CNN
F 1 "D" H 6050 1750 50  0000 C CNN
F 2 "Discret:D3" H 6050 1850 50  0001 C CNN
F 3 "" H 6050 1850 50  0000 C CNN
	1    6050 1850
	1    0    0    -1  
$EndComp
$Comp
L D D7
U 1 1 56896D6C
P 6050 1950
AR Path="/56894D4D/56896D6C" Ref="D7"  Part="1" 
AR Path="/568E4808/56896D6C" Ref="D7"  Part="1" 
F 0 "D7" H 6050 2050 50  0000 C CNN
F 1 "D" H 6050 1850 50  0000 C CNN
F 2 "Discret:D3" H 6050 1950 50  0001 C CNN
F 3 "" H 6050 1950 50  0000 C CNN
	1    6050 1950
	1    0    0    -1  
$EndComp
$Comp
L CONN_02X07 PNL_ID1
U 1 1 56897052
P 5450 1650
AR Path="/56894D4D/56897052" Ref="PNL_ID1"  Part="1" 
AR Path="/568E4808/56897052" Ref="PNL_ID1"  Part="1" 
F 0 "PNL_ID1" H 5450 2050 50  0000 C CNN
F 1 "CONN_02X07" V 5450 1650 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x07_Pitch2.54mm" H 5450 450 50  0001 C CNN
F 3 "" H 5450 450 50  0000 C CNN
	1    5450 1650
	1    0    0    -1  
$EndComp
$Comp
L CONN_02X03 P5
U 1 1 56897986
P 8100 1650
AR Path="/56894D4D/56897986" Ref="P5"  Part="1" 
AR Path="/568E4808/56897986" Ref="P5"  Part="1" 
F 0 "P5" H 8100 1850 50  0000 C CNN
F 1 "CONN_02X03" H 8100 1450 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x03_Pitch2.54mm" H 8100 450 50  0001 C CNN
F 3 "" H 8100 450 50  0000 C CNN
	1    8100 1650
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR12
U 1 1 56897A47
P 8450 1550
AR Path="/56894D4D/56897A47" Ref="#PWR12"  Part="1" 
AR Path="/568E4808/56897A47" Ref="#PWR04"  Part="1" 
F 0 "#PWR04" H 8450 1400 50  0001 C CNN
F 1 "VDD" H 8450 1700 50  0000 C CNN
F 2 "" H 8450 1550 50  0000 C CNN
F 3 "" H 8450 1550 50  0000 C CNN
	1    8450 1550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR11
U 1 1 56897BC9
P 7750 1850
AR Path="/56894D4D/56897BC9" Ref="#PWR11"  Part="1" 
AR Path="/568E4808/56897BC9" Ref="#PWR05"  Part="1" 
F 0 "#PWR05" H 7750 1600 50  0001 C CNN
F 1 "GND" H 7750 1700 50  0000 C CNN
F 2 "" H 7750 1850 50  0000 C CNN
F 3 "" H 7750 1850 50  0000 C CNN
	1    7750 1850
	1    0    0    -1  
$EndComp
$Comp
L CONN_02X03 P3
U 1 1 56897D13
P 3850 1600
AR Path="/56894D4D/56897D13" Ref="P3"  Part="1" 
AR Path="/568E4808/56897D13" Ref="P3"  Part="1" 
F 0 "P3" H 3850 1800 50  0000 C CNN
F 1 "CONN_02X03" H 3850 1400 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x03_Pitch2.54mm" H 3850 400 50  0001 C CNN
F 3 "" H 3850 400 50  0000 C CNN
	1    3850 1600
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR4
U 1 1 56897D19
P 4150 1500
AR Path="/56894D4D/56897D19" Ref="#PWR4"  Part="1" 
AR Path="/568E4808/56897D19" Ref="#PWR06"  Part="1" 
F 0 "#PWR06" H 4150 1350 50  0001 C CNN
F 1 "VDD" H 4150 1650 50  0000 C CNN
F 2 "" H 4150 1500 50  0000 C CNN
F 3 "" H 4150 1500 50  0000 C CNN
	1    4150 1500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR3
U 1 1 56897D21
P 3500 1800
AR Path="/56894D4D/56897D21" Ref="#PWR3"  Part="1" 
AR Path="/568E4808/56897D21" Ref="#PWR07"  Part="1" 
F 0 "#PWR07" H 3500 1550 50  0001 C CNN
F 1 "GND" H 3500 1650 50  0000 C CNN
F 2 "" H 3500 1800 50  0000 C CNN
F 3 "" H 3500 1800 50  0000 C CNN
	1    3500 1800
	1    0    0    -1  
$EndComp
Text HLabel 6050 3050 2    60   BiDi ~ 0
KSW_BUS
Text HLabel 3350 1500 0    60   Input ~ 0
PNL_BUS_IN
Text HLabel 8550 1550 2    60   Output ~ 0
PNL_BUS_OUT
$Comp
L 4053 U1
U 1 1 5689A5DE
P 4200 5750
AR Path="/56894D4D/5689A5DE" Ref="U1"  Part="1" 
AR Path="/568E4808/5689A5DE" Ref="U1"  Part="1" 
F 0 "U1" H 4300 5750 50  0000 C CNN
F 1 "4053" H 4300 5550 50  0000 C CNN
F 2 "Housings_SSOP:SOP-16_4.4x10.4mm_Pitch1.27mm" H 4200 5750 60  0001 C CNN
F 3 "" H 4200 5750 60  0000 C CNN
	1    4200 5750
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR5
U 1 1 5689B16D
P 4200 6550
AR Path="/56894D4D/5689B16D" Ref="#PWR5"  Part="1" 
AR Path="/568E4808/5689B16D" Ref="#PWR08"  Part="1" 
F 0 "#PWR08" H 4200 6300 50  0001 C CNN
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
AR Path="/56894D4D/568AC82C" Ref="IC1"  Part="1" 
AR Path="/568E4808/568AC82C" Ref="IC1"  Part="1" 
F 0 "IC1" H 1500 4375 50  0000 L BNN
F 1 "4094N" H 1500 3050 50  0000 L BNN
F 2 "Housings_SSOP:SOP-16_4.4x10.4mm_Pitch1.27mm" H 1900 3900 50  0001 C CNN
F 3 "" H 1900 3750 60  0000 C CNN
	1    1900 3750
	-1   0    0    -1  
$EndComp
$Comp
L 4094N IC2
U 1 1 568ACD3D
P 1900 5250
AR Path="/56894D4D/568ACD3D" Ref="IC2"  Part="1" 
AR Path="/568E4808/568ACD3D" Ref="IC2"  Part="1" 
F 0 "IC2" H 1500 5875 50  0000 L BNN
F 1 "4094N" H 1500 4550 50  0000 L BNN
F 2 "Housings_SSOP:SOP-16_4.4x10.4mm_Pitch1.27mm" H 1900 5400 50  0001 C CNN
F 3 "" H 1900 5250 60  0000 C CNN
	1    1900 5250
	-1   0    0    -1  
$EndComp
$Comp
L VDD #PWR2
U 1 1 568AD8C3
P 2700 2750
AR Path="/56894D4D/568AD8C3" Ref="#PWR2"  Part="1" 
AR Path="/568E4808/568AD8C3" Ref="#PWR09"  Part="1" 
F 0 "#PWR09" H 2700 2600 50  0001 C CNN
F 1 "VDD" H 2700 2900 50  0000 C CNN
F 2 "" H 2700 2750 50  0000 C CNN
F 3 "" H 2700 2750 50  0000 C CNN
	1    2700 2750
	1    0    0    -1  
$EndComp
$Comp
L CONN_02X10 P6
U 1 1 568AE13A
P 900 3600
AR Path="/56894D4D/568AE13A" Ref="P6"  Part="1" 
AR Path="/568E4808/568AE13A" Ref="P6"  Part="1" 
F 0 "P6" H 900 4150 50  0000 C CNN
F 1 "CONN_02X10" V 900 3600 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x10_Pitch2.54mm" H 900 2400 50  0001 C CNN
F 3 "" H 900 2400 50  0000 C CNN
	1    900  3600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR1
U 1 1 568AFDDA
P 950 4500
AR Path="/56894D4D/568AFDDA" Ref="#PWR1"  Part="1" 
AR Path="/568E4808/568AFDDA" Ref="#PWR010"  Part="1" 
F 0 "#PWR010" H 950 4250 50  0001 C CNN
F 1 "GND" H 950 4350 50  0000 C CNN
F 2 "" H 950 4500 50  0000 C CNN
F 3 "" H 950 4500 50  0000 C CNN
	1    950  4500
	1    0    0    -1  
$EndComp
$Comp
L 4094N IC1
U 2 1 568B55D1
P 2400 4000
AR Path="/56894D4D/568B55D1" Ref="IC1"  Part="2" 
AR Path="/568E4808/568B55D1" Ref="IC1"  Part="2" 
F 0 "IC1" H 2000 4625 50  0000 L BNN
F 1 "4094N" H 2000 3300 50  0000 L BNN
F 2 "Housings_SSOP:SOP-16_4.4x10.4mm_Pitch1.27mm" H 2400 4150 50  0001 C CNN
F 3 "" H 2400 4000 60  0000 C CNN
	2    2400 4000
	1    0    0    -1  
$EndComp
$Comp
L 4094N IC2
U 2 1 568B61D6
P 2600 4000
AR Path="/56894D4D/568B61D6" Ref="IC2"  Part="2" 
AR Path="/568E4808/568B61D6" Ref="IC2"  Part="2" 
F 0 "IC2" H 2200 4625 50  0000 L BNN
F 1 "4094N" H 2200 3300 50  0000 L BNN
F 2 "Housings_SSOP:SOP-16_4.4x10.4mm_Pitch1.27mm" H 2600 4150 50  0001 C CNN
F 3 "" H 2600 4000 60  0000 C CNN
	2    2600 4000
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR7
U 1 1 568B704F
P 5250 3900
AR Path="/56894D4D/568B704F" Ref="#PWR7"  Part="1" 
AR Path="/568E4808/568B704F" Ref="#PWR011"  Part="1" 
F 0 "#PWR011" H 5250 3750 50  0001 C CNN
F 1 "VDD" H 5250 4050 50  0000 C CNN
F 2 "" H 5250 3900 50  0000 C CNN
F 3 "" H 5250 3900 50  0000 C CNN
	1    5250 3900
	1    0    0    -1  
$EndComp
$Comp
L VSS #PWR9
U 1 1 568B78AE
P 7450 1750
AR Path="/56894D4D/568B78AE" Ref="#PWR9"  Part="1" 
AR Path="/568E4808/568B78AE" Ref="#PWR012"  Part="1" 
F 0 "#PWR012" H 7450 1600 50  0001 C CNN
F 1 "VSS" H 7450 1900 50  0000 C CNN
F 2 "" H 7450 1750 50  0000 C CNN
F 3 "" H 7450 1750 50  0000 C CNN
	1    7450 1750
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR013
U 1 1 592913AA
P 10000 1050
F 0 "#PWR013" H 10000 900 50  0001 C CNN
F 1 "VDD" H 10000 1200 50  0000 C CNN
F 2 "" H 10000 1050 50  0000 C CNN
F 3 "" H 10000 1050 50  0000 C CNN
	1    10000 1050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR014
U 1 1 592913E8
P 10000 1550
F 0 "#PWR014" H 10000 1300 50  0001 C CNN
F 1 "GND" H 10000 1400 50  0000 C CNN
F 2 "" H 10000 1550 50  0000 C CNN
F 3 "" H 10000 1550 50  0000 C CNN
	1    10000 1550
	1    0    0    -1  
$EndComp
$Comp
L C C5
U 1 1 5929143B
P 10100 1300
F 0 "C5" H 10125 1400 50  0000 L CNN
F 1 "100nF" H 10125 1200 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Disc_D5.0mm_W2.5mm_P2.50mm" H 10138 1150 50  0001 C CNN
F 3 "" H 10100 1300 50  0000 C CNN
	1    10100 1300
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 5929150F
P 9900 1300
F 0 "C4" H 9925 1400 50  0000 L CNN
F 1 "100nF" H 9925 1200 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Disc_D5.0mm_W2.5mm_P2.50mm" H 9938 1150 50  0001 C CNN
F 3 "" H 9900 1300 50  0000 C CNN
	1    9900 1300
	1    0    0    -1  
$EndComp
$Comp
L C C7
U 1 1 592915DD
P 10500 1300
F 0 "C7" H 10525 1400 50  0000 L CNN
F 1 "100nF" H 10525 1200 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Disc_D5.0mm_W2.5mm_P2.50mm" H 10538 1150 50  0001 C CNN
F 3 "" H 10500 1300 50  0000 C CNN
	1    10500 1300
	1    0    0    -1  
$EndComp
$Comp
L C C6
U 1 1 592915E3
P 10300 1300
F 0 "C6" H 10325 1400 50  0000 L CNN
F 1 "100nF" H 10325 1200 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Disc_D5.0mm_W2.5mm_P2.50mm" H 10338 1150 50  0001 C CNN
F 3 "" H 10300 1300 50  0000 C CNN
	1    10300 1300
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 5929169D
P 9700 1300
F 0 "C3" H 9725 1400 50  0000 L CNN
F 1 "100nF" H 9725 1200 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Disc_D5.0mm_W2.5mm_P2.50mm" H 9738 1150 50  0001 C CNN
F 3 "" H 9700 1300 50  0000 C CNN
	1    9700 1300
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 592916A3
P 9500 1300
F 0 "C2" H 9525 1400 50  0000 L CNN
F 1 "100nF" H 9525 1200 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Disc_D5.0mm_W2.5mm_P5.00mm" H 9538 1150 50  0001 C CNN
F 3 "" H 9500 1300 50  0000 C CNN
	1    9500 1300
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 59291E0A
P 4750 1750
F 0 "C1" H 4775 1850 50  0000 L CNN
F 1 "1uF" H 4775 1650 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Disc_D5.0mm_W2.5mm_P2.50mm" H 4788 1600 50  0001 C CNN
F 3 "" H 4750 1750 50  0000 C CNN
	1    4750 1750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR015
U 1 1 59295156
P 5700 3150
F 0 "#PWR015" H 5700 2900 50  0001 C CNN
F 1 "GND" H 5700 3000 50  0000 C CNN
F 2 "" H 5700 3150 50  0000 C CNN
F 3 "" H 5700 3150 50  0000 C CNN
	1    5700 3150
	1    0    0    -1  
$EndComp
$Comp
L RJ45 J1
U 1 1 592AED5A
P 4350 650
F 0 "J1" H 4550 1150 50  0000 C CNN
F 1 "RJ45" H 4200 1150 50  0000 C CNN
F 2 "custom_footprints:RJ45_8G" H 4350 650 50  0001 C CNN
F 3 "" H 4350 650 50  0000 C CNN
	1    4350 650 
	1    0    0    -1  
$EndComp
$Comp
L RJ45 J2
U 1 1 592AEE2D
P 8150 750
F 0 "J2" H 8350 1250 50  0000 C CNN
F 1 "RJ45" H 8000 1250 50  0000 C CNN
F 2 "custom_footprints:RJ45_8G" H 8150 750 50  0001 C CNN
F 3 "" H 8150 750 50  0000 C CNN
	1    8150 750 
	1    0    0    -1  
$EndComp
Text Label 3600 1400 0    60   ~ 0
reset
Text Label 4100 1700 0    60   ~ 0
clock
Text Label 3400 1600 0    60   ~ 0
mosi
Text Label 4100 1600 0    60   ~ 0
miso
$Comp
L GND #PWR016
U 1 1 592B2172
P 3850 1150
F 0 "#PWR016" H 3850 900 50  0001 C CNN
F 1 "GND" H 3850 1000 50  0000 C CNN
F 2 "" H 3850 1150 50  0000 C CNN
F 3 "" H 3850 1150 50  0000 C CNN
	1    3850 1150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR017
U 1 1 592B2DC8
P 4750 1900
F 0 "#PWR017" H 4750 1650 50  0001 C CNN
F 1 "GND" H 4750 1750 50  0000 C CNN
F 2 "" H 4750 1900 50  0000 C CNN
F 3 "" H 4750 1900 50  0000 C CNN
	1    4750 1900
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR018
U 1 1 592B2E39
P 4900 1200
F 0 "#PWR018" H 4900 1050 50  0001 C CNN
F 1 "VDD" H 4900 1350 50  0000 C CNN
F 2 "" H 4900 1200 50  0000 C CNN
F 3 "" H 4900 1200 50  0000 C CNN
	1    4900 1200
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR019
U 1 1 592B37CE
P 4750 1600
F 0 "#PWR019" H 4750 1450 50  0001 C CNN
F 1 "VDD" H 4750 1750 50  0000 C CNN
F 2 "" H 4750 1600 50  0000 C CNN
F 3 "" H 4750 1600 50  0000 C CNN
	1    4750 1600
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR020
U 1 1 592B4764
P 8700 1300
F 0 "#PWR020" H 8700 1150 50  0001 C CNN
F 1 "VDD" H 8700 1450 50  0000 C CNN
F 2 "" H 8700 1300 50  0000 C CNN
F 3 "" H 8700 1300 50  0000 C CNN
	1    8700 1300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR021
U 1 1 592B4ABD
P 7450 1300
F 0 "#PWR021" H 7450 1050 50  0001 C CNN
F 1 "GND" H 7450 1150 50  0000 C CNN
F 2 "" H 7450 1300 50  0000 C CNN
F 3 "" H 7450 1300 50  0000 C CNN
	1    7450 1300
	1    0    0    -1  
$EndComp
Text Notes 2400 1650 0    60   ~ 0
Connect Master here
Text Notes 9000 1700 0    60   ~ 0
Connect Slave here
$Comp
L GND #PWR022
U 1 1 59347FF4
P 8700 400
F 0 "#PWR022" H 8700 150 50  0001 C CNN
F 1 "GND" H 8700 250 50  0000 C CNN
F 2 "" H 8700 400 50  0000 C CNN
F 3 "" H 8700 400 50  0000 C CNN
	1    8700 400 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR023
U 1 1 5934807B
P 4900 300
F 0 "#PWR023" H 4900 50  50  0001 C CNN
F 1 "GND" H 4900 150 50  0000 C CNN
F 2 "" H 4900 300 50  0000 C CNN
F 3 "" H 4900 300 50  0000 C CNN
	1    4900 300 
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 3250 5900 3500
Wire Wire Line
	4900 3350 6000 3600
Wire Wire Line
	5800 4100 6300 4100
Wire Wire Line
	5800 4200 6400 4200
Wire Wire Line
	4900 3450 6100 3700
Wire Wire Line
	4900 3150 4950 3150
Wire Wire Line
	4950 3150 4950 3600
Wire Wire Line
	4950 3600 3500 3600
Wire Wire Line
	3500 3600 3500 2250
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
	4950 2950 4900 2950
Wire Wire Line
	4950 1450 5200 1450
Connection ~ 4950 1450
Connection ~ 4950 1550
Wire Wire Line
	4950 1550 5200 1550
Wire Wire Line
	4950 1650 5200 1650
Connection ~ 4950 1650
Wire Wire Line
	4950 1750 5200 1750
Connection ~ 4950 1750
Wire Wire Line
	4950 1850 5200 1850
Connection ~ 4950 1850
Wire Wire Line
	4950 1950 5200 1950
Connection ~ 4950 1950
Wire Wire Line
	5700 1350 5900 1350
Wire Wire Line
	5700 1450 5900 1450
Wire Wire Line
	5700 1550 5900 1550
Wire Wire Line
	5700 1650 5900 1650
Wire Wire Line
	5700 1750 5900 1750
Wire Wire Line
	5700 1850 5900 1850
Wire Wire Line
	5700 1950 5900 1950
Wire Wire Line
	8350 1550 8450 1550
Wire Wire Line
	7450 1750 7850 1750
Wire Wire Line
	7750 1750 7750 1850
Wire Wire Line
	3600 1700 3500 1700
Wire Wire Line
	3500 1700 3500 1800
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
	4950 1350 4950 2950
Wire Wire Line
	4950 1350 5200 1350
Wire Wire Line
	5900 2050 4950 2050
Connection ~ 4950 2050
Wire Wire Line
	6200 2050 6250 2050
Wire Wire Line
	6250 2050 6250 2950
Connection ~ 6250 2950
Wire Wire Line
	4100 1700 4200 1700
Wire Wire Line
	4200 1200 4200 2050
Wire Wire Line
	4200 2050 3350 2050
Wire Wire Line
	3350 2050 3350 5150
Wire Wire Line
	3250 4300 4700 4300
Wire Wire Line
	7550 850  7550 1650
Wire Wire Line
	7550 1650 7850 1650
Wire Wire Line
	3350 5150 3500 5150
Wire Wire Line
	4900 5150 5000 5150
Wire Wire Line
	5000 5150 5000 4950
Wire Wire Line
	5000 4950 2500 4950
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
	5050 6050 5050 6500
Wire Wire Line
	5050 6500 3500 6500
Wire Wire Line
	3500 6500 3500 6250
Wire Wire Line
	4200 6500 4200 6550
Connection ~ 4200 6500
Wire Wire Line
	4900 5250 8800 5250
Wire Wire Line
	8800 5250 8800 1750
Wire Wire Line
	8800 1750 8350 1750
Wire Wire Line
	4300 1100 4300 2100
Wire Wire Line
	4300 2100 3400 2100
Wire Wire Line
	3400 2100 3400 5450
Wire Wire Line
	3400 5450 3500 5450
Wire Wire Line
	4950 6150 4950 6350
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
	8900 5550 8900 1650
Wire Wire Line
	8900 1650 8350 1650
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
	5900 6900 2900 6900
Wire Wire Line
	2900 6900 2900 3250
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
Wire Wire Line
	2700 2750 2700 5050
Wire Wire Line
	2700 3550 2500 3550
Wire Wire Line
	2700 5050 2500 5050
Connection ~ 2700 3550
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
Wire Wire Line
	650  4050 650  4500
Wire Wire Line
	650  4500 2600 4500
Wire Wire Line
	1200 4500 1200 3150
Wire Wire Line
	1200 3150 1150 3150
Connection ~ 950  4500
Wire Wire Line
	2400 4500 2400 4300
Connection ~ 1200 4500
Wire Wire Line
	2400 2900 2400 3700
Connection ~ 2400 2900
Wire Wire Line
	2600 2900 2600 3700
Connection ~ 2600 2900
Wire Wire Line
	2600 4500 2600 4300
Connection ~ 2400 4500
Wire Wire Line
	5250 3900 5250 3950
Connection ~ 7750 1750
Wire Wire Line
	2800 850  7550 850 
Wire Wire Line
	3500 1600 3600 1600
Wire Wire Line
	3500 850  3500 1600
Connection ~ 3500 850 
Wire Wire Line
	3250 700  7650 700 
Wire Wire Line
	3600 700  3600 1500
Wire Wire Line
	3250 4300 3250 700 
Connection ~ 3600 700 
Wire Wire Line
	4950 6350 4900 6350
Connection ~ 4950 6250
Wire Wire Line
	5800 4000 6200 4000
Wire Wire Line
	6200 4000 6200 3250
Wire Wire Line
	6200 3250 7050 3250
Wire Wire Line
	7050 3350 6300 3350
Wire Wire Line
	6300 3350 6300 4100
Wire Wire Line
	6400 4200 6400 3450
Wire Wire Line
	6400 3450 7050 3450
Wire Wire Line
	6100 3700 6100 4500
Wire Wire Line
	6100 4500 5800 4500
Wire Wire Line
	6000 3600 6000 4400
Wire Wire Line
	6000 4400 5800 4400
Wire Wire Line
	5900 3500 5900 4300
Wire Wire Line
	5900 4300 5800 4300
Connection ~ 9700 1450
Connection ~ 9900 1450
Connection ~ 10100 1450
Connection ~ 10300 1450
Connection ~ 10300 1150
Connection ~ 10100 1150
Connection ~ 9900 1150
Connection ~ 9700 1150
Connection ~ 10000 1150
Connection ~ 10000 1450
Wire Wire Line
	10000 1150 10000 1050
Wire Wire Line
	10000 1450 10000 1550
Wire Wire Line
	9500 1150 10500 1150
Wire Wire Line
	9500 1450 10500 1450
Wire Wire Line
	4750 1900 4750 1900
Wire Wire Line
	5700 2950 5700 3150
Wire Wire Line
	4200 1150 4200 1100
Wire Wire Line
	4000 1100 4000 1150
Connection ~ 4000 1150
Connection ~ 4300 1600
Wire Wire Line
	4700 1100 4700 1200
Connection ~ 4700 1200
Wire Wire Line
	4150 1500 4100 1500
Wire Wire Line
	4500 1200 4900 1200
Wire Wire Line
	4500 1200 4500 1100
Connection ~ 3500 1300
Connection ~ 4200 1700
Wire Wire Line
	7650 1550 7850 1550
Wire Wire Line
	7650 700  7650 1550
Connection ~ 7650 1400
Wire Wire Line
	7450 1300 8000 1300
Wire Wire Line
	7800 1300 7800 1200
Wire Wire Line
	8000 1300 8000 1200
Connection ~ 7800 1300
Wire Wire Line
	8300 1300 8700 1300
Wire Wire Line
	8500 1300 8500 1200
Wire Wire Line
	8300 1300 8300 1200
Connection ~ 8500 1300
Connection ~ 7550 1450
Wire Wire Line
	8550 1250 8550 1650
Wire Wire Line
	8100 1250 8550 1250
Connection ~ 8550 1650
Connection ~ 8600 1750
Wire Wire Line
	3500 1300 4400 1300
Wire Wire Line
	7550 1450 8200 1450
Wire Wire Line
	3850 1150 4200 1150
Wire Wire Line
	3600 1250 4600 1250
Wire Wire Line
	4600 1250 4600 1100
Connection ~ 3600 1250
Wire Wire Line
	4200 1200 4100 1200
Wire Wire Line
	4100 1200 4100 1100
Wire Wire Line
	4400 1300 4400 1100
Wire Wire Line
	4100 1600 4300 1600
Wire Wire Line
	7650 1400 8400 1400
Wire Wire Line
	8400 1400 8400 1200
Wire Wire Line
	7900 1200 7900 1350
Wire Wire Line
	7900 1350 8600 1350
Wire Wire Line
	8600 1350 8600 1750
Wire Wire Line
	8200 1450 8200 1200
Wire Wire Line
	8100 1250 8100 1200
$EndSCHEMATC
