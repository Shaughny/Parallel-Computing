# Parallel Quicksort on a hypercube topology

- ### Distributed parallel quicksort algorithm for a n-dimensional hypercube where the number of processors is equal to p=2<sup>n</sup>
![alt text](https://media.geeksforgeeks.org/wp-content/uploads/20200505193417/Untitled-Diagram-524.png)
- ### Processors A and B are connected if and only if their unique log<sub>2</sub> n-bit strings differ in exactly one position
![alt text](https://research.cs.vt.edu/AVresearch/MPI/MPIVizHelp_files/image002.jpg)

## Parallel quicksort strategy:

1.  data is distributed among processors
2.  broadcast pivot to each processor
3.  each processor creates 2 lists based on being lower/higher than the pivot
4.  using the n-bit strings for each processor, we send higher or lower list to that processors neighbors based on their position in the hierarchy
5. once all sub-lists are organized and distributed, each processor performs sequential quicksort on their fragment
6. processor 0 gathers all the sub-lists into the final result
