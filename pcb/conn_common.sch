EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 2
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text GLabel 1550 1250 2    50   Input ~ 0
NPX_DATA
Wire Wire Line
	1550 1250 1450 1250
$Comp
L power:VCC #PWR039
U 1 1 619B59BF
P 1550 1350
F 0 "#PWR039" H 1550 1200 50  0001 C CNN
F 1 "VCC" V 1565 1478 50  0000 L CNN
F 2 "" H 1550 1350 50  0001 C CNN
F 3 "" H 1550 1350 50  0001 C CNN
	1    1550 1350
	0    1    1    0   
$EndComp
Wire Wire Line
	1550 1350 1450 1350
$Comp
L power:GND #PWR040
U 1 1 619B8152
P 1550 1450
F 0 "#PWR040" H 1550 1200 50  0001 C CNN
F 1 "GND" V 1555 1322 50  0000 R CNN
F 2 "" H 1550 1450 50  0001 C CNN
F 3 "" H 1550 1450 50  0001 C CNN
	1    1550 1450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1550 1450 1450 1450
Text Notes 700  950  0    118  ~ 24
Neopixel Connector
$Comp
L Connector_Generic:Conn_01x04 JHI1
U 1 1 619B9CA3
P 1250 2500
F 0 "JHI1" H 1168 2817 50  0000 C CNN
F 1 "Conn_01x04" H 1168 2726 50  0000 C CNN
F 2 "Gigahawk:JST_SH_SM04B-SRSS-TB_1x04-1MP_P1.00mm_Horizontal" H 1250 2500 50  0001 C CNN
F 3 "https://www.jst-mfg.com/product/pdf/eng/eSR.pdf" H 1250 2500 50  0001 C CNN
F 4 "SM04B-SRSS-TB" H 1250 2500 50  0001 C CNN "Digikey"
	1    1250 2500
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x03 JNPX1
U 1 1 619BB416
P 1250 1350
F 0 "JNPX1" H 1168 1667 50  0000 C CNN
F 1 "Conn_01x03" H 1168 1576 50  0000 C CNN
F 2 "Gigahawk:JST_PH_S3B-PH-SM4-TB_1x03-1MP_P2.00mm_Horizontal" H 1250 1350 50  0001 C CNN
F 3 "https://www.jst-mfg.com/product/pdf/eng/ePH.pdf" H 1250 1350 50  0001 C CNN
F 4 "455-1750-1-ND" H 1250 1350 50  0001 C CNN "Digikey"
	1    1250 1350
	-1   0    0    -1  
$EndComp
Text Notes 700  2100 0    118  ~ 24
Handle Interconnect
$Comp
L power:GND #PWR041
U 1 1 619BE6D7
P 1550 2400
F 0 "#PWR041" H 1550 2150 50  0001 C CNN
F 1 "GND" V 1555 2272 50  0000 R CNN
F 2 "" H 1550 2400 50  0001 C CNN
F 3 "" H 1550 2400 50  0001 C CNN
	1    1550 2400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1450 2400 1550 2400
$Comp
L power:VCC #PWR042
U 1 1 619BF4B2
P 1550 2500
F 0 "#PWR042" H 1550 2350 50  0001 C CNN
F 1 "VCC" V 1565 2628 50  0000 L CNN
F 2 "" H 1550 2500 50  0001 C CNN
F 3 "" H 1550 2500 50  0001 C CNN
	1    1550 2500
	0    1    1    0   
$EndComp
Wire Wire Line
	1550 2500 1450 2500
Text GLabel 1550 2600 2    50   Input ~ 0
IC_BTN_LED
Wire Wire Line
	1550 2600 1450 2600
Text GLabel 1550 2700 2    50   Input ~ 0
IC_BTN_SW
Wire Wire Line
	1550 2700 1450 2700
$Comp
L Connector_Generic:Conn_01x04 JBC1
U 1 1 619C0EF5
P 1250 3600
F 0 "JBC1" H 1168 3917 50  0000 C CNN
F 1 "Conn_01x04" H 1168 3826 50  0000 C CNN
F 2 "Gigahawk:JST_SH_SM04B-SRSS-TB_1x04-1MP_P1.00mm_Horizontal" H 1250 3600 50  0001 C CNN
F 3 "https://www.jst-mfg.com/product/pdf/eng/eSR.pdf" H 1250 3600 50  0001 C CNN
F 4 "SM04B-SRSS-TB" H 1250 3600 50  0001 C CNN "Digikey"
	1    1250 3600
	-1   0    0    -1  
$EndComp
Text Notes 700  3200 0    118  ~ 24
Button Connector
Text GLabel 1550 3500 2    50   Input ~ 0
BTN+
Wire Wire Line
	1550 3500 1450 3500
Text GLabel 1550 3600 2    50   Input ~ 0
BTN-
Text GLabel 1550 3700 2    50   Input ~ 0
LED+
Text GLabel 1550 3800 2    50   Input ~ 0
LED-
Wire Wire Line
	1450 3600 1550 3600
Wire Wire Line
	1450 3700 1550 3700
Wire Wire Line
	1450 3800 1550 3800
Text Notes 1850 3800 0    50   ~ 0
Vf = 2.8V
Text Notes 3050 950  0    118  ~ 24
Mounting Holes
$Comp
L Mechanical:MountingHole H1
U 1 1 61A85C5A
P 3350 1150
F 0 "H1" H 3450 1196 50  0000 L CNN
F 1 "MountingHole" H 3450 1105 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.7mm_M2.5" H 3350 1150 50  0001 C CNN
F 3 "~" H 3350 1150 50  0001 C CNN
F 4 "(3, 3)" H 3550 1200 50  0000 L CNN "Location"
	1    3350 1150
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 61A86BA6
P 3350 1350
F 0 "H2" H 3450 1396 50  0000 L CNN
F 1 "MountingHole" H 3450 1305 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.7mm_M2.5" H 3350 1350 50  0001 C CNN
F 3 "~" H 3350 1350 50  0001 C CNN
F 4 "(3, 32)" H 3550 1400 50  0000 L CNN "Location"
	1    3350 1350
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H3
U 1 1 61A86E72
P 3350 1550
F 0 "H3" H 3450 1596 50  0000 L CNN
F 1 "MountingHole" H 3450 1505 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.7mm_M2.5" H 3350 1550 50  0001 C CNN
F 3 "~" H 3350 1550 50  0001 C CNN
F 4 "(97, 32)" H 3550 1600 50  0000 L CNN "Location"
	1    3350 1550
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H4
U 1 1 61A8732B
P 3350 1750
F 0 "H4" H 3450 1796 50  0000 L CNN
F 1 "MountingHole" H 3450 1705 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.7mm_M2.5" H 3350 1750 50  0001 C CNN
F 3 "~" H 3350 1750 50  0001 C CNN
F 4 "(97, 3)" H 3550 1800 50  0000 L CNN "Location"
	1    3350 1750
	1    0    0    -1  
$EndComp
$Comp
L Graphic:Logo_Open_Hardware_Small LOGO1
U 1 1 6195747A
P 10700 950
F 0 "LOGO1" H 10700 1225 50  0001 C CNN
F 1 "Logo_Open_Hardware_Small" H 10700 725 50  0001 C CNN
F 2 "Symbol:OSHW-Logo_5.7x6mm_SilkScreen" H 10700 950 50  0001 C CNN
F 3 "~" H 10700 950 50  0001 C CNN
	1    10700 950 
	1    0    0    -1  
$EndComp
$EndSCHEMATC
