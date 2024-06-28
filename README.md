## Random Walk 
This program is an implementation of a 2d uniform random walk using the linear congruent pseudo RNG. It is part of exercise 5.4 of the compuational physics textbook by Landau (2015)[^1] that aims to introduce Monte Carlo methods.

## Pseudorandom Number Generator
The program uses the linear congruent method to generate random numbers. The algorithm to get the random number is:
$$r_{i+1} = (ar_i+c)\ \text{mod}\ M$$
and $r_0$ is the initial seed. The parameters used are $a=214013$ $c=2531011$ $M=2^{31}$ which i got from the wikipedia for linear congruential generator under the entry for Microsoft Visual/Quick C/C++. I use the machine time for the initial seed but for generating multiple random numbers, I add some large constant to the machine time for different seeds. 

## Random Walk
The random walk takes 2 random numbers initialized with different seeds for its X axis and Y axis. The random numbers are then normalized by its length so that the resulting vector has a length of 1.
![gif](media/random_walk.gif)

[^1]: Landau, R. H. (2015). Computational physics problem solving with python. John Wiley & Sons, Incorporated.