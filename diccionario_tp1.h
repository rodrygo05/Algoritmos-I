typedef void(*funcion_op_t)(mos6502_t *,instruccion_t *);  //puntero a funcion recibe 2 puntero a struct y no devuelva nada.
typedef void(*funcion_direc_t)(mos6502_t *,instruccion_t *);

typedef struct{
	funcion_op_t operacion;
	funcion_direc_t direccionamiento;
	size_t ciclos;
}diccionario_t;

diccionario_t diccionario[0x100]={
    [0x69]={operacion_adc,direc_inmediata,   2},
    [0x65]={operacion_adc,direc_pag_cero,    3},
    [0x75]={operacion_adc,direc_pag_cero_x,  4},
    [0x6d]={operacion_adc,direc_absoluta,    4},
    [0x7d]={operacion_adc,direc_absoluta_x,  4},
    [0x79]={operacion_adc,direc_absoluta_y,  4},
    [0x7d]={operacion_adc,direc_index_ind_x,  6},
    [0x79]={operacion_adc,direc_ind_index_y,  5},

    [0x29]={operacion_and,direc_inmediata,  2},
    [0x25]={operacion_and,direc_pag_cero,   3},
    [0x35]={operacion_and,direc_pag_cero_x, 4},
    [0x2d]={operacion_and,direc_absoluta,   4},
    [0x3d]={operacion_and,direc_absoluta_x, 4},
    [0x39]={operacion_and,direc_absoluta_y, 4},
    [0x21]={operacion_and,direc_index_ind_x, 6},
    [0x31]={operacion_and,direc_ind_index_y, 5},

    [0x0a]={operacion_asl,direc_acumulador, 2},
    [0x06]={operacion_asl,direc_pag_cero,   5},
    [0x16]={operacion_asl,direc_pag_cero_x, 6},
    [0x0E]={operacion_asl,direc_absoluta,   6},
    [0x1E]={operacion_asl,direc_absoluta_x, 7},

    [0x90]={operacion_bcc,direc_relativo, 2},

    [0xB0]={operacion_bcs,direc_relativo, 2},

    [0xF0]={operacion_beq,direc_relativo, 2},

    [0x24]={operacion_bit,direc_pag_cero, 3},
    [0x2C]={operacion_bit,direc_absoluta, 4},

    [0x30]={operacion_bmi,direc_relativo, 2},

    [0xD0]={operacion_bne,direc_relativo, 2},

    [0x10]={operacion_bpl,direc_relativo, 2},

    [0x00]={operacion_brk,direc_implicito, 7},

    [0x50]={operacion_bvc,direc_relativo, 2},

    [0x70]={operacion_bvs,direc_relativo, 2},

    [0x18]={operacion_clc,direc_implicito, 2},

    [0xD8]={operacion_cld,direc_implicito, 2},

    [0x58]={operacion_cli,direc_implicito, 2},

    [0xB8]={operacion_clv,direc_implicito, 2},

    [0xC9]={operacion_cmp,direc_inmediata,  2},
    [0xC5]={operacion_cmp,direc_pag_cero,   3},
    [0xD5]={operacion_cmp,direc_pag_cero_x, 4},
    [0xCD]={operacion_cmp,direc_absoluta,   4},
    [0xDD]={operacion_cmp,direc_absoluta_x, 4},
    [0xD9]={operacion_cmp,direc_absoluta_y, 4},
    [0xC1]={operacion_cmp,direc_index_ind_x, 6},
    [0xD1]={operacion_cmp,direc_ind_index_y, 5},

    [0xE0]={operacion_cpx,direc_inmediata, 2},
    [0xE4]={operacion_cpx,direc_pag_cero, 3},
    [0xEC]={operacion_cpx,direc_absoluta, 4},

    [0xC0]={operacion_cpy,direc_inmediata, 2},
    [0xC4]={operacion_cpy,direc_pag_cero, 3},
    [0xCC]={operacion_cpy,direc_absoluta, 4},

    [0xC6]={operacion_dec,direc_pag_cero,   5},
    [0xD6]={operacion_dec,direc_pag_cero_x, 6},
    [0xCE]={operacion_dec,direc_absoluta,   6},
    [0xDE]={operacion_dec,direc_absoluta_x, 7},

    [0xca]={operacion_dex,direc_implicito,  2},

    [0x88]={operacion_dey,direc_implicito,  2},

    [0x49]={operacion_eor,direc_inmediata,  2},
    [0x45]={operacion_eor,direc_pag_cero,   3},
    [0x55]={operacion_eor,direc_pag_cero_x, 4},
    [0x4D]={operacion_eor,direc_absoluta,   4},
    [0x5D]={operacion_eor,direc_absoluta_x, 4},
    [0x59]={operacion_eor,direc_absoluta_y, 4},
    [0x41]={operacion_eor,direc_index_ind_x, 6},
    [0x51]={operacion_eor,direc_ind_index_y, 5},

    [0xE6]={operacion_inc,direc_pag_cero,   5},
    [0xF6]={operacion_inc,direc_pag_cero_x, 6},
    [0xEE]={operacion_inc,direc_absoluta,   6},
    [0xFE]={operacion_inc,direc_absoluta_x, 7},

    [0xE8]={operacion_inx,direc_implicito, 2},

    [0xC8]={operacion_iny,direc_implicito, 2},

    [0x4c]={operacion_jmp,direc_absoluta,   3},
    [0x6C]={operacion_jmp,direc_indirecto,  5},

    [0x20]={operacion_jsr,direc_absoluta,  7},

    [0xA9]={operacion_lda,direc_inmediata,  2},
    [0xA5]={operacion_lda,direc_pag_cero,   3},
    [0xB5]={operacion_lda,direc_pag_cero_x, 4},
    [0xAD]={operacion_lda,direc_absoluta,   4},
    [0xBD]={operacion_lda,direc_absoluta_x, 4},
    [0xB9]={operacion_lda,direc_absoluta_y, 4},
    [0xA1]={operacion_lda,direc_index_ind_x, 6},
    [0xB1]={operacion_lda,direc_ind_index_y, 5},


    [0xA2]={operacion_ldx,direc_inmediata,  2},
    [0xA6]={operacion_ldx,direc_pag_cero,   3},
    [0xB6]={operacion_ldx,direc_pag_cero_y, 4},
    [0xAE]={operacion_ldx,direc_absoluta,   4},
    [0xBE]={operacion_ldx,direc_absoluta_y, 4},

    [0xA0]={operacion_ldy,direc_inmediata,  2},
    [0xA4]={operacion_ldy,direc_pag_cero,   3},
    [0xB4]={operacion_ldy,direc_pag_cero_x, 4},
    [0xAC]={operacion_ldy,direc_absoluta,   4},
    [0xBC]={operacion_ldy,direc_absoluta_x, 4},
    
    [0xA2]={operacion_lsr,direc_acumulador, 2},
    [0xA6]={operacion_lsr,direc_pag_cero,   5},
    [0xB6]={operacion_lsr,direc_pag_cero_x, 6},
    [0xAE]={operacion_lsr,direc_absoluta,   6},
    [0xBE]={operacion_lsr,direc_absoluta_x, 7},

    [0xea]={operacion_nop,direc_implicito,  2},

    [0x09]={operacion_ora,direc_inmediata,  2},
    [0x05]={operacion_ora,direc_pag_cero,   3},
    [0x15]={operacion_ora,direc_pag_cero_x, 4},
    [0x0D]={operacion_ora,direc_absoluta,   4},
    [0x1D]={operacion_ora,direc_absoluta_x, 4},
    [0x19]={operacion_ora,direc_absoluta_y, 4},
    [0x01]={operacion_ora,direc_index_ind_x, 6},
    [0x11]={operacion_ora,direc_ind_index_y, 5},

    [0x48]={operacion_pha,direc_implicito,  3},

    [0x08]={operacion_php,direc_implicito,  3},

    [0x68]={operacion_pla,direc_implicito,  4},

    [0x28]={operacion_plp,direc_implicito,  4}, 
    
    [0x2A]={operacion_rol,direc_acumulador, 2},
    [0x26]={operacion_rol,direc_pag_cero,   3},
    [0x36]={operacion_rol,direc_pag_cero_x, 4},
    [0x2E]={operacion_rol,direc_absoluta,   4},
    [0x3E]={operacion_rol,direc_absoluta_x, 4},

    [0x6A]={operacion_ror,direc_acumulador, 2},
    [0x66]={operacion_ror,direc_pag_cero,   3},
    [0x76]={operacion_ror,direc_pag_cero_x, 4},
    [0x6E]={operacion_ror,direc_absoluta,   4},
    [0x7E]={operacion_ror,direc_absoluta_x, 4},

    [0x40]={operacion_rti,direc_implicito,  6},

    [0x60]={operacion_rts,direc_implicito,  6},

    [0xE9]={operacion_sbc,direc_inmediata,  2},
    [0xE5]={operacion_sbc,direc_pag_cero,   3},
    [0xF5]={operacion_sbc,direc_pag_cero_x, 4},
    [0xED]={operacion_sbc,direc_absoluta,   4},
    [0xFD]={operacion_sbc,direc_absoluta_x, 4},
    [0xF9]={operacion_sbc,direc_absoluta_y, 4},
    [0xE1]={operacion_sbc,direc_index_ind_x, 6},
    [0xF1]={operacion_sbc,direc_ind_index_y, 5},

    [0x38]={operacion_sec,direc_implicito,  2},

    [0xF8]={operacion_sed,direc_implicito,  2},

    [0x78]={operacion_sei,direc_implicito,  2},

    [0x85]={operacion_sta,direc_pag_cero,   3},
    [0x95]={operacion_sta,direc_pag_cero_x, 4},
    [0x8D]={operacion_sta,direc_absoluta,   4},
    [0x9D]={operacion_sta,direc_absoluta_x, 4},
    [0x99]={operacion_sta,direc_absoluta_y, 5},
    [0x81]={operacion_sta,direc_index_ind_x, 6},
    [0x91]={operacion_sta,direc_ind_index_y, 6},

    [0x86]={operacion_stx,direc_pag_cero,   3},
    [0x96]={operacion_stx,direc_pag_cero_y, 4},
    [0x8E]={operacion_stx,direc_absoluta,   4},

    [0x84]={operacion_sty,direc_pag_cero,   3},
    [0x94]={operacion_sty,direc_pag_cero_x, 4},
    [0x8C]={operacion_sty,direc_absoluta,   4},

    [0xAA]={operacion_tax,direc_implicito,  2},
    [0xA8]={operacion_tay,direc_implicito,  2},
    [0xBA]={operacion_tsx,direc_implicito,  2},
    [0x8A]={operacion_txa,direc_implicito,  2},
    [0x9A]={operacion_txs,direc_implicito,  2},
    [0x98]={operacion_tya,direc_implicito,  2},


    [0x8c]={operacion_sty,direc_absoluta,   4}

};
