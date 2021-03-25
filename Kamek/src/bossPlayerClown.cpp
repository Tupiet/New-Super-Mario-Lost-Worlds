#include <common.h>
#include <game.h>
#include <g3dhax.h>
#include <sfx.h>
#include "boss.h"

// #define cField(TYPE, OFFSET) (*(TYPE*)(((u32)clown) + (OFFSET)))
// #define cPlayerOccupying cField(dStageActor_c*, 0x738)
// #define cModel cField(m3d::mdl_c*, 0xFEC)
// #define cTimer cField(u32, 0xFEC+sizeof(m3d::mdl_c))
// #define cAllocator cField(mHeapAllocator_c*, 0xFD0)

#define cPlayerOccupying (*(dStageActor_c**)(((u32)(clown)) + 0x738 ))
#define cAllocator ((mHeapAllocator_c*)(((u32)(clown)) + 0xFD0 ))
#define cModel ((m3d::mdl_c*)( ((u32)(clown)) + 0xFEC ))
#define cTimer (*(u32*)((u32)(clown) + sizeof(m3d::mdl_c) + 0xFEC ))

extern "C" int PClownCarExecute(dEn_c *clown);
extern "C" void PClownCarAfterCreate(dEn_c *clown, u32);
extern "C" int PClownCarDraw(dEn_c *clown);
extern "C" void PClownCarMove(dEn_c *clown);


const char* PCCarcNameList [] = {
	"koopaJr_clown_ply",
	NULL
};



int CConDraw(dEn_c *clown) {
	// setup cannon model
	clown->matrix.translation(clown->pos.x, clown->pos.y + 8.0, clown->pos.z-100.0);
	short newrotz = -0x2000;
	short newroty = ((clown->rot.y * 0x4000) / 0x800) - 0x4000;
	short newrotx;
	if (clown->rot.x < 0x8000) {
		newrotx = -clown->rot.x;
	}
	else {
		newrotx = clown->rot.x;
	}
	// OSReport("Angle?: %x, %x", clown->rot.y, newroty);
	clown->matrix.applyRotationYXZ(&clown->rot.x, &newroty, &newrotz);

	cModel->setDrawMatrix(clown->matrix);
	if(clown->settings >> 4 & 1) {
		cModel->setScale(&(Vec){0.25, 0.5, 0.25});
	} else {
		cModel->setScale(&(Vec){0.0, 0.0, 0.0});
	}
	cModel->calcWorld(false);

	cModel->scheduleForDrawing();


	return PClownCarDraw(clown);
	// run normal clown function
}
extern dStateBase_c JrClownEndDemoState;
extern dStateBase_c JrClownDemoWaitState;
extern dStateBase_c ClownDemoWaitState;

int CConExecute(dEn_c *clown) {
	// A REALLY TERRIBLE HACK.
	float saveX = clown->pos.x;
	float saveY = clown->pos.y;

	int ret = PClownCarExecute(clown);

	dStateBase_c *state = clown->acState.getCurrentState();
	if (state == &JrClownEndDemoState || state == &JrClownDemoWaitState || state == &ClownDemoWaitState) {
		clown->pos.x = saveX;
		clown->pos.y = saveY;
		clown->speed.x = 0.0f;
		clown->speed.y = 0.0f;
	}
}

void CCafterCreate(dEn_c *clown, u32 param) {

	clown->scale.x *= 1.25;
	clown->scale.y *= 1.25;
	clown->scale.z *= 1.25;

	// setup the model
	nw4r::g3d::ResFile resFile;

	cAllocator->link(-1, GameHeaps[0], 0, 0x20);

	resFile.data = getResource("koopaJr_clown_ply", "g3d/cannon.brres");
	nw4r::g3d::ResMdl mdl = resFile.GetResMdl("Cannon");
	cModel->setup(mdl, cAllocator, 0x224, 1, 0);
	SetupTextures_MapObj(cModel, 0);

	cAllocator->unlink();

	// Original AfterCreate
	PClownCarAfterCreate(clown, param);

	int playerCount = 0;
	for (int i = 0; i < 4; i++)
		if (Player_Active[i])
			playerCount++;

	if ((clown->settings & 0xF) != 0) {
		int playerID = (clown->settings & 0xF) - 1;
		if (playerID >= playerCount)
			clown->Delete(1);
	}
}

void CConExecuteMove(dEn_c *clown) {
	if(clown->settings >> 4 & 1) {

		u8 player = cPlayerOccupying->which_player;
		// OSReport("Angle = %x, %x, %x", (GetSpecificPlayerActor(player))->rot.y, (GetSpecificPlayerActor(player))->rot.x, (GetSpecificPlayerActor(player))->rot.z);
		// OSReport("Clown = %x, %x, %x", (clown)->rot.y, (clown)->rot.x, (clown)->rot.z);

		Vec tempPos;
		
		u32 buttonPushed = Remocon_GetPressed(GetRemoconMng()->controllers[cPlayerOccupying->which_player]);
		if (buttonPushed & 0x0100) {

			if (cTimer > 90) {
				if (clown->direction == 0) { // Going right
					tempPos = (Vec){clown->pos.x + 32.0, clown->pos.y + 32.0, 3564.0};
					//dStageActor_c *spawned = CreateActor(657, 0, tempPos, 0, 0);
					//spawned->speed.x = 5.0;
				}
				else {
					tempPos = (Vec){clown->pos.x - 32.0, clown->pos.y + 32.0, 3564.0};
					//dStageActor_c *spawned = CreateActor(657, 0, tempPos, 0, 0);
					//spawned->speed.x = -5.0;
				}

				SpawnEffect("Wm_en_killervanish", 0, &tempPos, &(S16Vec){0,0,0}, &(Vec){0.1, 0.1, 0.1});
				nw4r::snd::SoundHandle handle;
				PlaySoundWithFunctionB4(SoundRelatedClass, &handle, SE_OBJ_HOUDAI_S_SHOT, 1);

			cTimer = 0;
			}
		}

		cTimer++;

		ClassWithCameraInfo *cwci = ClassWithCameraInfo::instance;
		float leftBound = cwci->screenLeft + 12.0f;
		float rightBound = (cwci->screenLeft + cwci->screenWidth) - 12.0f;
		if (clown->pos.x < leftBound)
			clown->pos.x = leftBound;
		if (clown->pos.x > rightBound)
			clown->pos.x = rightBound;
	}

	// run normal move
	PClownCarMove(clown);
}


extern "C" m3d::mdl_c *__ct__Q23m3d5mdl_cFv(m3d::mdl_c *mdl);
extern "C" mHeapAllocator_c *__ct__16mHeapAllocator_cFv(mHeapAllocator_c *al);
extern "C" dEn_c *__ct__20daJrClownForPlayer_cFv(dEn_c *clown);

dEn_c *newClownCtor(dEn_c *clown) {
	__ct__20daJrClownForPlayer_cFv(clown);
	__ct__16mHeapAllocator_cFv(cAllocator);
	__ct__Q23m3d5mdl_cFv(cModel);
	return clown;
}


extern "C" void __dt__Q23m3d5mdl_cFv(m3d::mdl_c *mdl, u32 willDelete);
extern "C" void __dt__16mHeapAllocator_cFv(mHeapAllocator_c *al, u32 willDelete);
extern "C" void __dt__20daJrClownForPlayer_cFv(dEn_c *clown, u32 willDelete);

extern "C" u32 sAllocatorFunc__FrmHeap;

void newClownDtor(dEn_c *clown, u32 willDelete) {
	void **al = (void **)(((u32)clown) + 0x524);
	if (*al != &sAllocatorFunc__FrmHeap) {
		OSReport("oh no! bad allocator %p\n", *al);
		*al = &sAllocatorFunc__FrmHeap;
	}

	__dt__Q23m3d5mdl_cFv(cModel, 0xFFFFFFFF);
	__dt__16mHeapAllocator_cFv(cAllocator, 0xFFFFFFFF);
	__dt__20daJrClownForPlayer_cFv(clown, willDelete);
}

extern "C" void JrClownForPlayer_playAccelSound() {
	nw4r::snd::SoundHandle handle;
	PlaySoundWithFunctionB4(SoundRelatedClass, &handle, SE_PLY_CROWN_ACC, 1);
}