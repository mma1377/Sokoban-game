#include "sokobanCoreSingleBox.h"
#include <iostream>
#include <omp.h>
//#define _SECURE_SCL 0

namespace sokobanCoreSingleBox {

	bool foundInSearchParallelHistoryGlobalFlag = false;
	bool IDSSearchGlobalFlag = true;

	// Constructor function for SOKOBAN
	SOKOBAN::SOKOBAN(const char* input_file)
	{
		std::ifstream infile(input_file);

		if (!infile.is_open())
		{
			std::cout << "Input not found\n";
			exit(0);
		}

		infile >> n >> m;

		std::cout << n << ' ' << m << '\n';
		game_map = new bool* [n];

		ones = 0;
		for (short row = 0; row < n; row++)
		{
			bool* tmp;
			tmp = new bool[m];
			std::string line;
			infile >> line;
			for (short col = 0; col < m; col++)
			{
				if (line[col] == '#')
				{
					tmp[col] = 0;
				}
				else if (line[col] == '.')
				{
					tmp[col] = 1;
					ones++;
				}
				else if (line[col] == 'S')
				{
					tmp[col] = 1;
					player = std::make_pair(col, row);
					ones++;
				}
				else if (line[col] == '@')
				{
					tmp[col] = 1;
					box = std::make_pair(col, row);
					ones++;
				}
				else if (line[col] == 'X')
				{
					tmp[col] = 1;
					storage = std::make_pair(col, row);
					ones++;
				}
				game_map[row] = tmp;
			}
		}
	};

	// Destructor for SOKOBAN
	SOKOBAN::~SOKOBAN()
	{
		for (short i = 0; i < n; i++)
		{
			delete[] game_map[i];
		}
		delete[] game_map;
	}

	// Utility function that prints out the game map
	void SOKOBAN::print_map()
	{
		for (short i = 0; i < n; i++)
		{
			for (short j = 0; j < m; j++)
			{
				std::cout << game_map[i][j];
			}
			std::cout << '\n';
		}
	}

	// Returns the initial state of the puzzle
	STATE SOKOBAN::initial_state()
	{
		return STATE(player, box, std::string(""));
	}

	// Checks wether a STATE is a goal
	bool SOKOBAN::is_goal(STATE state)
	{
		return state.box == this->storage;
	}

	// Returns all possible successors of a state
	std::vector<STATE>* SOKOBAN::successor(STATE current_state)
	{
		std::vector<STATE>* next_states;
		next_states = new std::vector<STATE>;

		short plyr_x = current_state.player.first;
		short plyr_y = current_state.player.second;
		short box_x = current_state.box.first;
		short box_y = current_state.box.second;

		//Move player one step to the left
		// Check if the move is valid
		if (game_map[plyr_y][plyr_x - 1])
		{
			// Check if the player is moving into the box
			if ((box_x == plyr_x - 1) && (box_y == plyr_y))
			{
				// Check if the box is movable in this direction
				if (game_map[box_y][box_x - 1])
				{
					next_states->push_back(STATE(std::make_pair(plyr_x - 1, plyr_y),
						std::make_pair(box_x - 1, box_y), current_state.path + 'L'));
				}
			}
			else
			{
				next_states->push_back(STATE(
					std::make_pair(plyr_x - 1, plyr_y),
					std::make_pair(box_x, box_y),
					current_state.path + 'L'));
			}
		}

		//Move player one step to the right
		// Check if the move is valid
		if (game_map[plyr_y][plyr_x + 1])
		{
			// Check if the player is moving into the box
			if ((box_x == plyr_x + 1) && (box_y == plyr_y))
			{
				// Check if the box is movable in this direction
				if (game_map[box_y][box_x + 1])
				{
					next_states->push_back(STATE(std::make_pair(plyr_x + 1, plyr_y),
						std::make_pair(box_x + 1, box_y), current_state.path + 'R'));
				}
			}
			else
			{
				next_states->push_back(STATE(
					std::make_pair(plyr_x + 1, plyr_y),
					std::make_pair(box_x, box_y),
					current_state.path + 'R'));
			}
		}

		// Move player one step upward
		// Check if the move is valid
		if (game_map[plyr_y - 1][plyr_x])
		{
			// Check if the player is moving into the box
			if ((box_x == plyr_x) && (box_y == plyr_y - 1))
			{
				// Check if the box is movable in this direction
				if (game_map[box_y - 1][box_x])
				{
					next_states->push_back(STATE(std::make_pair(plyr_x, plyr_y - 1),
						std::make_pair(box_x, box_y - 1), current_state.path + 'U'));
				}
			}
			else
			{
				next_states->push_back(STATE(
					std::make_pair(plyr_x, plyr_y - 1),
					std::make_pair(box_x, box_y),
					current_state.path + 'U'));
			}
		}

		// Move player one step downward
		// Check if the move is valid
		if (game_map[plyr_y + 1][plyr_x])
		{
			// Check if the player is moving into the box
			if ((box_x == plyr_x) && (box_y == plyr_y + 1))
			{
				// Check if the box is movable in this direction
				if (game_map[box_y + 1][box_x])
				{
					next_states->push_back(STATE(std::make_pair(plyr_x, plyr_y + 1),
						std::make_pair(box_x, box_y + 1), current_state.path + 'D'));
				}
			}
			else
			{
				next_states->push_back(STATE(
					std::make_pair(plyr_x, plyr_y + 1),
					std::make_pair(box_x, box_y),
					current_state.path + 'D'));
			}
		}

		//std::random_shuffle(next_states->begin(), next_states->end());

		return next_states;
	}

	// Bread-first Search function that searches for the answer
	STATE SOKOBAN::bfs(const unsigned int& history_size, unsigned int& count)
	{
		// Initialize a queue and insert the initial state into that queue
		STATE initial_state = this->initial_state();
		std::queue<STATE> queue;
		queue.push(initial_state);

		// Initialize an array to store the kth most recent states
		// that we insert into the queue (k = history_size)
		STATE* visited_states;
		visited_states = new STATE[history_size];
		unsigned int i = 0;
		unsigned int cap = 0;

		STATE state;
		while (!queue.empty())
		{
			// Increment the number of states checked (visited)
			count++;
			state = queue.front();
			queue.pop();
			if (is_goal(state))
			{
				// Deallocate the visited_states array
				delete[] visited_states;

				return state;
			}
			std::vector<STATE>* successors = successor(state);
			for (auto s = successors->begin(); s != successors->end(); s++)
			{
				if (std::find(visited_states, visited_states + cap, *s) == visited_states + cap)
				{
					// Found an unvisited state
					queue.push(*s);

					// The state is inserted into queue, so it is a visited
					// state and must be added into visited_states
					visited_states[i++] = *s;
					// If the array is full, circle around
					i = i % history_size;
					cap = std::min(++cap, history_size);
				}
			}

			// Clear the successors vector when done with it
			successors->clear();

			//if (count % 1000 == 0)
			//	std::cout << count << '\n';
		}

		// Deallocate the visited_states array
		delete[] visited_states;

		// When no answer is found, return this
		return STATE(std::make_pair(-1, -1), std::make_pair(-1, -1), std::string(""));
	}

	// Bread-first Search function that searches for the answer and uses
	// multi-threaded search when searching in the visited states array
	STATE SOKOBAN::bfs_omp(const unsigned int& history_size, unsigned int& count)
	{
		// Initialize a queue and insert the initial state into that queue
		STATE initial_state = this->initial_state();
		std::queue<STATE> queue;
		queue.push(initial_state);

		// Initialize an array to store the kth most recent states
		// that we insert into the queue (k = history_size)
		STATE* visited_states;
		visited_states = new STATE[history_size];
		unsigned int i = 0;
		unsigned int cap = 0;

		while (!queue.empty())
		{
			// Increment the number of states checked (visited)
			count++;
			STATE state = queue.front();
			queue.pop();
			if (is_goal(state))
			{
				// Deallocate the visited_states array
				delete[] visited_states;

				return state;
			}

			// Get the successors for the current state
			std::vector<STATE>* successors = successor(state);

			// This is important because we want each thread to search a
			// specific part of the array
			omp_set_dynamic(0);

			omp_set_num_threads(omp_get_max_threads());

			for (auto s = successors->begin(); s != successors->end(); s++)
			{
				// This flag is always set to false at the beginning and
				// the end of the search
				foundInSearchParallelHistoryGlobalFlag = false;
#pragma omp parallel
				{
					// Split the array into equal sections. Each section will be
					// searched by one of the threads
					int thread_num = omp_get_thread_num();
					int number_of_threads = omp_get_num_threads();
					//std::cout << "thread = " << thread_num << "\n";

					int first = std::floor((float)cap * ((float)thread_num / (float)number_of_threads));
					int last = std::floor((float)cap * ((float)(thread_num + 1) / (float)number_of_threads));

					if (std::find(visited_states + first, visited_states + last, *s) != visited_states + last) {
						// If found a match, set this flag to true so all other
						// threads stop their search
						foundInSearchParallelHistoryGlobalFlag = true;
					}
#pragma omp barrier
					{
					}
				}

				// If the flag is true, set it to false and go on
				if (foundInSearchParallelHistoryGlobalFlag) {
					foundInSearchParallelHistoryGlobalFlag = false;
					continue;
				}

				// Found an unvisited state
				queue.push(*s);

				// The state is inserted into queue, so it is a visited
				// state and must be added into visited_states
				visited_states[i++] = *s;
				// If the array is full, circle around
				i = i % history_size;
				cap = std::min(++cap, history_size);

			}
			// Clear the successors vector when done with it
			successors->clear();

			/*if (count % 1000 == 0)
				std::cout << count << '\n';*/

		}

		// Deallocate the visited_states array
		delete[] visited_states;

		// When no answer is found, return this
		return STATE(std::make_pair(-1, -1), std::make_pair(-1, -1), std::string(""));
	}

	// Bread-first Search function that searches for the answer
	// Maximum depth must always be specified
	STATE SOKOBAN::dfs(int max_depth, const unsigned int& history_size, unsigned int& count)
	{
		// Initialize a stack and insert the initial state into that stack
		STATE initial_state = this->initial_state();
		std::stack<STATE> stack;
		stack.push(initial_state);

		// Initialize an array to store the kth most recent states
		// that we insert into the queue (k = history_size)
		STATE* visited_states;
		visited_states = new STATE[history_size];
		unsigned int i = 0;
		unsigned int cap = 0;

		STATE state;
		while (!stack.empty())
		{
			state = stack.top();
			stack.pop();

			// Max depth is reached
			if (state.path.length() > max_depth)
			{
				continue;
			}

			// Increment the number of states checked (visited)
			count++;

			if (is_goal(state))
			{
				// Deallocate the visited_states array
				delete[] visited_states;

				return state;
			}

			// Get the successors for the current state
			std::vector<STATE>* successors = successor(state);

			for (auto s = successors->begin(); s != successors->end(); s++)
			{
				if (std::find(visited_states, visited_states + cap, *s) == visited_states + cap)
				{
					// Found an unvisited state
					stack.push(*s);

					// The state is inserted into stack, so it is a visited
					// state and must be added into visited_states
					visited_states[i++] = *s;
					// If the array is full, circle around
					i = i % history_size;
					cap = std::min(++cap, history_size);
				}
			}

			// Clear the successors vector when done with it
			successors->clear();
		}

		// Deallocate the visited_states array
		delete[] visited_states;

		// When no answer is found, return this
		return STATE(std::make_pair(-1, -1), std::make_pair(-1, -1), std::string(""));
	}

	// Bread-first Search function that searches for the answer and uses
	// multi-threaded search when searching in the visited states array
	// Maximum depth must always be specified
	STATE SOKOBAN::dfs_omp(int max_depth, const unsigned int& history_size, unsigned int& count)
	{
		// Initialize a stack and insert the initial state into that stack
		STATE initial_state = this->initial_state();
		std::stack<STATE> stack;
		stack.push(initial_state);

		// Initialize an array to store the kth most recent states
		// that we insert into the queue (k = history_size)
		STATE* visited_states;
		visited_states = new STATE[history_size];
		unsigned int i = 0;
		unsigned int cap = 0;

		STATE state;
		while (!stack.empty())
		{
			state = stack.top();
			stack.pop();

			// Max depth is reached
			if (state.path.length() > max_depth)
			{
				continue;
			}

			// Increment the number of states checked (visited)
			count++;

			if (is_goal(state))
			{
				// Deallocate the visited_states array
				delete[] visited_states;

				return state;
			}

			// Get the successors for the current state
			std::vector<STATE>* successors = successor(state);

			// This is important because we want each thread to search a
			// specific part of the array
			omp_set_dynamic(0);

			omp_set_num_threads(omp_get_max_threads());

			for (auto s = successors->begin(); s != successors->end(); s++)
			{
				// This flag is always set to false at the beginning and
				// the end of the search
				foundInSearchParallelHistoryGlobalFlag = false;
				foundInSearchParallelHistoryGlobalFlag = false;
#pragma omp parallel
				{
					// Split the array into equal sections. Each section will be
					// searched by one of the threads
					int thread_num = omp_get_thread_num();
					int number_of_threads = omp_get_num_threads();
					//std::cout << "thread = " << thread_num << "\n";

					int first = std::floor((float)cap * ((float)thread_num / (float)number_of_threads));
					int last = std::floor((float)cap * ((float)(thread_num + 1) / (float)number_of_threads));

					if (std::find(visited_states + first, visited_states + last, *s) != visited_states + last) {
						// If found a match, set this flag to true so all other
						// threads stop their search
						foundInSearchParallelHistoryGlobalFlag = true;
					}

#pragma omp barrier
					{
					}
				}

				// If the flag is true, set it to false and go on
				if (foundInSearchParallelHistoryGlobalFlag) {
					foundInSearchParallelHistoryGlobalFlag = false;
					continue;
				}

				// Found an unvisited state
				stack.push(*s);

				// The state is inserted into stack, so it is a visited
				// state and must be added into visited_states
				visited_states[i++] = *s;
				// If the array is full, circle around
				i = i % history_size;
				cap = std::min(++cap, history_size);
			}

			// Clear the successors vector when done with it
			successors->clear();
		}

		// Deallocate the visited_states array
		delete[] visited_states;

		// When no answer is found, return this
		return STATE(std::make_pair(-1, -1), std::make_pair(-1, -1), std::string(""));
	}

	// Iterative Deepening Search function that searches for the answer
	STATE SOKOBAN::ids(const unsigned int& history_size, unsigned int& count)
	{
		// When this flag is set to false, the == operator for STATE compares
		// the level of the states, as well as their player and box coordinates.
		// This is to ensure optimal results
		IDSSearchGlobalFlag = false;

		STATE result;
		for (int depth = 0; depth < 1000; depth++)
		{
			std::cout << "SEARCHING DEPTH " << depth << '\n';
			result = dfs(depth, history_size, count);

			//std::cout << "COUNT = " << count << "STATES VISITED\n";

			// If an answer is found, halt
			if (this->is_goal(result))
			{
				break;
			}
		}

		// Set the flag back to true
		IDSSearchGlobalFlag = true;

		return result;
	}

	// Iterative Deepening Search function that searches for the answer and uses
	// multi-threaded search when searching in the visited states array
	STATE SOKOBAN::ids_omp(const unsigned int& history_size, unsigned int& count)
	{
		// When this flag is set to false, the == operator for STATE compares
		// the level of the states, as well as their player and box coordinates.
		// This is to ensure optimal results
		IDSSearchGlobalFlag = false;

		STATE result;
		for (int depth = 0; depth < 1000; depth++)
		{
			std::cout << "SEARCHING DEPTH " << depth << '\n';
			result = dfs_omp(depth, history_size, count);

			//std::cout << "COUNT = " << count << "STATES VISITED\n";

			// If an answer is found, halt
			if (this->is_goal(result))
			{
				break;
			}
		}

		// Set the flag back to true
		IDSSearchGlobalFlag = true;

		return result;
	}
}
