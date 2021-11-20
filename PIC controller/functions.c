#include "functions.h"

typedef struct { 
   int id[2];
   int pass[4]; //password
   int status; //0 - Unpaid, 1 - Paid, 3 - Admin
}User;

#include <stdlib.h>
#include <string.h>


void saveUser(int * id, int * pass, int status){
   printf (lcd_escreve,"\r\nid[0]:%u",id[0]);
   delay_ms(1000);
   if( id[0] < 256 && id[1] < 256 && getAddressByID(id) > -1 ){
      int address = lastNewUserPosition();
      //recebe os parâmetros do usuário
      User user;
      user.id[0] = id[0];
      user.id[1] = id[1];
      user.pass[0] = pass[0];
      user.pass[1] = pass[1];
      user.pass[2] = pass[2];
      user.pass[3] = pass[3];
      user.status = status;
      

      //Corrigir isso, o endereço tem que ser "dinâmico"
      
      write_ext_eeprom(address, user.id[0]);
      write_ext_eeprom(address+1, user.id[1]);
      write_ext_eeprom(address+2, user.pass[0]);
      write_ext_eeprom(address+3, user.pass[1]);
      write_ext_eeprom(address+4, user.pass[2]);
      write_ext_eeprom(address+5, user.pass[3]);       
      write_ext_eeprom(address+6, user.status);
   

      printf (lcd_escreve,"\fUsuario Cadastrado");
      delay_ms(500);

   }else{
      printf (lcd_escreve,"\fID incompativel");
      printf (lcd_escreve,"\r\nTente novamente");
      delay_ms(1000);

   }
}

void printUser(){
   //delay_ms(50);
   int tmp_result = read_ext_eeprom(0);  
   
   delay_ms(50);  
   
   printf (lcd_escreve,"\f Button: %d", tmp_result);
   printf(lcd_escreve, "\r\nPw:%d%d%d%d St:%d %d", read_ext_eeprom(1), read_ext_eeprom(2), read_ext_eeprom(3), read_ext_eeprom(4), read_ext_eeprom(5), read_ext_eeprom(6));
   
   //printf(lcd_escreve, "\f Client () else´{}{}
   // printf(lcd_escreve, "\r\nPw:%c%c%c%c St:%c %c", U1.pass[0], U1.pass[1], U1.pass[2], U1.pass[3], U1.status, U1.type_usr);
}

int getAddressByID(int * id){
   int id_temp[2];
   int address = 0;
   
   while( read_ext_eeprom(address) != -1){
      id_temp[0] = read_ext_eeprom(address);
      id_temp[1] = read_ext_eeprom(address+1);
      
      if (id_temp[0] == id[0] && id_temp[1] == id[1]){
         printf (lcd_escreve,"\fID Encontrado:%u%u", id_temp[0],id_temp[1]);
         delay_ms(1000);
         return address;
      }

      address += BLOCK_SIZE; 
   }
   printf (lcd_escreve,"\f ID N Encontrado");
   return -1;
   
}

void erase_program_eeprom(int addrr){
   for(int i=0; i < BLOCK_SIZE; i++){
         write_ext_eeprom(addrr + i, -1);
   }  
   printf (lcd_escreve,"\f User erased ");
   delay_ms(500);
}

int deleteUser(int8 address){
   
   int data_temp;
   int previous_block = address;
   int next_block = address + BLOCK_SIZE;

   //Case 1: without next block
   if (read_ext_eeprom(next_block) == -1){
      erase_program_eeprom(previous_block);      
      return 1;
   }

   //Case 2: Check whether the data in the address is empty
   while(read_ext_eeprom(next_block) != -1){
      //data_temp[index] = read_ext_eeprom(address);
      for(int i=0; i < BLOCK_SIZE; i++){
         data_temp = read_ext_eeprom(next_block + i);           
         write_ext_eeprom(previous_block + i, data_temp);    //overwrite delete block
      }  

      previous_block = next_block;
      next_block += BLOCK_SIZE;
   }
   
   next_block -= BLOCK_SIZE;
   
   //Erase last block  
   erase_program_eeprom(next_block);
   
   return 1;

}

int lastNewUserPosition(){
   int address = 0;
   int id_temp;

   while( read_ext_eeprom(address) != -1){
      address += BLOCK_SIZE; 
   }
   printf (lcd_escreve,"\fAddress: %d", address);
   delay_ms(1000);
   
   return address;

}

int isIdAvailable(int * id){
   unsigned int address = 0;
   int id_temp;
   while( read_ext_eeprom(address) != -1){
      id_temp = read_ext_eeprom(address);
      if (id_temp == id){
          printf (lcd_escreve,"\fID:%u, Existe", id_temp);
          delay_ms(1000);
         return 0;//Sucessful
      }

      address += BLOCK_SIZE; 
   }
   printf (lcd_escreve,"\fID:%u, N Existe", id_temp);
   delay_ms(1000);
   return -1;
}

void resetMemory(){
   int address = 0;
   for(; read_ext_eeprom(address) != -1;
    erase_program_eeprom(address), address += BLOCK_SIZE);
}

void adminMenu(){


  unsigned char keyboard_buffer[BLOCK_SIZE * 2];
  unsigned char option;
   // printf(lcd_escreve,"\f1: CAD Cliente ");
   // delay_ms(500);
   // printf(lcd_escreve,"\r\n2: DEL Cliente");
   // delay_ms(500);
   // printf(lcd_escreve,"\f3: Buscar Cliente ");
   // delay_ms(500);
   // printf(lcd_escreve,"\r\n4: Editar Cliente");
   // delay_ms(500);
   // printf(lcd_escreve,"\f5: SAIR do Menu ");
   // delay_ms(500);
  do{
    
     option = readKeyboard();
     printf(lcd_escreve,"\f Option: %c", option);
     delay_ms(500);


    switch(option){
       case '1':
         unsigned int * temp;
         unsigned int pass[4];
         int * id;
         unsigned int status;
         int i = 0;
           //The user needs to type 4 digits
           //For example, even if it's just 9
           //He/she will type: 0009
           while(i < 5){

            printf(lcd_escreve,"\fDigite o ID");
            delay_ms(50);
            option = readKeyboard();
            printf(lcd_escreve,"\fTyped ID:%c", option);
            delay_ms(500);
            if(option != 255){
               if(i == 2){
                  //To convert to int will be easier with space between them
                  keyboard_buffer[i] = ' ';
                  i++;
               }
               keyboard_buffer[i] = option;
               i++;
            }
           }
            // unsigned char *id;
            // id = keyboard_buffer;
            id = strToInt(keyboard_buffer);
            //https://www.tutorialspoint.com/cprogramming/c_pointer_to_an_array.htm
            //*(id+1) == id[1]
            printf(lcd_escreve,"\fid: %u%u",id[0],id[1]);
            delay_ms(1000);
      
         //password

         i = 0;
           while(i < 4){

            printf(lcd_escreve,"\fDigite a senha");
            delay_ms(50);
            option = readKeyboard();
            printf(lcd_escreve,"\fTyped Pass:%c", option);
            delay_ms(500);
            if(option != 255){
               // keyboard_buffer[i] = option;
               unsigned char destination[2];
               //Convert string from char and return 
               //to the left array of char(str_pass)
               strfromchar(destination,option);
               temp = strToInt(destination);
               pass[i] = temp[0];
               i++;
            }
           }
            printf(lcd_escreve,"\fPASS(4): %u%u%u%u",pass[0],pass[1],pass[2],pass[3]);
            delay_ms(1000);


         i = 0;
           while(i < 1){

            printf(lcd_escreve,"\fStatus(0,1,3):");
            delay_ms(50);
            option = readKeyboard();
            printf(lcd_escreve,"\fTyped Status:%c", option);
            delay_ms(500);
            if(option != 255){
               unsigned char destination[2];
               strfromchar(destination,option);
               temp = strToInt(destination);
               status = temp[0]; 
               i++;
            }
           }
            printf(lcd_escreve,"\fSTATUS: %u",status);
            delay_ms(1000);


            saveUser(id,pass,status);
            break;
       case 2:
            // listar();
            break;
       case 3:
            // mostrarMes();
            break;
       case 4:
            //  printf("\nTENHA UM BOM DIA\n");
            break;
       default:
            // printf("\nDIGITE UM VALOR VÁLIDO\n");
            break;

      }
   }while(option != 4);//só termina quando for 4 
   
 

   
}

unsigned char readKeyboard(){
   unsigned char tmp;
   unsigned char tmp_result;
   
   tmp = tc_tecla(1500); // ms
   if(tmp != 255){
      // write_ext_eeprom(0, tmp);
      // delay_ms(50);
      // tmp_result = read_ext_eeprom(0);
      // delay_ms(50);
      // tmp_result = tmp;
      // printf(lcd_escreve,"\f Button: %c", tmp);
      // delay_ms(50);
   }else{ 
      printf(lcd_escreve,"\f   TECLADO  ");
   }

   return tmp;
}


int * getAdminsID(){

   int address = 0;
   int temp_status;
   int index= 0;
   static int admins[BLOCK_SIZE];
   admins[0] = -1;
   while( read_ext_eeprom(address) != -1){
      temp_status = read_ext_eeprom(address + (BLOCK_SIZE - 1));//status of the user
      if (temp_status == 3){
         printf (lcd_escreve,"\fAdmin Encontrado");
         delay_ms(1000);
         for(int i=0; i < 2; i++){
            int id = read_ext_eeprom(address+i);   
            admins[index] = id;
            index++;
         }

      }

      address += BLOCK_SIZE; 
   }

   return admins;

}

void listAdmins(){
   int * admins;

   admins = getAdminsID();
   printf(lcd_escreve,"\f admins[0]: %d", admins[0]);
   delay_ms(1000);
   if(admins[0] != -1){
      for (int16 i=0; i < sizeof(admins); i+=2){
         printf(lcd_escreve, "\fid~:%u%u",admins[i], admins[i+1]);
         delay_ms(1000);
      } 
   }
}


int * strToInt(char * str){

  char *p = str;
  //https://flaviocopes.com/c-array-length/
//   int size = (sizeof str) / (sizeof * str);
  static unsigned int buffer[BLOCK_SIZE];  
  printf(lcd_escreve,"\fParsing:%s",p );
  delay_ms(1000);
  char * end;
  int index = 0;

  for (unsigned long number = strtoul(p, &end, 10);
        p != end;
        number = strtoul(p, &end, 10))
  {
    printf(lcd_escreve,"\n%lu",number );
    delay_ms(700);
    p = end;

    buffer[index] =  (int) number; 
    index++;
  }

   return buffer;
}

char * strfromchar(char destination[], char source) 
{ 
   destination[0] = source;   // copy the character into the string 
   destination[1] = '\0';      // null-terminate the string 
 
   return destination;         // common convention for str functions 
} 