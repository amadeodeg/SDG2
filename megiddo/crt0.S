.text

.globl __start
__start:
	movea.l #0x30000,%sp
	move.w  #0x2000,%sr
        link.w %fp,#0
	jsr main
        unlk %fp
        link.w %fp,#0
        clr.l -(%sp)
        jsr _exit
__end:
	jbra __end

.globl _prep_TOUT0
_prep_TOUT0:
	adda.l #-60, %a7
	movem.l %d0-%a6, (%a7)
	jbsr rutina_tout0
	movem.l (%a7), %d0-%a6
	adda.l #60,%a7
	rte

.globl _prep_TOUT1
_prep_TOUT1:
	adda.l #-60, %a7
	movem.l %d0-%a6, (%a7)
	jbsr rutina_tout1
	movem.l (%a7), %d0-%a6
	adda.l #60,%a7
	rte

.globl _prep_TOUT2
_prep_TOUT2:
	adda.l #-60, %a7
	movem.l %d0-%a6, (%a7)
	jbsr rutina_tout2
	movem.l (%a7), %d0-%a6
	adda.l #60,%a7
	rte

.globl _prep_TOUT3
_prep_TOUT3:
	adda.l #-60, %a7
	movem.l %d0-%a6, (%a7)
	jbsr rutina_tout3
	movem.l (%a7), %d0-%a6
	adda.l #60,%a7
	rte

.globl _prep_INT1
_prep_INT1:
	adda.l #-60, %a7
	movem.l %d0-%a6, (%a7)
	jbsr rutina_int1
	movem.l (%a7), %d0-%a6
	adda.l #60,%a7
	rte

.globl _prep_INT2
_prep_INT2:
	adda.l #-60, %a7
	movem.l %d0-%a6, (%a7)
	jbsr rutina_int2
	movem.l (%a7), %d0-%a6
	adda.l #60,%a7
	rte

.globl _prep_INT3
_prep_INT3:
	adda.l #-60, %a7
	movem.l %d0-%a6, (%a7)
	jbsr rutina_int3
	movem.l (%a7), %d0-%a6
	adda.l #60,%a7
	rte

.globl _prep_INT4
_prep_INT4:
	adda.l #-60, %a7
	movem.l %d0-%a6, (%a7)
	jbsr rutina_int4
	movem.l (%a7), %d0-%a6
	adda.l #60,%a7
	rte

