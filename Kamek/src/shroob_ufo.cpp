#include <common.h>
#include <game.h>
#include <g3dhax.h>
#include <sfx.h>

class daShroobUfo : public dEn_c {
	// Let's give ourselves a few functions
	int onCreate();
	int onDelete();
	int onExecute();
	int onDraw();

	static daShroobUfo* build();

	// And a model and an anmChr
	mHeapAllocator_c allocator;
	m3d::mdl_c bodyModel;
	nw4r::g3d::ResFile resFile;
	//m3d::anmChr_c chrAnimation;

	nw4r::g3d::ResMdl mdl;

	// Some variables to use
	int model;
	//bool isAnimating;
	float size;
	float zOrder;
	bool customZ;

	//void setupAnim(const char* name, float rate);
	void setupModel(const char* arcName, const char* brresName, const char* mdlName);
};

daShroobUfo *daShroobUfo::build() {
	void *buffer = AllocFromGameHeap1(sizeof(daShroobUfo));
	return new(buffer) daShroobUfo;
}

/*void daShroobUfo::setupAnim(const char* name, float rate) {
	if (isAnimating) {
		nw4r::g3d::ResAnmChr anmChr;

		anmChr = this->resFile.GetResAnmChr(name);
		this->chrAnimation.setup(this->mdl, anmChr, &this->allocator, 0);
		this->chrAnimation.bind(&this->bodyModel, anmChr, 1);
		this->bodyModel.bindAnim(&this->chrAnimation, 0.0);
		this->chrAnimation.setUpdateRate(rate);
	}
}*/

void daShroobUfo::setupModel(const char* arcName, const char* brresName, const char* mdlName) {
	this->resFile.data = getResource(arcName, brresName);
	this->mdl = this->resFile.GetResMdl(mdlName);

	bodyModel.setup(mdl, &allocator, 0x224, 1, 0);
}

int daShroobUfo::onCreate() {

		// Settings for your sprite!

		this->model = this->settings & 0xFF; 						// Sets nubble 12 to choose the model you want
		//this->isAnimating = this->settings & 0x100;					// Sets nybble 11 to a checkbox for whether or not the model has an anmChr to use
		this->size = (float)((this->settings >> 24) & 0xFF) / 4.0; 	// Sets nybbles 5-6 to size. Size equals value / 4.


		float zLevels[16] = { -6500.0, -5000.0, -4500.0, -2000.0,
							 -1000.0, 300.0, 800.0, 1600.0,
							  2000.0, 3600.0, 4000.0, 4500.0,
							  6000.0, 6500.0, 7000.0, 7500.0 };

		this->zOrder = zLevels[(this->settings >> 16) & 0xF];

		this->customZ = (((this->settings >> 16) & 0xF) != 0);

		allocator.link(-1, GameHeaps[0], 0, 0x20);
		switch (this->model) {
		case 0:

			setupModel("shroob_ufo", "g3d/Misc Data [0].brres", "UFO");
			SetupTextures_Item(&bodyModel, 0);
			this->pos.z = -3300.0;

			//setupAnim("anim00", 1.0);

			break;
		}

		allocator.unlink();

		if (size == 0.0) {	// If the person has the size nybble at zero, make it normal sized
			this->scale = (Vec){ 1.0,1.0,1.0 };
		}
		else {				// Else, use our size
			this->scale = (Vec){ size,size,size };
		}

		this->onExecute();
		return true;
}

int daShroobUfo::onDelete() {
	return true;
}

int daShroobUfo::onExecute() {
	/*if (isAnimating) {
		bodyModel._vf1C();	// Advances the animation one update

		if (this->chrAnimation.isAnimationDone()) {
			this->chrAnimation.setCurrentFrame(0.0);	// Resets the animation when it's done
		}
	}*/

	return true;
}

int daShroobUfo::onDraw() {
	if (customZ) {
		matrix.translation(pos.x, pos.y, this->zOrder);
	}	// Set where to draw the model : -5500.0 is the official behind layer 2, while 5500.0 is in front of layer 0.
	else {
		matrix.translation(pos.x, pos.y, pos.z - 6500.0);
	}	// Set where to draw the model : -5500.0 is the official behind layer 2, while 5500.0 is in front of layer 0.

	matrix.applyRotationYXZ(&rot.x, &rot.y, &rot.z);	// Set how to rotate the drawn model 

	bodyModel.setDrawMatrix(matrix);	// Apply matrix
	bodyModel.setScale(&scale);			// Apply scale
	bodyModel.calcWorld(true);			// Do some shit

	bodyModel.scheduleForDrawing();		// Add it to the draw list for the game
	return true;
}