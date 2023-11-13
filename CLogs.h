#pragma once
#include "CPlayer.h"

class CLogs : public CPlayer 
{	
public:
	bool isLong = false;
	void spawnLogs(int x, int y, int xv);

};