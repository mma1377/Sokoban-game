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
    
    def is_goal(self):
        if self.box == self.spot:
            return True
        return False

    def successor(self):
        player_x = self.player[0]
        player_y = self.player[1]
        box_x = self.box[0]
        box_y = self.box[1]

        # Move the player and/or the box in either of the four directions available
        # Each state is a tuple of two tuples: (Player position (x, y), Box position (x, y))
        next_states = []
        for i in [-1, 1]:
            # Move along the X axis
            next_plyr_x = player_x + i
            next_plyr_y = player_y

            if self.game_map[next_plyr_y][next_plyr_x] == 1:
                if (box_x == next_plyr_x and box_y == next_plyr_y):
                    if self.game_map[box_y][box_x + i] == 1:
                        # Move is valid
                        next_states.append(((next_plyr_x, next_plyr_y), (box_x + i, box_y)))
                else:
                    next_states.append(((next_plyr_x, next_plyr_y), (box_x, box_y)))
            
            # Move along the Y axis
            next_plyr_x = player_x
            next_plyr_y = player_y + i

            if self.game_map[next_plyr_y][next_plyr_x] == 1:
                if (box_x == next_plyr_x and box_y == next_plyr_y):
                    if self.game_map[box_y + i][box_x] == 1:
                        # Move is valid
                        next_states.append(((next_plyr_x, next_plyr_y), (box_x, box_y + i)))
                else:
                    next_states.append(((next_plyr_x, next_plyr_y), (box_x, box_y)))
        
        print("SUCCESSORS:")
        for x in next_states:
            print(x)
        return next_states

    def test(self):
        return self.spot
    
    def current_state(self):
        print("Player:", self.player)
        print("Box:", self.box)