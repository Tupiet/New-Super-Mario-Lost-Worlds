.text
.align 4

#include <asm_setup.S>

.extern CreateActor
.extern GenerateRandomNumber


.global checkKoopaSettingsLR
checkKoopaSettingsLR:
	stb r0, 0x348(r31)						# restore patched instruction

	stwu sp, -0x20(sp)						# save registers for restore after hack
	mflr r0
	stw r0, 0x24(sp)
	stw r3, 0x1C(sp)
	stw r4, 0x18(sp)
	stw r5, 0x14(sp)
	stw r6, 0x10(sp)
	stw r7, 0x6(sp)

	lbz r3, 0x5(r31)						# load settings
	andi. r3, r3, 0x2						# only leave Reggie bit 31
	cmpwi r3, 0								# if bit 31 is set
	bgt throwRingLR							# make Koopa throw a ring

	bl restoreRegistersForKoopa				# alternatively only restore registers
	blr										# return to original function


.global checkKoopaSettingsUD
checkKoopaSettingsUD:
	stw r0, 0x360(r31)						# restore patched instruction

	stwu sp, -0x20(sp)						# save registers for restore after hack
	mflr r0
	stw r0, 0x24(sp)
	stw r3, 0x1C(sp)
	stw r4, 0x18(sp)
	stw r5, 0x14(sp)
	stw r6, 0x10(sp)
	stw r7, 0x6(sp)

	lbz r3, 0x5(r31)						# load settings
	andi. r3, r3, 0x2						# only leave Reggie bit 31
	cmpwi r3, 0								# if bit 31 is set
	bgt throwRingUD							# make Koopa throw a ring

	bl restoreRegistersForKoopa				# alternatively only restore registers
	blr										# return to original function



.global throwRingLR
throwRingLR:
	li r3, 3								# int max for GenerateRandomNumber function = 3
	bl GenerateRandomNumber					# generate a random number between 0 and 2
	lis r4, leftRightThrowSettings@h		# get byte array with ring settings
	ori r4, r4, leftRightThrowSettings@l	# get byte array with ring settings
	add r3, r3, r4							# add random number to get a random element of the array

	lbz r4, 0x348(r31)						# get direction the Koopa is flying to
	mulli r4, r4, 0x3						# multiply by 3 to get either 0 or 3
	add r3, r3, r4							# add it to the address of the settings array -> first 3 entries for one direction and last 3 for the other direction
	lbz r4, 0(r3)							# load the byte of the array we just selected
	li r3, 0x107							# Actor ID of Bouncing Wendy Ring
	addi r5, r31, 0xAC						# Position -> r31 stores the address of the Koopa, 0xAC is the offset to it's pos vector
	li r6, 0								# Rotation
	lbz r7, 0x38F(r31)						# Layer
	bl CreateActor
	
	bl restoreRegistersForKoopa				# restore registers
	blr


.global throwRingUD
throwRingUD:
	li r3, 3								# int max for GenerateRandomNumber function = 3
	bl GenerateRandomNumber					# generate a random number between 0 and 2
	lis r4, leftRightThrowSettings@h		# get byte array with ring settings
	ori r4, r4, leftRightThrowSettings@l	# get byte array with ring settings
	add r3, r3, r4							# add random number to get a random element of the array

	lbz r4, 0(r3)							# load the byte of the array we just selected
	li r3, 0x107							# Actor ID of Bouncing Wendy Ring
	addi r5, r31, 0xAC						# Position -> r31 stores the address of the Koopa, 0xAC is the offset to it's pos vector
	li r6, 0								# Rotation
	lbz r7, 0x38F(r31)						# Layer
	bl CreateActor
	
	bl restoreRegistersForKoopa				# restore registers
	blr										# return to original function


.global restoreRegistersForKoopa
restoreRegistersForKoopa:
	lwz r7, 0x6(sp)
	lwz r6, 0x10(sp)
	lwz r5, 0x14(sp)
	lwz r4, 0x18(sp)
	lwz r3, 0x1C(sp)
	lwz r0, 0x24(sp)
	mtlr r0
	addi sp, sp, 0x20
	blr


.align 4
.data
.global leftRightThrowSettings
leftRightThrowSettings: .byte 3, 4, 5, 1, 0, 7