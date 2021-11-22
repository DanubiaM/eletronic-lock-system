#include "functions.h"

typedef struct { 
   int id[2];  
   int pass[4]; //password
   int status; //0 - Unpaid, 1 - Paid, 3 - Admin
}User;

#include <stdlib.h>
#include <string.h>


void saveUser(int * id, int * pass, int status){
   if( id[0] <= 99 && id[1] <= 99 && getAddressByID(id) == -1 ){
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

void updateUser(int * id, int * pass, int status, int address){
   if( id[0] <= 99 && id[1] <= 99){
      //recebe os parâmetros do usuário
      User user;
      user.id[0] = id[0];
      user.id[1] = id[1];
      user.pass[0] = pass[0];
      user.pass[1] = pass[1];
      user.pass[2] = pass[2];
      user.pass[3] = pass[3];
      user.status = status;
      
      write_ext_eeprom(address, user.id[0]);
      write_ext_eeprom(address+1, user.id[1]);
      write_ext_eeprom(address+2, user.pass[0]);
      write_ext_eeprom(address+3, user.pass[1]);
      write_ext_eeprom(address+4, user.pass[2]);
      write_ext_eeprom(address+5, user.pass[3]);       
      write_ext_eeprom(address+6, user.status);

      printf (lcd_escreve,"\fUsuario Atualizado");
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
         printf (lcd_escreve,"\fID Existe:%u%u", id_temp[0],id_temp[1]);
         delay_ms(1000);
         return address;
      }

      address += BLOCK_SIZE; 
   }
   printf (lcd_escreve,"\fID:%u%u \r\nDisponivel",id[0],id[1]);
   delay_ms(1000);
   return -1;
}

void searchUser(int * id){

   int address = getAddressByID(id);
   if(address != -1){
      printf (lcd_escreve,"\fID:%u%u",id[0],id[1]);
      int showStatus = 1;
      getUserStatus(address,showStatus);
   }else{
      printf(lcd_escreve,"\fUsuario N Existe");
      delay_ms(1000);
   }
}

void erase_program_eeprom(int addrr){
   for(int i=0; i < BLOCK_SIZE; i++){
         write_ext_eeprom(addrr + i, -1);
   }  
   printf (lcd_escreve,"\f User erased ");
   delay_ms(200);
}

int getUserStatus(int address, int show){
   int status = read_ext_eeprom(address+BLOCK_SIZE - 1);

   if(show == 1){
      char msg_status[10];
      if( status == 0){
         strcpy(msg_status,"NAO PAGO");
      }else{
         strcpy(msg_status,"PAGO");
      }
      printf (lcd_escreve,"\r\nStatus:%s",msg_status);
      delay_ms(1500);
   }
   return status;
}

int deleteUser(int * id){
   
   int address = getAddressByID(id);
   if(address == -1)
      return -1;
   int data_temp;
   int previous_block = address;
   int next_block = address + BLOCK_SIZE;

   //Case 1: without the next block
   if (read_ext_eeprom(next_block) == -1){
      erase_program_eeprom(previous_block);      
      return 1;
   }

   //Case 2: Check whether the data in the next block address is empty
   while(read_ext_eeprom(next_block) != -1){
      //data_temp[index] = read_ext_eeprom(address);
      for(int i=0; i < BLOCK_SIZE; i++){
         //Read the data from the next block 
         data_temp = read_ext_eeprom(next_block + i);           
         //overwrite the previous block with the data from the next
         write_ext_eeprom(previous_block + i, data_temp);  
      }  
      previous_block = next_block;
      next_block += BLOCK_SIZE;
   }
   //Go back to erase the block that's duplicated 
   next_block -= BLOCK_SIZE;
   //Erase the last block since everything 
   //moved a block_size to the left
   erase_program_eeprom(next_block);
   
   return 1;

}

int lastNewUserPosition(){
   int address = 0;
   int id_temp;

   while( read_ext_eeprom(address) != -1){
      address += BLOCK_SIZE; 
   }
   // printf (lcd_escreve,"\fAddress: %u", address);
   // delay_ms(500);
   
   return address;

}

void resetMemory(){
   int address = 0;
   for(; read_ext_eeprom(address) != -1;
    erase_program_eeprom(address), address += BLOCK_SIZE);
}

void adminMenu(){
   unsigned char option;
   unsigned int * temp;
   unsigned int id [2];
   printf(lcd_escreve,"\f1: CAD Cliente ");
   delay_ms(500);
   printf(lcd_escreve,"\r\n2: Buscar Cliente");
   delay_ms(500);
   printf(lcd_escreve,"\f3: DEL Cliente ");
   delay_ms(500);
   printf(lcd_escreve,"\r\n4: Editar Cliente");
   delay_ms(500);
   printf(lcd_escreve,"\f5: SAIR do Menu ");
   delay_ms(500);
   do{
    
      option = readKeyboard();
      printf(lcd_escreve,"\f Option: %c", option);
      delay_ms(500);


      switch(option){
         case '1':
            inputKeyboardUser();
            break;
         case '2':
            temp = inputId();
            id[0] = temp[0];
            id[1] = temp[1];
            searchUser(id);
            break;
         case '3':
            temp = inputId();
            id[0] = temp[0];
            id[1] = temp[1];
            signed int success = deleteUser(id);
            printf(lcd_escreve,"\fSuccess -> %d", success);
            delay_ms(500);
            (success >= 1)? 
            printf(lcd_escreve,"\fusuario deletado"):
            printf(lcd_escreve,"\fusuario N Existe");
            delay_ms(500);
            break;
         case '4':
            editUser();
            break;
         default:
            printf(lcd_escreve,"\fDigite um valor");
            printf(lcd_escreve,"\r\nValido!");
            delay_ms(500);
            break;
      }
   }while(option != '5');
}

void userMenu(){

   unsigned char option;
   do{
      printf(lcd_escreve,"\f1:Login | 5:Sair");
      delay_ms(50);
      option = readKeyboard();
      printf(lcd_escreve,"\r\n Option: %c", option);
      delay_ms(500);


      switch(option){
         case '1':
            unsigned int * temp;
            unsigned int id [2];
            temp = inputId();
            id[0] = temp[0];
            id[1] = temp[1];
            login(id);
            break;
         default:
            printf(lcd_escreve,"\fDigite um valor");
            printf(lcd_escreve,"\r\nValido!");
            delay_ms(500);
            break;
      }
   }while(option != '5');
}

void login(int * id){

   int address = getAddressByID(id);
   if(address != -1){//User exists
      unsigned int * temp;
      unsigned int pass[4];
      unsigned int status;


      char msg [] = "Digite a senha: ";
      int max = 4;
      temp = inputToKeyboard(msg, max);
      pass[0] = temp[0];
      pass[1] = temp[1];
      pass[2] = temp[2];
      pass[3] = temp[3];
      int result_pass = checkPassword(address,pass);
      if(result_pass == 0){
         int show = 0;
         int status = getUserStatus(address,show);
         if(status == 1){//Paid
            printf(lcd_escreve,"\fBem Vindo(a)!");
            delay_ms(1000);
            printf(lcd_escreve,"\fLiga Led e Rele");
            delay_ms(500);
         }
         else{//Unpaid
            printf(lcd_escreve,"\fConta Existe");
            delay_ms(1000);
            printf(lcd_escreve,"\f,Mas Falta Pagar!");
            delay_ms(500);
         }
      }else{
         printf(lcd_escreve,"\fProcure a secretaria");
         printf(lcd_escreve,"\r\nP/ resolver");
         delay_ms(1000);
         printf(lcd_escreve,"\fNADA eh Ligado!");
         delay_ms(500);
      }
   }
   else{
      printf(lcd_escreve,"\fID N Existe");
      printf(lcd_escreve,"\r\nTente de novo");
      delay_ms(1000);
   }

}

int checkPassword(int initBlockAddr, int * pass){
   int pass_addr = initBlockAddr + 2;
   int len = strlen(pass); 
   for(int i=0; i < len;i++,pass_addr++){
      if(pass[i] != read_ext_eeprom(pass_addr))
         return -1;
   }
   return 0;

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
         printf(lcd_escreve, "\fid:%u%u",admins[i], admins[i+1]);
         delay_ms(1000);
      } 
   }
}


int * strToInt(char * str){

  char *p = str;
  //https://flaviocopes.com/c-array-length/
  static unsigned int buffer[BLOCK_SIZE];  
  char * end;
  int index = 0;

  for (unsigned int number = strtoul(p, &end, 10);
        p != end;
        number = strtoul(p, &end, 10))
  {
    p = end;

    buffer[index] = number; 
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


int * inputId(){
   unsigned char keyboard_buffer[BLOCK_SIZE * 2];
   unsigned char option;

   int * temp;
   int i = 0;
   //The user needs to type 4 digits
   //For example, even if it's just 9
   //He/she will type: 0009
   while(i < 5){
      printf(lcd_escreve,"\fDigite o ID: ");
      delay_ms(50);
      option = readKeyboard();
      printf(lcd_escreve,"\n\rTyped:%c", option);
      delay_ms(400);
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
   temp = strToInt(keyboard_buffer);
   return temp;
   // id[0] = temp[0];
   // id[1] = temp[1];
   // //https://www.tutorialspoint.com/cprogramming/c_pointer_to_an_array.htm
   // //*(id+1) == id[1]
   // printf(lcd_escreve,"\fid: %u%u",id[0],id[1]);
   // delay_ms(1000);
}

int * inputToKeyboard(char * msg, int max){
   unsigned char option;
   int data[BLOCK_SIZE];
   int * temp;
   int i = 0;

   while(i < max){

      printf(lcd_escreve,"\f%s", msg);
      delay_ms(50);
      option = readKeyboard();
      printf(lcd_escreve,"\n\rTyped:%c", option);
      delay_ms(400);
      if(option != 255){
         unsigned char destination[2];
         //Convert string from char and return 
         //to the left array of char(str_pass)
         strfromchar(destination,option);
         temp = strToInt(destination);
         data[i] = temp[0];
         i++;
      }
   }

   temp = data;
   return temp;
   // printf(lcd_escreve,"\fPASS(4): %u%u%u%u",pass[0],pass[1],pass[2],pass[3]);
   // delay_ms(1000);

}
void inputKeyboardUser(){

   unsigned int * temp;
   unsigned int id [2];
   unsigned int pass[4];
   unsigned int status;

   temp = inputId();
   id[0] = temp[0];
   id[1] = temp[1];
   printf(lcd_escreve,"\fid: %u%u",id[0],id[1]);
   delay_ms(500);

   char msg [] = "Digite a senha: ";
   int max = 4;
   temp = inputToKeyboard(msg, max);
   pass[0] = temp[0];
   pass[1] = temp[1];
   pass[2] = temp[2];
   pass[3] = temp[3];
   printf(lcd_escreve,"\fPASS(4): %u%u%u%u",pass[0],pass[1],pass[2],pass[3]);
   delay_ms(500);

   char msg2 [] = "Status (0,1,3): ";
   max = 1;
   temp = inputToKeyboard(msg2, max);
   status = temp[0];
   printf(lcd_escreve,"\fSTATUS: %u",status);
   delay_ms(500);

   saveUser(id,pass,status);
}

void editUser(){
   unsigned int * temp;
   unsigned int id [2];
   temp = inputId();
   id[0] = temp[0];
   id[1] = temp[1];

   int address = getAddressByID(id);
   if(address != -1){
      unsigned int * temp;
      unsigned int pass[4];
      unsigned int status;

      char msg [] = "Digite a senha: ";
      int max = 4;
      temp = inputToKeyboard(msg, max);
      pass[0] = temp[0];
      pass[1] = temp[1];
      pass[2] = temp[2];
      pass[3] = temp[3];
      printf(lcd_escreve,"\fPASS(4): %u%u%u%u",pass[0],pass[1],pass[2],pass[3]);
      delay_ms(500);

      char msg2 [] = "Status (0,1,3): ";
      max = 1;
      temp = inputToKeyboard(msg2, max);
      status = temp[0];
      printf(lcd_escreve,"\fSTATUS: %u",status);
      delay_ms(500);

      updateUser(id,pass,status,address);
   }else{
      printf (lcd_escreve,"\fID N Existe",);
      delay_ms(500);
   }
}
