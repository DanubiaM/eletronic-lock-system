
#include <16F877A.h>
#device ADC=8

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES HS 

#use delay(crystal=20000000)
#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8,stream=Wireless)


// -------Variables' Declaration
#define BLOCK_SIZE sizeof(User) 
#define RX_BUFFER_SIZE 15
int8 rx_wr_index = 0;
int8 lock_pos = 0, rxd, read, valid_data_count;
int data_avail = FALSE, got_id = FALSE;
unsigned int8 rx_buffer[RX_BUFFER_SIZE];
char string [RX_BUFFER_SIZE];
#include "functions.c"

// ---- MSG from serial communication
#int_RDA
void RDA_isr(void){
   rx_buffer[rx_wr_index] = getc();
   string[rx_wr_index] = rx_buffer[rx_wr_index];
   rxd = rx_buffer[rx_wr_index];
   rx_wr_index++;

   if(rx_wr_index > RX_BUFFER_SIZE){
      rx_wr_index = 0;
   }

   //Look for unique ID: "IFMT"
   if(rxd == 'I' && lock_pos == 0){
      lock_pos++;
   }
   else if(rxd == 'F' && lock_pos == 1){
      lock_pos++;
   }
   else if(rxd == 'M' && lock_pos == 2){
      lock_pos++;
   }
   else if(rxd == 'T' && lock_pos == 3){
      lock_pos=0; //Reset the "combination lock"
      got_id = TRUE;
      read = rxd;
      //get ready to count the number of data bytes
      valid_data_count = 0; 

      //buffer is reset to index 0
      rx_wr_index = 0;
   }else {
      lock_pos = 0;
   }

   if(got_id && valid_data_count++ >= BLOCK_SIZE){
      data_avail = TRUE;
      got_id = FALSE;
   }
   
}




// #int_TIMER1
// void TIMER1_isr(void)
// {
// }

// #int_RTCC
// void RTCC_isr(void)
// {

      
// }

void main()
{
   //VARIAVEIS

   // setup_timer_0(RTCC_INTERNAL|RTCC_DIV_256|RTCC_8_bit);      //13.1ms overflow
   // setup_timer_1(T1_INTERNAL|T1_DIV_BY_8); //Overflow in 104ms | Resolution 1.6 us
   init_ext_eeprom();
   // enable_interrupts(INT_TIMER0);
   // enable_interrupts(INT_TIMER1);
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);

   lcd_ini();
   delay_us(50);

   printf(lcd_escreve, "\f  iniciando... ");
   delay_ms(500);

   printf(lcd_escreve, "\fIFMT - Serial");
   delay_ms(500);

   // resetmemory();

   // int id [2] = {12,34};
   // int pass [4] = {1,2,3,4};
   // saveuser(id, pass, 1);
   // int id1 [2] = {14,0};
   // saveuser(id1, pass, 0);
   // int id2 [2] = {70,10};
   // saveuser(id2, pass, 1);
   // int id3 [2] = {0,10};
   // saveuser(id3, pass, 1);
   // int id4 [2] = {99,99};
   // saveuser(id4, pass, 3);//admin
   
   
   // unsigned int * temp;
   // unsigned int id [2];
   // temp = inputId();
   // id[0] = temp[0];
   // id[1] = temp[1];
   // login(id);

   while(true){
      if(data_avail){
         output_high(PIN_D3);
         data_avail = FALSE;
         receiveClient();
      }
   }


   // unsigned char option; unsigned int * temp;
   // unsigned int id [2];
   // int status;
   // do{
   //    printf(lcd_escreve,"\f1:Login|2:Admin");
   //    delay_ms(500);
   //    option = readKeyboard();

   //    if(option != 255){
   //       printf(lcd_escreve,"\r\n Option: %c", option);
   //       delay_ms(500);

   //       switch(option){
   //          case '1':
   //             temp = inputId();
   //             id[0] = temp[0];
   //             id[1] = temp[1];
   //             status = login(id);
   //             if(status == 1 || status == 3){
   //                printf(lcd_escreve,"\fBem Vindo(a)!");
   //                delay_ms(1000);
   //                printf(lcd_escreve,"\fLiga Led e Rele");
   //                delay_ms(500);
   //             }else{//Unpaid
   //                printf(lcd_escreve,"\fConta Existe");
   //                printf(lcd_escreve,"\r\r,Mas Falta Pagar!");
   //                delay_ms(1000);
   //             }
   //             break;
   //          case '2':
   //             temp = inputId();
   //             id[0] = temp[0];
   //             id[1] = temp[1];
   //             status = login(id);
   //             if(status == 3){
   //                adminMenu();
   //             }
   //             else{
   //                printf(lcd_escreve,"\fN Permitido");
   //                delay_ms(500);
   //             }
   //             break;
   //          default:
   //             printf(lcd_escreve,"\fDigite um valor");
   //             printf(lcd_escreve,"\r\nValido!");
   //             delay_ms(500);
   //             break;
   //       }
   //    }


   // }while(option != '5');

}

