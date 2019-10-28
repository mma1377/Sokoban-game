#include "sokobanCore.h"
#include <iostream>

namespace sokobanCore {
	SOKOBAN::SOKOBAN(const char* input_file)
	{
		std::cout << "1\n";

		std::ifstream infile(input_file);

		std::cout << "2\n";
		if (!infile.is_open())
		{
			std::cout << "Input not found\n";
			exit(0);
		}
		std::cout << "3\n";

		infile >> n >> m;
		//n = 13;
		//m = 24;
		std::cout << n << ' ' << m << '\n';
		game_map = new bool* [n];

		for (short row = 0; row < n; row++)
		{
			bool* tmp;
			tmp = new bool[m];
			std::string line;
			infile >> line;
			for (short col = 0; col < m; col++)
			{
				if (line[col] == '#')
					tmp[col] = 0;
				else if (line[col] == '.')
					tmp[col] = 1;
				else if (line[col] == 'S')
				{
					tmp[col] = 1;
					player = std::make_pair(col, row);
				}
				else if (line[col] == '@')
				{
					tmp[col] = 1;
					box = std::make_pair(col, row);
				}
				else if (line[col] == 'X')
				{
					tmp[col] = 1;
					storage = std::make_pair(col, row);
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

	bool SOKOBAN::is_goal(STATE state)
	{
		if (state.second == this->storage)
		{
			return true;
		}
		return false;
	}

	std::vector<STATE>* SOKOBAN::successor(STATE current_state)
	{
		std::vector<STATE>* next_states;
		next_states = new std::vector<STATE>;
		for (short i = -1; i < 2; i += 2)
		{
			// Move player one step to the left/right
			short next_plyr_x = current_state.first.first + i;
			short next_plyr_y = current_state.first.second;

			// Check if the move is valid
			if (game_map[next_plyr_y][next_plyr_x] == 1)
			{
				// Check if the player is moving into the box
				if (current_state.second.first == next_plyr_x && current_state.second.second == next_plyr_y)
				{
					short next_box_x = current_state.second.first + i;
					short next_box_y = current_state.second.second;
					// Check if the box is movable in this direction
					if (game_map[next_box_y][next_box_x] == 1)
					{
						auto pair = std::make_pair(
							std::make_pair(next_plyr_x, next_plyr_y),
							std::make_pair(next_box_x, next_box_y));
						next_states->push_back(pair);
					}
				}
				else
				{
					next_states->push_back(std::make_pair(
						std::make_pair(next_plyr_x, next_plyr_y),
						std::make_pair(current_state.second.first, current_state.second.second)));
				}
			}

			// Move player one step upward/downward
			next_plyr_x = current_state.first.first;
			next_plyr_y = current_state.first.second + i;

			// Check if the move is valid
			if (game_map[next_plyr_y][next_plyr_x] == 1)
			{
				// Check if the player is moving into the box
				if (current_state.second.first == next_plyr_x && current_state.second.second == next_plyr_y)
				{
					short next_box_x = current_state.second.first;
					short next_box_y = current_state.second.second + i;
					// Check if the box is movable in this direction
					if (game_map[next_box_y][next_box_x] == 1)
					{
						next_states->push_back(std::make_pair(
							std::make_pair(next_plyr_x, next_plyr_y),
							std::make_pair(next_box_x, next_box_y)));
					}
				}
				else
				{
					next_states->push_back(std::make_pair(
						std::make_pair(next_plyr_x, next_plyr_y),
						std::make_pair(current_state.second.first, current_state.second.second)));
				}

			}
		}

		return next_states;
	}

	STATE SOKOBAN::bfs()
	{
		STATE initial_state = std::make_pair(player, box);
		std::queue<STATE> queue;
		queue.push(initial_state);

		// long long int history_size = this->n * this->n * this->m * this->m;
		// STATE* visited_states;
		// visited_states = new STATE[history_size];
		// long long int i = 0;
		// long long int cap = 0;
		std::vector<STATE> history;
		int history_size = 50000;
		history.resize(history_size);
		int count = 0;
		while (!queue.empty())
		{
			count++;
			STATE state = queue.front();
			//history.insert(state);
			history[count % history_size] = state;
			// visited_states[i++] = state;
			// i = i % history_size;
			// cap = std::min(++cap, history_size);
			queue.pop();
			if (is_goal(state))
			{
				std::cout << "COUNT: " << count << '\n';
				std::cout << "Vector size: " << history.size() << '\n';
				return state;
			}
			std::vector<STATE>* successors = successor(state);
			for (auto s = successors->begin(); s != successors->end(); s++)
			{
				bool flag = true;
				if (std::find(history.begin(), history.end(), *s) != history.end())
				{
					continue;
				}
				else
				{
					queue.push(*s);
				}
			}
			delete successors;
			if (count % 5000 == 0)
				std::cout << count << '\n';

		}
		return std::make_pair(std::make_pair(-1, -1), std::make_pair(-1, -1));
	}
}