====
7、交换两个变量的值,不使用第三个变量,即a=3, b=5, 交换后b=3, a=5。
    unsigned char a = 3, b = 5;
    a = a + b; 
    b = a - b; 
    a = a - b; 
或者 
    a = a ^ b; 
    b = a ^ b; 
    a = a ^ b;
如果写成函数：
void swap(int a,int b)
{ 
    a = a ^ b; 
    b = a ^ b; 
    a = a ^ b;
}
或者
void swap(int a, int b)
{ 
    a = a + b; 
    b = a - b; 
    a = a - b; 
}
不过这两种方法只是修改了函数的形参，如果要修改实参，可以采用如下的方法:
void swap(int* a, int *b)
{ 
    *a = *a ^ *b; 
    *b = *b ^ *a; 
    *a = *a ^ *b; 
    printf("In %s:a=%d,b=%d\n",__FUNCTION__,*a,*b); 
}
权重：较高
备注：主要考察对数据在硬件中的存储规则

====
11、如何判别一个数是unsigned？
#define issignal(x) ((x>=0 && ~x>=0) ? 1:0) //为1是无符号 为0有符号
权重：较高
备注：可以直接记住。
    signed最高位只是用来做标记(sign)，标记整数的正负，0表示正，1表示负。
    signed都是正数，而unsigned有正数有负数

====
试题1：请写一个C函数，若处理器是Big_endian的，则返回0；若是Little_endian的，则返回1
解答： 
int checkCPU()
{
    union w
    { 
        int a;
        char b;
    } c;
    c.a = 1;

    return (c.b == 1);
}
剖析：
　 　嵌入式系统开发者应该对Little-endian和Big-endian模式非常了解。采用Little-endian模式的CPU对操作数的存放方式是从低字节到高字节，而Big-endian模式对操作数的存放方式是从高字节到低字节。例如，16bit宽的数0x1234在Little-endian模式CPU内存中的存放方式（假设从地址0x4000开始存放）为：
内存地址 存放内容 
0x4000 0x34 
0x4001 0x12 
　　而在Big-endian模式CPU内存中的存放方式则为：
内存地址 存放内容 
0x4000 0x12 
0x4001 0x34 
　　32bit宽的数0x12345678在Little-endian模式CPU内存中的存放方式（假设从地址0x4000开始存放）为：
内存地址 存放内容 
0x4000 0x78 
0x4001 0x56 
0x4002 0x34 
0x4003 0x12 
　　而在Big-endian模式CPU内存中的存放方式则为：
内存地址 存放内容 
0x4000 0x12 
0x4001 0x34 
0x4002 0x56 
0x4003 0x78 
　　联合体union的存放顺序是所有成员都从低地址开始存放，面试者的解答利用该特性，轻松地获得了CPU对内存采用Little-endian还是Big-endian模式读写
权重：高

====
试题2：写一个函数返回1+2+3+…+n的值（假定结果不会超过长整型变量的范围） 
解答
int Sum( int n )
{ 
　 return ( (long)1 + n) * n / 2;　　//或return (1l + n) * n / 2;

}
剖析：
对于这个题，只能说，也许最简单的答案就是最好的答案。下面的解答，或者基于下面的解答思路去优化，不管怎么“折腾”，其效率也不可能与直接return ( 1 l + n ) * n / 2相比。
权重：中

====
42、编一个简单的求n!的程序
权重：中

====
26:写一语句实现x是否为2的若干次幂的判断。
参考答案：!(X)&(X-1)
权重：较高
备注：理解并记住

====
3 一语句实现x是否为2的若干次幂的判断
int i = 512;
cout << boolalpha << ((i & (i - 1)) ? false : true) << endl;
权重：中

===
5.下面算法中可以判断出一个有向图是否有环的是(BD)[多选]
A.求短路径
B.深度优先遍历
C.广度优先遍历
D.拓扑排序
分析：判断无向图 中是否存在回路（环）的算法描述
如果存在回路，则必存在一个子图，是一个环路。环路中所有顶点的度>=2。
算法：
第一步：删除所有度<=1的顶点及相关的边，并将另外与这些边相关的其它顶点的度减一。
第二步：将度数变为1的顶点排入队列，并从该队列中取出一个顶点重复步骤一。
如果最后还有未删除顶点，则存在环，否则没有环。
有向图是否有环的判定算法，主要有深度优先和拓扑排序两种方法。
权重：中

====
15.线性表(a1,a2,…,an)以链接方式存储时,访问第i位置元素的时间复杂性为©
A O(i)
B O(1)
C O(n)
D O(i-1)
权重：中

====
17.对一个含有20个元素的有序数组做二分查找，数组起始下标为1，则查找A[2]的比较序列的下标为(B)

A 9,5,4,2
B 10,5,3,2
C 9,6,2
D 20,10,5,3,2
解析：
(high-low)/2+low = middle; 下标从1开始，因为查找查找A[2]， low始终为1；
20-1）/2+1=10;
(10-1)/2+1 = 5;
(5-1)/2+1 = 3;
(3-1)/2+1 = 2;
权重：中

====
25.以下()属于线性分类器佳准则?（ACD）【多选】
A 感知准则函数
B 贝叶斯分类
C 支持向量机
D Fisher准则
权重：较低

====
1、写出两个排序算法，并说明哪个好?
答：一般使用冒泡法和快速排序法，对堆栈局域比较小的单片机来说冒泡法比较好，对时间要求苛刻的实时响应来说快速排序法好。
题注：时间复杂度：一个算法花费的时间与算法中语句的执行次数成正比例，用T(n)表示，n为问题的规模，若有某个辅助函数f(n),使得当n趋近于无穷大时，T（n)/f(n)的极限值为不等于零的常数，则称f(n)是T(n)的同数量级函数。记作T(n)=O(f(n)),称O(f(n)) 为算法的渐进时间复杂度，简称时间复杂度。时间频度不同，但时间复杂度可能相同。如：T(n)=n2+3n+4与T(n)=4n2+2n+1它们的频度不同，但时间复杂度相同，都为O(n2)。
本题中，最坏的情况要计算9+8+7+6+5+4+3+2+1次，即n的级数，结果为n（n/2）=n2/2。所以冒泡法时间复杂度O（n2）
1） 冒泡法：从小到大排，时间复杂度On2
#define MAX_NUM 10
int a_data[MAX_NUM]={1, 2, 3, 4, 5, 6, 7, 8, 9, 0}; // 也可以用scanf获取
int main(void)
{
    int i=0, j=0, tmp=0;
    for(i=0; i<MAX_NUM-1; i++) {
        for(j=i+1; j<MAX_NUM; j++) {
            if(a_data[i] > a_data[j]) { // 如果i不是小于j，则调换
                tmp = a_data[i];
                a_data[i] = a_data[j];
                a_data[j] = tmp;
            }
        }
    }
    return 0;
}

2）交换排序-快速排序，类似于二分法：采用递归。选第一个点或中间的点，左边放最小值，右边放最大值，依次递归到最低层的两个元素。因为每递归一次要压栈一次，占用存储空间，所以空间复杂度较高。时间复杂度Onlog2n
#define MAX_NUM 16
int a_data[MAX_NUM]={1, 2, 3, 4, 5, 6, 7, 8, 9, 0,11,12,13,14,15,16}; // 也可以用scanf获取
//快速排序  
void quick_sort(int s[], int l, int r)
{
	if (l < r)
	{
		//Swap(s[l], s[(l + r) / 2]); // 将中间的这个数和第一个数交换 可换可不换  
		int i = l, j = r, x = s[l]; // s[l]会先被替换，最后这个值会被写回到s[i]，它们也充当了临时变量的角色
		while (i < j)
		{
			while (i < j && s[j] >= x) // 从右向左找第一个小于x的数  
				j--;
			if (i < j)
				s[i++] = s[j];

			while (i < j && s[i] < x) // 从左向右找第一个大于等于x的数  
				i++;
			if (i < j)
				s[j--] = s[i];
		}
		s[i] = x;
		quick_sort(s, l, i - 1); // 递归调用   
		quick_sort(s, i + 1, r);
	}
}
int main(void)
{
    sort(a_data, 0, MAX_NUM - 1);
}
权重：高

====
21、可重入函数的条件有哪些？
答：主要用于多任务环境中，可被中断。除了自己栈上的变量外不调用全局变量（即便少量使用也要用同步与互斥进行保护）；不能调用malloc和free；操作硬件时屏蔽硬件中断，操作完成后释放硬件中断。

====
1、将一整数逆序后放入一数组中（要求递归实现）
void convert(int *result, int n) {
     if(n>=10)
         convert(result+1, n/10);
     *result = n%10; 
}

int main(int argc, char* argv[]) {
     int n = 123456789, result[20]={};
     convert(result, n);
     printf("%d:", n);
     for(int i=0; i<9; i++)
         printf("%d", result[i]);
}
权重：中

====
2、求高于平均分的学生学号及成绩（学号和成绩人工输入）
答：
double find(int total, int n) {
     int number, score,  average;
     scanf("%d", &number);
     if(number != 0) {
         scanf("%d", &score);
         average = find(total+score, n+1);
         if(score >= average)
              printf("%d:%d\n", number, score);
         return average;
     } else {
         printf("Average=%d\n", total/n);
         return total/n;
     }
}
int main(int argc, char* argv[]) {
     find(0, 0);
}
权重：中

====
3、递归实现回文判断（如：abcdedbca就是回文，判断一个面试者对递归理解的简单程序）
int find(char *str, int n) {
     if(n<=1) return 1;
     else if(str[0]==str[n-1])   return find(str+1, n-2);
     else     return 0;
}
int main(int argc, char* argv[]) {
     char *str = "abcdedcba";
     printf("%s: %s\n", str, find(str, strlen(str)) ? "Yes" : "No");
}
权重：较高
 
====
8.冒泡排序算法的时间复杂度是什么？
      时间复杂度是O(n^2)。
权重：中

====
2.数组a[N]，存放了1至N-1个数，其中某个数重复一次。写一个函数，找出被重复的数字.时间复杂度必须为o（N）函数原型：
int do_dup(int a[],int N)
答
算法思想：先对1..N-1之间的所有整数累加求和，再对数组中的所有元素累加求和；用后者减去前者得到的差就是重复的数字。
参考源代码(C++)：
#include "iostream.h"

void main()
{
    int arr[] = {6, 2, 3, 4, 3, 5, 1};
    int N = 7;
    int sum1, sum2;
    int i;

    for(i=1,sum1=0; i<N; sum1+=i,i++);
    for(i=0,sum2=0; i<N; sum2+=arr[i],i++);
    cout<<"重复的数字是 "<<sum2-sum1<<endl;
}
时间复杂度：O（n）
算法特点：对于数组中数值的出现顺序不做任何要求，即无需有序（这是二楼算法的缺陷）。
权重：中

====
2.写一段程序，找出数组中第k大小的数，输出数所在的位置。例如{2，4，3，4，7}中，第一大的数是7，位置在4。第二大、第三大的数都是4，位置在1、3随便输出哪一个均可。函数接口为：int find_orderk(const int* narry,const int n,const int k) 
要求算法复杂度不能是O(n^2）
答：
    可以先用快速排序进行排序，其中用另外一个进行地址查找
代码如下，在VC++6.0运行通过。
//快速排序
#include <iostream>
using namespace std;
int Partition (int *L, int low, int high)
{
    int temp = L[low];
    int pt = L[low];

    while (low < high)
    {
        while (low < high && L[high] >= pt)
            --high;
        L[low] = L[high];
        while (low < high && L[low] <= pt)
            ++low;
        L[low] = temp;
    }
    L[low] = temp;

    return low;
}

void QSort (int*L, intlow, int high)
{
    if (low < high)
    {
        int pl = Partition (L, low, high);

        QSort (L, low, pl - 1);
        QSort (L, pl + 1, high);
    }
}

int main()
{
    int narry[100], addr[100];
    int sum = 1, t;

    cout << "Input number:" << endl;
    cin >> t;

    while (t != -1)
    {
        narry[sum] = t;
        addr[sum - 1] = t;
        sum++;

        cin >> t;
    }

    sum -= 1;
    QSort (narry,1,sum);

    for (int i = 1; i <= sum;i++)
        cout << narry[i] << '\t';
    cout << endl;

    int k;
    cout << "Please input place you want:" << endl;
    cin >> k;

    int aa = 1;
    int kk = 0;
    for (;;)
    {
        if (aa == k)
            break;
        if (narry[kk] != narry[kk + 1])
        {
            aa += 1;
            kk++;
        }
    }

    cout << "The NO." << k << "number is:" << narry[sum - kk] << endl;
    cout << "And it's place is:" ;
    for (i = 0; i < sum; i++)
    {
    if (addr[i] == narry[sum - kk])
        cout << i << '\t';
    }

    return 0;
}
权重：较高

====
3、用递归算法判断数组a[N]是否为一个递增数组。
答：
递归的方法，记录当前最大的，并且判断当前的是否比这个还大，大则继续，否则返回false结束：
bool fun( int a[], int n )
{
    if( n == 1 )
    return true;
    if( n == 2 )
    return a[n-1] >= a[n-2];
    return fun(a, n-1) && ( a[n-1] >= a[n-2] );
}
权重：较高
备注：嵌入式使用递归要特别注意，事先预估好可能的递归次数，每次函数压栈时占用的空间，不要堆栈溢出了

====
5 设周期性任务P1,P2,P3的周期为T1,T2,T3分别为100，150，400；执行时间分别为20，40，100。请设计一种调度算法进行任务调度，满足任务执行周期及任务周期。
答：
1.  任务当然可以分段执行，不然P3执行时间100大于P1最大的间隔时间80（100-20，即从P1本次执行完毕到下次开始执行的间隔），无论如何都不可能。
2.  整个调度是可以循环的，即我们假设在一个时间轴上安排了一系列的任务运行，时间轴在某时刻与0时刻重合，这样就可以一直进行下去
权重：中




