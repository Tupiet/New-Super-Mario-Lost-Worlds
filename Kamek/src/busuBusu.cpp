#include <common.h>
#include <game.h>
#include <profile.h>

const char* BusuBusuFileList[] = { "busuBusu", 0 };


class daEnBusuBusu_c : public dEn_c {
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

	bool facingRight;
	u8 wSpeed;
	u8 wDistance;

	int stepCount;

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
};

const SpriteData BusuBusuSpriteData = { ProfileId::BusuBusu, 8, -8 , 0 , 0, 0x100, 0x100, 0, 0, 0, 0, 0 };
Profile BusuBusuProfile(&daEnBusuBusu_c::build, SpriteId::BusuBusu, BusuBusuSpriteData, ProfileId::BusuBusu, ProfileId::BusuBusu, "BusuBusu", BusuBusuFileList);



u8 hijackMusicWithSongName(const char* songName, int themeID, bool hasFast, int channelCount, int trackCount, int* wantRealStreamID);

void daEnBusuBusu_c::playerCollision(ActivePhysics* apThis, ActivePhysics* apOther) {
	DamagePlayer(this, apThis, apOther);
}
void daEnBusuBusu_c::yoshiCollision(ActivePhysics* apThis, ActivePhysics* apOther) {
}
bool daEnBusuBusu_c::collisionCat7_GroundPound(ActivePhysics* apThis, ActivePhysics* apOther) {
	return false;
}
bool daEnBusuBusu_c::collisionCat7_GroundPoundYoshi(ActivePhysics* apThis, ActivePhysics* apOther) {
	return false;
}
bool daEnBusuBusu_c::collisionCatD_Drill(ActivePhysics* apThis, ActivePhysics* apOther) {
	return false;
}
bool daEnBusuBusu_c::collisionCatA_PenguinMario(ActivePhysics* apThis, ActivePhysics* apOther) {
	return false;
}

bool daEnBusuBusu_c::collisionCat1_Fireball_E_Explosion(ActivePhysics* apThis, ActivePhysics* apOther) {
	return false;
}
bool daEnBusuBusu_c::collisionCat2_IceBall_15_YoshiIce(ActivePhysics* apThis, ActivePhysics* apOther) {

	return false;
}
bool daEnBusuBusu_c::collisionCat9_RollingObject(ActivePhysics* apThis, ActivePhysics* apOther) {

	return false;
}
bool daEnBusuBusu_c::collisionCat13_Hammer(ActivePhysics* apThis, ActivePhysics* apOther) {
	return false;
}
bool daEnBusuBusu_c::collisionCat14_YoshiFire(ActivePhysics* apThis, ActivePhysics* apOther) {
	return false;
}

bool daEnBusuBusu_c::collisionCat3_StarPower(ActivePhysics* apThis, ActivePhysics* apOther) {
	return false;
}


dActor_c* daEnBusuBusu_c::build() {
	void* buffer = AllocFromGameHeap1(sizeof(daEnBusuBusu_c));
	daEnBusuBusu_c* c = new(buffer) daEnBusuBusu_c;

	return c;
}


extern int getNybbleValue(u32 settings, int fromNybble, int toNybble);

void daEnBusuBusu_c::bindAnimChr_and_setUpdateRate(const char* name, int unk, float unk2, float rate)
{
	nw4r::g3d::ResAnmChr anmChr = this->resFileAnim.GetResAnmChr(name);
	this->chrAnimation.bind(&this->bodyModel, anmChr, unk);
	this->bodyModel.bindAnim(&this->chrAnimation, unk2);
	this->chrAnimation.setUpdateRate(rate);
}

int daEnBusuBusu_c::onCreate() {
	this->deleteForever = true;

	// Model creation	
	allocator.link(-1, GameHeaps[0], 0, 0x20);

	this->resFile.data = getResource("busuBusu", "g3d/busuBusu.brres");
	nw4r::g3d::ResMdl mdl = this->resFile.GetResMdl("BusuBusu");
	bodyModel.setup(mdl, &allocator, 0x224, 1, 0);
	SetupTextures_Player(&bodyModel, 0);

	this->resFileAnim.data = getResource("busuBusu", "g3d/busuBusuAnim.brres");
	nw4r::g3d::ResAnmChr anmChr = this->resFileAnim.GetResAnmChr("fly");
	this->chrAnimation.setup(mdl, anmChr, &this->allocator, 0);

	allocator.unlink();

	ActivePhysics::Info HitMeBaby;

	HitMeBaby.xDistToCenter = 0.0;
	HitMeBaby.yDistToCenter = 0.0;

	HitMeBaby.xDistToEdge = 7.5;
	HitMeBaby.yDistToEdge = 7.5;

	HitMeBaby.category1 = 0x3;
	HitMeBaby.category2 = 0x0;
	HitMeBaby.bitfield1 = 0x6F;
	HitMeBaby.bitfield2 = 0xffbafffe;
	HitMeBaby.unkShort1C = 0;
	HitMeBaby.callback = &dEn_c::collisionCallback;

	this->aPhysics.initWithStruct(this, &HitMeBaby);
	this->aPhysics.addToList();


	this->facingRight = settings >> 31 & 1;
	this->wDistance = settings >> 20 & 0b11111111;
	this->wSpeed = settings >> 16 & 0b1111;

	OSReport("fr: %d, wD: %d, wS: %d\n", this->facingRight, this->wDistance, this->wSpeed);


	// Stuff I do understand
	this->scale = (Vec){ 0.1, 0.1, 0.1 };

	this->rot.x = 0;
	if (facingRight)
	{
		this->rot.y = 0x4000;
	}
	else
	{
		this->rot.y = 0x4000;
		this->rot.y *= -1;
	}
	this->rot.z = 0;

	this->pos.z = 4000;


	bindAnimChr_and_setUpdateRate("fly", 1, 0.0, 1.0);


	this->onExecute();
	return true;
}


int daEnBusuBusu_c::onDelete() {
	return true;
}

int daEnBusuBusu_c::onDraw() {
	bodyModel.scheduleForDrawing();
	return true;
}


void daEnBusuBusu_c::updateModelMatrices() {
	matrix.translation(pos.x, pos.y, pos.z);
	matrix.applyRotationYXZ(&rot.x, &rot.y, &rot.z);

	bodyModel.setDrawMatrix(matrix);
	bodyModel.setScale(&scale);
	bodyModel.calcWorld(false);
}

int daEnBusuBusu_c::onExecute() {
	bodyModel._vf1C();
	updateModelMatrices();

	OSReport("fr: %d, wD: %d, wS: %d, stepCount: %d\n", this->facingRight, this->wDistance, this->wSpeed, this->stepCount);

	if (facingRight)
	{
		this->rot.y = 0x4000;

		this->pos.x += this->wSpeed;
		this->stepCount += 1;

		if ((stepCount * wSpeed) > wDistance)
		{
			this->facingRight = false;
			this->stepCount = 0;
		}
	}
	else
	{
		this->rot.y = 0x4000;
		this->rot.y *= -1;

		this->pos.x -= this->wSpeed;
		this->stepCount += 1;

		if ((stepCount * wSpeed) > wDistance)
		{
			this->facingRight = true;
			this->stepCount = 0;
		}
	}

	if (this->chrAnimation.isAnimationDone()) 
	{
		this->chrAnimation.setCurrentFrame(0.0);
	}

	return true;
}