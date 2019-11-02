// #include <sokoban-cpp\sokoban.h>
// #include <C:\Users\InVaderrr\Documents\repos\Sokoban-game\sokoban-cpp\sokoban.h>


// SOKOBAN::SOKOBAN(const char* input_file)
//         {
//             std::ifstream infile(input_file);
            
//             infile >> n >> m;

//             for (int row = 0; row < n; row++)
//             {
//                 bool* tmp = new bool(m);
//                 char* line;
//                 infile >> line;
//                 for (int col = 0; col < m; col++)
//                 {
//                     if (line[col] == '#')
//                         tmp[col] = 0;
//                     else if (line[col] == '.')
//                         tmp[col] = 1;
//                     else if (line[col] == 'S')
//                     {
//                         tmp[col] = 1;
//                         player = std::make_pair(col, row);
//                     }
//                     else if (line[col] == '@')
//                     {
//                         tmp[col] = 1;
//                         box = std::make_pair(col, row);
//                     }
//                     else if (line[col] == 'X')
//                     {
//                         tmp[col] = 1;
//                         storage = std::make_pair(col, row);
//                     }
//                 }
//                 game_map[row] = tmp;
//             }
//         };

// bool SOKOBAN::is_goal(STATE state)
// {
//     if (state.second == this->storage)
//         return true;
//     return false;
// }

// std::vector<STATE> SOKOBAN::successor(STATE current_state)
// {
//     std::vector<STATE> next_states;
//     for (int i = -1; i < 2; i += 2)
//     {
//         // Move player one step to the left/right
//         unsigned char next_plyr_x = current_state.first.first + i;
//         unsigned char next_plyr_y = current_state.first.second;

//         // Check if the move is valid
//         if (game_map[next_plyr_y][next_plyr_y] == 1)
//         {
//             // Check if the player is moving into the box
//             if (current_state.second.first == next_plyr_x && current_state.second.second == next_plyr_y)
//             {
//                 unsigned char next_box_x = current_state.second.first + i;
//                 unsigned char next_box_y = current_state.second.second;
//                 // Check if the box is movable in this direction
//                 if (game_map[next_box_y][next_box_x] == 1)
//                     next_states.push_back(std::make_pair(
//                                     std::make_pair(next_plyr_x, next_plyr_y), 
//                                     std::make_pair(next_box_x, next_box_y)));
//             }
//             else
//             {
//                 next_states.push_back(std::make_pair(
//                                 std::make_pair(next_plyr_x, next_plyr_y), 
//                                 std::make_pair(current_state.second.first, current_state.second.second)));
//             }
//         }

//         // Move player one step upward/downward
//         next_plyr_x = current_state.first.first;
//         next_plyr_y = current_state.first.second + i;

//         // Check if the move is valid
//         if (game_map[next_plyr_y][next_plyr_y] == 1)
//         {
//             // Check if the player is moving into the box
//             if (current_state.second.first == next_plyr_x && current_state.second.second == next_plyr_y)
//             {
//                 unsigned char next_box_x = current_state.second.first;
//                 unsigned char next_box_y = current_state.second.second + i;
//                 // Check if the box is movable in this direction
//                 if (game_map[next_box_y][next_box_x] == 1)
//                     next_states.push_back(std::make_pair(
//                                     std::make_pair(next_plyr_x, next_plyr_y), 
//                                     std::make_pair(next_box_x, next_box_y)));
//             }
//             else
//             {
//                 next_states.push_back(std::make_pair(
//                                 std::make_pair(next_plyr_x, next_plyr_y), 
//                                 std::make_pair(current_state.second.first, current_state.second.second)));
//             }
            
//         }
//     }

//     return next_states;
// }

// STATE SOKOBAN::bfs()
// {
//     STATE initial_state = std::make_pair(player, box);
//     std::queue<STATE> queue;
//     queue.push(initial_state);

//     while (!queue.empty())
//     {
//         STATE state = queue.back();
//         queue.pop();
//         if (is_goal(state))
//             return state;
//         std::vector<STATE> successors = successor(state);
//         for (auto s = successors.begin(); s != successors.end(); s++)
//             queue.push(*s);
//     }

//     return std::make_pair(std::make_pair(-1, -1), std::make_pair(-1, -1));
// }