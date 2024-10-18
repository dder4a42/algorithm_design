# Record of problems

## 1295

+ 需要获得≤n的素数个数
+ 似乎提示使用random，如Miller Rabin检测？
+ notice that probability is quite small when n is large, especiall << 1e-5. Then even guess p=0 is enough.

## 1301

逆序对问题，不过需要对每个数字记录其关联的对数。

## 1982

若现有最小周长为$d$，则新的最小三角形必须满足最长边$\le \frac{d}{2}$（考虑退化的三角形），则任意两点间的$|x_1 - x_2|<d/2$且$|y_1 - y_2| < d/2$。又，满足这些条件的点不会太密集地分布在$d/2$的方格中，于是可使用最近点对的框架。