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

namespace sokobanCoreSingleBox
{
	typedef std::pair<short, short> INTPAIR;

	// Global variable which helps multi-threaded searching run noticably faster
	// This flag is always set to false, except when a thread has found a result,
	// in which case it is changed to true. This causes the == operator for the
	// STATE struct to automatically return true no matter what the STATES are.
	// As a results, std::find will think it has found the result in each individual
	// thread, and terminates the search, and thus not letting the threads continue
	// their searchs.*/
	extern bool foundInSearchParallelHistoryGlobalFlag;

	// Global variable which makes the IDS search always find the optimal result
	// This flag is always true, and is only set to false when using the IDS search
	// algorithm. When false, the == operator for the STATE struct will check the
	// length of the nodes' paths (or in other words, the level of the node in the
	// search tree). Doing this will ensure an optimal result for the IDS search.
	extern bool IDSSearchGlobalFlag;

	struct STATE
	{
		// Coordinates of the player (or agent, if you like to be more technical)
		INTPAIR player;
		//Coordinates of the boxe
		INTPAIR box;
		// The path the player has moved so far
		std::string path;

		// Default constructor for STATE
		STATE()
		{
		};

		// Destructor for STATE
		~STATE()
		{
		}

		// Copy constructor for STATE
		STATE(const STATE& other) :
			player(other.player), box(other.box), path(other.path)
		{
		}

		// Another constructor for STATE
		STATE(INTPAIR plyr, INTPAIR b, std::string p) :
			player(plyr), box(b), path(p)
		{
		}

		// A utility function that prints the state
		void print()
		{
			// Print the current position of the player
			printf("PLAYER (%d, %d)\t[ ", player.first, player.second);
			// Print the current position of the box
			std::cout << "B(" << box.first << ", " << box.second << ") ";
			std::cout << "]\t";
			std::cout << path << '\n';
		}

		// == Operator overload for STATE
		bool operator==(const STATE& other)
		{
			// foundInSearchParallelHistoryGlobalFlag is only used in functions 
			//that use multi-threaded search.
			// This flag is set to true after std::find has found a match in
			// a thread. After that, every other std::find will think they
			// found a match and as a result will cease to continue the search
			// process. Without this flag, the thread that first found a match
			// would have to wait for the other threads to end their search.
			
			// The first term is to ensure IDS search returns the optimal
			// result. IDSSearchGlobalFlag is always true when using other
			// searches.

			return foundInSearchParallelHistoryGlobalFlag || (this->player == other.player) && (this->box == other.box) && (!IDSSearchGlobalFlag || (this->path.length() <= other.path.length()));
		}

		// != operator overload for STATE
		bool operator!=(const STATE & other)
		{
			return !(*this == other);
		}

		// Copy operator overload for STATE
		STATE& operator=(const STATE & other)
		{
			this->player = other.player;
			this->box = other.box;
			this->path = other.path;
			return *this;

			return *this;
		}
	};

	class SOKOBAN
	{
	private:
		// Number of rows
		short n;
		// Number of columns
		short m;
		
		short ones;

		// Number of boxes
		short num_boxes;
		// An array of 0s and 1s that tells us which squares of
		// the game map we can move to. Wall -> 0, Any other thing -> 1
		bool** game_map;
		// Initial coordinates of the player
		INTPAIR player;
		// Array of initial coordinates of the box
		INTPAIR box;
		// Array of initial coordinates of the storage location (or goal)
		INTPAIR storage;

	public:
		// Constructor function for SOKOBAN
		SOKOBAN(const char*);

		// Destructor for SOKOBAN
		~SOKOBAN();

		// Utility function that prints out the game map
		void print_map();

		// Returns the initial state of the puzzle
		STATE initial_state();

		// Checks wether a state is a final (goal) state
		bool is_goal(STATE);

		// Returns all possible successors of a state
		std::vector<STATE>* successor(STATE);

		// Bread-first Search function that searches for the answer
		STATE bfs(const unsigned int&, unsigned int&);

		// Bread-first Search function that searches for the answer and uses
		// multi-threaded search when searching in the visited states array
		STATE bfs_omp(const unsigned int&, unsigned int&);

		// Bread-first Search function that searches for the answer
		// Maximum depth must always be specified
		STATE dfs(int, const unsigned int&, unsigned int&);

		// Bread-first Search function that searches for the answer and uses
		// multi-threaded search when searching in the visited states array
		// Maximum depth must always be specified
		STATE dfs_omp(int, const unsigned int&, unsigned int&);

		// Iterative Deepening Search function that searches for the answer
		STATE ids(const unsigned int&, unsigned int&);

		// Iterative Deepening Search function that searches for the answer and uses
		// multi-threaded search when searching in the visited states array
		STATE ids_omp(const unsigned int&, unsigned int&);
	};
};