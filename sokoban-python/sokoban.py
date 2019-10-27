"""
This file contains the program that receives an initial state
of the Sokoban game, produces successors for each state and yields
the final result. It uses uninformed searching algorithms to search
for the answer in the search space.
"""

class SOKOBAN:
    def __init__(self, input_file):

        file = open(input_file, 'r')

        n, m = [eval(x) for x in file.readline().split()]

        self.game_map = []
        self.player = (-1, -1)
        self.box = (-1, -1)
        self.spot = (-1, -1)

        for row in range(n):
            tmp = []
            line = file.readline()
            for column in range(m):
                if line[column] == '#':
                    tmp.append(0)
                if line[column] == '.':
                    tmp.append(1)
                if line[column] == 'S':
                    self.player = (column, row)
                    tmp.append(1)
                if line[column] == '@':
                    self.box = (column, row)
                    tmp.append(1)
                if line[column] == 'X':
                    self.spot = (column, row)
                    tmp.append(1)
            self.game_map.append(tmp)
    
    def test(self):
        return self.spot
    
    def test2(self):
        print("Do something")
