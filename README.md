# GameOfLife

## Description

This application is a game of life written in C++ based on the SFML library. Application have 2 windows: the first window it is console (for informational messages)
and the secon window it is game window. In beginning it have a random map. If at some step of the game the field does not change after the previous step, the game will 
display a message about the established stability of populations and will close the window of game. If you push "Space" key game will be paused/resumed. If game is paused
you could kill/alive any cell (left mouse button click).

## Files description

### constants.h

Have contants: window size, cell size, tact (the map will be updated once a TACT).

### Map.h

 Map class:  
 public fields:  
 `int pre_map[][]`: previous map (constructor fill this map by 0)  
 `int cur_map[][]`: current map (constructor generate a random map)  
 public functions:  
 `Map Map()` - constructor;  
 `void updateMap()` - function for update current map;  
 `int getNeighborsCount(int x, int y)`:  
 input:  
 `int x` - number of column in map;  
 `int y` - number of string in map;  
 output:  
 `int neigborsCount`  
      
### Main.cpp

Here is game logic;
