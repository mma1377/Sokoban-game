#pragma once
#include <fstream>
#include <vector>
#include <queue>
#include <iostream>
#include <string>
#include <algorithm>

#define PAIR(T1, T2) std::pair<T1, T2>
#define INTPAIR PAIR(short, short)
#define STATE PAIR(INTPAIR, INTPAIR)

namespace sokobanCore {

	class SOKOBAN
	{
	private:
		short n;
		short m;
		bool** game_map;
		INTPAIR player;
		INTPAIR box;
		INTPAIR storage;

	public:
		// Constructor function for SOKOBAN class
		SOKOBAN(const char*);
		~SOKOBAN();
		void print_map();
		bool is_goal(STATE);
		std::vector<STATE>* successor(STATE);
		STATE bfs();
		STATE bfs_omp();
	};

}