///*
// * File:   USART.c
// * Author: HP
// *
// * Created on 26 de enero de 2020, 06:29 PM
// */
//
//
//#include <xc.h>
//#include "USART.h"
//
#define _XTAL_FREQ 20000000
//
//void USART_Init(long BAUD){
//    //Configuraci�n de los pines
//    TRISCbits.RC6 = 0;      //RC6 = Tx -> Salida
//    TRISCbits.RC7 = 1;      //RC7 = Rx -> Entrad
//    
//    //Baudios
//    SPBRG = (unsigned char)(((_XTAL_FREQ/BAUD)/64)-1);
//    
//    //Configuraci�n 
//    TXSTAbits.BRGH = 0;     //Low Speed
//    TXSTAbits.SYNC = 0;     //Asincrono
//    RCSTAbits.SPEN = 1;     //Habilitar Tx y Rx
//    
//    //Transmisi�n
//    TXSTAbits.TX9 = 0;      //8 bits
//    TXSTAbits.TXEN = 1;     //Activamos transmisi�n
//    
//    //Recepci�n
//    RCSTAbits.RC9 = 0;      //8 bits
//    RCSTAbits.CREN = 1;     //Activamos recepci�n
//}
//
//void USART_Tx(char data){
//    TXREG = data;
//}
//
//char USART_Rx(){
//    return RCREG; 
//}

#include <xc.h>
#include <stdint.h>
#include "USART.h"

void Confi_Blue(void){
    Tris_Rx=1;                                 //Configurar el pin Rx como entrada
    Tris_Tx=0;                                 //Configurar el pin Tx como salida
    SPBRG=31;                                  //Baudios
    //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    RCSTAbits.SPEN = 1;                        //Habilitar Tx y Rx
    TXSTAbits.SYNC = 0;                        //Asincrono
    BAUDCONbits.BRG16=0;                       //8 bits de Baudiage
    TXSTAbits.BRGH = 0;                        //Low Speed
    /*64 (8bits) ---> 000
     *8  (8bits) ---> 001
     *8  (16bits)---> 010
     *4  (16bits)---> 011*/
    //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
        //Transmisi�n
        TXSTAbits.TX9 = 0;                     //8 bits
        TXSTAbits.TXEN = 1;                    //Activamos transmisi�n
        //Recepci�n
        RCSTAbits.RC9 = 0;                     //8 bits
        RCSTAbits.CREN = 1;                    //Activamos recepci�n
}
/*XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX*/
void Tx_str(char data){
    while(TXSTAbits.TRMT == 0);
    TXREG = data;                               
}               //Esta funci�n envia datos cadena
/*XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX*/
char Rx(void){
    return RCREG; 
}                    //Esta funci�n recibe datos
/*XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX*/
void Tx_num(uint8_t dita){
    TXREG = dita;                               
}               //Esta funci�n envia datos cadena
/*XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX*/
void UART0_Tx_String(char *str){

	/* Mientras no se alcance el final de la cadena */
	while(*str != '\0'){
		/* Transmitir el caracter correspondiente */
		Tx_str(*str);
		/* Incrementar el valor del puntero (apuntar al siguiente caracter
		en el arreglo) */
		str++;
	}
}

void UART0_Tx_Integer(int32_t num){

	char signo_y_digitos[12];
	uint8_t signo = 0;
	int32_t digito;
	int8_t indice = 11;

	/* Determinar el signo del n�mero */
	if(num < 0){
		signo = 1;
		num = -num;
	}

	/* Indicar el fin de la cadena de caracteres */
	signo_y_digitos[indice--] = '\0';

	/* Extraer los d�gitos uno a uno, empezando por las unidades */
	do{
		digito = (num % 10) + '0';
		signo_y_digitos[indice--] = (char)digito;
		num /= 10;
	}while(num);

	/* Agregar el signo (de ser necesario) */
	if(signo){
		signo_y_digitos[indice] = '-';
	}else{
		indice++;
	}
    __delay_ms(100);
	/* Transmitir el n�mero */
	UART0_Tx_String(&signo_y_digitos[indice]);
}