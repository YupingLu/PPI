# PPI
Compute the clique intersection graph and clique commonality graph on PPI and Gene Expression data

example graph: kidney.el

example maximal clqiues: kidney.clique

example clique profile: kidney.profile

mci.cpp:  output clique commonality graph

mci1.cpp: treat maximal cliques as one vertex. if # of edges between two maximal cliques is above the threshold, connect the two vertices. 

mci2.cpp: output maximal clique intersection graph. If the number of overlap vertices is above the threshold, draw a edge between two points 

#Usage
./mci graph maximal_cliques number_of_cliques threshold > plot_file

e.g.

./mci kidney.el kidney.clique 217 1 > plot.1.kidney.txt

plot.R: In this file, I use igraph to plot the generated graphs.
