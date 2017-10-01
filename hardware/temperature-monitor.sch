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
LIBS:custom
LIBS:temperature-monitor-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L BME280 U?
U 1 1 59D053EE
P 3100 2850
F 0 "U?" H 3350 2600 60  0000 C CNN
F 1 "BME280" H 3000 3100 60  0000 C CNN
F 2 "" H 3050 2850 60  0001 C CNN
F 3 "" H 3050 2850 60  0001 C CNN
	1    3100 2850
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 59D0F678
P 2050 3250
F 0 "C?" H 2075 3350 50  0000 L CNN
F 1 "0.1uF" H 2075 3150 50  0000 L CNN
F 2 "" H 2088 3100 50  0000 C CNN
F 3 "" H 2050 3250 50  0000 C CNN
	1    2050 3250
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 59D0F713
P 2300 3250
F 0 "C?" H 2325 3350 50  0000 L CNN
F 1 "0.1uF" H 2325 3150 50  0000 L CNN
F 2 "" H 2338 3100 50  0000 C CNN
F 3 "" H 2300 3250 50  0000 C CNN
	1    2300 3250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 59D0F866
P 3100 3650
F 0 "#PWR?" H 3100 3400 50  0001 C CNN
F 1 "GND" H 3100 3500 50  0000 C CNN
F 2 "" H 3100 3650 50  0000 C CNN
F 3 "" H 3100 3650 50  0000 C CNN
	1    3100 3650
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 59D0F8A7
P 1800 2600
F 0 "R?" V 1880 2600 50  0000 C CNN
F 1 "4.7K" V 1800 2600 50  0000 C CNN
F 2 "" V 1730 2600 50  0000 C CNN
F 3 "" H 1800 2600 50  0000 C CNN
	1    1800 2600
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 59D0FBD8
P 3850 2600
F 0 "R?" V 3930 2600 50  0000 C CNN
F 1 "4.7K" V 3850 2600 50  0000 C CNN
F 2 "" V 3780 2600 50  0000 C CNN
F 3 "" H 3850 2600 50  0000 C CNN
	1    3850 2600
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 59D0FC3F
P 4150 2600
F 0 "R?" V 4230 2600 50  0000 C CNN
F 1 "4.7K" V 4150 2600 50  0000 C CNN
F 2 "" V 4080 2600 50  0000 C CNN
F 3 "" H 4150 2600 50  0000 C CNN
	1    4150 2600
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 59D0FC68
P 4450 2600
F 0 "R?" V 4530 2600 50  0000 C CNN
F 1 "4.7K" V 4450 2600 50  0000 C CNN
F 2 "" V 4380 2600 50  0000 C CNN
F 3 "" H 4450 2600 50  0000 C CNN
	1    4450 2600
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR?
U 1 1 59D0FCA7
P 3050 2250
F 0 "#PWR?" H 3050 2100 50  0001 C CNN
F 1 "+3.3V" H 3050 2390 50  0000 C CNN
F 2 "" H 3050 2250 50  0000 C CNN
F 3 "" H 3050 2250 50  0000 C CNN
	1    3050 2250
	1    0    0    -1  
$EndComp
$Comp
L ESP-12F U?
U 1 1 59D11718
P 8100 2100
F 0 "U?" H 8650 1550 60  0000 C CNN
F 1 "ESP-12F" H 7550 2650 60  0000 C CNN
F 2 "" H 8100 2100 60  0001 C CNN
F 3 "" H 8100 2100 60  0001 C CNN
	1    8100 2100
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR?
U 1 1 59D117B5
P 5250 900
F 0 "#PWR?" H 5250 750 50  0001 C CNN
F 1 "+3.3V" H 5250 1040 50  0000 C CNN
F 2 "" H 5250 900 50  0000 C CNN
F 3 "" H 5250 900 50  0000 C CNN
	1    5250 900 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 59D11DD6
P 7250 2800
F 0 "#PWR?" H 7250 2550 50  0001 C CNN
F 1 "GND" H 7250 2650 50  0000 C CNN
F 2 "" H 7250 2800 50  0000 C CNN
F 3 "" H 7250 2800 50  0000 C CNN
	1    7250 2800
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 59D11E4F
P 6950 2500
F 0 "C?" H 6975 2600 50  0000 L CNN
F 1 "100nF" H 6975 2400 50  0000 L CNN
F 2 "" H 6988 2350 50  0000 C CNN
F 3 "" H 6950 2500 50  0000 C CNN
	1    6950 2500
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 59D121A6
P 5700 1000
F 0 "R?" V 5780 1000 50  0000 C CNN
F 1 "12K" V 5700 1000 50  0000 C CNN
F 2 "" V 5630 1000 50  0000 C CNN
F 3 "" H 5700 1000 50  0000 C CNN
	1    5700 1000
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 59D124D6
P 5700 1150
F 0 "R?" V 5780 1150 50  0000 C CNN
F 1 "12K" V 5700 1150 50  0000 C CNN
F 2 "" V 5630 1150 50  0000 C CNN
F 3 "" H 5700 1150 50  0000 C CNN
	1    5700 1150
	0    1    1    0   
$EndComp
$Comp
L C C?
U 1 1 59D125B2
P 6300 1400
F 0 "C?" H 6325 1500 50  0000 L CNN
F 1 "100nF" H 6325 1300 50  0000 L CNN
F 2 "" H 6338 1250 50  0000 C CNN
F 3 "" H 6300 1400 50  0000 C CNN
	1    6300 1400
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 59D131E1
P 5700 1300
F 0 "R?" V 5780 1300 50  0000 C CNN
F 1 "12K" V 5700 1300 50  0000 C CNN
F 2 "" V 5630 1300 50  0000 C CNN
F 3 "" H 5700 1300 50  0000 C CNN
	1    5700 1300
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 59D1321E
P 5700 1450
F 0 "R?" V 5780 1450 50  0000 C CNN
F 1 "12K" V 5700 1450 50  0000 C CNN
F 2 "" V 5630 1450 50  0000 C CNN
F 3 "" H 5700 1450 50  0000 C CNN
	1    5700 1450
	0    1    1    0   
$EndComp
NoConn ~ 7900 1450
NoConn ~ 8000 1450
NoConn ~ 8100 1450
NoConn ~ 8200 1450
NoConn ~ 8300 1450
$Comp
L R R?
U 1 1 59D13555
P 9150 2250
F 0 "R?" V 9230 2250 50  0000 C CNN
F 1 "12K" V 9150 2250 50  0000 C CNN
F 2 "" V 9080 2250 50  0000 C CNN
F 3 "" H 9150 2250 50  0000 C CNN
	1    9150 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2300 2700 2600 2700
Wire Wire Line
	2300 2400 2300 3100
Wire Wire Line
	2050 2900 2600 2900
Wire Wire Line
	2050 2400 2050 3100
Wire Wire Line
	2600 2800 2550 2800
Wire Wire Line
	2550 2800 2550 3500
Connection ~ 2300 2700
Connection ~ 2050 2900
Wire Wire Line
	2300 3400 2300 3500
Wire Wire Line
	2050 3400 2050 3500
Wire Wire Line
	3700 3500 3700 2700
Wire Wire Line
	3700 2700 3600 2700
Wire Wire Line
	1800 3000 2600 3000
Wire Wire Line
	1800 2750 1800 3000
Wire Wire Line
	3850 2400 3850 2450
Wire Wire Line
	4150 2400 4150 2450
Wire Wire Line
	4450 2400 4450 2450
Wire Wire Line
	3600 2800 3850 2800
Wire Wire Line
	3850 2800 3850 2750
Wire Wire Line
	3600 2900 4250 2900
Wire Wire Line
	4150 2900 4150 2750
Wire Wire Line
	3600 3000 4650 3000
Wire Wire Line
	4450 3000 4450 2750
Wire Wire Line
	2050 3500 3700 3500
Connection ~ 2300 3500
Connection ~ 2550 3500
Connection ~ 3100 3500
Wire Wire Line
	1800 2400 4450 2400
Connection ~ 3050 2400
Connection ~ 2050 2400
Wire Wire Line
	2300 2400 2050 2400
Connection ~ 2300 2400
Connection ~ 3850 2400
Connection ~ 4150 2400
Wire Wire Line
	1800 2450 1800 2400
Wire Wire Line
	3100 3500 3100 3650
Wire Wire Line
	3050 2400 3050 2250
Wire Wire Line
	6700 1850 7300 1850
Wire Wire Line
	5250 900  5250 1450
Wire Wire Line
	7300 2350 7250 2350
Wire Wire Line
	7250 2350 7250 2800
Wire Wire Line
	6700 2350 6700 1850
Wire Wire Line
	6950 1450 6950 2350
Connection ~ 6950 1850
Wire Wire Line
	5250 1000 5550 1000
Wire Wire Line
	5250 1150 5550 1150
Connection ~ 5250 1000
Wire Wire Line
	7900 2750 7900 3150
Connection ~ 5250 1150
Wire Wire Line
	5250 1300 5550 1300
Connection ~ 5250 1300
Wire Wire Line
	8900 1950 9150 1950
Wire Wire Line
	9150 1950 9150 2100
$Comp
L CONN_02X03 P?
U 1 1 59D12A28
P 4350 1150
F 0 "P?" H 4350 1350 50  0000 C CNN
F 1 "CONN_02X03" H 4350 950 50  0000 C CNN
F 2 "" H 4350 -50 50  0000 C CNN
F 3 "" H 4350 -50 50  0000 C CNN
	1    4350 1150
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR?
U 1 1 59D12C11
P 3900 850
F 0 "#PWR?" H 3900 700 50  0001 C CNN
F 1 "+3.3V" H 3900 990 50  0000 C CNN
F 2 "" H 3900 850 50  0000 C CNN
F 3 "" H 3900 850 50  0000 C CNN
	1    3900 850 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 59D12C49
P 3950 1500
F 0 "#PWR?" H 3950 1250 50  0001 C CNN
F 1 "GND" H 3950 1350 50  0000 C CNN
F 2 "" H 3950 1500 50  0000 C CNN
F 3 "" H 3950 1500 50  0000 C CNN
	1    3950 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 850  3900 1050
Wire Wire Line
	3900 1050 4100 1050
Wire Wire Line
	4100 1250 3950 1250
Wire Wire Line
	3950 1250 3950 1500
Text Label 7300 2150 2    60   ~ 0
RX
Text Label 7300 2250 2    60   ~ 0
TX
Text Label 4600 1050 0    60   ~ 0
RX
Text Label 4600 1150 0    60   ~ 0
TX
Text Label 4100 1150 2    60   ~ 0
RTS
Text Label 4600 1250 0    60   ~ 0
DTR
$Comp
L UMH3N U?
U 1 1 59D13799
P 5200 3500
F 0 "U?" H 5350 3300 60  0000 C CNN
F 1 "UMH3N" H 5200 3700 60  0000 C CNN
F 2 "" H 5200 3500 60  0001 C CNN
F 3 "" H 5200 3500 60  0001 C CNN
	1    5200 3500
	1    0    0    -1  
$EndComp
Text Label 4850 3400 2    60   ~ 0
RTS
Text Label 5550 3500 0    60   ~ 0
RTS
Text Label 5550 3400 0    60   ~ 0
RST
Text Label 4850 3500 2    60   ~ 0
DTR
Text Label 5550 3600 0    60   ~ 0
DTR
Text Label 4850 3600 2    60   ~ 0
GPIO0
Text Label 7900 2750 3    60   ~ 0
GPIO0
Text Label 7300 2050 2    60   ~ 0
RST
Text Label 4250 2900 0    60   ~ 0
SDA
Text Label 4650 3000 0    60   ~ 0
SCL
Connection ~ 4150 2900
Connection ~ 4450 3000
Text Label 7650 3300 2    60   ~ 0
SDA
Wire Wire Line
	8100 2750 8100 3300
Text Label 7650 3150 2    60   ~ 0
SCL
NoConn ~ 8200 2750
NoConn ~ 8300 2750
NoConn ~ 8900 2350
NoConn ~ 8900 2250
NoConn ~ 8900 2150
NoConn ~ 8900 2050
NoConn ~ 8900 1850
$Comp
L GND #PWR?
U 1 1 59D14911
P 9150 2550
F 0 "#PWR?" H 9150 2300 50  0001 C CNN
F 1 "GND" H 9150 2400 50  0000 C CNN
F 2 "" H 9150 2550 50  0000 C CNN
F 3 "" H 9150 2550 50  0000 C CNN
	1    9150 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	9150 2550 9150 2400
$Comp
L +3.3V #PWR?
U 1 1 59D14B14
P 6950 1450
F 0 "#PWR?" H 6950 1300 50  0001 C CNN
F 1 "+3.3V" H 6950 1590 50  0000 C CNN
F 2 "" H 6950 1450 50  0000 C CNN
F 3 "" H 6950 1450 50  0000 C CNN
	1    6950 1450
	1    0    0    -1  
$EndComp
Text Label 7300 1950 2    60   ~ 0
EN
Text Label 5850 1000 0    60   ~ 0
EN
Text Label 5850 1150 0    60   ~ 0
RST
Wire Wire Line
	6300 1250 6300 1150
Wire Wire Line
	6300 1150 5850 1150
$Comp
L GND #PWR?
U 1 1 59D150AB
P 6300 1650
F 0 "#PWR?" H 6300 1400 50  0001 C CNN
F 1 "GND" H 6300 1500 50  0000 C CNN
F 2 "" H 6300 1650 50  0000 C CNN
F 3 "" H 6300 1650 50  0000 C CNN
	1    6300 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 1650 6300 1550
Text Label 5850 1300 0    60   ~ 0
GPIO0
Wire Wire Line
	5250 1450 5550 1450
Text Label 5850 1450 0    60   ~ 0
GPIO2
Text Label 8000 2750 3    60   ~ 0
GPIO2
Wire Wire Line
	7900 3150 7650 3150
Wire Wire Line
	8100 3300 7650 3300
$Comp
L C C?
U 1 1 59D11DFA
P 6700 2500
F 0 "C?" H 6725 2600 50  0000 L CNN
F 1 "10uF" H 6725 2400 50  0000 L CNN
F 2 "" H 6738 2350 50  0000 C CNN
F 3 "" H 6700 2500 50  0000 C CNN
	1    6700 2500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 59D15869
P 6950 2800
F 0 "#PWR?" H 6950 2550 50  0001 C CNN
F 1 "GND" H 6950 2650 50  0000 C CNN
F 2 "" H 6950 2800 50  0000 C CNN
F 3 "" H 6950 2800 50  0000 C CNN
	1    6950 2800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 59D158AA
P 6700 2800
F 0 "#PWR?" H 6700 2550 50  0001 C CNN
F 1 "GND" H 6700 2650 50  0000 C CNN
F 2 "" H 6700 2800 50  0000 C CNN
F 3 "" H 6700 2800 50  0000 C CNN
	1    6700 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 2800 6700 2650
Wire Wire Line
	6950 2800 6950 2650
$EndSCHEMATC
