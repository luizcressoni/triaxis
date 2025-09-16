/*! \file defines.h */

#pragma once




/*  ESP32 Pinout

                           EN -  *  MOSI GPIO23 V_SPI_D
         ADC1_0 GPIO36 SensVP -  *  SCL GPIO22 V_SPI_WP U0_RTS
         ADC1_3 GPIO39 SensVN -  *  CLK3 GPIO1 U0_TXD
                ADC1_6 GPIO34 -  *  CLK2 GPIO3 U0_RXD
                ADC1_7 GPIO35 -  *  SDA GPIO21 V_SPI_HD
  Touch9 ADC1_4 GPIO32 XTAl32 *  *  MISO GPIO19 V_SPI_Q U0_CTS
  Touch8 ADC1_5 GPIO33 XTAL32 *  *  SCK GPIO18 V_SPI_CLK
           DAC1 ADC2_8 GPIO25 *  *  GPIO5 V_SPI_CS0
           DAC2 ADC2_9 GPIO26 *  -  GPIO17 U2_TXD
         Touch7 ADC2_7 GPIO27 *  -  GPIO16 U2_TXD           
Touch6 HSPI_CLK ADC2_6 GPIO14 *  -  GPIO4 ADC2_0 HSPI_HD Touch0 
  Touch5 HSPI_Q ADC2_5 GPIO12 *  *  CS GPIO2 ADC2_2 HSPI_WP Touch2  <-- onboard LED
 Touch4 HSPI_ID ADC2_4 GPIO13 *  *  GPIO15 ADC2_3 HSPI_CS0 Touch3
                          GND -  -  GND
                          VIN -  -  3.3V



SPI:
    MOSI
    SDA
    MISO
    SCK
    CS_0

LCD:
    RS          13
    EN          12
    D4          14
    D5          27
    D6          26
    D7          25
    Contrast    15


LCD pinout
         GND -        
         Vcc -
    Contrast -
          RS -
         R/W -
           E -
          D0 -
          D1 -
          D2 -
          D3 -
          D4 -
          D5 -
          D6 -
          D7 -
        LED+ -
        LED- -
*/


#define LCD_RS          13
#define LCD_EN          12
#define LCD_D4          1
#define LCD_D5          27
#define LCD_D6          26    //mudar
#define LCD_D7          25    //mudar
#define LCD_Contrast    15

#define STEPPER_A       32
#define STEPPER_B       33
#define STEPPER_C       25
#define STEPPER_D       26




//eof defines.h