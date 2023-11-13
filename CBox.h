#pragma once
#include "CPlayer.h"
class CBox : public CPlayer
{
	//Inherits from Cplayer
public:
	bool exists = false;
	void spawnBox(int x, int y);
};