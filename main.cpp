#include "BlackGPIO/BlackGPIO.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h> 

using namespace std;

#define PATH_ADC "/sys/bus/iio/devices/iio:device0/in_voltage"

int readAnalog(int number){
   stringstream ss;
   ss << PATH_ADC << number << "_raw";
   fstream fs;
   fs.open(ss.str().c_str(), fstream::in);
   fs >> number;
   fs.close();
   return number;
}

void encerrarPrograma(int sig){
	printf("Encerrar PROGRAMA!\n");
	kill(getpid(), SIGTERM);
}


int main(int argc, char *argv[]){
    
    FILE *arquivo;
	
	int contador = 0;
    int estado;
    int valorFotoRes = 0;

	pid_t idProc;
    idProc = fork();

	BlackLib::BlackGPIO   ledR(BlackLib::GPIO_60,BlackLib::output, BlackLib::SecureMode);
    BlackLib::BlackGPIO   ledG(BlackLib::GPIO_50,BlackLib::output, BlackLib::SecureMode);
    BlackLib::BlackGPIO   ledB(BlackLib::GPIO_51,BlackLib::output, BlackLib::SecureMode);
    BlackLib::BlackGPIO   ledV(BlackLib::GPIO_30,BlackLib::output, BlackLib::SecureMode);
    BlackLib::BlackGPIO   btn1(BlackLib::GPIO_115,BlackLib::input, BlackLib::SecureMode);

    

    

    switch(idProc){
    	case -1:
    		printf("ERRO!\n");
    		exit(1);
    	case 0:
    		while(1 < 2){
				valorFotoRes = readAnalog(1);
					
				if(valorFotoRes <= 818){	
					ledR.setValue(BlackLib::low);
					ledG.setValue(BlackLib::low);
					ledB.setValue(BlackLib::high);
				}
					
				else if(valorFotoRes >= 819 && valorFotoRes <= 1637){
					ledR.setValue(BlackLib::low);
					ledG.setValue(BlackLib::high);
					ledB.setValue(BlackLib::high);
				}
				
				else if (valorFotoRes >= 1638 && valorFotoRes <= 2456){
					ledR.setValue(BlackLib::low);
					ledG.setValue(BlackLib::high);
					ledB.setValue(BlackLib::low);
				}
				
				else if(valorFotoRes >= 2457 && valorFotoRes <= 3275){
					ledR.setValue(BlackLib::high);
					ledG.setValue(BlackLib::low);
					ledB.setValue(BlackLib::high);
				}

				else if(valorFotoRes >= 3276 && valorFotoRes <= 4095){
					ledR.setValue(BlackLib::high);
					ledG.setValue(BlackLib::low);
					ledB.setValue(BlackLib::low);
				}    		
    		}
    	default:
    		alarm(6);
    		while(1 < 2){
				signal(SIGALRM, encerrarPrograma);
				
				int cmd1 = btn1.getNumericValue();
				cout << "Aperte o botão para comecar!" << endl;
				
				if(cmd1 == 1){
					kill(idProc, SIGCONT);	
					
					contador = 0;
					ledV.setValue(BlackLib::low);
					cout << "##################" << endl;
					cout << "PROGRAMA INICIADO!" << endl;
					cout << "###################\n" << endl; 
					int cmd2 = 0;

					while(cmd2 != 1){
						signal(SIGALRM, SIG_IGN);

						arquivo = fopen("dadosFOTORESISTOR.txt", "w");

						if(arquivo == NULL){
							cout << "Erro ao abrir o arquivo!" << endl;
						}		
    			
    					valorFotoRes = readAnalog(1);
    					fprintf(arquivo, "%i", valorFotoRes);
						cout << "Valor: " << valorFotoRes << endl;

						sleep(1);
						fclose(arquivo);
						sleep(5);
						
						cmd2 = btn1.getNumericValue();
					
						if(cmd2 == 1){
							alarm(6);
							cout << "##################" << endl;
							cout << "PROGRAMA DESLIGADO!" << endl;
							cout << "###################\n" << endl;
						}	
					}	
				}
				kill(idProc, SIGSTOP);
				sleep(1);
				ledR.setValue(BlackLib::low);
				ledG.setValue(BlackLib::low);
				ledB.setValue(BlackLib::low);
				ledV.setValue(BlackLib::low);
				cout << "Programa fecha em: " << (5 - contador) << endl;
				contador++;
			}	
    		kill(idProc, SIGTERM);
    }
	return 0;
}