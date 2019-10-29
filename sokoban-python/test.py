import sokoban

def main():
    testfile_dir = "C:/Users/InVaderrr/Documents/repos/Sokoban-game/sokoban-python/Soko2.txt"
    var = sokoban.SOKOBAN(testfile_dir)
    var.initial_state()
    #final_state_path = var.bfs_with_path()
    #print(final_state_path)
    final_state = var.bfs()
    print(final_state)
main()