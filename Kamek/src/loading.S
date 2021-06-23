.text
.align 4
.set sp, 1

.extern ContinueFromLoadingCRSIN
.global aI_kinoko_3, aI_fireflower_2, aI_iceflower_0, aI_star_0, aI_propeller_0, aI_penguin, aI_hammer_0, aI_boomerang_0, aI_spike_0, aI_bobomb_0, aI_frog_0, aI_thunder_0, aI_cloud_0

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

.global LoadThisShit
LoadThisShit:
	lis r5, LoadListArray@h
	ori r5, r5, LoadListArray@l
	b ContinueFromLoadingCRSIN

LoadListArray: 
	.long aMario_0								# "Mario"
	.long aLuigi_0								# "Luigi"
	.long aKinopio_0							# "Kinopio"
	.long aYoshi_1								# "Yoshi"
	.long aP_rcha_2								# "P_rcha"
	.long aL_rcha_0								# "L_rcha"
	.long aK_rcha_0								# "K_rcha"
	.long aY_rcha_0								# "Y_rcha"
	.long aY_texgreen_0							# "Y_TexGreen"
	.long aY_texred_0							# "Y_TexRed"
	.long aY_texyellow_0						# "Y_TexYellow"
	.long aY_texblue_0							# "Y_TexBlue"
	.long aObj_coin_3							# "obj_coin"
	.long aBalloon_0							# "balloon"
	.long aI_kinoko_3							# "I_kinoko"
	.long aI_fireflower_2						# "I_fireflower"
	.long aI_iceflower_0						# "I_iceflower"
	.long aI_star_0								# "I_star"
	.long aI_propeller_0						# "I_propeller"
	.long aI_penguin							# "I_penguin"
	.long aI_yoshi_egg_0						# "I_yoshi_egg"
	.long aBlock_tsuta							# "block_tsuta"
	.long aTeresa_0								# "teresa"
	.long aJump_step							# "jump_step"
	.long aIce_4								# "ice"
	.long aIce_piece_0							# "ice_piece"
	.long aObj_dokan_6							# "obj_dokan"
	.long aObj_door_3							# "obj_door"
	.long aObj_kusa_0							# "obj_kusa"
	.long aObj_hana								# "obj_hana"
	.long aObj_hana_dai_0						# "obj_hana_daishizen"
	.long aBlock_jump_0							# "block_jump"
	.long aObj_chikuwa__0						# "obj_chikuwa_block"
	.long aLift_rakka_a_0						# "lift_rakka_ashiba"
	.long aMask_3								# "Mask"
	.long aI_hammer_0							# "I_hammer"
	.long aHammerM_0							# "hammerM"
	.long aBros_0								# "bros"
	.long aGabon_rock_0							# "gabon_rock"
	.long aI_boomerang_0						# "I_boomerang"
	.long aBoomerangM_0							# "boomerangM"
	.long aI_spike_0							# "I_spike"
	.long aSpikeM_0								# "spikeM"
	.long aI_bobomb_0							# "I_bobomb"
	.long aBobombM_0							# "bobombM"
	.long aBomhei_0								# "bombhei"
	.long aI_frog_0								# "I_frog"
	.long aFrogM_0								# "frogM"
	.long aI_thunder_0							# "I_thunder"
	.long aThunderM_0							# "thunderM"
	.long aI_cloud_0							# "I_cloud"
	.long aCloudM_0								# "cloudM"
#	.long aGalaxy7_0							# "galaxy7"
#	.long aGalaxy_0								# "galaxy"
#	.long aGalaxy2_0							# "galaxy2"
#	.long aGalaxy3_0							# "galaxy3"
#	.long aGalaxy4_0							# "galaxy4"
#	.long aGalaxy5_0							# "galaxy5"
#	.long aGalaxy6_0							# "galaxy6"

aMario_0:
	.string "Mario"                          # DATA XREF: .data.10.d_basesNP.rel:5:off_8098C40C↓o
	.byte 0
	.short 0
aLuigi_0:
	.string "Luigi"                          # DATA XREF: .data.10.d_basesNP.rel:5:8098C410↓o
	.byte 0
	.short 0
aKinopio_0:
	.string "Kinopio"                      # DATA XREF: .data.10.d_basesNP.rel:5:8098C414↓o
	.byte 0
aYoshi_1:
	.string "Yoshi"                          # DATA XREF: .data.10.d_basesNP.rel:5:8098C418↓o
	.byte 0
	.short 0
aP_rcha_2:
	.string "P_rcha"                        # DATA XREF: .data.10.d_basesNP.rel:5:8098C41C↓o
	.byte 0
	.byte 0
aL_rcha_0:
	.string "L_rcha"                        # DATA XREF: .data.10.d_basesNP.rel:5:8098C420↓o
	.byte 0
	.byte 0
aK_rcha_0:
	.string "K_rcha"                        # DATA XREF: .data.10.d_basesNP.rel:5:8098C424↓o
	.byte 0
	.byte 0
aY_rcha_0:
	.string "Y_rcha"                        # DATA XREF: .data.10.d_basesNP.rel:5:8098C428↓o
	.byte 0
	.byte 0
aY_texgreen_0:
	.string "Y_TexGreen"                # DATA XREF: .data.10.d_basesNP.rel:5:8098C42C↓o
	.byte 0
	.byte 0
aY_texred_0:
	.string "Y_TexRed"                    # DATA XREF: .data.10.d_basesNP.rel:5:8098C430↓o
	.byte 0
	.byte 0, 0, 0
aY_texyellow_0:
	.string "Y_TexYellow"              # DATA XREF: .data.10.d_basesNP.rel:5:8098C434↓o
	.byte 0
aY_texblue_0:
	.string "Y_TexBlue"                  # DATA XREF: .data.10.d_basesNP.rel:5:8098C438↓o
	.byte 0
	.short 0
aObj_coin_3:
	.string "obj_coin"                    # DATA XREF: .data.10.d_basesNP.rel:5:8098C43C↓o
	.byte 0
	.byte 0, 0, 0
	.long 0
aBalloon_0:
	.string "balloon"                      # DATA XREF: .data.10.d_basesNP.rel:5:8098C440↓o
	.byte 0
aI_kinoko_3:
	.string "I_kinoko"                    # DATA XREF: .data.10.d_basesNP.rel:5:8098C444↓o
	.byte 0
	.byte 0, 0, 0
aI_fireflower_2:
	.string "I_fireflower"            # DATA XREF: .data.10.d_basesNP.rel:5:8098C448↓o
	.byte 0
	.byte 0, 0, 0
aI_iceflower_0:
	.string "I_iceflower"              # DATA XREF: .data.10.d_basesNP.rel:5:8098C44C↓o
	.byte 0
aI_star_0:
	.string "I_star"                        # DATA XREF: .data.10.d_basesNP.rel:5:8098C450↓o
	.byte 0
	.align 2
aI_propeller_0:
	.string "I_propeller"              # DATA XREF: .data.10.d_basesNP.rel:5:8098C454↓o
	.byte 0
aI_penguin:
	.string "I_penguin"                    # DATA XREF: .data.10.d_basesNP.rel:5:8098C458↓o
	.byte 0
	.short 0
aI_yoshi_egg_0:
	.string "I_yoshi_egg"              # DATA XREF: .data.10.d_basesNP.rel:5:8098C45C↓o
	.byte 0
aBlock_tsuta:
	.string "block_tsuta"                # DATA XREF: .data.10.d_basesNP.rel:5:8098C460↓o
	.byte 0
aTeresa_0:
	.string "teresa"                        # DATA XREF: .data.10.d_basesNP.rel:5:8098C464↓o
	.byte 0
	.byte 0
aJump_step:
	.string "jump_step"                    # DATA XREF: .data.10.d_basesNP.rel:5:8098C468↓o
	.byte 0
	.short 0
aIce_4:
	.string "ice"                              # DATA XREF: .data.10.d_basesNP.rel:5:8098C46C↓o
	.byte 0
aIce_piece_0:
	.string "ice_piece"                  # DATA XREF: .data.10.d_basesNP.rel:5:8098C470↓o
	.byte 0
	.align 2
aObj_dokan_6:
	.string "obj_dokan"                  # DATA XREF: .data.10.d_basesNP.rel:5:8098C474↓o
	.byte 0
	.align 2
aObj_door_3:
	.string "obj_door"                    # DATA XREF: .data.10.d_basesNP.rel:5:8098C478↓o
	.byte 0
	.align 2
aObj_kusa_0:
	.string "obj_kusa"                    # DATA XREF: .data.10.d_basesNP.rel:5:8098C47C↓o
	.byte 0
	.byte 0, 0, 0
aObj_hana:
	.string "obj_hana"                      # DATA XREF: .data.10.d_basesNP.rel:5:8098C480↓o
	.byte 0
	.byte 0, 0, 0
aObj_hana_dai_0:
	.string "obj_hana_daishizen"      # DATA XREF: .data.10.d_basesNP.rel:5:8098C484↓o
	.byte 0
	.byte 0
aBlock_jump_0:
	.string "block_jump"                # DATA XREF: .data.10.d_basesNP.rel:5:8098C488↓o
	.byte 0
	.byte 0
aObj_chikuwa__0:
	.string "obj_chikuwa_block"       # DATA XREF: .data.10.d_basesNP.rel:5:8098C48C↓o
	.byte 0
	.short 0
aLift_rakka_a_0:
	.string "lift_rakka_ashiba"       # DATA XREF: .data.10.d_basesNP.rel:5:8098C490↓o
	.byte 0
	.short 0
aMask_3:
	.string "Mask"                            # DATA XREF: .data.10.d_basesNP.rel:5:8098C494↓o
	.byte 0
	.byte 0, 0, 0
aI_hammer_0:
	.string "I_hammer"
	.byte 0
	.byte 0
aHammerM_0:
	.string "hammerM"
	.byte 0
	.byte 0
aBros_0:
	.string "bros"
	.byte 0
	.byte 0
aGabon_rock_0:
	.string "gabon_rock"
	.byte 0
	.byte 0
aPower_cloud_0:
	.string "power_cloud"
	.byte 0
	.byte 0
aI_boomerang_0:
	.string "I_boomerang"
	.byte 0
	.byte 0
aBoomerangM_0:
	.string "boomerangM"
	.byte 0
	.byte 0
aI_spike_0:
	.string "I_spike"
	.byte 0
	.byte 0
aSpikeM_0:
	.string "spikeM"
	.byte 0
	.byte 0
aI_bobomb_0:
	.string "I_bobomb"
	.byte 0
	.byte 0
aBobombM_0:
	.string "bobombM"
	.byte 0
	.byte 0
aBomhei_0:
	.string "bombhei"
	.byte 0
	.byte 0
aI_frog_0:
	.string "I_frog"
	.byte 0
	.byte 0
aFrogM_0:
	.string "frogM"
	.byte 0
	.byte 0
aI_thunder_0:
	.string "I_thunder"
	.byte 0
	.byte 0
aThunderM_0:
	.string "thunderM"
	.byte 0
	.byte 0
aI_cloud_0:
	.string "I_cloud"
	.byte 0
	.byte 0
aCloudM_0:
	.string "cloudM"
	.byte 0
	.byte 0
aGalaxy_0:
	.string "galaxy"
	.byte 0
	.byte 0
aGalaxy2_0:
	.string "galaxy2"
	.byte 0
	.byte 0
aGalaxy3_0:
	.string "galaxy3"
	.byte 0
	.byte 0
aGalaxy4_0:
	.string "galaxy4"
	.byte 0
	.byte 0
aGalaxy5_0:
	.string "galaxy5"
	.byte 0
	.byte 0
aGalaxy9_0:
	.string "galaxy9"
	.byte 0
	.byte 0
aGalaxy7_0:
	.string "galaxy7"
	.byte 0
	.byte 0