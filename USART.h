
//void USART_Init(long BAUD);
//void USART_Tx(char data);
//char USART_Rx();
/* 
 * File:   Usart.h
 * Author: EDWIN
 *
 * Created on 7 de julio de 2019, 01:31 AM
 */

#ifndef USART_H
#define	USART_H

//Seteo de Pines
#define Tris_Rx     TRISCbits.RC7
#define Tris_Tx     TRISCbits.RC6

#include <xc.h>
#include <stdint.h>

//Funciones
void Tx_str(char);
void Tx_num(uint8_t);
char Rx(void);
void Confi_Blue (void);
void UART0_Tx_String(char *str);
void UART0_Tx_Integer(int32_t num);

#endif	/* USART_H */

