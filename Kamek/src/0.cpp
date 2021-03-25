#include <game.h>

//#include "0.h"
u8 LastLevelPlayed[2] = {0xFF,0xFF};	//Powerup Jam fix
//bool enableDebugMode = true;			//Powerup Jam fix


void Test() {
	//OSReport("DoSceneChange finished\n");
	//SaveBlock *save = GetSaveFile()->GetBlock(-1);
	//save->addToLevelNum = 0;
	//OSReport("addToLevelNum: %p\n", save->addToLevelNum);
	
}




/*
stockItemLayoutCreate(){
	dStockItem_c *stockItem;
	stockItem = (dStockItem_c*)CreateParentedObject(STOCK_ITEM, this, 0, 0);
	
}*/



extern "C" int dStockItem(int i);
int dStockItemCreate(int i) {
	int orig_val = dStockItem(i);
	
	//OSReport("Orig: %p\n", orig_val);
	
	//DVD_LoadFile(GetDVDClass(), "Maps", "SI_hammer", 0);
	//if (orig_val==0) {
	//	OSReport("Loaded stockItem!\n");
	//	//DVD_LoadFile(GetDVDClass(), "Maps", "SI_hammer", 0);
	//	OSReport("Loaded SI_hammer!\n");
	//}
	
	return orig_val;
}










int AddToLevelNum(int orig) {
	//orig += GetSaveFile()->GetBlock(-1)->addToLevelNum;
	return orig;
}

extern u8 World;
int subWorld = 1;
int pointNode = 5;
extern u8 AssembleScWorldMapSettings(u8 world, int subworld, int pointNode);
extern void DoShitWithWMPlayer(int node);
extern char CS_ptr1[4];
extern char CS_ptr2[4];
extern char CS_ptr3[4];
extern char CS_ptr4[4];
extern char aWorld1;
extern char aWorld2;


//extern int reportCrashAdress;


extern int goToSpecificWorld(int world, int supworld, int node);

void wmtest() {
	
	SaveBlock *save = GetSaveFile()->GetBlock(-1);
	save->powerups_available[6]=10;
	save->addToLevelNum = 0;
	/*Remocon wiimote = *GetActiveRemocon();
	OSReport("lastHeldButtons: %p\n\n", wiimote.lastHeldButtons);*/
	
	
	//nw4r::g3d::Camera cam(GetCameraByID(GetCurrentCameraID()));


	if(Remocon_GetPressed(GetActiveRemocon()) & WPAD_B){
		SaveGame(0, false);
		//------------------------------------------------------------------------------------------------------------------------------
		/*void* reportCrashAdressAdress = &reportCrashAdress;
		int asmAdress = (int)reportCrashAdressAdress;
		asmAdress -= 0x80000300;
		asmAdress += 0x48000000;
		OSReport("reportCrashAdressAdress: %x\n", asmAdress);

		int* nopAddress = (int*)0x80000300;
		*nopAddress = asmAdress;*/

		//while(true){}
		//OSReport("Creating an exception here!\n");
		//typedef int func(void);
		//func* f = (func*)0x80000300;
		//int i = f();


		//OSReport("wm loop\n\n\n\n");


	//Print all played level conditions
	/*for(int i = 0; i < 10; i++) {
	OSReport("\nWorld: %p\n", i);
		for(int j = 0; j < 42; j++) {
			u32 conds = save->GetLevelCondition(i, j);
			if(conds > 0) {
				OSReport("Level: %p, 1: %p, 2: %p, 3: %p, Normal: %p, Secret: %p, SGNormal: %p, SGSecret: %p, Unlocked: %p\n", j, conds&COND_COIN1, conds&COND_COIN2, conds&COND_COIN3, conds&COND_NORMAL, conds&COND_SECRET, conds&COND_SGNORMAL, conds&COND_SGSECRET, conds&COND_UNLOCKED);
			}
		}
		//SetSomeConditionShit(i, 0, 0x40);
	}*/




		
		int world = 0x00000500 + World;
		if(save->addToLevelNum == 0){
			save->addToLevelNum = 10;
			OSReport("1: %p, 2: %p\n", aWorld1, aWorld2);
			/*aWorld1 = 'b';
			aWorld2 = 'b';
			CS_ptr1[3] = 'S';
			CS_ptr2[3] = 'S';
			CS_ptr3[3] = 'S';
			CS_ptr4[3] = 'S';*/
			
			OSReport("b World\n");
			OSReport("1: %p, 2: %p\n", aWorld1, aWorld2);
		} else {
			save->addToLevelNum = 0;
			
			
			/*aWorld1 = 'a';
			aWorld2 = 'a';*/
			OSReport("a World\n");
		}
		
		
		for(int i = 0; i < 4; i++){
			OSReport("%p\n", CS_ptr1[i]);
		}
		


		
		goToSpecificWorld(World, 1, 5);
		DoShitWithWMPlayer(5);
		ActivateWipe(WIPE_MARIO);
		//DoSceneChange(WORLD_MAP, AssembleScWorldMapSettings(World, 1, 5), 0);
		//DoSceneChange(WORLD_MAP, World, 0);
		OSReport("Success!!!\n\n\n\n");
		
			CS_ptr1[3] = 'W';
			CS_ptr2[3] = 'W';
			CS_ptr3[3] = 'W';
			CS_ptr4[3] = 'W';
		OSReport("Changed back!\n");
	}
}

u8 getActualLevelNum(u8 level) {
	if(GetSaveFile()->GetBlock(-1)->addToLevelNum == 10) {
		switch(level) {
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
				level += 9;
				break;
			case 20:
			case 21:
				level -= 4;
				break;
			case 23:
				level -= 5;
				break;
			case 35:
			case 37:
				level -= 13;
				break;
			default:
				break;
		}
	}
	return level;
}


u8 SetLevelIdentifier(u8 world,u8 level,u8 *world_ptr,u8 *level_ptr) {
	//OSReport("1: %p, 2: %p, 3: %p, 4: %p\n\n", world, level, world_ptr, level_ptr);
	//level += 1;

	level = getActualLevelNum(level);

	*world_ptr = world;
	*level_ptr = level;
	//OSReport("1: %p, 2: %p, 3: %p, 4: %p\n\n", world, level, world_ptr, level_ptr);
	return 1;
}





void SetConditionInWorldDataForWorldAndLevel(int structWithWorldData, int world, int level, unsigned int condition) {
	//OSReport("SetConditionInWorldDataForWorldAndLevel: %p, %p, %p, %p\n\n", structWithWorldData, world, level, condition);
	
	level = getActualLevelNum(level);
	
	int iVar1;
	iVar1 = structWithWorldData + world * 0xa8 + level * 4;
	*(unsigned int *)(iVar1 + 0x6c) = *(unsigned int *)(iVar1 + 0x6c) | condition;
	return;
}

unsigned int CheckIfConditionIsCompletedForWorldAndLevel(int structWithWorldData,int world,int level,unsigned int condition) {
	OSReport("CheckIfConditionIsCompletedForWorldAndLevel: %p, %p, %p, %p\n\n", structWithWorldData, world, level, condition);
	condition = condition & *(unsigned int *)(structWithWorldData + world * 0xa8 + level * 4 + 0x6c);
	return (-condition | condition) >> 0x1f;
}





void SetSpecificStarCoinToCollected(int structWithWorldData, int world, int level, unsigned int condition) {
	//OSReport("SetSpecificStarCoinToCollected: %p, %p, %p, %p\n\n", structWithWorldData, world, level, condition);

	
	level = getActualLevelNum(level);

	int iVar1;
	iVar1 = structWithWorldData + world * 0xa8 + level * 4;
	*(unsigned int *)(iVar1 + 0x6c) = *(unsigned int *)(iVar1 + 0x6c) | condition & 7;
	return;
}


unsigned int CheckIfWeHaveASpecificStarCoin(int structWithWorldData, int world, int level, int starCoin) {
	//OSReport("CheckIfWeHaveASpecificStarCoin: %p, %p, %p, %p\n\n", structWithWorldData, world, level, starCoin);

	level = getActualLevelNum(level);

	return 1 << starCoin & *(unsigned int *)(structWithWorldData + world * 0xa8 + level * 4 + 0x6c) & 0xff;
}

/*
504 -> Welt 5
501 -> Welt 2
500 -> Welt 1
*/














/*float rewrite_fail(char *str) {
	return 1.0f;
}

float rewrite(char *str) {
	float fVar1;
	int iVar2;
	float fVar3;
	if (*str == 'W') {
		fVar1 = (float)atoi(str + 3);
		switch(str[2]) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			iVar2 = atoi(str + 3);
			fVar3 = (float)(iVar2 + -0x40800001);
			break;
		case 'A':
			fVar3 = fVar1;
			break;
		case 'C':
			fVar3 = fVar1;
			break;
		case 'G':
			fVar3 = fVar1;
			break;
		case 'K':
			fVar3 = 1.00000000;
			break;
		case 'S':
			fVar3 = 1.00000000;
			break;
		case 'T':
			fVar3 = fVar1;
			break;
		case 'W':
			fVar3 = (float)((int)fVar1 + (int)168.00000000);
			break;
		case 'X':
			fVar3 = -999999.87500000;
		}
	}
	return fVar3;
}
*/
