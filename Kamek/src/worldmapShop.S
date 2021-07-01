.text
.align 4

#include <asm_setup.S>

.extern shopOpen
.extern continueFromShopCheck

.global isShopOpen
isShopOpen:
	lis     r4, shopOpen@h
	ori     r4, r4, shopOpen@l
	lbz     r4, 0(r4)
	#lbz     r0, shopOpen@l(r0)
	cmpwi   r4, 0
	bgt     li4InR5
	cmpwi   r5, 0x0
	b       continueFromShopCheck
	
li4InR5:
	li      r5, 0x4
	cmpwi   r5, 0x0
	b       continueFromShopCheck
	