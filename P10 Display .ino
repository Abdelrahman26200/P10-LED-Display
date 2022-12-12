#include"STD_TYPES.h"
#include <SPI.h>
#include <DMD.h>
#include <TimerOne.h>
#include "SystemFont5x7.h"
#include "Arial_black_16.h"

#define ROW 1
#define COLUMN 1
#define FONT Arial_Black_16
#define BOT1 2
#define BOT2 3
DMD led_module(ROW, COLUMN);


void scan_module()
{
  led_module.scanDisplayBySPI();
}

void setup() {
  Timer1.initialize(2000);
  Timer1.attachInterrupt(scan_module);
  led_module.clearScreen( true );
  
pinMode(BOT1,INPUT);
pinMode(BOT2,INPUT);

}

u32 num_counter = 0;
u8 counter =0 ;
void loop() {
   led_module.selectFont(FONT);
    led_module.drawChar(2,0,(48),GRAPHICS_NORMAL);
    led_module.drawChar(12,0,(48),GRAPHICS_NORMAL);
    led_module.drawChar(22,0,(48),GRAPHICS_NORMAL);
   if(digitalRead(BOT1) == true )  /*Countup from 0 until  Bot1 get pressed */
   {
    delay(250);
    while(digitalRead(BOT1) == true);    
      num_counter =1;    
    do
    { 
      led_module.clearScreen( true );
      LEDM_VidWriteNum(num_counter);
      num_counter++ ;
      delay(1000);
     
     }while(digitalRead(BOT1) != true  && num_counter < 999);
    if(num_counter >= 999)
    {
      led_module.clearScreen( true );
      do{
      led_module.drawString(2, 0, "999",5,GRAPHICS_NORMAL);
      delay(1000);
      led_module.clearScreen( true );
      delay(1000);
      }while(digitalRead(BOT1) != true);
    }
    delay(250);
    while(digitalRead(BOT1) == true)
      {
        delay(1);
      }
    delay(1200);
      while(digitalRead(BOT1) != true && digitalRead(BOT2) != true)
      {
        delay(1);
      }
      if(digitalRead(BOT2) == true)
      {
       led_module.clearScreen( true );
      LEDM_VidWriteNum(counter);
      delay(5000);
      led_module.clearScreen( true );
      }
      else
      {
         led_module.clearScreen( true );
         led_module.drawChar(2,0,(48),GRAPHICS_NORMAL);
         led_module.drawChar(12,0,(48),GRAPHICS_NORMAL);
         led_module.drawChar(22,0,(48),GRAPHICS_NORMAL);
      }
      delay(250);
    while(digitalRead(BOT1) == true);
             counter ++;
       }
   

    else if(digitalRead(BOT2) == true )  /*Show counter on LED matrix */
   {
      led_module.clearScreen( true );
      LEDM_VidWriteNum(counter);
      delay(5000);
      led_module.clearScreen( true );

    }
   }


void LEDM_VidWriteNum(s32 Copy_s32Number)
{
  s32 Local_s32Variable;
  u32 Local_u32Divider=10;
  u8 Local_u8Iterator=0,X,c,S;
  if(Copy_s32Number == 0)
  {
    led_module.drawChar(11,0,(48),GRAPHICS_NORMAL);
    return ; 
  }
  Local_s32Variable =Copy_s32Number;
  while(Local_s32Variable != 0)
  {
    Local_s32Variable/=Local_u32Divider;
    Local_u8Iterator++;
  }
  for(u8 i=Local_u8Iterator ; i>0 ; i--)
  {
    Local_s32Variable = Copy_s32Number;
    Local_u32Divider=1;
    
    for(u8 k=(i-1) ; k>0 ; k--)
    {
      Local_u32Divider*=10;
    }
    Local_s32Variable/=Local_u32Divider;
    Copy_s32Number-=(Local_s32Variable*Local_u32Divider);
    
    
   
    if(Local_u8Iterator == 3)
    {X = 2;c=8;S=2; }
    
    else if(Local_u8Iterator == 2)
    {
    X = 2;c=8;S=12;
    led_module.drawChar(2,0,(48),GRAPHICS_NORMAL);
    }
    
    else if(Local_u8Iterator == 1)
    {
    X = 2;c=8;S=22;
    led_module.drawChar(2,0,(48),GRAPHICS_NORMAL);
    led_module.drawChar(12,0,(48),GRAPHICS_NORMAL);
    }
    led_module.drawChar((S+(X+c)*(Local_u8Iterator-i)),0,(48+Local_s32Variable),GRAPHICS_NORMAL);
    }
    
   
 
  
  }
  
