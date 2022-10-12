====
思科
1. 用宏定义写出swap（x，y）
#define swap(x, y)  \
x = x + y;          \
y = x - y;          \
x = x - y;
权重：高
备注：掌握宏定义函数，此题答案有误，还需把所有的x和y都加上括号，最好还要用上do while(0)

====
12.要对绝对地址0x100000赋值，我们可以用(unsigned int*)0x100000 = 1234;
   那么要是想让程序跳转到绝对地址是0x100000去执行，应该怎么做？
　　  答案:
　　  *((void (*)( ))0x100000 ) ( );
　　  解析：
　　  首先要将0x100000强制转换成函数指针,即:
　　  (void (*)())0x100000
　　  然后再调用它:
　　  *((void (*)())0x100000)();
　　  用typedef可以看得更直观些:
　　  typedef void(*)() voidFuncPtr;
　　  *((voidFuncPtr)0x100000)();
权重：高
备注：要掌握函数指针，实际中会用

====
3、 编写一个函数，输入一个的整型数字，可以选择按照8/10/16进制输出字符串。
答：
void number_print(int i_num, int type) // type为8、10、16
{
    int divisor; // 除数
    int remainder; // 余数
    divisor = i_num / type;

    if (divisor > 0) {
        number_print(divisor, type); // 采用递归，从最大的数开始打印
    }

    remainder = i_num % type;
    if (remainder >= 10 ) {
        switch (remainder) {
        case 10:
            printf(“a”);
            break;
        case 11:
            printf(“b”);
            break;
        case 12:
            printf(“c”);
            break;
        case 13:
            printf(“d”);
            break;
        case 14:
            printf(“e”);
            break;
        case 15:
            printf(“f”);
            break;
        default:
            printf(“Type error!\n”);
        break;
    } else {
        printf(“%d”, remainder);
    }
}
权重：中
备注：对于将数字转换成可显示字符串，可以使用库函数snprintf输出到内存，或者printf输出到标准输出
    嵌入式编程一般不建议使用递归，因为内存比较小，容易造成堆栈溢出。

====
9.将一个数字字符串转换为数字."1234" --> 1234
int convert(char* str)
{
   int k = 0;
   while (*str != '\0')
   {
      k = k * 10 + (*str++) - '0';
   }
   return k;
}
权重：较高

====
4、将一个字符串逆序
答：思路为字符串前后数据调换，不另外开辟内存
char *string_reverse(char *p_str)
{
    int i = 0, j=0;
    int len = 0;
    char tmp = 0;
    char *p_str2 = p_str;

    if (NULL == p_str) {
        return NULL;
    }
    while ((*p_str2++) != ‘\0’) { // 如果没遇到字符串尾
        len++; // 算出字符串总长度
    }

    i = 0;
    j = len - 1;
    while (i < j) {
        tmp = p_str[i];
        p_str[i] = p_str[j];
        p_str[j] = tmp;
        i++;
        j--;
    }

    return p_str;
}
权重：高
备注：可以使用判断\0的方式判断字符串结尾，也可以使用strlen库函数

====
6、编写一个 C 函数，该函数在一个字符串中找到子字符串。
答：即手动实现string.h中的strstr函数，仿照它的函数名和形参返回值
char *strstr(const char *s1, const char *s2) // 在s1中查找s2，没找到返回NULL
{
    int n;

    if(*s2)
    { // 判断s2是否为空
        while(*s1) // 循环在s1中判断
        {
            for(n=0; *(s1+n)==*(s2+n); n++)
            {
                if(!*(s2+n+1)) // 如果s2下一个字节为字符串尾0x00，则所有字符串都已经找到
                    return (char*)s1;
            }
            s1++;
        }
        return NULL;
    }
    else
        return (char*)s1;
}
权重：较高
备注：考对指针的操作，实际工作中经常要对字符串进行各种操作，如置换、查找、拼接，有些在 库函数中找不到原型的就需要自己实现。
    string.h中的strstr函数已经实现了字符串查找功能

====
12、已知一个数组table，用一个宏定义，求出数据的元素个数。
参考答案：
#define NTBL (sizeof(table) / sizeof(table[0]))
权重：高
备注：实际工作经常使用

====
14、二维数组空间的动态申请
可以使用c语言的malloc free或者c++的new delete
a.简单的，已经有一维，如
    char (*c)[5];
    c = new char[n][5]; //n为已定义的行数
b.二维的 int **p;
    p = new int *[m_row]; //创建行指针
    for (int i = 0; i < m_row; i++) //为每一行分配空间
       p[i] = new int[m_cols];
写到某一个函数中：
void getmemory(int ** &p, int m_row, int m_cols)
{
    p = new int*[m_row]; //创建行指针
    for (int i=0; i<m_row; i++) //为每一行分配空间
        p[i] = new int[m_cols];
 }
释放空间:
void deletememory(int **&p, int m_row)
{
     //释放每一行所分配的空间
     for(int i = 0; i < m_row; i++) 
         delete [] x[i]; //释放行指针
     delete [] x; 
     x = 0;
}
权重：中
备注：内存申请了在用完后一定要释放，切记。忘了释放程序跑起来出了错，要花费大量的时间来查找问题，得不偿失。
    对于多模块配合的情况可以发送者只管申请，接收者只管释放。

====
26、printf可以接受多个参数，为什么，请写出printf的原型。
答：使用可变参数技术，va_list va_start va_arg
int printf(const char *fmt, ...);
权重：中
备注：直接记住可变参数的原理。
    考核C语言可变参数，比如main函数就可以用可变参数，在应用程序被调用时可以用不同的参数动态的控制不同的程序运行策略

====
30、a+++++b所表示的是什么意思？有什么问题？
    这种写法坚决不提倡，写代码要有完好的编码规范！包括能用括号表示优先级就要用括号，使用规范命名等等。
    这个东西其实并没有语法错误，按照C对运算符等级的划分，++的优先级大于+，那么这句话会被编译器看做：(a++)+(++b)，这回明白了吧。有什么问题，语法上没有问题，有的是道德上的问题！作为一个优秀的程序员，我们要力求语句的合法性和可读性，如果写这句的人是在一个team里，那么他基本会被打的半死
    最后讨论一下结果：假设a之前的值是3，b是4，那么运行完这个变态语句后，a的值是4，b是5，语句的结果是8。
权重：较低
备注：的确有公司出这个题，考察C语言所有操作符的优先级，其实不用记住，需要知道优先级的时候可以到网上去查

====
34、 对(-1.2345)取整是多少？
取整不是四舍五入，而是去掉尾巴。
其实不同的取整函数可能有不同的结果，不过这个数没有太大的争议，答案是-1。
权重：高

====
35、 如何在C中为一个数组分配空间。
    题目出的不好，应该出的具体化一点，给出要分配的数组名称和大小。
    最简单的方法是：char array[5]；意思是分配给数组array一个5个字节的空间。但是我们要知道在C中数组其实就是一个名字，其实质含义就是指针，比如char array[]；是到底分配的多少空间？所以我们要将其分成为两种不同的形式给出答案：
    一种是栈的形式：char array[5]；即局部变量的分配，我们要明白的是，这种形式空间分配的大小可能会受操作系统的限制,比如一般arm会限制512K，windows会限制在2M；这是嵌入式应该掌握的知识点。因为你不能在函数内部定义大的数组，这会导致程序异常崩溃，浪费你大量的debug时间。
    一种是堆的形式：char *array; array=(char *)malloc(5);//C++: array=new char[5];
第二种形式成空间分配很灵活，想分配多少分配多少，只要RAM够大，只是一定要记得使用完之后释放。
权重：较高

====
1、 s[10]的另外一种表达方式是什么。
    前面说过了，数组和指针其实是数据存在形态的两种表现形式，如果说对于数组s[]，我们知道*s=s[0]，那么s[10]的另一种表达方式就是：*(s+10)。
权重：较低
备注：需要理解题意，s[10]代表已有数组中的一个元素，int s[10];才是定义数组。

===
2、如何定义一个有10个元素的整数型指针数组。
既然只是定义而不是初始化，那就很简单且没有争议了：int *array[10];。
权重：高
备注：C语言基础

====
3、编写一个自己的完全C语言版本的memset函数，并且评价这个实现的性能和可移植性
理解了字符串结尾是’\0’，用while循环，将每个元素都赋给你想给的值。
权重：中
备注：理解字符串操作库函数，memset是将分配好的内存初始化为你想要的值，因为C语言分配好了内存后，内存里面的值是随机的，你往里面小范围放数据时就必须要全部初始化为0。

====
2、计算一个字节里（byte）里面有多少bit被置1 
答：
#include <stdio.h>
int comb(const int c)
{
    int count = 0;
    int i = 0;
    int cc = c;
    while(i++ < 8)
    {
        if((cc & 1) == 1)
        {
            count++;
        }
        cc = cc >> 1;
    }
    return count;
}
权重：中
备注：这是常规做法，还有一种更简单的做法

====
3.求函数返回值，假设输入x = 9999; 
int func(int x)
{ 
    int countx = 0; 
    while (x) 
    {
        countx++; 
        x = x & (x - 1); 
    } 
    return countx; 
} 
结果呢？
答：
知道了这是统计9999的二进制数值中有多少个1的函数，且有 
9999＝9×1024＋512＋256＋15
9×1024中含有1的个数为2； 
512中含有1的个数为1； 
256中含有1的个数为1； 
15中含有1的个数为4； 
故共有1的个数为8，结果为8。 
1000 - 1 = 0111，正好是原数取反。这就是原理。 
用这种方法来求1的个数是很效率很高的。 
不必去一个一个地移位。循环次数最少。
权重：较高

====
8.写一个内存拷贝函数,不用任何库函数.
答：
void* memcpy(void *pvTo, const void *pvFrom, size_t size)
{
    assert((pvTo != NULL) && (pvFrom != NULL));
    byte* pbTo = pvTo;
    byte* pbFrom = pbFrom;
    while (size-- > 0)
    {
       *pbTo++ = *pbFrom++;
    }
    return pvTo;
}
权重：高
备注：考超指针与赋值

====
编写一个标准strcpy函数的总分值为10，下面给出几个不同得分的答案：
2分
void strcpy( char *strDest, char *strSrc )
{
　   while( (*strDest++ = * strSrc++) != '\0' );
} 
4分
void strcpy( char *strDest, const char *strSrc ) 
//将源字符串加const，表明其为输入参数，加2分
{
　   while( (*strDest++ = * strSrc++) != '\0' );
} 
7分
void strcpy(char *strDest, const char *strSrc) 
{
　  //对源地址和目的地址加非0断言，加3分
　  assert( (strDest != NULL) && (strSrc != NULL) );
　  while( (*strDest++ = * strSrc++) != '\0' );
} 
10分
//为了实现链式操作，将目的地址返回，加3分！
char * strcpy( char *strDest, const char *strSrc ) 
{
　 assert( (strDest != NULL) && (strSrc != NULL) );
　 char *address = strDest; 
　 while( (*strDest++ = * strSrc++) != '\0' ); 
　　 return address;
} 
(4)对strlen的掌握，它没有包括字符串末尾的'\0'。
权重：较高

====
写出一个10分的strlen函数，完美的版本为
int strlen( const char *str ) //输入参数const
{
    assert( strt != NULL ); //断言字符串地址非0

　   int len;
　   while( (*str++) != '\0' ) 
　   { 
　　      len++; 
　   }
　   return len;
}
权重：较高

====
5. 编写strcat函数(6分)
已知strcat函数的原型是char *strcat (char *strDest, const char *strSrc);
其中strDest 是目的字符串，strSrc 是源字符串。
（1）不调用C++/C 的字符串库函数，请编写函数 strcat
答：
VC源码：
char * __cdecl strcat (char * dst, const char * src)
{
    char * cp = dst;
    while( *cp )
        cp++; /* find end of dst */
    while( *cp++ = *src++ ) ; /* Copy src to end of dst */
    return( dst ); /* return dst */
}
（2）strcat能把strSrc 的内容连接到strDest，为什么还要char * 类型的返回值？
答：方便赋值给其他变量
权重：较高
备注：学习精简写法

====
13.用户输入M,N值，从1至N开始顺序循环数数，每数到M输出该数值，直至全部输出。写出C程序。
     循环链表，用取余操作做
权重：中

====
3.在c语言库函数中将一个字符转换成整型的函数是atol()吗，这个函数的原型是什么？
函数名: atol 
功 能: 把字符串转换成长整型数 
用 法: long atol(const char *nptr); 
程序例: 
#include <stdlib.h> 
#include <stdio.h> 
int main(void) 
{ 
    long l;
    char *str = "98765432";

    l = atol(lstr);
    printf("string = %s integer = %ld\n", str, l);

    return(0); 
}
权重：高
备注：要知道<stdlib.h>的atoi、itoa等字符串转换函数

====
4.unsigned int intvert(unsigned int x,int p,int n)
实现对x的进行转换,p为起始转化位,n为需要转换的长度,假设起始点在右边.如x=0b0001 0001,p=4,n=3转换后x=0b0110 0001
答
unsigned int intvert(unsigned int x,int p,int n){
    unsigned int _t = 0;
    unsigned int _a = 1;
    for(int i = 0; i < n; ++i){
        _t |= _a;
        _a = _a << 1;
    }
    _t = _t << p;
    x ^= _t;

    return x;
}
权重：高
备注：会位操作

====



