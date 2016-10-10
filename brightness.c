#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){
   int menu;
   FILE *arquivo;
   
   char info[5];
   int valor = 0;

   while(1 < 2){
      system("sshpass -p 'temppwd' sftp debian@192.168.7.2:/home/debian/Dev/dadosFOTORESISTOR.txt");
      sleep(4);
      arquivo = fopen("dadosFOTORESISTOR.txt", "r");
      
      if(arquivo == NULL){
         printf("Erro, nao foi possivel abrir o arquivo\n");
      }
      else{
         while( (fgets(info, sizeof(info), arquivo))!= NULL){
         
            valor = atoi(info);
            
            printf("%d \n", valor);
            

            if(valor <= 1000){
               printf("Brilho minimo \n");
               system("echo -n 2 > /sys/class/backlight/acpi_video0/brightness");
            }
            else if (valor >= 1001 && valor <= 3000){
               printf("Brilho normal \n");
               system("echo -n 6 > /sys/class/backlight/acpi_video0/brightness");
            }
            else if (valor >= 3001 && valor <= 4095){
               printf("Brilho maximo \n");
               system("echo -n 9 > /sys/class/backlight/acpi_video0/brightness");
            }
         }
      }      
      fclose(arquivo);
   }   
   return 0;
}  