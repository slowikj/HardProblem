# HardProblem
The solution to [a codeforces's algorithmic task](http://codeforces.com/problemset/problem/706/C) (dynamic programming)

Task
----

We are given a sequence of strings and for each string there is a cost
connected with reversing it. 
The aim of the task is to compute the minimum cost of such reversing strings
that the obtained sequence of strings will be lexicographically sorted.

Example
----
Input
```
3
1 3 1
aa
ba
ac
```

Output:
```
1
```
because we can reverse only the third string and then
we get the following sorted sequence of strings:
```
aa
ba
ca
```
