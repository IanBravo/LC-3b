//
//  Shell.c
//  LC-3b
//
//  Created by Ian Bravo on 7/2/14.
//  Copyright (c) 2014 Ibrarabay. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Shell.h"
#include "Assembler.h"
#include "Cpu.h"

void shell(void)
{
	uint8_t texto[100];
	uint8_t comando[40] = {};
	uint8_t archivo[70] = {};
	uint8_t lineasRun[5] = {};
	uint32_t lineasDeRun = 0;
	uint8_t menor[8] = {};
	uint8_t mayor[8] = {};
	uint32_t menorF = 0;
	uint32_t mayorF = 0;
	uint32_t temporal = 0;
	uint8_t registro[2] = {};
	uint8_t valor[8] = {};
	uint32_t valorF = 0;
	uint8_t i = 0;
	uint8_t j = 0;
	uint8_t espacio = 0;
	uint32_t memoria = 0;
	
	FILE *fp;
	
	while(1)
    {
		printf("> ");
		fgets(texto, 100, stdin);
		fflush(stdin);
		i = 0;
		while(texto[i] != '\0')
        {
			if(texto[i] == ' ')
				espacio++;
			i++;
		}
		i = 0;
		
		if(espacio == 0)
        {
			while(texto[i] != '\n')
            {
				comando[i] = texto[i];
				i++;
			}
			if(strcmp(comando,"go") == 0)
            {
                go();
				printf("Fin del programa.\n");
				memset(comando, 0, sizeof comando);
			}
			else if(strcmp(comando,"next") == 0)
            {
				cpu();
				memset(comando, 0, sizeof comando);
			}
			else if(strcmp(comando,"?") == 0)
            {
				printf("loader <file.hex>\nassembler <file.txt>\nrun <n>\ngo\nnext\nmdump <low> <high>\nrdump\n");
				printf("input <registro> <valor>\n");
				memset(comando, 0, sizeof comando);
			}
			else if(strcmp(comando,"rdump") == 0)
            {
				rdump();
				memset(comando, 0, sizeof comando);
			}
			else if(strcmp(comando,"quit") == 0)
            {
				printf("Salida\n");
				exit(1);
			}
			else
            {
				printf("Comando no valido\n");
				memset(comando, 0, sizeof comando);
				memset(texto, 0, sizeof texto);
			}
		}
		else if(espacio == 1)
        {
			espacio = 0;
			while(texto[i] != ' ')
            {
				comando[i] = texto[i];
				i++;
			}
			i++;
			if(strcmp(comando,"loader") == 0)
            {
				while(texto[i] != '\n')
                {
					archivo[j] = texto[i];
					i++;
					j++;
				}
				i = 0;
				j = 0;
                
				fp = fopen(archivo, "rb");
				if(fp == NULL)
					printf("Error al abrir el archivo\n");
				else
					loader(fp);
				espacio = 0;
				memset(comando, 0, sizeof comando);
			    memset(archivo, 0, sizeof archivo);
			}
			else if(strcmp(comando,"assembler") == 0)
            {
				while(texto[i] != '\n')
                {
					archivo[j] = texto[i];
					i++;
					j++;
				}
				i = 0;
				j = 0;
                
				fp = fopen(archivo, "rb");
				if(fp == NULL)
					printf("Error al abrir el archivo\n");
				else
                    assembler(fp);
				espacio = 0;
				memset(comando, 0, sizeof comando);
			    memset(archivo, 0, sizeof archivo);
			}
			else if(strcmp(comando,"run") == 0)
            {
                uint16_t lineas = 0;
				while(texto[i] != '\n')
                {
					lineasRun[j] = texto[i];
					i++;
					j++;
				}
				i = 0;
				j = 0;
                
                lineas = strtoul(lineasRun, NULL, 0);
                run(lineas);
				i=0;
				espacio = 0;
				memset(comando, 0, sizeof comando);
				memset(lineasRun, 0, sizeof lineasRun);
			}
			else
            {
				printf("Comando invalido\n");
				memset(comando, 0, sizeof comando);
				memset(texto, 0, sizeof texto);
			}
		}
		else if(espacio == 2)
        {
            uint16_t low = 0;
            uint16_t high = 0;
			espacio = 0;
			while(texto[i] != ' '){
				comando[i] = texto[i];
				i++;
			}
			i++;
			if(strcmp(comando,"mdump") == 0)
            {
				while(texto[i] != ' ')
                {
					menor[j] = texto[i];
					i++;
					j++;
				}
				j = 0;
				i++;
				while(texto[i] != '\n')
                {
					mayor[j] = texto[i];
					i++;
					j++;
				}
				i = 0;
				j = 0;
                low = strtoul(menor, NULL, 0);
				memset(menor, 0, sizeof menor);
                high = strtoul(mayor, NULL, 0);
				memset(mayor, 0, sizeof mayor);
                
                memDump(low, high);
                
				printf("\n");
 				espacio = 0;
				memset(comando, 0, sizeof comando);
			}
			else if(strcmp(comando,"input") == 0)
            {
                int flag = 0;
                uint16_t value = 0;
                uint16_t reg = 0;
				while(texto[i] != ' ')
                {
					registro[j] = texto[i];
					i++;
					j++;
				}
                
                if (registro[0] != 'R')
                {
                    printf("Registro incorrecto [R0 - R7]\n");
                }
                else
                {
                    if (strcmp(registro, "R0") == 0)
                    {
                        reg = 0;
                    }
                    else if (strcmp(registro, "R1") == 0)
                    {
                        reg = 1;
                    }
                    else if (strcmp(registro, "R2") == 0)
                    {
                        reg = 2;
                    }
                    else if (strcmp(registro, "R3") == 0)
                    {
                        reg = 3;
                    }
                    else if (strcmp(registro, "R4") == 0)
                    {
                        reg = 4;
                    }
                    else if (strcmp(registro, "R5") == 0)
                    {
                        reg = 5;
                    }
                    else if (strcmp(registro, "R6") == 0)
                    {
                        reg = 6;
                    }
                    else if (strcmp(registro, "R7") == 0)
                    {
                        reg = 7;
                    }
                    else
                    {
                        printf("Registro incorrecto [R0 - R7]\n");
                        flag = 1;
                    }
                    
                    if (flag == 0)
                    {
                        j = 0;
                        i++;
                        while(texto[i] != '\n')
                        {
                            valor[j] = texto[i];
                            i++;
                            j++;
                        }
                        i = 0;
                        j = 0;
                        value = strtoul(valor, NULL, 0);
                        storeResult(value, reg);
                        espacio = 0;
                        valorF = 0;
                        memset(comando, 0, sizeof comando);
                        memset(valor, 0, sizeof valor);
                        memset(registro, 0, sizeof registro);
                    }
                    
                }
			}
			else
            {
				printf("Comando no valido\n");
				memset(comando, 0, sizeof comando);
				memset(texto, 0, sizeof texto);
			}
		}
		else
        {
			espacio = 0;
			memset(texto,0,sizeof texto);
			memset(comando,0,sizeof comando);
		}
	}
}







































