# C++总计63个关键字，C语言32个关键字。

#      ![C++关键字](assert\C++关键字.png)



#      C++的一些笔记

### 1、chrono的使用

```c++
#include<chrono>//这个是C++11的新特性


chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
///中间是代码块
、、、
chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
//chrono::duration<double> 也可以换成 auto time_used
cout << "持续时间为：" << time_used.count()<< endl;




```

###  2、typedef

```c++
//为类型创建别名
//typedef为C语言的关键字，作用是为一种数据类型定义一个新名字。这里的数据类型包括内部数据类型（int,char等）和自定义的数据类型（struct等）。 在编程中使用typedef目的一般有两个，一个是给变量一个易记且意义明确的新名字，另一个是简化一些比较复杂的类型声明。

typedef char* PCHAR;//这里char* 和PCHAR就是一样的了
PCHAR pa, pb; 

//define也可以为类型创建别名，但是不适用于声明一系列变量
define FLOAT_POINTER float *
FLOAT_POINTER pa,pb;
//预处理器将该声明转换成这样
float * pa,pb;//这样的话pa是一个指针但是pb只是一个float

//要注意这里是为类型创建别名，分为内部数据类型以及自定义的数据类型

```

### 3、isnan()

```c++
isnan()判断是不是一个NAN值(not a number)
//标准库中定义了一个宏，NAN表示非法数字，负数求对数，负数开方，0.0/0.0等
```



### 4、nullptr和NULL

nullptr在C++中未来区分0和空指针。

```c++
我们应该直接使用nullptr来替代NULL的宏定义。正常使用过程中他们是完全等价的。
#include <iostream>
#include <string>
#include<typeinfo>
using namespace std; 
void func(int* num)
{ 
	cout << "this is the ptr function..." << endl;
}
void func(int num) { 
	cout << "this is the normal function..." << endl;
} 
void main(int argc, char** argv) 
{
	func(NULL);//这里的NULL被编译器解释为0,输出为正常的函数
	func(nullptr);//nullptr就是空指针，不能转换为整数，输出为指针函数
	cout << typeid(NULL).name() << endl;//这里被默认输出了int类型
}
```

``` c++
//一般而言，在堆区创建的数据在程序结束时，首先需要将该数据置空，也就是这个保存这个数据的地址上已经没有数据了，然后我们再将指向该数据的指针置为空指针。如果不置为空指针的话，这个指针还是指向这个地址，后期的话可能还会出错。

int * p=new int(10);//创建指针

delete p;//析构指针
p=NULL;
```



### 5、auto的用法（decltype）循环的高级用法

```c++
//auto可以在声明变量的时候根据变量初始值的类型自动为此变量选择匹配的类型。decltype关键字和它对应。
auto num=1;//num是int类型
decltype(num) num2=num;//num2也是int类型

vector<int>::iterator it = vec.begin();
	for (it; it != vec.end(); it++)
	{
		cout << *it << " ";
	}


	for (auto a : vec)//应该就是依次把vec容器中的数据赋值给a,然后输出a
	{
		cout << a << " ";
	}

	for (int a : vec)//这样也可以，目前还不知道为什么。
	{
		cout << a << " ";
	}
//两者是等价的，可以看出，使用auto关键字更方便
for(auto c:s)与for(auto &c:s)
//前者在遍历操作的时候，相当于赋值了一个s，在循环里面进行s的相关操作的时候不会改变外面的s，这里的s是局部变量。
//后者直接将外面的s传进来，在循环里面对s进行相关操作的时候，是可以改变外面的s的。相当于引用的方式传入进来。

int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
for (int a : arr)//这是列表的这种遍历方法
     cout << a << endl;

//不能使用auto的场景
1.auto不能作为函数的参数
//void TestAuto(auto a){}
//此处代码编译失败，auto不能作为形参的类型，因为编译器无法对a的实际类型进行推导

2.auto不能直接用来声明数组
void TestAuto()
{
	int a[] = {1,2,3,4,5};
	//auto b[] = { 2,3,4,5,6 };
	//auto类型不能出现在顶级数组类型中
}    

//使用for循环的条件
1.范围for的迭代范围必须是确定的。
对于数组而言，就是数组中第一个元素和最后一个元素的范围；对于类而言，应该提供begin和end的方法，begin和end就是for循环的迭代范围。也就是说自定义的数据类型可能是不能用的
2.迭代的对象要实现++和==的操作

```

### 6、argc与argv

```C++
int argc,定义为int。 char **argv或者 char* argv[]字符串数组,存的是参数
arguments count      arguments value
默认情况下下，argc=1;argv[0]="文件的路径";

#include<iostream>
using namespace std;
int main(int argc, char* argv[])
{
    for (int i=0;i<argc;i++)
    {
        cout<<argc<<endl;
        cout << argv[i] << endl;
    }
    system("pause");
    return 0;
}

输出结果:
1
E:\wm\桌面\test\test\Debug\test.exe;

如果运行时输入:Debug\test.exe abc
那么输出结果就是:
2
Debug\test.exe
abc
//从这里可以看出argv保存的是字符串数组
```



### 7、minmax_element

```C++
#include<algorithm>
vector<int> v1;
	v1.push_back(1);
	v1.push_back(7);
	v1.push_back(4);
	v1.push_back(22);
	v1.push_back(101);
	v1.push_back(893);  
	 
	auto res = minmax_element(v1.begin(), v1.end());
	cout << "最小值：" << *(res.first) << endl;
	cout << "最大值：" << *(res.second) << endl;
```



### 8、lambda

```C++
//C++11中引入的匿名函数，在C++的stl算法的使用中，经常可以看到它的身影
[caputrue](params)opt->ret_type{body};
1)capture是捕获列表
2）params是参数列表
3）opt是选填的，可以填mutable,exception,attribute.
   mutable说明lambda表达式体内的代码可以修改被捕获的变量，exception说明表达式是否抛出异常以及何种异常，attribute声明属性
4）ret_type是返回值类型
5）body就是我们正常使用的函数体了。
    虽然lambda中的参数变量很多，通常情况下并不需要把每一个都使用上，根据自己的需要使用即可，大多数情况下可以直接省略->、mutable、exception，不需要返回类型的话也可以省略return type。一个简单的lambda表达式：[](int x){return x*x;}。//方括号中放置铺获的变量
    
auto comp = [](int x){return x*x;}//也可以通过这种方式给匿名函数命名
    
从下面的例子里面可以发现，捕获列表里面可以放数学运算符，或者直接是变量的名字，放上&就代表以引用的方式捕获而来相应的变量
 // 有点相当于函数中的引用传递
```



```c++
// TestLambda.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;



void myPrintf(int elem)
{
	cout << elem << " ";
}



int main()
{
	cout << "-----------lambda表达式的使用----------" << endl;
	vector<int> tmpVector{};
	tmpVector.resize(10);
	int i = 10;
	int num = 0;
	cout << "-----------使用lambda表达给tmpVector赋值----------" << endl;
	generate(tmpVector.begin(), tmpVector.end(), [i, &num]() {//捕获i的值和num的值，传入函数i是以值传递的方式捕获得到，而num是以引用的方式捕获得到的，就可以直接修改捕获得到的变量
		num = i * i + num;
		return num;
		});
	cout << "-----------打印i和num的值，以查看值传递和引用传递的区别----------" << endl;
	cout << "i=" << i << "  num=" << num << endl;
	cout << "-----------打印tmpVector中的值----------" << endl;
	for_each(tmpVector.begin(), tmpVector.end(), myPrintf);
	cout << endl;


	cout << "-----------给lambda表达指定一个名字----------" << endl;
	int a = 100;
	auto bFun = [a]()->int {return a / 10; }; // bFun是lambda表达式的名字
	int c = bFun();
	cout << "c=" << c << endl;

	cout << "-----------lambda表达传形参----------" << endl;
	int countIndex = count_if(tmpVector.begin(), tmpVector.end(),
		[](int x) {
			return x / 1000 == 0; // 找到除以1000等于零的那个数在第几个，注意下标序号从0开始
		})  ;
	cout << "除以1000等于零在vector中的索引为：countIndex=" << countIndex << endl;

	cout << "-----------lambda表达默认捕获外部变量,形参以值传递方式----------" << endl;
	int tmpNum1 = 10;
	int tmpNum2 = 5;
	for_each(tmpVector.begin(), tmpVector.end(), [=](int x) {//捕获前面等于号的值，这里需要说明一下，一般而言，前面两个int类型的值是不能够直接放进一个普通函数的，必须以形参的形式传入到一个普通函数中，这样才可以直接用，而我们用lambda函数来捕获之后，就可以直接在这个lambda匿名函数里面使用，不需要再经过传入的麻烦

		x = x * tmpNum1 + tmpNum2;
		cout << "x=" << x << endl;
		});
    for_each(tmpVector.begin(), tmpVector.end(), myPrintf);
    //这里输出以后，会发现容器里面的值没有发生改变
	cout << endl;

	cout << "-----------lambda表达默认捕获外部变量,形参以引用传递方式----------" << endl;
	for_each(tmpVector.begin(), tmpVector.end(), [=](int& x) {

		x = x * tmpNum1 + tmpNum2;
		cout << "x=" << x << endl;
		});

	for_each(tmpVector.begin(), tmpVector.end(), myPrintf);//注意这里与前面的以值传递的方式传入有一定的区别
    //这里输出以后，会发现容器里面的值发生了改变
	cout << endl;
	std::cout << "Hello World!\n";

	
	system("pause");
	return 0;
}
```



### 9、枚举 enum

```C++
//在CSDN上面收藏的，枚举也是C++11的

enum spectrum { red, orange,yellow,green,blue,violet,indigo,ultraviolet };
//enum 定义了spectrum是枚举类型的变量，里面的内容称为枚举量，默认情况下，将整数值赋给枚举量
//注意里面是逗号，最后一个不能加上逗号，结尾是分号

// 枚举可以转换为int类型，但是int类型不能转换为枚举类型的
int main()
{
    //注意事项1：
    spectrum a = blue;//只能将定义枚举时使用的枚举量赋给这种枚举的变量
    a = yellow;//枚举只有赋值运算符
    //a=3;不合法，不能将int类型的变量赋值给枚举类型
   // a = orange + yellow;不合法
    //++a;
    //注意事项2:枚举量是整形，可以自动转换为int类型，但是int类型不能被转换为枚举类型；（不能发生隐式转换）
    int color = orange;//color为1； 枚举类型直接赋值给整形
    color = orange + 3;//color为4；
    cout << a << endl;//输出2，a被自动转换为int类型
    //注意输出枚举类型的数据是以int类型的数据输出的

    //a = red + orange;不合法，原因是red和orange会被被转换为int类型，但是int类型的不能赋值给枚举类型
    a = (spectrum)3;//这样是合法的，先将整形转换为枚举类型，a=spectrum(3);也是可以的


    //使用：设置枚举量的值
    enum bits { one = 1,two=2,four=4,five,eight=8 };
    //可以自己显示指定枚举变量的值，没有显示指定的，会根据前一个枚举变量+1默认指定
   
    system("pause");
    return 0;
}
```

传统枚举存在一些问题，就是两个定义中的枚举量可能会发生冲突，传统的枚举总是隐式的将枚举变量看做int类型。下面介绍作用域内枚举，作用域内枚举就解决了上述两个问题

```c++
//作用域内枚举
enum eggs {small,medium,large};
enum shirt{small,medium,large,xlarge};//编译器会提示非法，原因是原因是两个枚举位于相同的作用域内

enum class eggs {small,medium,large};
enum class shirt{small,medium,large,xlarge};//也可以将class换成struct

//注意1：使用时，需要枚举名来限定枚举量
eggs a=eggs::large;
shirt b=shirt::small;
//注意2：常规类型的枚举可以自动转换为整形int，但是作用域内枚举不能隐式转换为整形；
eggs a = eggs::small;
//int b = a;报错
int b = (int)a;//显示指定之后就不会报错
```

sw itch语句通常与枚举用到一起,switch语句将值int和枚举量标签进行比较时，将枚举量提升为int类型，在while循环测试条件中，也会将枚举量提升为int类型

```cpp
#include <iostream>
using namespace std;

enum a
{
	red, orange, yellow, green, blue, violet, indigo
};

int main()
{
	using namespace std;
	cout << "输入一个颜色选项（0-6）:\n";
	int code;
	cin >> code;
	while (code >= red && code <= indigo)
	{
		switch (code)
		{
		case red: cout << "选择的是红色的嘴唇\n"; break;
		case orange: cout << "选择的是橘黄色\n"; break;
		case yellow: cout << "选择的是黄色的香蕉\n"; break;
		case green: cout << "选择的是绿色的草地\n"; break;
		case blue: cout << "选择的是蓝色的天空\n"; break;
		case violet: cout << "选择的是violet\n"; break;
		case indigo: cout << "选择的是indigo\n"; break;
		default:
			break;
		}
		cout << "选择0-6这7个数字:\n";
		cin >> code;
	}
	cout << "再见\n";
	return 0;
```

枚举类型也可以作为函数参数传入值

```c++
#include<iostream>
using namespace std;
enum spectrum { red, orange, yellow, green, blue, violet, indigo, ultraviolet };
void test(spectrum color)
{
	cout << "你输入的颜色是：" << color << endl;
}
int main()
{
	spectrum a = green;
	test(a);//枚举类型的变量作为函数参数传入值
	system("pause");
	return 0;
}
```



### 10、assert()函数

```C++
assert(expression)
#include<assert.h>//注意要加上assert的头文件
//如果表达式为真，则函数继续执行，如果表达式为假，那么它先向stderr打印一条出错信息，然后调用abort来终止程序
int a = 1;
int b = 2;
assert((a > b ? 1 : 0));
cout << "assert之后" << endl;//这一段代码是执行不了的
```

### 11、注解

```c++
/**
 * @brief Create new QToolButton
 *
 * @param name Name of button
 * @param iconPath Path to button icon.
 * @return QToolButton Created QToolButton.
*/
QToolButton* createToolButton(QAction *action);
```

### 12、按位或操作

```c++
a|=b //等效于 a=a^b 按位或并赋值;
a^=b //等效于 a=a^b 按位异或并赋值;相异为1，相同为0；(有差别才好)
a&=b //等效于 a=a&b 按位与并赋值
    
d|=1<<k//先把1转换成二进制0001，然后左移k位，得到的结果再与d进行按位或操作；
    
//如何计算一个数用二进制表示的时候1的个数
int cal_1(int a)
{
    int num=0;
    while(a)
    {
        a&=(a-1);//等价与把最右边的1置为0；
        num++;
    }
    return num;
}
//不用新变量交换两个变量的值
a = a ^ b;   b = a ^ b;   a = a ^ b
```



### 13、override(保留字)

有些情况下，我们的父类定义了一个虚函数，但是子类没有覆盖（重写）这个虚函数，而子类中却出现了一个与基类虚函数名相同、但是参数不同的函数，这仍是合法的。编译器会将派生类中新定义的这个函数与基类中原有的虚函数相互独立，这时，派生类的函数没有覆盖掉基类的虚函数版本，虽然程序没有出错，但是却违反了最初的原则

```c++
//1、函数比较多的情况下提示读者某个子类函数重写了基类虚函数（表明这个虚函数是从基类继承，不是派生类自己定义的）
//2、强制编译器检查某个函数是否重写基类虚函数，如果没有就报错
//用法：
class base
{
    virtual void func(){};
};
class son:public base
{
    void func() override
    {};//表示派生类重写基类虚函数
    void Func() override
    {};//报错，函数F没有重写基类任何的函数
};  
//如果编译器发现派生类重写的虚函数与基类的虚函数不一样（参数或其他不一样的地方），那么编译器将报错
```

### 13、final关键字

- 如果我们定义的一个虚函数不想被派生类覆盖（重写），那么可以在虚函数之后添加一个final关键字，声明这个虚函数不可以被派生类所覆盖（重写）
- 如果函数有尾指返回类型，那么要放在尾指返回类型后;



### 14、static_cast显性类型强制转换

```c++
//C语言中的类型转换分为隐式类型转换与显示类型转换
//1、隐式类型转换（很常见）
//2、显示类型转换
int a = 5 % 2.1;//出错误，必须是整形
int k = 5 % (int)2.1;//c语言类型的强制类型转换
int s = 5 % int(2.1);//函数风格的强制类型转换（c语言）
//以上为C语言类型的强制类型转换

//C++类型的强制类型转换分为4种,以下四种强制类型转换都被称为“命名的强制类型转换”，
//通用形式 强制类型转换名<type>(express)   type是要转换目标类型，express是要转换的值
//1)static_cast
int a=static_cast<int>(120.34) //结果为a=120;
    1)编译器隐式执行的任何类型都可以由它完成
    2)可以将void*指针转换为某一类型的指针
    3)可以将基类指针转换为派生类指针（子类与父类）
    但是一般不能用于指针类型的转换，比如int*转换成double*或者float*
//2)dynamic_cast
//3)const_cast
//4)reinterpret_cast
```

### 15、sizeof(type)与typeid(type).name

```c++
int a=10;
sizeof(int);sizeof(a);//输出字节数
cout<<typeid(a).name()<<endl;//输出int
```

### 16、Eigen::aligned_allocator< Eigen::Vector3d > 

```C++
//如果STL容器中的元素是Eigen库数据结构时，比如定义一个vector容器，元素是Matrix4d
vector<Eigen::Matrix4d>
//用这段代码的时候编译不会出错，但是运行的时候就会出错，标准的形式是用下面的类型
typedef std::vector<Eigen::Vector3d, Eig   <Eigen::Vector3d>> VecVector3d;
//这段代码才是标准的定义容器方法，只是一般情况下定义的容器都是C++类型的，所以是可以省略的，在eigen中管理内存和C++11中的方法是不一样的，所以需要单独强调元素的内存分配与管理
```

### 17、cout.precision(val)

```C++
cout.precision(val);//控制输出流输出多少位有效数字，注意是有效数字
//两种方式
//1
cout<<"cost="<<cout.precision(5)<<cost<<endl;//cost输出5位有效数字
//2第二种方式是分开使用
double value=0.0012345;
cout.precison(3);
cout<<value<<endl;
```

### 18、inline关键字

```C++
//inline加在前面就是内联函数的意思
//内联函数的编译代码和其他程序的代码内联起来，也就是不用跳来跳去，编译器将使用相应的函数代码吗替换函数调用
//内联函数不能递归，用于函数代码比较简单地情况下，节省了时间但是牺牲了内存

在 c/c++ 中，为了解决一些频繁调用的小函数大量消耗栈空间（栈内存）的问题，特别的引入了 inline 修饰符，表示为内联函数。
```

### 19、floor函数

```C++
floor(x);//像下取整
double a = 3.9;
cout << int(a) << endl;//cout<<(int)a<<endl;和这个效果是一样的
cout << floor(a)<<endl;
//两者都是向下取整的意思，int(a)返回的还是int类型
//floor之后虽然输出的是整数，但是数据实际上式double类型的数据
cout << typeid(floor(a)).name()<<endl;
```

### 20、bind函数

```C++
//将bind函数看做成一个通用的函数适配器，他接收一个可调用对象，生成一个新的可调用对象来"适应"原对象的参数列表。
//std::bind 是一个函数模板, 它就像一个函数适配器，可以把一个原本接收N个参数的函数fn，通过绑定一些参数，返回一个接收M个参数的函数ret，同时还可以实现参数顺序调整等操作
#include<iostream>
#include<functional>
using namespace std;

class Test1//这是一个测试的类
{
public:
	void fun(int val) 
    {
		cout << "hello world " << val << endl;
	}
    
};
void hello(int val) //这是一个测试的函数式
{
	cout << "val:" << val << endl;
}

int main() {
	Test1 t;
    //成员函数的绑定操作，function<void(int,int)>代表新的生成函数的返回值和形参列表，整个可以用auto来代替
    //注意成员函数的绑定，要把这个（类的函数，以及这个类的实例，后面是参数列表）
	function<void(int,int)> pf = std::bind(&Test1::fun, &t, placeholders:: _1);
    //前面是void(int)说明里面必须要有一个值，所以后面pf里面传入的4虽然用不到，但是必须要有的
	pf(4,4); 
    //placeholders:: _1代表传入的是向函数里面传入的参数是pf(int,int,int,int)里面的第几个参数
    function<void(int)> pf = std::bind(&Test1::fun,t,2);
    pf(4);//这里输入的4是不起任何作用的，但是bind已经把它都给绑定好了，是2。 
    
    
   
    //普通函数的绑定操作，只需要函数名和传入的参数就可以了
    function<void()> fun = std::bind(hello, 2);
	fun();
    
    //反正上面和下面都是
	system("pause");
	return 0;
}

void hello(int a,int b) //这是一个测试的函数式
{
    cout << "a:" <<a <<" b="<<b << endl;
}

int main() {
 
    auto fun = std::bind(hello, std::placeholders::_6, std::placeholders::_3);//这里面的参数列表还是按照函数定义的来的，这里占位符表示的是下面函数里的参数s
    fun(5,9,8,9,0,0);//输出的是a:0 b=8
    system("pause");
    return 0;
```

```c++
class Test//这是一个测试的类
{
public:
    void fun(int val)
    {
        cout << "hello world " << val << endl;
    }
    void fun2()
    {
        auto pf = std::bind(&Test::fun, this, placeholders::_1);//类内部绑定
    }

};
```







  ### 21、boost::format使用

```C++
//c语言有printf这个格式化输出函数，但是缺点是不会做类型安全检查。boost库提供了一个类似printf功能的boost.format
//format组件的构造函数接收string类型作为格式化字符串，并且提供成员函数str()来返回已经格式化好的字符串。
//主要是用来格式化std::string字符串以及配合std::cout代替C语言中的printf
#include<boost/format.hpp>//要包含这个头文件
boost::format("format-string") % arg1 %arg2 %argN;//引号里面
//示例
std::cout<<boost::format("%2% \n %3% \n %4%")%"first"%"second"%"third";//输出second first third
//也可以这样
boost::format fmt("%2% \n %3% \n %4%");
fmt %"first";
fmt %"second";
fmt %"third";

//格式化后的实例付给str
boost::format fmt("%1%") %"helloworld";
std::string st=fmt.str;

    
```

### 22、关于&的一些容易误解的地方

```c++
#include<iostream>
using namespace std;
class test
{
public:
	test(int &a,int &b,int &c): m_a(a),m_b(b),m_c(c) {}
		int get_a() {return m_a;}
		int get_b() {return m_b;}
		int get_c() {return m_c;}
private: int &m_a; int &m_b; int &m_c;//加上&结果会变化，不加上&结果不会变化的。
};//这样的话类内的参数是就是构造函数传进来的参数，类外操作那个数，类内也会发生改变。
int main()
{
	int a = 1,b = 2,c = 3;
	test t(a, b, c);
	cout << "-----before change-----" << endl;
	cout<<t.get_a()<<endl;
	cout<<t.get_b()<<endl;
	cout << t.get_c() << endl;
	cout << "-----after change-----" << endl;
	a = 2; b = 3; c = 4;//又在外面操作这些数，发现类内也是变换了。
	cout << t.get_a() << endl;
	cout << t.get_b() << endl;
	cout << t.get_c() << endl;
	system("pause");
	return 0;
}
```

### 23、explicit关键字

```C++
//类中的构造函数如果只含有一个参数，默认情况下存在一种隐式转换，即定义了转换为此类类型的隐式转换机制。然而，这种机制并非总是合理//的，甚至容易产生错误，因此，新标准增加了explicit关键字，用来限制隐式转换
class Test {
public:
    Test();  // 空构造函数
    Test(double a); // 含一个参数的构造函数
    Test(int a, int b); // 含两个参数的构造函数
    Test(int a, double b = 1.2);  // 带有默认初始值的构造函数
    ~Test();
};

// 调用
Test d1(12.3);  //直接使用默认构造函数
Test d2 = 1.2;  // 也是调用含有一个参数的构造函数，但是包含一次隐式转换
Test d3(12, 13);  
Test d3 = 12;  // 隐式转换，调用带有默认初始值的构造函数Test(int a, double b = 1.2)


//explicit用在类的构造函数前面
class Test {
public:
    Test() {}  // 空构造函数
    explicit Test(double a); // 该构造函数无法进行隐式类类型转换
    explicit Test(int a, int b);  // 含有两个参数，explicit对其无效，然而该构造函数本身也是不能隐式转换的
    explicit Test(int a, double b = 1.2);  // 该构造函数无法进行隐式类类型转换
    ~Test() {}
};

// 调用
Test d1(12.3);  // 正确
Test d2 = 1.2;  // 错误，不能进行隐式类类型转换
Test d3(12, 13);  // 正确
Test d3 = 12;  // 错误，不能进行隐式类类型转换

//explicit就是用来限制隐式类型转换的，用来提升代码的可读性
```

### 24、浮点数的比较

```c++
//两个浮点数不能直接用 == 运算符来判断是否相等，否则往往会得到错误的结果。
//因为两个数值上相等的浮点数，由于计算机内部表示的原因可能会有微小的误差（不同）。
numeric_limits<double>::epsilon//运行编译程序的计算机所能识别的最小非零浮点数
    
#include<cmath>
#include<limits>
double a = 0.0, b = 0.0f;

if (abs(a-b)<=std::numeric_limits<double>::epsilon())
{
	cout << "a=b" << endl;

}
else
{
	cout << "a！=b" << endl;
}
```

### 25、ifndef 防止头文件重复包含的语句

```c++
C++中防止头文件重复包含有两种方式
方式1：
#ifndef RAND_H
#define RAND_H
#endif
//这是防止头文件重复包含的语句
//是指一个头文件在同一个cpp文件中被include了多次，这种错误常常是由于include嵌套造成的。
//比如：存在a.h文件#include "c.h"而此时b.cpp文件导入了#include "a.h" 和#include "c.h"此时就会造成c.h重复引用。这样就会循环展开，造成一定的错误。
//同时也能够防止编译器进行循环展开，
//比如a.h文件中引入了c.h c.h中又引入了a.h， 这样的话两者就会无穷无尽的进行引用。从而最终导致报错
这种方式不仅可以保证同一个文件不会被包含多次，也能保证内容完全相同的两个文件(或者代码片段)不会被不小心同时包含
    
    
一般会采用第二种方式，采用这种方式，内部会进行一个计数，如果多于一个的话，最终则不会去采用。
方式2:#pragma once
一般由编译器提供保证，同一个文件不会被包含多次，这里同一个文件是指物理上的同一个文件而不是内容相同的两个文件

//头文件重复包含的后果
//1）有些头文件重复引用只是增加了编译工作的工作量，不会引起太大的问题，仅仅是编译效率低一些，但是对于大工程而言编译效率低下那将是一件多么痛苦的事情。
//2）有些头文件重复包含，会引起错误，比如在头文件中定义了全局变量(虽然这种方式不被推荐，但确实是C规范允许的)这种会引起重复定义。
    
    
有时候会出现两者混用的情况，先用2再用1
```

### 26、#include <stdlib.h>

```c++
//stdlib.h是standard library标准库头文件，定位在通用工具函数。
//stdlib.h主要封装了malloc()、calloc()、realloc()、free()、system()、atoi()、atol()、rand()、srand()、exit()等函数
rand();//产生一个随机数（伪随机数）返回0至RAND_MAX之间的随机整数值,且0-RAND_MAX每个数字被选中的机率是相同的。
sramd();//srand（）用于设置供rand（）使用的随机数种子
//第一次调用rand()之前如果没有调用srand()，那么系统会自动调用srand()，自动调用传参值为1（就是说种子默认为1）使用相同种子（srand函数传参值相同），调用 rand()生成的是相同随机数序列（同一个种子结出的果实相同）
如果要产生0-99这100个整数中的一个随机整数，可以用int num=rand()%100
如果要产生1-100这100个整数中一个随机整数，可以用int num=rand%100+1
rand()%(b-a+1)+a，表示a-b之间随机产生的一个整数;
a%b//产生数字的范围就是0~b-1;



```

### 27、C语言字符串与C++类型的字符串之间的相互比较

```c++
//在C语言中，字符串以字符数组或指针的形式存储。而C++中则直接引入string类(注意"s"是小写！)。C风格的字符串很容易转化成C++风格的字符串，反过来却可能引起语法错误。
#include <iostream>
#include <string.h>
using namespace std;
int main()
{
     char *str = "hello, world!"; //char str[] = "hello, world!";
     string str2(str); //string str2 = str;
     cout << "C风格：" << str <<endl;
	 cout << "C++风格：" << str2 <<endl;
     return 0;
}


#include <iostream>
#include <string.h>
using namespace std;
int main()
{
string str2("hello, world!");
const char *str = str2.c_str();//把C++类型的字符串转换为C语言类型的字符串,注意前面要加上const
cout << "C++风格：" << str2 <<endl;
cout << "C风格：" << str <<endl;
return 0;
}

//c_str()返回的是const char *类型。在第7行str的声明前加上限定符const，一切就正常了
```



### 28、nth_element()函数

```c++
//使用方法：nth_element(start, start+n, end)
//使第n大元素处于第n位置（从0开始,其位置是下标为n的元素），并且比这个元素小的元素都排在这个元素之前，比这个元素大的元素都排在这个元素之后，但不能保证他们是有序的。这个数的前面虽然都他小，但是前面这些数字不一定是按照从小到大的函数来的。
nth_element(a,a+6,a+10);  //在a中，找到第七小的元素并且将其放到a[6]
int a[10] = { 699,3,45,1,-36,20,42,3,7,12 };
nth_element(a, a + 6, a + 10);  //在a中，找到第七小
cout<<a[6]<<endl;



vector<int> s;
s.push_back(123);
s.push_back(32);
s.push_back(12);
s.push_back(986);
s.push_back(36);
s.push_back(9856);
nth_element(s.begin(), s.begin() + 2, s.end()); 

cout << "排序后" << endl;
for (int i = 0; i < s.size(); i++)
{cout << s[i] << " ";}

cout << endl;
cout << "s中第3小为：" << s[2] << endl;
```



### 29、memcpy函数

```c++
//memcpy指的是c和c++使用的内存拷贝函数，memcpy函数的功能是从源src所指的内存地址的起始位置开始拷贝n个字节到目标dest所指的内存地址的起始位置中
//用法 memcpy(目的地址，源地址，需要拷贝的字节数)
int a[] = { 1,2,3,4,5,6,7,8 };
int b[8];
memcpy(b, a, sizeof(int) * 8);
for(int i=0;i<8;i++)
cout << b[i] << endl;

//最后的输出结果是1,2,3,4,5,6,7,8
//也就是说将a中的数据拷贝到b中了
```



### 30、#include< limits >头文件

```c++
// limits是STL提供的头文件（包含numeric_limits模板类），limit.h是C语言提供的头文件（包含一些宏定义）

```



### 31、类的匿名对象

```c++
struct stdrr
{
public:
    stdrr() {}
public:
    int m_a;
    int m_b;
    int m_c;
};

int main()
{
    stdrr s = stdrr();//这里是把一个匿名对象复制给新创建的一个对象。类名+()
    system("pause");
    return 0;
}

```

### 32、数组名与&数组名

```c++
int arr[10]={0};
cout<<arr<<endl;
cout<<&arr<<endl;
//输出上面两个结果是一样的，但是意义是不一样的。
//&arr表示的是数组的首地址。arr表示的是数组首元素的地址。数组的首地址与数组首元素的地址是一样的。
//&arr+1会跳过整个数组，而arr+1只会跳过数组中的一个元素



//arr等价于&arr[0]
arr与&arr[0]的地址类型为int *,使用int类型的指针接收
//&arr
int *p=(int*)(&arr+1)//指向数组末尾的地址
&arr的地址类型为int(*) [数组长度]类型，使用数组指针来接收
```



### 33、new的默认值

```c++
int* a = new int;
int* b = new int();
cout << *a << "---" << *b << endl;
//输出结果：
-842150451---0;

//由结果可以知道，不叫括号的话，系统会帮你任意指定一个任意值；
//加上（）之后，指向的是一个默认值。也就是0


struct stdrr
{
public:
    stdrr() {}
public:
    int m_a;
    int m_b;
    int m_c;
};
stdrr* s1 = new stdrr();
stdrr* s2 = new stdrr;
cout << s1->m_a << "-" << s1->m_b << "-" << s1->m_c << endl;
cout << s2->m_a << "-" << s2->m_b << "-" << s2->m_c << endl;
//最后输出的结果是一样的，对于类而言貌似又是一样的
```



### 34、C++中查看变量数据类型

```C++
#include<typeinfo>//包含种类信息的头文件
cout<<typeid(data).name()<<endl;//输出变量类型名，data就是我们需要知道的变量类型

bool:                     b
 
char:                     c
signed char:              a
unsigned char:            h
 
(signed) short (int):     s
unsigned short (int):     t
 
(signed) (int):           i
unsigned (int):           j
 
(signed) long (int):      l
unsigned long (int):      m
 
(signed) long long (int): x
unsigned long long (int): y
 
float:                    f
double:                   d
long double:              e
```



### 35、to_string()函数

```c++
to_string()系列函数将数值转换成字符串形式。
string to_string(int val);
string to_string(long val);
string to_string(long long val);
string to_string(unsigned val);
string to_string(unsigned long val);
string to_string(unsigned long long val);
string to_string(float val);
string to_string(double val);
string to_string(long double val);

//注意在visual studio中使用时需要包括头文件#include<string>
```

### 36、void*与void 指针

```c++
指针有两个属性：指向对象/变量的地址和长度，指针只存储地址，长度取决于指针的类型
int*从指定地址向后寻找4字节作为变量的存储单元
double*从指定地址向后寻找8字节作为变量的存储单元void *是一种特别的指针，这个类型不能判断出指向对象的长度

void *的指针没有指定跳跃的步长
普通类型的指针指定了跳跃的步长。
//void字面意思是“无类型”，void*为无类型指针，void*可以指向任何类型的指针 
int a;
void * p1;
int* p2=&a;
p1 = p2;//可以把其他任何指针赋值给void*

void* myfunc(void* args)//说明返回值类型可以为任何类型的指针，函数传入的参数也可以为任何类型的指针
{
	cout << "hello" << endl;
	return NULL;
}

int main()
{
	
	int* p = new int;
	myfunc(p);//这里面的p可以改成NULL，nullprt,NULL等等

	system("pause");
	return 0;
}
```

### 37、char ** a与char * arr[]区别

```c++
//1、char ** a
在这个语句中，a是一个指针，这个指针指向一块内存地址，该内存地址保存（指向）的是 char* 类型的数据。指针的加法在这里体现为a+1表示地址加上8个字节。
char* 也是一个指针，用*a表示，这个指针指向（保存）一块内存地址，该地址中保存的是 char 类型的数据。指针的加法在这里体现为 （*a）+1表示地址加上一个字节
    
//2、char* arr[]
在char* arr[]中，arr是数组，数组中的元素是指针，这些指针指向char类型当然数据
注意：数组里面所有的元素，在内存中都是连续存放的
    
//两者都可以作为程序的传入参数
int main(int argc,char ** argv)
int main(int argc,char * argv[])
```



### 38、（字符串的一些备注）C++中字符串所占用的字节个数

```c++
字符串所占用的字节数是字符串里面包含的字符个数+1，因为编译器会自动在字符串末尾加上/0，代表这个字符串结束的标志位
char * 字符串与 char str[] 字符串的理解；
const char* str = "test";//用char*来表示字符串，前面必须加上const
cout <<str<< endl;//这时候会输出 test
//按理来说这个地方应该是输出字符串"test"的地址，但是并不是输出地址
//如果再把指针++
str++;cout<<str<<endl;
//这时候会输出 est
char str[]="test";等价于 char str[]={"t","e","s","t"};
cout<<test<<endl;//这最后都会输出 test


```

### 39、define 宏定义的时候后面不要加上分号

```c++
#define MAX_SIZE 1000;//注意这里宏定义的时候不能加上逗号

```



### 40、输出运行的时间

```c++
在终端里面运行的时候，在前面加上 time 后，最后会输出运行的时间
例如：time ../test5
```

### 41、class 与 struct的一个小区别

```c++
class cla
{
	int a;
	int b;
};

struct str
{
	int a;
	int b;
};

//cla a = { 1,2 };这样是不合法的；
str ss = { 1,2 };//这样是合法的，结构体这样是合法的

```

### 42、namespace的用法

在C/C++中，变量、函数和后面要学的类都是大量存在的，这些变量、函数和类的名称都将存在于全局作用域中，可能会导致很多冲突。使**用命名空间的目的是对标识符的名称进行本地化，以避免命名冲突或名字污染**，namespace关键字的出现就是针对这种问题的。

```c++
//命名空间定义：C++中所有的命名空间都是有命名的，没有命名的是主命名空间，如果不加命名空间的作用域，那就是主命空间。

//1、普通的命名空间
namespace N1  // N1为命名空间的名称
{
	//命名空间中的内容，既可以定义变量，也可以定义函数
	int a;
	int Add(int x, int y)
	{
		return x + y;
	}
}

//2、命名空间可以嵌套
namespace N2
{
	int a;
	int b;
	int Add(int x, int y)
	{
		return x + y;
	}
	namespace N3
	{
		int c;
		int d;
		int Sub(int x, int y)
		{
			return x - y;
		}
	}
}

//3、同一个工程中允许存在多个相同名称的命名空间，编译器最后会合成同一个命名空间
namespace N4
{
	int Mul(int x, int y)
	{
		return x * y;
	}
}
```

命名空间的使用

```cpp
//1、指定命名空间名称及作用域限定符（麻烦，每一个地方都要指定，但也是最规范的方式）
int main()
{
	std::cout << "hello" << std::endl;
	std::vector<int> v;
	std::string s;
	return 0;
}

//2、使用using namespace 命名空间名称引入（即把std整个展开，相当于库里面的东西全部都到全局域里面了，这样看起来是方便了，但如果我们定义的东西与库里面的东西冲突，那么就没有办法解决了，所以规范的工程项目不推荐使用这一种方式）
using namespace std;
int main()
{
	cout << "hello" << endl;
	vector<int> v;
	string s;
	return 0;
}

//3、使用using将命名空间中成员引入（对部分常用的库里面的东西展开，项目中比较常用）
using std::cout;
using std::endl;
int main()
{
	cout << "hello" << endl;
	return 0;
}
```



### 43、C++智能指针 std::unique_ptr

```c++
//C++智能指针一共有三个，std::unique_ptr、std::shared_ptr和std::weak_ptr
//普通指针是指针，智能指针本质上是一个一个类，所以普通指针是不能够直接赋值给智能指针的，但是可以通过构造函数的方式来传入
//智能指针的头文件是#include<memory>

一、std::unique_ptr 对其持有的堆内存具有唯一拥有权，也就是说引用计数永远是 1;std::unique_ptr 对象销毁时会释放其持有的堆内存。可以使用以下方式初始化一个;
//初始化方式1  用构造函数
std::unique_ptr<int> sp1(new int(123));

//初始化方式2  用类内方法，reset函数
std::unique_ptr<int> sp2;
sp2.reset(new int(123));

//初始化方式3  使用另外一个类来创建
std::unique_ptr<int> sp3 = std::make_unique<int>(123); //使用make_unique来创建
//尽量使用方式三来初始化对象，因为这样更加安全

二、std::unique_ptr 禁止复制语义，为了达到这个效果，std::unique_ptr 类的拷贝构造函数和赋值运算符（operator =）被标记为 delete;

std::unique_ptr<int> sp1(std::make_unique<int>(123));;
//以下代码无法通过编译
//std::unique_ptr<int> sp2(sp1);
//std::unique_ptr<int> sp3;
//sp3 = sp1;

//但是禁止复制也存在特例，可以通过一个函数返回std::unique_ptr
std::unique_ptr<int> func(int val)
{
	std::unique_ptr<int> up(new int(val));
	return up;
}
int main()
{
	std::unique_ptr<int> sp1 = func(123);
	system("pause");
	return 0;
}

//既然 std::unique_ptr 不能复制，那么如何将一个 std::unique_ptr 对象持有的堆内存转移给另外一个呢？答案是使用移动构造，示例代码如下：
std::unique_ptr<int> sp1(std::make_unique<int>(123));
std::unique_ptr<int> sp2(std::move(sp1));//通过移动构造

std::unique_ptr<int> sp3;
sp3 = std::move(sp2);
//以上代码利用 std::move 将 sp1 持有的堆内存（值为 123）转移给 sp2，再把 sp2 转移给 sp3。最后，sp1 和 sp2 不再持有堆内存的引用，变成一个空的智能指针对象。


//创建10个int类型的堆对象
//形式1
std::unique_ptr<int[]> sp1(new int[10]);

//形式2
std::unique_ptr<int[]> sp2;
sp2.reset(new int[10]);
//形式3
std::unique_ptr<int[]> sp3(std::make_unique<int[]>(10));

```



### 44、C++智能指针 std::shared_ptr

```c++
//std::shared_ptr 和 std::weak_ptr 也可以持有一组堆对象，用法与 std::unique_ptr 相同，下文不再赘述。
std::shared_ptr 持有的资源可以在多个 std::shared_ptr 之间共享，每多一个 std::shared_ptr 对资源的引用，资源引用计数将增加 1，每一个指向该资源的 std::shared_ptr 对象析构时，资源引用计数减 1，最后一个 std::shared_ptr 对象析构时，发现资源计数为 0，将释放其持有的资源。
std::shared_ptr 提供了一个 use_count() 方法来获取当前持有资源的引用计数。除了上面描述的，std::shared_ptr 用法和 std::unique_ptr 基本相同。
三种初始化方式:
//初始化方式1   通过构造函数
std::shared_ptr<int> sp1(new int(123));

//初始化方式2   通过类内方法
std::shared_ptr<int> sp2;
sp2.reset(new int(123));

//初始化方式3   通过其他类
std::shared_ptr<int> sp3;
sp3 = std::make_shared<int>(123);

class A
{
public:
    A()
    {
        std::cout << "A constructor" << std::endl;
    }

    ~A()
    {
        std::cout << "A destructor" << std::endl;
    }
};

int main()
{
    {//作用域，离开作用域对象会被销毁
        //初始化方式1
        std::shared_ptr<A> sp1(new A());
        std::cout << "use count: " << sp1.use_count() << std::endl;//通过use_count()方法来获取引用次数

        //初始化方式2
        std::shared_ptr<A> sp2(sp1);
        std::cout << "use count: " << sp1.use_count() << std::endl;

        sp2.reset();//通过设置空指针
        std::cout << "use count: " << sp1.use_count() << std::endl;

        {
            std::shared_ptr<A> sp3 = sp1;
            std::cout << "use count: " << sp1.use_count() << std::endl;
        }

        std::cout << "use count: " << sp1.use_count() << std::endl;
    }//离开最后一个作用域之后其引用次数为0，此时会自动销毁
        system("pause");
        return 0;
}

运行结果：
A constructor
use count: 1
use count: 2
use count: 1
use count: 2
use count: 1
A destructor
    
实际开发中，有时候需要在类中返回包裹当前对象（this）的一个 std::shared_ptr 对象给外部使用，C++ 新标准也为我们考虑到了这一点，有如此需求的类只要继承自 std::enable_shared_from_this 模板对象即可；  
类 A 的继承 std::enable_shared_from_this 并提供一个 getSelf() 方法返回自身的 std::shared_ptr 对象，在 getSelf() 中调用 shared_from_this() 即可
class A : public std::enable_shared_from_this<A>
{
public:
    A()
    {
        std::cout << "A constructor" << std::endl;
    }
    ~A()
    {
        std::cout << "A destructor" << std::endl;
    }
    std::shared_ptr<A> getSelf()//这个成员函数是继承过来的，但是是管理堆区对象的，不能用于管理栈区对象
    {
        return shared_from_this();//可以理解为this指针，返回他本身
    }
};

int main()
{
    std::shared_ptr<A> sp1(new A());
    std::shared_ptr<A> sp2 = sp1->getSelf();//这个函数返回的是他本身
    std::cout << "use count: " << sp1.use_count() << std::endl;//输出结果是2
    return 0;
}
陷阱一：不应该共享栈对象的 this 给智能指针对象
//将上诉代码改成这样
int main()
{
    A a;//这个对象是保存在栈区的而不是堆区的
    std::shared_ptr<A> sp2 = a.getSelf();
    std::cout << "use count: " << sp2.use_count() << std::endl;
    return 0;
}
栈对象会在函数调用结束后自行销毁，因此不能通过 shared_from_this() 将该对象交由智能指针对象管理。
//智能指针最初设计的目的就是为了管理堆对象的（即那些不会自动释放的资源）。不能用于管理栈对象。
    
陷阱二：避免 std::enable_shared_from_this 的循环引用问题
#include <iostream>
#include <memory>
class A : public std::enable_shared_from_this<A>
{
public:
    A()
    {
        m_i = 9;
        std::cout << "A constructor" << std::endl;
    }

    ~A()
    {
        m_i = 0;
        std::cout << "A destructor" << std::endl;
    }

    void func()
    {
        m_SelfPtr = shared_from_this();//把对象本身又赋值给类内地成员对象
    }

public:
    int  m_i;
    std::shared_ptr<A>  m_SelfPtr;
};

int main()
{
    {
        std::shared_ptr<A> spa(new A());
        spa->func();//调用这段函数代码之后，会发现spa里面保存了一个指针，这个指针保存的地址就是spa
        //这个时候spa的引用次数为2；
    }//离开这个作用域，引用次数只是减少1，并没有变为0，因此spa并不会释放，也就不会调用析构函数
    system("pause");
    return 0;
}
//上述程序运行的结果是只调用了A的构造函数，而没有调用A的析构函数。spa 出了其作用域准备析构，在析构时其发现仍然有另外的一个 std::shared_ptr 对象即 A::m_SelfPtr 引用了 A，因此 spa 只会将 A 的引用计数递减为 1，然后就销毁自身了。现在留下一个矛盾的处境：必须销毁 A 才能销毁其成员变量 m_SelfPtr，而销毁 m_SelfPtr 必须先销毁 A。这就是所谓的 std::enable_shared_from_this 的循环引用问题。
```

### 45、C++智能指针std::weak_ptr

```c++
std::weak_ptr 是一个不控制资源生命周期的智能指针，是对对象的一种弱引用，只是提供了对其管理的资源的一个访问手段，引入它的目的为协助 std::shared_ptr 工作。std::weak_ptr 可以从一个 std::shared_ptr 或另一个 std::weak_ptr 对象构造，std::shared_ptr 可以直接赋值给 std::weak_ptr ，也可以通过 std::weak_ptr 的 lock() 函数来获得 std::shared_ptr。它的构造和析构不会引起引用计数的增加或减少。std::weak_ptr 可用来解决 std::shared_ptr 相互引用时的死锁问题（即两个std::shared_ptr 相互引用，那么这两个指针的引用计数永远不可能下降为 0， 资源永远不会释放）。

//从下面可以看出weak_ptr不能直接定义智能指针对象，必须依靠shared_ptr或者已经存在的weak_ptr来创建新指针
int main()
{
    //创建一个std::shared_ptr对象
    std::shared_ptr<int> sp1(new int(123));
    std::cout << "use count: " << sp1.use_count() << std::endl;

    //通过构造函数得到一个std::weak_ptr对象
    std::weak_ptr<int> sp2(sp1);
    std::cout << "use count: " << sp1.use_count() << std::endl;

    //通过赋值运算符得到一个std::weak_ptr对象
    std::weak_ptr<int> sp3 = sp1;
    std::cout << "use count: " << sp1.use_count() << std::endl;

    //通过一个std::weak_ptr对象得到另外一个std::weak_ptr对象
    std::weak_ptr<int> sp4 = sp2;
    std::cout << "use count: " << sp1.use_count() << std::endl;

    return 0;
}//上述代码最后的输出结果全为1

既然，std::weak_ptr 不管理对象的生命周期，那么其引用的对象可能在某个时刻被销毁了，如何得知呢？std::weak_ptr 提供了一个 expired() 方法来做这一项检测，返回 true，说明其引用的资源已经不存在了；返回 false，说明该资源仍然存在。
std::weak_ptr 类没有重写 operator-> 和 operator 方法，因此不能像 *std::shared_ptr 或 std::unique_ptr 一样直接操作对象，同时 std::weak_ptr 类也没有重写 operator! 操作，因此也不能通过 std::weak_ptr** 对象直接判断其引用的资源是否存在：

#include <memory>
class A
{
public:
    void doSomething() {}
};
int main()
{    
    std::shared_ptr<A> sp1(new A());
    std::weak_ptr<A> sp2(sp1);
    //正确代码
    if (sp1)
    {
        //正确代码
        sp1->doSomething();
        (*sp1).doSomething();
    }
    //正确代码
    if (!sp1){ }

    //错误代码，无法编译通过
    //if (sp2)
    //{
    //    //错误代码，无法编译通过
    //    sp2->doSomething();
    //    (*sp2).doSomething();
    //}

    //错误代码，无法编译通过
    //if (!sp2){}
    return 0;
}
```



### 46、C++智能指针的大小

```c++
在 32 位机器上，std_unique_ptr 占 4 字节，std::shared_ptr 和 std::weak_ptr 占 8 字节；在 64 位机器上，std_unique_ptr 占 8 字节，std::shared_ptr 和 std::weak_ptr 占 16 字节。也就是说，std_unique_ptr 的大小总是和原始指针大小一样，std::shared_ptr 和 std::weak_ptr 大小是原始指针的 2 倍。

```



### 47、unordered_map容器的用法

```c++
#include<iostream>
using namespace std;
#include<unordered_map>//无顺序的map容器

int main()
{
    typedef unordered_map<int, string> typem;
    typem m1; 
    m1.insert(make_pair(1, "wangming"));
    m1.insert(make_pair(2, "shaolin"));

    for (auto& str : m1)
    {
        cout << str.first << endl;
        cout << str.second << endl;
    }

    system("pause");
    return 0;
}
```

```
输出结果：
1
wangming
2
shaolin
```

### 48、std::weak_ptr的lock()成员函数

```c++
#include<iostream>
using namespace std;
#include<memory>
#include<typeinfo>
int main()
{
    std::shared_ptr<int> sp(new int(10));
    std::weak_ptr<int> swp = sp;
    auto a = swp.lock();
    cout << *a << endl;
    cout << typeid(a).name() << endl;
    /*
     *.lock()方法的功能是：判断weak_ptr所指向的shared_ptr对象是否存在。
     *若存在，则这个lock方法会返回一个指向该对象的shared_ptr指针；
     *若它所指向的这个shared_ptr对象不存在，则lock()函数会返回一个空的shared_ptr。
    */
    system("pause");
    return 0;
}
```

```C++
输出：
10
class std::shared_ptr<int>
```

### 49、std::weak_ptr的reset()成员函数

```c++
#include<iostream>
using namespace std;
#include<memory>
#include<typeinfo>
int main()
{
    std::shared_ptr<int> sp(new int(10));
    std::weak_ptr<int> swp(sp);
    auto a = swp.lock();

    swp.reset();//此时swp为空指针了，，注意并不返回任何值；auto p=swp.reset();是错误的表达
  //在弱引用weak_ptr中，.reset()方法的作用是将该弱引用指针设置为空nullptr
  //但不影响指向该对象的强引用数量，只会使得其弱引用数量减少。
    system("pause");
    return 0;
}
```



### 50、C++中最常用的读文件的操作

```c++
//C++中比较常用的读文件的操作

```



   ### 51、函数指针

```c++
#include<iostream>
#include<functional>
using namespace std;

//函数名就是函数指针
int fun(int x, int y)
{
    cout << x + y << endl;
    return x + y;
}

//fun1的第一个形参是函数指针
int fun1(int (*fp)(int, int), int x, int y)//int (*fp)(int, int)是一个函数指针，这个指针是函数，也相当于一个数据类型；
{
    return fp(x, y);
}

    typedef int(*Ftype)(int, int);//定义了一个函数指针类型

int fun2(Ftype fp, int x, int y)
{
    return fp(x, y);
}
int main() {
    fun1(fun, 1, 2);
    fun2(fun, 3, 4);
    system("pause");
    return 0;
}
```

### 53、windows下的睡眠函数

```c++
#include<iostream>
#include<windows.h>//头文件
using namespace std;

int main() {
   
    while (1)
    {
        cout << "nihao" << endl;
        Sleep(1000);//大写，里面的单位是ms
    }
 
    system("pause");
    return 0;
}



linux环境下：
#include<unistd.h>
sleep(200);//小写
```

### 54、ref函数

```c++
#include<iostream>
#include<windows.h>
using namespace std;

int main() {
    int a=1;
    int c = ref(a);
    int &b = a;
    cout << "c=" << c << endl;
    cout << "&c="<<&c << endl;
    cout << "&a=" << &a << endl;
    cout << "&b=" << &a << endl;
    system("pause");
    return 0;
}
```

```c++
输出为：
c=1
&c=0097FB50
&a=0097FB5C
&b=0097FB5C
请按任意键继续. .
//可以看出引用的地址是一样的，而使用ref则是不同的
```

### 55、extern关键字

```c++
//当extern语句出现在头文件中，不要将声明与定义在一条语句中给出
//extern int a=0;//这句话写在头文件中是不建议的

extern//声明与定义的区别，定义只有一次，但是声明没有限制，可以有很多次，所以不能将定义和声明都放一起
    
    
在C语言中，修饰符extern用在变量或者函数的声明前，用来说明“此变量/函数是在别处定义的，要在此处引用”。

1：extern修饰变量的声明。举例来说，如果文件a.c需要引用b.c中变量int v，就可以在a.c中声明extern int v，然后就可以引用变量v。这里需要注意的是，被引用的变量v的链接属性必须是外链接（external）的，也就是说a.c要引用到v，不只是取决于在a.c中声明extern int v，还取决于变量v本身是能够被引用到的。这涉及到c语言的另外一个话题－－变量的作用域。能够被其他模块以extern修饰符引用到的变量通常是全局变量。还有很重要的一点是，extern int v可以放在a.c中的任何地方，比如你可以在a.c中的函数fun定义的开头处声明extern int v，然后就可以引用到变量v了，只不过这样只能在函数fun作用域中引用v罢了，这还是变量作用域的问题。对于这一点来说，很多人使用的时候都心存顾虑。好像extern声明只能用于文件作用域似的。

2：extern修饰函数声明。从本质上来讲，变量和函数没有区别。函数名是指向函数二进制块开头处的指针。如果文件a.c需要引用b.c中的函数，比如在b.c中原型是int fun(int mu)，那么就可以在a.c中声明extern int fun（int mu），然后就能使用fun来做任何事情。就像变量的声明一样，extern int fun（int mu）可以放在a.c中任何地方，而不一定非要放在a.c的文件作用域的范围中。对其他模块中函数的引用，最常用的方法是包含这些函数声明的头文件。

使用extern和包含头文件来引用函数有什么区别呢？
extern的引用方式比包含头文件要简洁得多！extern的使用方法是直接了当的，想引用哪个函数就用extern声明哪个函数。这大概是KISS原则的一种体现吧！这样做的一个明显的好处是，会加速程序的编译（确切的说是预处理）的过程，节省时间。在大型C程序编译过程中，这种差异是非常明显的。

3：此外，extern修饰符可用于指示C或者C++函数的调用规范。比如在C++中调用C库函数，就需要在C++程序中用extern “C”声明要引用的函数。这是给链接器用的，告诉链接器在链接的时候用C函数规范来链接。主要原因是C++和C程序编译完成后在目标代码中命名规则不同。
```



### 56、exit(0)

```c++
//退出当前程序
```

### 57、strcmp()函数

```c++
//字符串函数strcmp
strcmp比较两个字符串的大小，一个字符一个字符比较，按ASCLL码比较
标准规定：
第一个字符串大于第二个字符串，则返回大于0的数字
第一个字符串等于第二个字符串，则返回0
第一个字符串小于第二个字符串，则返回小于0的数字
```

### 58、函数名作为函数传入参数

```c++
#include<iostream>
using namespace std;
//函数名作为参数可以用(*func)来表示


int add(int x, int y)   // 定义函数 
{
	return x + y;
}

int subtract(int x, int y)   // 定义函数 
{
	return x - y;
}

// 函数作为参数传递给函数
// operation的参数为函数指针， 还有输入参数x,y 
int operation(int (*func)(int, int), int x, int y)
{
	return (*func)(x, y);
}


void sayHello()   // 无参数和返回值的函数 
{
	cout << "Hello" << endl;
}


void sayGoogbye()  // 无参数和返回值的函数
{
	cout << "goodbye" << endl;
}

void greet(void (*func)())//函数名用(*func)来表示
{
	(*func)();   // 调用函数 
}

void saySomething(string s)   // 定义有参数但没有返回值的函数 
{
	cout << "Hello " << s << endl;
}

void greetSomeone(void (*func)(string), string word)//里面并不一定要是func，改成其他的也是可以的
{
	(*func)(word);   // 调用函数 
}


int main(int argc, char* argv[])
{
	//binaryTree<int> tree; 
	cout << operation(add, 3, 4) << endl;
	cout << operation(subtract, 10, 5) << endl;
	greet(sayHello);
	greet(sayGoogbye);
	greetSomeone(saySomething, string("Elithbeas"));
	return 0;
}
```

### 59、mallo的用法

```c++
//也是在堆区创建一个数据
//使用方法
int * p=(int *)malloc(sizeof(int*));//创建时需要确定出创建数据的大小，注意这个大小指的是堆区上保存的数据，不是字节数。
//malloc返回的是void*类型的指针，需要先将其转化为int*类型的指针
//与new差不多，也是在堆区创建数据，最后需要释放
//采用free来释放
free(p);//注意free是一个函数，这是与delete不同的地方。
```

### 60、pair和make_pair()

一、pair 的介绍

pair 是一个很实用的 "小玩意"，当想要将两个元素绑在一起作为一个合成元素、又不想要因此定义[结构体](https://so.csdn.net/so/search?q=结构体&spm=1001.2101.3001.7020)时，使用 pair 可以很方便地作为一个代替品。也就是说，pair 实际上可以看作一个内部有两个元素的结构体，且这两个元素的类型是可以指定的，如下

```c++
struct pair
{
	typeName1 first;
	typeName2 second;
};
```

二、pair 的定义

要使用 pair，应先添加头文件 #include <utility>，并在头文件下面加上 " using namespace std; " ，然后就可以使用了。

注意：由于 map 的内部实现中涉及 pair，因此添加 map 头文件时会自动添加 utility 头文件，此时如果需要使用 pair ，就不需要额外再去添加 utility 头文件了。

```c++
// pair 有两个参数，分别对应 first 和 second 的数据类型，它们可以是任意基本数据类型或容器。
pair<typeName1, typeName2> name;
 
// 想要定义参数为 string 和 int 类型的 pair，如下：
pair<string, int> p;
 
//如果想在定义 pair 时进行初始化，只需要跟上一个小括号，里面填写两个想要初始化的元素即可；
pair<string, int> p("haha",5);//这样就很类似于构造函数
```

```c++
//如果想要在代码中临时构建一个 pair，有如下两种方法：
 
// (1) 将类型定义写在前面，后面用小括号内两个元素的方式。
pair<string, int>("haha", 5);
 
// (2) 使用自带的 make_pair 函数。
make_pair("haha", 5)
```

三、pair 中元素的访问

pair 中只有两个元素，分别是 first 和 second ，只需要按正常结构体的方式去访问即可。

```c++
#include <iostream>
#include <utility>
#include <string>
using namespace std;
 
int  main()
{
    //第一种构建方法
	pair<string, int> p;
	p.first = "haha";
	p.second = 5;
	cout << p.first << " " << p.second << endl;
    
    //第二种构建方法
	p = make_pair("xixi", 55);
	cout << p.first << " " << p.second << endl;
    
    //把匿名对象给传给P
	p = pair<string, int>("heihei", 555);
	cout << p.first << " " << p.second << endl;
	return 0;
}
```

四、pair 常用函数实例解析

两个 pair 类型数据可以直接使用 ==，！=，<，<=，>，>= 比较大小，比较规则是先以 first 的大小作为标准，只有当 first 相等时才去判别 second 的大小。

（1）比较操作数

```c++
#include <cstdio>
#include <utility>
using namespace std;
 
int  main()
{
	pair<int, int> p1(5,10);
	pair<int, int> p2(5, 15);
	pair<int, int> p3(10, 5);
	if (p1<p3)
	{
		printf("p1 < p3\n");
	}
	if (p1 <= p3)
	{
		printf("p1 <= p3\n");
	}
	if (p1 < p2)
	{
		printf("p1 < p2\n");
	}
	return 0;
}
```

五、pair 的常见用途

关于 pair 有两个比较常见的例子：
（1）用来代替二元结构体及其构造函数，可以节省编码时间。

（2) 作为 map 的键值对来进行插入，如下。

```c++
#include <iostream>
#include <string>
#include <map>
using namespace std;
 
int  main()
{
	map<string, int> mp;
	mp.insert(make_pair("hah",5));
	mp.insert(pair<string,int>("heihei", 10));
	for (map<string, int>::iterator it = mp.begin(); it != mp.end(); it++)
	{
		cout << it->first << " " << it->second << endl;
	}
	return 0;
}  
```

### 61、typename的用法

```c++
#include<iostream>
using namespace std;
template<typename T>
class Person
{
public:
	Person(T tc) :t(tc) {};
	typename void pt(typename T ts)//这里的typename貌似只是一个声明的作用，并没有其他作用
	{
		cout << "年龄：" << ts << endl;
	}
	T t;
};

int main()
{
	Person<int> p1(10);
	p1.pt(20);
	system("pause");
	return 0;
}
```

### 63、boost库中filesystem中path的使用



```c++
#include <iostream>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;

int main(int argc, char* argv[])
{
    string filePath = "/work/test/testPath";
    string fileName = "test_path.txt";

    //path("/work/test/testPath/test_path.txt");
    boost::filesystem::path testFilePath(filePath);

    // 使用'/'追加路径，并把路径转化成字符串
    string fullFilePath = (testFilePath / fileName).string();
    cout << "fullFilePath:" << fullFilePath << endl;

    if (!testFilePath.empty())
        cout << "path is not empty" << endl;
    // 取fullFilePath中的部分路径
    boost::filesystem::path workPath(fullFilePath.begin(), fullFilePath.begin() + 5);
    cout << "workPath:" << workPath << endl;
    // 追加路径'/='
    workPath /= "testPath";
    cout << "workPath append path:" << workPath << endl;
    // 追加字符序列append
    workPath.append(fileName.begin(), fileName.end());
    cout << "workPath append string file:" << workPath << endl;

    // 返回当前文件系统下的绝对路径system_complete
    cout << "system_complete:" << system_complete(workPath) << endl;

    // 返回标准格式的文件路径string()
    cout << "string():" << workPath.string() << endl;

    // 返回文件通用路径
    if (workPath.is_absolute())
        cout << "generic_string():" << workPath.generic_string() << endl;

    // 返回路径中的父路径
    if (workPath.has_parent_path())
        cout << "parent_path():" << workPath.parent_path() << endl;

    // 不含扩展名的全路径
    if (workPath.has_stem())
        cout << "stem():" << workPath.stem() << endl;

    // 返回文件名
    if (workPath.has_filename())
        cout << "filename():" << workPath.filename() << endl;

    // 返回文件扩展名
    cout << "extension():" << workPath.extension() << endl;

    // 返回路径根目录
    if (workPath.has_root_path())
        cout << "root_path():" << workPath.root_path() << endl;

    // 返回根名称
    if (workPath.has_root_name())
        cout << "root_name():" << workPath.root_name() << endl;

    // 返回相对路径
    if (workPath.has_relative_path())
        cout << "relative_path():" << workPath.relative_path() << endl;

    // 返回root文件夹目录
    if (workPath.has_root_directory())
        cout << "root_directory():" << workPath.root_directory() << endl;

    // 变更文件扩展名(只是看起来像更改了，实际的文件名字并没有发生变化)
    cout << "replace_extension() remove:" << workPath.replace_extension() << endl; // 删除扩展名
    cout << "replace_extension() change:" << workPath.replace_extension("go") << endl; // 更改扩展名

    // 删除文件名
    cout << "remove_filename():" << workPath.remove_filename() << endl;

    cout << "Hello World!" << endl;
    return 0;
}
```

### 63、time(0)函数与time(NULL)

```cpp
//time(0)函数返回自格林尼治标准时间1970年1月1日00:00:00至当前时刻所流逝的秒数。
```

### 64、rand与srand()函数

当前普通的随机数生成就是这样生成的

```c++
//srand()用来初始化随机数种子,rand()用来产生随机数。rand()用来产生随机数的默认随机数种子是1
一、rand()
  函数名:   rand   
  功   能:   随机数发生器 
  用   法:   int rand(void);  
  所在头文件: stdlib.h
函数说明 :
rand()的内部实现是用线性同余法做的，它不是真的随机数，因其周期特别长，故在一定的范围里可看成是随机的。
rand()返回一随机数值的范围在0至RAND_MAX 间。RAND_MAX的范围最少是在32767之间(int)。用 unsigned int 双字节是65535，四字节是4294967295的整数范围。0~RAND_MAX每个数字被选中的机率是相同的。                      
用户未设定随机数种子时，系统默认的随机数种子为1。
rand()产生的是伪随机数字，每次执行时是相同的;若要不同,用函数srand()初始化它。
    
    
二、srand()
  函数名:   srand   
  功   能:   初始化随机数发生器   
  用   法:   void srand(unsigned  int  seed); //;里面传入一个int类型的指针 
  所在头文件： stdlib.h  
  函数说明：
srand()用来设置rand()产生随机数时的随机数种子。
参数seed必须是个整数，通常可以利用time(0)的返回值或NULL来当做seed。
如果每次seed都设相同值，rand()所产生的随机数值每次就会一样。
      
//通常生成随机数的方法
#include <iostream>
using namespace std;

int main()
{
    srand(time(0));

    int x = rand();
    cout << "x: " << x << endl;

    return 0;
}

```

### 65、new的一些问题() 小括号还是中括号

```c++
#include<iostream>
using namespace std;
int main()
{
	int* p =new int( 10 );
	int* p2 = new int{ 10 };//不知道为啥，这两个输出都是一样的
    两者好像都是一样的
    
	cout << *p << endl;
	cout << *p2 << endl;
	system("pause");
	return 0;
}
```

### 66、string

```cpp
//int类型转换为string类型的操作为
string name=to_string(50);

//string有一个使用重点就是在linux平台下，前面加上 using namespce std;要不然会报错
//或者直接用std::string
```

### 67、C++中实现递归

```c++
//C++中实现递归是通过if与else实现的
#include<iostream>
using namespace std;
int digui(int n)
{
	if (n==0)
		return 1;
	else
		return n* digui(n - 1);
}

int main()
{
	cout << digui(5) << endl;
	system("pause");
	return 0;
}
    

```

### 68、C++中类中函数可以直接调用类内属性

```C++
#include<iostream>
using namespace std;
class wm {

public:
	wm(int a_)
	{
		a = a_;
	}

	int a;
	void pr()
	{
		cout << "a=" << a << endl;
	}
};

int main() {
	wm w(5);
	w.pr();
	//cout << "my name is wangming" << endl;
	system("pause");
	return 0;
}

//输出结果如下所示：
//a=5

类内的成员函数其实也就是基于这个类所做的一些操作
```



### 69、const

const 作用于类型(int double etc.)的时候，作用的值不能更改，const 作用与 * 的时候，表明作用在指针上，那么指针就是一个常量，指针是不能更改的。

官方定义：const applies to the thing left of it. If there is nothing on the left then it applies to the thing right of it.

```C++
const int *
// const 左边无东西，所以其修饰int，变成常量整形, 然后 * 再作用于不可改变的常量int，所以(该语句表示指针指向的值不可以改变，但是指针的指向是可以改变的)
    
int const *
// 左右都有东西，则默认作用于左边，
    
int * const
// 作用于*(指针的指向不可以改变)，但是指针指向的值是可以改变的
    
    
const int * const
// 最终的结果是都不可以该改变的(一个常量指针指向一个常量整数)

int const * const
// 同上，都不可以改变，一个常量指针指向了一个常量整数
```



### 70、返回vector容器

```cpp
# include<iostream>
using namespace std;
# include<vector>

vector<int> sum(int a, int b)
{
	return { a,b }; // 这个地方可以直接返回中括号，中括号里面就是对应数字
}


int main()
{
	vector<int> a;
	a = sum(3, 2);
	cout << a[0]<<" "<<a[1] << endl;
	system("pause");
	return 0;
}
```

### 71、void关键字

在c++中，void为无类型，主要有是三个用途

1、函数的返回值用void，表示函数没有返回值

2、函数的参数填void，表示函数不需要参数(一般情况下空着)

- void func( void );

3、函数的形参用void*, 表示接受任意类型的指针

- 不能用void声明变量，它不能代表一个真实的白能量
- 不能对void*指针直接解引用，需要转换成其他类型的指针
- 把其他类型的指针赋值给void不需要转换
- 把void*指针赋值给其他类型的指针需要转换。



### 72、iota()函数

给数组中的元素+1递增

1.对于数组

`iota(array, array+length[array], number)`

array因为数组名就是元素首地址，相当于属于数组首地址和终地址

```cpp
#include<iostream>
#include<numeric>
using namespace std;

int main() {	
	
	int number[10];

	iota(number, number + 10, 66);
	for (int i = 0; i < 10; i++) {
		cout << number[i] << " ";		//输出：66 67 68 69 70 71 72 73 74 75
	}

	system("pause");
	return 0;
}

```

2.对于vector容器

`iota(vector.begin(), vector.end(), number)`

```cpp
#include<vector>
using namespace std;

int main() {	
	
	vector<int>number(10);

	iota(number.begin(), number.end(), 66);
	for (int i = 0; i < 10; i++) {
		cout << number[i] << " ";		//输出：66 67 68 69 70 71 72 73 74 75
	}

	system("pause");
	return 0;
}

```

### 73、引入头文件

```cpp
# include "a.h"     // 告诉编译器首先在同级的目录里进行查找头文件
# include<iostream> // 告诉编译器首先在环境变量定义的文件中首先进行查找

// 通常情况下，C++标准库的头文件是没有.h后缀的
// 自己写的库一般是有.h后缀的
```





