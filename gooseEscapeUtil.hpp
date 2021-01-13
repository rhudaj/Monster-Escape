//STUDENTS: Be very careful if you decide to change these values

#ifndef GOOSE_UTIL
#define GOOSE_UTIL

//display characters
const int EMPTY = 0;
const int SHALL_NOT_PASS = int('o');
const int WINNER = 2;
const int PLAYER_CHAR = int('@');
const int MONSTER_CHAR = int('G');
const int WIN_CHAR = int('%'); //% sign, a special character used in the ancient game "Rogue"
const int POWERUP_CHAR = int('P'); 
const int PICKUP_CHAR = int('*'); 

// Screen layout
const int NUM_SCREEN_X = 80;
const int NUM_SCREEN_Y = 25;
const char SETUP_MESSAGE[] = "window: title='Escape the Goose', size=80x25";
const int MIN_SCREEN_X = 0;
const int MIN_SCREEN_Y = 0;
const int MAX_SCREEN_X = NUM_SCREEN_X - 1;
const int MAX_SCREEN_Y = NUM_SCREEN_Y - 1;

// Play area layout
const int NUM_BOARD_X = 80;  
const int NUM_BOARD_Y = 21; 
const int MIN_BOARD_X = 0;
const int MIN_BOARD_Y = 0;
const int MAX_BOARD_X = NUM_BOARD_X - 1;
const int MAX_BOARD_Y = NUM_BOARD_Y - 1;

// Console message area layout
const int NUM_CONSOLE_X = 79;  // needs to be <= NUM_SCREEN_X
const int NUM_CONSOLE_Y = NUM_SCREEN_Y - NUM_BOARD_Y;
const int MIN_CONSOLE_X = 1;
const int MIN_CONSOLE_Y = MAX_BOARD_Y + 1;
const int MAX_CONSOLE_X = MAX_SCREEN_X;
const int MAX_CONSOLE_Y = MAX_SCREEN_Y;

//point increments 
const int UP_ONE = -1; 
const int DOWN_ONE = 1; 
const int RIGHT_ONE = 1; 
const int LEFT_ONE = 1; 

//other 
const int MIN_WALL_LENGTH = 6; 
const int ZERO_LIVES = 0; 
const int STARTING_PICK_UPS = 2;
const int NUM_OPTIONS = 4; 
const int MIN_WALL_SPACING = 4; 



//Output Messages (to go on te board). 
const char gameOver[] = "GAME OVER"; 
const char nextLevelText[] = "YOU WIN! RESTART THE GAME FOR A FOR A NEW LEVEL!"; 

#endif
