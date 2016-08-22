# Algorithms-Butler
Some of the algorithms from my class at Butler University.

These algorithms are for the 0-1 Knapsack problem.

Algorithms Used:
* Dynamic Programming (Knapsack-Dynamic-Simple, Knapsack-Dynamic-Refined)
* Backtracking (Knapsack-Backtrack)
* Branch and Bound w/ Priority Queue (Knapsack-Branch-Bound)

Given n items with a weight and value, put these items into a knapsack with a maximum weight capacity in order to receive a maximum total value while staying below or at the capacity.

Example input:

```
5 6        -- 5 items and the knapsack has a weight capacity of 6
1 20 2     -- Item 1 has a value of 20 and a weight of 2
2 25 5
3 15 1
4 15 3
5 10 1
```
Example output:
```
4 15 3
3 15 1
1 20 2
Total Value: 50
Total Weight: 6
```
Putting items 4,3, and 1 into the knapsack is the optimal solution. We get the most profit while not going over the capacity of 6.
