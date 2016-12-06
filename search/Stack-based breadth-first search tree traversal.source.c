#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define CCOUNT 7
#define false 0
#define true 1

//typedef char bool;

typedef struct NODE {
    char data;
    struct NODE* child;
} NODE;

/*Tree Intializatin routine ** Not part of the algorithm*/
NODE* initializetree(NODE* root, int childrencount, int level) {
    int i;
    static int si;
    if (root == NULL) {
        si = level;
        root = (NODE*) malloc(sizeof (NODE));
        root->data = 'a';
        root->child = NULL;
    }
    if (--level == 0) return root;
    root->child = (NODE*) malloc(childrencount * sizeof (NODE));
    for (i = 0; i < childrencount; i++) {
        (root->child + i)->data = ((si + 1 - level) % 3 ? ((si - level) % 3 ? 48 : 97) : 65) + i;
        (root->child + i)->child = NULL;
        initializetree(root->child + i, childrencount, level);
    }
    return root;
}

/*Tree deallocation routine ** Not part of the algorithm*/
bool deallocatetree(NODE* root, int level) {
    int i;
    if (root == NULL) return false;
    if (root->child != NULL) {
        for (i = 0; i < CCOUNT; i++) if (deallocatetree(root->child + i, level + 1)) break;
    } else {
        free(root);
        return true;
    }
    if (i == CCOUNT) free(root->child);
    if (level == 1) free(root);
    return false;
}

/*BFS sub routine*/
bool printtree(NODE* node, int target, int level) {
    int i;
    bool returnval = false;
    if (target > level) {
        for (i = 0; i < CCOUNT; i++) if (printtree(node->child + i, target, level + 1)) returnval = true;
    } else {
        printf("%c", (node->data));
        if (node->child != NULL) returnval = true;
    }
    return returnval;
}

/*BFS routine*/
void printbfstree(NODE* root) {
    if (root == NULL) return;
    int target = 0;
    while (printtree(root, target++, 0)) {
        printf("\n");
    }
}

/*Main routine*/
int main(int argc, char **argv) {
    int c;
    int desiredlevel = 3;
    while ((c = getopt(argc, argv, "hl:")) != -1)
        switch (c) {
            case 'l':
                desiredlevel = atoi(optarg);
                break;
            case 'h':
                printf("stackbasedBFS [-l level] [-h]\n");
                return -1;
        }
    NODE* root = NULL;
    root = initializetree(NULL, CCOUNT, desiredlevel);
    printbfstree(root);
    deallocatetree(root, 1);
    return 0;
}
Raw
 Stack-based breadth-first search tree traversal.txt
简介： 本文讲解了传统的广度优先搜索 (BFS)的缺陷是队列数据结构需要大量额外空间。如果一个树有多个子树，而且是一个平衡树，那么队列大小将呈指数级增长，可能导致严重的内存不足。本文中的解决方案提供一种并行方法，以 BFS 方式打印树，完全不需要使用队列数据结构。该解决方案使用了堆栈内存，内存使用量是以 N 为底数的 log(n)，其中 N 是每个节点的平均子节点数量，“n” 是树中的节点数量。

简介

本文介绍了如何使用堆栈在树上执行广度优先搜索（逐级搜索），可以使用过程分配的堆栈或者使用一个独立的堆栈数据结构。BFS 是一种优先考虑广度的树扫描方式。打印的第一个节点是根节点，随后是它的直系子节点，然后是下一级子节点。在这里，根节点位于第 1 级，它的子节点位于第 2 级。接下来打印第 3 级上的孙节点。BFS 将继续以这种方式打印，直到到达最后一级。下面的树就是一个例子。

                                (a)
                                 |
                                 v
             ---------------------------------------------
             |      |      |      |      |     |         |
             v      v      v      v      v     v         v
            (0)    (1)    (2)    (3)    (4)   (5)       (6)
             |      |      |      |      |     |         |
             v      |      v      --+    v     ------+   v
   -------------    | ------------- |  ------------- | -------------
   | | | | | | |    | | | | | | | | |  | | | | | | | | | | | | | | |
   A B C D E F G    | A B C D E F G |  A B C D E F G | A B C D E F G
                    |               |                |
                    v               v                v
                 -------------  -------------   -------------
                 | | | | | | |  | | | | | | |   | | | | | | |
                 A B C D E F G  A B C D E F G   A B C D E F G


这将打印为 “a 0 1 2 3 4 5 6 A B C D E F G A B C D E F G A B C D E F G A B C D E F G A B C D E F G A B C D E F G A B C D E F G”。

回页首

方案

该问题的已知解决方案是使用一个额外队列。在遇到一个节点时，将它的子节点推送到队列中。不断上移队列以打印该节点，同时将它的所有子节点推入队列中。

 procedure bfs(root:NODE*);
 var myqueue:Queue;
 var node:NODE*;
 BEGIN
 push(myqueue,root);
 while(myqueue not empty) do
 begin
 node=pop(myqueue);
 print node;
 for (all children of node) do
 push(myqueue,children);
 end
 END


在此解决方案中，我们有一个内存问题，尤其是在树不是二叉树或它是一种平衡类型的树（节点数量呈指数级增长）时。例如，在上面的树中，第 3 级本身有 49 个节点。在此情形下，如果打印第 2 级的端节点（‘6’），那么队列将包含所有 49 个条目。现在计算第 N 级，它将包含 7^(N-1) 个节点。所以，如果一个树有 11 级，那么将有 3 亿个条目，如果每个条目有一个 4 字节地址指针，那么累积将占用 1 MB 内存。当函数是重入式的 (re-entrant) 且通过多个线程访问时，那么情况会更糟糕。

回页首

建议的解决方案

使用新解决方案，我们可以牺牲一定的时间来换取空间优势。如果发现递归式节点，那么所用的空间将仅仅取决于级数，而在平衡树中，它将为 log(n)，其中 ‘n’ 是节点总数。该解决方案的伪代码如下所示。

procedure bfs(root:NODE*);
 var target=0;
 var node=root;
 BEGIN
 for each level in tree do
 begin
 printtree(node,target,0);
 target=target+1;
 end
 END
 

 procedure printtree(node:NODE*, target:int, level:int);
 BEGIN
 if(target > level) then
 begin
 for each children of node do
 printtree(child,target,level+1);
 end
 else
 print node;
 END


在 32 位系统中，如果计算每次函数调用期间占用的堆栈大小，那么它将为 ‘参数 + 返回地址 + 当前堆栈指针 + 当前基址指针’。占用大小通常为 4*3+4+4+4=20 字节。如果总共有 11 级，占用大小将为 220 字节，比 1 MB 小得多。

回页首

工作原理

这里涉及到两个实体：一个帮助器 和一个树扫描器。在设计中，帮助器 包含一个树扫描器。

     +------+         +------------+
     |Helper|<>------>|Tree Scanner|
     |      |         |            |
     +------+         +------------+
   <>--------> Aggregation


帮助器要求树扫描器打印特定级别上的所有节点。树扫描器找到每个级别上的节点，询问它们是否属于帮助器寻找的级别。如果该节点属于此特定级别，那么它会得到证实并被返回。然后打印这个特定级别上的所有节点，帮助器要求树扫描器打印下一个节点，直到到达最后一个级别。在下面的例子中，一个树帮助器要求打印第 3 级的所有节点。


            +-->(0)   +-->(A)   |-->(e)
            |-->(1)   |-->(B)-->|-->(f)
            |-->(2)-->|-->(C)   |-->(h)
   (a)----->| .       |.
            | .                           |-->(i)
    ^       | .       +-->(D)------------>|-->(j)
    |       +-->(6)-->|-->(E)   |-->(a)   |-->(k)
                      |-->(F)-->|-->(b)
    |                 |-->(G)   |-->(c)
                      +-->(H)
    |


 Tree scanner checks
 at first level, if
 it does not match
 to level number 3 it
 proceeds to next level

 

            +-->(0)   +-->(A)   |-->(e)
            |-->(1)   |-->(B)-->|-->(f)
            |-->(2)-->|-->(C)   |-->(h)
   (a)----->| .       |.
            | .                           |-->(i)
            | .       +-->(D)------------>|-->(j)
            +-->(6)-->|-->(E)   |-->(a)   |-->(k)
                      |-->(F)-->|-->(b)
                 ^    |-->(G)   |-->(c)
                 |    +-->(H)
                /
               /
 Tree scanner checks
 at second level next
 if it does not match
 to level number 3 it
 proceeds to next level

 


            +-->(0)   +-->(A)   |-->(e)
            |-->(1)   |-->(B)-->|-->(f)
            |-->(2)-->|-->(C)   |-->(h)
   (a)----->| .       |.
            | .                           |-->(i)
            | .       +-->(D)------------>|-->(j)
            +-->(6)-->|-->(E)   |-->(a)   |-->(k)
                      |-->(F)-->|-->(b)
                      |-->(G)   |-->(c)
                      +-->(H)

                           ^        
                           |
                          /
                         /
        Tree scanner checks
        at third level next
        and it does match to
        level number 3 it prints
        this level nodes to next


回页首

其他优势

美化

输出美化能够以更轻松的方式完成。我们假设，您需要在每个子节点之间插入一个分界线 ‘-------------’，如下面的示例所示：

 a
 -------------
 0 1 2 3 4 5 6
 -------------
 A B C D E F G A B C D E F G A B C D E F G A B C D E F G A B C D E F G A B C D E F G A B C
 D E F G


这可通过在 printtree 命令后插入 println 命令来完成。

 for each level in tree do
 printtree(node, target, 0);
 println('-------------');
 .
 .
 .


特定于级别

这对打印一个特定级别（比如第 4 级）很有用。我们考虑下面这个真实例子。在公司分层结构中，将这个例子与一个树相对应，其中 CEO 位于顶级，初级工程师位于最底级。级别通常按等级分布。所以，如果高级工程师位于特定的等级（假设为等级 x），并且您需要打印所有与级别 (N+1-x)（其中 N 是最高的等级）对应的高级工程师，请查看下面的示例：


                         CEO            <---BAND N
                          ^
                          |
                      +------+       
                      |      |
                PresidentA  PresidentB
                   ^
                   |
              +---------+
              |    |    |
             VP1   VP2  VP3
                        .
                        .
                        .
                        ^
                        |
                    +-------+
                    |   |   |
                   SE1  SE2  SE3      <----BAND x
                        .
                        .
                        ^
                        |
                   +--------+
                   |    |   |
                  ENG1 ENG2 ENG3      <----BAND 1


程序代码将为：

 printtree(root,N+1-x,0);


而且，也可以直接从脚本使用此函数。

回页首

泛化（Generalization）

如果有人需要有一种不同类型的列表和一种不同类型的列表迭代方式，那么模板方法将是最适合的模式。用户可选择使用列表迭代的模板方法，处理多种类型的列表，而不实际揉合算法（类似于一个抽象类）。泛化 (generalization ) 可在某些类型的列表（比如数组、单链接列表、双链接列表等）迭代。

                    +----------------+
                    | BFS            |
                    |                |
                    |+iteratelist()=0|
                    +----------------+
                          ^
                         /_\
                          |
                        / | \
                       /  |  \
               /-------   |   -------\
              /           |           \
             /            |            \
            /             |             \
  +--------------+ +--------------+ +--------------+
  | ARRAY        | |SGL LINKED LST| |DBL LINKED LST|
  |              | |              | |              |
  |+iteratelist()| |+iteratelist()| |+iteratelist()|
  +--------------+ +--------------+ +--------------+


回页首

程序

下面给出了一个 BFS C 程序（其中子节点列表为连续内存形式）：

 /*BFS sub routine*/
 bool printtree(NODE* node, int target, int level) {
 int i;
 bool returnval=false;
 if (target > level) {
 for(i=0;i<CCOUNT;i++) if(printtree(node->child+i,target,level+1) ) returnval=true;
 }
 else {
 printf("%c",(node->data));
 if(node->child != NULL) returnval=true;
 }
 return returnval;
 }


 /*BFS routine*/
 void printbfstree(NODE* root) {
 if(root == NULL) return;
 int target=0;
 while(printtree(root,target++,0)) {
 printf("\n");
 }
 }


回页首

实验数据

使用 -DSPACEDATA 选项提供编译空间数据，使用 -DTIMEDATA 选项提供编译时间数据，使用 -DLPRINT 编译行打印，使用 -DNOPRINT 则不打印数据。 请注意：‘---------------’ 行之间的行是命令和它生成的输出。

子节点级别数为 7 且树深度为 3 的两种类型的正常打印

 ---------------
 >a.out -l3 -c7
 queue based, allocated for queue size 50 ,each node size 4 bytes
 printing queue based
 a0123456ABCDEFGABCDEFGABCDEFGABCDEFGABCDEFGABCDEFGABCDEFG
 printing stack based
 a0123456ABCDEFGABCDEFGABCDEFGABCDEFGABCDEFGABCDEFGABCDEFG
 printing done
 ---------------


打印基于堆栈的 BFS 方法的逐行输出

 ----------------
 >gcc -DLPRINT -lm stackbasedBFS.c
 >./a.out -l3 -c7
 queue based, allocated for queue size 50 ,each node size 4 bytes
 printing queue based
 a0123456ABCDEFGABCDEFGABCDEFGABCDEFGABCDEFGABCDEFGABCDEFG
 printing stack based
 a
 0123456
 ABCDEFGABCDEFGABCDEFGABCDEFGABCDEFGABCDEFGABCDEFG
 printing done
 ----------------


打印空间数据和时间数据

 ---------------
 >./a.out -l5 -c2
 queue based, allocated for queue size 17 ,each node size 4 bytes
 printing queue based
 a01ABABabababab0101010101010101
 queue based, queue usage size 16
 diff time 0 sec 26 micro

 printing stack based
 a01ABABabababab0101010101010101
 stack used 128
 diff time 0 sec 14 micro

 printing done
 ---------------


空间和时间分析

 --------------
 > cc -DNOPRINT -DSPACEDATA -DTIMEDATA -lm  stackbasedBFS.c
 > ./a.out -l10 -c10
 queue based, allocated for queue size 1000000001 ,each node size 4 bytes
 > ./a.out -l10 -c9
 queue based, allocated for queue size 387420490 ,each node size 4 bytes
 printing queue based
 Segmentation fault
 > ./a.out -l9 -c10
 queue based, allocated for queue size 100000001 ,each node size 4 bytes
 printing queue based
 queue based, queue usage size 100000000
 diff time 28 sec 490083 micro

 printing stack based
 stack used 256
 diff time 1 sec 469060 micro

 printing done
 > ./a.out -l5 -c10
 queue based, allocated for queue size 10001 ,each node size 4 bytes
 printing queue based
 queue based, queue usage size 10000
 diff time 0 sec 2891 micro

 printing stack based
 stack used 128
 diff time 0 sec 164 micro

 printing done
 > ./a.out -l10 -c7
 queue based, allocated for queue size 40353608 ,each node size 4 bytes
 printing queue based
 queue based, queue usage size 40353607
 diff time 11 sec 874163 micro

 printing stack based
 stack used 288
 diff time 0 sec 788580 micro

 printing done
 > ./a.out -l20 -c2
 queue based, allocated for queue size 524289 ,each node size 4 bytes
 printing queue based
 queue based, queue usage size 524288
 diff time 0 sec 333929 micro

 printing stack based
 stack used 608
 diff time 0 sec 40476 micro

 printing done
 > ./a.out -l25 -c2
 queue based, allocated for queue size 16777217 ,each node size 4 bytes
 printing queue based
 queue based, queue usage size 16777216
 diff time 10 sec 635081 micro

 printing stack based
 stack used 768
 diff time 1 sec 482634 micro

 printing done
 > ./a.out -l30 -c2
 queue based, allocated for queue size 536870913 ,each node size 4 bytes
 allocation failed, exiting

 > ./a.out -l28 -c2
 queue based, allocated for queue size 134217729 ,each node size 4 bytes
 allocation failed, exiting
 > ./a.out -l27 -c2
 queue based, allocated for queue size 67108865 ,each node size 4 bytes
 printing queue based
 queue based, queue usage size 67108864
 diff time 43 sec 22479 micro

 printing stack based
 stack used 832
 diff time 5 sec 773319 micro

 printing done
 -----------------


在空间分析中，我们可考虑最糟糕的场景，也就是 9 级和 10 个子节点。这里，基于队列的方法所使用的节点数量为 100,000,000，如果每个节点 4 个字节，累计内存大小为 100000000*4=400 MB(arr)。基于堆栈的方法使用的内存为 256 字节。在此程序中，它仅计算 8 级，而不是 9 级。对于 9 级，合计为 (9/8)*256=288，也就是每级 288/9=32 字节。在下一节中，我们将证明理想情况下这一数据为 20 字节（其中没有局部变量）。

在时间分析中，我们可考虑最糟的场景，也就是 27 级和 2 个子节点。基于队列的方法花费的时间为 42 秒和 22,479 微秒。基于堆栈的方法花费的时间为 5 秒和 773,319 微秒。

在这里，我们将讨论一下树的每个级别所用的 32 字节。

 ----------------
 > gdb
 GNU gdb 6.3
 Copyright 2004 Free Software Foundation, Inc.
 GDB is free software, covered by the GNU General Public License, and you are
 welcome to change it and/or distribute copies of it under certain conditions.
 Type "show copying" to see the conditions.
 There is absolutely no warranty for GDB.  Type "show warranty" for details.
 This GDB was configured as "i686-pc-linux-gnu".
 (gdb) file a.out
 Reading symbols from /home/pravinsi/a.out...done.
 Using host libthread_db library "/lib/tls/libthread_db.so.1".
 (gdb) b printtree
 Breakpoint 1 at 0x8048802: file stackbasedBFS.c, line 79.
 (gdb) run
 Starting program: /home/pravinsi/a.out
 queue based, allocated for queue size 50 ,each node size 4 bytes
 printing queue based
 a0123456ABCDEFGABCDEFGABCDEFGABCDEFGABCDEFGABCDEFGABCDEFG
 queue based, queue usage size 49
 diff time 0 sec 82 micro

 printing stack based

 Breakpoint 1, printtree (node=0x804b008, target=0, level=0) at stackbasedBFS.c:79
 79          __asm__("movl %%ebp, %0;" : "=r" ( i));
 (gdb) c
 Continuing.

 Breakpoint 1, printtree (node=0x804b008, target=1, level=0) at stackbasedBFS.c:79
 79          __asm__("movl %%ebp, %0;" : "=r" ( i));
 (gdb) bt
 #0  printtree (node=0x804b008, target=1, level=0) at stackbasedBFS.c:79
 #1  0x080488d6 in printbfstree (root=0x804b008) at stackbasedBFS.c:99
 #2  0x08048f51 in main (argc=1, argv=0xbffff894) at stackbasedBFS.c:216
 (gdb) c
 Continuing.

 Breakpoint 1, printtree (node=0x804b018, target=1, level=1) at stackbasedBFS.c:79
 79          __asm__("movl %%ebp, %0;" : "=r" ( i));
 (gdb) bt
 #0  printtree (node=0x804b018, target=1, level=1) at stackbasedBFS.c:79
 #1  0x0804886c in printtree (node=0x804b008, target=1, level=0) at stackbasedBFS.c:84
 #2  0x080488d6 in printbfstree (root=0x804b008) at stackbasedBFS.c:99
 #3  0x08048f51 in main (argc=1, argv=0xbffff894) at stackbasedBFS.c:216
 (gdb) f 1
 #1  0x0804886c in printtree (node=0x804b008, target=1, level=0) at stackbasedBFS.c:84
 84    for(i=0;i<CCOUNT;i++) if(printtree(node->child+i,target,level+1) ) returnval=true;
 (gdb) info reg ebp
 ebp            0xbffff7a8       0xbffff7a8
 (gdb) f 0
 #0  printtree (node=0x804b018, target=1, level=1) at stackbasedBFS.c:79
 79          __asm__("movl %%ebp, %0;" : "=r" ( i));
 (gdb) info reg ebp
 ebp            0xbffff788       0xbffff788
 (gdb) x/10x 0xbffff788
 0xbffff788:     0xbffff7a8      0x0804886c      0x0804b018      0x00000001
 0xbffff798:     0x00000001      0x08048d5b      0x000490cf      0x00000000
 0xbffff7a8:     0xbffff7c8      0x080488d6
 (gdb) x 0x0804886c
 0x804886c <printtree+112>:      0x8410c483
 (gdb) x 0x08048d5b
 0x8048d5b <BFS+413>:    0xc910c483
 -----------------


可以看到，两个连续基址指针（也就是 0xbffff7a8 和 0xbffff788）之间的内存区域为：

 0xbffff788:     0xbffff7a8      0x0804886c      0x0804b018      0x00000001
 0xbffff798:     0x00000001      0x08048d5b      0x000490cf      0x00000000
 0xbffff7a8:     0xbffff7c8


一个基址指针 (0xbffff7a8) 与下一个基址指针 (0xbffff788) 之间相差 32 字节。其中两个是局部变量 0x00000000('i') 和 0x000490cf('returnval')，一个是缓存的数据 0x08048d5b。如果我们删除实现细节，仅查看一般内存使用，那么结果为每个级别 8-3=5. 5*4=20 字节。

回页首

读者练习

由于函数递归方法在内部使用了堆栈，所以另一种方法是显式使用堆栈而不是使用函数递归。读者可练习使用另一种非递归方法。它可以节省更多的内存。

回页首

结束语

实验数据符合我们的理论假设。我们已说明，在本文中提供的示例程序中，基于堆栈的 BFS 的树的每个级别占 32 字节，其中有 8 字节是算法树递归函数的局部变量。对于
