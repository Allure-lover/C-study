#include<iostream>
#include<cmath>
using namespace std;

/*
    函数分为库函数和用户自定义函数， 库函数包含相应的头文件就可以直接调用
    函数定义的基本形式： 函数类型 函数名(形参列表){ 语句序列 } 
        函数如果没有参数，可以写 void 或者 缺省
    函数类型与返回值
        函数类型缺省是为int类型
        无值型函数的函数类型为void
        return 语句 返回函数的运行结果，并结束函数的运行 return 表达式;  或 return (表达式); 无返回值函数 return;
    函数调用： 格式 函数名(实参列表)
    函数的嵌套；函数的调用可以嵌套，但是函数定义不能嵌套
    函数的递归调用：直接递归调用：函数体内调用函数自己
                   间接递归调用：函数体内调用其他函数，其他函数在调用本函数
    函数参数的传递：函数的值传递： 函数的值传递是单向的，对形参的操作不影响实参的值
                   函数的地址传递：形参是某种指针类型，实参为相应的地址，传递的是地址，既可以操纵传递的指针，也可以操纵传递的指针所指的内存空间
                   函数的引用传递：形参为某种类型的变量引用，实参为相应的变量，引用传递时，形参是对实参的重新命名，形参和实参指的是同一个内存空间
    函数参数的默认值：默认值可以在函数定义的时候给出，也可以在函数声明的时候给出
                   如果提供实参，则以提供的实参为主，若没有提供实参则以默认值作为实参
    函数的重载：函数名相同，函数参数的个数、类型、或者次序不同的函数。返回值不能作为重载的条件
    内联函数：当函数的功能比较简单时，可以将其定义为内联函数，在程序编译时将该函数的代码直接插入调用处
             语法：inline 函数类型 函数名(形参列表){ 语句序列 }
             用户指定为内联函数，系统不一定将其处理为内联函数
    exit函数和abort函数：终止程序的执行
            exit函数：exit(表达式); 如表达式的为0，正常退出；若非0，则异常退出
            abort函数：abort(); 执行该函数，系统不做任何收尾的工作，直接终止程序的执行
    指向函数的指针：定义指向函数的指针  函数类型 (*指针变量名)(形参列表); 函数类型和形参列表必须和所指向的函数相同，且指针名括起来的括号不能省略
                   指针指向函数：  指针变量名 = 函数名    将函数的入口地址赋值给指针变量
                   指针调用函数：  指针变量名(实参列表)  或者  (*指针变量名)(实参列表)
    预编译处理：预编译处理命令包括文件的包含，宏定义，条件编译
            头文件包含：#include<文件名>     在系统默认的文件目录中查找  （系统的库文件常用）
                       或者  #include"文件名"   会先在当前的源文件目录中查找，若未找到，再去默认目录中查找  （用户自定义文件常用）
                       功能：将指定的文件插入到该命令行位置以取代该命令行
                       注意点：①一条命令只能包含一个文件 ②文件包含允许嵌套
            宏定义：用一个表示符来代替一个字符序列，在预编译过程中将所有的宏名均替换为字符序列，字符序列可以是字符串，常量，表达式
                无参宏： #define 宏名 字符序列  
                有参宏： #define 宏名(形参列表) 字符序列  例：#define MAX(x,y) x*y  c = MAX(a,b);  --> c = a*b;
            条件编译：宏作为条件编译的基本语法格式： #ifdef 宏名   \n 程序段  \n #endif
                                                  #ifdef 宏名   \n 程序段1 \n #else \n 程序段2 #endif
    变量的作用域：
        块作用域：在语句块中定义的变量是局部变量  局部优先原则
        文件作用域：全局变量 应该先定义在使用；如果使用在前，定义在后，应该使用extern关键字说明  void f(){ extern int n; n++; } int n;
        函数原型作用域：函数原型说明语句中的形参的作用域只局限于该函数原型说明语句
        函数作用域
        类作用域
    变量的存储类型：
        计算机的存储系统主要包括：外存、内存、CPU的寄存器，外存的数据通常要调入到内存才可使用。计算机的存储空间大体可分为程序区和数据区
        数据区又可以分为静态存储区和静态存储区
        变量的存储类型可以分为 自动类型、静态类型、寄存器类型和外部类型，其中自动类型和寄存器类型属于动态存储方式，静态类型和外部类型属于静态存储方式
        静态存储类型在整个程序执行期间一直占用内存，动态存储类型只在生命期内占用存储空间
        自动类型变量：最广泛使用 存储关键字为auto， 局部变量默认为auto类型。从作用域看，自动类型具有块作用域，从存储方式看，自动类型属于动态存储方式
                    若未赋值，其值不确定
        静态类型变量：关键字为static，属于静态存储方式，未赋初始值，默认为0。
                    局部静态变量：仅限于块作用域。与自动类型的不同之处，出默认值为0外，生命周期不同，静态变量局部周期为整个源程序，出了作用域仍然存在，且保存其值
                    全局变量无论是否使用static关键字，期都是静态存储变量，用static说明的仅限于它的源程序，未使用static说明的全局变量可以被其他文件使用
        寄存器类型变量：要求系统在cpu的寄存器中为其分配存储空间变量 关键字为 register 通常用于频繁使用的变量
        外部类型变量：指在函数外部说明的变量
            两种情况：同一源程序，全局变量先使用在声明，在使用之前需要声明该变量为外部类型变量
                     在一个源程序文件中，使用其他文件中定义的全局变量时，使用前需要声明该变量是外部类型变量，且该变量还不能是static修饰的全局变量



*/

//3.1 求一个角度的正弦值  有库函数sin() 但是参数是弧度
//将弧度转换为角度
double f(double a){
    double t;
    t = a*3.1415926/180;
    return t;
}

void test01(){
    double h;
    cout << "请输入角度";
    cin >> h;
    double re = sin(f(h));
    cout << h << "的正弦值为 " << re << endl;
}

//3-2 输出阶乘的表达式 和 阶乘的值
int fac(int n){
    int ret = 1;
    while(n>0){
        ret *= n;
        n--;
    }
    return ret;
}

void print(int n){
    int re = fac(n);
    cout << n;
    n--;
    while(n>0){
        cout << " * " << n;
        n--;
    }
    cout << " = " << re << endl;
}

void test02(){
    int n=10;
    print(n);
}

//3-3 求三个整数的最大公约数
//辗转相除法
int getMaxYveShu(int m ,int n){
    // if(m < n) return getMaxYveShu(n, m);
    int r;
    while( r=m%n ){
        m = n;
        n = r;
    }
    return n;    
}

void test03(){
    int a, b, c;
    cout << "请输入三个数：" ;
    cin >> a >> b >> c;
    int res = getMaxYveShu(getMaxYveShu(a,b),c);
    cout << "最大公约数为：" << res << endl;
}

//函数直接递归调用
long f(int n){
    if(n==1 || n==0) return 1;
    else return n*f(n-1);
}

//函数间接递归调用
void f2(int);
void f1(int n){                //f1(123456)  << 6  --> f2(12345) -->f1(1234) << 4  --> f2(123) --> f1(12) << 2 --> f2(1) --> f1(0)
    cout << n%10;              // f1(0) << 0 --> f2(1) << 1 --> f1(12) --> f2(123) << 3 --> f1(1234) --> f2(12345) << 5 --> f1(123456) end;
    if(n>0) f2(n/10);           // ----<< 6420135
}

void f2(int n){
    if(n>0) f1(n/10);
    cout << n%10;
}

//测试递归调用
void test04(){
    int res = f(5);
    cout << res << endl;
    f1(123456);
}

//此方法无效
void swap1(int x, int y){
    int t;
    t = x;
    x = y;
    y = t;
}

void swap2(int *x, int *y){
    int t;
    t = *x; 
    *x = *y; 
    *y = t;
}

void swap3(int &a, int &b){
    int t;
    t = a;
    a = b;
    b = t;
}

void test05(){
    int a=66, b=88;
    cout << "a=" << a << ',' << "b=" << b << '\n';    // a=66, b=88
    swap1(a,b);
    cout << "a=" << a << ',' << "b=" << b << '\n';    // a=66, b=88
    swap2(&a, &b);
    cout << "a=" << a << ',' << "b=" << b << '\n';    // a=88, b=66
    swap3(a,b);
    cout << "a=" << a << ',' << "b=" << b << '\n';    // a=66, b=88
}

//函数重载
double area(double x, double y, double z){
    double s;
    s = (x+y+z)/2;
    return sqrt(s*(s-x)*(s-y)*(s-z));
}

double area(double x, double y){
    return x*y;
}

#define PI 3.1415926

double area(double x){
    return PI*x*x;
}

void test06(){
    cout << "圆的面积为：" << area(3) << endl;
    cout << "矩形的面积为：" << area(3,4) << endl;
    cout << "三角形的面积为: " <<area(3,4,5) << endl;
}

//测试指针函数
double Add(double x, double y){
    return x+y;
}

double Sub(double x, double y){
    return x-y;
}

double Mul(double x, double y){
    return x*y;
}

double Div(double x, double y){
    return x/y;
}

void test07(){
    double(*fp)(double, double);
    double x, y;
    char op;

    cout << "请输入表达式 (操作数1 运行符 操作数2): ";
    cin >> x >> op >> y;
    switch(op){
        case '+': fp = Add; break;
        case '-': fp = Sub; break;
        case '*': fp = Mul; break;
        case '/': if(y){
                    fp = Div; }else{ cout << "不能除0" << endl; }; break;
        default: cout << "输入有误" << endl;
    }

    cout << x << " " << op << " " << y << " = " << fp(x,y) << endl;
    cout << x << " " << op << " " << y << " = " << (*fp)(x,y) << endl;
}   

//测试静态变量和局部变量
void f3(){
    auto i=0;
    static int j, k=1;
    i++;
    j++;
    k++;
    cout << i << " " << j << " " << k << endl;
}
void test08(){
    f3();
    f3();
}

//3-18
void f18(int x){
    extern int i;
    static int j=20;
    int k=30;
    i+=x;
    j+=x;
    k+=x;
    cout << i << '\t' << j << '\t' << k << endl;
}
int i=10;
void test18(){
    for(int i=1; i<3;i++){
        //int i=5;
        f18(i);
    }
    cout << i << '\t' << ::i << endl;
}

//3-19
int *f19(int x1, int &x2, int *x3, int *x4){
    x1 = x2;
    x2 = *x3;
    *x3 = *x4;
    x4 = &x1;    //将原来指向x4的指针指向了x1，对实参b没有影响
    cout << x1 << '\t' << x2 << '\t' << *x3 << '\t' << *x4 << endl;     // 2  3  4  2
    return &x2;
}

void test19(){
    int a(1), b(2), c(3), d(4);
    cout << *f19(a, b, &c, &d) << endl;                               // 3
    cout << a << '\t' << b << '\t' << c << '\t' << d << endl;         // 1  3  4  4
}

//3-20
#define FX(x,y) x/y
double fx(double x, double y){
    return x/y;
}

void test20(){
    cout << FX(4+2, 3+1) << endl;
    cout << fx(4+2, 3+1) << endl;
}

//3-21
//求最大公约数
int f211(int x, int y){
    int t=x>y?y:x;
    while(x%t || y%t)t--;
    return t;
}

//求最小公倍数
int f212(int x, int y){
    return x*y/f211(x,y);
}

void f21(int m1, int d1, int m2, int d2, int &m3, int &d3){
    d3 = f212(d1, d2);  //求分母最小公倍数
    m3 = m1*(d3/d1)+m2*(d3/d2);
    int t = f211(m3, d3);
    m3/t;
    d3/t;
}

void test21(){
    int m1(1), d1(6), m2(1), d2(3), m3, d3;
    f21(m1, d1, m2, d2, m3, d3);
    cout << m1 << '/' << d1 << '+' << m2 << '/' << d2 << '=' << m2 << '/' << d3 << endl;
}


//习题
//1.求根 牛顿迭代法
double fdao381(double x){
    return  9*x*x-4*x+5;             // 9x^2-4x+5
}

double f381(double x){
    return 3*x*x*x-2*x*x+5*x-7;
}

void qiugen(){
    double x=1;
    double x0;
   do{
        x0=x;
        x-=f381(x)/fdao381(x);
    } while(fabs(x-x0)>1e-6);
    cout << "根为：" << x;

}

float solution(float a, float b, float c, float d)
{
    float x0, f, fd, h; 
    float x = 1;

    do
    {
        x0 = x; 

        f = a * x0 * x0 * x0 + b * x0 * x0 + c * x0 + d;

        fd = 3 * a * x0 * x0 + 2 * b * x0 + c;

        h = f / fd;

        x = x0 - h; 

    } while (fabs(x-x0) >= 1e-5);

    return x;
}

void test381(){
    // float res = solution(3,-2,5,-7);
    // cout << res;
    qiugen();
}

//382孪生素数
// 判断素数
bool judgeSushu(int a){
    for(int i=2; i<=sqrt(a); i++){
        if(a%i==0)
            return false;
    }
    return true;
}

void getDoubleSuShu(){
    int pre = 1;
    for(int i=1; i<=100;i++){
        if(!judgeSushu(i)) continue;
        if(i-pre==2) {
            cout << pre << "-" << i << " | ";
        }
        pre = i;
    }
}


//383 组合数
//计算阶乘
int f383(int n){
    if(n==0 || n==1) return 1;
    else return n*f383(n-1); 
}

void qiuzuheshu(){
    int m, r;
    cout << "请输入组合数的下标和上标：" ;
    cin >> m >> r;
    double res = f383(m)/(f383(r)*f383(m-r));
    cout << "结果为：" << res;
}


//384 进制转换

string decimalToBase(int num, int base){
    char digits[] = "0123456789ABCDEF";
    if(num < base){
        return string(1, digits[num]);
    }else{
        return decimalToBase(num/base, base) +  digits[num%base];
    }
}

void test384(){
    int ten=124;
    cout << decimalToBase(ten, 16);
}


//385 求圆的面积

#define AREA(r) PI*r*r

void getArea(int r){
    cout << "面积为："  <<  PI*r*r;
}

void test385(){
    cout << "面积为： " << AREA(10);
    getArea(10);
}


int main(){
    // test01();
    // test02();
    // test03();
    // test04();
    // test05();
    // test06();
    // test07();
    // test08();
    // test18();
    // test19();
    // test20();
    // test21();
    //test381();
    // getDoubleSuShu();
    // qiuzuheshu();
    // test384();
    test385();
    return 0;
}