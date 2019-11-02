#include <sokoban.h>


int main()
{

    auto skb = SOKOBAN("Soko2.txt");

    //STATE st;

    // Print map test
    skb.print_map();

    // Goal check test
    // st = std::make_pair(std::make_pair(7, 2), std::make_pair(8, 1));
    // std::cout << skb.is_goal(st) << '\n';

    // Successor test
    // st = std::make_pair(std::make_pair(7, 2), std::make_pair(6, 2));
    // std::vector<STATE> next_vec = skb.successor(st);
    // for (auto it = next_vec.begin(); it != next_vec.end(); it++)
    // {
    //     STATE temp = *it;
    //     std::cout << temp.first.first << ' ' << temp.first.second << '\t' << temp.second.first << ' ' << temp.second.second << '\n';
    // }

    // BFS test
    std::cout << "Now lest do some BFS...\n";
     STATE bfs_res = skb.bfs();
     std::cout << bfs_res.first.first << ' ' << bfs_res.first.second << '\t' << bfs_res.second.first << ' ' << bfs_res.second.second << '\n';
    
}