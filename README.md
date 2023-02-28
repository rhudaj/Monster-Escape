# Monster-Escape
## Overview
This is a 2D console game for windows developed in C++. 
It is able to run in real-time on the console with the use of the BareLibTerminal libraries. 

### The Game
You play as a character who spawns on a map full of obstacles and survivors. Your goal is to collect all of the survivors before a monster catches you. 
Every level will get progressively more difficult as the monster gets stronger, the map gets more obstacles and there may be more survivors to rescue. 
You can pick up power ups: 
* some slow the monster down 
* some speed you up 
* some freeze the monster

### Features 
* Randomly Generated levels 
* AI monster: 
  * utilizes a path-finding algorithm to search for the player
  * the level of difficulty of the monster is changed by changed the depth of the path-finding algorithm 
* Game menu
* End Screen

## How to Play: 

Use the <kbd>←</kbd> , <kbd>→</kbd> , <kbd>↑</kbd> , <kbd>↓</kbd> arrow keys to move your player

At the end/start of a game you will be prompted to press: `y` to start the game/level or `n` to exit out of the game
