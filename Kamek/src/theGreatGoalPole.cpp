#include <common.h>
#include <game.h>
#include <profile.h>

extern "C" dCourse_c::rail_s *GetRail(int id);

const char* GreatGoalPoleFileList[] = { "goal_set", "wing", 0 };

class daGreatGoalPole_c : public daEnBlockMain_c {
public:
	int onCreate();
	int onExecute();
	int afterExecute(int param);
	int onDelete();
	int onDraw();

	mHeapAllocator_c allocator;
	nw4r::g3d::ResFile goalBrres;
	m3d::mdl_c baseA;
	m3d::mdl_c goal_flag;
	nw4r::g3d::ResFile wingBrres;
	m3d::mdl_c wing;
	m3d::anmChr_c anmFlag;
	m3d::anmTexSrt_c flagSrt;
	m3d::anmChr_c anmWing;

	S16Vec baseArot;
	S16Vec wingRot;
	Vec wingScale;

	ActivePhysics a1UPPhysics;
	Physics::Info physicsInfo;
	StandOnTopCollider  sotCollider;
	
	bool done;

	dCourse_c *course;
	dCourse_c::rail_s *rail;
	dCourse_c::railNode_s *currentNode;
	dCourse_c::railNode_s *nextNode;
	int currentNodeNum;
	float moveDeltaX, moveDeltaY;
	int steps;
	int speed;
	


	static dActor_c *build();

	void updateModelMatrices();
	void playerCollision(ActivePhysics *apThis, ActivePhysics *apOther);
	void yoshiCollision(ActivePhysics *apThis, ActivePhysics *apOther);

	bool collisionCat7_GroundPound(ActivePhysics *apThis, ActivePhysics *apOther);
	bool collisionCat7_GroundPoundYoshi(ActivePhysics *apThis, ActivePhysics *apOther);
	bool collisionCatD_Drill(ActivePhysics *apThis, ActivePhysics *apOther);
	bool collisionCatA_PenguinMario(ActivePhysics *apThis, ActivePhysics *apOther);

	bool collisionCat1_Fireball_E_Explosion(ActivePhysics *apThis, ActivePhysics *apOther);
	bool collisionCat2_IceBall_15_YoshiIce(ActivePhysics *apThis, ActivePhysics *apOther);
	bool collisionCat9_RollingObject(ActivePhysics *apThis, ActivePhysics *apOther);
	bool collisionCat13_Hammer(ActivePhysics *apThis, ActivePhysics *apOther);
	bool collisionCat14_YoshiFire(ActivePhysics *apThis, ActivePhysics *apOther);
	bool collisionCat3_StarPower(ActivePhysics *apThis, ActivePhysics *apOther);
	
	void bindAnimChr_and_setUpdateRate(const char* name, int unk, float unk2, float rate);
	
	USING_STATES(daGreatGoalPole_c);
	
	DECLARE_STATE(Wait);
	DECLARE_STATE(Fly);
	DECLARE_STATE(Run);
};

CREATE_STATE(daGreatGoalPole_c, Wait);
CREATE_STATE(daGreatGoalPole_c, Fly);
CREATE_STATE(daGreatGoalPole_c, Run);


void daGreatGoalPole_c::beginState_Wait() {}
void daGreatGoalPole_c::executeState_Wait() {
	
	if (this->anmFlag.isAnimationDone()) {
		this->anmFlag.setCurrentFrame(0.0);
	}
	if (!done) {
		dStageActor_c* player = (dStageActor_c*)FindActorByType(PLAYER, 0);

		OSReport("HI 1\n");

		if (player->pos.x >= this->pos.x - 64) {
			OSReport("HI 2\n");
			doStateChange(&StateID_Run);
		}
	}
	//doStateChange(&StateID_Fly);
}
void daGreatGoalPole_c::endState_Wait() {}







void daGreatGoalPole_c::beginState_Run() 
{
	OSReport("HI 2.7\n"); 

	/*switch ((int)currentNode->speed)
	{
	case 0:
		bindAnimChr_and_setUpdateRate("YB_Rwait", 1, 0.0, 1.5);
		break;
	case 1:
		bindAnimChr_and_setUpdateRate("YB_Rrun", 1, 0.0, 1.5);
		break;
	case 2:
		bindAnimChr_and_setUpdateRate("YB_Rb_dash", 1, 0.0, 1.5);
		break;
	case 3:
		bindAnimChr_and_setUpdateRate("YB_Rb_dash2", 1, 0.0, 1.5);
		break;
	}*/
}
void daGreatGoalPole_c::executeState_Run() {
	OSReport("HI 3\n");

	if (this->anmFlag.isAnimationDone()) {
		this->anmFlag.setCurrentFrame(0.0);
	}
	if (this->anmWing.isAnimationDone()) {
		this->anmWing.setCurrentFrame(0.0);
	}
	if (!done) {
		float dx = nextNode->xPos - currentNode->xPos;
		float dy = (-nextNode->yPos) - (-currentNode->yPos);

		float ux = (dx / sqrtf((dx * dx) + (dy * dy)));
		float uy = (dy / sqrtf((dx * dx) + (dy * dy)));

		this->pos.y += uy * speed;
		this->pos.x += ux * speed;

		if (dx <= 0) {
			//this->rot.y = 0x4000;
			//this->rot.y *= -1;
		} else {
			//this->rot.y = 0x4000;
		}

		OSReport("x: %f; y: %f\n", this->pos.x, this->pos.y);
		OSReport("nx: %f; ny: %f\n", currentNode->xPos, -currentNode->yPos);
		OSReport("dx: %f; dy: %f\n", dx, dy);
		OSReport("ux: %f; uy: %f\n", ux, uy);

		if (this->pos.x > dx + currentNode->xPos - 2 && this->pos.x < dx + currentNode->xPos + 2 && this->pos.y > dy - currentNode->yPos - 2 && this->pos.y < dy - currentNode->yPos + 2) {
			done = true;
		}
	} else {
		currentNodeNum++;
		currentNode = nextNode;
		nextNode = &course->railNode[rail->startNode + 1 + currentNodeNum];
		this->pos.x = currentNode->xPos;
		this->pos.y = -currentNode->yPos;

		if (rail->nodeCount == currentNodeNum + 1) {
			doStateChange(&StateID_Wait);
			//this->rot.y = 0x4000;
			//this->rot.y *= -1;
		} else {
			done = false;
		}

		/*switch ((int)currentNode->speed)
		{
		case 0:
			bindAnimChr_and_setUpdateRate("YB_Rwait", 1, 0.0, 1.5);
			break;
		case 1:
			bindAnimChr_and_setUpdateRate("YB_Rrun", 1, 0.0, 1.5);
			break;
		case 2:
			bindAnimChr_and_setUpdateRate("YB_Rb_dash", 1, 0.0, 1.5);
			break;
		case 3:
			bindAnimChr_and_setUpdateRate("YB_Rb_dash2", 1, 0.0, 1.5);
			break;
		}*/
	}
}
void daGreatGoalPole_c::endState_Run() { OSReport("HI 5.3\n"); }








void daGreatGoalPole_c::beginState_Fly() {}
void daGreatGoalPole_c::executeState_Fly() {
	
}
void daGreatGoalPole_c::endState_Fly() {}

void daGreatGoalPole_c::bindAnimChr_and_setUpdateRate(const char* name, int unk, float unk2, float rate) {
	nw4r::g3d::ResAnmChr anmChr = this->goalBrres.GetResAnmChr(name);
	this->anmFlag.bind(&this->goal_flag, anmChr, unk);
	this->goal_flag.bindAnim(&this->anmFlag, unk2);
	this->anmFlag.setUpdateRate(rate);
}


const SpriteData GreatGoalPoleSpriteData = { ProfileId::GreatGoalPole, 8, -8 , 0 , 0, 0x100, 0x100, 0, 0, 0, 0, 0 };
Profile GreatGoalPoleProfile(&daGreatGoalPole_c::build, SpriteId::GreatGoalPole, GreatGoalPoleSpriteData, ProfileId::GreatGoalPole, ProfileId::GreatGoalPole, "TheGreatGoalPole", GreatGoalPoleFileList);


void daGreatGoalPole_c::playerCollision(ActivePhysics* apThis, ActivePhysics* apOther) {
}
void daGreatGoalPole_c::yoshiCollision(ActivePhysics* apThis, ActivePhysics* apOther) {

}
bool daGreatGoalPole_c::collisionCat7_GroundPound(ActivePhysics* apThis, ActivePhysics* apOther) {
	return false;
}
bool daGreatGoalPole_c::collisionCat7_GroundPoundYoshi(ActivePhysics* apThis, ActivePhysics* apOther) {
	return false;
}
bool daGreatGoalPole_c::collisionCatD_Drill(ActivePhysics* apThis, ActivePhysics* apOther) {
	return false;
}
bool daGreatGoalPole_c::collisionCatA_PenguinMario(ActivePhysics* apThis, ActivePhysics* apOther) {
	return false;
}

bool daGreatGoalPole_c::collisionCat1_Fireball_E_Explosion(ActivePhysics* apThis, ActivePhysics* apOther) {
	return false;
}
bool daGreatGoalPole_c::collisionCat2_IceBall_15_YoshiIce(ActivePhysics* apThis, ActivePhysics* apOther) {
	return false;
}
bool daGreatGoalPole_c::collisionCat9_RollingObject(ActivePhysics* apThis, ActivePhysics* apOther) {

	return false;
}
bool daGreatGoalPole_c::collisionCat13_Hammer(ActivePhysics* apThis, ActivePhysics* apOther) {
	return false;
}
bool daGreatGoalPole_c::collisionCat14_YoshiFire(ActivePhysics* apThis, ActivePhysics* apOther) {
	return false;
}

bool daGreatGoalPole_c::collisionCat3_StarPower(ActivePhysics* apThis, ActivePhysics* apOther) {
	return false;
}


dActor_c* daGreatGoalPole_c::build() {
	void* buffer = AllocFromGameHeap1(sizeof(daGreatGoalPole_c));
	daGreatGoalPole_c* c = new(buffer) daGreatGoalPole_c;

	return c;
}


int daGreatGoalPole_c::onCreate() {
	this->deleteForever = true;

	// Model creation	
	allocator.link(-1, GameHeaps[0], 0, 0x20);

	this->goalBrres.data = getResource("goal_set", "g3d/t00.brres");
	nw4r::g3d::ResMdl baseAMdl = this->goalBrres.GetResMdl("baseA");
	nw4r::g3d::ResMdl goal_flagMdl = this->goalBrres.GetResMdl("goal_flag");
	

	
	this->wingBrres.data = getResource("wing", "g3d/wing.brres");
	nw4r::g3d::ResMdl wingMdl = this->wingBrres.GetResMdl("wing");
	

	
	this->baseA.setup(baseAMdl, &allocator, 0x224, 1, 0);
	this->goal_flag.setup(goal_flagMdl, &allocator, 0x224, 1, 0);
	this->wing.setup(wingMdl, &allocator, 0x224, 1, 0);
	
	SetupTextures_MapObj(&this->baseA, 0);
	SetupTextures_MapObj(&this->goal_flag, 0);
	SetupTextures_Enemy(&this->wing, 0);


	
	nw4r::g3d::ResAnmChr anmChr = this->goalBrres.GetResAnmChr("wait");
	this->anmFlag.setup(goal_flagMdl, anmChr, &this->allocator, 0);
	
	
	nw4r::g3d::ResAnmTexSrt anmSrt = this->goalBrres.GetResAnmTexSrt("wait");
	this->flagSrt.setup(goal_flagMdl, anmSrt, &this->allocator, 0, 1);
	this->flagSrt.setEntryByte34(0, 0);


	nw4r::g3d::ResAnmChr anmChr2 = this->wingBrres.GetResAnmChr("wing_kuri");
	this->anmWing.setup(wingMdl, anmChr2, &this->allocator, 0);
	
	
	
	//bindAnimChr_and_setUpdateRate("wait", 1, 0.0, 1.0);
	this->anmFlag.bind(&this->goal_flag, anmChr, 1);
	this->goal_flag.bindAnim(&this->anmFlag, 0.0);
	this->anmFlag.setUpdateRate(1.0);

	this->flagSrt.bindEntry(&this->goal_flag, anmSrt, 0, 1);
	this->goal_flag.bindAnim(&this->flagSrt, 1.0);
	this->flagSrt.setFrameForEntry(1.0, 0);
	this->flagSrt.setUpdateRateForEntry(1.0, 0);

	this->anmWing.bind(&this->wing, anmChr2, 1);
	this->wing.bindAnim(&this->anmWing, 0.0);
	this->anmWing.setUpdateRate(1.0);
	

	allocator.unlink();

	//goal_flag
	ActivePhysics::Info aPhysicsInfo;
	aPhysicsInfo.xDistToCenter = 0.0;
	aPhysicsInfo.yDistToCenter = 72.0;
	aPhysicsInfo.category1 = 0x0;
	aPhysicsInfo.category2 = 0x0;
	aPhysicsInfo.bitfield1 = 0x0;

	aPhysicsInfo.bitfield2 = 0x0;
	aPhysicsInfo.xDistToEdge = 3;
	aPhysicsInfo.yDistToEdge = 76;

	aPhysicsInfo.unkShort1C = 0;
	aPhysicsInfo.callback = &dEn_c::collisionCallback;

	this->aPhysics.initWithStruct(this, &aPhysicsInfo);
	this->aPhysics.addToList();

	//goal_flag 1UP
	ActivePhysics::Info a1UPPhysicsInfo;
	a1UPPhysicsInfo.xDistToCenter = 0.0;
	a1UPPhysicsInfo.yDistToCenter = 151.0;
	a1UPPhysicsInfo.category1 = 0x0;
	a1UPPhysicsInfo.category2 = 0x0;
	a1UPPhysicsInfo.bitfield1 = 0x0;

	a1UPPhysicsInfo.bitfield2 = 0x0;
	a1UPPhysicsInfo.xDistToEdge = 3;
	a1UPPhysicsInfo.yDistToEdge = 3;

	a1UPPhysicsInfo.unkShort1C = 0;
	a1UPPhysicsInfo.callback = &dEn_c::collisionCallback;

	this->a1UPPhysics.initWithStruct(this, &a1UPPhysicsInfo);
	this->a1UPPhysics.addToList();



	//baseA
	physicsInfo.x1 = -16;
	physicsInfo.y1 = 15.5;
	physicsInfo.x2 = 16;
	physicsInfo.y2 = 0;

	physicsInfo.otherCallback1 = &daEnBlockMain_c::OPhysicsCallback1;
	physicsInfo.otherCallback2 = &daEnBlockMain_c::OPhysicsCallback2;
	physicsInfo.otherCallback3 = &daEnBlockMain_c::OPhysicsCallback3;

	physics.setup(this, &physicsInfo, 1, 0, 0);
	physics.flagsMaybe = 0x260;
	physics.callback1 = &daEnBlockMain_c::PhysicsCallback1;
	physics.callback2 = &daEnBlockMain_c::PhysicsCallback2;
	physics.callback3 = &daEnBlockMain_c::PhysicsCallback3;
	physics.addToList();
	
	
	sotCollider.init(this, 0, 16, 0, 16, -16, 0, 1);
	sotCollider._47 = 0xA;
	sotCollider.flags = 0x80180 | 0xC00;
	sotCollider.addToList();
	
	
	done = false;

	speed = this->settings >> 12 & 0b1111;						    		//Bit 29-32
	speed += 1;
	speed *= 2;
	//speed = 8;
	currentNodeNum = this->settings >> 8 & 0b11111111;						//Bit 33-40
	int pathID = this->settings & 0b11111111;                               //Bit 41-48
	OSReport("speed: %d, currentNodeNum: %d, pathID: %d\n", speed, currentNodeNum, pathID);
	if (pathID) {
		rail = GetRail(pathID);
		course = dCourseFull_c::instance->get(GetAreaNum());
		currentNode = &course->railNode[rail->startNode + currentNodeNum];
		nextNode = &course->railNode[rail->startNode + 1 + currentNodeNum];
		OSReport("pathID: %d\n", pathID);
		OSReport("startNode: %d\n", currentNodeNum);
		OSReport("N1.x: %d, N1.y: %d, N2.x: %d, N2.y: %d\n", currentNode->xPos, currentNode->yPos, nextNode->xPos, nextNode->yPos);
		//OSReport("Ballon: %f, %f\n", this->pos.x, this->pos.y);
		this->pos.x = currentNode->xPos;
		this->pos.y = -currentNode->yPos;
		//OSReport("Ballon: %f, %f\n", this->pos.x, this->pos.y);
		OSReport("HI 0.1\n");
	}
	else {
		OSReport("HI 0.2\n");
	}
	
	
	
	
	
	
	this->disableEatIn();


	/*for (int i = 0; i < 4; i++)
		if (dAcPy_c *player = dAcPy_c::findByID(i))
			player->dealsWithGoalPutonCapAnimation();
	*/

	baseArot = (S16Vec){0, 0, 0};
	wingRot = (S16Vec){0, 0x4000, 0};
	
	
	this->scale = (Vec){1, 1, 1};
	this->wingScale = (Vec){2, 2, 2};

	this->rot.x = 0;
	this->rot.y = 0xC000; //0x8000;
	this->rot.z = 0;

	this->pos.z = 4000;

	doStateChange(&StateID_Wait);
	
	//this->onExecute();
	return true;
}


int daGreatGoalPole_c::onDelete() {
	physics.removeFromList();
	return true;
}

int daGreatGoalPole_c::onDraw() {
	baseA.scheduleForDrawing();
	goal_flag.scheduleForDrawing();
	wing.scheduleForDrawing();
	return true;
}


void daGreatGoalPole_c::updateModelMatrices() {
	matrix.translation(pos.x, pos.y, pos.z);
	matrix.applyRotationYXZ(&baseArot.x, &baseArot.y, &baseArot.z);
	baseA.setDrawMatrix(matrix);
	baseA.setScale(&scale);
	baseA.calcWorld(false);

	matrix.translation(pos.x, pos.y, pos.z + 5);
	matrix.applyRotationYXZ(&wingRot.x, &wingRot.y, &wingRot.z);
	wing.setDrawMatrix(matrix);
	wing.setScale(&wingScale);
	wing.calcWorld(false);

	matrix.translation(pos.x, pos.y+85, pos.z);
	matrix.applyRotationYXZ(&rot.x, &rot.y, &rot.z);
	goal_flag.setDrawMatrix(matrix);
	goal_flag.setScale(&scale);
	goal_flag.calcWorld(false);
}

int daGreatGoalPole_c::onExecute() {
	baseA._vf1C();
	goal_flag._vf1C();
	wing._vf1C();
	updateModelMatrices();
	acState.execute();
	/*physics1.removeFromList();
	physics1.setupRound(this, 0.0f, 200.0f - this->aTestFloat, 80.0f, (void*)&BallonPhysCB1, (void*)&BallonPhysCB2, (void*)&BallonPhysCB3, 1, 0, 0);
	physics1.addToList();
	OSReport("Ballon aTestFloat: %f\n", this->aTestFloat);
	this->aTestFloat += 0.25;*/
	//this->pos.x += aTestFloat;
	
	//this->rot.y -= -0x100;
	//OSReport("Rot.y: %x\n", this->rot.y);
	
	this->flagSrt.process();
	if(this->flagSrt.isEntryAnimationDone(0))
		this->flagSrt.setFrameForEntry(1.0, 0);
	
	sotCollider.update();
	physics.update();
	return true;
}

int daGreatGoalPole_c::afterExecute(int param) {
	dEn_c::afterExecute(param);
	a1UPPhysics.clear();
	return true;
}