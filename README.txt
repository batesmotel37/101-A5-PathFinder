README
Student name: Kenneth High
username: khigh
hostname: unix_.lt.ucsc.edu

This program takes an input graph (which contains a set of points and "edges", which connect various points together) and maps a quickest (defined as the path where we traverse the fewest number of edges) path possible to get to a given point from all other points.

FindComponents.c
   *A program which uses calls on DFS method of Graph.c and prints its results, along with a adjacency list form of the graph searched to an output file. the Graph is received via an input file.*

List.h
   *The header file which lets Graph.c use methods from List.c*

List.c
   *A List ADT, reused from pa2, These Lists hold the adjecent verticies of a given vertex*

Graph.h
   *The header file which lets FindPath.c and GraphTest.c use methods from Graph.c*

Graph.c
   *A Graph ADT which stores a graph in the form of an adjacency list (an array of Lists) each list holds all verticies adjacent to a single given vertex*

GraphTest.c
   *A test Client which runs all functions from Graph.c in order to show that they run without error*

Makefile
   *uses "make" to compile/recompile the .c files in the FindPath project
Creates executable "FindComponents"
"make submit" copies all files from the project to the submit directory for grading*

README
   *This file
a table of contents for the pa5 project*
