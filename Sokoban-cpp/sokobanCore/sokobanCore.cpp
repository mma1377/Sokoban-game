#include "sokobanCore.h"
#include <iostream>
#include <omp.h>
//#define _SECURE_SCL 0

namespace sokobanCore {

	bool foundInSearchParallelHistoryGlobalFlag = false;
	bool idsFlag = false;

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
		return state.box == this->storage;
	}

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

	STATE SOKOBAN::bfs(const unsigned int& history_size, unsigned int& count)
	{
		idsFlag = false;
		std::cout << history_size << '\n';
		STATE initial_state = this->initial_state();
		std::queue<STATE> queue;
		queue.push(initial_state);

		STATE* visited_states;
		visited_states = new STATE[history_size];
		unsigned int i = 0;
		unsigned int cap = 0;

		STATE state;
		while (!queue.empty())
		{
			count++;
			state = queue.front();

			std::cout << "CHECKING PATH " << count << ' ' << state.path.length() << ' ' << state.path << '\n';
			printf("\t\t\tP(%d,% d)\tB(%d, %d)\n", state.player.first, state.player.second, state.box.first, state.box.second);
			visited_states[i++] = state;
			i = i % history_size;
			cap = std::min(++cap, history_size);

			queue.pop();
			if (is_goal(state))
			{
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
					visited_states[i++] = *s;
					i = i % history_size;
					cap = std::min(++cap, history_size);
				}
			}
			successors->clear();
			if (count % 1000 == 0)
				std::cout << count << '\n';
		}

		delete[] visited_states;
		return STATE(std::make_pair(-1, -1), std::make_pair(-1, -1), std::string(""));
	}

	STATE SOKOBAN::bfs_omp(const unsigned int& history_size, unsigned int& count)
	{
		idsFlag = false;
		STATE initial_state = this->initial_state();
		std::queue<STATE> queue;
		queue.push(initial_state);

		int indx = 0;
		int top = 0;

		STATE* history = new STATE[history_size];
		
		//int count = 0;
		while (!queue.empty())
		{
			count++;
			STATE state = queue.front();
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
				foundInSearchParallelHistoryGlobalFlag = false;
#pragma omp parallel
				{
					int thread_num = omp_get_thread_num();
					int number_of_threads = omp_get_num_threads();
					//std::cout << "thread = " << thread_num << "\n";
					
					int first = std::floor((float)top * ((float)thread_num / (float)number_of_threads));
					int last = std::floor((float)top * ((float)(thread_num + 1) / (float)number_of_threads));

					if (std::find(history + first, history + last, *s) != history + last) {
						foundInSearchParallelHistoryGlobalFlag = true;
					}
#pragma omp barrier
					{
					}
				}
//#pragma omp single
				if (foundInSearchParallelHistoryGlobalFlag) {
					foundInSearchParallelHistoryGlobalFlag = false;
					continue;
				}
				queue.push(*s);
				history[indx++] = *s;
				indx = indx % history_size;
				top++;
				if (top > history_size)
					top = history_size;

			}
			delete successors;
			//std::cout << count << '\n';
			if (count % 1000 == 0)
				std::cout << count << '\n';

		}
		return STATE(std::make_pair(-1, -1), std::make_pair(-1, -1), std::string(""));
	}

	STATE SOKOBAN::dfs(int max_depth, const unsigned int& history_size, unsigned int& count)
	{
		STATE initial_state = this->initial_state();
		std::stack<STATE> stack;
		stack.push(initial_state);

		STATE* visited_states;
		visited_states = new STATE[history_size];
		unsigned int i = 0;
		unsigned int cap = 0;

		STATE state;
		while (!stack.empty())
		{
			//state = queue.front();
			state = stack.top();
			stack.pop();
			if (state.path.length() > max_depth)
			{
				continue;
			}
			count++;
			//std::cout << "CHECKING PATH " << count << ' ' << state.path.length() << ' ' << state.path << '\t';
			//printf("\t\t\tP(%d,% d)\tB(%d, %d)\n", state.player.first, state.player.second, state.box.first, state.box.second);

			if (is_goal(state))
			{
				delete[] visited_states;
				return state;
			}
			std::vector<STATE>* successors = successor(state);
			for (auto s = successors->begin(); s != successors->end(); s++)
			{
				if (std::find(visited_states, visited_states + cap, *s) == visited_states + cap)
				{
					// Found an unvisited state
					stack.push(*s);
					visited_states[i++] = state;
					i = i % history_size;
					cap = std::min(++cap, history_size);
				}
			}
			successors->clear();
		}

		delete[] visited_states;
		return STATE(std::make_pair(-1, -1), std::make_pair(-1, -1), std::string(""));
	}

	STATE SOKOBAN::dfs_omp(int max_depth, const unsigned int& history_size, unsigned int& count)
	{
		STATE initial_state = this->initial_state();
		std::stack<STATE> stack;
		stack.push(initial_state);

		STATE* visited_states;
		visited_states = new STATE[history_size];
		unsigned int i = 0;
		unsigned int cap = 0;
		omp_set_dynamic(0);

		omp_set_num_threads(omp_get_max_threads());

		STATE state;
		while (!stack.empty())
		{
			//state = queue.front();
			state = stack.top();
			stack.pop();
			if (state.path.length() > max_depth)
			{
				continue;
			}
			count++;
			//std::cout << "CHECKING PATH " << count << ' ' << state.path.length() << ' ' << state.path << '\t';
			//printf("\t\t\tP(%d,% d)\tB(%d, %d)\n", state.player.first, state.player.second, state.box.first, state.box.second);

			if (is_goal(state))
			{
				delete[] visited_states;
				return state;
			}
			std::vector<STATE>* successors = successor(state);
			for (auto s = successors->begin(); s != successors->end(); s++)
			{
				foundInSearchParallelHistoryGlobalFlag = false;
#pragma omp parallel
				{
					int thread_num = omp_get_thread_num();
					int number_of_threads = omp_get_num_threads();

					int first = std::floor((float)cap * ((float)thread_num / (float)number_of_threads));
					int last = std::floor((float)cap * ((float)(thread_num + 1) / (float)number_of_threads));
					
					if (std::find(visited_states + first, visited_states + last, *s) != visited_states + last) {
						foundInSearchParallelHistoryGlobalFlag = true;
					}

#pragma omp barrier
					{
					}
				}
				//#pragma omp single
				if (foundInSearchParallelHistoryGlobalFlag) {
					foundInSearchParallelHistoryGlobalFlag = false;
					continue;
				}
				stack.push(*s);
				visited_states[i++] = *s;
				i = i % history_size;
				cap = std::min(++cap, history_size);
			}
			successors->clear();
		}

		delete[] visited_states;
		return STATE(std::make_pair(-1, -1), std::make_pair(-1, -1), std::string(""));
	}

	STATE SOKOBAN::ids(const unsigned int& history_size, unsigned int& count)
	{
		idsFlag = true;
		STATE not_found = STATE(std::make_pair(-1, -1), std::make_pair(-1, -1), std::string(""));
		STATE result;
		for (int depth = 0; depth < 1000; depth++)
		{
			std::cout << "SEARCHING DEPTH " << depth << '\n';
			result = dfs(depth, history_size, count);

			std::cout << "COUNT = " << count << '\n';

			if (this->is_goal(result))
			{
				break;
			}
		}
		idsFlag = false;
		return result;
	}

	STATE SOKOBAN::ids_omp(const unsigned int& history_size, unsigned int& count)
	{
		idsFlag = true;
		STATE not_found = STATE(std::make_pair(-1, -1), std::make_pair(-1, -1), std::string(""));
		STATE result;
		for (int depth = 0; depth < 1000; depth++)
		{
			std::cout << "SEARCHING DEPTH " << depth << '\n';
			result = dfs_omp(depth, history_size, count);

			std::cout << "COUNT = " << count << '\n';

			if (this->is_goal(result))
			{
				break;
			}
		}
		idsFlag = false;
		return result;
	}
}