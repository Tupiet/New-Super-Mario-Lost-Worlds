.text
.align 4
#include <asm_setup.S>

.global selectLiftFromSettings
selectLiftFromSettings:
	lbz		r0, 0x7(r29)		#last settings byte in reggie
	cmpwi	r0, 6
	blt		storeColorSinceValid
	li		r0, 0

.global storeColorSinceValid
storeColorSinceValid:
	stw		r0, 0x504(r29)
	blr