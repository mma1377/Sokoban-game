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
		// The number of the boxes in the state
		short num_boxes;
		// An array of coordinates. Each coordinate correspondes to one of the boxes
		INTPAIR* box;
		// The path the player has moved so far
		std::string path;

		// Default constructor for STATE
		STATE(): box(new INTPAIR)
		{
		};

		// Destructor for STATE
		~STATE()
		{
			delete[] box;
		}

		// Copy constructor for STATE
		STATE(const STATE& other) :
			player(other.player), num_boxes(other.num_boxes), path(other.path)
		{
			this->box = new INTPAIR[this->num_boxes];
			std::copy(other.box, other.box + other.num_boxes, this->box);
		}

		// Another constructor for STATE
		STATE(INTPAIR plyr, int n_boxes, std::string p) :
			player(plyr), box(new INTPAIR[n_boxes]), num_boxes(n_boxes), path(p)
		{
		}

		// A utility function that prints the state
		void print()
		{
			// Print the current position of the player
			printf("PLAYER (%d, %d)\t[ ", player.first, player.second);
			// Print the current positions of the boxes
			for (int i = 0; i < num_boxes; i++)
			{
				std::cout << "B(" << box[i].first << ", " << box[i].second << ") ";
			}
			std::cout << "]\t";
			std::cout << path << '\n';
		}

		// == Operator overload for STATE
		bool operator==(const STATE& other)
		{
			// This is only used in functions that use multi-threaded search.
			// This flag is set to true after std::find has found a match in
			// a thread. After that, every other std::find will think they
			// found a match and as a result will cease to continue the search
			// process. Without this flag, the thread that first found a match
			// would have to wait for the other threads to end their search.
			if (foundInSearchParallelHistoryGlobalFlag)
			{
				return true;
			}

			// Check if the coordinates are different
			if (this->player != other.player)
			{
				return false;
			}

			// Check if ANY box has a different value than the same box in
			// the other state
			for (int i = 0; i < num_boxes; i++)
			{
				if (this->box[i] != other.box[i])
				{
					return false;
				}
			}

			// The IDSSearchGlobalFlag is to ensure IDS search returns the 
			// optimal result. IDSSearchGlobalFlag is always true when using
			// other searches.
			return true && (IDSSearchGlobalFlag || this->path.length() <= other.path.length());
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
			this->path = other.path;
			this->num_boxes = other.num_boxes;
			// Create a new array of box coordinates
			this->box = new INTPAIR[other.num_boxes];
			// Copy each box coordinate to the new array
			std::copy(other.box, other.box + other.num_boxes, this->box);

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
			// Number of boxes
			short num_boxes;
			// An array of 0s and 1s that tells us which squares of
			// the game map we can move to. Wall -> 0, Any other thing -> 1
			bool** game_map;
			// Initial coordinates of the player
			INTPAIR player;
			// Array of initial coordinates of the boxes
			INTPAIR* boxes;
			// Array of initial coordinates of the storage locations (or goals)
			INTPAIR* goals;
		
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
