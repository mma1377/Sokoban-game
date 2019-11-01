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
		INTPAIR* box;
		int num_boxes;
		std::string path;

		STATE()
		{
		};
		~STATE()
		{
			delete[] box;
		}

		STATE(INTPAIR plyr, int n_boxes, std::string p) :
			player(plyr), box(new INTPAIR[n_boxes]), num_boxes(n_boxes), path(p)
		{
		}

		bool operator==(const STATE& other)
		{
			if (foundInSearchParallelHistoryGlobalFlag)
			{
				return true;
			}

			if (this->player != other.player)
			{
				return false;
			}

			for (int i = 0; i < num_boxes; i++)
			{
				if (this->box[i] != other.box[i])
				{
					return false;
				}
			}

			return true;
		}

		bool operator!=(const STATE & other)
		{
			return !(*this == other);
		}

		STATE& operator=(const STATE & other)
		{
			this->player = other.player;
			this->path = other.path;
			this->num_boxes = other.num_boxes;
			this->box = new INTPAIR[other.num_boxes];
			std::copy(other.box, other.box + other.num_boxes, this->box);

			return *this;
		}
	};

	class SOKOBAN
	{
		private:
			short n;
			short m;
			short num_boxes;
			bool** game_map;
			INTPAIR player;
			INTPAIR* box;
			INTPAIR* storage;
		
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