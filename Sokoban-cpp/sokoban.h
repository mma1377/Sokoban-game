/*
This file contains the program that receives an initial state
of the Sokoban game, produces successors for each state and yields
the final result. It uses uninformed searching algorithms to search
for the answer in the search space.
*/

#include <fstream>
#include <vector>
#include <queue>
#include <iostream>
#include <stdlib.h>

// TODO: Find a better way to rename this:
#define PAIR(T1, T2) std::pair<T1, T2>
#define INTPAIR PAIR(short, short)
#define STATE PAIR(INTPAIR, INTPAIR)


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

        // Destructor function for SOKOBAN class
        ~SOKOBAN();

        // Prints out the game's current map layout
        void print_map();

        // Returns true if the current state is a final state
        // Arguments: any STATE
        bool is_goal(STATE);

        // Returns all possible next moves in the game
        // TODO: Pass by reference
        std::vector<STATE> successor(STATE);

        // Searches for the goal using breadth-first search algorithm
        STATE bfs();
};


SOKOBAN::SOKOBAN(const char* input_file)
{
    std::ifstream infile(input_file);
    
    infile >> n >> m;
    game_map = new bool*[n];
    for (int row = 0; row < n; row++)
    {
        bool* tmp;
        tmp = new bool[m];
        char* line;
        infile >> line;
        for (int col = 0; col < m; col++)
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
                box = std::make_pair(col, row);
            }
            else if (line[col] == 'X')
            {
                tmp[col] = 1;
                storage = std::make_pair(col, row);
            }
        }
        game_map[row] = tmp;
    }
};

void SOKOBAN::print_map()
{
    for (short row = 0; row < n; row++)
    {
        for (short col = 0; col < m; col++)
        {
            std::cout << game_map[row][col];
        }
        std::cout << '\n';
    }
}

SOKOBAN::~SOKOBAN()
{
    for (short i = 0; i < n; i++)
    {
        delete game_map[i];
    }
    delete game_map;
}


bool SOKOBAN::is_goal(STATE state)
{
    if (state.second == this->storage)
    {
        return true;
    }
    return false;
}

std::vector<STATE> SOKOBAN::successor(STATE current_state)
{
    std::vector<STATE> next_states;
    for (int i = -1; i < 2; i += 2)
    {
        // Move player one step to the left/right
        short next_plyr_x = current_state.first.first + i;
        short next_plyr_y = current_state.first.second;

        // Check if the move is valid
        if (game_map[next_plyr_y][next_plyr_y] == 1)
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
                    next_states.push_back(pair);
                }
            }
            else
            {
                next_states.push_back(std::make_pair(
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
                    next_states.push_back(std::make_pair(
                                    std::make_pair(next_plyr_x, next_plyr_y), 
                                    std::make_pair(next_box_x, next_box_y)));
                }
            }
            else
            {
                next_states.push_back(std::make_pair(
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

    while (!queue.empty())
    {
        STATE state = queue.back();
        queue.pop();
        if (is_goal(state))
        {
            return state;
        }
        std::vector<STATE> successors = successor(state);
        for (auto s = successors.begin(); s != successors.end(); s++)
            queue.push(*s);
    }

    return std::make_pair(std::make_pair(-1, -1), std::make_pair(-1, -1));
}