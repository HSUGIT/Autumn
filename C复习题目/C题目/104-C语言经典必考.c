====
9.写出float x 与“零值”比较的if语句。
      if(x > 0.000001 && x < -0.000001)
权重：高
备注：实际编程时要注意

====
12、已知一个数组table，用一个宏定义，求出数据的元素个数。
参考答案：
#define NTBL (sizeof(table) / sizeof(table[0]))
权重：高
备注：实际工作经常使用

====
34、 对(-1.2345)取整是多少？
取整不是四舍五入，而是去掉尾巴。
其实不同的取整函数可能有不同的结果，不过这个数没有太大的争议，答案是-1。
权重：高

====
26:写一语句实现x是否为2的若干次幂的判断。
参考答案：!(X)&(X-1)
权重：较高
备注：理解并记住

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

16.有一个如下的结构体：
struct A{
    long a1;
    short a2;
    int a3;
    int *a4;
};
请问在64位编译器下用sizeof(struct A)计算出的大小是多少?(A)
A 24
B 28
C 16
D 18
解析：
32位编译器：32位系统下指针占用4字节
char ：1个字节
char*（即指针变量）: 4个字节（32位的寻址空间是2^32, 即32个bit，也就是4个字节。同理64位编译器）
short int : 2个字节
int： 4个字节
unsigned int : 4个字节
float: 4个字节
double: 8个字节
long: 4个字节
long long: 8个字节
unsigned long: 4个字节
64位编译器：64位系统下指针占用8字节
char ：1个字节
char*(即指针变量): 8个字节
short int : 2个字节
int： 4个字节
unsigned int : 4个字节
float: 4个字节
double: 8个字节
long: 8个字节
long long: 8个字节
unsigned long: 8个字节
Win64下：long 8字节、short 2字节、int 4字节、int* 8字节，C++中内存对齐，按最大长度对齐：8+（2+4+2（补齐2字节））+8 = 24字节
权重：高
备注：主要是了解32位和16位系统各种数据类型所占的存储空间

===
4. 写出嵌入式中经常使用的死循环有几种
while (1) {};
for(;;} 
__loop
goto loop;
权重：高
备注：写Linux驱动经常会用到goto

====
5. volatile 的含义，写出3种使用方式
答：
volatile提醒编译器它后面所定义的变量随时都有可能改变，因此编译后的程序每次需要存储或读取这个变量的时候，都会直接从变量地址中读取数据。如果没有volatile关键字，则编译器可能优化读取和存储，可能暂时使用寄存器中的值，如果这个变量由别的程序更新了的话，将出现不一致的现象。
一般说来，volatile用在如下的几个地方：
(1)、中断服务程序中修改的供其它程序检测的变量需要加volatile；
(2)、多任务环境下各任务间共享的标志应该加volatile；
(3)、存储器映射的硬件寄存器通常也要加volatile说明，因为每次对它的读写都可能由不同意义
权重：高

====
6. 给定一整型变量a写两段代码：第一个设置a的bit3,第二个清除a的bit3
答：
#define BIT3 (0x1 << 3)
static int a;
void set_bit3(void)
{
	a |= BIT3;
}
void clear_bit3(void)
{
	a &= ~BIT3;
}
权重：高
备注：写驱动经常用

====
7. 某工程中要设置一个绝对地址为0x67a9整形变量值为0xaa66，编译器是纯ANSI编译器。
int *ptr;
ptr = (int *)0x67a9;
*ptr = 0xaa55;
权重：高
备注：掌握函数指针

====
8. 使用__interrupt定义一个ISR,评论代码有什么不妥
__interrupt double compute_area (double radius)
{
	double area = PI * radius * radius;
	printf(" Area = %f", area);
	return area;
}
1). ISR 不能返回一个值。如果你不懂这个，那么你不会被雇用的。
2). ISR 不能传递参数。如果你没有看到这一点，你被雇用的机会等同第一项。
3). 在许多的处理器/编译器中，浮点一般都是不可重入的。有些处理器/编译器需要让额处的寄存器入栈，有些处理器/编译器就是不允许在ISR中做浮点运算。此外，ISR应该是短而有效率的，在ISR中做浮点运算是不明智的。
4). 与第三点一脉相承，printf()经常有重入和性能上的问题。如果你丢掉了第三和第四点，我不会太为难你的。不用说，如果你能得到后两点，那么你的被雇用前景越来越光明了。
不能传参数 不能有返回值 不能有打印语句 不应该使用浮点运算
权重：高
备注：写驱动时经常要写中断函数，没写好会有运行时错误

====
9.sizeof和strlen的区别?
答案：sizeof是运算符，在编译时即计算好了； 而strlen是函数，要在运行时才能计算。
还有对字符串来说，sizeof包含字符串结尾，strlen不包含
权重：高
备注：经常用

====
4 嵌入式系统相关问题
a) 对于整形变量A=0x12345678,请画出在little endian及big endian的方式下在内存中是如何存储的。
答：
little endian                big endian 刚好反过来
  高地址--〉 0x12      低地址--〉  0x12
                   0x34                          0x34
                   0x56                          0x56
  低地址--〉 0x78       高地址--〉 0x78
权重：较高
备注：很多CPU大端模式和小端模式是可以配置的

====
c) 中断(interrupt,如键盘中断)与异常(exception,如除零异常)有何区别?
异常：在产生时必须考虑与处理器的时钟同步，实践上，异常也称为同步中断。在处理器执行到由于编程失误而导致的错误指令时，或者在执行期间出现特殊情况(如缺页)，必须靠内核处理的时候，处理器就会产生一个异常。
所谓中断应该是指外部硬件产生的一个电信号，从cpu的中断引脚进入，打断cpu当前的运行；
所谓异常，是指软件运行中发生了一些必须作出处理的事件，cpu自动产生一个陷入来打断当前运行，转入异常处理流程。
权重：中

====
预处理器（Preprocessor）
1 . 用预处理指令#define 声明一个常数，用以表明1年中有多少秒（忽略闰年问题）
         #define SECONDS_PER_YEAR (60 * 60 * 24 * 365)UL
我在这想看到几件事情：
1) #define 语法的基本知识（例如：不能以分号结束，括号的使用，等等）
2)懂得预处理器将为你计算常数表达式的值，因此，直接写出你是如何计算一年中有多少秒而不是计算出实际的值，是更清晰而没有代价的。
3) 意识到这个表达式将使一个16位机的整型数溢出-因此要用到长整型符号L,告诉编译器这个常数是的长整型数。
4) 如果你在你的表达式中用到UL（表示无符号长整型），那么你有了一个好的起点。记住，第一印象很重要。
权重：高
备注：掌握宏定义

====
2 . 写一个"标准"宏MIN ，这个宏输入两个参数并返回较小的一个。
        #define MIN(A,B) （（A） <= (B) ? (A) : (B))
这个测试是为下面的目的而设的：
1) 标识#define在宏中应用的基本知识。这是很重要的。因为在  嵌入(inline)操作符 变为标准C的一部分之前，宏是方便产生嵌入代码的唯一方法，对于嵌入式系统来说，为了能达到要求的性能，嵌入代码经常是必须的方法。
2)三重条件操作符的知识。这个操作符存在C语言中的原因是它使得编译器能产生比if-then-else更优化的代码，了解这个用法是很重要的。
3) 懂得在宏中小心地把参数用括号括起来
4) 我也用这个问题开始讨论宏的副作用，例如：当你写下面的代码时会发生什么事？
        least = MIN(*p++, b);
权重：高
备注：掌握

====
3. 预处理器标识#error的目的是什么？
如果你不知道答案，你是对的。这问题对区分一个正常的伙计和一个书呆子是很有用的。只有书呆子才会读C语言课本的附录去找出象这种问题的答案。当然如果你不是在找一个书呆子，那么应试者最好希望自己不要知道答案。
权重：中
备注：有时候可以在头文件里用#error来判断是不是有需要传入的宏定义没有定义，如果是就用#error来退出编译，以便提示程序员修改

===
13、预处理器标识#error的目的是什么？
编译时就进行错误输出，比如必须的宏定义没有定义，必须的宏定义超出阈值
#error预处理指令的作用是，编译程序时，只要遇到#error就会生成一个编译错误提示消息，并停止编译。
指令用于报告编译时错误信息的；如果预处理方面有错误，那么就会打印#error指令后面的文本内容。
其语法格式为：
#error error-message
注意，宏串error-message不用双引号包围。遇到#error指令时，错误信息被显示，可能同时还显示编译程序作者预先定义的其他内容。系统所支持的error-message请查找相关信息获得！
权重：中

====
死循环（Infinite loops）
4. 嵌入式系统中经常要用到无限循环，你怎么样用C编写死循环呢？
这个问题用几个解决方案。我首选的方案是：
while(1)
{
}
一些程序员更喜欢如下方案：
for(;;)
{
}
这个实现方式让我为难，因为这个语法没有确切表达到底怎么回事。如果一个应试者给出这个作为方案，我将用这个作为一个机会去探究他们这样做的基本原理。如果他们的基本答案是："我被教着这样做，但从没有想到过为什么。"这会给我留下一个坏印象。
第三个方案是用 goto
Loop:
...
goto Loop;
应试者如给出上面的方案，这说明或者他是一个汇编语言程序员（这也许是好事）或者他是一个想进入新领域的BASIC/FORTRAN程序员。
权重：中

====
数据声明（Data declarations）
5. 用变量a给出下面的定义
a) 一个整型数（An integer） 
b)一个指向整型数的指针（ A pointer to an integer） 
c)一个指向指针的的指针，它指向的指针是指向一个整型数（ A pointer to a pointer to an intege）r 
d)一个有10个整型数的数组（ An array of 10 integers） 
e) 一个有10个指针的数组，该指针是指向一个整型数的。（An array of 10 pointers to integers） 
f) 一个指向有10个整型数数组的指针（ A pointer to an array of 10 integers） 
g) 一个指向函数的指针，该函数有一个整型参数并返回一个整型数（A pointer to a function that takes an integer as an argument and returns an integer） 
h) 一个有10个指针的数组，该指针指向一个函数，该函数有一个整型参数并返回一个整型数（ An array of ten pointers to functions that take an integer argument and return an integer ）
答案是： 
a) int a; // An integer 
b) int *a; // A pointer to an integer 
c) int **a; // A pointer to a pointer to an integer 
d) int a[10]; // An array of 10 integers 
e) int *a[10]; // An array of 10 pointers to integers 
f) int (*a)[10]; // A pointer to an array of 10 integers 
g) int (*a)(int); // A pointer to a function a that takes an integer argument and returns an integer 
h) int (*a[10])(int); // An array of 10 pointers to functions that take an integer argument and return an integer
人们经常声称这里有几个问题是那种要翻一下书才能回答的问题，我同意这种说法。当我写这篇文章时，为了确定语法的正确性，我的确查了一下书。但是当我被面试的时候，我期望被问到这个问题（或者相近的问题）。因为在被面试的这段时间里，我确定我知道这个问题的答案。应试者如果不知道所有的答案（或至少大部分答案），那么也就没有为这次面试做准备，如果该面试者没有为这次面试做准备，那么他又能为什么出准备呢？
权重：高
备注：不管你需不需要搜索才知道答案，反正工作中会用到

====
Static
6. 关键字static的作用是什么？
这个简单的问题很少有人能回答完全。在C语言中，关键字static有三个明显的作用：
1)在函数体，一个被声明为静态的变量在这一函数被调用过程中维持其值不变。
2) 在模块内（但在函数体外），一个被声明为静态的变量可以被模块内所用函数访问，但不能被模块外其它函数访问。它是一个本地的全局变量。
3) 在模块内，一个被声明为静态的函数只可被这一模块内的其它函数调用。那就是，这个函数被限制在声明它的模块的本地范围内使用。
大多数应试者能正确回答第一部分，一部分能正确回答第二部分，同是很少的人能懂得第三部分。这是一个应试者的严重的缺点，因为他显然不懂得本地化数据和代码范围的好处和重要性。
     static全局变量与普通的全局变量有什么区别：static全局变量只初使化一次，防止在其他文件单元中被引用;
     static局部变量和普通局部变量有什么区别：static局部变量只被初始化一次，下一次依据上一次结果值；
     static函数与普通函数有什么区别：static函数在内存中只有一份，普通函数在每个被调用中维持一份拷贝
权重：高
备注：常用

====
Const
7．关键字const有什么含意？
我只要一听到被面试者说："const意味着常数"，我就知道我正在和一个业余者打交道。去年Dan Saks已经在他的文章里完全概括了const的所有用法，因此ESP(译者：Embedded Systems Programming)的每一位读者应该非常熟悉const能做什么和不能做什么.如果你从没有读到那篇文章，只要能说出const意味着"只读"就可 以了。尽管这个答案不是完全的答案，但我接受它作为一个正确的答案。（如果你想知道更详细的答案，仔细读一下Saks的文章吧。）
如果应试者能正确回答这个问题，我将问他一个附加的问题：
下面的声明都是什么意思？
const int a;
int const a;
const int *a;
int * const a;
int const * a const;
前两个的作用是一样，a是一个常整型数。第三个意味着a是一个指向常整型数的指针（也就是，整型数是不可修改的，但指针可以）。第四个意思a是一个指向整型 数的常指针（也就是说，指针指向的整型数是可以修改的，但指针是不可修改的）。最后一个意味着a是一个指向常整型数的常指针（也就是说，指针指向的整型数 是不可修改的，同时指针也是不可修改的）。如果应试者能正确回答这些问题，那么他就给我留下了一个好印象。顺带提一句，也许你可能会问，即使不用关键字 const，也还是能很容易写出功能正确的程序，那么我为什么还要如此看重关键字const呢？我也如下的几下理由：
1) 关键字const的作用是为给读你代码的人传达非常有用的信息，实际上，声明一个参数为常量是为了告诉了用户这个参数的应用目的。如果你曾花很多时间清理 其它人留下的垃圾，你就会很快学会感谢这点多余的信息。（当然，懂得用const的程序员很少会留下的垃圾让别人来清理的。）
2) 通过给优化器一些附加的信息，使用关键字const也许能产生更紧凑的代码。
3) 合理地使用关键字const可以使编译器很自然地保护那些不希望被改变的参数，防止其被无意的代码修改。简而言之，这样可以减少bug的出现。
权重：高
备注：常用

====
Volatile
8. 关键字volatile有什么含意?并给出三个不同的例子。
一个定义为volatile的变量是说这变量可能会被意想不到地改变，这样，编译器就不会去假设这个变量的值了。精确地说就是，优化器在用到这个变量时必须每次都小心地重新读取这个变量的值，而不是使用保存在寄存器里的备份。下面是volatile变量的几个例子：
1) 并行设备的硬件寄存器（如：状态寄存器）
2) 一个中断服务子程序中会访问到的非自动变量(Non-automatic variables)
3) 多线程应用中被几个任务共享的变量
回答不出这个问题的人是不会被雇佣的。我认为这是区分C程序员和嵌入式系统程序员的最基本的问题。搞嵌入式的家伙们经常同硬件、中断、RTOS等等打交道，所有这些都要求用到volatile变量。不懂得volatile的内容将会带来灾难。
假设被面试者正确地回答了这是问题（嗯，怀疑是否会是这样），我将稍微深究一下，看一下这家伙是不是直正懂得volatile完全的重要性。
1)一个参数既可以是const还可以是volatile吗？解释为什么。
2); 一个指针可以是volatile 吗？解释为什么。
3); 下面的函数有什么错误：
int square(volatile int *ptr)
{
        return *ptr * *ptr;
}
下面是答案：
1)是的。一个例子是只读的状态寄存器。它是volatile因为它可能被意想不到地改变。它是const因为程序不应该试图去修改它。
2); 是的。尽管这并不很常见。一个例子是当一个中服务子程序修该一个指向一个buffer的指针时。
3) 这段代码有点变态。这段代码的目的是用来返指针*ptr指向值的平方，但是，由于*ptr指向一个volatile型参数，编译器将产生类似下面的代码：
int square(volatile int *ptr) 
{
    int a,b;
    a = *ptr;
    b = *ptr;
    return a * b;
}
由于*ptr的值可能被意想不到地该变，因此a和b可能是不同的。结果，这段代码可能返不是你所期望的平方值！正确的代码如下：
long square(volatile int *ptr) 
{
    int a;
    a = *ptr;
    return a * a;
}
权重：高
备注：写驱动常用

====
位操作（Bit manipulation）
9. 嵌入式系统总是要用户对变量或寄存器进行位操作。给定一个整型变量a，写两段代码，第一个设置a的bit 3，第二个清除a 的bit 3。在以上两个操作中，要保持其它位不变。
对这个问题有三种基本的反应
1)不知道如何下手。该被面者从没做过任何嵌入式系统的工作。
2) 用bit fields。Bit fields是被扔到C语言死角的东西，它保证你的代码在不同编译器之间是不可移植的，同时也保证了的你的代码是不可重用的。我最近不幸看到 Infineon为其较复杂的通信芯片写的驱动程序，它用到了bit fields因此完全对我无用，因为我的编译器用其它的方式来实现bit fields的。从道德讲：永远不要让一个非嵌入式的家伙粘实际硬件的边。
3) 用 #defines 和 bit masks 操作。这是一个有极高可移植性的方法，是应该被用到的方法。最佳的解决方案如下：
#define BIT3 (0x1 << 3)
static int a;
void set_bit3(void) 
{
    a |= BIT3;
}
void clear_bit3(void) 
{
    a &= ~BIT3;
}
一些人喜欢为设置和清除值而定义一个掩码同时定义一些说明常数，这也是可以接受的。我希望看到几个要点：说明常数、|=和&=~操作。
权重：高
备注：写驱动常用

====
访问固定的内存位置（Accessing fixed memory locations）
10. 嵌入式系统经常具有要求程序员去访问某特定的内存位置的特点。在某工程中，要求设置一绝对地址为0x67a9的整型变量的值为0xaa66。编译器是一个纯粹的ANSI编译器。写代码去完成这一任务。
这一问题测试你是否知道为了访问一绝对地址把一个整型数强制转换（typecast）为一指针是合法的。这一问题的实现方式随着个人风格不同而不同。典型的类似代码如下：
    int *ptr;
    ptr = (int *)0x67a9;
    *ptr = 0xaa55;
 A more obscure approach is: 
一个较晦涩的方法是：
    *(int * const)(0x67a9) = 0xaa55;
即使你的品味更接近第二种方案，但我建议你在面试时使用第一种方案。
权重：高
备注：常用

====
中断（Interrupts）
11. 中断是嵌入式系统中重要的组成部分，这导致了很多编译开发商提供一种扩展—让标准C支持中断。具代表事实是，产生了一个新的关键字 __interrupt。下面的代码就使用了__interrupt关键字去定义了一个中断服务子程序(ISR)，请评论一下这段代码的。
__interrupt double compute_area (double radius) 
{
    double area = PI * radius * radius;
    printf("\nArea = %f", area);
    return area;
}
这个函数有太多的错误了，以至让人不知从何说起了：
1) ISR 不能返回一个值。如果你不懂这个，那么你不会被雇用的。
2) ISR 不能传递参数。如果你没有看到这一点，你被雇用的机会等同第一项。
3) 在许多的处理器/编译器中，浮点一般都是不可重入的。有些处理器/编译器需要让额处的寄存器入栈，有些处理器/编译器就是不允许在ISR中做浮点运算。此外，ISR应该是短而有效率的，在ISR中做浮点运算是不明智的。
4) 与第三点一脉相承，printf()经常有重入和性能上的问题。如果你丢掉了第三和第四点，我不会太为难你的。不用说，如果你能得到后两点，那么你的被雇用前景越来越光明了。
权重：高
备注：写驱动常用

代码例子（Code examples）
12 . 下面的代码输出是什么，为什么？
void foo(void)
{
    unsigned int a = 6;
    int b = -20;
    (a+b > 6) ? puts("> 6") : puts("<= 6");
}
这个问题测试你是否懂得C语言中的整数自动转换原则，我发现有些开发者懂得极少这些东西。不管如何，这无符号整型问题的答案是输出是 ">6"。原因是当表达式中存在有符号类型和无符号类型时所有的操作数都自动转换为无符号类型。因此-20变成了一个非常大的正整数，所以该表达式 计算出的结果大于6。这一点对于应当频繁用到无符号数据类型的嵌入式系统来说是丰常重要的。如果你答错了这个问题，你也就到了得不到这份工作的边缘。
权重：中

====
13. 评价下面的代码片断：
unsigned int zero = 0;
unsigned int compzero = 0xFFFF; 
/*1's complement of zero */
对于一个int型不是16位的处理器为说，上面的代码是不正确的。应编写如下：
unsigned int compzero = ~0;
这一问题真正能揭露出应试者是否懂得处理器字长的重要性。在我的经验里，好的嵌入式程序员非常准确地明白硬件的细节和它的局限，然而PC机程序往往把硬件作为一个无法避免的烦恼。
到 了这个阶段，应试者或者完全垂头丧气了或者信心满满志在必得。如果显然应试者不是很好，那么这个测试就在这里结束了。但如果显然应试者做得不错，那么我就 扔出下面的追加问题，这些问题是比较难的，我想仅仅非常优秀的应试者能做得不错。提出这些问题，我希望更多看到应试者应付问题的方法，而不是答案。不管如何，你就当是这个娱乐吧...
权重：中

====
动态内存分配（Dynamic memory allocation）
14. 尽管不像非嵌入式计算机那么常见，嵌入式系统还是有从堆（heap）中动态分配内存的过程的。那么嵌入式系统中，动态分配内存可能发生的问题是什么？
这 里，我期望应试者能提到内存碎片，碎片收集的问题，变量的持行时间等等。这个主题已经在ESP杂志中被广泛地讨论过了（主要是 P.J. Plauger, 他的解释远远超过我这里能提到的任何解释），所有回过头看一下这些杂志吧！让应试者进入一种虚假的安全感觉后，我拿出这么一个小节目：
下面的代码片段的输出是什么，为什么？
char *ptr;
if ((ptr = (char *)malloc(0)) == NULL) 
    puts("Got a null pointer");
else
    puts("Got a valid pointer");
这 是一个有趣的问题。最近在我的一个同事不经意把0值传给了函数malloc，得到了一个合法的指针之后，我才想到这个问题。这就是上面的代码，该代码的输 出是"Got a valid pointer"。我用这个来开始讨论这样的一问题，看看被面试者是否想到库例程这样做是正确。得到正确的答案固然重要，但解决问题的方法和你做决定的基本原理更重要些。
权重：较低

====
Typedef 
15 Typedef 在C语言中频繁用以声明一个已经存在的数据类型的同义字。也可以用预处理器做类似的事。例如，思考一下下面的例子：
#define dPS struct s *
typedef struct s * tPS;
以上两种情况的意图都是要定义dPS 和 tPS 作为一个指向结构s指针。哪种方法更好呢？（如果有的话）为什么？
这是一个非常微妙的问题，任何人答对这个问题（正当的原因）是应当被恭喜的。答案是：typedef更好。思考下面的例子：
dPS p1,p2;
tPS p3,p4;
第一个扩展为
struct s * p1, p2;
上面的代码定义p1为一个指向结构的指，p2为一个实际的结构，这也许不是你想要的。第二个例子正确地定义了p3 和p4 两个指针。
权重：高
备注：常用typedef
 
====
晦涩的语法
16 . C语言同意一些令人震惊的结构,下面的结构是合法的吗，如果是它做些什么？
int a = 5, b = 7, c;
c = a+++b;
这个问题将做为这个测验的一个愉快的结尾。不管你相不相信，上面的例子是完全合乎语法的。问题是编译器如何处理它？水平不高的编译作者实际上会争论这个问题，根据最处理原则，编译器应当能处理尽可能所有合法的用法。因此，上面的代码被处理成：
c = a++ + b;
因此, 这段代码持行后a = 6, b = 7, c = 12。
如果你知道答案，或猜出正确答案，做得好。如果你不知道答案，我也不把这个当作问题。我发现这个问题的最大好处是这是一个关于代码编写风格，代码的可读性，代码的可修改性的好的话题。
权重：较低
备注：实际工作会用括号扩起来

====
14：写出float，bool，int 类型与零的比较，假设变量为X：
       Int ：    if（x == 0）
       Float：    if（x > 0.0000001 && x）
       Bool:      if(x == false)
权重：高

====
17：程序的局部变量存储在（栈）中，全局变量存储于（静态存储区），动态申请数据存储于（堆中）；
权重：较高

====
18：编写一个字符串复制函数：strcpy（const char *str，const char *str1）
void strcpy(const *char str, const chat *str1)
{
    if(*str1 == ’\0’) return;
    char *sp1, *sp2;
    sp1 = str;
    sp2 = str1;
    while(*sp2 != ’\0’)
    {
        *sp1 = sp2;
        sp1++;
        sp2++;
    }
}
权重：高

====
19:编写一个函数实现字符串翻转 void rechange（char *str）
void rechange（char *str）
{
    int len；
    char t；
    len = strlen（str）；
    for（int i = 0；len / 2；i++）
    {
        t = str;
        str = str[len - i - 1];
        str[len - i - 1] = t;
    }
}
权重：较高

====
20:编写一个函数实现字符串比较 int strcmp（char *str1，char *str2）,相等返回1，不相等返回0：
int strcmp（char *str1，char *str2）
{
    if（*str1 == ‘\0’ || *str2 == ’\0’） return;
    while(*str1 != ’\0’ && *str2 != ’\0’ && *str1 == *str2)
    {
        str1++；
        str2++；
    }
    if(*str1 == *str2)
        return 1;
    else return 0;
}
权重：高

====
一、 C语言基础
1、do{}while(); 和while(){};的区别？
答：do{}while();至少执行一次，while(){};可能一次也不会执行，前一个循环一遍再判断，后一个判断以后再循环 。
权重：高

====
3、 计算一个字节里（byte）里面有多少bit被置1
答：
int bit_set_counts_of_one_byte(char byte)
{
	int count = 0;
	while (byte) { // byte里面的1右移完之后会变为0
		if (byte & 1) {
			count++;
		}
		byte = byte >> 1;
	}
	return count;
}
或者：
for (; a; count ++) {
    a &= a - 1; // 一个二进制整数减1相当于把低位第一个1及之后的数取反，然后与原数相与就把低位第一个1清0了，从低到高等到所有的位都被清0，就会跳出循环。这种算法的效率跟1的个数有关，有多少1就循环多少次。老牛了。
}
权重：高

====
4、第12题:考查typedef类型定义,函数指针 
typedef int (*test) ( float * , float*) 
test tmp;  
tmp 的类型是？   
(a) 函数的指针，该函数以 两个指向浮点数(float)的指针(pointer)作为参数(arguments)        Pointer to function of having two arguments that is pointer to float 
(b) 整型 
(c) 函数的指针，该函数以 两个指向浮点数(float)的指针(pointer)作为参数(arguments),并且函数的返回值类型是整型       Pointer to function having two argument that is pointer to float and return int 
(d) 以上都不是 
答案：C
权重：高

====
5、写出你所知道的C语言关键字 
答：bool char int long float double true false NULL short unsigned signed void
if else switch case continue default while do for goto return
static volatile inline define include auto register __interrupt extern
struct enum typedef union
其它重要函数：sizeof malloc free printf scanf memcpy memset strcmp strlen va_list va_start va_rag
权重：高

====
6、函数 int compare(int a, int b), 定义一个该函数的函数指针p:
答：
    int (*p)(int a, int b);
    p = compare;
或者 
    typedef int (*P_FUNC)(int a, int b);
    P_FUNC p = compare;
权重：高
备注：要掌握

====
15、16位short int 类型所能表示的数值下限与上限，如果使用printf的格式串”%d,%d”打印，其结果是__-32768 ，32767 ____；
这个题意义不大，不知道没什么稀奇，算一算或者网上查一查就行，知道存储的数据大概在什么数量级会溢出就行了。
备注：较高

====
16、如何定义Bool变量的TRUE和FALSE的值。
使用#define就可以：
#define TURE 1
#define FALSE 0
权重：高

====
17、switch()中不允许的数据类型是? 
答：实型 （即浮点型，因为switch是在集合中查找匹配，只能在整形中查找）
权重：较高

====
18、关于内存对齐的问题 
    答：编译器自动对齐的原因：为了提高程序的性能，数据结构（尤其是栈）应该尽可能 地在自然边界上对齐。原因在于，为了访问未对齐的内存，处理器需要作两次内存访问 ；然而，对齐的内存访问仅需要一次访问。
struct中的数据会进行字节对齐，有时候代码中需要手动取消字节对齐。
权重：高
备注：嵌入式应该掌握

====
24、内存对齐问题的原因?
 平台原因（移植原因）：不是所有的硬件平台都能访问任意地址上的任意数据；
 性能原因：数据结构（尤其是栈）应该尽可能地在自然边界上对齐，因为为了访问未对齐的内存，处理器需要做两次内存访问，
     而对齐的内存访问仅需要一次。
权重：高

====
20、有如下CAT_s结构体定义，
struct CAT_s{
  int ld; // 4  4
  char Color; // 1  1
  unsigned short Age; // 2+1  2+1
  char *Name; // 4  8
  void(*Jump)(void); // 4  8
} Garfield;
回答：
  1) 在一台64位的机器上，使用32位编译，Garfield变量占用多少内存空间？64位编译又是如何？
答：16字节（字节对齐） 24字节（字节对齐）
权重：高

====
  2) 使用32位编译情况下，给出一种判断所使用机器大小端的方法。
答：
方法一：
int tmp = 0x11223344
if (*(char *)tmp == 0x44) 小端模式
else 大端模式
方法二：
typedef union {
	int a;
	struct {
		char aa; // aa存放在低地址
		char bb;
		char cc
		char dd; // dd存放在高地址
	} b;
} MY_UNION;
MY_UNION tmp = 0x11223344;
if (tmp.b.aa == 0x44) 小端模式
else 大端模式
权重：高

====
22、C语言程序代码优化方法
  * 选择合适的算法和数据结构
  * 使用尽量小的数据类型
  * 使用自加、自减指令
  * 减少运算的强度
   求余运算（a=a%8改为a=a&7）
   平方运算（a=pow(a,2.0)改为a=a*a）
   用移位实现乘除法运算
  * 延时函数的自加改为自减
  * switch语句中根据发生频率来进行case排序
权重：较高

====
23、宏和函数的优缺点？
 (1)、函数调用时，先求出实参表达式的值，然后带入形参。而使用带参数的宏只是进行简单的字符替换。
 (2)、函数调用是在程序运行时处理的，分配临时的内存单元；而宏展开则是在编译时进行的，在展开时并不分配内存单元，
   不进行值的传递处理，也没有“返回值”的概念。
 (3)、对函数中的实参和形参都要定义类型，二者的类型要求一致，应进行类型转换；而宏不存在类型问题，宏名无类型，
   它的参数也是无类型，只是一个符号代表，展开时带入指定的字符即可。宏定义时，字符串可以是任何类型的数据。
 (4)、调用函数只可得到一个返回值，而宏定义可以设法得到几个结果。
 (5)、使用宏次数多时，宏展开后源程序长，因为每次展开一次都使程序增长，而函数调用不使源程序变长。
 (6)、宏替换不占运行时间，只占编译时间；而函数调用则占运行时间（分配单元、保留现场、值传递、返回）。
权重：高

====
27、有定义char *str = “hello\n\0\n”,则strlen(str)的值是__6____；
(tip：’\0’即0x00为字符结束符标志，应该掌握) 
权重：高

====
28、完成宏定义，将int型变量a的第0位到第n位取反（右数最低位为第0位），其他位保持不变：
#define BIT_REVERSE(a,n)  ( (a)^ 1<<(n) )
权重：高
备注：掌握位的左移右移

====
29、枚举类型定义enum boolean {yes, no}; yes的数值是___0___；
权重：高
备注：必须知道enum默认从0、1、2往后赋值

====
39、头文件中的#ifndef/#define/#endif是干什么用的？ 
防止该头文件被重复引用
权重：高
备注：每个头文件都必须有，必须掌握。

====
试题4：为什么标准头文件都有类似以下的结构？
#ifndef __INCvxWorksh
#define __INCvxWorksh 
#ifdef __cplusplus

extern "C" {
#endif 
/* */ 
#ifdef __cplusplus
}

#endif 
#endif /* __INCvxWorksh */ 

解答：
头文件中的编译宏
#ifndef　__INCvxWorksh
#define　__INCvxWorksh
#endif 
的作用是防止被重复引用。
作为一种面向对象的语言，C++支持函数重载，而过程式语言C则不支持。函数被C++编译后在symbol库中的名字与C语言的不同。例如，假设某个函数的原型为： 
void foo(int x, int y); 
该函数被C编译器编译后在symbol库中的名字为_foo，而C++编译器则会产生像_foo_int_int之类的名字。_foo_int_int这样的名字包含了函数名和函数参数数量及类型信息，C++就是考这种机制来实现函数重载的。
为了实现C和C++的混合编程，C++提供了C连接交换指定符号extern "C"来解决名字匹配问题，函数声明前加上extern "C"后，则编译器就会按照C语言的方式将该函数编译为_foo，这样C语言中就可以调用C++的函数了。
权重：高

====
40、#include <filename.h>和#incldue "filename.h"有什么区别？ 
对于#include <filename.h>，编译器从标准头文件的路径开始搜索filename.h，在UNIX类的系统中通常是/usr/include。 
对于#include "filename.h"，编译器从包含该头文件的C源程序文件所在的路径开始搜索filename.h，如果没搜到再从标准头文件的路径开始搜索。 
权重：高
备注：养成好的编码习惯

====
43、已知char a[10]，问sizeof(a) strlen(a)各为多少
答：sizeof为10，strlen不确定，和存储的字符串相关，值为0-n。
权重：高

====
5、const与 ＃define相比有什么不同？ 
C++语言可以用const定义常量，也可以用#define定义常量，但是前者比后者有更多的优点： 
（1）const常量有数据类型，而宏常量没有数据类型。编译器可以对前者进行类型安全检查，而对后者只进行字符替换，没有类型安全检查，并且在字符替换中可能会产生意料不到的错误（边际效应） 
（2）有些集成化的调试工具可以对const常量进行调试，但是不能对宏常量进行调试。在C++程序中只使用const常量而不使用宏常量，即const常量完全取代宏常量。 
常量的引进是在早期的C++版本中，当时标准C规范正在制定。那时，常量被看作一个好的思想而被包含在C中。但是，C中的const的意识是“一 个不能被改变的普通变量”。在C中，它总是占用内存，而且它的名字是全局符。C编译器不能把const看成是一个编译期间的常量。在C中，如果写： 
const bufsize = 100; 
char buf[bufsize]; 
尽管看起来好像做了一件合理的事情，但这将得到一个错误的结果。因为bufsize占用内存的某个地方，所以C编译器不知道它在编译时的值。在C语言中可以选择这样书写： 
const bufsize; 
这样写在C++中是不对的，而C编译器则把它作为一个声明，这个声明指明在别的地方有内存分配。因此C默认const是外部连接的，C++默认const是内部连接的。这样，如果在C++中想完成与C中同样的事情，必须用extern把内部连接改写外部连接： 
extern const bufsize; // declaration only 
这种方法也可用在C语言中。在C语言中使用限定符const不是很有用，即使是在常数表达式里（必须在编译期间被求出）想使用一个已命名的值，使用const也不是很有用的。C迫使程序员在预处理里使用#define。
权重：较高

====
6、编译和链接有什么不同？（如外部符号的处理）
 编译生成的是目标文件(object  *.o);
 编译过程中对于外部符号不做任何解释和处理。外部符号对应的就是“符号”
 链接生成的是可执行程序
 链接将会解释和处理外部符号。外部符号对应的是地址
权重：较高

30:已知一个数组table，用一个宏定义，求出数据的元素个数。
参考答案：
#define NTBL (sizeof(table)/sizeof(table[0]))
权重：高
备注：常用

====
3、将一个链表逆序 
LinkList *reverse(LinkList *head)
{
    LinkList *p1,*p2 = NULL,*p3 = NULL;
    if(head == NULL || head->next == NULL)
        return head;
    p1 = head->next;
    while(p1!=NULL)
    {
        p3 = p1->next;
        p1->next = p2;
        p2 = p1;
        p1 = p3;
    }
    head->next = p2;
    // head = p2;

    return head; 
}
权重：高
备注：常考

====
3、在一个字符串中找到可能的最长的子字符串（子字符串从前往后匹配最长的） 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *commanstring(char shortstring[], char longstring[])
{
    int i,j;
    char *substring = malloc(256);
    if(strstr(longstring,shortstring)!=NULL)
        return shortstring;
    for(i=strlen(shortstring)-1;i>0;i--)
    {
        for(j=0;j<=strlen(shortstring)-i;j++)
        {
            memcpy(substring,&shortstring[j],i);
            substring[i]='\0';
            if(strstr(longstring,substring)!=NULL)
                return substring;
        }
    }
    return NULL;
}
void main(void)
{
    char *str1 = "aocdfe";
    char *str2 = "pmcdfa";
    char *comman = NULL;
    if(strlen(str1)>strlen(str2))
        comman= commanstring(str2,str1);
    else
        comman = commanstring(str1,str2);
    printf("the longest comman string is:%s\n",comman);
}
权重：高
备注：常考

====
试题2：以下为Windows NT下的32位C++程序，请计算sizeof的值
void Func ( char str[100] )
{
    sizeof( str ) = ?
}
void *p = malloc( 100 );
sizeof ( p ) = ? 
解答：
sizeof( str ) = 4
sizeof ( p ) = 4 
剖析：
Func ( char str[100] )函数中数组名作为函数形参时，在函数体内，数组名失去了本身的内涵，仅仅只是一个指针；在失去其内涵的同时，它还失去了其常量特性，可以作自增、自减等操作，可以被修改。
数组名的本质如下：
(1) 数组名指代一种数据结构，这种数据结构就是数组；
例如：
char str[10];
cout << sizeof(str) << endl; 
　　输出结果为10，str指代数据结构char[10]。
(2) 数组名可以转换为指向其指代实体的指针，而且是一个指针常量，不能作自增、自减等操作，不能被修改；
char str[10]; 
str++; //编译出错，提示str不是左值　 
(3) 数组名作为函数形参时，沦为普通指针。
Windows NT 32位平台下，指针的长度（占用内存的大小）为4字节，故sizeof( str ) 、sizeof ( p ) 都为4。
权重：高
备注：理解

====



