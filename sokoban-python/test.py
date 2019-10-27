import sokoban


def main():
    testfile_dir = "C:/Users/InVaderrr/Documents/repos/Sokoban-game/sokoban-python/Soko1.txt"
    var = sokoban.SOKOBAN(testfile_dir)
    var.current_state()
    var.successor()


main()