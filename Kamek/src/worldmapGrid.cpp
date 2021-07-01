bool showGrid = false;
dActor_c* theGrid;

int wmtest() {
	dActor_c* shop = (dActor_c*)fBase_c::search(WM_GRID);
	if(!shop) {
		dActor_c::create(WM_GRID, 0, 0, 0);
	}
	if(Remocon_GetPressed(GetActiveRemocon()) & WPAD_HOME){
		showGrid = !showGrid;
		return showGrid ? 2 : 1;
	}
	return 0;
}

void createWMGrid() {
	dActor_c* player = (dActor_c*)fBase_c::search(WM_PLAYER);
	OSReport("Player: %p\n", player);
	theGrid = dActor_c::create(WM_MANTA, 0, &player->pos, 0);
}

void deleteWMGrid() {
	theGrid->Delete();
	theGrid = NULL;
}