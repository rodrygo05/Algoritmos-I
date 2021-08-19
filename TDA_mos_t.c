/*
    Crear,
    Destruir,
    Cargar una nueva ROM desde el nombre de archivo,
    Reiniciar el procesador,
    Ejecutar una instrucción,
    Setear el archivo de log.
*/
#include<stdio.h>
#include<assert.h>
#include<stdbool.h>
#include<stdint.h>
#include<stdlib.h>

void most6502_destruir(mos6502_t *p){
	free(p->mem);
	free(p);
}

bool Cargar_ROM(FILE *fi, mos6502_t *p, size_t *tam){
	p->mem = malloc(sizeof(uint8_t)*MAX_INST);
		if(p->mem == NULL){
			most6502_destruir(p);
			fclose(fi);
			return false;
		}

	p-sp=0xFF;
	size_t i=0;

	while(fread(&p->mem[i],sizeof(uint8_t),1,fi)==1){
		i++;
	}

	p->pc = (p->mem[0xFFFC]>>8) | (p->mem[0xFFFD]<<8);
	*n=i;
	return true;

}

void reiniciar_micro(){
	m->a = m->x = m->y = 0;
    m->status = 0x00;
	m->mem = mem;
    m->pc = 0;
    m->sp=0xFF;
	m->ciclos = 0;
}

void ejecutar_instruccion(mos6502_t *p){

    uint8_t opcode=p->mem[p->pc];
    (p->pc)++;
    instruccion_t i;
    i.ciclos= diccionario[opcode].ciclos;
    i.codigo=opcode;
    diccionario[opcode].direccionamiento(p,&i);
    diccionario[opcode].operacion(p,&i);
    p->ciclos += i.ciclos;

}

void set_log(mos6502_t *p){

   
}