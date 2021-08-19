#include<stdio.h>
#include<assert.h>
#include<stdbool.h>
#include<stdint.h>
#include<stdlib.h>

#include "registros.h"

//*************************************************************************************************//

bool get_status(uint8_t *reg, flag_t flag);
void set_status(uint8_t *reg, flag_t flag, bool status);
void set_zero(uint8_t *reg, uint8_t res);
void set_negative(uint8_t *reg, uint8_t res);
void set_carry(uint8_t *reg, uint16_t res);
void set_overflow(uint8_t *reg, uint8_t a, uint8_t b, uint8_t res);
void rotate_left(uint8_t *reg, uint8_t *x);
void rotate_right(uint8_t *reg, uint8_t *x);

//*************************************************************************************************//

bool get_status(uint8_t *reg, flag_t flag){
	if(*reg & flag) return true;
	else return false;
}

void set_status(uint8_t *reg, flag_t flag, bool status){
	if(status==true) *reg |= flag; 
	else  
	 	*reg &= ~flag;
}

void set_zero(uint8_t *reg, uint8_t res){
	if(!res) *reg &= ~ZERO;
	else  
		*reg |= ZERO;
}

void set_negative(uint8_t *reg, uint8_t res){
	if((res & MSB)!=0)
		*reg |= NEGATIVE;
	else 
        *reg &= ~NEGATIVE;
}

void set_carry(uint8_t *reg, uint16_t res){
	if((res&MASK_CARRY)!=0)
	 *reg |= CARRY;
	else *reg &= ~CARRY;
}

void set_overflow(uint8_t *reg, uint8_t a, uint8_t b, uint8_t res){
	if( ((a & MSB) == (b & MSB))  &&  ((res & MSB) != (a & MSB)) )
		*reg |= OVERFLOW;
    else 
        *reg &= ~OVERFLOW;
}

void rotate_left(uint8_t *reg, uint8_t *x){
   uint8_t bit8= *x & MSB;	
   *x=*x<<1;
   
   if((*reg&CARRY)!=0)
        *x|=LSB;
   if(bit8!=0)
         *reg |= CARRY;
    else  
    	*reg &= ~CARRY ;

}

void rotate_right(uint8_t *reg, uint8_t *x){
   uint8_t bit1= *x & LSB;	
   *x=*x>>1;
   
   if((*reg&CARRY)!=0)
   	*x|=MSB;
   if(bit1!=0) *reg |= CARRY;
    else 
    	*reg &= ~CARRY ;
}