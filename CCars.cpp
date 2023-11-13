#include "CCars.h"
#include <iostream>
using namespace std;


void CCars::spawnCar(int x, int y, int xv)
{
    position.x = x;
    position.y = y;
    velocity.x = xv;
    velocity.y = 0;
}
