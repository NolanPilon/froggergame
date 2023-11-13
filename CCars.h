#pragma once
#include "CPlayer.h"

class CCars : public CPlayer 
{
	//Inherits from Cplayer
public: 
	void spawnCar(int x, int y, int xv);
};