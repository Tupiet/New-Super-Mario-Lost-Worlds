#ifndef __BADDY_H
#define __BADDY_H

class daEnLaunchStar_c;
class daEnShyCart_c;
class daEnRail_c;

daEnShyCart_c* playerCart[4] = {};

bool launchStarChipCollectedBeforeFlag[32][5];
bool launchStarChipCollectedAfterFlag[32][5];

bool playerInWork[4] = { false,false,false,false };

bool playerRiding[4] = { false,false,false,false };

#endif