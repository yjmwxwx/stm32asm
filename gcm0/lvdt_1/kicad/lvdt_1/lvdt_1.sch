EESchema Schematic File Version 4
LIBS:lvdt_1-cache
EELAYER 30 0
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
L Regulator_Linear:LM317_TO3 U?
U 1 1 5DC43329
P 3000 5400
F 0 "U?" H 3000 5642 50  0000 C CNN
F 1 "LM317_TO3" H 3000 5551 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-3" H 3000 5600 50  0001 C CIN
F 3 "http://www.ti.com/lit/ds/symlink/lm317.pdf" H 3000 5400 50  0001 C CNN
	1    3000 5400
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5DC47E67
P 3450 5550
F 0 "R?" H 3520 5596 50  0000 L CNN
F 1 "R" H 3520 5505 50  0000 L CNN
F 2 "" V 3380 5550 50  0001 C CNN
F 3 "~" H 3450 5550 50  0001 C CNN
	1    3450 5550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5DC48C8E
P 3450 5900
F 0 "R?" H 3520 5946 50  0000 L CNN
F 1 "R" H 3520 5855 50  0000 L CNN
F 2 "" V 3380 5900 50  0001 C CNN
F 3 "~" H 3450 5900 50  0001 C CNN
	1    3450 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 5700 3450 5700
Wire Wire Line
	3450 5750 3450 5700
Connection ~ 3450 5700
Wire Wire Line
	3300 5400 3450 5400
$Comp
L Device:C C?
U 1 1 5DC4C405
P 2450 5600
F 0 "C?" H 2565 5646 50  0000 L CNN
F 1 "C" H 2565 5555 50  0000 L CNN
F 2 "" H 2488 5450 50  0001 C CNN
F 3 "~" H 2450 5600 50  0001 C CNN
	1    2450 5600
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C?
U 1 1 5DC4D833
P 2000 5600
F 0 "C?" H 2118 5646 50  0000 L CNN
F 1 "CP" H 2118 5555 50  0000 L CNN
F 2 "" H 2038 5450 50  0001 C CNN
F 3 "~" H 2000 5600 50  0001 C CNN
	1    2000 5600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 5400 2450 5400
Wire Wire Line
	2450 5400 2450 5450
Connection ~ 2450 5400
Wire Wire Line
	2450 5400 2000 5400
$Comp
L Regulator_Switching:LM2596T-ADJ U?
U 1 1 5DC787C5
P 2900 7200
F 0 "U?" H 2900 7567 50  0000 C CNN
F 1 "LM2596T-ADJ" H 2900 7476 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-5_P3.4x3.7mm_StaggerOdd_Lead3.8mm_Vertical" H 2950 6950 50  0001 L CIN
F 3 "http://www.ti.com/lit/ds/symlink/lm2596.pdf" H 2900 7200 50  0001 C CNN
	1    2900 7200
	1    0    0    1   
$EndComp
Wire Wire Line
	2900 6900 2600 6900
Wire Wire Line
	2400 6900 2400 7100
$Comp
L Device:C C?
U 1 1 5DC7AFCC
P 2000 7150
F 0 "C?" H 2115 7196 50  0000 L CNN
F 1 "C" H 2115 7105 50  0000 L CNN
F 2 "" H 2038 7000 50  0001 C CNN
F 3 "~" H 2000 7150 50  0001 C CNN
	1    2000 7150
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C?
U 1 1 5DC7C491
P 1450 7150
F 0 "C?" H 1332 7104 50  0000 R CNN
F 1 "CP" H 1332 7195 50  0000 R CNN
F 2 "" H 1488 7000 50  0001 C CNN
F 3 "~" H 1450 7150 50  0001 C CNN
	1    1450 7150
	-1   0    0    1   
$EndComp
Wire Wire Line
	2400 7300 2000 7300
Wire Wire Line
	1450 7300 2000 7300
Connection ~ 2000 7300
$Comp
L Diode:1N5822 D?
U 1 1 5DC7D3A9
P 3200 6900
F 0 "D?" H 3200 6684 50  0000 C CNN
F 1 "1N5822" H 3200 6775 50  0000 C CNN
F 2 "Diode_THT:D_DO-201AD_P15.24mm_Horizontal" H 3200 6725 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88526/1n5820.pdf" H 3200 6900 50  0001 C CNN
	1    3200 6900
	-1   0    0    1   
$EndComp
Wire Wire Line
	3350 6900 3400 6900
Wire Wire Line
	3400 6900 3400 7100
Wire Wire Line
	3050 6900 3000 6900
Connection ~ 2900 6900
$Comp
L Device:R R?
U 1 1 5DC7FF81
P 3450 6350
F 0 "R?" H 3520 6396 50  0000 L CNN
F 1 "R" H 3520 6305 50  0000 L CNN
F 2 "" V 3380 6350 50  0001 C CNN
F 3 "~" H 3450 6350 50  0001 C CNN
	1    3450 6350
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5DC81979
P 3150 6500
F 0 "R?" V 2943 6500 50  0000 C CNN
F 1 "R" V 3034 6500 50  0000 C CNN
F 2 "" V 3080 6500 50  0001 C CNN
F 3 "~" H 3150 6500 50  0001 C CNN
	1    3150 6500
	0    1    1    0   
$EndComp
Wire Wire Line
	3300 6500 3450 6500
Wire Wire Line
	3000 6500 3000 6600
Connection ~ 3000 6900
Wire Wire Line
	3000 6900 2900 6900
Wire Wire Line
	3400 7300 3450 7300
Wire Wire Line
	3450 7300 3450 6500
Connection ~ 3450 6500
$Comp
L Device:C C?
U 1 1 5DC83D52
P 2600 6700
F 0 "C?" H 2715 6746 50  0000 L CNN
F 1 "C" H 2715 6655 50  0000 L CNN
F 2 "" H 2638 6550 50  0001 C CNN
F 3 "~" H 2600 6700 50  0001 C CNN
	1    2600 6700
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C?
U 1 1 5DC857D0
P 2100 6700
F 0 "C?" H 2218 6746 50  0000 L CNN
F 1 "CP" H 2218 6655 50  0000 L CNN
F 2 "" H 2138 6550 50  0001 C CNN
F 3 "~" H 2100 6700 50  0001 C CNN
	1    2100 6700
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 6850 2600 6900
Connection ~ 2600 6900
Wire Wire Line
	2600 6900 2400 6900
Wire Wire Line
	2100 6850 2100 6900
Wire Wire Line
	2100 6900 2400 6900
Connection ~ 2400 6900
Wire Wire Line
	2100 6550 2250 6550
Wire Wire Line
	2000 5750 2250 5750
Connection ~ 2250 5750
Wire Wire Line
	2250 5750 2450 5750
Connection ~ 2250 6550
Wire Wire Line
	2250 6550 2600 6550
Wire Wire Line
	2250 5750 2250 6100
Wire Wire Line
	2000 7000 1700 7000
Wire Wire Line
	3850 6100 3450 6100
Connection ~ 2250 6100
Wire Wire Line
	2250 6100 2250 6550
Wire Wire Line
	1700 6100 1700 7000
Connection ~ 1700 7000
Wire Wire Line
	1700 7000 1450 7000
Wire Wire Line
	3450 6200 3450 6100
Connection ~ 3450 6100
Wire Wire Line
	3450 6100 2250 6100
Wire Wire Line
	3450 6100 3450 6050
Wire Wire Line
	2000 5400 2000 5450
Wire Wire Line
	2000 5400 1250 5400
Wire Wire Line
	1250 5400 1250 7300
Wire Wire Line
	1250 7300 1450 7300
Connection ~ 2000 5400
Connection ~ 1450 7300
$Comp
L power:GND #PWR?
U 1 1 5DC9BC39
P 3850 6100
F 0 "#PWR?" H 3850 5850 50  0001 C CNN
F 1 "GND" H 3855 5927 50  0000 C CNN
F 2 "" H 3850 6100 50  0001 C CNN
F 3 "" H 3850 6100 50  0001 C CNN
	1    3850 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 6600 3850 6600
Connection ~ 3000 6600
Wire Wire Line
	3000 6600 3000 6900
Wire Wire Line
	3450 5400 3800 5400
Connection ~ 3450 5400
Text GLabel 3800 5400 2    50   Output ~ 0
+5
Text GLabel 3850 6600 2    50   Output ~ 0
-5
Text GLabel 1150 5400 0    50   Input ~ 0
+12
Wire Wire Line
	1150 5400 1250 5400
Connection ~ 1250 5400
Wire Wire Line
	1700 6100 2250 6100
$Comp
L MCU_ST_STM32F0:STM32F030F4Px U?
U 1 1 5DCA2C21
P 5650 6500
F 0 "U?" H 5650 5611 50  0000 C CNN
F 1 "STM32F030F4Px" H 5650 5520 50  0000 C CNN
F 2 "Package_SO:TSSOP-20_4.4x6.5mm_P0.65mm" H 5250 5800 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00088500.pdf" H 5650 6500 50  0001 C CNN
	1    5650 6500
	1    0    0    -1  
$EndComp
Wire Notes Line
	4200 5050 4200 7650
Wire Notes Line
	4200 7650 800  7650
Wire Notes Line
	800  7650 800  5050
Wire Notes Line
	800  5050 4200 5050
$Comp
L Device:C C?
U 1 1 5DCA8C8B
P 4950 6000
F 0 "C?" V 4698 6000 50  0000 C CNN
F 1 "C" V 4789 6000 50  0000 C CNN
F 2 "" H 4988 5850 50  0001 C CNN
F 3 "~" H 4950 6000 50  0001 C CNN
	1    4950 6000
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5DCA9FCF
P 4950 6450
F 0 "R?" V 4743 6450 50  0000 C CNN
F 1 "R" V 4834 6450 50  0000 C CNN
F 2 "" V 4880 6450 50  0001 C CNN
F 3 "~" H 4950 6450 50  0001 C CNN
	1    4950 6450
	0    1    1    0   
$EndComp
Wire Wire Line
	5100 6450 5100 6200
Wire Wire Line
	5100 6200 5150 6200
Wire Wire Line
	5150 6000 5100 6000
Wire Wire Line
	4800 6450 4800 6200
$Comp
L power:GND #PWR?
U 1 1 5DCAE1F7
P 4600 6250
F 0 "#PWR?" H 4600 6000 50  0001 C CNN
F 1 "GND" H 4605 6077 50  0000 C CNN
F 2 "" H 4600 6250 50  0001 C CNN
F 3 "" H 4600 6250 50  0001 C CNN
	1    4600 6250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 6250 4600 6200
Wire Wire Line
	4600 6200 4800 6200
Connection ~ 4800 6200
Wire Wire Line
	4800 6200 4800 6000
Text GLabel 5650 5550 0    50   Input ~ 0
+5
Wire Wire Line
	5650 5800 5650 5700
Wire Wire Line
	5750 5800 5750 5700
Wire Wire Line
	5750 5700 5650 5700
Connection ~ 5650 5700
Wire Wire Line
	5650 5700 5650 5550
$Comp
L power:GND #PWR?
U 1 1 5DCB178F
P 5150 7300
F 0 "#PWR?" H 5150 7050 50  0001 C CNN
F 1 "GND" H 5155 7127 50  0000 C CNN
F 2 "" H 5150 7300 50  0001 C CNN
F 3 "" H 5150 7300 50  0001 C CNN
	1    5150 7300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 7300 5650 7300
Text GLabel 6150 7100 2    50   BiDi ~ 0
DIO
Text GLabel 6150 7000 2    50   BiDi ~ 0
CLK
Wire Notes Line
	4300 5400 6550 5400
Wire Notes Line
	6550 5400 6550 7650
Wire Notes Line
	6550 7650 4300 7650
Wire Notes Line
	4300 7650 4300 5400
$Comp
L Display_Character:KCSA02-105 U?
U 1 1 5DC5497F
P 5150 4100
F 0 "U?" H 5150 4767 50  0000 C CNN
F 1 "KCSA02-105" H 5150 4676 50  0000 C CNN
F 2 "Display_7Segment:KCSC02-105" H 5150 3500 50  0001 C CNN
F 3 "http://www.kingbright.com/attachments/file/psearch/000/00/00/KCSA02-105(Ver.10A).pdf" H 4650 4575 50  0001 L CNN
	1    5150 4100
	1    0    0    -1  
$EndComp
$Comp
L Display_Character:KCSA02-105 U?
U 1 1 5DC56233
P 4100 4100
F 0 "U?" H 4100 4767 50  0000 C CNN
F 1 "KCSA02-105" H 4100 4676 50  0000 C CNN
F 2 "Display_7Segment:KCSC02-105" H 4100 3500 50  0001 C CNN
F 3 "http://www.kingbright.com/attachments/file/psearch/000/00/00/KCSA02-105(Ver.10A).pdf" H 3600 4575 50  0001 L CNN
	1    4100 4100
	1    0    0    -1  
$EndComp
$Comp
L Display_Character:KCSA02-105 U?
U 1 1 5DC57023
P 3100 4100
F 0 "U?" H 3100 4767 50  0000 C CNN
F 1 "KCSA02-105" H 3100 4676 50  0000 C CNN
F 2 "Display_7Segment:KCSC02-105" H 3100 3500 50  0001 C CNN
F 3 "http://www.kingbright.com/attachments/file/psearch/000/00/00/KCSA02-105(Ver.10A).pdf" H 2600 4575 50  0001 L CNN
	1    3100 4100
	1    0    0    -1  
$EndComp
$Comp
L Display_Character:KCSA02-105 U?
U 1 1 5DC58259
P 2100 4100
F 0 "U?" H 2100 4767 50  0000 C CNN
F 1 "KCSA02-105" H 2100 4676 50  0000 C CNN
F 2 "Display_7Segment:KCSC02-105" H 2100 3500 50  0001 C CNN
F 3 "http://www.kingbright.com/attachments/file/psearch/000/00/00/KCSA02-105(Ver.10A).pdf" H 1600 4575 50  0001 L CNN
	1    2100 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 3800 4850 3350
Wire Wire Line
	4850 3350 3800 3350
Wire Wire Line
	4850 3900 4750 3900
Wire Wire Line
	4750 3900 4750 3300
Wire Wire Line
	4750 3300 3750 3300
Wire Wire Line
	4850 4000 4700 4000
Wire Wire Line
	4700 4000 4700 3250
Wire Wire Line
	4700 3250 3700 3250
Wire Wire Line
	4850 4100 4650 4100
Wire Wire Line
	4650 4100 4650 3200
Wire Wire Line
	4650 3200 3650 3200
Wire Wire Line
	4850 4200 4600 4200
Wire Wire Line
	4600 4200 4600 3150
Wire Wire Line
	4600 3150 3600 3150
Wire Wire Line
	4850 4300 4550 4300
Wire Wire Line
	4550 4300 4550 3100
Wire Wire Line
	4550 3100 3550 3100
Wire Wire Line
	4850 4400 4500 4400
Wire Wire Line
	4500 4400 4500 3050
Wire Wire Line
	4500 3050 3500 3050
Wire Wire Line
	4850 4500 4450 4500
Wire Wire Line
	4450 4500 4450 3000
Wire Wire Line
	4450 3000 3450 3000
Wire Wire Line
	3800 3800 3800 3350
Connection ~ 3800 3350
Wire Wire Line
	3800 3350 2800 3350
Wire Wire Line
	3800 3900 3750 3900
Wire Wire Line
	3750 3900 3750 3300
Connection ~ 3750 3300
Wire Wire Line
	3750 3300 2750 3300
Wire Wire Line
	3800 4000 3700 4000
Wire Wire Line
	3700 4000 3700 3250
Connection ~ 3700 3250
Wire Wire Line
	3700 3250 2700 3250
Wire Wire Line
	3800 4100 3650 4100
Wire Wire Line
	3650 4100 3650 3200
Connection ~ 3650 3200
Wire Wire Line
	3650 3200 2650 3200
Wire Wire Line
	3800 4200 3600 4200
Wire Wire Line
	3600 4200 3600 3150
Connection ~ 3600 3150
Wire Wire Line
	3600 3150 2600 3150
Wire Wire Line
	3800 4300 3550 4300
Wire Wire Line
	3550 4300 3550 3100
Connection ~ 3550 3100
Wire Wire Line
	3550 3100 2550 3100
Wire Wire Line
	3800 4400 3500 4400
Wire Wire Line
	3500 4400 3500 3050
Connection ~ 3500 3050
Wire Wire Line
	3500 3050 2500 3050
Wire Wire Line
	3800 4500 3450 4500
Wire Wire Line
	3450 4500 3450 3000
Connection ~ 3450 3000
Wire Wire Line
	3450 3000 2450 3000
Wire Wire Line
	2800 3800 2800 3350
Connection ~ 2800 3350
Wire Wire Line
	2800 3350 1800 3350
Wire Wire Line
	2800 3900 2750 3900
Wire Wire Line
	2750 3900 2750 3300
Connection ~ 2750 3300
Wire Wire Line
	2750 3300 1750 3300
Wire Wire Line
	2800 4000 2700 4000
Wire Wire Line
	2700 4000 2700 3250
Connection ~ 2700 3250
Wire Wire Line
	2700 3250 1700 3250
Wire Wire Line
	2800 4100 2650 4100
Wire Wire Line
	2650 4100 2650 3200
Connection ~ 2650 3200
Wire Wire Line
	2800 4200 2600 4200
Wire Wire Line
	2600 4200 2600 3150
Connection ~ 2600 3150
Wire Wire Line
	2600 3150 1600 3150
Wire Wire Line
	2800 4300 2550 4300
Wire Wire Line
	2550 4300 2550 3100
Connection ~ 2550 3100
Wire Wire Line
	2550 3100 1550 3100
Wire Wire Line
	2800 4400 2500 4400
Wire Wire Line
	2500 4400 2500 3050
Connection ~ 2500 3050
Wire Wire Line
	2500 3050 1500 3050
Wire Wire Line
	2800 4500 2450 4500
Wire Wire Line
	2450 4500 2450 3000
Connection ~ 2450 3000
Wire Wire Line
	2450 3000 1450 3000
Wire Wire Line
	1800 3800 1800 3350
Connection ~ 1800 3350
Wire Wire Line
	1800 3350 1400 3350
Wire Wire Line
	1800 3900 1750 3900
Wire Wire Line
	1750 3900 1750 3300
Connection ~ 1750 3300
Wire Wire Line
	2650 3200 1650 3200
Wire Wire Line
	1800 4000 1700 4000
Wire Wire Line
	1700 4000 1700 3250
Connection ~ 1700 3250
Wire Wire Line
	1800 4100 1650 4100
Wire Wire Line
	1650 4100 1650 3200
Connection ~ 1650 3200
Wire Wire Line
	1800 4200 1600 4200
Wire Wire Line
	1600 4200 1600 3150
Connection ~ 1600 3150
Wire Wire Line
	1800 4300 1550 4300
Wire Wire Line
	1550 4300 1550 3100
Connection ~ 1550 3100
Wire Wire Line
	1800 4400 1500 4400
Wire Wire Line
	1500 4400 1500 3050
Connection ~ 1500 3050
Wire Wire Line
	1800 4500 1450 4500
Wire Wire Line
	1450 4500 1450 3000
Connection ~ 1450 3000
Wire Wire Line
	1450 3000 1400 3000
Wire Wire Line
	2400 4400 2400 4500
Connection ~ 2400 4500
Wire Wire Line
	2400 4500 2400 4800
Wire Wire Line
	3400 4400 3400 4500
Connection ~ 3400 4500
Wire Wire Line
	3400 4500 3400 4800
Wire Wire Line
	4400 4400 4400 4500
Connection ~ 4400 4500
Wire Wire Line
	4400 4500 4400 4800
Wire Wire Line
	5450 4400 5450 4500
Connection ~ 5450 4500
Wire Wire Line
	5450 4500 5450 4750
Text GLabel 6150 6700 2    50   Output ~ 0
A
Text GLabel 1100 3500 0    50   Input ~ 0
A
Text GLabel 1100 3400 0    50   Input ~ 0
B
Text GLabel 1100 3300 0    50   Input ~ 0
C
Text GLabel 1100 3200 0    50   Input ~ 0
D
Text GLabel 1100 3100 0    50   Input ~ 0
E
Text GLabel 1100 3000 0    50   Input ~ 0
F
Text GLabel 1100 2900 0    50   Input ~ 0
G
Text GLabel 1100 2800 0    50   Input ~ 0
DP
Wire Wire Line
	1400 3000 1400 2800
Wire Wire Line
	1400 2800 1100 2800
Wire Wire Line
	1350 3050 1350 2900
Wire Wire Line
	1350 2900 1100 2900
Wire Wire Line
	1350 3050 1500 3050
Wire Wire Line
	1300 3100 1300 3000
Wire Wire Line
	1300 3000 1100 3000
Wire Wire Line
	1300 3100 1550 3100
Wire Wire Line
	1200 3150 1200 3100
Wire Wire Line
	1200 3100 1100 3100
Wire Wire Line
	1200 3150 1600 3150
Wire Wire Line
	1100 3200 1650 3200
Wire Wire Line
	1200 3250 1200 3300
Wire Wire Line
	1200 3250 1700 3250
Wire Wire Line
	1200 3300 1100 3300
Wire Wire Line
	1250 3300 1250 3400
Wire Wire Line
	1250 3400 1100 3400
Wire Wire Line
	1250 3300 1750 3300
Wire Wire Line
	1400 3350 1400 3500
Wire Wire Line
	1400 3500 1100 3500
Text GLabel 6150 6600 2    50   Output ~ 0
B
Text GLabel 6150 6500 2    50   Output ~ 0
D
Text GLabel 6150 6100 2    50   Output ~ 0
G
Text GLabel 6150 6200 2    50   Output ~ 0
F
Text GLabel 6150 6300 2    50   Output ~ 0
E
Text GLabel 6150 6400 2    50   Output ~ 0
C
Text GLabel 6150 6800 2    50   Output ~ 0
CA
Text GLabel 6150 6900 2    50   Output ~ 0
CA1
Text GLabel 5150 6800 0    50   Output ~ 0
CA3
Text GLabel 5150 6900 0    50   Output ~ 0
CA2
Text GLabel 5150 7100 0    50   Output ~ 0
SPWM
Text GLabel 6150 6000 2    50   Output ~ 0
ADC
Text GLabel 5450 4750 0    50   Input ~ 0
CA
Text GLabel 4400 4800 0    50   Input ~ 0
CA1
Text GLabel 3400 4800 0    50   Input ~ 0
CA2
Text GLabel 2400 4800 0    50   Input ~ 0
CA3
Wire Notes Line
	800  2550 5550 2550
Wire Notes Line
	5550 2550 5550 4950
Wire Notes Line
	5550 4950 800  4950
Wire Notes Line
	800  4950 800  2550
$Comp
L Amplifier_Operational:TL084 U?
U 1 1 5DD73CD0
P 1950 1950
F 0 "U?" H 1950 2317 50  0000 C CNN
F 1 "TL084" H 1950 2226 50  0000 C CNN
F 2 "" H 1900 2050 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl081.pdf" H 2000 2150 50  0001 C CNN
	1    1950 1950
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:TL084 U?
U 2 1 5DD85F79
P 3700 1650
F 0 "U?" H 3700 2017 50  0000 C CNN
F 1 "TL084" H 3700 1926 50  0000 C CNN
F 2 "" H 3650 1750 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl081.pdf" H 3750 1850 50  0001 C CNN
	2    3700 1650
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:TL084 U?
U 3 1 5DD88DAA
P 2850 1550
F 0 "U?" H 2850 1917 50  0000 C CNN
F 1 "TL084" H 2850 1826 50  0000 C CNN
F 2 "" H 2800 1650 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl081.pdf" H 2900 1750 50  0001 C CNN
	3    2850 1550
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:TL084 U?
U 4 1 5DD8DC30
P 1900 1100
F 0 "U?" H 1900 1467 50  0000 C CNN
F 1 "TL084" H 1900 1376 50  0000 C CNN
F 2 "" H 1850 1200 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl081.pdf" H 1950 1300 50  0001 C CNN
	4    1900 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 1350 2200 1350
Wire Wire Line
	2200 1350 2200 1100
Wire Wire Line
	3400 1750 3400 1950
Wire Wire Line
	3400 1950 4000 1950
Wire Wire Line
	2250 2250 2250 1950
$Comp
L Device:R R?
U 1 1 5DDBB7D1
P 2350 1100
F 0 "R?" V 2143 1100 50  0000 C CNN
F 1 "R" V 2234 1100 50  0000 C CNN
F 2 "" V 2280 1100 50  0001 C CNN
F 3 "~" H 2350 1100 50  0001 C CNN
	1    2350 1100
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5DDBD0E3
P 2700 1100
F 0 "R?" V 2493 1100 50  0000 C CNN
F 1 "R" V 2584 1100 50  0000 C CNN
F 2 "" V 2630 1100 50  0001 C CNN
F 3 "~" H 2700 1100 50  0001 C CNN
	1    2700 1100
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5DDBE53D
P 2400 1950
F 0 "R?" V 2607 1950 50  0000 C CNN
F 1 "R" V 2516 1950 50  0000 C CNN
F 2 "" V 2330 1950 50  0001 C CNN
F 3 "~" H 2400 1950 50  0001 C CNN
	1    2400 1950
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 5DDD2D73
P 2750 1950
F 0 "R?" V 2543 1950 50  0000 C CNN
F 1 "R" V 2634 1950 50  0000 C CNN
F 2 "" V 2680 1950 50  0001 C CNN
F 3 "~" H 2750 1950 50  0001 C CNN
	1    2750 1950
	0    1    1    0   
$EndComp
Connection ~ 2250 1950
Connection ~ 2200 1100
Wire Wire Line
	1600 1350 1600 1200
Wire Wire Line
	1650 2250 2250 2250
Wire Wire Line
	1650 2050 1650 2250
Wire Wire Line
	2550 1450 2550 1100
Wire Wire Line
	2500 1100 2550 1100
Connection ~ 2550 1100
Wire Wire Line
	2550 1650 2550 1950
Wire Wire Line
	2600 1950 2550 1950
Connection ~ 2550 1950
Wire Wire Line
	2900 1950 3150 1950
Wire Wire Line
	3150 1950 3150 1550
$Comp
L power:GND #PWR?
U 1 1 5DE68653
P 3100 1100
F 0 "#PWR?" H 3100 850 50  0001 C CNN
F 1 "GND" H 3105 927 50  0000 C CNN
F 2 "" H 3100 1100 50  0001 C CNN
F 3 "" H 3100 1100 50  0001 C CNN
	1    3100 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 1100 3100 1100
Wire Wire Line
	4000 1950 4000 1650
Wire Wire Line
	3400 1550 3150 1550
Connection ~ 3150 1550
Text GLabel 1600 1000 0    50   Input ~ 0
chuan_gan_qi
Text GLabel 1650 1850 0    50   Input ~ 0
chuan_gan_qi_1
Text GLabel 4300 1650 2    50   Input ~ 0
adc
$Comp
L Device:R R?
U 1 1 5DE97225
P 4150 1650
F 0 "R?" V 3943 1650 50  0000 C CNN
F 1 "R" V 4034 1650 50  0000 C CNN
F 2 "" V 4080 1650 50  0001 C CNN
F 3 "~" H 4150 1650 50  0001 C CNN
	1    4150 1650
	0    1    1    0   
$EndComp
Connection ~ 4000 1650
Wire Notes Line
	4650 550  4650 2450
Wire Notes Line
	4650 2450 850  2450
Wire Notes Line
	850  2450 850  550 
Wire Notes Line
	850  550  4650 550 
$Comp
L Amplifier_Operational:NE5532 U?
U 1 1 5DF04C36
P 9800 5200
F 0 "U?" H 9800 5567 50  0000 C CNN
F 1 "NE5532" H 9800 5476 50  0000 C CNN
F 2 "" H 9800 5200 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/ne5532.pdf" H 9800 5200 50  0001 C CNN
	1    9800 5200
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:NE5532 U?
U 2 1 5DF07E0E
P 10700 4850
F 0 "U?" H 10700 5217 50  0000 C CNN
F 1 "NE5532" H 10700 5126 50  0000 C CNN
F 2 "" H 10700 4850 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/ne5532.pdf" H 10700 4850 50  0001 C CNN
	2    10700 4850
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:NE5532 U?
U 3 1 5DF09E0C
P 9450 6050
F 0 "U?" H 9408 6096 50  0000 L CNN
F 1 "NE5532" H 9408 6005 50  0000 L CNN
F 2 "" H 9450 6050 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/ne5532.pdf" H 9450 6050 50  0001 C CNN
	3    9450 6050
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:TL084 U?
U 5 1 5DF0BA01
P 4400 1000
F 0 "U?" H 4358 1046 50  0000 L CNN
F 1 "TL084" H 4358 955 50  0000 L CNN
F 2 "" H 4350 1100 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl081.pdf" H 4450 1200 50  0001 C CNN
	5    4400 1000
	1    0    0    -1  
$EndComp
Text GLabel 4200 700  0    50   Input ~ 0
+5
Text GLabel 4200 1300 0    50   Input ~ 0
-5
Wire Wire Line
	4200 1300 4300 1300
Wire Wire Line
	4300 700  4200 700 
$Comp
L Device:CP C?
U 1 1 5DF362BE
P 7850 5100
F 0 "C?" V 8105 5100 50  0000 C CNN
F 1 "4.7UF" V 8014 5100 50  0000 C CNN
F 2 "" H 7888 4950 50  0001 C CNN
F 3 "~" H 7850 5100 50  0001 C CNN
	1    7850 5100
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 5DF39E53
P 8050 5500
F 0 "R?" H 8120 5546 50  0000 L CNN
F 1 "100K" H 8120 5455 50  0000 L CNN
F 2 "" V 7980 5500 50  0001 C CNN
F 3 "~" H 8050 5500 50  0001 C CNN
	1    8050 5500
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5DF3B2D2
P 8350 5100
F 0 "R?" V 8143 5100 50  0000 C CNN
F 1 "7K" V 8234 5100 50  0000 C CNN
F 2 "" V 8280 5100 50  0001 C CNN
F 3 "~" H 8350 5100 50  0001 C CNN
	1    8350 5100
	0    1    1    0   
$EndComp
$Comp
L Device:C C?
U 1 1 5DF604D7
P 8600 4650
F 0 "C?" H 8715 4696 50  0000 L CNN
F 1 "2.2NF" H 8715 4605 50  0000 L CNN
F 2 "" H 8638 4500 50  0001 C CNN
F 3 "~" H 8600 4650 50  0001 C CNN
	1    8600 4650
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5DF61428
P 9000 5450
F 0 "C?" H 9115 5496 50  0000 L CNN
F 1 "1NF" H 9115 5405 50  0000 L CNN
F 2 "" H 9038 5300 50  0001 C CNN
F 3 "~" H 9000 5450 50  0001 C CNN
	1    9000 5450
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5DF6212A
P 8850 5100
F 0 "R?" V 8643 5100 50  0000 C CNN
F 1 "22K" V 8734 5100 50  0000 C CNN
F 2 "" V 8780 5100 50  0001 C CNN
F 3 "~" H 8850 5100 50  0001 C CNN
	1    8850 5100
	0    1    1    0   
$EndComp
Wire Wire Line
	9500 5300 9500 5550
Wire Wire Line
	9500 5550 10100 5550
Wire Wire Line
	8500 5100 8600 5100
Wire Wire Line
	8050 5350 8050 5100
Wire Wire Line
	8000 5100 8050 5100
Connection ~ 8050 5100
Wire Wire Line
	8050 5100 8200 5100
Wire Wire Line
	9000 5100 9500 5100
Wire Wire Line
	9000 5300 9000 5100
Connection ~ 9000 5100
Wire Wire Line
	8050 5650 8050 5700
Wire Wire Line
	8050 5700 8500 5700
Wire Wire Line
	9000 5700 9000 5600
Wire Wire Line
	8600 4800 8600 5100
Connection ~ 8600 5100
Wire Wire Line
	8600 5100 8700 5100
Wire Wire Line
	8600 4500 10100 4500
Wire Notes Line
	11150 4200 11150 6400
Wire Notes Line
	7000 6400 7000 4200
Wire Notes Line
	7000 4200 11150 4200
Wire Notes Line
	7000 6400 11150 6400
Text GLabel 7700 5100 0    50   Input ~ 0
SPWM
Text GLabel 10300 6200 0    50   Output ~ 0
zheng_xian_bo
$Comp
L power:GND #PWR?
U 1 1 5E0C9F88
P 8500 5700
F 0 "#PWR?" H 8500 5450 50  0001 C CNN
F 1 "GND" H 8505 5527 50  0000 C CNN
F 2 "" H 8500 5700 50  0001 C CNN
F 3 "" H 8500 5700 50  0001 C CNN
	1    8500 5700
	1    0    0    -1  
$EndComp
Connection ~ 8500 5700
Wire Wire Line
	8500 5700 9000 5700
Text Notes 4400 5550 0    50   ~ 0
MCU
Text Notes 900  5150 0    50   ~ 0
dian_yuan
Text Notes 950  650  0    50   ~ 0
shu_ma_guan
Text Notes 7100 4300 0    50   ~ 0
di_tong_lv_bo
$Comp
L Device:L L?
U 1 1 5E0CF093
P 7900 2300
F 0 "L?" H 7856 2254 50  0000 R CNN
F 1 "L" H 7856 2345 50  0000 R CNN
F 2 "" H 7900 2300 50  0001 C CNN
F 3 "~" H 7900 2300 50  0001 C CNN
	1    7900 2300
	-1   0    0    1   
$EndComp
$Comp
L Device:L L?
U 1 1 5E0FBC7D
P 7900 2650
F 0 "L?" H 7856 2604 50  0000 R CNN
F 1 "L" H 7856 2695 50  0000 R CNN
F 2 "" H 7900 2650 50  0001 C CNN
F 3 "~" H 7900 2650 50  0001 C CNN
	1    7900 2650
	-1   0    0    1   
$EndComp
$Comp
L Device:L L?
U 1 1 5E0FD279
P 7900 3000
F 0 "L?" H 7856 2954 50  0000 R CNN
F 1 "L" H 7856 3045 50  0000 R CNN
F 2 "" H 7900 3000 50  0001 C CNN
F 3 "~" H 7900 3000 50  0001 C CNN
	1    7900 3000
	-1   0    0    1   
$EndComp
Wire Notes Line
	7800 2750 7850 2750
Wire Notes Line
	7850 2200 7800 2200
Wire Notes Line
	7850 2750 7850 2200
Wire Notes Line
	7800 2200 7800 2750
Text GLabel 8100 2500 2    50   Input ~ 0
zheng_xian_bo
Text GLabel 8100 2150 2    50   Input ~ 0
chuan_gan_qi
Text GLabel 8100 2850 2    50   Input ~ 0
chuan_gan_qi_1
Wire Wire Line
	8100 2150 7900 2150
Wire Wire Line
	8100 2500 7900 2500
Wire Wire Line
	8100 2850 7900 2850
Wire Wire Line
	8100 2450 8100 2400
Wire Wire Line
	8100 2400 8800 2400
Wire Wire Line
	8800 2400 8800 2750
Wire Wire Line
	7900 2450 8100 2450
Wire Wire Line
	8100 2800 8100 2750
Wire Wire Line
	7900 2800 8100 2800
Wire Wire Line
	8100 2750 8800 2750
Connection ~ 8800 2750
Wire Wire Line
	8800 2750 8800 3150
Wire Wire Line
	7900 3150 8800 3150
Connection ~ 8800 3150
Wire Wire Line
	8800 3150 8800 3250
$Comp
L power:GND #PWR?
U 1 1 5E380494
P 8800 3250
F 0 "#PWR?" H 8800 3000 50  0001 C CNN
F 1 "GND" H 8805 3077 50  0000 C CNN
F 2 "" H 8800 3250 50  0001 C CNN
F 3 "" H 8800 3250 50  0001 C CNN
	1    8800 3250
	1    0    0    -1  
$EndComp
Wire Notes Line
	6950 1750 9550 1750
Wire Notes Line
	9550 1750 9550 3950
Wire Notes Line
	9550 3950 6950 3950
Wire Notes Line
	6950 3950 6950 1750
Text Notes 7050 1900 0    50   ~ 0
chuan_gan_qi
$Comp
L Device:R R?
U 1 1 5E3BE160
P 10350 5900
F 0 "R?" H 10420 5946 50  0000 L CNN
F 1 "200" H 10420 5855 50  0000 L CNN
F 2 "" V 10280 5900 50  0001 C CNN
F 3 "~" H 10350 5900 50  0001 C CNN
	1    10350 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	10350 6050 10350 6200
Wire Wire Line
	10350 6200 10300 6200
Wire Wire Line
	10350 5750 10350 5350
Wire Wire Line
	10350 5350 10100 5350
Connection ~ 10100 5350
Wire Wire Line
	10100 5350 10100 5550
Wire Wire Line
	10100 4500 10100 5200
Connection ~ 10100 5200
Wire Wire Line
	10100 5200 10100 5350
$EndSCHEMATC
