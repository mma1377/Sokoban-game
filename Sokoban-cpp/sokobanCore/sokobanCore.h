#pragma once

/*
This file contains the program that receives an initial state
of the Sokoban game, produces successors for each state and yields
the final result. It uses uninformed searching algorithms to search
for the answer in the search space.
*/

#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <iostream>
#include <string>
#include <algorithm>
#include <math.h>
#include <chrono>

namespace sokobanCore
{
	typedef std::pair<short, short> INTPAIR;

	extern bool foundInSearchParallelHistoryGlobalFlag;

	struct STATE
	{
		INTPAIR player;
		INTPAIR box;
		std::string path;

		STATE()
		{

		};
		STATE(INTPAIR plyr, INTPAIR b, std::string p)
		{
			this->player = plyr;
			this->box = b;
			this->path = p;
		}
		bool operator==(const STATE& other)
		{
			return foundInSearchParallelHistoryGlobalFlag || (this->player == other.player) && (this->box == other.box) && (this->path.length() <= other.path.length());
		}
		bool operator!=(const STATE & other)
		{
			return !(*this == other);
		}
		STATE& operator=(const STATE & other)
		{
			this->player = other.player;
			this->box = other.box;
			this->path = other.path;
			return *this;
		}
	};

	class SOKOBAN
	{
		private:
			short n;
			short m;
			short ones;
			bool** game_map;
			INTPAIR player;
			INTPAIR box;
			INTPAIR storage;
		
		public:
			// Constructor function for SOKOBAN class
			SOKOBAN(const char*);
			~SOKOBAN();
			void print_map();
			STATE initial_state();
			bool is_goal(STATE);
			std::vector<STATE>* successor(STATE);
			STATE bfs(const unsigned int&, unsigned int&);
			STATE bfs_omp(const unsigned int&, unsigned int&);
			STATE dfs(int, const unsigned int&, unsigned int&);
			STATE dfs_omp(int, const unsigned int&, unsigned int&);
			STATE ids(const unsigned int&, unsigned int&);
			STATE ids_omp(const unsigned int&, unsigned int&);
	};
};