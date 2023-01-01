# # $\pi$ approximation algorithm using the master-worker paradigm and Monte Carlo method

## Parallel $\pi$ approximation strategy:

1.  data is distributed among processors
2.  each processor has a dartboard with radius r that is inside a square with length 2r
3.  randomly generate N darts inside the square and approximately N * $\pi$ / 4 of those darts should land inside the board
4.  each processor performs the dart calculations
5.  processor 0 then approximates $\pi$ after gathering the data from each processor
