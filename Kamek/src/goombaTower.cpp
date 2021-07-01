#include <common.h>
#include <game.h>
#include <profile.h>

const char* GoombaTowerFileList[] = { 0 };


class daEnGoombaTower_c : public dEn_c {
public:
	int onCreate();
	int onExecute();
	int onDelete();
	int onDraw();

	static dActor_c* build();

	dStageActor_c* goombas[8];
	bool starting;

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

const SpriteData GoombaTowerSpriteData = { ProfileId::GoombaTower, 8, -8 , 0 , 0, 0x100, 0x100, 0, 0, 0, 0, 0 };
Profile GoombaTowerProfile(&daEnGoombaTower_c::build, SpriteId::GoombaTower, GoombaTowerSpriteData, ProfileId::GoombaTower, ProfileId::GoombaTower, "GoombaTower", GoombaTowerFileList);



u8 hijackMusicWithSongName(const char* songName, int themeID, bool hasFast, int channelCount, int trackCount, int* wantRealStreamID);

void daEnGoombaTower_c::playerCollision(ActivePhysics* apThis, ActivePhysics* apOther) {
}
void daEnGoombaTower_c::yoshiCollision(ActivePhysics* apThis, ActivePhysics* apOther) {
}
bool daEnGoombaTower_c::collisionCat7_GroundPound(ActivePhysics* apThis, ActivePhysics* apOther) {
	return false;
}
bool daEnGoombaTower_c::collisionCat7_GroundPoundYoshi(ActivePhysics* apThis, ActivePhysics* apOther) {
	return false;
}
bool daEnGoombaTower_c::collisionCatD_Drill(ActivePhysics* apThis, ActivePhysics* apOther) {
	return false;
}
bool daEnGoombaTower_c::collisionCatA_PenguinMario(ActivePhysics* apThis, ActivePhysics* apOther) {
	return false;
}

bool daEnGoombaTower_c::collisionCat1_Fireball_E_Explosion(ActivePhysics* apThis, ActivePhysics* apOther) {
	return false;
}
bool daEnGoombaTower_c::collisionCat2_IceBall_15_YoshiIce(ActivePhysics* apThis, ActivePhysics* apOther) {

	return false;
}
bool daEnGoombaTower_c::collisionCat9_RollingObject(ActivePhysics* apThis, ActivePhysics* apOther) {

	return false;
}
bool daEnGoombaTower_c::collisionCat13_Hammer(ActivePhysics* apThis, ActivePhysics* apOther) {
	return false;
}
bool daEnGoombaTower_c::collisionCat14_YoshiFire(ActivePhysics* apThis, ActivePhysics* apOther) {
	return false;
}

bool daEnGoombaTower_c::collisionCat3_StarPower(ActivePhysics* apThis, ActivePhysics* apOther) {
	return false;
}


dActor_c* daEnGoombaTower_c::build() {
	void* buffer = AllocFromGameHeap1(sizeof(daEnGoombaTower_c));
	daEnGoombaTower_c* c = new(buffer) daEnGoombaTower_c;

	return c;
}


extern int getNybbleValue(u32 settings, int fromNybble, int toNybble);

int daEnGoombaTower_c::onCreate() {
	this->deleteForever = true;

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

	this->starting = true;

	// Stuff I do understand
	this->scale = (Vec){ 0.2, 0.2, 0.2 };

	this->rot.x = 0;
	this->rot.y = 0;
	this->rot.z = 0;


	this->onExecute();
	return true;
}


int daEnGoombaTower_c::onDelete() {
	return true;
}

int daEnGoombaTower_c::onDraw() {
	return true;
}

int daEnGoombaTower_c::onExecute() {

	//OSReport("Goomba 0 x,y,z: %f, %f, %f\n", this->goombas[0]->pos.x, this->goombas[0]->pos.y, this->goombas[0]->pos.z);

	OSReport("Goomba alive: %d, %d, %d, %d, %d, %d, %d, %d\n", goombas[0], goombas[1], goombas[2], goombas[3], goombas[4], goombas[5], goombas[6], goombas[7]);
	//OSReport("Goomba state: %d, %d, %d, %d, %d, %d, %d, %d\n", goombas[0]->acState.getCurrentState()->getName(), goombas[1]->acState.getCurrentState()->getName(), goombas[2]->acState.getCurrentState()->getName(), goombas[3]->acState.getCurrentState()->getName(), goombas[4]->acState.getCurrentState()->getName(), goombas[5]->acState.getCurrentState()->getName(), goombas[6]->acState.getCurrentState()->getName(), goombas[7]->acState.getCurrentState()->getName());
	OSReport("Goomba rot: %f, %f, %f\n", goombas[3]->rot.x, goombas[3]->rot.y, goombas[3]->rot.z);

	dStageActor_c* player = (dStageActor_c*)FindActorByType(PLAYER, 0);

	OSReport("111111111111111\n");

	if (this->starting && player->pos.x >= this->pos.x - 16 && player->pos.x <= this->pos.x + 16)
	{
		OSReport("222222222222222222222222222222222\n");
		Vec3 goombaPos;
		OSReport("2.55555555555555555555555\n");
		for (int i = 0; i < 8; i++)
		{
			OSReport("333333333333333333333333333333333\n");
			if (this->goombas[i] == 0)
			{
				OSReport("4444444444444444444444\n");
				for (int j = i + 1; j < 8; j++)
				{
					OSReport("5555555555555555555555555555555555\n");
					this->goombas[j - 1] = this->goombas[j];
				}
			}
			OSReport("2266666666666666666666666666666662\n");
			goombaPos.x = this->pos.x;
			OSReport("2222777777777777777777777777777777\n");
			goombaPos.y = this->pos.y + (16 * i);
			OSReport("28888888888888888888888888888888888888\n");
			goombaPos.z = this->pos.z;
			OSReport("2229999999999999999999999999999999992\n");
			this->goombas[i] = (dStageActor_c*)CreateActor(51, 0, goombaPos, 0, 0);
			OSReport("222221010110101010101010101010\n");
		}
		starting = false;
	}

	/*for (int i = 1; i < 8; i++)
	{
		this->goombas[i]->pos.x = this->goombas[0]->pos.x;
		this->goombas[i]->pos.y = this->goombas[0]->pos.y + (16 * i);
		this->goombas[i]->pos.z = this->goombas[0]->pos.z - (16 * i);

		this->goombas[i]->speed.x = this->goombas[0]->speed.x;
		this->goombas[i]->speed.y = this->goombas[0]->speed.y;
		this->goombas[i]->speed.z = this->goombas[0]->speed.z;
	}*/

	return true;
}