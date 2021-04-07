.text

#include <asm_setup.S>

.align 4
.extern slowDownTime
.extern updateUI
.extern ApparentlyStartsMusic
.extern continueTimerLeq100
.extern continueAt8019e154
.extern continueAt8019e140

.global TimeCmpwi100
TimeCmpwi100:								
	cmpwi r0, 100
	bgt		TimeIsBgt100				#if time is greater than 100 branch to TimeIsBgt100
	b		continueTimerLeq100			#else return to orginal code for is less or equals 100


.global TimeIsBgt100
TimeIsBgt100:
	lis		r4, slowDownTime@h			#Store slowDownTime address in r4
	ori		r4, r4, slowDownTime@l
	lbz		r0, 0x0(r4)					#Store slowDownTime value in r0
	cmpwi	r0, 0x1						#If slowDownTime = True
	beq		slowDownMusic				#Slow down the music
	b		updateUI					#return to original code


.global slowDownMusic
slowDownMusic:
	li		r0, 0x0						#Load false in r0
	stb		r0, 0xb(r31)				#Store r0 in paused
	li 		r4, 0x10
	lwz		r3, -0x51f8(r13)
	bl		ApparentlyStartsMusic		#start slowed down music
	b		updateUI					#return to original code



.global speedSelection
speedSelection:
	cmpwi	r0, 0x0
	beq		continueForNormalSpeed
	lis		r3, slowDownTime@h			#Store slowDownTime address in r3
	ori		r3, r3, slowDownTime@l
	lbz		r0, 0x0(r3)					#Store slowDownTime value in r0
	cmpwi	r0, 0x1						#if slowDownTime is true ...
	li		r0, 0x0						
	stb		r0, 0x0(r3)					#Store false at r3 aka slowDownTime
	beq		continueForNormalSpeed		#... goto continueForNormalSpeed
	b		continueAt8019e140


.global continueForNormalSpeed			#roundabout return to original code because Kamek is bad!
continueForNormalSpeed:
	b		continueAt8019e154