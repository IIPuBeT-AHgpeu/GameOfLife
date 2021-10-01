#pragma once

#include <ctime>
#include <cstdlib>
#include "constants.h"

class Map
{

public:
	
	int cur_map[WINDOW_HEIGHT/CELL_SIZE][WINDOW_WIDTH/CELL_SIZE];
	int pre_map[WINDOW_HEIGHT/CELL_SIZE][WINDOW_WIDTH/CELL_SIZE];

	Map()
	{
		//for random generation (set seed by time)
		std::srand(time(0));

		for (int i = 0; i < WINDOW_HEIGHT / CELL_SIZE; i++)
			for (int j = 0; j < WINDOW_WIDTH / CELL_SIZE; j++)
			{
				cur_map[i][j] = rand() % 2;
				pre_map[i][j] = 0;
			}
	}

	bool updateMap()
	{
		bool haveChanges = false;
		int neighborsCount = 0;

		//save old map in pre_map
		for (int i = 0; i < WINDOW_HEIGHT / CELL_SIZE; i++)
			for (int j = 0; j < WINDOW_WIDTH / CELL_SIZE; j++)
			{
				pre_map[i][j] = cur_map[i][j];
			}

		//generate new map
		for (int i = 0; i < WINDOW_HEIGHT / CELL_SIZE; i++)
			for (int j = 0; j < WINDOW_WIDTH / CELL_SIZE; j++)
			{
				neighborsCount = getNeighborsCount(j, i);

				if (pre_map[i][j] == 0)
				{
					if (neighborsCount == 3)
						cur_map[i][j] = 1;
				}
				else
				{
					if (!(neighborsCount == 2 || neighborsCount == 3))
						cur_map[i][j] = 0;
				}
			}

		//have change in new map?
		for (int i = 0; i < WINDOW_HEIGHT / CELL_SIZE && !haveChanges; i++)
			for (int j = 0; j < WINDOW_WIDTH / CELL_SIZE && !haveChanges; j++)
			{
				if (pre_map[i][j] != cur_map[i][j]) haveChanges = true;
			}

		return haveChanges;
	}

	int getNeighborsCount(int x, int y)
	{
		int neighborsCount = 0;
		
		if (y != 0)
		{
			if(x != 0)
				if (pre_map[y - 1][x - 1] == 1) 
					neighborsCount++;

			if(x != WINDOW_HEIGHT / CELL_SIZE - 1)
				if (pre_map[y - 1][x + 1] == 1) 
					neighborsCount++;

			if (pre_map[y - 1][x] == 1)
				neighborsCount++;
		}
		
		if (y != WINDOW_WIDTH / CELL_SIZE - 1)
		{
			if (x != 0)
				if (pre_map[y + 1][x - 1] == 1)
					neighborsCount++;

			if (x != WINDOW_HEIGHT / CELL_SIZE - 1)
				if (pre_map[y + 1][x + 1] == 1)
					neighborsCount++;

			if (pre_map[y + 1][x] == 1)
				neighborsCount++;
		}

		if (x != 0)
			if (pre_map[y][x - 1] == 1)
				neighborsCount++;

		if (x != WINDOW_HEIGHT / CELL_SIZE - 1)
			if (pre_map[y][x + 1] == 1)
				neighborsCount++;

		return neighborsCount;
	}

};