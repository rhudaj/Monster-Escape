#include <ctime>
#include <cstdlib>
#include "gooseEscapeUtil.hpp"

//random value between 0 - NUM_BOARD_Y
int randomX() 
{
	return rand()%NUM_BOARD_X; 
}

//random value between 0 - NUM_BOARD_X
int randomY() 
{
	return rand()%NUM_BOARD_Y; 
}

//random value between 0 - 1
int randomBool() 
{
	return rand()%2; 
}

//random value between 0 - MIN_WALL_LENGTH
int randomWallLength() 
{
	return (rand()%MIN_WALL_LENGTH) + MIN_WALL_LENGTH; 
}

