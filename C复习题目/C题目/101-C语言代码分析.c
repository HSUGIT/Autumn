====
1 读程序段，回答问题
int main(int argc, char *argv[])
{
    int c = 9, d = 0;

    c = c++ % 5;
    d = c;
    printf("d=%d\n",d);

    return 0;
}
a) 写出程序输出
b) 在一个可移植的系统中这种表达式是否存在风险？why?
答：
1.程序输出为： 5
2.存在风险，因为： 因为c = c++ % 5;这个表达式对c有两次修改，行为未定义，c的值不确定
对于下面这句话的解释：
c = c++ % 5;
一些编译器会这么解读：
c % 5       //是4
c = (c % 5) //是4
c++         //变成5了

但是eclipse是这么解读的：
c % 5   //是4
(c++)   //作为一个表达式，这里c先被自增为5，但是表达式的结果还是4。
c = 4;  //把表达式再赋值给c，结果c又变回4
权重：中
备注：所以在可移植系统中，要注意编译环境和运行环境的区别，同样的代码可能有不同的结果，主机仿真的结果不一定是目标板运行的结果。 

====
#include <stdio.h>
int a = 0;
int b;
static char c;
int main(int argc, char *argv[])
{
    char d = 4;
    static short e;

    a++;
    b = 100;
    c = (char)++a;
    e = (++d)++;
    printf("a=%d, b=%d, c=%d, d= %d, e=%d", a, b, c, d, e);

    return 0;
}
a) 写出程序输出
b) 编译器如果安排各个变量(a,b,c,d)在内存中的布局(eg. stack,heap,data section,bss section), 最好用图形方式描述。
答：a = 2, b = 100, c = 2, d = 6, e = 5
程序编译后，生成一个map，动态分配内存放到堆中，函数内变量放在栈中，全局未初始化变量放在bss中，代码code、全局常量放在text中，
bss段：
　　bss段（bss segment）通常是指用来存放程序中未初始化的全局变量的一块内存区域。
　　bss是英文Block Started by Symbol的简称。
　　bss段属于静态内存分配。 
data段：
　　数据段（data segment）通常是指用来存放程序中已初始化的全局变量的一块内存区域。
　　数据段属于静态内存分配。
text段：
　　代码段（code segment/text segment）通常是指用来存放程序执行代码的一块内存区域。
　　这部分区域的大小在程序运行前就已经确定，并且内存区域通常属于只读(某些架构也允许代码段为可写，即允许修改程序)。
　　在代码段中，也有可能包含一些只读的常数变量，例如字符串常量等。 
堆（heap）：
　　堆是用于存放进程运行中被动态分配的内存段，它的大小并不固定，可动态扩张或缩减。
　　当进程调用malloc等函数分配内存时，新分配的内存就被动态添加到堆上（堆被扩张）；
　　当利用free等函数释放内存时，被释放的内存从堆中被剔除（堆被缩减）。
栈(stack)：
　　 栈又称堆栈，是用户存放程序临时创建的局部变量，
　　也就是说我们函数括弧“{}”中定义的变量（但不包括static声明的变量，static意味着在数据段中存放变量）。
　　除此以外，在函数被调用时，其参数也会被压入发起调用的进程栈中，并且待到调用结束后，函数的返回值也会被存放回栈中。
　　由于栈的先进先出(FIFO)特点，所以栈特别方便用来保存/恢复调用现场。
　　从这个意义上讲，我们可以把堆栈看成一个寄存、交换临时数据的内存区。 
一个程序本质上都是由 bss段、data段、text段三个组成的。
　　这样的概念，不知道最初来源于哪里的规定，但在当前的计算机程序设计中是很重要的一个基本概念。
　　而且在嵌入式系统的设计中也非常重要，牵涉到嵌入式系统运行时的内存大小分配，存储单元占用空间大小的问题。
    在采用段式内存管理的架构中（比如intel的80x86系统），bss段通常是指用来存放程序中未初始化的全局变量的一块内存区域，
　　一般在初始化时bss 段部分将会清零。bss段属于静态内存分配，即程序一开始就将其清零了。
    比如，在C语言之类的程序编译完成之后，已初始化的全局变量保存在.data 段中，未初始化的全局变量保存在.bss 段中。
　　text和data段都在可执行文件中（在嵌入式系统里一般是固化在镜像文件中），由系统从可执行文件中加载；
　　而bss段不在可执行文件中，由系统初始化。
权重：中
备注：系统移植开发需要手动配置堆栈大小，合理对内存的使用按照实际的使用进行分配。

====
13.下面这段代码的输出结果为：(A)
void change(int *a, int &b, int c)
{
    c = *a;
    b = 30;
    *a = 20;
}
int main()
{
    int a = 10, b = 20, c = 30;

    change(&a, b, c);
    printf(“%d,%d,%d,”, a, b, c);

    return 0;
}
A 20，30，30
B 10，20，30
C 20,30，10
D 10,30，30
解析：
该题考察函数传参问题。
1，指针传参 -> 将变量的地址直接传入函数，函数中可以对其值进行修改。
2，引用传参 -> 将变量的引用传入函数，效果和指针相同。
3，值传参 -> 在传参过程中，首先将c的值复制给函数c变量，然后在函数中修改的即是函数的c变量，然后函数返回时，系统自动释放变量c。而对main函数的c没有影响。
a为指针传递，b为引用传递，c为值传递。
*a = 20; b = 30; a和b的值确实发生了修改。而c只是将值复制到形参，在函数内的操作并不会影响c的实际值，因此c还是为原来的30.
权重：较低
备注：C语言实际使用只会用到指针传参

====
1. 写出函数执行的结果：
void join(int x) //递归运算
{
    x++;
    if (x >= 7) return;
    join(x);
    printf("%d", x); //注意别漏掉这个打印信息!
}

int main()
{
	int x = 3,y = 0;

	join(x);
	printf("OK\n");
	while (--x)
	{
		for(y = 0; y < 4; y++)
		{
			printf("x = %d,y = %d\n", x, y);
			if (y >= 1) break;
			else continue;
		}
	}
	printf("over!");
}
654OK
x = 2,y = 0
x = 2,y = 1
x = 1,y = 0
x = 1,y = 1
over!
权重：较高
备注：看得懂代码

====
8、定义函数时，缺省函数的类型声明，则函数类型取缺省类型
A.void
B.char
C.float
D.int
参考答案：D

====
36、 下面是一个16x16的黑白图标：
static unsigned short stopwatch[] = { 0x07c6, 0x1ff7, 0x383b, 0x600c, 0x600c, 0xc006, 0xc006,
0xdf06, 0xc106, 0xc106, 0x610c, 0x610c, 0x3838, 0x1ff0, 0x07c0, 0x0000, }; 
如何修改声明，可以使之在源代码中形象地表现出图形的模样。 
答：用二进制字符串代替16进制。但是C语言不直接支持二进制表示，需要写一些中间函数，将0x07c6存储成0b0000011111000110（字符串），使用时再用自写函数转换一遍。
权重：中
备注：可用于点阵图显示

====
1、 请写出下列代码的输出内容
#include <stdio.h>
int main(void)
{
	int a, b, c, d;
	a = 10;
	b = a++; // b=10 a=11
	c = ++a; // c=12 a=12
	d = 10 * a++; // d=120 a=13
	printf(“b，c，d：%d，%d，%d”，b，c，d）;
	
	return 0;
} 
答：b,c,d:10,12,120。
权重：较高
备注：考察自增自减

----
约定:
1) 下面的测试题中，认为所有必须的头文件都已经正确的包含了
2)数据类型 
char 一个字节 1 byte
int 两个字节 2 byte (默认16位系统，认为整型是2个字节)
long int 四个字节 4 byte
float 四个字节4 byet
double 八个字节 8 byte
long double 十个字节 10 byte
pointer 两个字节 2 byte(默认16位系统,地址总线只有16位)

====
2、 第1题: 考查对volatile关键字的认识
#include <setjmp.h>
static jmp_buf buf;
main()
{
    volatile int b; // 该值每次从硬件中直接读取，不为了效率从缓存中读取上次的值

    b = 3;
    if (setjmp(buf) != 0) { // setjmp : 设置非局部跳转 /* setjmp.h */ 
        printf("%d ", b);
        exit(0);
    }
    b = 5;  
    longjmp(buf , 1);
}
请问，这段程序的输出是 (a) 3  (b) 5  (c) 0  (d)以上均不是 
答案b；
权重：较低

第1题: (b)
volatile字面意思是易于挥发的。这个关键字来描述一个变量时，意味着 给该变量赋值(写入)之后，马上再读取，写入的值与读取的值可能不一样,所以说它"容易挥发"的。
这是因为这个变量可能一个寄存器，直接与外部设备相连，你写入之后，该寄存器也有可能被外部设备的写操作所改变; 该变量随时会被一个中断程序，或另一个进程
改变了.
volatile 不会被编译器优化影响，在longjump 后,它的值 是后面假定的变量值,b最后的值是5,所以5被打印出来.

setjmp : 设置非局部跳转 /* setjmp.h*/
Stores context information such as register values so that the lomgjmp function can return control to the statement following the one calling setjmp.Returns 0 when it is initially called.

Lonjjmp: 执行一个非局部跳转 /* setjmp.h*/
Transfers control to the statement where the call to setjmp (which initialized buf) was made. Execution continues at this point as if longjmp cannot return the value 0.A nonvolatile automatic variable might be changed by a call to longjmp.When you use setjmp and longjmp, the only automatic variables guaranteed to remain valid are those declared volatile.

Note: Test program without volatile qualifier (result may very)
更详细介绍，请参阅 C语言的setjmp和longjmp

====
3、第2题:考查类型转换
main(){
    struct node {
        int a;
        int b;
        int c;
    }; // 结构体的成员在内存中的地址是按照他们定义的位置顺序依次增长的
    struct node s = { 3, 5, 6 };
    struct node *pt = &s;
    printf("%d" ,  *(int*)pt);  
}
这段程序的输出是: (a) 3 (b) 5 (c) 6 (d) 7
答案：a
权重：高
备注：理解结构体和取址

第2题: (a)
结构题的成员在内存中的地址是按照他们定义的位置顺序依次增长的。如果一个结构体的指针被看成它的第一个成员的指针,那么该指针的确指向第一个成员

====
4、第3题:考查递归调用
int foo (int x, int n)
{
   int val;
   val = 1;

   if ( n > 0) {
       if (n%2 == 1) val = val *x; // 如果是奇数次幂, x(val)要先乘上一次
       val = val * foo(x*x, n / 2);
   }
 
   return val;
}
这段代码对x和n完成什么样的功能(操作)? (a) x^n (x的n次幂) (b) x*n(x与n的乘积) (c) n^x(n的x次幂) (d) 以上均不是
答案：a，用一两个数代进去算一下可以得出结果。
权重：中
备注：嵌入式中计算少用递归，堆栈太小会溢出。

第3题: (a)
这个程序的非递归版本 
int what ( int x , int n)
{
    int val;
    int product;
    product = 1;
    val = x;

    while (n > 0)
    {
        if (n%2 == 1) 
        product = product * val; /*如果是奇数次幂, x(val)要先乘上一次,; 偶数次幂,最后返回时才会到这里乘以1*/
        val = val * val; 
        n = n / 2; 
    }
    return product;
}
/* 用二元复乘策略 */
算法描述
(while n > 0) 
{
    if next most significant binary digit of n( power) is one
    then multiply accumulated product by current val , 
    reduce n(power) sequence by a factor of two using integer division .
    get next val by multiply current value of itself 
}

====
5、第4题:考查指针
void main(void)
{
    int a[5] = {1, 2, 3, 4, 5};
    int *ptr =  (int *)(&a + 1); // &a取址后以a[0-4]整个数组为步进，a以a[0]也就是int为步进
    printf("%d %d" , *(a + 1), *(ptr - 1));
}
这段程序的输出是: (a) 2 2 (b) 2 1 (c) 2 5  (d) 以上均不是
答案：c
权重：较高
备注：需要知道数组取址后的涵义，因为实际中会用到
    之所以写成void main(void){} 而不写成main(){} 是要告诉别人你就是要用void，而不是你写代码时遗漏了

第4题: (c)
a的类型是一个整型数组,它有5个成员
&a的类型是一个整型数组的指针
所以&a + 1指向的地方等同于 a[6]

所以*(a+1) 等同于a[1]
ptr等同 a[6], ptr-1就等同与a[5]

====
6、第5题:考查多维数组与指针
void foo(int [][3]);
void main(void)
{
    int a [3][3]= { { 1,2,3}, {4,5,6}, {7,8,9} };
    foo(a);
    printf("%d", a[2][1]);
}
void foo(int b[][3])
{
   ++ b;
   b[1][1] = 9;
}
这段程序的输出是:  (a) 8 (b) 9 (c) 7  (d)以上均不对 
答案：b
权重：较高
备注：需要知道数组取址后的涵义，因为实际中会用到

第5题: (b)
题目自身就给了足够的提示
b[0][0] = 4
b[1][0] = 7

====
7、第6题目:考查逗号表达式
void main(void)
{
    int a, b, c, d;

    a = 3;
    b = 5;
    c = a, b;   // 逗号表达式的优先级最低
    d = (a, b); // 逗号表达式的值是最右边的值
    printf("c=%d", c);
    printf("d=%d", d);
}
这段程序的输出是:(a) c=3 d=3 (b) c=5 d=3 (c) c=3 d=5 (d) c=5 d=5
答案：c
权重：中
备注：逗号操作符在实际工作中会用到，用于简写代码

第6题: (c)
考查逗号表达式,逗号表达式的优先级是很低的，比赋值(=)的优先级低. 逗号表达式的值就是最后一个元素的值
逗号表达式的还有一个作用就是分割函数的参数列表..

E1, E2, ..., En
上面这个表示式的左右是,E1, E2,... En的值被分别计算出来，En计算出来的结构赋给整个逗号表达式 
c=a,b; / *yields c=a* /
d=(a,b); /* d =b */

====
8、第7题:考查指针数组 
void main(void) 
{
    int a[][3] = {1, 2, 3, 4, 5, 6};
    int (*ptr)[3] = a;  // 指针数组ptr为123，ptr+1为456，ptr+2为非法的不确定
    printf("%d %d ", (*ptr)[1], (*ptr)[2]);
    ++ptr;
    printf("%d %d", (*ptr)[1], (*ptr)[2]);
}  
这段程序的输出是:   (a) 2 3 5 6 (b) 2 3 4 5 (c) 4 5 0 0 (d) 以上均不对
答案：a
权重：较高
备注：指针和数组都是嵌入式中用得非常多的

第7题: (a)
ptr是一个数组的指针，该数组有3个int成员

====
9、第8题:考查函数指针 
int *f1(void) 
{
    int x =10;
    return (&x);    // 函数内的变量退出后会释放
}   
int *f2(void) 
{
   int *ptr;
   *ptr = 10;       // 指针指向常量
   return ptr;      // 函数内的常量指针也不要返回
}
int *f3(void) 
{
   int *ptr;
   ptr = (int *)malloc(sizeof(int)); // 分配的内存记得取消就可以了
   return ptr; 
}  
上面这3个函数哪一个最可能引起指针方面的问题   (a) 只有 f3 (b) 只有f1 and f3 (c) 只有f1 and f2 (d) f1 , f2 ,f3
答案：c
权重：较高
备注：malloc后一定要free释放，实际工作中用的多

第8题: (c)
f1显然有问题，它返回一个局部变量的指针，局部变量是保存在stack中的,退出函数后，局部变量就销毁了，保留其指针没有意义，因为其指向的stack空间可能被其他变量覆盖了
f2也有问题, ptr是局部变量，未初始化，它的值是未知的，*ptr不知道指向哪里了，直接给*ptr赋值可能会覆盖重要的系统变量，这就是通常说的野指针的一种

====
10、第9题:考查自加操作(++) 
void main(void) 
{
   int i = 3;
   int j;  
   j = sizeof(++i + ++i); // sizeof中的表达式编译器不计算，记住就行，这是算int大小的
   printf("i=%d j=%d", i, j); 
} 
这段程序的输出是: (a) i=4 j=2 (b) i=3 j=2 (c) i=3 j=4 (d) i=3 j=6
答案：b（16位cpu）
权重：较低

第9题: (b)
sizeof 操作符给出其操作数需要占用的空间大小，它是在编译时就可确定的，所以其操作数即使是一个表达式，也不需要在运行时进行计算.( ++i + ++ i )是不会执行的，所以
i 的值还是3

====
11、第10题:考查形式参数，实际参数，指针和数组 
void f1(int *, int);  
void f2(int *, int);  
void (*p[2]) (int *, int); // 函数指针数组
void main(void) 
{
   int a;
   int b;

   p[0] = f1;
   p[1] = f2;
   a = 3;
   b = 5;
   p[0](&a, b); 
   printf("%d\t %d\t", a, b); // 5 5
   p[1](&a, b); 
   printf("%d\t %d\t", a, b); 
}   
void f1(int *p, int q) 
{
   int tmp;
   tmp = *p; // 3
   *p = q; // a = 5
   q = tmp; 
}  
void f2(int* p, int q) 
{
   int tmp;
   tmp = *p;
   *p = q;
   q = tmp; 
}    
这段程序的输出是: (a) 5 5 5 5 (b) 3 5 3 5 (c) 5 3 5 3 (d) 3 3 3 3 
答案：a
权重：中

第10题: (a)
很显然选a.
f1交换*p 和 q的值，f1执行完后, *p 和 q的值的确交换了, 但 q的改变不会影响到 b的改变, *p 实际上就是 a 
所以执行f1后, a=b=5
这道题考查的知识范围很广,包括typedef自定义类型,函数指针,指针数组
void(*p[ 2 ]) (int *, int);
定义了一个函数指针的数组p,p有两个指针元素. 元素是函数的指针，函数指针指向的函数是一个带2个参数,返回void的函数，所带的两个参数是 指向整型的指针，和整型
p[ 0 ] = f1; p[ 1 ] = f2 contain address of function .function name without parenthesis represent address of function Value and address of variable is passed to function only argument that is effected is a (address is passed). Because of call by value f1, f2 can not effect b

====
12、第11题:考查自减操作(--) 
void e(int);     
void main(void) 
{
   int a;
   a = 3;
   e(a); 
}   
void e(int n) 
{
   if (n > 0) {
       e(--n);
       printf("%d", n);
       e(--n);   
   } 
}  
这段程序的输出是:   (a) 0 1 2 0 (b) 0 1 2 1 (c) 1 2 0 1 (d) 0 2 1 1
答案：a
权重：中
备注：在纸上推演一下

第11题: (a)
考查--操作和递归调用,仔细分析一下就可以了

====
13、第13题:数组与指针的区别与联系 
void main(void) 
{
   char p;
   char buf[10] = {1, 2, 3, 4, 5, 6, 9, 8};
   p = (buf + 1)[5];
   printf("%d" , p); 
}  
这段程序的输出是:  (a) 5 (b) 6 (c) 9  (d) 以上都不对
答案：c
权重：高
备注：指针很重要，数组名也重要，数组名自增就是移到其中元素的下一位

第13题: (c)
考查什么时候数组就是指针.对某些类型T而言，如果一个表达式是 T[] (T的数组), 这个表达式的值实际上就是指向该数组的第一个元素的指针.所以(buf+1)[5]实际上就是*(buf +6)或者buf[6]

====
14、第14题: 考查指针数组的指针 
void f(char **);  
void main(void)
{
    char *argv[] = {"ab", "cd", "ef", "gh", "ij", "kl"}; // argv是指针数组
    f(argv); 
}   
void f(char **p) // p是指针数组，*p是一个字符串的指针，**p是字符串中第一个字符
{
    char *t; 
    t = (p += sizeof(int))[-1];
    printf("%s", t); 
}  
这段程序的输出是:  (a) ab (b) cd (c) ef(d) gh
答案：b
权重：较高
备注：这里的默认是16位系统，sizeof(int)是2，要理解p+2之后指向"ef"，再[-1]后再指向"cd"

第14题: (b)
sizeof(int)的值是2,所以p+=sizeof(int) 指向 argv[2],这点估计大家都没有什么疑问
(p+=sizeof(int))[-1] 指向 argv[1],能理解吗，因为(p+=sizeof(int))[-1] 就相当于 (p+=2)[-1] ,也就是(p+2-1)

====
15、第15题:此题考查的是C的变长参数,就像标准函数库里printf()那样 
#include <stdarg.h> 
int ripple(int, ...);  
void main(void)
{
    int num;
    num = ripple(3, 5, 7); // 3不是第一个参数，3是参数的总个数，第一个参数为5
    printf("%d", num); 
}
int ripple(int n, ...) 
{
    int i, j;
    int k;  
    va_list p;  
    k = 0;
    j = 1;
    va_start(p, n);      
    for (; j < n; ++j) {        // 注：自己写代码时把j=1放到for表达式里，不要让人误以为你是代码写漏了
        i = va_arg(p, int);     // 第一次取出5，第二次取出7
        for (; i; i &= i-1)     // 循环次数为数字中有过少个1
            ++k;
    }
    return k; 
}  
这段程序的输出是:  (a) 7 (b) 6 (c) 5 (d) 3
答案：c
权重：较高
备注：实际工作中经常会用到，例如自定义不同级别的调试输出

第15题: (c)
在C编译器通常提供了一系列处理可变参数的宏，以屏蔽不同的硬件平台造成的差异，增加程序的可移植性。这些宏包括va_start、 va_arg和va_end等。 
采用ANSI标准形式时，参数个数可变的函数的原型声明是： 
type funcname(type para1, type para2, ...) 
这种形式至少需要一个普通的形式参数，后面的省略号不表示省略，而是函数原型的一部分。type是函数返回值和形式参数的类型。
不同的编译器，对这个可变长参数的实现不一样 ，gcc4.x中是内置函数.
关于可变长参数,可参阅 
http://www.upsdn.net/html/2004-11/26.html
http://www.upsdn.net/html/2004-11/24.html

程序分析
va_list p; /*定义一个变量 ,保存 函数参数列表 的指针*/
va_start( p , n); /*用va_start宏 初始化 变量p, 
    va_start宏的第2个参数n ,
    是一个固定的参数,
    必须是我们自己定义的变长函数的最后一个入栈的参数
    也就是调用的时候参数列表里的第1个参数*/
for (; j<n; ++j) /* j从1开始, 遍历所有可变参数 */
{
    i = va_arg( p , int);   /*va_arg取出当前的参数, 并认为取出的参数是一个整数(int) */
    for (; i; i &=i-1 )     /*判断取出的i是否为0*/
        ++k;                /* 如果i不为0, k自加, i与i-1进行与逻辑运算, 直到i 为0这是一个技巧，下面会谈到它的功能*/
}
当我们调用ripple函数时，传递给ripple函数的 参数列表的第一个参数n的值是3 .
va_start 初始化 p士气指向第一个未命名的参数(n是有名字的参数) ,也就是 is 5 (第一个).
每次对 va_arg的调用，都将返回一个参数，并且把 p 指向下一个参数.
va_arg 用一个类型名来决定返回的参数是何种类型,以及在 var_arg的内部实现中决定移动多大的距离才到达下一个 参数
(; i; i&=i-1) k++ /* 计算i有多少bit被置1 */

5用二进制表示是 (101) 2
7用二进制表示 (111) 3
所以 k 返回 5(2+3),也即本题应该选c

举个例子，就很好理解了
令 i= 9 = 1001
i-1 = 1000 
(i-1) +1 = i
1000
+1
1 001
因为i与i-1的最右边的那位(最低位) 肯定是不同，如果i1,i-1肯定是0，反之亦然. i & i-1 这个运算，在二相补的数字系统中，将会 消除最右边的1位

====
16、第16题:考查静态变量的知识 
int counter (int i) 
{
    static int count = 0; // 函数内静态变量函数退出后值会保持，且不会再次初始化
    count = count + i;
    return (count); 
} 
void main(void)
{  
     int i, j;
     for (i = 0; i <= 5; i++)
         j = counter(i); // 0-5等加数列=3*（0+5）
}  
本程序执行到最后,j的值是:(a) 10 (b) 15 (c) 6 (d) 7
答案：b
权重：高
备注：静态变量必须掌握，用的多

第16题: (b)
答案是 (b)
这道题考查的是静态变量的知识,当每次调用完函数之后,静态变量的值不会丢失,这与栈中的临时局部变量明显不同的地方.
所以,第一次调用counter(0)之后,count =0
第二次调用 counter(1)后 count = 0+1;
第三次调用 counter(2) count = 1+2; /* count = count +i */
第四次调用 counter(3) count = 3+3;
第五次调用 counter(4) count = 6+4;
第六次调用 counter(5) count = 10+5;
命题人信息 Ashok K. Pathak a member ( Research Staff ) at Bharat Electronics Limited (CRL) , Ghaziabad. He has been developing embedded application for the past five years .Ashok holds a M.E in computer science and engineering . Ashok recently completed a book about' "Advanced Test in C and Embedded System Programming" , Published by BPB , ND . 

====
17、设
#define N 3
#define Y(n) ((N+1)*n)  // 注：小n本应该在周围放上小括号，自己写代码时要注意
则表达式2*(N+Y(5+1))的值是
A.42
B.48
C.54
D.出错
参考答案：B Y(5+1) 传递过去的应该是6，而不是简单的把5+1给替换掉
权重：中
备注：宏定义函数应该把参数用括号括起来

====
18、下列转义字符中错误的是
A.′\000′
B.′\14′
C.′\x111′// 十六进制只有两个数
D.′\2′
参考答案：C error C2022: '273' : too big for character
权重：中

====
19、下面的代码输出是什么，为什么？ 
void foo(void)
{ 
    unsigned int a = 6;
    int b = -20;
    (a + b > 6) ? puts("> 6") : puts("<= 6");
}
权重：中
备注：测试是否懂得C语言中的整数自动转换原则。无符号整型问题的答案是输出是 “>6”。原因是当表达式中存在有符号类型和无符号类型时所有的操作数都自动转换为无符号类型。因此-20变成了一个非常大的正整数，所以该表达式计算出的结果大于6。这一点对于应当频繁用到无符号数据类型的嵌入式系统来说是丰常重要的。

====
选择题
1:设float a=2, b=4, c=3；，以下C语言表达式与代数式 (a+b)+c计算结果不一致的是
A.(a+b)*c/2
B.(1/2)*(a+b)*c
C.(a+b)*c*1/2
D.c/2*(a+b)
参考答案：B，因为a,b,c三个变量都是浮点数，所以在B答案中其结果是0，因为在计算1/2是就是0，如果改成1/2.0就正确了。
权重：高
备注：自己写代码时要注意避免整数相除之后变成0

====
3:下述程序执行后的输出结果是
void main(void)
{
    int x = 'f';
    printf("%c\n", 'a' + (x -'a' + 1));
}
A.g
B.h
C.i
D.j
参考答案：A
权重：较高
备注：了解ASCII的存储规则

====
4:C语言中，下列运算符优先级最高的是
A.！
B.％
C.>>
D.==
参考答案：A
权重：中
备注：单目运算符优先级更高

====
5:数组定义为“ int a [ 4 ] ; ”，表达式 ( ) 是错误的。
A.*a
B.a [ 0 ]
C.a
D.a++
参考答案：D
权重：中
备注：不能自加，只能加1，因为+1是加一个(int)大小地址偏移

====
6:执行语句“ k=7>>1; ”后，变量 k 的当前值是
A.15
B.31
C.3
D.1
参考答案：C
权重：较高
备注：右移相当于除以2

====
9:若有宏定义：#define MOD(x，y) x％y
则执行以下语句后的输出结果是
int a=13，b=94；
printf(″％d\n″，MOD(b，a+4))；
A.5
B.7
C.9
D.11
参考答案：B
权重：较高
备注：主要考宏定义函数需要给参数加上括号，不加会产生错误计算结果

====
10:下列各个错误中，哪一个不属于编译错误
A.改变 x 原值 3 为 5 ，写作“ x==5 ;”
B.花括号不配对
C.复合语句中的最后一条语句后未加分号
D.变量有引用、无定义
参考答案：A
权重：重
备注：编译时是否报错

====
11:下列程序段运行后， x 的值是( )
a = 1; b = 2; x = 0;
if (!(--a)) x--;
if (!b) x=7; else ++x;
A.0
B.3
C.6
D.7
参考答案：A
权重:中
备注：自增放在变量前面：先自加再使用；放在后面：先使用再自加

====
17:表达式 strcmp( “ 3.14 ”，“ 3.278 ” ) 的值是一个
A.非零整数
B.浮点数
C.0
D.字符
参考答案： A
权重：较高
备注：记住大多数string.h中的函数用法，常用的strlen strstr strcmp strcat strcpy...

====
18:设struct
{
    short a;
    char b;
    float c;
} cs;
则sizeof(cs)的值是
A.4
B.5
C.6
D.7
参考答案： D
权重：较高
备注：其实答案应该是8，因为一般都是默认有字节对齐，字节不对齐的情况需要显示声明。
需要了解如何将结构体按不同的字节对其，特别是使用在通讯链路中的数据

19:若变量已正确定义，表达式( j=3 ， j++ )的值是
A.3
B.4
C.5
D.0
参考答案：A
权重：较高
备注：理解逗号运算符

====
简答题
24:
void main(void)
{
    int c;

　　  while ((c = getchar()) != '\n')
　　  switch (c - '2')
    {
    case 0:
　　  case 1: putchar(c+4); break;
　　  case 2: putchar(c+4); break;
　　  case 3: putchar(c+3); break;
　　  default:putchar(c+2); break;
　　  }

　　  printf("\n");
}
运行时输入： 2473 ，输出结果：
参考答案：6897
权重：中

====
29:执行下述程序的输出结果是  ABCDEFCDEFEF  。
char b[]= "ABCDEF";
void main(void)
{
    char *bp;
    for (bp = b; *bp; bp += 2)
        printf("%s",bp);
    printf("\n");
}
权重：中

====
1.
#define pi 3.14
#define Area(R) pi*R*R //考察R应该加括号，不加括号会出错
void main(void)
{
    int r1 = 5, r2 = 2;
    double s = 0;
    s = Area(r1 - r2);
    printf("The area is %f",s);
}
求结果： The area is 3.700000
权重：中

====
2.函数 int compare(int a,int b),定义该函数的函数指针P
答：int(*p)(int, int);
p = compare;
权重：高
备注：需要掌握函数指针

====
4、将整数转换为字符串
答：
#include <stdio.h>
#include <string.h>
void reverse(char s[])
{ //字符串反转

    int c, i = 0, j;
    for(j = strlen(s) - 1; i < j; j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
        i++;
    }
}
void IntegerToString(char s[], int n)
{
    int i = 0, sign;
    if((sign = n) < 0)  //如果是负数，先转成正数 
        n = -n;
    do //从个位开始变成字符,直到最高位,最后应该反转
    {
        s[i++] = n % 10 + '0';
    } while((n = n / 10) > 0);

    //如果是负数，补上负号
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';//字符串结束

    reverse(s);
}
void main(void)
{
    int m;
    char c[100];
    m = 215;
    IntegerToString(c, m);
    printf("integer = %d string = %s\n", m, c);
}
权重：较高

====
5、字符串转换为整数
答：
#include <stdio.h>
#include <string.h>
int Atoi(char str[])
{
    int i;
    int weight = 1; // 权重
    int rtn = 0; // 用作返回

    for(i = strlen(str) - 1; i >= 0; i--)
    {
        rtn += (str[i] - '0') * weight;
        weight *= 10; // 增重
    }

    return rtn;
}
void main(void)
{
    char str[32];

    printf("Input a string :");
    gets(str);
    printf("%d\n", Atoi(str));
}
权重：高
备注：知道‘0’字符可以直接也表示0所代表的ASCII码

====
6、将一个字符串逆序 
答： 
#include <stdio.h>
#include <string.h>
char *strconv(char *p)
{
    int length = strlen(p);
    char *ptr = p;
    char *ptr_1 = p + length -1;
    while(ptr < ptr_1)
    {
    char c = *ptr;
    *ptr = *ptr_1;
    *ptr_1 = c;
    ++ptr;
    --ptr_1;
    }
    return p;
}
int main(void)
{
    char str[] = "abcdef1234";
    char *p;
    p = strconv(str);
    printf("%s",p);
    return 1;
}
权重：高
备注：实际工作中经常需要对字符串进行各种操作

====
4.分析下面的程序，并且得出结果
struct s1 
{
    int i: 8; 
    int j: 4; 
    int a: 3; 
    double b; 
}; 
struct s2 
{ 
    int i: 8; 
    int j: 4; 
    double b; 
    int a: 3; 
}; 
printf("sizeof(s1)= %d\n", sizeof(s1)); 
printf("sizeof(s2)= %d\n", sizeof(s2)); 
result: 16, 24 
解析：
第一个struct s1 
{ 
    int i: 8; 
    int j: 4; 
    int a: 3; 
    double b; 
}; 
理论上是这样的，首先是i在相对0的位置，占8位一个字节，然后，j就在相对一个字节的位置，由于一个位置的字节数是4位的倍数，因此不用对齐，就放在那里了，然后是a，要在3位的倍数关系的位置上，因此要移一位，在15位的位置上放下，目前总共是18位，折算过来是2字节2位的样子，由于double是8 字节的，因此要在相对0要是8个字节的位置上放下，因此从18位开始到8个字节之间的位置被忽略，直接放在8字节的位置了，因此，总共是16字节。 
1. 一个位域必须存储在同一个字节中，不能跨两个字节。如一个字节所剩空间不够存放另一位域时，应从下一单元起存放该位域。也可以有意使某位域从下一单元开始。例如：    
struct bs   
{   
    unsigned a:4   
    unsigned :0 /*空域*/   
    unsigned b:4 /*从下一单元开始存放*/   
    unsigned c:4   
}   
在这个位域定义中，a占第一字节的4位，后4位填0表示不使用，b从第二字节开始，占用4位，c占用4位。 
2. 由于位域不允许跨两个字节，因此位域的长度不能大于一个字节的长度，也就是说不能超过8位二进位
3. 位域可以无位域名，这时它只用来作填充或调整位置。无名的位域是不能使用的。例如：  
struct k   
{   
    int a:1   
    int :2 /*该2位不能使用*/   
    int b:3   
    int c:2   
};   
从以上分析可以看出，位域在本质上就是一种结构类型， 不过其成员是按二进位分配的。
权重：高
备注：在通讯协议中对数据处理经常会精确到位。

====
5.在对齐为4的情况下 分析下面程序的结果
struct BBB 
{ 
    long num； 
    char *name; 
    short int data; 
    char ha; 
    short ba[5]; 
} *p; 
p = 0x1000000; 
p + 0x200 = ____; 
(Ulong)p + 0x200 = ____; 
(char*)p + 0x200 = ____; 
解答：假设在32位CPU上， 
sizeof(long) = 4 bytes 
sizeof(char *) = 4 bytes 
sizeof(short int) = sizeof(short) = 2 bytes 
sizeof(char) = 1 bytes 
由于是4字节对齐， 
sizeof(struct BBB) = sizeof(*p) 
= 4 + 4 + 2 + 1 + 1/*补齐*/ + 2*5 + 2/*补齐*/ = 24 bytes
p = 0x1000000; 
p + 0x200 = ____; 
= 0x1000000 + 0x200*24   指针加法，加出来的是指针类型的字节长度的整倍数。就是p偏移sizeof(p)*0x200.
(Ulong)p + 0x200 = ____;
= 0x1000000 + 0x200   经过ulong后，这已经不再是指针加法，而变成一个数值加法了
(char *)p + 0x200 = ____; 
= 0x1000000 + 0x200 * 1  结果类型是char*，这儿的1是char的数据类型是1字节
权重：高
备注：需要理解结构体的数据存储规则和对齐规则，知道怎么手动按1字节对齐、2字节对齐、4字节对齐

====
6.分析一下下面程序的输出结果
#include <iostream.h>
#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
typedef struct AA
{
    int b1:5;
    int b2:2;
} AA;
void main(void)
{
    AA aa;
    char cc[100];
    strcpy(cc, "0123456789abcdefghijklmnopqrstuvwxyz");
    memcpy(&aa, cc, sizeof(AA));
    cout << aa.b1 <<endl;
    cout << aa.b2 <<endl;
}
答案： -16和１
首先sizeof(AA)的大小为4,b1和b2分别占5bit和2bit.
经过strcpy和memcpy后,aa的4个字节所存放的值是:
0,1,2,3的ASC码，即00110000,00110001,00110010,00110011
所以，最后一步：显示的是这４个字节的前５位，和之后的２位
分别为：10000,和01
因为int是有正负之分,所以是-16和1
权重：较高

====
7.改错：
#include <stdio.h>
int main(void) {
    int **p;
    int arr[100];
    p = &arr;
    return 0;
}
答案：
int **p; //二级指针
&arr; //得到的是指向第一维为100的数组的指针
应该这样写
#include <stdio.h>
int main(void)
{
    int **p, *q;
    int arr[100];
    q = arr;
    p = &q;
    return 0;
}
权重：高
备注：数组名是指向整个数组，对数组名取址，还是指向整个数组，采用+1运算时步进是一样的

====
10.写出运行结果
#include <stdio.h>
#include <string.h>

#define STRCPY(a, b) strcpy(a##_p, #b)
#define STRCPY1(a, b) strcpy(a##_p, b##_p)
int main(void)
{
    char var1_p[20];
    char var2_p[30];

    strcpy(var1_p, "aaaa");
    strcpy(var2_p, "bbbb");

    STRCPY1(var1, var2);
    STRCPY(var2, var1);

    printf("var1 = %s\n", var1_p);
    printf("var2 = %s\n", var2_p);

    return 0;
}
答案：var1 = bbbb
var2 = var1
宏中"#"和"##"的用法
权重：高
备注：需要知道宏定义中直接将变量名变成字符串#，和将两个变量名拼接成字符串的用法##，实际工作中会用
扩展阅读：
一、一般用法
我们使用#把宏参数变为一个字符串,用##把两个宏参数贴合在一起.
用法:
#include <cstdio>
#include <climits>
using namespace std;
#define STR(s) #s
#define CONS(a,b) int(a##e##b)
int main(void)
{
    printf(STR(vck)); // 输出字符串"vck"
    printf("%d\n", CONS(2,v3)); // 2e3 输出:2000
    return 0;
}
二、当宏参数是另一个宏的时候
需要注意的是凡宏定义里有用'#'或'##'的地方宏参数是不会再展开.
1, 非'#'和'##'的情况
#define TOW (2)
#define MUL(a,b) (a*b)
printf("%d*%d=%d\n", TOW, TOW, MUL(TOW,TOW));
这行的宏会被展开为：
printf("%d*%d=%d\n", (2), (2), ((2)*(2)));
MUL里的参数TOW会被展开为(2).
2, 当有'#'或'##'的时候
#define A (2)
#define STR(s) #s
#define CONS(a,b) int(a##e##b)
printf("int max: %s\n", STR(INT_MAX)); // INT_MAX #include<climits>
这行会被展开为：
printf("int max: %s\n", "INT_MAX");
printf("%s\n", CONS(A, A)); // compile error
这一行则是：
printf("%s\n", int(AeA));
A不会再被展开, 然而解决这个问题的方法很简单. 加多一层中间转换宏.
加这层宏的用意是把所有宏的参数在这层里全部展开, 那么在转换宏里的那一个宏(_STR)就能得到正确的宏参数.
#define A (2)
#define _STR(s) #s
#define STR(s) _STR(s) // 转换宏
#define _CONS(a,b) int(a##e##b)
#define CONS(a,b) _CONS(a,b) // 转换宏
printf("int max: %s\n", STR(INT_MAX)); // INT_MAX,int型的最大值，为一个变量
#include<climits>
输出为: int max: 0x7fffffff
STR(INT_MAX) --> _STR(0x7fffffff) 然后再转换成字符串；
printf("%d\n", CONS(A, A));
输出为：200
CONS(A, A) --> _CONS((2), (2)) --> int((2)e(2))

====
1. 找错
试题1：
void test1(void)
{
    char string[10];
    char *str1 = "0123456789";
    strcpy(string, str1);
}
test1: 字符串str1需要11个字节才能存放下(包括末尾的'\0')，而string只有10个字节的空间，strcpy会导致数组越界
权重：高
备注：常用

==== 
试题2：
void test2(void)
{
    char string[10], str1[10];
    for(i = 0; i < 10; i++)
    {
        str1[i] = 'a';
    }
    strcpy(string, str1);
}
test2: 如果面试者指出字符数组str1不能在数组内以‘\0’结束可以给3分；如果面试者指出strcpy(string, str1)调用使得从str1内存起复制到string内存起所复制的字节数具有不确定性可以给7分，在此基础上指出库函数strcpy工作方式的给10分
权重：高
备注：要时刻注意字符串应该以‘\0’也就是0x0来结尾

====
试题3：
void test3(char *str1)
{
    char string[10];
    if(strlen(str1) <= 10)
    {
        strcpy(string, str1);
    }
}
解答：
test3: if(strlen(str1) <= 10)应改为if(strlen(str1) < 10)，因为strlen的结果未统计'\0'所占用的1个字节
剖析：
考查对基本功的掌握：
(1)字符串以'\0'结尾；
(2)对数组越界把握的敏感度；
(3)库函数strcpy的工作方式

====
找错
试题4：
void GetMemory( char *p )
{
    p = (char *) malloc( 100 );
}
void Test( void ) 
{
    char *str = NULL;
    GetMemory( str );
    strcpy( str, "hello world" );
    printf( str );
}
解答：
试题4传入中GetMemory( char *p )函数的形参为字符串指针，在函数内部修改形参并不能真正的改变传入形参的值，执行完char *str = NULL;  GetMemory( str ); 后的str仍然为NULL；
权重：高
备注：形参不会改变实参

====
试题5：
char *GetMemory( void )
{ 
    char p[] = "hello world"; 
    return p; 
}

void Test( void )
{ 
    char *str = NULL; 
    str = GetMemory();
    printf( str ); 
}
试题5中 char p[] = "hello world";  return p; 的p[]数组为函数内的局部自动变量，在函数返回后，内存已经被释放。这是许多程序员常犯的错误，其根源在于不理解变量的生存期。
权重：高

====
试题6：
void GetMemory( char **p, int num )
{
    *p = (char *) malloc( num );
}

void Test( void )
{
    char *str = NULL;
    GetMemory( &str, 100 );
    strcpy( str, "hello" );
    printf( str ); 
}
试题6的GetMemory避免了试题4的问题，传入GetMemory的参数为字符串指针的指针，但是在GetMemory中执行申请内存及赋值语句
*p = (char *) malloc( num );后未判断内存是否申请成功，应加上：
if ( *p == NULL )
{
　...//进行申请内存失败处理
}
权重：高
备注：会用malloc和free

====
试题7：
void Test( void )
{
    char *str = (char *) malloc( 100 );
    strcpy( str, "hello" );
    free( str );
      //省略的其它语句
}
试题7存在与试题6同样的问题，在执行char *str = (char *) malloc(100); 后未进行内存是否申请成功的判断；另外，在free(str)后未置str为空，导致可能变成一个“野”指针，应加上：str = NULL; 试题6的Test函数中也未对malloc的内存进行释放。
剖析：
试题4～7考查面试者对内存操作的理解程度，基本功扎实的面试者一般都能正确的回答其中50~60的错误。但是要完全解答正确，却也绝非易事。
对内存操作的考查主要集中在：
(1) 指针的理解；
(2) 变量的生存期及作用范围；
(3) 良好的动态内存申请和释放习惯。
权重：高

====
再看看下面的一段程序有什么错误：
swap( int* p1, int* p2 )
{
    int *p;
　   *p = *p1;
　   *p1 = *p2;
　   *p2 = *p;
}
答：p未指向实际的存储空间，应该这样写：
swap( int* p1, int* p2 )
{
　   int p;
　   p = *p1;
　   *p1 = *p2;
　   *p2 = p;
}
权重：较高

====
15.
unsigned char *p1;
unsigned long *p2;
p1=(unsigned char *)0x801000;
p2=(unsigned long *)0x810000;
请问
p1+5=______;
p2+5=______;
答案：801005；810014。不要忘记了这个是16进制的数字，p2要加20变为16进制就是14
权重：高
备注：理解指针加法的步进

====
16、设有以下说明和定义：
typedef union {long i; int k[5]; char c;} DATE;
struct data { int cat; DATE cow; double dog;} too;
DATE max;
则语句 printf("%d",sizeof(too)+sizeof(max));的执行结果是：______
答：DATE是一个union, 变量公用空间. 里面最大的变量类型是int[5], 占用20个字节. 所以它的大小是20
data是一个struct, 每个变量分开占用空间. 依次为int4 + DATE20 + double8 = 32.
所以结果是 20 + 32 = 52.
当然...在某些16位编辑器下, int可能是2字节,那么结果是 int2 + DATE10 + double8 = 20
权重：高
备注：理解结构体占用存储空间的逻辑

====
华为笔试题 
1.写出判断ABCD四个表达式的是否正确, 若正确, 写出经过表达式中 a的值(3分)
int a = 4;
(A)a += (a++); (B) a += (++a) ;(C) (a++) += a;(D) (++a) += (a++);
a = ?
答：C错误，左侧不是一个有效变量，不能赋值，可改为(++a) += a;
改后答案依次为9,10,10,11
权重：较低

====
2.某32位系统下, C++程序，请计算sizeof 的值(5分).
char str[] = “http://www.ibegroup.com/”
char *p = str ;
int n = 10;
请计算
sizeof (str ) = ？（1）
sizeof ( p ) = ？（2）
sizeof ( n ) = ？（3）
void Foo ( char str[100]){
    // 请计算
    sizeof( str ) = ？（4）// 形参是指针，是4个字节
}
void *p = malloc( 100 ); // p是指针
请计算
sizeof ( p ) = ？（5）
答：（1）25 （2）4 （3） 4 （4）4 （5）4
权重：高
备注：理解sizeof的规则

====
4. 回答下面的问题(6分)
(1).
void GetMemory(char **p, int num){
    *p = (char *)malloc(num);
}
void Test(void){
    char *str = NULL;
    GetMemory(&str, 100);
    strcpy(str, "hello");
    printf(str);
}
请问运行Test 函数会有什么样的结果？
答：输出“hello”
权重：中

====
(2). void Test(void){
    char *str = (char *) malloc(100);
    strcpy(str, “hello”);
    free(str);
    if(str != NULL){
        strcpy(str, “world”);
        printf(str);
    }
}
请问运行Test 函数会有什么样的结果？
答：输出“world”
权重：较低
备注：被释放的指针所拥有空间原理上是可以被使用的，只是如果修改了，而这块内存被已有的程序使用，可能程序跑飞。

====
(3). char *GetMemory(void){
    char p[] = "hello world";
    return p;
}
void Test(void){
    char *str = NULL;
    str = GetMemory();
    printf(str);
}
请问运行Test 函数会有什么样的结果？
答：无效的指针，输出不确定
权重：高

====
20 int i=10, j=10, k=3; k*=i+j; k最后的值是？
答：60，此题考察优先级，实际写成： k *= (i + j);，赋值运算符优先级最低
权重：低
备注：实际编程中公司会要求多级运算必须加括号。

====
6、请写出下列代码的输出内容
#include<stdio.h>
void main(void)
{
    int a, b, c, d;
    a = 10;
    b = a++;
    c = ++a;
    d = 10 * a++;
    printf("b，c，d：%d，%d，%d"，b，c，d）;
    return 0;
} 
答：10，12，120
权重：高
备注：++a先加再使用，a++先使用再加

====
5、写出下列代码的输出内容
#include<stdio.h>
int inc(int a)
{
    return(++a);
}
int multi(int*a, int*b, int*c)
{
    return(*c = *a * *b);
}
typedef int(FUNC1)(int in);
typedef int(FUNC2) (int*, int*, int*);

void show(FUNC2 fun, int arg1, int *arg2)
{
    INC p = &inc;
    int temp = p(arg1);
    fun(&temp, &arg1, arg2);
    printf("%d\n", *arg2);
}
void main(void)
{
    int a;
    show(multi, 10, &a);
    return 0;
}
答：110
权重：中

====
7、请找出下面代码中的所有错误
说明：以下代码是把一个字符串倒序，如“abcd”倒序后变为“dcba”
1、#include"string.h"	//1
2、main()	//2
3、{
4、 char*src="hello,world";
5、 char* dest=NULL;
6、 int len=strlen(src);
7、 dest=(char*)malloc(len);	//3，4
8、 char* d=dest;
9、 char* s=src[len];	
10、 while(len--!=0) 
11、 d++=s--;
12、 printf("%s",dest);
13、 return 0;
14、} 
答：
方法1：
int main(void)
{
    char *src = "hello,world";
    int len = strlen(src);
    char *dest = (char *)malloc(len + 1);    //要为\0分配一个空间
    char *d = dest;
    char *s = &src[len - 1];                //指向最后一个字符

    while(len-- != 0)
       *d++ = *s--;
    *d = 0;                                 //尾部要加\0
    printf("%s\n", dest);
    free(dest);                             // 使用完，应当释放空间，以免造成内存汇泄露

    return 0;
}
方法2：
#include <stdio.h>
#include <string.h>
void main(void)
{
    char str[] = "hello,world";
    int len = strlen(str);
    char t;
 
    for (int i = 0; i < len / 2; i++)
    {
        t = str[i];
        str[i] = str[len - i - 1]; str[len - i - 1] = t;
    }
    printf("%s", str);

    return 0;
}
权重：高
备注：找错题能看出有没有实际工作经验，知道哪些坑

====
1.请问以下代码有什么问题：
int main()
{
    char a;
    char *str=&a;
    strcpy(str,"hello");
    printf(str);
    return 0;
}
答：
没有为str分配内存空间，将会发生异常
问题出在将一个字符串复制进一个字符变量指针所指地址。虽然可以正确输出结果，但因为越界进行内在读写而导致程序崩溃。
权重：高

====
char *s = "AAA";
printf("%s", s);
s[0] = 'B';
printf("%s", s);
有什么错？
答：
"AAA"是字符串常量。s是指针，指向这个字符串常量，所以声明s的时候就有问题。
cosnt char* s="AAA";
然后又因为是常量，所以对是s[0]的赋值操作是不合法的。
权重：高

====
1.有以下表达式：
int a=248; b=4;int const c=21;const int *d=&a;
int *const e=&b;int const *f const =&a;
请问下列表达式哪些会被编译器禁止？为什么？
答：
*c=32;d=&b;*d=43;e=34;e=&a;f=0x321f;
*c const，禁止
*d const整数， 禁止
e = &a const指针 禁止
const *f const =&a; 禁止
权重：较高
备注：int *const是指针只读，存的整数可改，const int *是指针可改，存的整数只读

====
1：(void *)ptr 和 (*(void**))ptr的结果是否相同？其中ptr为同一个指针
答：(void *)ptr 和 (*(void**))ptr值是相同的
权重：较低

====
2：int main()
{
    int x = 3;
    printf("%d", x);

    return 1;
}
问函数既然不会被其它函数调用，为什么要返回1？
mian中，c标准认为0表示成功，非0表示错误。具体的值是某中具体出错信息
权重：低

====
2. 输出多少？并分析过程
unsigned short A = 10;
printf("~A = %u\n", ~A);

char c=128; 
printf("c=%d\n",c);
第一题，～A ＝0xfffffff5,int值 为－11，但输出的是uint。所以输出4294967285
第二题，c＝0x10,输出的是int，最高位为1，是负数，所以它的值就是0x00的补码就是128，所以输出－128。
这两道题都是在考察二进制向int或uint转换时的最高位处理。
权重：低
备注：反码补码实际用到的时候再去查也可以

====
4.char a[10],strlen(a)为什么等于15？运行的结果
#include "stdio.h"
#include "string.h"
void main()
{
    char aa[10];

    printf("%d",strlen(aa));
}
答：
sizeof()和初始化没有关系，值为10；
strlen()和初始化有关，以‘\0’判断字符串结尾，结果为15只能说在不确定数据的内存中刚好第15个字节是0x0，也有可能没得出结果程序就崩溃了。
权重：中

====
1)给定结构struct A 
{
       char t:4;
       char k:4;
       unsigned short i:8;
       unsigned long m;
};问sizeof(A) = ?
答
给定结构struct A 
{
       char t:4; 4位
       char k:4; 4位
       unsigned short i:8; 8位      
       unsigned long m; // 偏移2字节保证4字节对齐
}; // 共8字节
权重：高

====
2)下面的函数实现在一个数上加一个数，有什么错误？请改正。
int add_n ( int n )
{
    static int i = 100;
    i += n;
    return i;
}
答：第二次调用时得不到正确的结果，问题出在 static上
权重：较低

====
3.int a,b,c 请写函数实现c=a+b ,不可以改变数据类型,如将c改为long int,关键是如何处理溢出问题
答：
bool add (int a, int b,int *c)
{
    *c = a + b;
    return (a>0 && b>0 &&(*c<a || *c<b) || (a<0 && b<0 &&(*c>a || *c>b)));
}
权重：较低

====
4.分析输出是什么：
struct bit 
{
    int a:3; 
    int b:2; 
    int c:3; 
}; 
int main() 
{ 
    bit s; 
    char *c = (char *)&s; 
    cout << sizeof(bit) << endl;
    *c = 0x99;
    cout << s.a <<endl <<s.b<<endl<<s.c<<endl; 
    int a = -1;
    printf("%x",a);
   return 0; 
} 
输出为什么是
4
1
-1
-4
ffffffff
因为0x99在内存中表示为 100 11 001 , a = 001, b = 11, c = 100
当c为有符合数时, c = 100, 最高1为表示c为负数，负数在计算机用补码表示，所以c = -4;同理 
b = -1;
当c为有符合数时, c = 100,即 c = 4,同理 b = 3
权重：中

位域 ：   
有些信息在存储时，并不需要占用一个完整的字节， 而只需占几个或一个二进制位。例如在存放一个开关量时，只有0和1 两种状态， 用一位二进位即可。为了节省存储空间，并使处理简便，Ｃ语言又提供了一种数据结构，称为“位域”或“位段”。所谓“位域”是把一个字节中的二进位划分为几个不同的区域， 并说明每个区域的位数。每个域有一个域名，允许在程序中按域名进行操作。 这样就可以把几个不同的对象用一个字节的二进制位域来表示。一、位域的定义和位域变量的说明位域定义与结构定义相仿，其形式为：     
struct 位域结构名     
{ 位域列表 };    
其中位域列表的形式为： 类型说明符 位域名：位域长度     
例如：     
struct bs    
{    
    int a:8;    
    int b:2;    
    int c:6;    
};    
位域变量的说明与结构变量说明的方式相同。 可采用先定义后说明，同时定义说明或者直接说明这三种方式。例如：     
struct bs    
{    
    int a:8;    
    int b:2;    
    int c:6;    
} data;    
说明data为bs变量，共占两个字节。其中位域a占8位，位域b占2位，位域c占6位。对于位域的定义尚有以下几点说明：    
1. 一个位域必须存储在同一个字节中，不能跨两个字节。如一个字节所剩空间不够存放另一位域时，应从下一单元起存放该位域。也可以有意使某位域从下一单元开始。例如：     
struct bs    
{    
    unsigned a:4    
    unsigned :0 /*空域*/    
    unsigned b:4 /*从下一单元开始存放*/    
    unsigned c:4    
}    
在这个位域定义中，a占第一字节的4位，后4位填0表示不使用，b从第二字节开始，占用4位，c占用4位。    
2. 由于位域不允许跨两个字节，因此位域的长度不能大于一个字节的长度，也就是说不能超过8位二进位。    
3. 位域可以无位域名，这时它只用来作填充或调整位置。无名的位域是不能使用的。例如：     
struct k    
{    
    int a:1    
    int :2 /*该2位不能使用*/    
    int b:3    
    int c:2    
};    
从以上分析可以看出，位域在本质上就是一种结构类型， 不过其成员是按二进位分配的。    
二、位域的使用位域的使用和结构成员的使用相同，其一般形式为： 位域变量名:位域名 位域允许用各种格式输出。    
main(){    
struct bs    
{    
    unsigned a:1;    
    unsigned b:3;    
    unsigned c:4;    
} bit, *pbit;    
bit.a=1;    
bit.b=7;    
bit.c=15;    

====
4.下面这个程序执行后会有什么错误或者效果:
#define MAX 255
int main()
{
   unsigned char A[MAX], i; //i被定义为unsigned char
   for (i = 0; i <= MAX; i++)
      A[i] = i;
}
解答：死循环加数组越界访问（C/C++不进行数组越界检查）
MAX=255 
数组A的下标范围为:0..MAX-1,这是其一..
其二.当i循环到255时,循环内执行:
  A[255]=255;
这句本身没有问题..但是返回for (i=0;i<=MAX;i++)语句时,
由于unsigned char的取值范围在(0..255),i++以后i又为0了..无限循环下去.
权重：高
备注：实际工作中也要注意要int i;

====
2.#define Max_CB 500
void LmiQueryCSmd(Struct MSgCB * pmsg)
{
    unsigned char ucCmdNum;
    ......
    for(ucCmdNum = 0; ucCmdNum < MAX_CB; UCCMDNUM++)
    {
        ......;
    }
}
答: 死循环,unsigned char的取值范围是0~255
权重：高

====
5.求结构体占内存大小
struct name1 {
   char  str;
   short x;
   int   num;
}
struct name2{
   char str;
   int num;
   short x;
}
sizeof(struct name1)=8,sizeof(struct name2)=12
在第二个结构中，为保证num按四个字节对齐，char后必须留出3字节的空间；同时为保证整个结构的自然对齐（这里是4字节对齐），在x后还要补齐2个字节，这样就是12字节。
权重：高
备注：理解结构体字节对齐

====
2. 写出程序输出结果
void g(int**);
int main()
{
    int line[10], i;
    int *p = line; //p是地址的地址
    for (i = 0; i < 10; i++)
    {
        *p = i;
        g(&p); //数组对应的值加1
    }
    for (i = 0; i < 10; i++)
    printf("%d\n", line[i]);
    return 0;
}

void g(int **p)
{
    (**p)++;
    (*p)++; // 无效
}
答：
输出：
1
2 
3 
4 
5 
6 
7 
8 
9 
10
权重：中

====
3. 写出程序运行结果
int sum(int a)
{
    auto int c = 0;
    static int b = 3;
    c += 1;
    b += 2;
    return(a + b + c);
}

void main()
{
    int I;
    int a = 2;
    for(I = 0; I < 5; I++)
    {
        printf("%d,", sum(a));
    }
}
// static会保存上次结果
输出：8,10,12,14,16,
权重：较高

====
4.
int func(int a)
{
    int b;
    switch(a)
    {
        case 1: 30;
        case 2: 20;
        case 3: 16;
        default: 0
    }
    return b;
}
则func(1)=?
答：b定义后就没有赋值，返回不确定，如果将代码改为
    switch(a)
    {
        case 1: b = 30; // flow down
        case 2: b = 20; // flow down
        case 3: b = 16; // flow down
        default: b = 0
    }则最终返回0，因为没有break会顺延到最后一个。
权重：较高

====
5:
int a[3];
a[0] = 0; a[1] = 1; a[2] = 2;
int *p, *q;
p = a;
q = &a[2];
则a[q-p] = ?
答：a[2]
解释：指针一次移动一个int但计数为1
权重：高

====
1.前几天面试，有一题想不明白,请教大家！
  typedef struct 
  { 
     int a:2;
     int b:2;
     int c:1;
  } test;

  test t;
  t.a = 1;
  t.b = 3;
  t.c = 1;

  printf("%d",t.a);
  printf("%d",t.b);
  printf("%d",t.c);
答：
t.a为01,输出就是1
t.b为11，输出就是-1
t.c为1，输出也是-1
3个都是有符号数int嘛。
这是位扩展问题 
01
11
1
编译器进行符号扩展
权重：较高

====
1.分析,输出是什么？：
int arr[] = {6, 7, 8, 9, 10};
int *ptr = arr;
*(ptr++) += 123;
printf(“ %d %d ”, *ptr, *(++ptr));
输出：8 8
过程：对于*(ptr++)+=123;先做加法6+123，然后++，指针指向7；对于printf(“ %d %d ”, *ptr, *(++ptr));从后往前执行，指针先++，指向8，然后输出8，紧接着再输出8
权重：中

====
1.分析下面的代码,结果是什么：
char *a = "hello";
char *b = "hello";
if(a == b)
    printf("YES");
else
    printf("NO");
答：
如果是笔试题目，答案是no(考察指针地址)
可在VC实际结果是YES 在C是NO
常量字符串存储于静态存储区，它在程序生命期内恒定不变。如果编译器优化的话，会有可能a和b同时指向同一个hello的。则地址相同。如果编译器没有优化，那么就是两个不同的地址，则不同！
权重：较高

====
4.输出是什么？
#include <stdio.h>
void foo(int m, int n)
{
    printf("m=%d, n=%d\n", m, n);
}

int main()
{
    int b = 3;
    foo(b += 3, ++b);
    printf("b=%d\n", b);
    return 0;
}
输出：m=7,n=4,b=7(VC6.0)
这种方式和编译器中得函数调用关系相关即先后入栈顺序。不过不同
编译器得处理不同。也是因为C标准中对这种方式说明为未定义，所以
各个编译器厂商都有自己得理解，所以最后产生得结果完全不同。
因为这样，所以遇见这种函数，我们首先要考虑我们得编译器会如何处理
这样得函数，其次看函数得调用方式，不同得调用方式，可能产生不同得
结果。最后是看编译器优化。
权重：中

====　　
四.找错题:
1.请问下面程序有什么错误?
int a[60][250][1000], i, j, k;
for(k = 0; k <= 1000; k++)
    for(j = 0; j < 250; j++)
        for(i = 0; i < 60; i++)
            a[i][j][k] = 0;
答: 把循环语句内外换一下，i在最外层
权重：中

3.以下是求一个数的平方的程序,请找出错误:
#define SQUARE(a)((a)*(a))
int a=5;
int b;
b=SQUARE(a++);
答:结果与编译器相关,得到的可能不是平方值. 

====
4. C++:memset ,memcpy 和strcpy 的根本区别？ 
答:#include "memory.h"
memset用来对一段内存空间全部设置为某个字符，一般用在对定义的字符串进行初始化为' '或''；例:char a[100];memset(a, '', sizeof(a)); 
memcpy用来做内存拷贝，你可以拿它拷贝任何数据类型的对象，可以指定拷贝的数据长度；例：char a[100],b[50]; memcpy(b, a, sizeof(b));注意如用sizeof(a)，会造成b的内存地址溢出。 
strcpy就只能拷贝字符串了，它遇到'\0'就结束拷贝；例：char a[100],b[50];strcpy(a,b);如用strcpy(b,a)，要注意a中的字符串长度（第一个'\0'之前）是否超过50位，如超过，则会造成b的内存地址溢出。
权重：高
备注：这都是常用的库函数

strcpy 
原型：extern char *strcpy(char *dest, char *src); 
{
    ASSERT((dest != NULL) && (src != NULL));
    char *address = dest;
    while((*dest++ = *src++) != ’\0’)
    continue;
    return dest;
}
功能：把src所指由NULL结束的字符串复制到dest所指的数组中。
说明：src和dest所指内存区域不可以重叠且dest必须有足够的空间来容纳src的字符串。
返回指向dest的指针。
memcpy 
原型：extern void *memcpy(void *dest, void *src, unsigned int count);
{
    ASSERT((dest != NULL) && (src != NULL));
    ASSERT((dest > src+count) || (src > dest + count)); //防止内存重叠,也可以用restrict修饰指针
    Byte* bdest = (Byte*)dest;
    Byte* bsrc = (Byte*) src;
    while(count-- > 0)
        *bdest++ = **bsrc++;
    return dest;
}
功能：由src所指内存区域复制count个字节到dest所指内存区域。
说明：src和dest所指内存区域不能重叠，函数返回指向dest的指针。
memset
原型：extern void *memset(void *buffer, char c, int count);
功能：把buffer所指内存区域的前count个字节设置成字符c。
说明：返回指向buffer的指针。

====








