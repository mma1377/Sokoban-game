#include "sokobanCore.h"
#include <iostream>
#include <omp.h>
//#define _SECURE_SCL 0

namespace sokobanCore {
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
		game_map = new bool*[n];

		ones = 0;
		for (short row = 0; row < n; row++)
		{
			bool *tmp;
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

	SOKOBAN::~SOKOBAN()
	{
		for (short i = 0; i < n; i++)
		{
			delete game_map[i];
		}
		delete game_map;
	}

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

	STATE SOKOBAN::initial_state()
	{
		return STATE(player, box, std::string(""));
	}

	bool SOKOBAN::is_goal(STATE state)
	{
		if (state.box == this->storage)
		{
			return true;
		}
		return false;
	}

	std::vector<STATE>* SOKOBAN::successor(STATE current_state)
	{
		std::vector<STATE>* next_states;
		next_states = new std::vector<STATE>;
		// Horizontal movements
		char h[2] = {'L', 'R'};
		// Vertical movements
		char v[2] = {'U', 'D'};
		for (short i = -1; i < 2; i += 2)
		{
			// Move player one step to the left/right
			short next_plyr_x = current_state.player.first + i;
			short next_plyr_y = current_state.player.second;

			// Check if the move is valid
			if (game_map[next_plyr_y][next_plyr_x] == 1)
			{
				// Check if the player is moving into the box
				if (current_state.box.first == next_plyr_x && current_state.box.second == next_plyr_y)
				{
					short next_box_x = current_state.box.first + i;
					short next_box_y = current_state.box.second;
					// Check if the box is movable in this direction
					if (game_map[next_box_y][next_box_x] == 1)
					{
						next_states->push_back(STATE(std::make_pair(next_plyr_x, next_plyr_y), 
										std::make_pair(next_box_x, next_box_y), current_state.path + h[std::max((short)0, i)]));
					}
				}
				else
				{
					next_states->push_back(STATE(
									std::make_pair(next_plyr_x, next_plyr_y), 
									std::make_pair(current_state.box.first, current_state.box.second),
									current_state.path + h[std::max((short)0, i)]));
				}
			}

			// Move player one step upward/downward
			next_plyr_x = current_state.player.first;
			next_plyr_y = current_state.player.second + i;

			// Check if the move is valid
			if (game_map[next_plyr_y][next_plyr_x] == 1)
			{
				// Check if the player is moving into the box
				if (current_state.box.first == next_plyr_x && current_state.box.second == next_plyr_y)
				{
					short next_box_x = current_state.box.first;
					short next_box_y = current_state.box.second + i;
					// Check if the box is movable in this direction
					if (game_map[next_box_y][next_box_x] == 1)
					{
						next_states->push_back(STATE(std::make_pair(next_plyr_x, next_plyr_y), 
										std::make_pair(next_box_x, next_box_y), current_state.path + v[std::max((short)0, i)]));
					}
				}
				else
				{
					next_states->push_back(STATE(
									std::make_pair(next_plyr_x, next_plyr_y), 
									std::make_pair(current_state.box.first, current_state.box.second),
									current_state.path + v[std::max((short)0, i)]));
				}
				
			}
		}

		return next_states;
	}

	STATE SOKOBAN::bfs()
	{
		STATE initial_state = this->initial_state();
		std::queue<STATE> queue;
		queue.push(initial_state);
	// If a manual HISTORY SIZE is not set, make it the maximum number needed, which is
	// the tartib of 2 in the number of ones
	#ifndef HISTORY_SIZE
	#define HISTORY_SIZE int(((this->ones) * (this->ones - 1)))
	#endif
		unsigned int history_size = HISTORY_SIZE;
		STATE* visited_states;
		visited_states = new STATE[history_size];
		unsigned int i = 0;
		unsigned int cap = 0;
		std::vector<STATE> history;
		//history.resize(HISTORY_SIZE);

		std::cout << "HISTORY SIZE: " << history_size << '\n';
		int count = 0;
		while (!queue.empty())
		{
			count++;
			STATE state = queue.front();
			// history.insert(state);
			// history[count % history_size] = state;
			visited_states[i++] = state;
			i = i % history_size;
			cap = std::min(++cap, history_size);
			queue.pop();
			if (is_goal(state))
			{
				std::cout << "COUNT: " << count << '\n';
				return state;
			}
			std::vector<STATE>* successors = successor(state);
			for (auto s = successors->begin(); s != successors->end(); s++)
			{
				bool flag = true;
				// if (std::find(history.begin(), history.end(), *s) != history.end())
				// {
				//     continue;
				// }
				if (std::find(visited_states, visited_states + history_size, *s) != visited_states + history_size)
				{
					continue;
				}
				else
				{
					queue.push(*s);
				}
			}
			delete successors;
			if (count % 1000 == 0) 
				std::cout << count << '\n';
			
		}

		delete visited_states;
		return STATE(std::make_pair(-1, -1), std::make_pair(-1, -1), std::string(""));
	}

	STATE SOKOBAN::bfs_omp()
	{
		STATE initial_state = this->initial_state();
		std::queue<STATE> queue;
		queue.push(initial_state);

		// long long int history_size = this->n * this->n * this->m * this->m;
		// STATE* visited_states;
		// visited_states = new STATE[history_size];
		// long long int i = 0;
		// long long int cap = 0;
		int indx = 0;
		int top = 0;
		//std::vector<STATE> history;
		int history_size = 50000;
		STATE defaultState = STATE();
		//history.resize(history_size, defaultState);

		STATE* history = new STATE[history_size];
		for (int i = 0; i < history_size; i++) {
			history[i] = defaultState;
		}

		int count = 0;
		while (!queue.empty())
		{
			count++;
			STATE state = queue.front();
			//history.insert(state);
			history[indx++] = state;
			// visited_states[i++] = state;
			// i = i % history_size;
			indx = indx % history_size;
			top++;
			if (top > history_size)
				top = history_size;
			// cap = std::min(++cap, history_size);
			queue.pop();
			if (is_goal(state))
			{
				std::cout << "COUNT: " << count << '\n';
				//std::cout << "Vector size: " << history.size() << '\n';
				return state;
			}
			std::vector<STATE>* successors = successor(state);
			omp_set_dynamic(0);
			
			omp_set_num_threads(omp_get_max_threads());
			
			for (auto s = successors->begin(); s != successors->end(); s++)
			{
				bool flag = true;
				bool foundInHistoryFlag = false;
#pragma omp parallel
				{
					int thread_num = omp_get_thread_num();
					int number_of_threads = omp_get_num_threads();
					//std::cout << "thread = " << thread_num << "\n";
					
					/*auto first = history.begin() + std::floor((float)history.size() * ((float)thread_num / (float)number_of_threads));
					auto last = history.begin() + std::floor((float)history.size() * ((float)(thread_num + 1) / (float)number_of_threads));*/
					
					int first = std::floor((float)top * ((float)thread_num / (float)number_of_threads));
					int last = std::floor((float)top * ((float)(thread_num + 1) / (float)number_of_threads));

					//std::string h = std::hash<STATE>(*s);
//#pragma omp barrier
//					{
//					std::cout << thread_num << " " << last - first << "\n";
//					}

					/*if (std::search(first, last, s, s + 1, [](STATE a, STATE b) -> bool {return a == b; }) != last) {
						foundInHistoryFlag = true;
					}*/

					/*if (std::find_if(first, last, [s, defaultState, foundInHistoryFlag](STATE a) -> bool {return a == *s || a == defaultState || foundInHistoryFlag; }) != last) {
						foundInHistoryFlag = true;
					}*/

					/*if (std::find(first, last, *s) != last) {
						foundInHistoryFlag = true;
					}*/

					if (std::find(history + first, history + last, *s) != history + last) {
						foundInHistoryFlag = true;
					}

					/*for (int i = first; i != last; i++) {
						if (foundInHistoryFlag || (history[i] == defaultState))
							break;
						if (history[i] == *s)
							foundInHistoryFlag = true;
					}*/

					/*for (auto i = first; i != last; i++) {
						if (foundInHistoryFlag || *i == defaultState)
							break;
						if (*i == *s)
							foundInHistoryFlag = true;
					}*/
#pragma omp barrier
					{
					}
				}
//#pragma omp single
				if (foundInHistoryFlag)
					continue;
				queue.push(*s);

			}
			delete successors;
			//std::cout << count << '\n';
			if (count % 1000 == 0)
				std::cout << count << '\n';

		}
		return STATE(std::make_pair(-1, -1), std::make_pair(-1, -1), std::string(""));
	}

	STATE SOKOBAN::dfs(STATE state, int depth)
	{
		if (this->is_goal(state))
		{
			return state;
		}
		if (depth == 0)
		{
			return STATE(std::make_pair(-1, -1), std::make_pair(-1, -1), std::string(""));
		}
		std::vector<STATE>* successors = successor(state);
			for (auto s = successors->begin(); s != successors->end(); s++)
			{
				return dfs(state, --depth);
			}
		delete successors;
	}

	STATE SOKOBAN::dfs(STATE state, int depth, STATE* visited_states, int& history_size, int& i, int& cap)
	{
		if (this->is_goal(state))
		{
			return state;
		}
		if (depth == 0)
		{
			return STATE(std::make_pair(-1, -1), std::make_pair(-1, -1), std::string(""));
		}
		visited_states[i++] = state;
		i = i % history_size;
		cap = std::min(++cap, history_size);
		std::vector<STATE>* successors = successor(state);
			for (auto s = successors->begin(); s != successors->end(); s++)
			{
				if (std::find(visited_states, visited_states + history_size, *s) != visited_states + history_size)
				{
					continue;
				}
				else
				{
					dfs(state, --depth, visited_states, history_size, i, cap);
				}
			}
			delete successors;
	}
}