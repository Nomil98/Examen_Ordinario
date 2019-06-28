#include<18F4620.h> //Se incluye la librería del PIC 18F4620
#include <stdio.h>
#include <stdlib.h>
#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT // EL HS es el high speed
#fuses NOPBADEN, NOMCLR, STVREN, NOLVP, NODEBUG
#use delay (clock = 4000000)
#use RS232(BAUD=9600, XMIT= PIN_C6, RCV = PIN_C7, BITS = 8, PARITY = N, STOP=1, STREAM = PORT1)
#use fast_io(b)
#use fast_io(c)
#use fast_io(a)
#use fast_io(d)
int contadorA=0, contadorB=0, contadorD=0;
int anilloA=1, anilloB=1, anilloD=1;
char caracter[50];
int dato=0;
int flagdatorecibido=0, flagcontadorA=0, flagcontadorB=0, flagcontadorD=0 ;
int Contar=0;
#INT_RDA
void serial_isr(){
    if(kbhit()){
    caracter[dato]=getch();
    dato++;
    flagdatorecibido=1;
    }

}
#int_timer0
void timer0(){
   contadorA++;
   contadorB++;  
   contadorD++;
   set_timer0(100);
}

void main(){
   setup_oscillator(OSC_4MHZ);
   setup_adc_ports(NO_ANALOGS); 
   set_tris_a(0x00);
   set_tris_b(0x00);
   set_tris_c(0xff);
   set_tris_d(0x00);
   setup_timer_0(T0_INTERNAL|rtcc_div_64);
   set_timer0(100); //Esto se obtuvo con los cálculos.
   enable_interrupts(INT_TIMER0);
   enable_interrupts(int_rda);
   enable_interrupts(GLOBAL);
   
   while(1){
         if(flagdatorecibido==1){
            flagdatorecibido=0;
            printf("%c", caracter[dato-1]);
        if(caracter[dato-1]==13){
             Contar=1;
            dato= atoi(caracter);
            
            
        }
     }
     if(Contar==1){
          if((dato&0x12)>0){
             flagcontadorA=1;
             
         }
      
     }
     else{
         Contar=0;
     }
         
     if(flagcontadorA==1 && contadorA==1){
         flagcontadorA=0;
         output_a(anilloA);
         anilloA*=2;
         if(anilloA==128){
             anilloA=1;
             }         
     }
     if(contar==1){
          if((dato&0x11)>0){
             flagcontadorB=1;
     }
     
     
   }
      else{
          Contar=0;
      }
      if(flagcontadorB==1 && contadorB==3){
             flagcontadorB=0;
             output_b(anilloB);
             anilloB*=2;
             if(anilloB==256){
                 anilloB=1;
             }
     }
  }
}
