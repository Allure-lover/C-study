#include<iostream>
#include<cmath>
using namespace std;

#define PI 3.1415926

/*
1.标识符必须由字母,数字,下划线组成,且不能数字开头

2.常量

整型常量 十进制 D 八进制 Q 十六进制 H 八进制以0开头 十六进制以 0x 或 0X开头

实型常量 浮点小数 一般形式:整数与小数间用小数点隔开 加 f 或 F 表示 float 常量 默认 double 类型常量 也可以加 L 或者 l 表示长双精度常量
                 指数形式:由尾数和指数两部分组成,中间以 E 或者 e 隔开,指数部分只能是十进制整数 0.573E+2 表示 0.573*10^2

字符型常量 单引号括起来的一个字符,在内存用ASCLL码存储, 还有一些常见的转义字符

字符串常量 用双括号括起来的若干字符, 字符串后都会加'\0'作为结束符, 其为空字符 "A" 占两个字节, 'A'占一个字节

符号常量 true 和 false 就是两个符号常量 代表 1 0
        用#define声明符号常量   #define PI 3.1425926
        用cosnt声明符号常量     const 数据类型 常量名=常量值  或者 const 数据类型 常量名(常量值)
        const float PI = 3.1415926

3.变量
    定义: 数据类型 变量名1, 变量名2, ... ;
    变量初始化: 数据类型 变量名 = 常量值; 或者 数据类型 变量名(常量值); 或者 先声明再赋值

指针变量 数据类型 *变量名;  通过指针存取变量,也可以由指针变量取得改变量的地址进行,称间接访问方式
        二级指针 数据类型 **变量名;   char a='5'; char *r=&a; char **q=&r; 

引用变量 就是给变量起别名  格式 数据类型 &引用名 = 变量名;
         int solution;
         int &result = solution;
         result = 5;  //变量solution 和 result 具有相同的地址,是一个变量

4.基本语句
声明语句   int a=2;   void fun(int x, float y);

表达式语句  a = a*2;  a++;

空语句   ;

复合语句  {  char ch = '3';  cout << ch << '\n;  }

基本的输入输出语句

输入 cin  格式  cin >> 变量1 >> 变量2;  获取空格和回车 使用函数 cin.get(ch) 

输出 cout 格式 cout << 变量1 << 变量2;
    
5.运算符和表达式    运算符的优先级表要看一看 在 p15
算数运算符和算数表达式  优先级 1 自增(++) 自减(--)
                             2 负(-) 正(+)
                             3 * / %
                             4 加(+) 减(-)

赋值运算符与赋值表达式  格式 标量名 = 表达式
关系运算符和关系表达式  大小比较 结果为 true 或 false
逻辑运算符和逻辑表达式  逻辑 ! 逻辑或 || 逻辑与&&
其他运算符及表达式  sizeof运算符  sizeof(类型名或变量名);
                   条件运算符    三目运算符   格式  表达式1 ? 表达收2 : 表达式3;
                   地址运算符    &变量名  返回变量的地址 注意与引用的区别
                   指针运算符    *变量名  求指针变量所指内存空间的值  注意与指针变量声明的时候的 * 的区别
                   逗号运算符    顺序求值运算符  格式 表达式1, 表达式2, 表达式3  例子 d = (x=1, 3+x, ++x); //d = 2
表达式中的数据类型转换  自动类型转换 在双目运算中,类型不一致, 会进行自动类型转换 
                                   转换的基本原则 char -> short -> int -> long -> float -> double 
                                   字符型数据参与运算是用它的ASCLL码进行的,因而会自动转换成整型数据
表达式格式   根号  sqrt(表达式);
            lnx+10^-5    log(x)+1E-5
            绝对值       fabs(表达式);
            次方         pow(数, 方次);

6.基本控制结构
顺序结构
分支结构 if语句  if(表达式) 语句块;
        if-else语句 if(表达式) 语句块A; else 语句块B;
        switch语句  switch(表达式){
                        case 常量表达式1: 语句序列1;break;
                        case 常量表达式2: 语句序列2;break;
                        case 常量表达式3: 语句序列3;break;
                        default: 语句序列4;
                    }
        选择语句的嵌套
循环结构  while(条件表达式)循环体;
        do{ 循环体; }while(条件表达式);
        for语句  for(表达式1;表达式2;表达式3) 循环体;
        环语句的嵌套
转向语句 break语句 作用: 跳出 switch 跳出循环
        continue语句 作用: 结束当前循环, 开启下一次循环

*/
//书上p15 例2.1
float twoNums(){
    cout << "请输入两个数" << endl;
    int num1, num2;
    cin >> num1 >> num2;
    return (num1 + num2)/2.0;
}

void test01(){
    float res = twoNums();
    cout << "此两数之平均值为:" << res;
}

//测试运算
void test02(){
    int x = 6;
    cout << -x << '\t';
    cout << (1+'a') << '\t';
    cout << (5/3-8) << '\t';
    cout << (5%3*5/3) << '\t';
}

//测试自动类型转换
void test03(){
    char a= 'a';
    int b =a+1;
    short c = 10+a;
    double d = 3.2;

    cout << b << endl;
    cout << c << endl;
    cout << d+a << endl;
    cout << d+c << endl;
}

//2.7程序举例
//2-16 求三角形的面积

void getTriangle(){
    double a, b, c;
    cout << "请输入三角形的三条边" << endl;
    cin >> a >> b >> c;
    if(a+b > c && a+c > b && b+c > a){
        double s, area;
        s = (a+b+c)/2;
        area = sqrt(s*(s-a)*(s-b)*(s-c));
        cout << "三角形的面积为" << area << endl;
    }
}
//2-17水仙花数
void getWaterflower(){
    int sum, pre;
    for(int i=100; i<1000;i++){
        sum =0;
        pre = i;
        while(pre){
            sum += pow(pre%10,3);
            pre/=10;
        }
        if(sum == i)
            cout << i << " ";
    }
}

void getWaterFlower2(){
    int n,k,s,i;
    for(i=100;i<1000;i++){
        s=0;n=i;
        while(n){
            k=n%10;
            s+=k*k*k;
            n/=10;
        }
        if(i == s) cout << i << endl;
    }
}

//2-18Fibonacci数列
//递归法
int getFib(int n){
    if(n==1 || n==2){
        return 1;
    }
    return getFib(n-1) + getFib(n-2);
}
//书上的方法
void Fib20(){
    long int f1=1, f2 = 1, f3;
    cout << '\t' << f1 << '\t' << f2;
    for(int n=3; n<=20; n++){
        f3 = f2 + f1;
        cout << '\t' << f3;
        if(n%4==0) cout << endl;
        f1 = f2; f2 = f3;
    }
    cout << endl;
}

//2-19利用迭代法求a的平方根的近似值， 公式 xn+1 = (xn+a/xn)/2;
void getsqrtA(){
    double a;
    cout << "请输入 a: " ;
    cin >> a;
    if(a < 0 ){
        cout << "负数不能求平方根" << endl;
        return ;
    }

    double x0=1, x1 = a/2;
    while(fabs(x1-x0) >= 1e-5){
        x0 = x1;
        x1 = (x0+a/x0)/2;
    }

    cout << "a的平方根为: " << x1 << endl; 
}

//2-20 求pi
void getPi(){
    int k=1;
    double num, pi=0 , fenmu = 1;
    num = 1/fenmu;
    while(fabs(num) > 1e-6){
        pi+=num;
        fenmu+=2;
        k*=-1;                 //根据-1*（-1）=1 来对正负号进行操作 -- 很好的思想， 可以替代%2判断法
        num = (k/fenmu);
    }
    cout << "pi = " << pi*4;
}

//p36 3题
void test04(){
    char str1[] = "abc";
    cout << "sizeof(str1) = " << sizeof(str1) << endl;  //4
    char str2[] = "abc\0xy";  //7
    cout << "sizeof(str) = " << sizeof(str2) << endl;
    char str3[] = "a\134\n\\bc\t";  
    cout << "sizeof(str3) = " << sizeof(str3) << endl;
    for(int i=0; i < sizeof(str3) ; i++){
        if(str3[i] == '\n') {
            cout << "1" << "|";
            continue;
        }
        cout << str3[i] << "|";
    }
    cout << endl;

    cout << "\134" << "|";
}

//4题打印函数
void print(int x, int y, int z){
    cout << "x = " << x << "  y = " << y << "  z = " << z << endl;
}
//p36 4题
void test05(){
    int x = 2, y=4, z=7;
    z%=x;   // x=2, y=4, z=1;
    print(x, y, z);  

    z=(++x, y--);  // x=3, y=3, z = 4
    print(x,y,z);
    // x = 2, y =4, z=7;
    cout << (x+y > ++z) << "  ";  // 1    x=3, y=3 , z=5
    print(x,y,z); 

    cout << (x>(y>z?y:z)?x:(y>z?y:z)) << "  ";
    print(x,y,z);

    x=y=z;  // x=y=z=5
    print(x,y,z);

    cout << (y==z) << endl; // 1

    cout << ((x--<y) && (++x<z)) << "  "; // 0  x=4 , y=5, z =5   && 该运算符 如果前面为0 则后面部分不执行
    print(x,y,z);
    
    cout << ((x--<y) || (++x<z)) << "  "; // 1 x=3, y=5, z=5    
    print(x,y,z);

}

//p36 5
float getMax(){
    float n1, n2, n3;
    cout << "请输入三个数 : " ;
    cin >> n1 >> n2 >> n3;
    return (n1 < (n2 < n3 ? n2 : n3) ? n1 : (n2 < n3 ? n2 : n3));
}

//p36 6
void getfangchengjie(){
    cout << "请输入方程的系数：" ;
    int a,b,c;
    cin >> a >> b >> c;
    //判断的他
    int detafang = b*b - 4*a*c;
    if(detafang < 0 ){
        cout << "该方程无解" << endl;
        return;
    }else if(detafang == 0){
        cout << "该方程有唯一解 : x = " << (-b/ (2*a)) ;
    }else{
        double deta = sqrt(detafang);
        double x1 = ((-1) * b + deta)/(2*a);
        double x2 = ((-1) * b - deta)/(2*a);

        cout << "该方程有两个解 x1 = " << x1 << ", x2 = " << x2;
    }  
}

//p36 7
void getSeason(){
    cout << "请输入月份 : " ;
    int month;
    cin >> month;
    switch(month){
        case 12: case 1: case 2: cout << "这是冬季" ; break;
        case 3: case 4: case 5: cout << "这是春季" ; break;
        case 6: case 7: case 8: cout << "这是夏季" ; break;
        case 9: case 10: case 11: cout << "这是秋季" ; break;
        default: cout << "输入有误";
    }
}

//p36 8 求10个数的平均值
void getAverage(){
    int num, sum = 0;
    for(int i=0; i<10; i++){
        cout << "请输入第" << i+1 << "个数";
        cin >> num;
        sum += num;
    }
    cout << "平均值为：" << sum/10.0 << endl; 
}

//p36 9 输出最大最小的成绩
void getMaxOrMinGrade(){
    int grade;
    int min, max;
    cout << "请输入成绩" ;
    cin >> grade;
    max = min = grade;
    if(grade <0) return;
    do{
        min = grade > min ? min : grade;
        max = grade > max ? grade : max;
        cout << "请输入成绩" ;
        cin >> grade;
    }while(grade >=0);
    cout << "最高成绩为：" << max << "|| 最低成绩为：" << min;
}

//10的判断完数函数


bool isPerfectNumber(int num) {
    int sum=0;
    for(int i=1; i< num;i++){
        if(num%i==0){
            sum+=i;
        }
    }

    if(sum == num ){
        return true;
    }else{
        return false;
    }
}


//p36 10
void getwanshu(){
    for(int i=1; i< 1000; i++){
        if(isPerfectNumber(i)){
            cout << i << '\t';
        }
    }
    cout << endl;
}

int main(){
    cout << "第二章的练习代码" << endl;
    // char ch;
    // cout << "输入空格或者回车" << endl;
    // cin.get(ch);
    // cout << "1" <<ch << "2"; 
    // cout << "测试平均数" << endl;
    // test01();
    // test02();
    // test03();
    // getTriangle();
    // getWaterflower();
    // getWaterFlower2();
    // int re = getFib(20);
    // cout << re << endl;
    // Fib20();
    // getsqrtA();
    // getPi();
    // float res = tan(45*PI/180);  //tan()函数中放的是弧度， 要想输入度数 需要 度数*PI/180
    // cout << res;
    // test04();
    // test05();
    // float ret = getMax();
    // cout << "最小值为  " << ret; 
    // getfangchengjie();
    // getSeason();
    // getAverage();
    // getMaxOrMinGrade();
    getwanshu();
    return 0;
}