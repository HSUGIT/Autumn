====
1.设一棵完全二叉树有700个结点，则在该二叉树中有多少个叶子结点
答：
    如果一棵具有n个结点的深度为k的二叉树，它的每一个结点都与深度为k的满二叉树中编号为1~n的结点一一对应，这棵二叉树称为完全二叉树。
    可以根据公式进行推导，假设n0是度为0的结点总数（即叶子结点数），n1是度为1的结点总数，n2是度为2的结点总数，由二叉树的性质可知：n0＝n2＋1，则n= n0＋n1＋n2（其中n为完全二叉树的结点总数），由上述公式把n2消去得：n= 2n0+n1－1，由于完全二叉树中度为1的结点数只有两种可能0或1，由此得到n0＝（n＋1）/2或n0＝n/2，合并成一个公式：n0＝（n＋1）/2 ，就可根据完全二叉树的结点总数计算出叶子结点数。

700/2=350个叶子节点 
权重：中

====
5.什么是平衡二叉树？
      左右子树都是平衡二叉树 且左右子树的深度差值的绝对值不大于1。
权重：中

====
2、什么是平衡二叉树？
	当且仅当两个子树的高度差不超过1时，这个树是平衡二叉树。
权重：中

====
扩展：以下与数据的存储结构有关的术语是（ABC）[多选]
A．循环队列
B．链表
C．哈希表
D．栈
解析：循环队列、链表和哈希表都属于存储结构的描述，而栈属于逻辑结构描述
权重：中

====
1.若某线性表常用的操作是存取任一指定序号的元素和在后进行插入和删除运算，则利用()存储方式节省时间（A）
A.顺序表
B.双链表
C.带头结点的双循环链表
D.单循环链表
解析：采用顺序存储方式在已知元素序号的情况下可以直接计算出地址，当指定在线性表的最后进行插入和删除运算时，也不需要进行大量元素的移动
权重：中

====
11.若一棵具有n(n>0)个结点的二叉树的先序序列与后序序列正好相反，则该二叉树一定？( C)
A.结点均无左孩子的二叉树
B.结点均无右孩子的二叉树
C.高度为n的二叉树
D.存在度为2的结点的二叉树
解析：
原理如下：
先序遍历顺序是：M-L-R;
后序遍历顺序是：L-R-M;
可以看到，只有中间的结点（M）顺序变化了，左右结点相对位置是不变的。那可以推断出，要满足题意的话“二叉树的先序序列与后序序列正好相反”，说明整个二叉树左子树或者右子树有一个没有（遍历就成了，先：M-L ；后：L-M 或者 先：M-R ；后：R-M ）也就是必然是一条链.
权重：中

====
19.在一个10阶的B-树上，每个树根结点中所含的关键字数目多允许为( )个，少允许为( B)个。

A 10,5
B 9,4
C 8,3
D 7,6
解析：最多M-1 最少M/2-1 向上取整。
权重：中

====
20.关于红黑树和AVL树，以下哪种说法正确?（ABC）[多选]
A 两者都属于自平衡二叉树
B 两者查找,插入，删除的时间复杂度相同
C 包含n个内部节点的红黑树的高度是O(log(n))
D JDK的TreeMap是一个AVL的实现
解析：红黑树和avl树都属于自平衡二叉树；
两者查找、插入、删除的时间复杂度相同；
包含n个内部结点的红黑树的高度是o(logn);
TreeMap是一个红黑树的实现，能保证插入的值保证排序。
权重：中






