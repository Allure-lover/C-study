#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;

/*
友元与运算符重载
    友元函数和友元类：
        采用类的机制实现了数据的封装和隐藏，而通过友元就可以实现越权访问这些数据
        友元函数：不是类的成员函数但是可以直接访问类的成员，包括私有成员
            格式：friend void fun(){}
            也可以在类体内进行原型说明，在类外定义，但是类外不能加friend关键字，同时函数名前也不能加类名和作用域运算符
            格式：friend void fun();     void fun(){}
            友元函数不是类的成员，类的访问权限对友元函数不起作用
            友元是外部函数，不能使用this指针
            友元函数不能通过类对象调用
            友元函数虽然可提高程序的运行效率，但是破坏了类的封装性，应该谨慎使用
            友元关系不具备继承性
        友元类：将一个类说明为另一个类的友元，则此类的所有成员函数都是另一个类的友元函数
    运算符重载：
        若要使对象可以参与运算符的运算就必须重新定义这些运算符
        格式：使用类成员函数重载时： 函数类型 operator 运算符(形参列表) { 函数体 }
              使用类的友元函数重载时：friend 函数类型 operator 运算符(形参列表) { 函数体 }
        不能重写的运算符：成员运算符(.)、指针运算符(*)、作用域运算符(::)、条件运算符(? : )、求字节长度的运算符sizeof()
        只能成员函数重载的运算符：赋值运算符(=)、数组下标运算符([])、函数调用运算符(())、和指针访问成员运算符(->)
        只能友元函数重载的运算符：插入运算符(<<)、提取运算符(>>)
        运算符重载不能改变运算符的优先级，操作数的个数和结合性等基本特征
        重载运算符只是重新定义已有的运算符的操作规则，不能创建新的运算符
    单目运算符的重载： 自增++、自减--、负号-、逻辑非！
        重载函数通常是无参函数，通过this指针完成对当前对象的运算。自增和自减运算有前置和后置之分，为了区别，在重载函数定义时建一个标志参数int
        成员函数重载前置自增运算格式：  函数类型 operator++(){ 函数体 }
        成员函数后置自增运算符的格式：  函数类型 operator++(int){ 函数体 }
        友元函数是外部函数，没有this指针，所以需要一个对象作为形参，传递操作对象，为了能将结果带回主函数，需要引用传递
        在这个友元函数内部，我们首先创建了一个临时变量 temp，并将当前对象的值复制给它。然后，我们对当前对象的值进行自增操作。最后，我们返回了保存
        的临时变量 temp，而不是当前对象。
        这样做的原因是，自增运算符 ++ 有两种用法：前缀和后缀。前缀自增返回自增后的值，而后缀自增返回自增前的值。
        重载强制类型转换运算符可以将一个对象转换为其他类型的数据，转换函数只能用成员函数重载，不能指定函数的返回值类型，转换函数没有参数
            格式： operator 类型名(){ 函数体 }   类型名是转换后的数据类型，关键字和operator与类型名一起构成函数名
    双目运算符重载：
        用成员函数重载双目运算符时，运算符的第一个操作数一定是对象，这是因为要将其作为当前对象来调用重载函数。第二个操作数作为哦重载函数的实参
        ，可以是对象、对象的引用，也可以是其他类型的数据。
        友元函数重载双目运算符：重载函数有两个参数，两个操作数都作为函数的实参，但至少一个操作时时对象，或者对象的引用
    重载运算符的适用场景：C++编译器会为每一个类提供默认的赋值运算符重载函数，通常情况，相同类型之间的对象可以会想赋值。但是当对象使用动态内存时，
        即数据成员是指针成员，并指向new运算符申请的空间，对象就不能直接赋值。此时赋值就会导致不同对象的成员是用来相同的内存空间，当系统策撤销对象
        并释放内存空间的时候会出现错误。所以，当类的对象是用了动态内存，应重载赋值运算符，赋值运算符必须使用成员函数重载。
        重载参数中对象参数推荐使用引用，否则就会导致连等这种操作报错
        
*/

//8-1
const double PI = 3.1415;
class A1{
    float r, h;
    friend float v1(A1 &a);   //类外定义友元函数
public:
    A1(float a, float b){ r=a; h=b; }
    float v2() { return PI*r*r*h; }
    float getr(){ return r; }
    float geth(){ return h; }
    friend void show(A1 *p){   //类内定义友元函数
        cout << PI*(p->r)*(p->r)*(p->h);
    }
};

float v1(A1 &a){ return PI*a.r*a.r*a.h; }

float v3(A1 b){ return PI*b.getr()*b.getr()*b.geth(); }

void test81(){
    A1 a1(25,40);
    cout << v1(a1) << endl;
    cout << a1.v2() << endl;
    cout << v3(a1) << endl;
    show(&a1);
    cout << endl;
}

//8-2
class C2;
class B2{
public:
    void sub(C2 &t);
    void show(C2 t);
};

class C2{
    int a, b;
public:
    C2(int x, int y){ a=x; b=y; }
    friend class B2;
};

void B2::sub(C2 &t){
    t.a--;
    t.b--;
}

void B2::show(C2 t){ cout << t.a << '\t' << t.b << endl; }

void test82(){
    B2 b1;
    C2 c1(30,40);
    b1.show(c1);
    b1.sub(c1);
    b1.show(c1);
}


//8-3加法运算符的重载
class D3{
    int a,b,c;
public:
    D3(int x=0, int y=0, int z=0){
        a=x; b=y; c=z;
    }
    // D3 operator+(D3 t){
    //     D3 temp;
    //     temp.a = t.a+a;
    //     temp.b = t.b+b;
    //     temp.c = t.c+c;
    //     return temp;
    // }
    friend D3 operator+(const D3 &t1, const D3 &t2){
        D3 temp;
        temp.a = t1.a + t2.a;
        temp.b = t1.b + t2.b;
        temp.c = t1.c + t2.c;
        return temp;
    }
    void print(){ cout << a << '\t' << b << "\t" << c << endl; }
};

void test83(){
    D3 a1(1,2,3), a2(4,5,6), a3;
    a3=a1+a2;
    a3.print();
}


//8-4自增运算符的重载
class E{
    int m,n;
public:
    E(int x=0, int y=0){
        m=x; n=y;
    }
    E operator++(){ 
        ++m; ++n; 
        return *this;
    }

    E operator++(int);
    void print(){
        cout << "m=" << m << ", n=" << n << endl;
    }
};

E E::operator++(int ){
    E t = *this;
    ++m; ++n;
    return t;
}

void test84(){
    E a1(1,2), a2(10,20), a3, a4;
    a3=++a1;
    a4=a2++;
    cout << "a1:\t"; a1.print(); //2,3
    cout << "a3:\t"; a3.print(); //2,3
    cout << "a2:\t"; a2.print(); //11,21
    cout << "a4:\t"; a4.print(); //10,20
}

//8-5友元函数实现自减的重载
class F{
    int m,n;
public:
    F(int x=0, int y=0){
        m=x; n=y;
    }
    friend F operator--(F &f){
        --f.m; --f.n;
        return f;
    }
    friend F operator--(F &f, int);

    void print(){
        cout << "m=" << m << "\tn=" << n << endl; 
    }
};

F operator--(F &f, int){
    F temp =f;
    --f.m; --f.n;
    return temp;
}

void test85(){
    F a1(1,2), a2(10,20), a3, a4;
    a3=--a1;
    a4=a2--;
    cout << "a1:\t"; a1.print();
    cout << "a3:\t"; a3.print();
    cout << "a2:\t"; a2.print();
    cout << "a4:\t"; a4.print();
}

//8-6
class G{
    int a;
public:
    G(int x=0){ a=x; }
    int geta(){ return a; }
    operator char*(){
        int n=1, t=a;
        while(t=t/10) n++;
        char *s=new char[n+1];
        for(int i=n-1,t=a; i>=0; i--){
            s[i] = t%10+'0';
            t = t/10;
        }
        s[n]='\0';
        return s;
    }
};

void test86(){
    G a1(12345);
    cout << "a1=" << a1.geta() << endl;
    char *str;
    str = a1;
    cout << "str=" << str << endl;
    delete []str; 
}

//8-7
class A7{
    int s[2];
public:
    A7(int x=0, int y=0){ s[0]=x; s[1]=y; }
    void operator+=(A7 t){
        s[0]+=t.s[0];
        s[1]+=t.s[1];
    }
    A7 operator-(int t){
        A7 temp = *this;
        temp.s[0]-=t;
        temp.s[1]-=t;
        return temp;
    }

    void print() { cout << s[0] << '\t' << s[1] << '\t' << endl; }
};

void test87(){
    A7 a1(1,2), a2(3,4), a(10, 20);
    a1+=a;
    a2=a2-3;
    a1.print();
    a2.print();
    a.print();
}

//8-8
class A8{
    char *s;
public:
    A8(){ s=0; }
    A8(char *p) {
        s = new char[strlen(p)+1];
        strcpy(s, p);
    }
    char *gets(){ return s; }
    ~A8(){ if(s) delete []s;}
    A8 &operator=(A8 &t){
        if(s) delete []s;              //当前对象的s非空
        if(t.s){                       //对s进行重新赋值
            s=new char[strlen(t.s)+1]; 
            strcpy(s, t.s);
        }else{
            s=0;
        }
        return *this;
    }
};

void test88(){
    A8 a1, a2("String1"), a3("String2");
    a1=a2=a3;          //重载=运算符时应该使用引用参数，否则这种连等就会导致不同对象使用相同的动态内存而引起错误
    cout << a1.gets() << endl;
    cout << a2.gets() << endl;
}

//8-9  重写+ 、+= 运算符
class A9{
    int a,b,c;
public:
    A9(int x=0, int y=0, int z=0){ a=x; b=y; c=z; }
    friend void operator+=(A9 &t1, A9 t2);
    friend A9 operator+(A9 t1, A9 t2);
    void print(){
        cout << a << '\t' << b << '\t' << c << endl;
    }
};

void operator+=(A9 &t1, A9 t2){
    t1.a+=t2.a;
    t1.b+=t2.b;
    t1.c+=t2.c;
}

A9 operator+(A9 t1, A9 t2){
    A9 t;
    t.a=t1.a+t2.a;
    t.b=t1.b+t2.b;
    t.c=t1.c+t2.c;
    return t;
}

void test89(){
    A9 a1, a2(1,2,3), a3;
    a1.print();
    a3=a1+a2;
    a3.print();
    a3+=a2;
    a3.print();
}

//程序举例
class String{
    char *p;
public:
    String(char *s){
        if(s){
            p=new char[strlen(s)+1];
            strcpy(p, s);
        }
        else p=0;
    }

    ~String(){
        if(p){
            delete []p;
        }
    }
    String &operator-=(char c);        //为了实现连续的赋值，需要将返回值设置成对象的引用
    void show(){ cout << p << endl; }
};
String &String::operator-=(char c){
    char *p1=p;
    while(*p1){                 //*p1!=0  逐一遍历p1
        if(*p1==c){             //if *p1==c 进入
            for(char *q=p1; *q; q++) *q=*(q+1);     //定义一个q指向p1，如果*q!=0 循环，值前移
        }else p1++;
    }
    return *this;
}

void test810(){
    String s1("Microsoft Visual C++");
    s1.show();
    char c1 = 'i';
    s1-=c1;
    s1.show();
}

//8-11 重写下标运算符 只能使用成员函数来实现
class Array{
    float *p;
    int len;
public:
    Array(int n=0){
        if(n>0){
            p=new float[n];
            len=n;
        }else{
            p=0;
            len=0;
        }
    }
    ~Array(){
        if(p){ delete []p; }
    }
    float &operator[](int index);
};

float &Array::operator[](int index){
    if(index <0 || index >=len){
        cout << "\nError:数组下标：" << index << "越界" << endl;
        exit(1);
    }
    return p[index];
}

void test811(){
    Array s1(10), s2(3);
    int i;
    for(int i=0; i<10; i++){  s1[i]=i;  }
    for(int i=0; i<10;i++) cout << s1[i] << '\t';
    cout << endl;
    cout << s1[10] << endl;    //越界了
    s2[2]=26;
    cout << "s2[2]=" << s2[2] << endl;
}

//习题
//1求正方形的面积
class Sample{
    int n;
public:
    friend int get_area(Sample &s);
    Sample(int x){ n=x; }
    void display(){
        cout << "边长为" << n << "的正方形面积为：" << get_area(*this) << endl;
    }
};

int get_area(Sample &s){
    return s.n*s.n;
}

void test861(){
    Sample s1(4);
    s1.display();
}

//2
class Complex{
    int a,b;
public:
    Complex(int x=0, int y=0){
        a=x; b=y;
    }
    //+
    Complex operator+(Complex c){
        Complex r;
        r.a = a+c.a;
        r.b = b+c.b;
        return r;
    }
    // friend Complex operator+(Complex &c1, Complex c2);
    // / *
    Complex operator*(Complex c){
        Complex r;
        r.a = a*c.a + b*c.b;
        r.b = a*c.b + b*c.a;
        return r;
    }
    // friend Complex operator*(Complex &c1, Complex c2);
    //+=
    void operator+=(Complex c){
        a+=c.a;
        b+=c.b;
    }
    // /  !=
    int operator!=(Complex c){
        if(a==c.a && b==c.b){
            return 0;
        }
        return 1;
    }
    void print(){
        cout << "( " << a << " + " << b << "i " << ")";
    }
};

// Complex operator+(Complex &c1, Complex c2){
//     Complex r;
//     r.a = c1.a + c2.a;
//     r.b = c1.b + c2.b;
//     return r;
// }

// Complex operator*(Complex &c1, Complex c2){
//     Complex r;
//     r.a = c1.a*c2.a+c1.b*c2.b;
//     r.b = c1.a*c2.b+c1.b*c2.a;
//     return r;
// }

void test862(){
    Complex c1(1,2), c2(2,3), c3;
    c3 = c1+c2;
    c1.print(); cout << "+"; c2.print(); cout << "=" ; c3.print(); cout << endl;
    c3 = c1*c2;
    c1.print(); cout << "*"; c2.print(); cout << "=" ; c3.print(); cout << endl;
    c1+=c2;
    c1.print();
    if(c1 != c2){
        cout << "c1 != c2" << endl;
    }else {
        cout << "c1 == c2" << endl;
    }
    cout << endl;

}

//3
class Array3 {
    int* p;
    int len;

public:
    Array3(int n = 0) {
        if (n > 0) {
            p = new int[n];
            len = n;
        } else {
            p = nullptr;
            len = 0;
        }
    }

    // 添加拷贝构造函数
    Array3(const Array3& other) {
        len = other.len;
        if (len > 0) {
            p = new int[len];
            for (int i = 0; i < len; ++i) {
                p[i] = other.p[i];
            }
        } else {
            p = nullptr;
        }
    }

    // 添加赋值运算符重载
    Array3& operator=(const Array3& other) {
        if (this == &other) return *this; // 处理自我赋值
        delete[] p; // 释放原有资源
        len = other.len;
        if (len > 0) {
            p = new int[len];
            for (int i = 0; i < len; ++i) {
                p[i] = other.p[i];
            }
        } else {
            p = nullptr;
        }
        return *this;
    }

    ~Array3() {
        delete[] p; // 释放内存
    }

    int& operator[](int);

    Array3& operator++() {          //成员函数前置++
        for (int i = 0; i < len; i++) {
            p[i] += 1;
        }
        return *this;
    }

    Array3 operator++(int){        //成员函数后置++
        Array3 temp(*this);
        for(int i=0; i<len; i++){
            temp.p[i] +=1;
        }
        return temp;
    }

    friend Array3& operator--(Array3 &a);        //友函数实现前置--
    friend Array3 operator--(Array3&, int);      //友函数实现后置--

};

Array3& operator--(Array3 &a){
    for(int i=0; i<a.len; i++){
        a.p[i]-=1;
    }
    return a;
}

Array3 operator--(Array3 &a, int){
    Array3 t(a);
    for(int i=0; i<10; i++){
        a.p[i]-=1;
    }
    return t;
}

int& Array3::operator[](int index) {
    if (index < 0 || index >= len) {
        cout << "越界了" << endl;
        // 用异常来处理越界情况
        throw out_of_range("Index out of range");
    } else {
        return p[index];
    }
}

void test863() {
    Array3 a1(10);
    for (int i = 0; i < 10; i++) {
        a1[i] = i;
    }

    cout << "前a1:\t";
    for (int i = 0; i < 10; i++) {
        cout << a1[i] << '\t';
    }
    cout << endl << "后a1:\t";
    ++a1;
    for (int i = 0; i < 10; i++) {
        cout << a1[i] << '\t';
    }
    
    cout << endl << "a2:\t";
    Array3 a2 = ++a1;
    for(int i=0; i<10; i++){
        cout << a2[i] << '\t';
    }

    cout << endl << "a1:\t";

    Array3 a3=a1++;

    for(int i=0; i<10; i++){
        cout << a1[i] << '\t';
    }
    cout << endl << "a3:\t";
    for(int i=0; i<10; i++){
        cout << a3[i] << '\t';
    }
    cout << endl << "--a1:\t";
    --a1;
    for(int i=0; i< 10; i++){
        cout << a1[i] << '\t';
    } 
    cout << endl << "a4:\t";
    Array3 a4 = a1--;
    for(int i=0; i<10; i++){
        cout << a4[i] << '\t';
    } 
    cout << endl << "a1:\t";
    for(int i=0; i<10; i++){
        cout << a1[i] << '\t';
    }
    cout << endl;
}

//4
class Array4{
    int n;
    int *p;
public:
    Array4(int x=0){
        if(x>0){
            p=new int[x];
            n=x;
        }else{
            p=nullptr;
            n=0;
        }
    }
    Array4(const Array4& other) : n(other.n) {
        if (n > 0) {
            p = new int[n];
            for (int i = 0; i < n; i++) {
                p[i] = other.p[i];
            }
        } else {
            p = nullptr;
        }
    }

    ~Array4(){
        if(p) delete[] p;
    }

    int power(int base, int exp) {
        int result = 1;
        for (int i = 0; i < exp; i++) {
            result *= base;
        }
        return result;
    }

    Array4 operator^(Array4 a){
        Array4 temp(n);
        for(int i=0 ;i<n;i++){
            temp.p[i] = power(p[i], a.p[i]);
        }
        return temp;
    }

    int& operator[](int index){
        if(index <0 || index >=n){
            cout << "越界了" << endl;
            throw out_of_range("Index out of range");
        }else{
            return p[index];
        }
    }

};

void test864(){
    Array4 a1(3), a2(3);
    for(int i=0; i<3;i++){
        a1[i] = 2; a2[i] = 3;
    }

     try {
        Array4 a3 = a1^a2;
        for (int i = 0; i < 3; i++) {
            cout << a3[i] << '\t';
        }
        cout << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}


int main(){
    // test81();
    // test82();
    // test83();
    // test84();
    //test85();
    // test86();
    // test87();
    // test88();
    // test89();
    // test810();
    // test811();
    // test861();
    // test862();
    // test863();
    test864();
    system("pause");
    return 0;
}