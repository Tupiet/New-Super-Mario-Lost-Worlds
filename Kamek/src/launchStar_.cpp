#include <common.h>
#include <game.h>
#include <profile.h>
#include "boomeranghax.h"

const char* LaunchStarFileList[] = { "launchStar", 0 };



class daEnLaunchStar_c : public dEn_c {
public:
	int onCreate();
	int onExecute();
	int onDelete();
	int onDraw();

	mHeapAllocator_c allocator;
	nw4r::g3d::ResFile resFile;
	nw4r::g3d::ResFile resFileAnim;
	m3d::mdl_c bodyModel;

	m3d::anmChr_c chrAnimation;

	bool isSuperLaunchStar;			//Nybble 1
	bool active;					//Nybble 1
	bool isActivatedByEvent;		//Nybble 1

	int id;							//Nybble 2-3

	int xDestination;				//Nybble 4-7
	int yDestination;				//Nybble 8-11
	int destinationWorld;			//Nybble 4-5
	int destinationSubWorld;		//Nybble 6-7
	int destinationLevelNode;		//Nybble 8-11

	int xRotation;					//Nybble 12-13
	int yRotation;					//Nybble 14-15
	int rotationSpeed;				//Nybble 16



	int increaseCollected(int increment);


	static dActor_c* build();

	void bindAnimChr_and_setUpdateRate(const char* name, int unk, float unk2, float rate);

	void updateModelMatrices();
	void playerCollision(ActivePhysics* apThis, ActivePhysics* apOther);
	void yoshiCollision(ActivePhysics* apThis, ActivePhysics* apOther);

	bool collisionCat7_GroundPound(ActivePhysics* apThis, ActivePhysics* apOther);
	bool collisionCat7_GroundPoundYoshi(ActivePhysics* apThis, ActivePhysics* apOther);
	bool collisionCatD_Drill(ActivePhysics* apThis, ActivePhysics* apOther);
	bool collisionCatA_PenguinMario(ActivePhysics* apThis, ActivePhysics* apOther);

	bool collisionCat1_Fireball_E_Explosion(ActivePhysics* apThis, ActivePhysics* apOther);
	bool collisionCat2_IceBall_15_YoshiIce(ActivePhysics* apThis, ActivePhysics* apOther);
	bool collisionCat9_RollingObject(ActivePhysics* apThis, ActivePhysics* apOther);
	bool collisionCat13_Hammer(ActivePhysics* apThis, ActivePhysics* apOther);
	bool collisionCat14_YoshiFire(ActivePhysics* apThis, ActivePhysics* apOther);
	bool collisionCat3_StarPower(ActivePhysics* apThis, ActivePhysics* apOther);

	int type;
};

const SpriteData LaunchStarSpriteData = { ProfileId::LaunchStar, 8, -8 , 0 , 0, 0x100, 0x100, 0, 0, 0, 0, 0 };
Profile LaunchStarProfile(&daEnLaunchStar_c::build, SpriteId::LaunchStar, LaunchStarSpriteData, ProfileId::LaunchStar, ProfileId::LaunchStar, "LaunchStar", LaunchStarFileList);



u8 hijackMusicWithSongName(const char* songName, int themeID, bool hasFast, int channelCount, int trackCount, int* wantRealStreamID);

void daEnLaunchStar_c::playerCollision(ActivePhysics* apThis, ActivePhysics* apOther) {
	if (this->active) {
		dStageActor_c* p = apOther->owner;
		
	}
}
void daEnLaunchStar_c::yoshiCollision(ActivePhysics* apThis, ActivePhysics* apOther) {
	this->playerCollision(apThis, apOther);
}
bool daEnLaunchStar_c::collisionCat7_GroundPound(ActivePhysics* apThis, ActivePhysics* apOther) {
	return false;
}
bool daEnLaunchStar_c::collisionCat7_GroundPoundYoshi(ActivePhysics* apThis, ActivePhysics* apOther) {
	return false;
}
bool daEnLaunchStar_c::collisionCatD_Drill(ActivePhysics* apThis, ActivePhysics* apOther) {
	return false;
}
bool daEnLaunchStar_c::collisionCatA_PenguinMario(ActivePhysics* apThis, ActivePhysics* apOther) {
	return false;
}

bool daEnLaunchStar_c::collisionCat1_Fireball_E_Explosion(ActivePhysics* apThis, ActivePhysics* apOther) {
	return false;
}
bool daEnLaunchStar_c::collisionCat2_IceBall_15_YoshiIce(ActivePhysics* apThis, ActivePhysics* apOther) {
	return false;
}
bool daEnLaunchStar_c::collisionCat9_RollingObject(ActivePhysics* apThis, ActivePhysics* apOther) {

	return false;
}
bool daEnLaunchStar_c::collisionCat13_Hammer(ActivePhysics* apThis, ActivePhysics* apOther) {
	return false;
}
bool daEnLaunchStar_c::collisionCat14_YoshiFire(ActivePhysics* apThis, ActivePhysics* apOther) {
	return false;
}

bool daEnLaunchStar_c::collisionCat3_StarPower(ActivePhysics* apThis, ActivePhysics* apOther) {
	return false;
}


dActor_c* daEnLaunchStar_c::build() {
	void* buffer = AllocFromGameHeap1(sizeof(daEnLaunchStar_c));
	daEnLaunchStar_c* c = new(buffer) daEnLaunchStar_c;

	return c;
}


extern int getNybbleValue(u32 settings, int fromNybble, int toNybble);

void daEnLaunchStar_c::bindAnimChr_and_setUpdateRate(const char* name, int unk, float unk2, float rate) {
	nw4r::g3d::ResAnmChr anmChr = this->resFileAnim.GetResAnmChr(name);
	this->chrAnimation.bind(&this->bodyModel, anmChr, unk);
	this->bodyModel.bindAnim(&this->chrAnimation, unk2);
	this->chrAnimation.setUpdateRate(rate);
}

int daEnLaunchStar_c::onCreate() {

	this->isSuperLaunchStar = this->settings & 0b1;						//Bit 17 (0=false, 1=true)
	this->active = this->settings >> 1& 0b1;							//Bit 18 (0=false, 1=true)
	this->isActivatedByEvent = this->settings >> 2 & 0b1;				//Bit 19 (0=false, 1=true)

	this->id = this->settings >> 3 & 0b111111;							//Bit 20-25 (2^6=64 possible launchstars)

	if(this->isSuperLaunchStar) {
		this->destinationWorld = this->settings >> 9 & 0b1111;			//Bit 26-29 (2^4=16 main worlds)
		this->destinationSubWorld = this->settings >> 13 & 0b111;		//Bit 30-32 (2^3=8 sub worlds)
		this->destinationLevelNode = this->settings >> 16 & 0b1111111;	//Bit 33-39 (2^7=128 level nodes)
	} else {
		this->xDestination = this->settings >> 9 & 0b1111111;			//Bit 26-32 (2^7=128 different relative x positions)
		this->yDestination = this->settings >> 16 & 0b1111111;			//Bit 33-39 (2^7=128 different relative x positions)
	}

	this->xRotation = this->settings >> 23 & 0b111;						//Bit 40-42 (2^3=8 values)
	this->yRotation = this->settings >> 26 & 0b111;						//Bit 43-45 (2^3=8 values)
	this->rotationSpeed = this->settings >> 29 & 0b111;					//Bit 46-48 (2^3=8 values)



	this->deleteForever = true;

	// Model creation
	allocator.link(-1, GameHeaps[0], 0, 0x20);

	this->resFile.data = getResource("launchStar", "g3d/launchStar.brres");
	nw4r::g3d::ResMdl mdl = this->resFile.GetResMdl("LaunchStar");
	bodyModel.setup(mdl, &allocator, 0x224, 1, 0);
	SetupTextures_Player(&bodyModel, 0);


	this->resFileAnim.data = getResource("launchStar", "g3d/launchStarAnim.brres");
	nw4r::g3d::ResAnmChr anmChr = this->resFileAnim.GetResAnmChr("idle");
	this->chrAnimation.setup(mdl, anmChr, &this->allocator, 0);

	allocator.unlink();

	ActivePhysics::Info HitMeBaby;

	HitMeBaby.xDistToCenter = 0.0;
	HitMeBaby.yDistToCenter = 0.0;

	HitMeBaby.xDistToEdge = 7.5;
	HitMeBaby.yDistToEdge = 7.5;

	HitMeBaby.category1 = 0x3;
	HitMeBaby.category2 = 0x0;
	HitMeBaby.bitfield1 = 0x4F;
	HitMeBaby.bitfield2 = 0x8028E;
	HitMeBaby.unkShort1C = 0;
	HitMeBaby.callback = &dEn_c::collisionCallback;

	this->aPhysics.initWithStruct(this, &HitMeBaby);
	this->aPhysics.addToList();

	this->disableEatIn();

	// Stuff I do understand
	this->scale = (Vec){ 0.2, 0.2, 0.2 };

	this->rot.x = 0;
	this->rot.y = 0;
	this->rot.z = 0;

	this->pos.z = 4000;

	daEnLaunchStar_c::bindAnimChr_and_setUpdateRate("idle", 1, 0.0, 1.0);

	this->id = this->settings >> 24 & 0xF;
	//this->collected = 0;

	if (type == 0) {
		this->active = false;
	} else {
		this->active = true;
	}
	this->active = true;


	this->onExecute();
	return true;
}


int daEnLaunchStar_c::onDelete() {
	return true;
}

int daEnLaunchStar_c::onDraw() {
	bodyModel.scheduleForDrawing();
	return true;
}


void daEnLaunchStar_c::updateModelMatrices() {
	matrix.translation(pos.x, pos.y, pos.z);
	matrix.applyRotationYXZ(&rot.x, &rot.y, &rot.z);

	bodyModel.setDrawMatrix(matrix);
	bodyModel.setScale(&scale);
	bodyModel.calcWorld(false);
}

int daEnLaunchStar_c::onExecute() {
	if (this->active == true) {
		this->scale = (Vec){ 0.2, 0.2, 0.2 };
		bodyModel._vf1C();
		updateModelMatrices();

		if (this->chrAnimation.isAnimationDone()) {
			this->chrAnimation.setCurrentFrame(0.0);
		}

		return true;
	} else {
		this->scale = (Vec){ 0, 0, 0 };
		/*if (collected >= 5) {
			active = true;
		}*/
		return true;
	}
}