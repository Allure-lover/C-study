# 细节：

**signed：数据以补码方式存放，存储单元最高位用来表示数值的符号**

**unsigned：数值没有符号，全部二进制用来表示数值本身**

<img src="../../../Typora/img/image-20230815212935282.png" alt="image-20230815212935282" style="zoom: 80%;" />

十进制：1357， 1274L 或者 1274l ( long int )    

八进制：020  前加0，表示8进制的20  代表10进制的16

十六进制：0x20  或者  0X20   十六进制的20 代表十进制的32

**十进制的小数形式：**单精度浮点数 实数后面f/F   

​								   长双精度数    字母后加L或者l

**指数形式：**0.314159x10^1^     程序中表示  0.314159e1



<img src="../../../Typora/img/image-20230815215130809.png" alt="image-20230815215130809" style="zoom:80%;" />

<img src="../../../Typora/img/image-20230815215151021.png" alt="image-20230815215151021" style="zoom:80%;" />

## 常量：

加入const关键字，变量的值在程序运行的期间不能修改，这种变量称为常变量，**常变量必须在定义的时候就赋值**

符号常量#define只是用一个符号代替所指定的字符串

![image-20230816202515482](../../../Typora/img/image-20230816202515482.png)

## 类型转化

![image-20230816203636287](../../../Typora/img/image-20230816203636287.png)



# 程序从编写到最后得到运行步骤

**编写程序**

**对源程序进行编译**：编译以源程序文件为单位，编译的作用是对源程序进行词法检查和语法检查(.obj)

**将目标文件进行连接**：将一个所有目标程序和系统库文件以及系统提供的其他信息连接起来，最终形成一个可执行的二进制文件（.exe）

**运行程序**

**分析结果**

<img src="../../../Typora/img/image-20230815203136765.png" alt="image-20230815203136765" style="zoom:50%;" />





# 一、代码执行过程的内存

*程序执行将内存分为四个区域*

*代码区：存放函数体的二进制代码，由操作系统进行管理*

​		*共享和只读*

*全局区：存放全局变量和静态变量及常量，程序执行结束，由操作系统回收*

​		*包括常量区：存放全局变量、静态变量（**static**）、自字符串常量（**“HELLO WORLD”**）和其他常量（**const**修饰的全局变量）*

*栈区：由编译器自动分配和释放，存放函数的参数值，局部变量等*

​		*注意事项：不要返回局部变量的地址（例如：函数里的局部变量）*

*堆区：由程序员分配和释放，若程序员不释放程序运行结束由操作系统回收*

​		*利用**new**开辟内存*

​				*创建单个变量*   *int \* p = new int(10);*     *释放单个变量*    *delete p;*

​				*创建数组变量*   *int \* arr = new int[10]*    *释放数组变量*    *delete[] arr;*

# 二、引用的基本用法

## 引用声明变量

**本质：给变量起别名**

**语法：数据类型 &别名 = 原名** 

**格式：int &b = a;       (a,b操作同一块内存)**

```c++
	int a =10;
    int &b = a;
    cout << a << endl;
    cout << b << endl;
    b=100;
    cout << a << endl;
    cout << b << endl;
//输出结果 10 \n 10 \n 100 \n 100 \n
```

**注意事项：引用必须要初始化    int &b; 错误**

​					**引用初始化后不能更改   int a = 10; int c = 20; int &b = a;  b =  c; 错误**

```c++
void test04(){
    int a = 10;
    int c = 20;
    int &b = a;    //初始化
    b=c;           //赋值操作
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;
}
```

b=c是赋值操作；

## **引用做函数参数**

作用：函数传参时，可以利用引用技术让形参修饰实参

优点：简化指针修改实参

```c++
//值传递  此方法交换失败，形参的值改变不会影响实参
void mySwap01(int a, int b){
    int temp = a;
    a = b;
    b = temp;
}
//地址传递 此方法可以
void mySwap02(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

//引用传递
void mySwap03(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}
int main(){
    int a = 10;
    int b = 20;
    mySwap02(&a, &b);  // ok
    mySwap03(a,b);  // ok
    return 0;
}
```

## 引用做函数的返回值

```c++

//1.不要返回局部变量的引用
int& test01(){
    int a = 10;   //存放在栈区，函数执行完成释放内存
    return a;
}
//函数的引用可以作为左值
int& test02(){
    static int a = 10; // 静态变量，存放全局区，全局区的数据程序运行结束释放
    return a;
}

int main(){
    int &ref1 = test01();
    cout << "ref1 = " << ref1 << endl;   //可能第一次打印成功，但第二次失败
    int &ref2 = test02();
    cout << "ref2 = " << ref2 << endl;   //这个是可以的
    
    test02() = 1000;
    cout << "ref2 = " << ref2 << endl;  //结果 1000
    system("pause");
}
```

## 引用的原理

**本质就是指针常量，但是所有的指针操作都由编译器帮我们实现**

```c++
//发现引用，转换成 int* const ref = &a;
void func(int& ref){
    ref = 100;  // ref是引用， 转换为 *ref = 100
}

int main(){
    int a = 10;
    
    //自动转换为 int* const ref = &a; 指针常量是指针指向不可改变的，也说明为什么引用不可更改
    int& ref = a;
    ref = 20; // 内部发现ref是引用，自动帮我们转换为：*ref = 20;
    
    cout << "a:" << a << endl;
    cout << "ref:" << ref << endl;
    
    system("pause");
    return 0;
}
```

## 	常量引用

作用：常量引用主要用来修饰形参，防止误操作

加入const关键字，变量的值在程序运行的期间不能修改，这种变量称为常变量，**常变量必须在定义的时候就赋值**

```c++
const int& ref =10;  <--->  int temp = 10; const int& ref = temp;    //加入const不可修改
void showVal(const int& val){     //加入const防止修改形参，以至于修改实参****
    cout << "val = " << val << endl;
}

int main(){
	int a = 100;
    showVal(a);
    return 0;
}
```

# 三、函数的提高

## 函数的默认参数

c++中，函数的形参列表可以有默认值

语法：返回值类型 函数名（参数 = 默认值）{}

```c++
int func(int a, int b=20, int c=30){   //给b，c设置默认值
    return a+b+c;
}
int main(){
    int res = func(10);
    int res2 = func(10,30);
    cout << res << endl;
    system("pause");
    return 0;
}
```

==注意事项：如果某个位置有默认参数，从这个参数往后，从左往右都必须有默认值，即要带默认值的形参放在后面==

​					==如果函数声明和函数实现不能同时有默认值==

```c++
//两种正确的写法
int func2(int a=10, int b=20);
int func2(int a, int b){ 
	return a+b;
}
int func2(int a, int b);
int func2(int a=10, int b=20){ 
	return a+b;
}
```

## 函数的占位参数

**c++中函数形参列表里可以有占位参数，用来占位，但是函数调用的时候必须填补该位置**

**语法：返回值类型 函数名（数据类型）{}**

```c++
//占位参数，暂时用不到
void func1(int a, int){
    cout << "this a function " << endl;
}
void func2(int a, int=10){
    cout << "this a function " << endl;
}
int main(){
    //占位形参位置，必须传值，否则报错
    func1(10,10);
	func2(10);  //可以有默认，可不传
    system("pause");
}
```

占位参数可以有默认参数

## 函数重载

**作用：函数名可以相同，提高复用性**

**函数重载满足条件：**

​	**同一个作用于下**

​	**函数名相同**

​	**函数 ==参数类型==或者==个数==或者==顺序==不同，不能全一样**

```c++
void func(){
	cout << "函数调用 func()" << endl;
}
void func(int a){
    cout << "函数调用 func(int a)" << endl;
}
void func(double a){
    cout << "函数调用 func(double a)" << endl;
}
void func(int a, double b){
    cout << "函数调用 func(int a, double b)" << endl;
}
void func(double a, int b){
    cout << "函数调用 func(double a, int b)" << endl;
}
```

**==注意事项：函数返回值不能作为重载的条件==**

### 函数重载注意事项

```c++
void func(int& a){ //int &a =10 不合法，不走这
	cout << "函数调用 func(int &a)" << endl;
}

void func(const int& a){
	cout << "函数调用 func(const int &a)" << endl;
}

//----------------------------------------------------------------
int main(){
    int a = 10;
    //这样调用func(int& a)  
    func(a);    
    //这样调用func(const int& a) 编译器优化  const int& ref =10;  <--->  int temp = 10; const int& ref = temp;
    func(10);  
    system("pause");
}
```

```c++
void func(int a){
    cout << "func(int a) 调用" << endl;
}
void func(int a, int b=10){
    cout << "func(int a, int b) 调用" << endl;
}
int main(){
    func(10);  //这个报错，此时出现二义性，不知道调用哪个，避免
}
```

# 四、类与对象

**C++ 三大特性：封装、继承 和 多态**

## 封装

**访问权限：**

​	**public：类内可以访问，类外也可以访问**

​	**protected：类内可以访问，类外不能访问，但是子类可以访问父类的private权限的属性和行为**

​	**private：类内可以访问，类外不能访问，子类也不能访问父类的private权限的属性和行为**

struct 与 class区别：

​	**struct默认权限是公共；**

​	**class默认权限是私有；**

==成员属性一般设置为私有；==

```c++
class Person{
private:
    string m_Name;
    int m_Age;
    string m_Sex;

public:
    void setName(string name){
        m_Name = name;
    }

    string getName(){
        return m_Name;
    }

    int getAge(){
        m_Age = 0;  //初始化
        return m_Age;
    }

    void setSex(string sex){
       	m_Sex = sex;
    }
};
```

### 类的拆分

**优点：将实现代码和mian函数分离；**

```c++
//circle.h
#pragma once
#include <iostream>
using namespace std;

class Circle2{
private:
    int c_x;
    int c_y;
    double c_r;

public:
    int getCX() const ;
    void setCX(int cX) ;
    int getCY() const;
    void setCY(int cY);
    double getCR() const;
    void setCR(double cR);
};
```

```c++
//circe2.cpp
#include "circle.h"

int Circle2::getCX() const {
    return c_x;
}
void Circle2::setCX(int cX) {
    c_x = cX;
}
int Circle2::getCY() const {
    return c_y;
}
void Circle2::setCY(int cY) {
    c_y = cY;
}
double Circle2::getCR() const {
    return c_r;
}
void Circle2::setCR(double cR) {
    c_r = cR;
}
```

```c++
//main函数
#include <iostream>
#include "circle.h"
using namespace std;

int main(){
    Circle2 cir1;
    cir1.setCX(10);
    cir1.setCY(10);
    cir1.setCR(20);
    system("pause");
   	return 0;
}
```

## 对象的初始化和清理

**构造函数：作用于创建对象的时候为成员属性赋值，有编译器自动调用，无需手动调用**

语法：类名(){}

可重载，只会调用一次

**析构函数：作用于对象销毁前系统的自动调用，执行一些清理操作**

语法：~类名(){}

不可以有参数，不能重载

```c++
class Person{
private:
    string name;

public:
    //普通构造
    Person(){
        cout << "Person的构造函数" << endl;
    }
    Person(int a){
        cout << "Person的构造函数" << endl;
    }

    //拷贝构造函数
    Person(const Person &p){
        name = p.name;
    }
    
    //析构函数
    ~Person(){
        cout << "Person的析构函数" << endl;
    }
};

//调用
void test01(){
    //括号法
    Person p1;     //栈上数据，test01执行完毕，就会自动释放
    Person p2("张三");
    Person p3(p2);
    //注意事项：调用默认构造的时候不要加括号 Person p1();会被编译器识别为函数声明，所以不会创建对象
    
    //显示法
    Person p4;
    Person p5 = Person(10); //有参构造
    Person p6 = Person(p2); //拷贝构造
    Person(10); //匿名对象 特点：当前行执行结束，系统会立即回收掉匿名对象
    //主要事项：不要利用拷贝构造函数 初始化匿名对象  Person(p2); == Person p2;   相当于对象声明，与上面p2的对象声明重复
    
    //隐式转换法
    Person p7 = 10;  // Person7 = Person(10); 等价
    Person p8 = p7;  //拷贝构造
}
```

==注意事项：调用默认构造的时候不要加括号 Person p1();会被编译器识别为函数声明，所以不会创建对象==

​					==不要利用拷贝构造函数 初始化匿名对象==

### **拷贝构造函数的调用时机**

使用已经创建的对象类来初始化一个新对象

值传递的方式给函数参数传值

以值方式返回局部对象

```c++
class Person{
private:
    int age;
public:
    Person(){
    }
    Person(int p_age){
        age = p_age;
    }
    
    Person(const Person &p){
        age = p.age;
    }
    
    ~Person(){
        
    }
};

void doWork(Person p){
    
}
Person doWork2(){
    Person p1;
    return p1;
}
void test(){
    //使用已经创建的对象类来初始化一个新对象
    Person p1 = Person(10);
    Person p2 = Person(p1);
    //值传递的方式给函数参数传值
	doWork(p1);  //此处使用了构造构造函数，在函数参数地方使用拷贝构造函数给形参机型赋值
	//以值方式返回局部对象
    Person p3 = doWork2();  //原理：doWork2的返回值作为一个Person类型的数据，赋值给p3，相当于使用的是拷贝构造函数给p3赋值
}
```

### **构造函数的调用规则**

c++会给每个类默认提供三个函数

默认构造函数（无参，函数体为空）

默认析构函数（无参，函数体为空）

默认拷贝构造函数，对属性进行值拷贝

**如果用户定义有参构造函数，c++不提供默认的无参构造函数，但是会提供默认的拷贝构造函数**

**如果用户定义拷贝构造函数，c++不提供其他构造函数**



**深拷贝和浅拷贝**

浅拷贝：简单的赋值拷贝操作

深拷贝：在堆空间重新申请一块区域，将数据赋值



```c++
class Person{
private:
    int age;
    int *height;
public:
    Person(){
    }
    Person(int p_age, int  p_height){
        height = new int(p_height);
        age = p_age;
    }
        
    ~Person(){
        //销毁数据
        if(height != NULL){
			delete height;
            height = NULL;
        }
    }
};  //此代码会崩
```

使用编译器提供的拷贝构造函数，会做浅拷贝操作

浅拷贝会把指针*height会被浅拷贝，也就是拷贝其指向的地址，而在析构函数会对一块地址进行重复释放操作，会报错

深拷贝可以解决这个问题，深拷贝不是直接把地址拷贝，而是另外开辟一块空间来存放数据

```c++
Person(const Person &p){
        age = p.age;
//        height = p.height;  //编译器默认写法
        height = new int(*p.height); //重新创建一块
    }
```

注意事项：如果属性有在堆区开辟的，一定要自己提供拷贝构造函数，防止浅拷贝带来的问题



### 初始化列表

```c++
class Person{
public:
//    Person(int a, int b, int c){
//        m_A = a;
//        m_B = b;
//        m_C = c;
//    }
    //初始化列表
    Person(int a, int b, int c):m_A(a), m_B(b), m_C(c){
    }
    int m_A;
    int m_B;
    int m_C;
};

int main(){
    Person p(20,30,40);
    system("pause");
    return 0;
}
```

### 类对象做类成员

```c++
class Phone{
public:
    Phone(string pName):m_PName(pName){
        cout << "Phone 构造器" << endl;
    }
    string m_PName;
};

class Person{
public:
    Person(string name, string pName):m_Name(name), m_Phone(pName){
        cout << "Person 构造器" << endl;
    }

    string m_Name;
    Phone m_Phone;
};
//当其他类对象作为本类的成员时，先构造成员对象，再构造自己，析构与构造相反
int main(){
   Person p("张三", "PHONE_13");

   cout << p.m_Name << "带着 " << p.m_Phone.m_PName << endl;
    system("pause");
    return 0;
}
```

### 静态成员

**所有对象共享一份数据，编译阶段分配内存，存于全局区，必须类内声明，类外初始化**

==静态成员函数只能访问静态成员变量==

```c++
#include<iostream>
using namespace std;
class Person{
public:
    static int m_A;
    static void func(){
        m_A = 100;   //静态成员方法只能调用静态成员变量，无法区分非静态成员变量的对象是哪一个
        cout << "static func的调用 " << endl;
    }

private:
    static int m_B;
};
int Person::m_A = 100;   //此步骤必须做
int Person::m_B = 200;
void test(){
    Person p;
    cout << p.m_A << endl;  //100
    Person p2;
    p2.m_A = 200;
    cout << p.m_A << endl;  //200

    //静态成员不属于某个对象，所有对象共享以分数
    //静态成员的两种访问方式
    Person p1;
    p1.m_A = 200;
    cout << p1.m_A << endl;
    Person::m_A = 300;
    cout << Person::m_A << endl;
    p1.func();
    Person::func();
}

int main(){
    test();
    system("pause");
    return 0;
}
```



### 成员变量和成员函数是分开存储的

**空对象占用的内存空间：1字节**   ==这一个字节是用来区分空对象占用的位置==

每个空对象也应该有一个独一无二的内存地址

静态成员变量占用的内存不属于类对象上

**非静态成员变量属于类对象**

非静态和静态成员函数也不属于类对象

## c++对象模型和this指针

**this指针指向被调用的成员函数所属的对象**

**使用场景：**

​		当形参名与成员变量重名时，可用this来区分

​		在类的非静态成员函数中返回类对象本身，可用 return *this

```c++
#include <iostream>
using namespace std;

class Person{
public:
    int age;
    Person(int age){
        this->age = age;   //this指针的使用
    }
    Person& PersonAddAge(Person &p){   //返回本体需要引用的方式
        this->age += p.age;
        return *this;          //this返回该类对象本身
    }
};


int main() {

    Person p(10);
    cout << "p的年龄：" <<  p.age << endl;  //10

    Person p2(20);
    p2.PersonAddAge(p).PersonAddAge(p).PersonAddAge(p);  //返回p2本身可以多次调用
    cout << "p2的年龄：" <<  p2.age << endl;  // 50
    
    system("pause");
    return 0;
}
```

### 空指针访问成员函数

```c++
Person{
public:
    int age;
    showClassName(){
		cout << "CLassName is : Person" << endl;
    }
    
    showPersonAge(){
        
        //避免报空
        if(this == NULL){
            return;
        }
        cout << "age = " << age <<endl;
    }
}

int main{
    //经过测试showClassName函数是可以调用成功的，而showPersonAge函数里面使用age属性，
    //前面默认会有this，所以会报this空指针错误
    Person *p = NULL:
    p->showClassName();
    p->showPersonAge();
    system("pause");
    return 0;
}
```

### const修饰成员函数

**常函数：**成员函数后加const我们称这个函数是常函数

​	常函数内不能修改成员属性

​	成员属性声明时加关键字mutable后，在常函数中依然可以修改

**常对象：**声明对象前加const称为常对象

​	常对象只能调用常函数

```c++
#include <iostream>
using namespace std;

class Person{
public:
    void showPerson() const{       //const限定this指针指向的值，即指针指向的值也不能改
        //age = 10;  // --> this->age = 100;  //加入const就不能修改age了
        //this 是常指针，不能修改  Person * const this  但是指针指向的值可以修改
        sex = 2;
    }
    void showPerson2(){

    }
    int age;
    mutable int sex;   //使用mutable关键字，在常函数依然可修改
};


int main(){

    Person p;
    p.showPerson();
    const Person p2{};
    p2.showPerson();
//    p2.showPerson2();  //常对象不能调用
    system("pause");
    return 0;
}

```

## 友元

**关键字：**friend

**目的：**然一个函数或者类 访问另一个类中的私有成员

**三种实现方式：**

全局函数做友元    friend void  goodGay(Building &building); 

类做友元  friend class GoodGay;

成员函数做友元     friend void GoodGay::visit();

```c++
#include "iostream"
using namespace  std;
class Building;
class GoodGay{
public:
    GoodGay();
    void visit();   //可以访问另一个类的private属性
    void visit2();  //不可以访问
    Building *building;
};

class Building{
    friend void  goodGay(Building &building);  //给这个全局函数访问private属性的权限
//    friend class GoodGay;  //给好基友类访问本类的private属性权限
    friend void GoodGay::visit();  //只给GoodGay类中的visit方法访问private属性权限
public:
//    Building(){
//        m_SittingRoom = "客厅";
//        m_BedRoom = "卧室";
//    }
    Building();
public:
    string m_SittingRoom;

private:
    string m_BedRoom;
};

//下面的这些方法有顺序要求，即调用的方法先写在前面
Building::Building() {
    m_SittingRoom = "客厅";
    m_BedRoom = "卧室";
}
//类外写类内部成员函数或者构造函数
GoodGay::GoodGay(){
    building = new Building();
}

void GoodGay::visit(){
    cout << "好基友要访问：" << building->m_SittingRoom << endl;
    cout << "好基友要访问：" << building->m_BedRoom << endl;  //一个类想访问另一个类的私有成员变量
}
void GoodGay::visit2(){
    cout << "好基友2要访问：" << building->m_SittingRoom << endl;
//    cout << "好基友2要访问：" << building->m_BedRoom << endl;  //一个类想访问另一个类的私有成员变量
}

//全局函数
void  goodGay(Building &building){
    cout << "好基友的全局函数正在访问：" << building.m_SittingRoom << endl;
    cout << "好基友的全局函数正在访问：" << building.m_BedRoom << endl;    //访问private权限属性

}

int main(){
    Building building;
    goodGay(building);  //全局函数
    GoodGay gay;     //类对象
    gay.visit();
    gay.visit2();
    system("pause");
    return 0;
}
```

## 运算符重载

### 加法+运算符重载

```c++
#include "iostream"
using namespace std;

class Person{
    friend Person operator+(Person &p1, Person &p2);
private:
    int m_A;
    int m_B;
public:
    Person(){}
    Person(int a, int b){
        m_A = a;
        m_B = b;
    }
//    Person operator+(Person &p){
//        Person temp;
//        temp.m_A = this->m_A + p.m_A;
//        temp.m_B = this->m_B + p.m_B;
//        return temp;
//    }
};

Person operator+(Person &p1, Person &p2){
    Person temp;
    temp.m_A = p1.m_A + p2.m_A;
    temp.m_B = p1.m_B + p2.m_B;
    return temp;
}
//重载
Person operator+(Person &p, int num){
    Person temp;
    temp.m_A = p1.m_A + num;
    temp.m_B = p1.m_B + num;
    return temp;
}

void test01(){
    Person p1(20, 30);
    Person p2(50, 60);
    Person p3 = p1 + p2;  //两种情况
    					  //使用成员函数时，等价于 Person p3 = p1.operate+(p2);
						  //使用全局函数时，等价于 Person p3 = operate+(p1, p2);
    //运算符重载也可以发生函数重载
    Person p4 = p1 + 2;
    cout << "p3：" << p3.m_A << "\t" << p3.m_B << endl;
}

int main(){
    test01();
    system("pause");
    return 0;
}
```

总结：**内置数据类型的表达式的运算符是不可改变的**，，，==不要滥用运算符重载==

### 左移<<运算符重载

一般使用全局函数来重载左移运算符，配合友元可以实现输出自定义数据类型

```c++
#include "iostream"
using namespace std;

class Person{
    friend ostream& operator<<(ostream &cout, Person &p);
private:
    int m_A;
    int m_B;
public:
    Person(){}
    Person(int a, int b){
        m_A = a;
        m_B = b;
    }
};

ostream& operator<<(ostream &cout, Person &p){
    cout << "m_A = " << p.m_A << "\t" << "m_B = " << p.m_B ;
    return cout;  // &cout
}

void test01(){
    Person p1(20, 30);
    Person p2(50, 60);

    cout << p1 << endl;
}

int main(){
    test01();
    system("pause");
    return 0;
}

```

### ++和--的重载

```c++
#include "iostream"
using namespace std;

class Person{
    friend ostream & operator<<(ostream &cout, Person p);
    //friend Person& operator++(Person &p);
public:
    Person() {
        m_A = 0;
        m_B = 1;
    }
    //前置递增
    Person& operator++(){    //返回引用，否则不能进行递归调用
        m_B++;
        m_A++;
        return *this;
    }
    //前置递减
    Person& operator--(){
        m_A--;
        m_B--;
        return *this;
    }

    //后置递增（int） 是占参数，用于区分前置和后置递增
    Person operator++(int){
        Person temp = *this;
        m_A++;
        m_B++;
        return temp;
    }

    //后置递减
    Person operator--(int){
        Person temp = *this;
        m_A--;
        m_B--;
        return temp;
    }

private:
    int m_A;
    int m_B;
};

ostream& operator<<(ostream &cout, Person p){
    cout << "m_A = " << p.m_A << endl << "m_B = " << p.m_B << endl;
    return cout;
}
//
//Person& operator++(Person &p){
//    p.m_A = ++p.m_A;
//    p.m_B = ++p.m_B;
//    return p;
//}

int main(){

    Person p;
    cout << p << endl;

    ++p;
    p++;
    cout << p++ << endl;
//    cout << ++(++p) << endl;
    cout << p << endl;
    cout << (p++)++ << endl;
    cout << p << endl;
    system("pause");
    return 0;
}
```

### 赋值运算符=的重载

**c++至少会给一个类添加4个函数**

​	无参，函数体为空的构造函数

​	无参，函数体为空的析构函数

​	默认拷贝函数，对属性进行值拷贝

​	默认运算符 operator=，对属性进行值拷贝

==如果类中有属性指向堆区，做赋值操作时也会出现深浅拷贝的问题==

```c++
#include "iostream"
using namespace std;

class Person{
    friend ostream & operator<<(ostream& cout, Person p);
public:
    Person(int age){
        m_Age = new int (age);
    }
    ~Person(){
        if(m_Age != NULL){
            delete m_Age;
            m_Age = NULL;
        }
    }

    Person& operator=(Person &p){
        if(m_Age != NULL) delete m_Age;
        m_Age = new int(*p.m_Age);    //这样给拷贝另外分配一块地址，给该地址赋予
        							  //和要等的数值，这样就不会在析构函数中发生对一块区域重复释放的错误
        return *this;
    }

private:
    int * m_Age;
};

ostream & operator<<(ostream& cout, Person p){
    cout << "Person的年龄为："<< *p.m_Age << endl;
    return cout;
}

void test01(){
    Person p1(18);
    Person p2(28);
    Person p3(30);
    p2 = p1 = p3;

    cout << p1 << endl;
    cout << p2 << endl;
    cout << p3 << endl;
}

int main(){

    test01();

    system("pause");
    return 0;
}

```

### 关系运算==、!=符重载

```c++
#include <iostream>
using namespace std;

class Person{
public:
    Person(string name, int age){
        m_Name = name;
        m_Age = age;
    }
    //重载关系 ==
    bool operator==(Person &p){
        if(p.m_Name == this->m_Name && p.m_Age == this->m_Age){
            return true;
        }
        return false;
    }
	//!=
    bool operator!=(Person &p){
        if(p.m_Name == this->m_Name && p.m_Age == this->m_Age){
            return false;
        }
        return true;
    }
private:
    string m_Name;
    int m_Age;
};

void test01(){
    Person p1("Tom",20);
    Person p2("Jerry",20);

    if(p1 == p2){
        cout << "p1 和 p2 相等！" << endl;
    }else{
        cout << "p1 和 p2 不等！" << endl;
    }
    if(p1 != p2){
        cout << "p1 和 p2 不等！" << endl;
    }else{
        cout << "p1 和 p2 相等！" << endl;
    }
}

int main(){
    test01();
    system("pause");
    return 0;
}
```

### 函数调用运算符（）重载

重载()使用像函数，所以叫仿函数

```c++
#include <iostream>
using namespace std;

class MyPrint{
public:
    //重载函数调用运算符
    void operator()(string test){
        cout << test << endl;
    }
};

class MyADD{
public:
    int operator()(int a, int b){   //写法很灵活
        return a+b;
    }
};

void test01(){
    MyPrint myPrint;
    myPrint("Hello WORLD");   //调用void operator()(string test)， 类似函数调用，叫仿函数
}

void test02(){
    MyADD myAdd;
    int ret = myAdd(100,200);
    cout << ret << endl;
    cout << MyADD()(100,100) << endl;    //匿名对象，直接执行仿函数（对 () 的重载 ）

}

int main(){
    test01();
    test02();
    system("pause");
    return 0;
}
```

## 继承

```c++
class BasePage{
}
class Java : public BasePage{
}
```

**语法：class 子类 ： 继承方式 父类**

**好处：减少重复代码**

**父类：基类**

**子类：派生类**

父类的私有属性，无法被子类访问

**继承方式的选择确定的是父类属性继承到子类的属性权限（==父类的比该权限更大的缩小为继承方式的权限，小的权限不变==）**

<img src="../../../Typora/img/image-20230803203016519.png" alt="image-20230803203016519" style="zoom:50%;" />

**父类中所有非静态的成员属性都会被子类继承下去**

**父类的私有成员属性，被编译器隐藏，因此访问不到，但是确实会被继承下去**

![image-20230803204826808](../../../Typora/img/image-20230803204826808.png)

### **利用开发人员命令提示工具查看对象模型**

跳转盘符：D:

跳转文件路径 cd 具体目录

查看命名

cl /d1 reportSingleClassLayout类名 文件名

### 继承中的构造和析构的调用顺序

**先构造父类，再构造子类，析构的顺序和构造相反**

### 继承同名成员处理方式

访问子类的同名成员属性直接访问即可   **s.m_A**

访问父类的同名成员属性访问需要加父类的作用域  **s.Base::m_A**

访问子类的同名成员函数直接调用即可   **s.func()**

访问父类的同名成员函数需要加父类的作用域   **s.Base::func()**

子类中出现和父类同名的成员函数，子类的同名成员会隐藏掉父类中的所有同名函数，即重构的函数也会被隐藏掉，想要调用需要加作用域

### 继承中同名静态成员处理方式

访问子类的静态同名成员属性直接访问即可 **s.m_A    Son::m_A**

访问父类的静态同名成员属性需要加父类的作用域  **s.Base::m_A    Son::Base::m_A**

访问子类的静态同名成员函数直接访问   **s.func()   Son::func()**

访问父类的静态同名成员函数需要加父类的作用域   **s.Base::fuc()   Son::Base::func()**

想要调用父类中的同名重构函数，也需要加作用域，因为所有父类和子类重名的静态函数都会被隐藏

### 多继承（不推荐）

语法：class 子类 : 继承方式  父类1，继承方式 父类2 ...

多继承可能出现父类中属性同名的成员出现，需加作用域区分

### 菱形继承（钻石继承）

问题：数据只需要一份就可以了，重复继承了两个拥有同一个父类的类，会有两份数据

```c++
class Animal{}
class Sheep : public Animal{}
class Camel : public Animal{}
class SheepCamel : public Sheep, public Camel{}

//-------------------------------------------
//虚继承
class Animal{}
class Sheep : virtual public Animal{}
class Camel : virtual public Animal{}
class SheepCamel : public Sheep, public Camel{}
```

虚继承类解决：加关键字virtual

vbptr：虚基类指针，指向 vbtable 

![image-20230803213740114](../../../Typora/img/image-20230803213740114.png)

## 多态

**分类：**

静态多态：函数重载 和 运算符重载属于静态多态，复用函数名

动态多态：派生类和虚函数实现运行时多态

**区别：**

静态多态的函数地址早绑定 -- 编译阶段确定函数地址

动态多态的函数地址晚绑定 -- 运行阶段确定函数地址

**多态条件：**

有继承关系

子类重写父类的方法

**多态的使用：**

父类的指针或者引用 指向子类对象

```C++
#include <iostream>
using namespace std;

//多态
class Animal{
public:
    virtual void speak(){                //注意点1：使用虚函数
        cout << "动物在说话" << endl;
    }
};

class Cat : public Animal{
public:
    void speak(){						//此处的virtual关键字可写可不写
        cout << "小猫在说话" << endl;
    }
};

class Dog : public Animal{
public:
    void speak(){
        cout << "小狗在说话" << endl;
    }
};
void doSpeak(Animal &animal){           //注意点2：引用的方式传参
    animal.speak(); 
}

void test01(){
    Cat cat;
    doSpeak(cat);
    Dog dog;
    doSpeak(dog);
}

//指针方式使用多态
void test02(){
    Animal * a = new Cat;
    a.speak();
    delete a;
    a = new Dog;
    a.speak();
}

int main(){
    test01();
    system("pause");
    return 0;
}
```

**原理**：

加virtual 会创建 vfptr 指针（虚函数指针）              virtual function pointer

vfptr 会指向 vftable                                                    virtual function table

vftable 会记录虚函数的地址   &Animal :: speak 

![img](../../../Typora/img/_160495518__489a0b5781f3cc55470b7c7988b27b61_-123718074_Screenshot_20230803_221017_tv.danmaku_0_wifi_0.jpg)

### 纯虚函数、抽象类

```c++
//多态
class Animal{
public:
    virtual void speak()=0; //纯虚函数
};
```

**拥有纯虚函数的类称之为抽象类**

抽象类无法实例化对象

子类必须重写抽象类中的纯虚函数，否则也属于抽象类

### 案例：制作饮品

```c++
#include<iostream>
using namespace std;

class AbstractDrinking{
public:
    virtual void boil() = 0;
    virtual void brew() = 0;
    virtual void pourInCup() = 0;
    virtual void putSth() = 0;
    void makeDrink(){
        boil();
        brew();
        pourInCup();
        putSth();
    }
};

class Coffee : public AbstractDrinking{
    virtual void boil(){
        cout << "煮农夫山泉---" << endl;
    }
    virtual void brew() {
        cout << "冲泡咖啡-----" << endl;
    }
    virtual void pourInCup(){
        cout << "倒入杯中-----" << endl;
    }
    virtual void putSth(){
        cout << "加糖和牛奶---" << endl;
    }
};

class Tea : public AbstractDrinking{
    virtual void boil(){
        cout << "煮自来水----" << endl;
    }
    virtual void brew() {
        cout << "冲泡茶-----" << endl;
    }
    virtual void pourInCup(){
        cout << "倒入杯中----" << endl;
    }
    virtual void putSth(){
        cout << "加枸杞-----" << endl;
    }
};
void doWork(AbstractDrinking *abs){
    abs->makeDrink();
    delete abs;
}
void test01(){
    doWork(new Coffee);
    doWork(new Tea);
}
int main(){
    test01();
    system("pause");
    return 0;
}
```

### 虚析构和纯虚析构函数

**虚析构和纯虚析构的共性：**

可以解决父类指针释放子类对象

都需要具体函数实现

**区别：**
		如果是纯虚析构，该类属于抽象类，无法实例化对象

```c++
class Animal{
    
    virtual ~Animal(){}  //利用虚析构可以解决 父类指针释放子类对象不干净问题
}

class Cat : public Animal{
public:
    int *m_A;
    ~Cat(){}
}
//----------------------------------------------------------------------

class Animal{
    
    virtual ~Animal()=0; //利用纯虚析构可以解决 父类指针释放子类对象不干净问题，需要声明和实现
}
Animal :: ~Animal(){
}
class Cat : public Animal{
public:
    int *m_A;
    ~Cat(){
        if(m_A != NULL){
            delete m_A;
            m_A == NULL;
        }
    }
}
```

**虚析构语法：**

`virtual ~类名(){}`

**纯虚析构语法：**

`virtual ~类名(){}=0;`

`类名::~类名(){}`

**总结：**

1.虚析构或者纯虚析构就是用来解决通过父类指针释放子类对象

2.如果子类中没有堆区数据，可以不写为虚析构和纯虚析构

3.拥有纯虚析构函数的类也属于抽象类

# 五、文件操作

程序运行时产生的数据都属于临时数据，程序一旦运行结束都会被释放

通过文件可以将数据持久化

c++中对文件操作需要包含头文件`<fstream>`



文件类型分为两种：
		1.文本文件 --- 文件以文本的ASCII码形式存放在计算机中

2.二进制文件 --- 文件以二进制形式存储在计算机中，用户一般不能读懂它



操作文件的三大类：

1.ofstream：写操作

2.ifstream：读操作

3.fstream：读写操作

## 文本文件

### 写操作

写文件步骤如下：

1.包含头文件    #include <fstream>

2.创建流对象    ofstream ofs;

3.打开文件        ofs.open("文件路径"，打开方式);

4.写数据            ofs << "写入数据" << endl;

5.关闭文件        ofs.close();



文件打开方式

| 打开方式    | 解释                       |
| ----------- | -------------------------- |
| ios::in     | 为读文件而打开             |
| ios::out    | 为写文件而打开             |
| ios::ate    | 初始位置：文件尾           |
| ios::app    | 追加方式写文件             |
| ios::trunc  | 如果文件存在先删除，再创建 |
| ios::binary | 二进制方式                 |

文件打开方式可以配合使用，利用|操作符

比如：用二进制方式写文件 `ios::binary | ios::out`

```c++
	ofstream ofs;
    ofs.open("./test01.txt", ios::out);
    ofs << "你好，第一次使用c++写文件" << endl;
    ofs.close();
```

总结：

文件操作必须包含头文件 fstream

写文件可以利用 ofstream 或者 fstream

打开文件时需要指定操作文件路径，以及打开方式

利用 << 可以像文件中写数据

操作完毕，需要关闭文件

### 读文件

读文件步骤如下：

1.包含头文件            #include<fstream>

2.创建对象流            ifstream ifs;

3.打开文件                ifs.open("文件路径", 打开方式);

4.读数据                    四种读取方式

5.关闭文件                ifs.close();

```C++
void test02(){
    ifstream ifs;
    ifs.open("./test01.txt", ios::in);
    if(!ifs.is_open()){
        cout << "文件打开失败" << endl;
        return;
    }

    //第一种
    char buff[1024] = {0};
    while(ifs >> buff){
        cout << buff << endl;
    }
    //第二种
//    char buf[1024] = {0};
//    while(ifs.getline(buf, sizeof(buf))){
//        cout << buf << endl;
//    }
    //第三种
//    string text;
//    while(getline(ifs, text)){
//        cout << text << endl;
//    }
//    cout << text << endl;
    //第四种 不推荐
//    char c;
//    while((c = ifs.get()) != EOF){
//        cout << c;
//    }
    ifs.close();
}
```

## 二进制文件

以二进制的方式对文件进行读写操作

打开方式要指定为 `ios::binary`

### 写文件

二进制写文件主要利用流对象调用成员函数write

函数原型 `ostream&  write(const char * buffer , int len);`

参数解释：字符指针buffer指向内存中一段存储空间。len是读写的字节数

```c++
class Person{
public:
    char m_Name[64];
    int m_Age;
};
void test03(){
//    ofstream ofs;
    ofstream ofs("person.txt", ios::binary | ios::out);
//    ofs.open("./perosn.txt", ios::binary | ios::out);
    Person p = {"张三", 18};
    ofs.write((const char *)&p, sizeof(Person));
    ofs.close();
}
```

### 读文件

二进制方式读文件主要利用流对象调用成员函数read

函数原型：`istream& read(char *buffer, int len);`

参数解释：字符指针buffer指向内存中一段存储空间。len是读写的字节数

```c++
class Person{
public:
    char m_Name[64];
    int m_Age;
};
void test04(){
    ifstream ifs;
    ifs.open("person.txt", ios::binary | ios::in);
    if(!ifs.is_open()){
        cout << "文件打开失败" << endl;
        return;
    }
    Person p;
    ifs.read((char *)&p, sizeof(Person));
    cout << p.m_Name << "\t" << p.m_Age << endl;

    ifs.close();
}
```







# 六、模板

## 函数模板

```c++
#include <iostream>
using namespace std;

template<typename T> //声明模板

void mySwap(T &a, T &b){
    T temp = a;
    a = b;
    b = temp;
}

void test01(){
    int a = 2;
    int b = 3;
    mySwap(a,b);//自动类型推导
    mySwap<int>(a,b);  //显示指定类型
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
}


int main(){
    test01();

    system("pause");
    return 0;
}
```

总结： 函数模板利用关键字template

​			使用函数模板两种方式：自动类型推导，显示指定类型

​			模板的目的为了提高复用性，将类型参数化

### 注意事项

1.自动类型推导，必须要推导出一致的数据类型T才可以使用

2.模板必须要确定出T的数据类型，才可以使用

`template<class T>    template<typename T>`两个作用一致

### 函数模板案例

通用排序函数

```c++
#include <iostream>
using namespace std;

template<typename T> //声明模板
void mySwap(T &a, T &b){
    T temp = a;
    a = b;
    b = temp;
}

template<class T>
void selectSort(T a[], int len){
    for(int i=0; i < len; i++){
        int min = i;
        for(int j=i+1; j<len;j++){
            if(a[min] > a[j]) min = j;
        }
        if(min != i){
            T temp = a[i];
            a[i] = a[min];
            a[min] = temp;
        }
    }
}

void test01(){
    int a = 2;
    int b = 3;
    mySwap(a,b);
    mySwap<int>(a,b);  //显示指定类型
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
}
template<typename T>
void printArr(T *a, int len){
    cout << "开始打印" << endl;
    for(int i=0; i<len;i++){
        cout << a[i] << endl;
    }
}


void test02(){
    int a[6] = {3,5,6,8,2,0};
    selectSort(a, 6);
    printArr(a, 6);
    char charArr[] = "abdefsh";
    int len = sizeof(charArr)/sizeof(char);
    selectSort(charArr, len);
    printArr(charArr, len);
}

int main(){
//    test01();
    test02();
    system("pause");
    return 0;
}
```

### 普通函数和模板函数的区别

普通函数调用时可以发生自动类型转换（隐式类型转换）

函数模板调用时，如果利用自动类型推导，不会发生隐式类型转换

如果利用显示指定类型的方式，可以发生隐式类型转换

```c++
template<typename T>
T addTwo(T a, T b){
    return a+b;
}
void test(){
	int a = 10;
    int b = 20;
    char c = 'c';
    //addTwo(a,c); //不可以转换，编译器无法推导类型， a，c类型不一样
    addTwo<int>(a,c); //可以执行，编译器会把c隐式转换成int
}
```

### 普通函数与函数模板的调用规则

如果函数模板和普通函数都可以实现，优先调用普通函数

可以通过空模板参数列表来强制调用函数模板

函数模板也可以发生重载

如果函数模板可以产生更好的匹配，优先调用函数模板

```c++
void myPrint(int a, int b){
    cout << "调用普通函数" << endl;
}

template<typename T>
void myPrint(T a, T b){
    cout << "调用模板函数" << endl;
}
template<typename T>
void myPrint(T a, T b, T c){
    cout << "调用模板函数" << endl;
}
void test04(){
    int a = 10;
    int b = 20;
    int c = 30;
    myPrint(a,b);   //调用普通函数
    //空模板参数列表，强制调用模板
    myPrint<>(a,b);  //调用函数模板
    myPrint(a,b,c);  //调用函数模板

    char c1 = 'a';
    char c2 = 'b';
    //如果函数模板可以产生更好的匹配，优先调用函数模板
    myPrint(c1,c2);  //函数模板
}
```

### 模板的局限性

```c++
//对比两个数据
template<typename T>
bool myCompare(T &a, T &b){
    if(a == b) return true;
    return false;
}

class Person{
public:
    Person(string name , int age){
        this->name = name;
        this->age = age;
    }
    int age;
    string name;
//    bool operator==(Person &p){}   //方法一重写载==
};

void test05(){
    int a=10;
    int b=10;
    bool ret = myCompare(a,b);
    if(ret){
        cout << "a == b" << endl;
    }else{
        cout << "a != b" << endl;
    }
}

template<> bool myCompare(Person &p1, Person &p2){
    if(p1.name == p2.name && p1.age == p2.age){
        return true;
    } else{
        return false;
    }
}

void test06(){
    Person p1 = Person("汤姆", 10);
    Person p2 = Person("汤姆", 20);

    bool ret = myCompare(p1,p2);
    if(ret){
        cout << "p1 == p2" << endl;
    }else{
        cout << "p1 != p2" << endl;
    }
}
```

利用具体化的模板，可以解决自定义类型的通用化

学习模板并不是为了写模板，而是在STL能够用系统提供的模板

## 类模板

作用：建立一个通用类，类中的成员 数据类型可以不具体指定，用**虚拟类型**来代表

```c++
template<class NameType, class AgeType>   //定义两个模板
class Person{
public:
    Person(NameType name, AgeType age){
        this->name = name;
        this->age = age;
    }
    NameType name;
    AgeType age;
    void showInfo(){
        cout << "name = " << name << ", age = " << age << endl;
    }
};

void test01(){
    Person<string, int> p1("孙悟空",20);
    p1.showInfo();
}
```

### 类模板和函数模板的区别

类模板没有自动类型推导的使用方式

类模板在模板参数列表可以有默认参数

```c++
template<class NameType, class AgeType=int>   //可以有默认参数
class Person{
public:
    Person(NameType name, AgeType age){
        this->name = name;
        this->age = age;
    }
    NameType name;
    AgeType age;
    void showInfo(){
        cout << "name = " << name << ", age = " << age << endl;
    }
};

void test01(){
    Person<string> p1("孙悟空", 20);  //有默认类型的模板可以不用显示转换
    p1.showInfo();
}
```

### 类模板中成员函数创建时机

1.普通类中的成员函数一开始就可以创建

2.类模板中的成员函数在调用时才创建（**要显示指定完类型才知道该怎么创建**）

### 类模板对象做函数参数

三种方式：

指定传入的类型：直接显示对象的数据类型

参数模板化：将对象中的参数变为模板进行传递

整个类模板化：将这个对象类型 模板化进行传递

```c++
template<class T1, class T2>
class Person2{
public:
    Person2(T1 name, T2 age){
        this->name = name;
        this->age = age;
    }
    void showPerson2(){
        cout << "姓名：" << name << "，年龄：" << age << endl;
    }
    T1 name;
    T2 age;

};
//指定传入类型（常用）
void printPerson1(Person2<string, int> &p){
    p.showPerson2();
}
//参数模板化
template<class T1, class T2>
void printPerson2(Person2<T1, T2> &p){
    p.showPerson2();
    cout << "T1的类型：" << typeid(T1).name() << endl;
    cout << "T2的类型：" << typeid(T2).name() << endl;
}
//将整个类模板化
template<class T>
void printPerson3(T &t){
    t.showPerson2();
    cout << "T参数类型" << typeid(t).name() << endl;
}
void test02(){
    Person2<string, int> p1("孙悟空", 1000);
    printPerson1(p1);
    Person2<string, int> p2("猪八戒", 300);
    printPerson2(p2);
    Person2<string, int> p3("唐僧", 50);
    printPerson3(p3);
}
```

### 类模板与继承

**注意点：**当子类继承的父类是一个类模板时，子类在声明的时候，要制定出父类中T的类型

​				如果不指定，编译器无法给子类分配内存

​				如果想要灵活的指定父类中的T的类型，子类也需要变成类模板

```c++
template<class T>
class Base{
    T m;
};

class Son1 : public Base<int>{};  //当子类继承的父类是一个类模板时，子类在声明的时候，要制定出父类中T的类型

template<class T>
class son2 : public Base<T>{};  //如果想要灵活的指定父类中的T的类型，子类也需要变成类模板
```

### 类模板成员函数的类外实现

```c++
template<class T1, class T2>
class Person{
public:
    Person(T1 name, T2 age);
    void showPerson();
    T1 name;
    T2 age;
};
//类外实现
template<class T1, class  T2>
Person<T1,T2>::Person(T1 name, T2 age){
    this->name = name;
    this->age = age;
}
template<class T1, class T2>
void Person<T1, T2>::showPerson(){
    cout << "...." << endl;
}
```

### 类模板分文件编写

**问题：**类模板中成员函数创建时机在调用阶段，导致分文件编写时链接不到

**解决：**①：直接包含.cpp文件

​			②：将声明和实现写到同一个文件中，并更改后缀名尾.hpp, hpp是约定的名称，并不是强制（主流）

第①种解决方式

`person.h`

```c++
#pragma once
#include <iostream>
using namespace std;

template<class T1,class T2>
class Person{
public:
    Person(T1 name, T2 age);
    void showPerson();
    T1  name;
    T2 age;
};
```

`person.cpp`

```c++
#include "person.h"


template<class T1, class T2>
Person<T1, T2>::Person(T1 name, T2 age) {
    this->name = name;
    this->age = age;
}

template<class T1, class T2>
void Person<T1, T2>::showPerson() {
    cout << ".............." << endl;
}
```

第②种解决方式

`person.hpp`

```c++
#pragma once
#include <iostream>
using namespace std;

template<class T1,class T2>
class Person{
public:
    Person(T1 name, T2 age);
    void showPerson();
    T1  name;
    T2 age;
};
template<class T1, class T2>
Person<T1, T2>::Person(T1 name, T2 age) {
    this->name = name;
    this->age = age;
}

template<class T1, class T2>
void Person<T1, T2>::showPerson() {
    cout << ".............." << endl;
}
```

```c++
#include <iostream>
using namespace std;
//第一种解决方式，直接包含 源文件
//#include "person.cpp"  //#include "person.h"

//第二种解决方式，将.h和.cpp中的内容写到一起，将后缀名改为.hpp文件
#include "person.hpp"
void test01(){
    Person<string, int> p1("孙悟空", 20);
    p1.showPerson();
}

int main(){
    test01();
    system("pause");
    return 0;
}
```

### 类模板和友元

全局函数类内实现：直接在类内声明友元

全局含类外实现：需要提前让编译器知道全局函数的存在

```c++
#include<iostream>
using namespace std;

//2.
template<class T1, class T2>
class Person;                    //提前声明Person类
template<class T1, class T2>
void printPerson2(Person<T1, T2> &p);     //让编译器提前知道这个函数的存在

template<class T1, class T2>
class Person{
    //1.全局函数，类内实现
    friend void printPerson(Person<T1, T2> &p){
        cout << "姓名：" << p.name << "，年龄：" << p.age << endl;
    }
    //2.全局函数类外实现
    friend void printPerson2<>(Person<T1, T2> &p);  //创建友元
public:
    Person(T1 name, T2 age){
        this->name = name;
        this->age = age;
    }
private:
    T1 name;
    T2 age;
};
//1.
void test01(){
    Person<string, int> p("Tom", 20);
    printPerson(p);
}

//2.
template<class T1, class T2>
void printPerson2(Person<T1, T2> &p){
    cout << "姓名：" << p.name << "，年龄：" << p.age << endl;
}
//2.
void test02(){
    Person<string,int> p2("Jerry", 20);
    printPerson2(p2);
}

int main(){
    test01();
    test02();
    system("pause");
    return 0;
}
```

### 类模板案例：数组类封装

`myArray.hpp`

```c++
#pragma once
#include <iostream>
using namespace std;

template<class T>
class MyArray{
public:
    //有参构造
    MyArray(int capacity);
    //拷贝构造
    MyArray(const MyArray &myArray){
        this->capacity = myArray.capacity;
        this->size = myArray.size;
        //深拷贝
        this->pAddress = new T[myArray.capacity];
        //将myArray中的数据都拷贝过来
        for(int i=0; i<myArray.size;i++){
            this->pAddress[i] = myArray.pAddress[i];
        }
//        cout << "MyArry拷贝构造调用" << endl;
    }
    //重载operator 防止浅拷贝的问题
    MyArray& operator=(const MyArray &myArray){
        //先判断原来堆区是否有数据，如果有先释放
        if(this->pAddress != NULL){
            delete[] this->pAddress;
            this->pAddress = NULL;
            this->capacity = 0;
            this->size = 0;
        }
//        cout << "MyArry的operator=调用" << endl;
        //深拷贝
        this->capacity = myArray.capacity;
        this->size = myArray.size;
        this->pAddress = new T[myArray.capacity];
        for(int i=0;i<myArray.size;i++){
            this->pAddress[i] = myArray.pAddress[i];
        }
        return *this;
    }
    //尾插法
    void pushBack(const T &value) {
        if(size == capacity){
            cout << "容量满了" << endl;
            return;
        }
        this->pAddress[size++] = value;
    }
    //尾删法
    void popBack(){
        //让用户访问不到最后一个元素
        if(size == 0){
            cout << "无数据" << endl;
        }
        size--;
    }
    //通过下标方式访问数组中的数据
    T& operator[](int index){
        return pAddress[index];
    }
    //返回数组的容量
    int getCapacity(){
        return capacity;
    }
    //返回数组大小
    int getSize(){
        return size;
    }
    //析构函数
    ~MyArray();
private:
    T * pAddress;  //指针指向堆区开辟的真实数组
    int capacity;  //数组容量
    int size;  //数组大小
};

template<class T>
MyArray<T>::MyArray(int capacity) {
    this->capacity = capacity;
    this->size = 0;
    this->pAddress = new T[capacity];
//    cout << "MyArry有参构造调用" << endl;
}
template<class T>
MyArray<T>::~MyArray() {
    if(this->pAddress != NULL){
//        cout << "MyArry析构调用" << endl;
        delete[] this->pAddress;
        this->pAddress = NULL;
    }
}
```

`person.hpp`

```C++
#pragma once
#include <iostream>
using namespace std;

template<class T1,class T2>
class Person{
public:
    Person(){};
    Person(T1 name, T2 age);
    void showPerson();
    T1  name;
    T2 age;
};
template<class T1, class T2>
Person<T1, T2>::Person(T1 name, T2 age) {
    this->name = name;
    this->age = age;
}

template<class T1, class T2>
void Person<T1, T2>::showPerson() {
    cout << ".............." << endl;
}
```

`mian.cpp`

```c++
#include <iostream>
using namespace std;
#include "myArray.hpp"
#include "person.hpp"

void printArray(MyArray<int> myArray){
    for(int i=0; i<myArray.getSize() ;i++){
        cout << myArray[i] << "  ";
    }
    cout << endl;
}

void test01(){
    MyArray<int> arr1(5);
    MyArray<int> arr2(arr1);
    MyArray<int> arr3(100);
    arr3 = arr1;
    for(int i=0; i<5;i++){
        arr1.pushBack(i);
    }
    cout << "arr1的打印输出为" << endl;
    printArray(arr1);
    cout << "arr1的容量：" << arr1.getCapacity() << endl;
    cout << "arr1的大小：" << arr1.getSize() << endl;
    arr1.popBack();
    printArray(arr1);
    cout << "arr1的容量：" << arr1.getCapacity() << endl;
    cout << "arr1的大小：" << arr1.getSize() << endl;
}

void printPersonArray(MyArray<Person<string, int>>& arr){
    for(int i =0 ;i < arr.getSize(); i++){
        cout << "姓名：" << arr[i].name << "\t年龄：" << arr[i].age << endl;
    }
}

void test02(){
    Person<string, int> p1("张三0", 20);
    Person<string, int> p2("张三1", 30);
    Person<string, int> p3("张三2", 40);
    Person<string, int> p4("张三3", 50);
    Person<string, int> p5("张三4", 60);
    MyArray<Person<string, int>> array(10);
    array.pushBack(p1);
    array.pushBack(p2);
    array.pushBack(p3);
    array.pushBack(p4);
    array.pushBack(p5);
    printPersonArray(array);
    cout << "array的容量：" << array.getCapacity() << endl;
    cout << "array的大小：" <<array.getSize() << endl;
}

int main(){
//    test01();
    test02();
    system("pause");
    return 0;
}
```



# 七、STL

## STL概念：

STL(Standard Template Library)标准模板库

STL从广义上分为：容器、算法、迭代器

容器和算法之间通过迭代器进行无缝衔接

STL几乎所有的代码都采用了模板类或者模板函数

### STL 六大组件

**容器、算法、迭代器、仿函数、适配器（配接器）、空间配置器**

**容器**：各种数据结构，如 vector、list、deque、set、map等，用来存放数据

**算法**：各种常用的算法，如sort、find、copy、for_each等

**迭代器**：扮演了容器与算法之间的胶合剂

**仿函数**：行为类似函数，可作为算法的某种策略

**适配器**：一种用来修饰容器或者仿函数或者迭代器接口的东西

**空间配置器**：负责空间的配置与管理



**容器**：

常用的数据结构：数组，链表，树，栈，队列，集合，映射表 等

序列式容器：强调值的排序，序列式容器中的每个元素均有固定的位置

关联式容器：二叉树结构，各元素之间没有严格的物理上的顺序关系

**算法**：

质变算法：是指运算过程中会更改区间内的元素的内容，例如 拷贝，替换，删除等

非质变算法：不更改区间内的元素，如 查找，计数，遍历，寻找极值等

**迭代器**：
		提供一种方法，使之能够依序寻访某个容器的各个元素，而又无需暴露该容器的内部表示方式

每种容器都有自己的专属迭代器

迭代器类似于指针

迭代器的种类

| 种类           | 功能                                             | 支持运算                                  |
| -------------- | ------------------------------------------------ | ----------------------------------------- |
| 输入迭代器     | 对数据只读访问                                   | 只读，支持++、==、！=                     |
| 输出迭代器     | 对数据只写访问                                   | 只写，支持++                              |
| 前向迭代器     | 读写操作，并能向前推进迭代器                     | 读写，支持++、==、！=                     |
| 双向迭代器     | 读写操作，并能向前向后操作                       | 读写，支持++、--                          |
| 随机访问迭代器 | 读写操作，可以以跳跃的方式任意访问数据，功能最强 | 读写，支持++、--、[n]、-n、< ，<=，> ，>= |

常用的式双向或者随机访问的迭代器



## 常用容器

### vector测试

#### 测试vector的声明、写数据和打印

```c++
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void MyPrint(int val){
    cout << val << endl;
}

void test(){
    vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);

    vector<int>::iterator  itBegin = v.begin();   //起始迭代器   指向容器中第一个元素
    vector<int>::iterator  itEnd = v.end();       //结束迭代器，指向容器中最后一个元素的下一个位置

    while (itBegin != itEnd){
        cout << *itBegin << endl;
        itBegin++;
    }

    for(vector<int>::iterator it = v.begin();it!=v.end(); it++){
        cout << *it << endl;
    }

    //第三种
    for_each(v.begin(), v.end(), MyPrint);

}

int main(){
    test();
    system("pause");
    return 0;
};

```

#### 测试：vector存放指针

```c++
#include<iostream>
#include <vector>

using namespace std;
#include "person.hpp"

void test01(){
    vector<Person<string, int>> v;
    Person<string, int> p1("aaa", 10);
    Person<string, int> p2("bbb", 60);
    Person<string, int> p3("ccc", 30);
    Person<string, int> p4("ddd", 20);
    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);
    for(vector<Person<string,int>>::iterator it=v.begin(); it!=v.end();it++){
        it->showPerson();
    }
}

void test2(){
    vector<Person<string, int>*> v;
    Person<string, int> p1("aaa", 10);
    Person<string, int> p2("bbb", 60);
    Person<string, int> p3("ccc", 30);
    Person<string, int> p4("ddd", 20);
    v.push_back(&p1);
    v.push_back(&p2);
    v.push_back(&p3);
    v.push_back(&p4);

    for(vector<Person<string,int>*>::iterator it = v.begin(); it!=v.end(); it++){
        (*it)->showPerson();
    }
}


int main(){
    test01();
    test2();
    system("pause");
    return 0;
}
```

#### vector嵌套容器

```c++
void test03(){
    vector<vector<int>> v;
    vector<int> v1;

    vector<int> v2;
    vector<int> v3;
    vector<int> v4;
    for(int i=0;i<4;i++){
        v1.push_back(i+1);
        v2.push_back(i+2);
        v3.push_back(i+3);
        v4.push_back(i+4);
    }

    v.push_back(v1);
    v.push_back(v2);
    v.push_back(v3);
    v.push_back(v4);

    for(vector<vector<int>>::iterator it = v.begin(); it != v.end(); it++){
        for(vector<int>::iterator it2 = it->begin(); it2 != it->end(); it2++){
            cout << *it2 << " ";
        }
        cout << endl;
    }


}
```

### string

#### string基本概念

本质：string是c++风格的字符串，而string的本质是一个类

string和char *区别：
		`char*`是一个指针

stirng是一个类*，类内封装了`char*`，管理这个字符串，是一个`char*`型的容器

特点：

封装了很多的方法 **查找find，拷贝copy，删除delete，替换replace，插入insert**

string管理char*所分配的内存，不用担心复制越界和取值越界，由类内部进行负责

#### string的构造函数

```c++
string();                             //创建一个空字符串
string(const char* s);				  //使用字符串s初始化
string(const string& str);			  //使用一个string对象初始化另一个对象 （拷贝构造）
string(int n, char c);                //使用n个字符c初始化
```

#### string的赋值操作

```c++
string& operator=(const char *s);               //str = str3;
string& operator=(const string &s);
string& operator=(char c);
string& assign(const char *s);                  //str.assign();
string& assign(const char *s, int n);           //把字符串的前n赋值个当前字符串
string& assign(const string &S);
string& assign(int n, char c);
```

#### string的拼接操作

```c++
string& operator+=(const char *s); 
string& operator+=(const char c); 
string& operator+=(const string& str);
string& append(const char *s); 
string& append(const char *s, int n); 
string& append(const string &s); 
string& append(const string &s, int pos,int n); 
```

#### string查找和替换

```c++
int find(const string& str, int pos=0) const;             //查找str第一次出现位置，从pos开始
int find(const char* s, int pos=0) const;				  //查找s第一次出现位置，从pos开始查找
int find(const char* s, int pos, int n) const;			  //从pos位置查找s的前n个字符的第一次位置
int find(const char c, int pos=0) const;				  //查找字符c此一次出现的位置
int rfind(const string* str, int pos=npos) const;		  //查找str最后一次位置，从pos开始
int rfind(const char* s, int pos=npos) const;			  //查找s最后一次出现的位置，从pos开始查找
int rfind(const char* s, int pos, int n) const;    		  //从pos开始查找s的前n个字符最后一次位置
int rfind(const char c, int pos=0) const; 				  //查找字符c最后出现的位置
string& replace(int pos, int n, const string& str);   	  //替换从pos开始n个字符为字符串str
string& replace(int pos, int n, const char *s);			  //替换从pos开始的n个字符为字符串s
```

**find() 和 rfind() 没查到返回 -1**

#### string的比较

```c++
int compare(const string &s) const;
int compare(const char *s) const;
```

返回值为0，则两个字符串相等

#### string的存取

`char& operator[](int n);`

`char& at(int n);`

#### string的插入和删除

`string& insert(int pos, const char *s);`           				//插入字符

`string& insert(int pos, const string& str);`				//插入字符

`string& insert(int pos, int n, char c);`						//在指定位置插入n个字符c	

`string& erase(int pos, int n =npos);`							  //删除从pos开始的你和字符

#### string截字串

`string substr(int pos = 0, int n=npos) const;` 			//返回由pos开始的n个字符串组成的字符串

### vector容器

单端数组

与普通数组的区别：数组是静态空间，vector可以**动态扩展**

**动态扩展：**

找更大的空间把数据拷贝进去，然后释放原来的空间

**v.begin()指向开始元素**

**v.end()指向最后元素的后一位置**

**v.rend()指向开始元素前一位置**

**v.rbegin()指向最后一个元素**

==vector的迭代器是支持随机访问的迭代器==

#### vector的构造函数

`vector<T> v;`											//采用模板实现类实现，默认构造函数

`vector v2(v.begin(), v.end());`  				   //将[begin(), end())区间中元素拷贝给自身

`vector v(n,elem);`									   //构造函数将n个elem拷贝给本身

`vector v(const vector &vec);`					//拷贝构造函数

#### vector的赋值操作

`vector& operator=(const vector &vec);`    //重载等号赋值操作

`assign(beg , end);`    //将[beg， end) 区间中的数据拷贝赋值给本身

`assign(n, elem);`      //将n个elem拷贝赋值给本身

#### vector的容量和大小

`empty();`                                          	//判断是否为空

`capacity();`										//容器容量

`size();`												//返回容器中元素个数，																		

`resize(int num);`                             //重新指定容器长度，若容器变成，则以默认值填充新位置，如果容器变短，则末尾超出的元																		//素会被删除

`resize(int num, elem);`				//重新定义容器的长度，若容器边长，用elem填充新位置，若变短，删除超出元素

#### vector插入和删除

`push_back(elem);`															//尾插elem

`pop_back();`																	  //删除最后一个元素

`insert(const_iterator pos, ele);`						  //迭代器指向位置pos插入ele

`insert(const_iterator pos, int count, elem)`   //迭代器指向位置pos插入count 个 elem元素

`erase(const_iterator pos);`									  //删除迭代器指向的元素

`erase(const_iterator start, const_iterator end);`	//删除迭代器从start到end之间的元素

`clear();`																			//清空容器中的所有元素

#### vector数据存储

at(index);              返回index所指元素

operator[];           返回index索引元素

front();					返回第一个元素

back();					返回最后一个元素

#### vector互换容器

swap(vec);    //互换两个容器的元素

用途：巧用swap可以收缩内存空间

使用resize() 不会改变容量，可以使用swap

```c++
void test(){
    vector<int> v;
    for(int i=0; i<10000; i++){
        v.push_back(i);
    }
    cout << "v的容量为：" << v.capacity() << endl;         //16384
    cout << "v的大小为：" << v.size() << endl;             //10000
    v.resize(3);
    cout << "v的容量为：" << v.capacity() << endl;         //10000
    cout << "v的大小为：" << v.size() << endl; 			  //3
    vector<int>(v).swap(v);								 //vector<int>(v)//匿名对象，以v初始化;与v交换容器，匿名对														 //象系统自动回收
    cout << "v的容量为：" << v.capacity() << endl;  		  //3
    cout << "v的大小为：" << v.size() << endl;             //3
}
```

#### vector预留空间

减少vector在动态拓展容量时的拓展次数

`reserve(int len);`  容器预留len个元素长短，预留位置不初始化，元素不可访问

### deque容器

双端数组，可以对头端进行插入删除操作

**deque和vector的区别：**

vector对于头部的插入删除效率低，数据量越大，效率越低

deque相对而言，对头部的插入删除速度比vector快

vector访问元素时的速度会比vector快，这和两者的内部实现有关

<img src="https://img-blog.csdnimg.cn/e22b69bf6a294a9da53d8714428230d8.png#pic_center" alt="在这里插入图片描述" style="zoom:50%;" />

内部工作原理

- deque内部有个`中控器`，维护每段缓冲区中的内容，缓冲区中存放真实数据
- 中控器维护的是每个缓冲区的地址，使得使用deque时像一片连续的内存空间

<img src="https://img-blog.csdnimg.cn/9971deddb67f47ebb6871886f6255790.png#pic_ceter" alt="在这里插入图片描述" style="zoom: 67%;" />

deque迭代器支持随机访问



#### deque构造函数

`deque<T> deqT;`

`deque(beg,end);`

`deque(n,ele);`

`deque(const deque &deq);`



#### deque的赋值操作

`deque& operator=(const deque &deq);`

`assign(beg, end);`

`assign(n, elem);`

#### deque的大小操作

`deque.empty();`

`deque.size();`

`deque.resize(num);`

`deque.resize(num, elem);`

#### deque插入和删除

两端插入操作：
		`push_back(elem);`

`push_front(elem);`

`pop_back();`

`pop_front();`



`insert(pos, elem);`

`insert(pos, n, elem);`

`insert(pos, beg, end);`

`clear();`

`erase(beg, end);`

`erase(pos);`

#### deque数据存取

`at(int idx);`

`operator [];`

`front();`

`back();`

#### deque排序

头文件：`algorithm`

对于支持随机访问的迭代器容器，都可以利用sort算法进行排序

sort(iterator beg, iterator end);

### stack容器

**先进后出**

构造函数

`stack<T> stk;`

`stack(cosnt stack &stk);`

赋值操作

`stack& operator=(const stack &stk);`

数据存取

`push(elem);`

`pop();`

`top();`   				//返回栈顶

大小操作

`empty();`

`size();`

### queue容器

**先进先出**

构造函数

`queue<T> que;`

`queue(const queue &que);`

赋值操作

`queue& operator=(const queue &que);`

数据存取

`push(elem);`

`pop();`

`back();`

`front();`

大小操作

`empty();`

`size();`





### list容器

![img](https://img0.baidu.com/it/u=2691757174,3486416381&fm=253&fmt=auto&app=138&f=PNG?w=499&h=218)

链表的存储方式并不是连续的内存空间，因此链表list中的迭代器只支持前移和后移，属于**双向迭代器**

**优点：**

采用动态的存储分配，不会造成内存的浪费和溢出

链表执行插入和删除操作十分方便，修改指针即可，不需要大量移动元素

**缺点：**

链表灵活，但是空间（指针域）和时间（遍历）额外耗费较大

list的重要性质：插入操作和删除操作都不会造成原有的list迭代器的失效，这在vector是不成立的

**总结：**list和vector是最常使用的，各有优缺点



**list的构造函数**

`list<T> list;`

`list(beg, end);`

`list(n, elem);`

`list(const list &lst);`

**list的赋值和交换**

`assign(beg, end);`

`assign(m, elem);`

`list& operator=(const list &lst);`

`swap(lst);`

**list大小操作**

`size();`

`empty();`

`resize(num);`

`resize(num, elem);`

**list插入和删除**

`push_bcak(elem);`

`pop_back();`

`push_front(elem);`

`pop_front();`

`insert(pos, elem);`

`insert(pos, n, elem);`

`insert(pos, beg, end);`

`clear();`

`erase(beg, end);`

`erase(pos);`

`remove(elem);`  //删除所有和elem匹配的元素

**list数据存取**

`front();`

`nack();`

**list的反转和排序**

`reserve();`

`sort();`               //成员函数

所有不支持随机访问的迭代器容器，不可以用标准算法，但是**内部会提供对应的一些算法**

降序

```c++
bool myCompare(int v1, int v2){
	return v1 > v2;
}
void test(){
    list<int> L;
    L.sort(); //默认升序排序
    L.sort(myCompare); // 降序排序，自己指定规则
}
```

### set/multiset容器

所有元素在插入时自动被排序

本质：属于**关联式**容器，底层结构是**二叉树**实现的

**set/multiset区别：**

set不允许容器里有重复的元素

multiset允许有重复的元素

**set的构造与赋值**

`set<T> st;`

`set(const set &st);`

赋值：

`set& operator=(const set &st);`

**set的大小和交换**

`size();`

`empty();`

`swap(st);`

**set的插入和删除**

`insert();`

`clear();`

`erase();`

`erase(beg, end);`

`erase(elem);`    // 删除elem元素

**set 查找和统计**

`find(key);`   //存在，返回该键的元素的迭代器，若不存在，返回set.end();

`count(key);`   //对于set而言 非0即1

**set和multiset的区别**

set不可存放重复值，multiset可以

set插入数据的同时会返回插入结果，表示插入成功

`pair<set<int>::iterator, bool> ret = s.insert(10);`

`ret.second  //取bool值`

multiset不会检测数据，因此可插入重复数据

**pari使用-pair对组的创建**

成对出现的数据，利用对组可以返回两个数据

创建方式

`pair<type, type> p (value1, value2);`

`pair<type, type> p = make_pair(value1, value2);`

获取数据

**p.first   p.second**

**set容器 内置类型指定排序规则**

set容器默认是从大到小，掌握如何改变排序规则

利用仿函数，可以改变排序规则

```c++
#include<iostream>
using namespace std;
#include<set>

class MyCompare{
public:
    bool operator()(int v1, int v2) const{
        return v1 > v2;
    }
};

void test01(){
    set<int> s1;
    s1.insert(10);
    s1.insert(20);
    s1.insert(50);
    s1.insert(30);
    s1.insert(40);
    for(set<int>::iterator it=s1.begin(); it!=s1.end(); it++){
        cout << *it  << "  ";
    }
    cout << endl;

    //指定排序规则为从大到小
    set<int,MyCompare> s2;
    s2.insert(10);
    s2.insert(20);
    s2.insert(50);
    s2.insert(30);
    s2.insert(40);
    for(set<int, MyCompare>::iterator it = s2.begin(); it != s2.end(); it++){
        cout << *it << "  ";
    }
    cout << endl;
}

int main(){
    test01();
    system("pause");
    return 0;
}
```

**自定义类型数据类型指定排序规则**

```c++
class Person{
public:
    Person(string name, int age){
        this->name = name;
        this->age = age;
    }
    string name;
    int age;
};
class ComparePerson{
public:
    bool operator()(const Person &p1, const Person &p2) const{
        return p1.age > p2.age;
    }
};
void test02(){
    //自定义数据类型，都指定排序规则
    set<Person, ComparePerson> sp;
    Person p1("刘备", 24);
    Person p2("关羽", 26);
    Person p3("张飞", 29);
    Person p4("赵云", 14);

    sp.insert(p1);
    sp.insert(p2);
    sp.insert(p3);
    sp.insert(p4);

    for(set<Person, ComparePerson>::iterator it=sp.begin(); it!=sp.end(); it++){
        cout << "姓名：" << it->name << "年龄：" << it->age << endl;
    }
}
```

### map/multimap容器

**map的基本概念**

**简介：** map里面的所有元素都是pair

​			pair中第一个元素为key（键值），起到索引的作用，第二个元素为value（实值）

​			所有元素都会根据元素的键值进行自动排序

**本质：**map/multimap属于关联式容器，底层结构是用二叉树实现的。

**优点：**

可以根据key值快速获取vlaue值

map和multimap的区别：

map不允许容器中有重复的key值元素

multimap允许容器中有重复key值的元素

**map的构造和赋值**

`map<T1, T2> mp;`

`map(const map &mp);`

`map& operator=(const map &map);`

 

**map的大小和交换**

`size();`

`empty();`

`swap(st);`



**map的插入和删除**

`insert(elem);`

```c++
map.insert(pair<int, int> (1,10));

map.insert(make_pair(2,20));

map.insert(map<int, int>::value_type(3,30));

m[4] = 40;  //不推荐，如果[key] 里面的key不存在，会自动创建这个键值对，key = this.key ， value = 0
```

`clear();`

`erase(pos);`

`erase(beg, end);`

`erase(key);`



**map的查找和统计**

find(key);                 //有返回该键的元素的迭代器，没有，返回map.end();

count(key);           // 非0即1



**map容器的排序**

map容器默认是按照key从小到大排序

利用仿函数，可以改变排序规则

```c++
#include<iostream>
#include <map>
#include <utility>

using namespace std;


class MyCompare{
public:
    bool operator()(int v1, int v2) const{
        return v1 > v2;
    }
};

void test01(){
    map<int, int, MyCompare> mp;
    mp.insert(make_pair(1,10));
    mp.insert(make_pair(2,20));
    mp.insert(make_pair(3,30));
    mp.insert(make_pair(4,40));
    mp.insert(make_pair(5,50));
    mp.insert(make_pair(6,60));


    for(map<int,int>::iterator it=mp.begin(); it!=mp.end(); it++){
        cout << "key = " << it->first << "   value = " << it->second << endl;
    }
    cout << endl;
}

class Person{
    friend ostream& operator<<(ostream &cout , Person &p1);
public:
    Person(string name, int age){
        this->name = std::move(name);
        this->age = age;
    }
    string name;
    int age;

};

ostream& operator<<(ostream &cout , const Person &p1){
    cout << "姓名：" << p1.name << "  年龄：" << p1.age;
    return cout;
}

class MyCompare2{
public:
    bool operator()(const Person &p1, const Person &p2)const{
        return p1.age > p2.age;
    }
};

void test02(){
    map< Person,int, MyCompare2> mp;
    Person p1("张三" , 20);
    Person p2("李四" , 21);
    Person p3("王五" , 23);
    Person p4("马六" , 10);
    Person p5("七七" , 19);

    mp.insert(make_pair(p1, 1));
    mp.insert(make_pair(p2, 2));
    mp.insert(make_pair(p3, 3));
    mp.insert(make_pair(p4, 4));
    mp.insert(make_pair(p5, 5));

    for(map<Person, int, MyCompare2>::iterator it=mp.begin(); it!=mp.end(); it++){
        cout << "key = " << (*it).first << "  value = " << it->second << endl;
    }
}

int main(){
//    test01();
    test02();
    system("pause");
    return 0;
}
```

#### 案例员工分组

```c++
#include<iostream>
#include <vector>
#include <map>


#define CEHUA 1
#define MEISHU 2
#define YANFA 3

using namespace std;

class Worker{
public:
    string e_Name;
    int e_Salary;
};

void createWorker(vector<Worker> &vector1) {
    string nameSeed = "ABCDEFGHIJ";

    for(int i=0; i<10; i++){
        Worker worker;
        worker.e_Name = "Worker";
        worker.e_Name += nameSeed[i];
        worker.e_Salary = rand() %10000 + 10000;
        vector1.push_back(worker);
    }
}
void setGroup(vector<Worker> &v, multimap<int, Worker> &mm){
    for(vector<Worker>::const_iterator it = v.begin(); it!=v.end();it++){
        //产生随机部门编号
        int deptId = rand()%3+1;

        mm.insert(make_pair(deptId, *it));
    }
}

void showWorkByGroup(multimap<int, Worker> &mm){
    cout << "策划部门： " << endl;
    auto pos= mm.find(CEHUA);  //找到这个部门起始地址
    int count = mm.count(CEHUA);        //计数
    int index = 0;
    for(;pos!=mm.end()&&index < count; pos++, index++){
        cout << "姓名：" << pos->second.e_Name << "  工资：" << pos->second.e_Salary << endl;
    }
    cout << endl << "美术部门： " << endl;
    pos = mm.find(MEISHU);
    count = mm.count(MEISHU);
    index = 0;
    for(;pos!=mm.end()&&index < count; pos++, index++){
        cout << "姓名：" << pos->second.e_Name << "  工资：" << pos->second.e_Salary << endl;
    }
    cout << endl << "研发部门： " << endl;
    pos = mm.find(YANFA);
    count = mm.count(YANFA);
    index=0;
    for(;pos!=mm.end()&&index < count; pos++, index++){
        cout << "姓名：" << pos->second.e_Name << "  工资：" << pos->second.e_Salary << endl;
    }
}

int main(){
    srand((unsigned int)time(NULL));
    //创建员工
    vector<Worker> vWorker;
    createWorker(vWorker);

    //分组
    multimap<int, Worker> mm;

    setGroup(vWorker, mm);
//    for(vector<Worker>::const_iterator it=vWorker.begin(); it!=vWorker.end(); it++){
//        cout << "姓名：" << it->e_Name << "  年龄：" << it->e_Salary << endl;
//    }

    showWorkByGroup(mm);

    system("pause");
    return 0;
}
```

## 函数对象

### 函数对象

**函数对象的概念**

**重载函数**调用操作符的类，其对象常称为**函数对象**

函数对象使用重载的()时，行为类似函数调用，也叫**仿函数**

**本质：**

函数对象（**仿函数**）是一个类，不是一个函数

**函数对象使用**

**特点：**

函数对象使用时，可以像普通函数那样调用，可以有参数，可以有返回值

函数对象超出普通函数的概念，函数对象可以有自己的状态

函数对象可以作为参数传递

```c++
#include <iostream>
using namespace std;

class MyAdd{
public:
    int operator()(int v1, int v2){
        return v1 + v2;
    }
};

void test1(){
    //函数对象使用时，可以像普通函数那样调用，可以有参数，可以有返回值
    MyAdd myAdd;
    cout << myAdd(1,2) << endl;
}

class MyPrint{
public:
    MyPrint(){
        this->count = 0;
    }
    void operator()(string test){
        cout << test << endl;
        count++;
    }
    int count;
};

void test2(){
    //函数对象超出普通函数的概念，函数对象可以有自己的状态，count计数
    MyPrint myPrint;
    myPrint("Hello World");
    myPrint("Hello World");
    myPrint("Hello World");
    cout << "调用次数：" << myPrint.count <<endl;
}

//函数对象可以作为参数传递
void doPrint(MyPrint & mp, string test){
    mp(test);
}
void test3(){
    MyPrint myPrint;
    doPrint(myPrint, "Hello,C++ ");
}

int main(){
    test1();
    test2();
    test3();
    system("pause");
    return 0;
}
```

### 谓词

返回bool类型的仿函数称为**谓词**

如果operator()接受一个参数，那么叫做一元谓词

如果operator()接受两个参数，那么叫做二元谓词

```c++
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class GreaterFive{
public:
    bool operator()(int val){
        return val > 5;
    }
};

void test01(){
    vector<int> v;
    for(int i=0; i<10; i++){
        v.push_back(i);
    }

    //查找容器，有没有大于5的数
    vector<int>::iterator it = find_if(v.begin(), v.end(),GreaterFive());
    if(it == v.end()){
        cout << "没找到" << endl;
    }else{
        cout << "找到了： " << *it << endl;
    }
}

class MyCompare{
public:
    bool operator()(int v1, int v2) const{
        return v1 > v2;
    }
};

void test02(){
    vector<int> v;
    v.push_back(10);
    v.push_back(40);
    v.push_back(30);
    v.push_back(60);
    v.push_back(50);
    sort(v.begin(), v.end());

    for(vector<int>::iterator it=v.begin(); it!=v.end(); it++){
        cout << *it << "  ";
    }
    cout << endl;

    sort(v.begin(),v.end(),MyCompare());   //传入仿函数改变排序规则
    for(vector<int>::iterator it=v.begin(); it!=v.end(); it++){
        cout << *it << "  ";
    }
    cout << endl;
}

int main(){
    test01();
    test02();
    system("pause");
    return 0;
}
```

### 内建函数对象

STL内建了一些函数对象

分类：
		算数仿函数

关系仿函数

逻辑仿函数

用法：

这些仿函数所产生的对象，用法和一般函数完全相同

使用内建函数对象，需要引入头文件`#include<functional>`

#### 算数仿函数：

实现四则运算

其中negate是一元运算，其他是二元运算

```C++
template<class T> T plus<T>  //加法仿函数
template<class T> T minus<T> //减法仿函数
template<class T> T multiplies<T>  //乘法仿函数
template<class T> T divides<T>  //除法仿函数
template<class T> T modulus<T>  //取模仿函数
template<class T> T negate<T>  //取反仿函数
    
negate<int> n;
cout << n(50) << endl;
plus<int> p;
cout << p(1,2) << endl;
```

#### 关系仿函数

```c++
template<class T> bool equal_to<T>  //等于
template<class T> bool not_equal_to<T>  //不等于
template<class T> bool greater<T>  //大于
template<class T> bool greater_equal<T>  //大于等于
template<class T> bool less<T>  //小于
template<class T> bool less_equal<T>  //小于等于
    
void test04(){
    vector<int> v;
    v.push_back(10);
    v.push_back(40);
    v.push_back(30);
    v.push_back(60);
    v.push_back(50);
    for(vector<int>::iterator it=v.begin(); it!=v.end(); it++){
        cout << *it << "  ";
    }
    cout << endl;
    sort(v.begin(), v.end(), greater<int>());   //重点 ，不需要自己手写 降序
    for(vector<int>::iterator it=v.begin(); it!=v.end(); it++){
        cout << *it << "  ";
    }
    cout << endl;
}
```

#### 逻辑仿函数

```c++
template<class T> bool logical_and<T>  //逻辑与
template<class T> bool logical_or<T>  //逻辑或
template<class T> bool logical_not<T>  //逻辑非
```





## 常用的算法

算法主要是由头文件`<algorithm>` `<functinal>` `<numeric>` 组成

`<algorithm>`是STL头文件中最大的一个，范围涉及到比较、交换、查找、遍历、复制、修改等等

`<numeric>`体积很小，只包含几个在序列上面进行简单的数学运算的模板函数

`<functional>`定义了一些模板类，用以声明函数对象

### 遍历算法

`for_each`   //遍历容器

`transform`   //搬运容器到另一个容器

`for_each(iterator beg, iterator end, _func)`

```c++
void print01(int val){
    cout << val << " ";
}

class print02{
public:
    void operator()(int val){
        cout << val << " ";
    }
};
void test(){
    vector<int> v;
    v.push_back(10);
    v.push_back(40);
    v.push_back(30);
    v.push_back(60);
    v.push_back(50);
	for_each(v.begin(), v.end(), print01);  //普通函数传函数名
    cout << endl;
    for_each(v.begin(), v.end(),print02());  //仿函数传对象
    cout << endl;
}
```

`transform(iterator beg1, iterator end1, iterator beg2, _func);`前面是源容器，后面是目标容器

```c++
class Transform{
public:
    int operator()(int v){
        //可以进行逻辑运算
        return v;
    }
};
class print02{
public:
    void operator()(int val){
        cout << val << " ";
    }
};
void test(){
    vector<int> v;
    for(int i=0; i<10; i++){
        v.push_back(i);
    }
    vector<int>vTarget;
    vTarget.resize(v.size());  //目标容器需要提前开辟空间，否则会崩
    transform(v.begin(), v.end(), vTarget.begin(), Transform());
    for_each(vTarget.begin(), vTarget.end(), print02());
}
```

### 查找算法

`find`         //查找元素

`find(iterator beg, iterator end , value);`

如果是自定义数据类型需要重载**operator==()**函数，返回值是迭代器



`find_if`    //按条件查找元素

`find_if(iterator beg, iterator end, _Pred);`

_Pred 函数或者谓词

```c++
class GreaterFive{
public:
    bool operator()(int val){
        return val > 5;
    }
};


class Person{
public:
    Person(string name, int age){
        this->name = name;
        this->age = age;
    }
    string name;
    int age;
};
class Greater20{
public:
    bool operator()(Person &p){
        return p.age > 20;
    }
};

void test06(){
    vector<int> v;
    v.reserve(10);
    for(int i=0; i<10; i++){
        v.push_back(i);
    }
    vector<int>::iterator  it = find_if(v.begin(), v.end(), GreaterFive());
    if(it == v.end()){
        cout << "没有找到" << endl;
    }else{
        cout << "找到大于5的数：" << (*it) << endl;
    }

    vector<Person> vP;
    Person p1("aaa", 10);
    Person p2("bbb", 20);
    Person p3("ccc", 30);
    Person p4("ddd", 40);
    vP.push_back(p1);
    vP.push_back(p2);
    vP.push_back(p3);
    vP.push_back(p4);
    vector<Person>::iterator it2 = find_if(vP.begin(), vP.end(), Greater20());
    if(it2 == vP.end()){
        cout << "没找到" << endl;
    }else{
        cout << "找到了，" << it2->name << " " << it2->age << endl;
    }
}
```

`adjacent_find(iterator beg, iterator end);`     //查找**相邻重复**元素

查的结果是相邻元素的第一个元素的迭代器



`binary_search(iterator beg, iterator end, vale);`    //二分法查找

返回结果是bool类型，有 返回true， 无 返回false，查找**有序序列**

`count(iterator beg, iterator end, value);`       //统计元素个数

自定义数据类型需要重载==号

`count_if(iterator beg, iterator end, _Pred)`     //按条件统计元素个数

**_Pred谓词**



### 排序算法

`sort(iterator beg, iterator end, _Pred);`  //排序

_Pred可以不写，不写只能处理内置数据类型，默认为升序排序

`random_shuffle(iterator beg, iterator end);`    //打乱排序

可能被删除了，需要加随机种子

`merge(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);`

需要提前分配内存 resize(num)；两个容器里数据必须是有序且排序规则相同（升， 降）

`reverse(iterator begin, iterator end);`



### 拷贝和替换算法

`copy(iterator beg, iterator end, iterator dest); ` //拷贝

需要提前分配空间

`replace(iterator beg, iterator end, oldvalue, newvalue);`   //替换

替换所有的oldvalue

`replace_if(iterator beg, iterator end, _pred, newvalue);`  //条件替换

_pred谓词，利用仿函数可以灵活



`swap(container c1, container c2);`  //交换，同类型的容器



### 算数生成算法

包含于`<numeric>`

`accumulate(iterator beg, iterator end ,value);`                //计算容器元素累计总和

vlaue起始值

`fill(iterator beg, iterator end, value);`                            //向容器中添加元素

后期重新填充元素

### 集合算法

`set_intersection(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);`//求两个容器的交集

**有序序列**

注意要给dest提前分配空间，返回交集的end迭代器，遍历时判断条件用返回的end迭代器，而不用dest的end迭代器

`set_union(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);`   //求两个容器的并集

**有序序列**

注意要给dest提前分配空间，返回并集的end迭代器，遍历时判断条件用返回的end迭代器，而不用dest的end迭代器

`set_difference(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);` //求两个容器的差集

**有序序列**

注意要给dest提前分配空间，返回并集的end迭代器，遍历时判断条件用返回的end迭代器，而不用dest的end迭代器 	



# 常见的细节问题：

## c++中会自动初始化的位置：

在 C++ 中，以下位置的变量可以自动初始化：

1. **命名空间作用域的静态变量**：静态变量在程序启动时会自动初始化为默认值，如果没有显式指定初始值。

    ```cpp
    static int myStaticVariable; // 在命名空间作用域内的静态变量，默认初始化为0
    ```

2. **块作用域的静态变量**：如果一个变量在块（如函数内部）中声明为静态，它会在程序的生命周期内保持其值，并在程序启动时自动初始化。

    ```cpp
    void myFunction() {
        static int myStaticVariable; // 在块作用域内的静态变量，默认初始化为0
    }
    ```

3. **全局变量**：全局变量（在任何函数之外定义的变量）会在程序启动时自动初始化。

    ```cpp
    int myGlobalVariable; // 全局变量，默认初始化为0
    ```

4. **静态成员数据变量**：静态成员数据变量属于整个类，会在程序启动时自动初始化。

    ```cpp
    class MyClass {
    public:
        static int myStaticVariable; // 静态成员数据变量，默认初始化为0
    };
    int MyClass::myStaticVariable;
    ```

5. **内建类型的局部变量**（C++11及更高版本）：如果你在函数内部声明一个内建类型（如int）的局部变量，并且没有显式地初始化它，它将会被默认初始化。

    ```cpp
    void myFunction() {
        int myVariable; // 默认初始化为未知的随机值
    }
    ```

需要注意的是，这些变量的初始化行为取决于它们的类型和声明位置，以及是否提供了显式的初始值。如果你不提供显式的初始值，它们将会按照默认规则进行初始化。

## 拷贝构造函数会出现的问题

拷贝构造函数可能会出现以下问题：

1. **无限递归调用**：如果拷贝构造函数的参数是按值传递的，而不是按引用传递，那么在调用拷贝构造函数时，会创建一个新的对象，这将导致无限递归调用。

    ```cpp
    class MyClass {
    public:
        int myVariable;

        // 错误的拷贝构造函数
        MyClass(MyClass other) {
            myVariable = other.myVariable;
        }
    };
    ```

    在上面的示例中，拷贝构造函数的参数是按值传递的，这将导致在拷贝构造函数内部创建一个新的 `MyClass` 对象，这个过程会不断循环下去，直到栈溢出。

2. **浅拷贝问题**：如果类中包含动态分配的资源（如堆内存），并且拷贝构造函数未正确实现，可能会导致多个对象共享同一块内存，这称为浅拷贝问题。

    ```cpp
    class MyClass {
    public:
        int* ptr;

        MyClass(const MyClass& other) {
            ptr = other.ptr; // 这是一个浅拷贝，导致两个对象共享同一块内存
        }
    };
    ```

    在上述示例中，拷贝构造函数将 `ptr` 的指针值从 `other` 复制给了自身对象。这意味着现在两个对象共享相同的内存块，如果其中一个对象释放了这块内存，另一个对象的指针就会成为悬空指针。

3. **未正确初始化成员变量**：如果拷贝构造函数没有正确地初始化所有成员变量，可能会导致对象在复制后处于一个不稳定的状态。

    ```cpp
    class MyClass {
    public:
        int myVariable;
    
        MyClass(const MyClass& other) {
            // myVariable没有被初始化，可能会包含未知的随机值
        }
    };
    ```

    在上面的示例中，拷贝构造函数没有正确初始化 `myVariable`，这意味着在复制后，新对象的 `myVariable` 可能包含未知的随机值。

总的来说，拷贝构造函数需要小心地实现，以确保正确地复制对象的状态，避免出现问题。通常，将拷贝构造函数的参数定义为引用类型是避免这些问题的重要步骤。此外，需要特别注意当类中包含动态分配的资源时，应该实现深拷贝而不是浅拷贝。



## 构造函数的调用问题：

在C++中，对于以下定义：

```cpp
A a1, a2[3], *pa, *pb[3];
```

会调用A类的构造函数几次取决于A类的默认构造函数是否存在以及是否被调用。

具体情况如下：

1. `A a1;`：会调用A类的构造函数一次，创建一个名为`a1`的对象。

2. `A a2[3];`：会调用A类的构造函数三次，分别创建一个数组`a2[0]`、`a2[1]`和`a2[2]`。

3. `A* pa;`：这里只是声明了一个指针`pa`，没有调用A类的构造函数。

4. `A* pb[3];`：这里只是声明了一个指针数组`pb`，没有调用A类的构造函数。

总结起来，对于给定的定义，会调用A类的构造函数四次。需要注意的是，只有在对象被创建时才会调用构造函数，声明一个指针并不会触发构造函数的调用。

## 构造函数的形式

当一个类中包含引用成员、常量成员和对象成员时，它的构造函数应该使用成员初始化列表来进行初始化。成员初始化列表允许你在构造函数体之前对成员进行初始化。

下面是一个示例：

```cpp
class MyClass {
public:
    int& myReference;    // 引用成员
    const int myConstant;  // 常量成员
    OtherClass myObject;  // 对象成员

    // 构造函数的成员初始化列表
    MyClass(int& ref, int constantValue, const OtherClass& obj) 
        : myReference(ref),  // 对引用成员进行初始化
          myConstant(constantValue),  // 对常量成员进行初始化
          myObject(obj)  // 对象成员的构造函数会在这里调用
    {
        // 在构造函数体中可以进行其他的初始化操作
    }
};
```

在上述示例中，`MyClass` 包含了一个引用成员 `myReference`，一个常量成员 `myConstant` 和一个对象成员 `myObject`。在构造函数中，使用了成员初始化列表来分别初始化这些成员。

请注意，引用成员和常量成员必须在成员初始化列表中进行初始化，因为它们不能在构造函数体内被赋值。

总的来说，构造函数的形式应该是：

```cpp
MyClass::MyClass(引用成员的类型& ref, const 常量成员的类型 constantValue, const 对象成员的类型& obj)
    : myReference(ref), myConstant(constantValue), myObject(obj)
{
    // 构造函数体
    // 其他初始化操作
}
```

这种方式可以确保在对象被创建时，所有成员都得到了正确的初始化。



## 派生类和基类同名方法的用优先问题

在 C++ 中，如果派生类和基类中都定义了同名的成员函数，派生类的函数会覆盖基类的函数，也就是说会优先调用派生类中的函数。

这个特性被称为函数的覆盖（override）。当你在派生类中定义了一个与基类中的成员函数具有相同名称和参数列表的函数时，该函数会覆盖基类中的函数。

举个例子：

```cpp
class Base {
public:
    void show() {
        std::cout << "Base class" << std::endl;
    }
};

class Derived : public Base {
public:
    void show() {
        std::cout << "Derived class" << std::endl;
    }
};

int main() {
    Derived d;
    d.show(); // 输出 "Derived class"
    return 0;
}
```

在上面的例子中，`Base` 类和 `Derived` 类都有一个名为 `show` 的成员函数。当你创建一个 `Derived` 类的对象并调用 `show` 函数时，会调用 `Derived` 类中的 `show` 函数，而不是 `Base` 类中的。

如果你想在派生类中调用基类的同名函数，你可以使用作用域解析运算符 `::` 来明确指定要调用的是基类中的函数：

```cpp
class Derived : public Base {
public:
    void show() {
        Base::show(); // 调用基类中的 show 函数
        std::cout << "Derived class" << std::endl;
    }
};
```

在上面的例子中，`Base::show()` 调用了基类 `Base` 中的 `show` 函数。

**但是如果将派生类的对象赋值给基类对象，再调用这个同名的方法？**

如果你将派生类的对象赋值给了一个基类对象，然后调用同名函数，会根据赋值时的对象类型来确定调用的是哪个函数。如果派生类对象被赋值给了一个基类对象，那么只能调用基类中存在的成员函数，而无法访问派生类特有的成员函数。

举个例子：

```cpp
class Base {
public:
    void show() {
        std::cout << "Base class" << std::endl;
    }
};

class Derived : public Base {
public:
    void show() {
        std::cout << "Derived class" << std::endl;
    }

    void derivedFunction() {
        std::cout << "Derived specific function" << std::endl;
    }
};

int main() {
    Derived d;
    Base b = d;  // 派生类对象 d 赋值给基类对象 b

    b.show(); // 输出 "Base class"
    // b.derivedFunction(); // 错误！基类对象无法调用派生类特有的成员函数

    return 0;
}
```

在上面的例子中，将派生类对象 `d` 赋值给了基类对象 `b`。当调用 `b.show()` 时，由于 `b` 是一个基类对象，所以调用的是基类中的 `show` 函数，输出 "Base class"。但是如果尝试调用 `b.derivedFunction()` 就会产生一个编译错误，因为基类对象无法访问派生类特有的成员函数。

如果你希望在基类中使用派生类特有的功能，你可能需要重新设计你的类层次结构或者使用虚函数来实现多态性。

