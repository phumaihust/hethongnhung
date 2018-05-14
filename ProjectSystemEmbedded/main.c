#include <main.h>
#include <math.h>

int pin1_status = 0;
int1 is_updated = 1;

#include "esp8266.c"

unsigned char rx_data;


unsigned int16 temp_count = 1000;
int16 lux;
unsigned char temp0,temp1,temp2,temp3;



//#include "lcd.h"

#define LED1_PIN        PIN_B4
#define LED2_PIN        PIN_B5
#define LED3_PIN        PIN_B6

#define BUT1_PIN        PIN_D1
#define BUT2_PIN        PIN_D0
#define BUT3_PIN        PIN_C2


unsigned char str[5];
//unsigned char i = 0;

const char buf1[]={"<head><meta HTTP-EQUIV=\"refresh\" CONTENT=\"10;url=http://192.168.137.250/\"><title>title</title></head><h1 align=\"center\"></h1><h1 align=\"center\"><font face=\"Times new roman\" size=\"6\" >BTL THIET KE HE THONG NHUNG</font></h1>"};
const char buf2[]={"<h1 align=\"center\"><font face=\"Times new roman\" size=\"6\" >Mai Phu, Hoang Viet, Van Tho"};
const char buf3[]={"<p align=\"center\"><font size=\"6\" color=\"black \">DEN</font></p>"};
const char buf_TAT[]= {"<p align=\"center\" width =\"150\"><a href=\"?pin=TAT \"><button><font size=\"6\" color=\"green\" >TAT</font></button></a>"};//&nbsp;<a href=\"?pin=LV1\"><button><font size=\"6\">MUC 1</font></button></a>&nbsp;<a href=\"?pin=LV2\"><button><font size=\"6\">MUC 2</font></button></a><font size=\"6\">" };
const char buf_MUC1[]={"<p align=\"center\" width =\"150\"><a href=\"?pin=MUC1 \"><button><font size=\"6\" color=\"green\" >MUC 1</font></button></a>"};
const char buf_MUC2[]={"<p align=\"center\" width =\"150\"><a href=\"?pin=MUC2 \"><button><font size=\"6\" color=\"green\" >MUC 2</font></button></a>"};

const char buf_temp1[]={"<p align=\"center\"><font size=\"6\" color=\"black \">Do roi: "};
const char buf_temp2[] = {" lux p>"};

const char status_on1[]= {"<svg height=\"100\" width=\"100\"><circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"black\" stroke-width=\"4\" fill=\"lime  \" /></svg></font></p>"};
const char status_on2[]= {"<svg height=\"100\" width=\"100\"><circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"black\" stroke-width=\"4\" fill=\"red   \" /></svg></font></p>"};
const char status_off[]= {"<svg height=\"100\" width=\"100\"><circle cx=\"50\" cy=\"50\" r=\"40\" stroke=\"black\" stroke-width=\"4\" fill=\"silver\" /></svg></font></p>"};

unsigned int16 word_number;

//!unsigned char ssid[] = "TP-LINK_6B50";
//!unsigned char pass[] = "41633465";
//!unsigned char ip_address[] = "192.168.0.123";
unsigned char ssid[] = "Windows Phone0559";
unsigned char pass[] ="12345679";
unsigned char ip_address[] = "192.168.137.250";


unsigned int16 count_web_word_number()
{
   unsigned int16 i = 0, word_count = 0;
 
   while (buf1[i] != '\0')
   {
      if (buf1[i] != '\\')
      {
         word_count++;
         i++;
      }
   }
   
   i = 0;
   while (buf2[i] != '\0')
   {
      if (buf2[i] != '\\')
      {
         word_count++;
         i++;
      }
   }
   
      i = 0;
   while (buf3[i] != '\0')
   {
      if (buf3[i] != '\\')
      {
         word_count++;
         i++;
      }
   }
   
   
   i = 0;
   while (buf_TAT[i] != '\0')
   {
      if (buf_TAT[i] != '\\')
      {
         word_count++;
         i++;
      }
   }
   
      i = 0;
   while (buf_MUC1[i] != '\0')
   {
      if (buf_MUC1[i] != '\\')
      {
         word_count++;
         i++;
      }
   }
   
      i = 0;
   while (buf_MUC2[i] != '\0')
   {
      if (buf_MUC2[i] != '\\')
      {
         word_count++;
         i++;
      }
   }
   
      i = 0;
      while (status_off[i] != '\0')
      {
         if (status_off[i] != '\\')
         {
            word_count++;
            i++;
         }
      }
   
   i = 0;
   while (buf_temp1[i] != '\0')
   {
      if (buf_temp1[i] != '\\')
      {
         word_count++;
         i++;
      }
   }
   
   word_count += 2;
   i = 0;
   while (buf_temp2[i] != '\0')
   {
      if (buf_temp2[i] != '\\')
      {
         word_count++;
         i++;
      }
   }
      
   return word_count;
   
}

void show_web()
{
   if (start_CONNECT == 1)
   {
      ESP8266_CIPSEND(id_connect, word_number);
      delay_ms(100);
      
      fprintf(ESP_STR, buf1);
      fprintf(ESP_STR, buf2);
      fprintf(ESP_STR, buf3);
      
      if (pin1_status == 0)
         fprintf(ESP_STR, status_off);
      else if (pin1_status == 1)
         fprintf(ESP_STR, status_on1);
      else if (pin1_status == 2)
         fprintf(ESP_STR, status_on2);
      fprintf(ESP_STR, buf_TAT);
      fprintf(ESP_STR, buf_MUC1);
      fprintf(ESP_STR, buf_MUC2);
      
      
      
         
      fprintf(ESP_STR, buf_temp1);
     // sprintf(str, "%2u", );
      sprintf(str, "%u", temp0);
      fprintf(ESP_STR, str);
      sprintf(str, "%u", temp1);
      fprintf(ESP_STR, str);
      sprintf(str, "%u", temp2);
      fprintf(ESP_STR, str);
      sprintf(str, "%u", temp3);
      fprintf(ESP_STR, str);
      fprintf(ESP_STR, buf_temp2);
   }
   start_CONNECT = 0;
   
   ESP8266_clearBuffer();
}
void main()
{

     int16 GiaTriADC;
         float Tam;
         int32 DienTro;
         int16 j;
         int32 Tong;
//   lcd_init();
//   lcd_clear();
   
//   lcd_gotoxy(1,1);
//   printf(lcd_putc,"HE THONG NHUNG");
   
         
    
   output_float(BUT1_PIN);
   output_float(BUT2_PIN);
   
   output_high(LED1_PIN);
   output_high(LED2_PIN);
   output_high(LED3_PIN);
   
   
   //Khoi tao ngat UART ben RX
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
   
   //Dem so word cua code html web
   word_number = count_web_word_number();
   
   delay_ms(1000);
   
   ESP8266_AT();
   delay_ms(100);
   
   ESP8266_RST();
   delay_ms(100);
   
   ESP8266_CWMODE(3);
   delay_ms(100);
   
   ESP8266_CWJAP(ssid, pass);
   delay_ms(500);
   
   ESP8266_CIPSTA(ip_address);
   delay_ms(500);
   
   ESP8266_CIPMUX(1);
   delay_ms(200);
   
   ESP8266_CIPSERVER(1,80);
   delay_ms(100);
   
   ESP8266_CIPSTO(1);
   delay_ms(100);
   
   ESP8266_clearBuffer();
   delay_ms(100);

   setup_adc(ADC_CLOCK_INTERNAL);
   setup_adc_ports(AN0_AN1_AN2_AN3_AN4);
   set_adc_channel(0);
   
   setup_ccp1(CCP_PWM);                   // Configure CCP1 as a PWM
  setup_ccp2(CCP_PWM);                   // Configure CCP2 as a PWM
  delay_ms(100);                         // Wait 100ms
  setup_timer_2(T2_DIV_BY_16, 255, 1);   // Set PWM frequency to 488Hz
   
   
//   lcd_clear();
   while (true)
   {
      
     Tong=0;
      for(j=1;j<=50;j++)
      {
         GiaTriADC = read_adc();   
         //Tong += GiaTriADC;
         Tong = Tong + GiaTriADC; 
         delay_us(5);
      }
      Tong = Tong/50;
      
      //Tam =  (500f*(float)Tong)/1023f;
      Tam = ((5f * (float)Tong)/1023f);
  //    lcd_gotoxy(1,1);
    //  printf(lcd_putc,"%ld/ %f", Tong,Tam);
      
      DienTro = (int32)(((15345f/(float)Tong) - 23f)*1000);// (float)giatriAdc)/1023;
      lux = (int16)(12500000f * (float)(pow((float)(DienTro),(-1.4059f)))); 
      
   //   lcd_gotoxy(1,2);
    //  printf(lcd_putc,"R: %ld/ %ld", DienTro,lux);
      
      
      
      
      
      
      temp0 = (unsigned char)(lux/1000);//1235
      temp1 = (unsigned char)((lux%1000)/100);
      temp2 = (unsigned char)(((lux%1000)%100)/10);
      temp3 = (unsigned char)((((lux%1000)%100)%10));
       
      
      
      if (!input(BUT1_PIN))
      {
         while (!input(BUT1_PIN)) {}
         
         if (pin1_status == 0)
            pin1_status = 1;
         else if (pin1_status == 1)
            pin1_status = 2;
         else if (pin1_status == 2)
            pin1_status = 0;
      }
     
   
      if (pin1_status == 0){
      output_high(LED1_PIN);
         set_pwm1_duty(0);
         is_updated == 0;
      }
         
         
      else if (pin1_status == 1){
      output_low(LED1_PIN);
         set_pwm1_duty(120);
         set_pwm2_duty(50);
         is_updated == 0;
      }
         
      else if (pin1_status == 2){
      output_low(LED1_PIN);
         set_pwm1_duty(255);
         set_pwm2_duty(20);
         is_updated == 0;
      }
         
         
      
      if (is_updated == 0)
      {
         is_updated = 1;
         show_web();
      }
      delay_ms(50);
   }
}

#INT_RDA
void int_rda_isr()
{
   clear_interrupt(INT_RDA);
   
   rx_data = getc(ESP_STR);

   ESP8266_executeBuffer(rx_data);
}
