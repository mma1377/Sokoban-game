# Sokoban Puzzle Solver GUI #
	IASBS Artificial Intelligence I (981)
	Assignment 1
	Fall 2019
	Mohammadmahdi Alijani (964413)
	Alireza Nadirkhanlou (964407)

This project solves Sokoban puzzles using basic A.I. search algorithms (both uninformed and informed). The project is still in development, and as of now, you can only use uninformed algorithms to solve your puzzles.

The core layer of this solver is written in C++.

___

## Search Algorithms ##
- __Uninformed__
	- __Breadth-first search (BFS)__
	- __Depth-first search (DFS)__
	- __Iterative deepening depth-first search (IDS or IDDFS)__

## State History ##
In order to avoid producing too many repititious states, we store the N most recent _checked_ states in a _state_history_ buffer. Bigger N values helps the algorithm to reach an answer with checking fewer states, but will also slow it down because for every produced state, it has to compare it to N previously checked states.

### State History Search Optimization Using Multi-threaded Searching ###
Searching this buffer could be quite a bottleneck for the algorithm, so for each algorithm, we implemented a duplicate with Multi-threaded searching using the OpenMP library, which noticably speeds up the whole process. You need to enable OpenMP support for your porject to be able to use these algorithms.

## Instructions ##

### Input ###
Your input must be in the following format:
<pre>
#	Wall
.	Floor
S	Player
@	Box
X	Goal 
</pre>
Note that the four sides of the game map must be surrounded with walls (reduced code complexity)
Example:
<pre>
############
######..X###
#S....@@..##
#####..X####
############ 
</pre>

(We are aware this format is not the standard format of this puzzle, but our assignment had this format as a standard, and after presenting the project, we will switch to the standard format!)

### Running the program ###
After sorting out your input, you can easily choose the path to your input, and after loading it, choose the algorithm you want to solve the puzzle with. In the console window, you can see how many states were checked (COUNT) in order to find the answer.

Here you can also set your _State History_ buffer size!

### Output ###
After solving the puzzle, you will see Mr. Sokoban (!) start to move the boxes into the goal spots. In the console window, you will see a string of steps consisting of L's, R's, D's and U's denoting the path to solve the puzzle!

## Screenshots ##
Coming soon...
