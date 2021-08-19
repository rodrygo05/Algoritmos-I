#ifndef _DIRECCIONAMIENTOS_H_
#define _DIRECCIONAMIENTOS_H_


typedef struct complejo complejo_t;

void direc_implicito(mos6502_t *p, instruccion_t *i);
void direc_acumulador(mos6502_t *p, instruccion_t *i);
void direc_inmediata(mos6502_t *p, instruccion_t *i) 
void direc_relativo(mos6502_t *p, instruccion_t *i)
void direc_absoluta(mos6502_t *p, instruccion_t *i)
void direc_pag_cero(mos6502_t *p, instruccion_t *i)
void direc_indirecto(mos6502_t *p, instruccion_t *i)



#endif