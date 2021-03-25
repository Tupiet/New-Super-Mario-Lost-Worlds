#include <common.h>
#include <game.h>
#include <actors.h>
#include "sfx.h"

class daBlockSource_c : public daEnBlockMain_c {
public:
	TileRenderer tileMiddle;
	Physics::Info physicsInfo;

	int onCreate();
	int onDelete();
	int onExecute();

	void calledWhenUpMoveExecutes();
	void calledWhenDownMoveExecutes();

	void blockWasHit(bool isDown);
	
	virtual bool isOutOfView();
	virtual void willBeDeleted();
	

	USING_STATES(daBlockSource_c);
	DECLARE_STATE(Wait);

	static daBlockSource_c *build();
};


CREATE_STATE(daBlockSource_c, Wait);


int daBlockSource_c::onCreate() {
	blockInit(pos.y);

	physicsInfo.x1 = -8;
	physicsInfo.y1 = 16;
	physicsInfo.x2 = 8;
	physicsInfo.y2 = 0;

	physicsInfo.otherCallback1 = &daEnBlockMain_c::OPhysicsCallback1;
	physicsInfo.otherCallback2 = &daEnBlockMain_c::OPhysicsCallback2;
	physicsInfo.otherCallback3 = &daEnBlockMain_c::OPhysicsCallback3;

	physics.setup(this, &physicsInfo, 3, currentLayerID);
	physics.flagsMaybe = 0x260;
	physics.callback1 = &daEnBlockMain_c::PhysicsCallback1;
	physics.callback2 = &daEnBlockMain_c::PhysicsCallback2;
	physics.callback3 = &daEnBlockMain_c::PhysicsCallback3;
	physics.addToList();
	
	TileRenderer::List *list = dBgGm_c::instance->getTileRendererList(0);

	//Middle
	u32 reggieToTile[] = {0x99,0x0,0x0,0x0,0x9A,0xA6,0xA7,0x9B,0xA8,0xA9,0x0}; //Mushroom, Star, Coin, 1UP, Fire Flower, Ice Flower, Penguin, Propeller, Mini Shroom, Hammer, 10 Coins
	list->add(&tileMiddle);

	tileMiddle.x = pos.x - 8;
	tileMiddle.y = -(16 + pos.y);
	tileMiddle.tileNumber = reggieToTile[(this->settings >> 20 & 0xF)];

	this->pos.z = 200.0f;
	
	this->spriteSomeRectX = 6000.0f;
	
	doStateChange(&daBlockSource_c::StateID_Wait);

	return true;
}


int daBlockSource_c::onDelete() {
	TileRenderer::List *list = dBgGm_c::instance->getTileRendererList(0);
	list->remove(&tileMiddle);

	physics.removeFromList();

	return true;
}


int daBlockSource_c::onExecute() {
	acState.execute();
	physics.update();
	blockUpdate();
	
	tileMiddle.setPosition(pos.x-8, -(16+pos.y), pos.z);
	tileMiddle.setVars(scale.x);

	// now check zone bounds based on state
	if (acState.getCurrentState()->isEqual(&StateID_Wait)) {
		checkZoneBoundaries(0);
	}

	return true;
}


daBlockSource_c *daBlockSource_c::build() {
	void *buffer = AllocFromGameHeap1(sizeof(daBlockSource_c));
	return new(buffer) daBlockSource_c;
}

extern "C" int CheckExistingPowerup(void * Player);

void daBlockSource_c::blockWasHit(bool isDown) {
	pos.y = initialY;
	
	int p = CheckExistingPowerup(dAcPy_c::findByID(this->playerID)); // Powerups - 0 = small; 1 = big; 2 = fire; 3 = mini; 4 = prop; 5 = peng; 6 = ice; 7 = hammer
	
	Vec coinPosL = (Vec){this->pos.x - 16, this->pos.y + 8, this->pos.z}; //Setting non-GP coinLeft position
	Vec coinPosR = (Vec){this->pos.x + 16, this->pos.y + 8, this->pos.z}; //Setting non-GP coinRight position
	
	nw4r::snd::SoundHandle handle; //Sound Handle
	
	u32 enitemsettings; //EN_ITEM settings
	u32 reggieToIG[] = {0x17,0x1,0x2,0x7,0x9,0xE,0x11,0x15,0x19,0x6,0x2}; //Mushroom, Star, Coin, 1UP, Fire Flower, Ice Flower, Penguin, Propeller, Mini Shroom, Hammer, 10 Coins
	u32 powerupToSet = reggieToIG[(this->settings >> 20 & 0xF)]; //Spritedata ID to EN_ITEM ID
	enitemsettings = 0 | (powerupToSet << 0) | (2 << 18) | (4 << 9) | (2 << 10) | (this->playerID + 8 << 16); //Setting non-GP settings
	
	
	if(isGroundPound) { //If the player groundpounded the block, change some setting and positions
		enitemsettings = 0 | (powerupToSet << 0) | (3 << 18) | (4 << 9) | (2 << 10) | (this->playerID + 8 << 16); //Changing value 0xD98 from 2 to 3
	}

	if((powerupToSet != 0x2 && powerupToSet != 0x15) || p == 0 || p == 3) { //Propeller does a different sound and Coin doesn't do any sound
		PlaySoundWithFunctionB4(SoundRelatedClass, &handle, SE_OBJ_ITEM_APPEAR, 1); //Item sound
	}

	if(powerupToSet == 0x15 && p != 0) { //If powerup = propeller
		PlaySoundWithFunctionB4(SoundRelatedClass, &handle, SE_OBJ_ITEM_PRPL_APPEAR, 1); //Propeller sound
	}

	dStageActor_c *PowerUp = dStageActor_c::create(EN_ITEM, enitemsettings, &this->pos, 0, 0); //Creating PowerUp

	if(powerupToSet != 0x15 || p == 0 || p == 3) { //If powerup =/= propeller OR actual powerup = 0
		PowerUp->pos.z = 100.0f; //make the powerup behind the triple block
	}

	physics.setup(this, &physicsInfo, 3, currentLayerID);
	physics.addToList();

	doStateChange(&StateID_Wait); //Back to waiting state
}



void daBlockSource_c::calledWhenUpMoveExecutes() {
	if (initialY >= pos.y)
		blockWasHit(false);
}

void daBlockSource_c::calledWhenDownMoveExecutes() {
	if (initialY <= pos.y)
		blockWasHit(true);
}



void daBlockSource_c::beginState_Wait() {
}

void daBlockSource_c::endState_Wait() {
}

void daBlockSource_c::executeState_Wait() {
	int result = blockResult();

	if (result == 0)
		return;

	if (result == 1) {
		doStateChange(&daEnBlockMain_c::StateID_UpMove);
		anotherFlag = 2;
		isGroundPound = false;
	} else {
		doStateChange(&daEnBlockMain_c::StateID_DownMove);
		anotherFlag = 1;
		isGroundPound = true;
	}
}

bool daBlockSource_c::isOutOfView() {
}

void daBlockSource_c::willBeDeleted() {
	return;
}