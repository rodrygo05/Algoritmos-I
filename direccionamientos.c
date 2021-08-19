#include "direccionamientos.h"

#include <stdlib.h>


void direc_implicito(mos6502_t *p, instruccion_t *i)  
{
	i->m=NULL;
}

void direc_acumulador(mos6502_t *p, instruccion_t *i) 
{
	(i->m)=&(p->a);
}

void direc_inmediata(mos6502_t *p, instruccion_t *i) 
{
	i->m = &(p->mem[(p->pc)]);
	(p->pc) ++;
}

void direc_relativo(mos6502_t *p, instruccion_t *i)
{

}

void direc_absoluta(mos6502_t *p, instruccion_t *i)  
{
	i->direccion = (p->mem[(p->pc)]) | (p->mem[(p->pc)+1])<<8;
	i->m= &p->mem[i->direccion];
	(p->pc)+=2;
}

void direc_pag_cero(mos6502_t *p, instruccion_t *i)
{
	i->direccion = p->mem[(p->pc)];
	i->m= &p->mem[i->direccion];
	(p->pc) ++;
}

void direc_indirecto(mos6502_t *p, instruccion_t *i)
{
	i->direccion = (p->mem[(p->pc)]) | (p->mem[(p->pc)+1])<<8;
	i->m=
}