#ifndef _OPERACIONES_H_
#define _OPERACIONES_H_

struct instruccion;
typedef struct instruccion instruccion_t;

struct mos6502;
typedef struct instruccion mos6502_t;

void operacion_adc(mos6502_t *p, instruccion_t *i);
void operacion_and(mos6502_t *p, instruccion_t *i);
void operacion_asl(mos6502_t *p, instruccion_t *i);
void operacion_bbc(mos6502_t *p, instruccion_t *i);
void operacion_bcs(mos6502_t *p, instruccion_t *i);
void operacion_beq(mos6502_t *p, instruccion_t *i);
void operacion_bit(mos6502_t *p, instruccion_t *i);
void operacion_bmi(mos6502_t *p, instruccion_t *i);
void operacion_bne(mos6502_t *p, instruccion_t *i);
void operacion_bpl(mos6502_t *p, instruccion_t *i);
void operacion_bvs(mos6502_t *p, instruccion_t *i);
void operacion_bvc(mos6502_t *p, instruccion_t *i);
void operacion_clc(mos6502_t *p, instruccion_t *i);
void operacion_cli(mos6502_t *p, instruccion_t *i);
void operacion_clv(mos6502_t *p, instruccion_t *i);
void operacion_cmp(mos6502_t *p, instruccion_t *i);
void operacion_cpx(mos6502_t *p, instruccion_t *i);
void operacion_cpy(mos6502_t *p, instruccion_t *i);
void operacion_dec(mos6502_t *p, instruccion_t *i);
void operacion_dex(mos6502_t *p, instruccion_t *i);
void operacion_dey(mos6502_t *p, instruccion_t *i);
void operacion_eor(mos6502_t *p, instruccion_t *i);
void operacion_inc(mos6502_t *p, instruccion_t *i);
void operacion_inx(mos6502_t *p, instruccion_t *i);
void operacion_jmp(mos6502_t *p, instruccion_t *i);
void operacion_jsr(mos6502_t *p, instruccion_t *i);
void operacion_lda(mos6502_t *p, instruccion_t *i);
void operacion_ldx(mos6502_t *p, instruccion_t *i);
void operacion_ldy(mos6502_t *p, instruccion_t *i);
void operacion_lsr(mos6502_t *p, instruccion_t *i);
void operacion_nop(mos6502_t *p, instruccion_t *i);
void operacion_pha(mos6502_t *p, instruccion_t *i);
void operacion_php(mos6502_t *p, instruccion_t *i);
void operacion_pla(mos6502_t *p, instruccion_t *i);
void operacion_plp(mos6502_t *p, instruccion_t *i);
void operacion_rol(mos6502_t *p, instruccion_t *i);
void operacion_ror(mos6502_t *p, instruccion_t *i);
void operacion_rti(mos6502_t *p, instruccion_t *i);
void operacion_rts(mos6502_t *p, instruccion_t *i);
void operacion_sbc(mos6502_t *p, instruccion_t *i);
void operacion_sec(mos6502_t *p, instruccion_t *i);
void operacion_sed(mos6502_t *p, instruccion_t *i);
void operacion_sei(mos6502_t *p, instruccion_t *i);
void operacion_sta(mos6502_t *p, instruccion_t *i);
void operacion_stx(mos6502_t *p, instruccion_t *i);
void operacion_sty(mos6502_t *p, instruccion_t *i);
void operacion_tax(mos6502_t *p, instruccion_t *i);
void operacion_tay(mos6502_t *p, instruccion_t *i);
void operacion_tsx(mos6502_t *p, instruccion_t *i);
void operacion_txa(mos6502_t *p, instruccion_t *i);
void operacion_txs(mos6502_t *p, instruccion_t *i);
void operacion_tya(mos6502_t *p, instruccion_t *i);

void operacion_ld_aux(mos6502_t *p, instruccion_t *i, uint8_t *aux);
void operacion_de_aux(mos6502_t *p, instruccion_t *i, uint8_t *aux);

void apilar(mos6502_t *p, uint8_t valor);
uint8_t desapilar(mos6502_t *p);

#endif