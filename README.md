# PPI
Compute the clique intersection graph and clique commonality graph on PPI and Gene Expression data

example graph: 
example maximal clqiues:
example clique profile: 

mci.cpp:  output clique commonality graph

mci1.cpp: treat maximal cliques as one vertex. if # of edges between two maximal cliques is above the threshold, connect the two vertices. 

mci2.cpp: output maximal clique intersection graph. If the number of overlap vertices is above the threshold, draw a edge between two points 

#Usage
./mci

plot.R: In this file, I use igraph to plot the generated graphs.
