# graphs-challenge-c
Algorithm to solve a school assignment using C programming language

## What is it?
A PERT network is a form of respresenting the tasks in a project with its respective flow and time,
and the critical path of this graph would be the longest path (the one that would take more time)
from a PERT network the challenge is to find the critical path and all the tasks that, if we reduce the time, would lead to a different critical path for the same graph

## How it works?
It begins loading a 'grafo.txt' file that contains the graph information as conections between vertices like the following:

A, B, 10

B, C, 5

...

where the first character is the initial state of the task, the second character is the final state of the task, and the number represents the time that takes to execute the task.
from this file the program can build the graph and run an adapted dijkstra's algorithm to find the critical path.
After finding the critical path it check all the tasks in the path from the end to the beginning to see if there's another path that have a longer path than the (current path - the current task), if there is it presents the formated message showing the task that shoul be reduced and the new critical path.

## Try it yourself
To run this code in your machine you should have any C compiler
Clone this repository and simply compile the three .c files in it into the same binary.
"clang main.c grafo.c arestas.c -o app && ./app"

### Attention!
!!! The program will load the "grafo.txt" file in the same folder, if you want you can create other graphs in this file to test other situations.

!!! The graph in the file should NOT have more than 1 origin and end nodes.

!!! The graph in the file should NOT have any cicles in it.
