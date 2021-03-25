.text
.align 4
.set sp, 1

.extern DoFrogFootsteps
.extern DontDoFrogFootsteps
.extern NoSwimBegin
.extern YesSwimBegin
.extern NoSwimHip0a
.extern YesSwimHip0a
.extern NoSwimHip0b
.extern YesSwimHip0b
.extern NoSwimHip1
.extern YesSwimHip1
.extern NoSwimHip2
.extern YesSwimHip2
.extern NoSwimHip3a
.extern YesSwimHip3a
.extern NoSwimHip3b
.extern YesSwimHip3b

#ifndef __MWERKS__
.set r0,0;   .set r1,1;   .set r2,2; .set r3,3;   .set r4,4
.set r5,5;   .set r6,6;   .set r7,7;   .set r8,8;   .set r9,9
.set r10,10; .set r11,11; .set r12,12; .set r13,13; .set r14,14
.set r15,15; .set r16,16; .set r17,17; .set r18,18; .set r19,19
.set r20,20; .set r21,21; .set r22,22; .set r23,23; .set r24,24
.set r25,25; .set r26,26; .set r27,27; .set r28,28; .set r29,29
.set r30,30; .set r31,31; .set f0,0; .set f2,2; .set f3,3
.set f1,1;   .set f30,30; .set f31,31
#endif

.global FrogFootsteps
FrogFootsteps:
	cmpwi r0, 5			#If current powerup isn't penguin
	bne notPenguin		#Then notPenguin
	b DoFrogFootsteps	#Otherwise, DoFrogFootsteps
notPenguin:
	cmpwi r0, 11				#If current powerup isn't frog neither
	bne _DontDoFrogFootsteps	#Then DontDoFrogFootsteps
	b DoFrogFootsteps			#Otherwise, DoFrogFootsteps
_DontDoFrogFootsteps:
	b DontDoFrogFootsteps
#So basically, Treeki was too lazy to implement rel type 11, so i can't "beq" or "bne" externs, so i have to do it on another function that then calls the extern in question.

.global FrogSwimBegin
FrogSwimBegin:
	cmpwi r0, 5
	bne stillNotPenguin
	b YesSwimBegin
stillNotPenguin:
	cmpwi r0, 11
	bne _NoSwimBegin
	b YesSwimBegin
_NoSwimBegin:
	b NoSwimBegin


.global FrogSwimHip0a
FrogSwimHip0a:
	cmpwi r0, 5
	bne nyehNotPenguinA
	b YesSwimHip0a
nyehNotPenguinA:
	cmpwi r0, 11
	bne _NoSwimHip0a
	b YesSwimHip0a
_NoSwimHip0a:
	b NoSwimHip0a


.global FrogSwimHip0b
FrogSwimHip0b:
	cmpwi r0, 5
	beq _YesSwimHip0b
	cmpwi r0, 11
	beq _YesSwimHip0b
	b NoSwimHip0b
_YesSwimHip0b:
	b YesSwimHip0b


.global FrogSwimHip1
FrogSwimHip1:
	cmpwi r0, 5
	bne bruhNotPenguin
	b YesSwimHip1
bruhNotPenguin:
	cmpwi r0, 11
	bne _NoSwimHip1
	b YesSwimHip1
_NoSwimHip1:
	b NoSwimHip1


.global FrogSwimHip2
FrogSwimHip2:
	cmpwi r0, 5
	bne grrNotPenguin
	b YesSwimHip2
grrNotPenguin:
	cmpwi r0, 11
	bne _NoSwimHip2
	b YesSwimHip2
_NoSwimHip2:
	b NoSwimHip2


.global FrogSwimHip3a
FrogSwimHip3a:
	cmpwi r0, 5
	beq _YesSwimHip3a
	cmpwi r0, 11
	beq _YesSwimHip3a
	b NoSwimHip3a
_YesSwimHip3a:
	b YesSwimHip3a


.global FrogSwimHip3b
FrogSwimHip3b:
	cmpwi r0, 5
	bne owoNotPenguin
	b YesSwimHip3b
owoNotPenguin:
	cmpwi r0, 11
	bne _NoSwimHip3b
	b YesSwimHip3b
_NoSwimHip3b:
	b NoSwimHip3b