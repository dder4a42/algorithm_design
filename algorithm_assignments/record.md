# Record of problems

## 1295

+ 需要获得≤n的素数个数
+ 似乎提示使用random，如Miller Rabin检测？
+ notice that probability is quite small when n is large, especially << 1e-5. Then even guess p=0 is enough.

## 1301

逆序对问题，不过需要对每个数字记录其关联的对数。

## 1982

若现有最小周长为$d$，则新的最小三角形必须满足最长边$\le \frac{d}{2}$（考虑退化的三角形），则任意两点间的$|x_1 - x_2|<d/2$且$|y_1 - y_2| < d/2$。又，满足这些条件的点不会太密集地分布在$d/2$的方格中，于是可使用最近点对的框架。

## 2466

simulate DFS step by step. can't use BFS, because we can operate at most 2n step, and every vertex can be visited once at forward step and once at back forward step. we must return to parent manually, a pre[] array is needed.

## 1344

the length of a negative cycle is negative. if we go through this loop, the total weights of edges are negative. 
record $v.\pi$ for every vertex to trace which edge and which vertex the update is from. 

## 1428

use union-find set to detect cycle. 

## 2535

greedy algorithm fails. $\max(L_n-\max(L_{n+1}, R_{n+1}), R_n-\max(L_{n+1}, R_{n+1}))$, $L_n$ means the player choose $L$ in n-th round. 

It has finite states. totally $2^{n-1}$ states for making $2^{n-1}$ decisions. maybe we can define state $(i, j)$ as the max gain a player can get from Array[i:j]. 

Define $f(i,j)$ as the max gain a player can get from $array[i:j]$ if another player always take optimal choice. Record the optimal choice at the same time. 

## 1429

Since $1n<x$, we can only work hardly. arrange as many jobs as possible. construct a graph $G$ where $V=\{ job(i)\mid i=1, ..., m \}$ and $E=\{ (u, v) \mid \text{end-time}(u)<\text{start-time}(v) \}$. find a longest path. $O(m^2)$, too expensive. 

construct a graph $G$ where $V=\{1, ..., n\}$(every day is a vertex) and $E=\{ (u, v) \mid \text{there is a job occupy }[u, v] or u+1=v\}$. 

## knapsack problem

base case is $dp[0][w]=value[0]$ for $w\ge weight[0]$, not only $dp[0][weight[0]]=value[0]$ like the subset-sum problem. 
since update $dp[i][j]$ only use $dp[i-1][j]$ and $dp[i-1][j-weight[i]]$ whose second index is all less than $j$, we can use a 1D array to maintain states. 

in bounded knapsack problem, suppose $a_{ij}$ is j-th item of i-th kind of item. Then to consider choosing $a_{i1},a_{i2}$ is the same as considering choosing $a_{i2},a_{i3}$. Thus, view it as a 01 knapsack is unnecessary since some items are the same. we just consider the numbers instead of combination of them. 

## 1433

think of buying a stock and sale it as a pair. find such pairs as many as possible. 