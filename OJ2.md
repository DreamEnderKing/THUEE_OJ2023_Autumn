## 问题描述

军训时需要将所有同学(包括教官)排成一队，一开始只有教官(编号为1)排在第一个，之后教官会发出如下三种命令：
 
1 x y   编号为y的同学入队，排在编号为x的同学的后面，若要排在队首，则用0表示x
2 x     编号为x的同学报告其后面的同学编号，若要报告队首同学的编号，则用0表示x，若x在队尾，则报告0
3 x     编号为x的同学出队
 
要求对于每次命令2，都输出报告同学后面同学的编号，并最后从头到尾输出队列中同学的编号。
 
![](images/OJ2.png)

## 输入格式

第一行为一个正整数N，表示总共有几条命令
接下来N行中，每行表示一个命令；每行命令中，数字之间用空格隔开

## 输出格式

对于每次命令2，都输出一个编号，用换行隔开
最后从头到尾输出队列，用换行隔开