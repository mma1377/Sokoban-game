#include "sokobanCore.h"
#include <iostream>
#include <omp.h>
//#define _SECURE_SCL 0

namespace sokobanCore {

	bool foundInSearchParallelHistoryGlobalFlag = false;

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
		std::vector<INTPAIR> temp_boxes;
		std::vector<INTPAIR> temp_storages;
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
				}
				else if (line[col] == 'S')
				{
					tmp[col] = 1;
					player = std::make_pair(col, row);
				}
				else if (line[col] == '@')
				{
					tmp[col] = 1;
					temp_boxes.push_back(std::make_pair(col, row));
				}
				else if (line[col] == 'X')
				{
					tmp[col] = 1;
					temp_storages.push_back(std::make_pair(col, row));
				}
				game_map[row] = tmp;
			}
		}
		if (temp_boxes.size() != temp_storages.size())
		{
			std::cerr << "INVALID INPUT\n";
			exit(0);
		}
		this->num_boxes = temp_boxes.size();
		box = new INTPAIR[this->num_boxes];
		storage = new INTPAIR[this->num_boxes];
		for (int i = 0; i < this->num_boxes; i++)
		{
			box[i] = temp_boxes[i];
			storage[i] = temp_storages[i];
		}
	};

	SOKOBAN::~SOKOBAN()
	{
		for (short i = 0; i < n; i++)
		{
			delete this->game_map[i];
		}
		delete this->game_map;
		delete this->box;
		delete this->storage;
	}

	void SOKOBAN::print_map()
	{
		for (short i = 0; i < n; i++)
		{
			for (short j = 0; j < m; j++)
			{
				std::cout << this->game_map[i][j];
			}
			std::cout << '\n';
		}
	}

	STATE SOKOBAN::initial_state()
	{
		STATE t(this->player, num_boxes, "");
		for (int i = 0; i < this->num_boxes; i++)
		{
			t.box[i] = this->box[i];
		}
		return t;
	}

	bool SOKOBAN::is_goal(STATE state)
	{
		for (int i = 0; i < this->num_boxes; i++)
		{
			if (std::find(storage, storage + this->num_boxes, state.box[i]) == storage + this->num_boxes)
			{
				return false;
			}
		}
		return true;
	}

	std::vector<STATE>* SOKOBAN::successor(STATE current_state)
	{
		/*STATE current_state;
		current_state.player = current_state2.player;
		current_state.num_boxes = current_state2.num_boxes;
		current_state.path = current_state2.path;
		current_state.box = new INTPAIR[current_state.num_boxes];
		for (int i = 0; i < current_state.num_boxes; i++)
			current_state.box[i] = current_state2.box[i];*/
		std::vector<STATE>* next_states;
		next_states = new std::vector<STATE>;

		short plyr_x = current_state.player.first;
		short plyr_y = current_state.player.second;
		short num_boxes = current_state.num_boxes;

		// Move player one step to the left
		// Check if the move is valid
		if (game_map[plyr_y][plyr_x - 1])
		{
			// Check if the player is moving into any box
			bool hit_box = false;
			short i;
			for (i = 0; i < num_boxes; i++)
			{
				if ((plyr_x - 1 == current_state.box[i].first) && (plyr_y == current_state.box[i].second))
				{
					hit_box = true;
					break;
				}
			}
			if (hit_box)
			{
				// Check whether the box can move too
				// First, we must check wether there is a wall in its way
				if (game_map[current_state.box[i].second][current_state.box[i].first - 1])
				{
					// Now we must see whether there is another box in this box's way
					bool flag = false;
					for (int j = 0; j < num_boxes; j++)
					{
						if (j != i)
						{
							if ((current_state.box[i].first - 1 == current_state.box[j].first) &&
								(current_state.box[i].second == current_state.box[j].second))
							{
								flag = true;
								break;
							}
						}
					}
					if (!flag)
					{
						STATE temp = current_state;
						temp.player.first = plyr_x - 1;
						temp.box[i].first = temp.box[i].first - 1;
						temp.path += "L";
						next_states->push_back(temp);
					}
				}
			}
			else
			{
				STATE temp = current_state;
				temp.player.first = plyr_x - 1;
				temp.path += "L";
				next_states->push_back(temp);
			}
		}

		// Move player one step to the right
		// Check if the move is valid
		if (game_map[plyr_y][plyr_x + 1])
		{
			// Check if the player is moving into any box
			bool hit_box = false;
			short i;
			for (i = 0; i < num_boxes; i++)
			{
				if ((plyr_x + 1 == current_state.box[i].first) && (plyr_y == current_state.box[i].second))
				{
					hit_box = true;
					break;
				}
			}
			if (hit_box)
			{
				// Check whether the box can move too
				// First, we must check wether there is a wall in its way
				if (game_map[current_state.box[i].second][current_state.box[i].first + 1])
				{
					// Now we must see whether there is another box in this box's way
					bool flag = false;
					for (int j = 0; j < num_boxes; j++)
					{
						if (j != i)
						{
							if ((current_state.box[i].first + 1 == current_state.box[j].first) &&
								(current_state.box[i].second == current_state.box[j].second))
							{
								flag = true;
							}
						}
					}
					if (!flag)
					{
						STATE temp = current_state;
						temp.player.first = plyr_x + 1;
						temp.box[i].first = temp.box[i].first + 1;
						temp.path += "R";
						next_states->push_back(temp);
					}
				}
			}
			else
			{
				STATE temp = current_state;
				temp.player.first = plyr_x + 1;
				temp.path += "R";
				next_states->push_back(temp);
			}
		}

		// Move player one step upward
		// Check if the move is valid
		if (game_map[plyr_y - 1][plyr_x])
		{
			// Check if the player is moving into any box
			bool hit_box = false;
			short i;
			for (i = 0; i < num_boxes; i++)
			{
				if ((plyr_x == current_state.box[i].first) && (plyr_y - 1 == current_state.box[i].second))
				{
					hit_box = true;
					break;
				}
			}
			if (hit_box)
			{
				// Check whether the box can move too
				// First, we must check wether there is a wall in its way
				if (game_map[current_state.box[i].second - 1][current_state.box[i].first])
				{
					// Now we must see whether there is another box in this box's way
					bool flag = false;
					for (int j = 0; j < num_boxes; j++)
					{
						if (j != i)
						{
							if ((current_state.box[i].first == current_state.box[j].first) &&
								(current_state.box[i].second - 1 == current_state.box[j].second))
							{
								flag = true;
								break;
							}
						}
					}
					if (!flag)
					{
						STATE temp = current_state;
						temp.player.second = plyr_y - 1;
						temp.box[i].second = temp.box[i].second - 1;
						temp.path += "U";
						next_states->push_back(temp);

					}
				}
			}
			else
			{
				STATE temp = current_state;
				temp.player.second = plyr_y - 1;
				temp.path += "U";
				next_states->push_back(temp);
			}
		}

		// Move player one step downward
		// Check if the move is valid
		if (game_map[plyr_y + 1][plyr_x])
		{
			// Check if the player is moving into any box
			bool hit_box = false;
			short i;
			for (i = 0; i < num_boxes; i++)
			{
				if ((plyr_x == current_state.box[i].first) && (plyr_y + 1 == current_state.box[i].second))
				{
					hit_box = true;
					break;
				}
			}
			if (hit_box)
			{
				// Check whether the box can move too
				// First, we must check wether there is a wall in its way
				if (game_map[current_state.box[i].second + 1][current_state.box[i].first])
				{
					// Now we must see whether there is another box in this box's way
					bool flag = false;
					for (int j = 0; j < num_boxes; j++)
					{
						if (j != i)
						{
							if ((current_state.box[i].first == current_state.box[j].first) &&
								(current_state.box[i].second + 1 == current_state.box[j].second))
							{
								flag = true;
								break;
							}
						}
					}
					if (!flag)
					{
						STATE temp = current_state;
						temp.player.second = plyr_y + 1;
						temp.box[i].second = temp.box[i].second + 1;
						temp.path += "D";
						next_states->push_back(temp);
					}
				}
			}
			else
			{
				STATE temp = current_state;
				temp.player.second = plyr_y + 1;
				temp.path += "D";
				next_states->push_back(temp);
			}
		}

		return next_states;
	}

	STATE SOKOBAN::bfs(const unsigned int& history_size, unsigned int& count)
	{
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
			//if (count % 1000 == 0)
			//	std::cout << count << '\n';
		}

		delete[] visited_states;
		return STATE(std::make_pair(-1, -1), 0, std::string(""));
	}

	STATE SOKOBAN::bfs_omp(const unsigned int& history_size, unsigned int& count)
	{
		STATE initial_state = this->initial_state();
		std::queue<STATE> queue;
		queue.push(initial_state);

		unsigned int i = 0;
		unsigned int cap = 0;

		STATE* visited_states = new STATE[history_size];
		
		//int count = 0;
		while (!queue.empty())
		{
			count++;
			STATE state = queue.front();
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
				queue.push(*s);
				visited_states[i++] = *s;
				i = i % history_size;
				cap = std::min(++cap, history_size);

			}
			successors->clear();
			//std::cout << count << '\n';
			if (count % 1000 == 0)
				std::cout << count << '\n';

		}
		delete[] visited_states;

		return STATE(std::make_pair(-1, -1), 0, std::string(""));
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
		return STATE(std::make_pair(-1, -1), 0, std::string(""));
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
		return STATE(std::make_pair(-1, -1), 0, std::string(""));
	}

	STATE SOKOBAN::ids(const unsigned int& history_size, unsigned int& count)
	{
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
		return result;
	}

	STATE SOKOBAN::ids_omp(const unsigned int& history_size, unsigned int& count)
	{
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
		return result;
	}
}