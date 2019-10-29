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
        self.storage = (-1, -1)

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
                    self.storage = (column, row)
                    tmp.append(1)
            self.game_map.append(tmp)
    
    def is_goal(self, box):
        # box is a tuple containing the box's coordinates
        if box == self.storage:
            return True
        return False

    def successor(self, current_state):
        current_plyr_x = current_state[0][0]
        current_plyr_y = current_state[0][1]
        current_box_x = current_state[1][0]
        current_box_y = current_state[1][1]

        # Move the player and/or the box in either of the four directions available
        # Each state is a tuple of two tuples: (Player position (x, y), Box position (x, y))
        next_states = []
        for i in [-1, 1]:
            # Move along the X axis
            next_plyr_x = current_plyr_x + i
            next_plyr_y = current_plyr_y

            if self.game_map[next_plyr_y][next_plyr_x] == 1:
                if (current_box_x == next_plyr_x and current_box_y == next_plyr_y):
                    if self.game_map[current_box_y][current_box_x + i] == 1:
                        # Move is valid
                        next_states.append(((next_plyr_x, next_plyr_y), (current_box_x + i, current_box_y)))
                else:
                    next_states.append(((next_plyr_x, next_plyr_y), (current_box_x, current_box_y)))
            
            # Move along the Y axis
            next_plyr_x = current_plyr_x
            next_plyr_y = current_plyr_y + i

            if self.game_map[next_plyr_y][next_plyr_x] == 1:
                if (current_box_x == next_plyr_x and current_box_y == next_plyr_y):
                    if self.game_map[current_box_y + i][current_box_x] == 1:
                        # Move is valid
                        next_states.append(((next_plyr_x, next_plyr_y), (current_box_x, current_box_y + i)))
                else:
                    next_states.append(((next_plyr_x, next_plyr_y), (current_box_x, current_box_y)))

        return next_states

    def test(self):
        return self.storage
    
    def initial_state(self):
        return (self.player, self.box)
    
    def bfs(self):
        init_state = self.initial_state()
        queue = []
        queue.insert(0, init_state)
        while len(queue) != 0:
            state = queue.pop()
            if self.is_goal(state[1]):
                return state
            next_steps = self.successor(state)
            for x in next_steps:
                queue.insert(0, x)

        # no goal was found
        return ((-1, -1), (-1, -1))

    def bfs_with_path(self):
        init_state = self.initial_state()
        queue = []
        queue.insert(0, [init_state])
        while len(queue) != 0:
            path = queue.pop()
            state = path[-1]
            if self.is_goal(state[1]):
                return path
            next_steps = self.successor(state)
            for x in next_steps:
                new_path = list(path)
                new_path.append(x)
                queue.insert(0, new_path)

        # no goal was found
        return ((-1, -1), (-1, -1))
