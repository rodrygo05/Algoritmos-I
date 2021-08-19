#include<stdio.h>
#include<assert.h>
#include<stdbool.h>
#include<stdint.h>
#include<stdlib.h>

#include "operaciones.h"
#include "registros.h"

//***************ESTRUCTURAS**********************/
struct intruccion {
    uint8_t codigo;     // Opcode.
    short ciclos;       // Cantidad de ciclos de la instrucción.
    uint8_t *m;         // Puntero al operando (registro o memoria).
    uint16_t direccion; // Dirección del operando (si corresponde).
};


struct mos6502{
    uint8_t a, x, y;    // Registros A, X e Y.
    uint16_t pc;        // Program counter.
    uint8_t status;     // Registro de status.
    uint8_t sp;         // Stack pointer.
    uint8_t *mem;       // Memoria.

    long ciclos;        // Cantidad de ciclos totales de ejecución.
};

void apilar(mos6502_t *p, uint8_t valor){
	p->mem[0x0100|p->sp];
	(p->sp)++;
}

uint8_t desapilar(mos6502_t *p){
	(p->sp)--;
	return p->mem[0x0100|p->sp];
}

void operacion_adc(mos6502_t *p, instruccion_t *i){
	uint16_t aux= p->a + *(i->m) + get_status(&p->status,CARRY);  // A= A + M + Carry (1 o 0)
	p->a=aux;

	set_zero(&p->status,p->a);
	set_negative(&p->status,p->a);
	set_carry(&p->status,aux);
} 

void operacion_and(mos6502_t *p, instruccion_t *i){
	p->a &= *(i->m);
	set_zero(&p->status,p->a);
	set_negative(&p->status,p->a);
}

void operacion_asl(mos6502_t *p, instruccion_t *i){
	uint16_t aux= *(i->m) <<1;
	*(i->m)=aux;

	set_zero(&p->status,*(i->m));
	set_negative(&p->status,*(i->m));
	set_carry(&p->status,aux);

}

void operacion_bcc(mos6502_t *p, instruccion_t *i){
	if(get_status(&p->status, CARRY))
		p->pc+ = *(i->m);
}

void operacion_bcs(mos6502_t *p, instruccion_t *i){
	if(!get_status(&p->status, CARRY))
		p->pc+ = *(i->m);
}

void operacion_beq(mos6502_t *p, instruccion_t *i){
	if(!get_status(&p->status, ZERO))
		p->pc+ = *(i->m);
}

void operacion_bmi(mos6502_t *p, instruccion_t *i){
	if(!get_status(&p->status, NEGATIVE))
		p->pc+ = *(i->m);
}

void operacion_bne(mos6502_t *p, instruccion_t *i){
	if(get_status(&p->status, ZERO))
		p->pc+ = *(i->m);
}

void operacion_bvc(mos6502_t *p, instruccion_t *i){
	if(get_status(&p->status, OVERFLOW))
		p->pc+ = *(i->m);
}

void operacion_bvs(mos6502_t *p, instruccion_t *i){
	if(!get_status(&p->status, OVERFLOW))
		p->pc+ = *(i->m);
}

void operacion_bpl(mos6502_t *p, instruccion_t *i){
	if(get_status(&p->status, NEGATIVE))
		p->pc+ = *(i->m);
}


void operacion_clc(mos6502_t *p, instruccion_t *i){
	set_status(&(p->status),CARRY, false);
}

void operacion_cld(mos6502_t *p, instruccion_t *i){
	set_status(&(p->status),DECIMAL, false);
}

void operacion_cli(mos6502_t *p, instruccion_t *i){
	set_status(&(p->status),INTERRUPT_DISABLE, false);
}

void operacion_clv(mos6502_t *p, instruccion_t *i){
	set_status(&(p->status),OVERFLOW, false);
}

void operacion_cmp(mos6502_t *p, instruccion_t *i){

    set_status(&p->status,ZERO, (p->a) == *(i->m)  );
    set_status(&p->status,NEGATIVE, p->a < *(i->m)  );
    set_status(&p->status,CARRY, (p->a) >= *(i->m) );
    
} 

void operacion_cmx(mos6502_t *p, instruccion_t *i){

    set_status(&p->status,ZERO, (p->x) == *(i->m)  );
    set_status(&p->status,NEGATIVE, p->x < *(i->m)  );
    set_status(&p->status,CARRY, (p->x) >= *(i->m) );   
} 

void operacion_cmy(mos6502_t *p, instruccion_t *i){

    set_status(&p->status,ZERO, (p->y) == *(i->m)  );
    set_status(&p->status,NEGATIVE, p->y < *(i->m)  );
    set_status(&p->status,CARRY, (p->y) >= *(i->m) );    
} 
 
void operacion_de_aux(mos6502_t *p, instruccion_t *i, uint8_t *aux){
    (*aux)--;
    set_zero(&p->status,*aux);
    set_negative(&p->status,*aux);
}

void operacion_dec(mos6502_t *p, instruccion_t *i){
    operacion_de_aux(p,i,&(*(i->m)));
}

void operacion_dex(mos6502_t *p, instruccion_t *i){
	operacion_de_aux(p,i,&p->x);
}

void operacion_dey(mos6502_t *p, instruccion_t *i){
	operacion_de_aux(p,i,&p->y);
}

void operacion_eor(mos6502_t *p, instruccion_t *i){
	p->a ^= (*(i->m));
	set_zero(&p->status,p->a);
	set_negative(&p->status,p->a);
}

void operacion_inc(mos6502_t *p, instruccion_t *i){
	*(i->m)= *(i->m) + 1;
	set_zero(&p->status,*(i->m));
	set_negative(&p->status,*(i->m));
}

void operacion_inx(mos6502_t *p, instruccion_t *i){
	p->x= p->x + 1;
	set_zero(&p->status,p->x);
	set_negative(&p->status,p->x);
}

void operacion_iny(mos6502_t *p, instruccion_t *i){
	p->x= p->x + 1;
	set_zero(&p->status,p->x);
	set_negative(&p->status,p->x);
}

void operacion_jmp(mos6502_t *p, instruccion_t *i){
	p->pc = i->direccion;
} 

void operacion_jsr(mos6502_t *p, instruccion_t *i){
	apilar(p,(p->pc)-1);
	p->pc = *(i->m);
} 

void operacion_ld_aux(mos6502_t *p, instruccion_t *i, uint8_t *aux){
	*aux=*(i->m);
	set_zero(&p->status,*aux);
	set_negative(&p->status,*aux);
}

void operacion_lda(mos6502_t *p, instruccion_t *i) //A = M => Z, N
{
	operacion_ld_aux(p,i,&p->a);
}

void operacion_ldx(mos6502_t *p, instruccion_t *i) //X = M => Z, N
{
	operacion_ld_aux(p,i,&p->x);;
}

void operacion_ldy(mos6502_t *p, instruccion_t *i) //Y = M => Z, N
{
	operacion_ld_aux(p,i,&p->y);
}

void operacion_lsr(mos6502_t *p, instruccion_t *i){
	uint16_t aux= *(i->m) >>1;
	*(i->m)=aux;

	set_zero(&p->status,*(i->m));
	set_negative(&p->status,*(i->m));
	set_carry(&p->status,aux);
}

void operacion_ora(mos6502_t *p, instruccion_t *i) 
{
	p->a | = *(i->m);

	set_zero(&p->status,p->a);
	set_negative(&p->status,p->a);
} 

void operacion_nop(mos6502_t *p, instruccion_t *i) 
{
	//no hace nada//
} 

void operacion_pha(mos6502_t *p, instruccion_t *i) {
	apilar(p,p->a);
} 

void operacion_php(mos6502_t *p, instruccion_t *i) {
	apilar(p,p->status);
} 

void operacion_pla(mos6502_t *p, instruccion_t *i) {
	p->a = desapilar(p);
	set_zero(&p->status,p->a);
	set_negative(&p->status,p->a);

} 
void operacion_plp(mos6502_t *p, instruccion_t *i) {
	p->status = desapilar(p);
}

void operacion_rol(mos6502_t *p, instruccion_t *i) {
	rotate_left(&(p->status),&(*(i->m)) );

	set_zero(&p->status,*(i->m));
	set_negative(&p->status,*(i->m));
	set_carry(&p->status,aux);
}

void operacion_rol(mos6502_t *p, instruccion_t *i) {
	rotate_right(&(p->status),&(*(i->m)) );

	set_zero(&p->status,*(i->m));
	set_negative(&p->status,*(i->m));
	set_carry(&p->status,aux);
}


void operacion_sec(mos6502_t *p, instruccion_t *i)  //C = 1
{
	set_status(&(p->status),CARRY,1);
}

void operacion_sed(mos6502_t *p, instruccion_t *i)  //C = 1
{
	set_status(&(p->status),DECIMAL,1);
}

void operacion_sei(mos6502_t *p, instruccion_t *i)  //C = 1
{
	set_status(&(p->status),INTERRUPT_DISABLE,1);
}
void operacion_sta(mos6502_t *p, instruccion_t *i)  //M = A
{
	*(i->m)=p->a;
}

void operacion_stx(mos6502_t *p, instruccion_t *i)  //M = X
{
	*(i->m)=p->x;
}

void operacion_sty(mos6502_t *p, instruccion_t *i)  //M = Y
{
	*(i->m)=p->y;
}

void operacion_tax(mos6502_t *p, instruccion_t *i)  //M = Y
{
	p->x=p->a;

	set_zero(&p->status,p->x);
	set_negative(&p->status,p->x);
}

void operacion_tay(mos6502_t *p, instruccion_t *i)  //M = Y
{
	p->y=p->a;

	set_zero(&p->status,p->y);
	set_negative(&p->status,p->y);
}

void operacion_tsx(mos6502_t *p, instruccion_t *i)  //M = Y
{
	p->x=p->sp;

	set_zero(&p->status,p->x);
	set_negative(&p->status,p->x);
}

void operacion_txa(mos6502_t *p, instruccion_t *i)  //M = Y
{
	p->a=p->x;

	set_zero(&p->status,p->a);
	set_negative(&p->status,p->a);
}

void operacion_txs(mos6502_t *p, instruccion_t *i)  //M = Y
{
	p->sp=p->x;

	set_zero(&p->status,p->sp);
	set_negative(&p->status,p->sp);
}

void operacion_tya(mos6502_t *p, instruccion_t *i)  //M = Y
{
	p->a=p->y;

	set_zero(&p->status,p->a);
	set_negative(&p->status,p->a);
}