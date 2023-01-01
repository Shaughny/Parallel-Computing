# Floyd-Warshall all-pairs shortest path algorithm

- Given a weighed graph G = (V, E) with n nodes, the cost of an edge from node i to j is c<sub>i,j</sub>
- Floyd’s algorithm calculates the cost d<sub>i,j</sub> of the shortest path between each pair of nodes (i,j) in V

### This repo contains two strategies for using Floyd's algorithm in parallel on a graph of with n nodes using p processors:

1.  Row and Column wise one-to-all broadcasts while computing the matrix
2.  Pipelining to replace all the one-to-all broadcasts in strategy 1
