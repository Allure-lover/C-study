#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;

/*
继承和多态性：
    派生类定义：
        class Student : public Human{};
        派生类中对继承成员的权限：主要由基类的原有属性权限和派生方式共同决定：
            共有派生时，派生成员的访问权限和基类中的访问权限一致
            私有派生时，基类的所有成员，派生后全变成私有
            保护派生时，基类中的原有的共有的和保护的成员，派生后变成保护成员，原有的私有成员，在派生后任是私有的
        总的来说，以派生方式为界限，高于此界限的全部降低为此界限，低于此界限的保持不变
    多继承的格式： class Student : public Human, public Score, ....{};
    赋值的兼容性：具有继承关系的类中，派生类向基类的赋值关系称为赋值的兼容性
        将派生类的对象赋值给基类对象
        用派生类对象初始化基类对象的引用
        将派生类的对象赋值给基类指针，即基类指针指向派生类对象
        注意问题：
            赋值兼容性是单向的，只能派生类向基类对象
            只有在共有派生时才会生效
            基类指针指向派生类对象时，通常只能访问从基类继承来的派生成员，不能访问派生类新增的成员，除非新增成员是虚函数
    派生类的构造函数和析构函数：
        派生成员通常是在派生类构造器函数的头部通过调用基类构造函数完成，新增成员通常在函数体里完成  Student(int a, int b, int c) : Human(a,b){}
        注意事项：派生类的构造函数通常必须包括基类构造函数的调用，当基类由默认构造函数时，如果在派生类中主动调用基类构造函数时，会自动调用基类的默认构造函数，
                 当基类没有默认构造函数时，你又没有主动调用，就会报错
        多继承的派生类也类似
        派生类的对象：
            需要调用构造函数：通常先调用基类的构造函数初始化从基类继承来的派生数据成员，再执行派生类构造函数的函数体来初始化新增的成员函数
        派生类的析构函数：
            析构函数调用的顺序与构造函数相反，会先调用派生类的析构函数释放新增的数据成员，再调用基类的析构函数释放派生数据成员
    冲突：同一个类的作用域内，不允许出现重名的成员，但是派生类中，来自不同基类的派生成员的名称可以相同，因为作用域不同，这也就会引发冲突
        解决方法：使用 类:: 来区分不同作用域的同名成员
        支配规则：新增成员和派生成员出现重名，而又没进行 类名加与作用域区分 ， 这时候使用的派生类中的新增成员
        虚基类：多级继承中出现多个相同的基类被继承，比如：B继承A，C继承A，D又继承B、C 这样D中会出现两个A的基类表示，在使用之前类名加作用域符号的方法就不能解决
                此时，就要采用虚拟继承的方式来解决
            虚拟继承，将共同的基类设置成虚基类，从不同路径继承过来的虚基类的数据成员再类中只有一个拷贝，成员函数也只有一个映射
                格式：class Student : virtual public Human{};  或者  class Student : public virtual Human{};
                构造函数：除了虚基类有默认的构造函数，否则必须列出虚基类的构造函数调用
    虚函数和多态性：
        多态：不同对象接收相同命令，产生不一样的结果
        地址绑定：调用函数就是执行与函数名相应的某段存储空间的代码，函数名与首地址的匹配过程称为地址绑定
            编译多态性||静态多态性：存储空间的入口地址和函数名编译时绑定    如：函数重载，运算符重载
            动态多态性：要等到运行时根据具体对象才能确定绑定到哪个入口  通过虚函数实现
                虚函数允许在派生类中被重写，编译阶段不绑定虚函数的地址，而在程序运行时，根据具体的对象绑定所调用函数的入口地址
        虚函数实现动态多态性：
            格式： virtual void fun(){}  或者 类内声明， 类外实现  virtual void fun();  void Student::fun(){}
            注意点：虚构函数具有遗传性，构造函数不能定义为虚函数，但是析构函数可以，可以保证正确释放动态派生类对象
                    类内使用virtual声明了函数，类外不能再加 virtual 了
            要求：
                必须具有继承关系，在基类中将动态绑定行为定义为虚函数
                派生类必须重写虚函数，格式必须一样
                必须通过基类的指针或者基类对象的引用虚函数才能实现动态多态性
        纯虚函数和抽象类：
            纯虚函数：可以被派生类改写的接口，本身不能被调用，只是被声明，没有被定义，没有函数体
                格式：virtual void fun()=0;  或者 void virtual fun()=0;
            抽象类：含有纯虚函数的类是一个不完整的类，不能用这样的类创建对象，含有纯虚函数的类叫抽象类，只能做派生类的基类，不能
                定义抽象类的对象，但可以定义抽象类的指针和引用，并指向或者引用派生类对象
            抽象类的唯一用途就是为派生类提供基类，纯虚函数的作用是作为派生类中的成员函数的公共接口，实现动态多态性。在派生类中，只要重写了从抽象类
            继承到的所有纯虚函数，即定义它们的函数体，抽象类中的纯虚函数就成了普通函数，派生类就可以产生对象。重写后的纯虚函数同样可以实现动态多态性
*/
//7-2
class Base{
    int y;
protected:
    int z;
public:
    int x;
    Base(){
        x=1; y=2; z=3;
    }
    int getY(){ return y; }
    int getZ(){ return z; }
};

class Derived : public Base{
public:
    void print(){
        cout << x << '\t' << getY() << '\t'  << z << endl;
    }
};

void test72(){
    Derived d;
    d.print();
    cout << d.x << '\t' << d.getY() << '\t' << d.getZ() << endl; 
}

//7-4
class Base4{
public:
    int b;
    void show(){ cout << b << endl; }
};

class Derived4 : public Base4{
public:
    int d;
    void show() { cout << b << '\t' << d << endl; }
};

void test74(){
    Base4 t1={1}, *p;        
    Derived4 t2;
    t2.b = 5, t2.d = 10;
    t1 = t2;                        //派生类对象 t2 向基类对象t1赋值
    t1.show();
    Base4 &t3 = t2;                 //派生类对象 t2 初始化基类对象 t3 的引用
    t3.show(); 
    p = &t2;                        //基类指针p指向派生的对象 t2
    p->show();
}

//7-5
class Base5{
    int b1, b2;
public:
    Base5(int x, int y) { b1=x; b2=y; }
    void show(){ cout << "b1=" << b1 << ", b2=" << b2 << endl;}
};

class Derived5 : public Base5{
    int d1, d2;
public:
    Derived5(int a, int b, int c, int d):Base5(a,b){
        d1 = c; d2 = d;
    }
    void print(){
        cout << "派生成员：";
        show();
        cout << "新增成员：";
        cout << "d1=" << d1 << ", d2=" << d2 << endl;
    }
};

//注意事项：
// class B5 : public Base5{
// public:
//     B5(int a){      //类 "Base5" 不存在默认构造函数

//     }
// };

void test75(){
    Derived5 d(1,2,3,4);
    d.print();
}

//7-6
class A6{
public:
    A6(){ cout << "调用A构造函数" << endl; }
};

class B6 {
public:
    B6(){ cout << "调用B构造函数" << endl; }
};

class C6 : public A6, public B6{
public:
    C6(){ cout << "调用C构造函数" << endl; }
};

class D6 : public C6{
public:
    D6(){ cout << "调用D构造函数" << endl; }
};


void test76(){
    C6 c6;
    D6 d6;
}

//7-8
class A8{
protected:
    int a;
public:
    A8(int x){ a=x; cout << "调用基类A的构造函数 " << endl; }
};

class B8 : public virtual A8{
protected:
    int b;
public:
    B8(int y, int z):A8(z){
        b=y;
        cout << "调用类B的构造函数" << endl;
    }

    void print(){
        cout << a << '\t' << b << endl;
    }
};

class C8 : virtual public A8{
protected:
    int c;
public:
    C8(int x, int y):A8(y){
        c=x;
        cout << "调用类C的构造函数" << endl;
    }
};

class D8 : public C8 , public B8{
    int d;
public:
    D8(int m, int n, int k):B8(m+10, n+10), C8(m+20, n+20), A8(m+n+k){
        d=m;
        cout << "调用类D的构造函数" << endl;
    }  
    void show(){
        cout << a << "\t" << b << '\t' << c << '\t' << d << endl;
    }
};

void test78(){
    B8 t1(1,2);
    t1.print();
    D8 t2(1,2,3);
    t2.show();
}

//7-9
class A9{
public:
    void f(){ cout << "classA::f" << endl; }
};

class B9 : public A9{
public:
    void f(){ cout << "classB::f" << endl; }
};

void test79(){
    A9 t1, *p;
    B9 t2;
    t1.f();
    t2.f();
    p=&t1; p->f();
    p=&t2; p->f();  //p是A9类型的，在编译阶段被绑定到基类成员上，调用的是A9的成员函数f 若要实现多态性，需要将f说明为虚函数
}

//7-10
class Base10{
public:
    virtual void f(){ cout << "调用Base的f函数 " << endl; }
};

class Derived10 : public Base10 {
public:
    void f(){ cout << "调用Derived的f函数" << endl; }
};

void fa(Base10 *p){
    p->f();
}

void fb(Base10 &t){
    t.f();
}

void test710(){
    Base10 t1;
    Derived10 t2;
    fa(&t1);
    fa(&t2);
    fb(t1);
    fb(t2);
}

//7-11
class Graph{
public:
    virtual void area()=0;
};

class Circle : public Graph{
protected:
    double r;
public:
    Circle (double x) { r=x; }
    void area(){
        cout << "半径为：" << r;
        cout << ", 面积为：" << 3.14*r*r << endl;;
    }
};

class Rectangle : public Circle{
    double h;
public:
    Rectangle(double x, double y) : Circle(x){ h=y; }
    void area(){
        cout << "边长为：" << h  << ", " << r;
        cout << ", 面积为：" << h*r;
    }
};

void test711(){
    Graph *p;
    Circle c(10);
    p=&c; p->area();
    Rectangle r(4,5);
    p=&r; p->area();
}

//程序举例
//7-12
class A12{
protected:
    int a;
public:
    A12(int x){ a=x; cout << "调用类A的构造函数" << endl; }
    void show(){ cout << a << '\n'; }
    ~A12(){ cout << "释放成员a" << endl; }
};

class B12{
protected:
    int b;
public:
    B12(int x){ b=x; cout << "调用B的构造函数" << endl; }
    ~B12(){ cout <<"释放成员b" << endl; }
};

class C12 : public B12{
    int c;
    A12 obj;
public:
    C12(int x, int y, int z):obj(y), B12(z){
        c=x; cout << "调用类C的构造函数" << endl;
    }
    void print(){
        cout << "对象成员："; obj.show();
        cout << "派生成员：" << b << '\n';
        cout << "普通成员：" << c << '\n';
    }
    ~C12(){
        cout << "释放成员c" << endl;
    }
};

void test712(){
    C12 test(10,20,30);  //调用构造器顺序：b a c
    test.print();    //释放顺序：c a b
}

//7-13
class Base13{
public:
    Base13(char *s="string"){ cout << s << endl; }
};

class A13 : virtual public Base13{
public:
    A13(char *s1, char *s2):Base13(s1){
        cout << s2 << endl;
    }
};

class B13:public virtual Base13{
public:
    B13(char *s1, char *s2):Base13(s1){
        cout << s2 << endl;
    }
};

class AB : public A13, public B13{
public:
    AB(char *s1, char *s2, char *s3, char *s4):B13(s1, s2), A13(s3, s4){
        cout << s2 << endl;
    }
};

void test713(){
    AB test("stringA", "stringB", "stringC", "stringD");  
    /*
    结果:    string
            stringD
            stringB
            stringB
            其中Base13没有列出构造函数的调用，则会调用它的默认的构造函数，而调用A13 和 B13的构造函数虽然也会调用
            构造函数的执行顺序为：Base -> 类A -> 类B -> 类AB
            若去掉两个类上的virtual关键字，则构造函数的调用顺序为：Base -> A -> Base -> B -> AB
    */
}

//7-14
class MyclassA{
public:
    int val;
    MyclassA(int x){ val = x; }
};
class MyclassB : public MyclassA{
public:
    int val;
    MyclassB(int x):MyclassA(2*x){
        val = x;
    }
};

class MyclassC : public MyclassB{
public:
    int val;
    MyclassC(int x):MyclassB(2*x){
        val = x;
    }
};

void test714(){
    MyclassC test(3), *pc=&test;
    MyclassB *pb = &test;
    MyclassA *pa = &test;
    cout << pa->val << endl;
    cout << pb->val << endl;
    cout << pc->val << endl;
}


//7-15
class Base15{
public:
    virtual void fa(float x){ cout << "Base::fa\t" << x << endl; }
    virtual void fb(float x){ cout << "Base::fb\t" << x << endl; }
    virtual void fc(float x){ cout << "Base::fc\t" << x << endl; }
    void fd(float x){ cout << "Base::fd\t" << x << endl; }
};

class Derived15 : public Base15{
public:
    void fa(float x){ cout << "Derived::fa\t" << x << endl; }
    void fb(int x){ cout << "Derived::fb\t" << x << endl; }
    void fd(float x){ cout << "Derived::fd\t" << x << endl; }
};

void test715(){
    Derived15 d, *pd = &d;
    Base15 *pb = &d;
    pd->fa(1.23); pd->fb(1.23); pd->fc(1.23); pd->fd(1.23);
    pb->fa(1.23); pb->fb(1.23); pb->fc(1.23); pb->fd(1.23);
    /*
    执行结果：
        派生类的指针调用对象d的函数成员时，根据支配规则，调用派生类中的新增成员
        Derived::fa     1.23    直接调用派生类中的Derived::fa(float)函数
        Derived::fb     1       调用的是Derived::fb(int)函数
        Base::fc        1.23    当派生类中没有新增成员时，则调用从基类继承来的派生成员 Base::fc(float)函数
        Derived::fd     1.23    直接调用新增成员Derived::fd(float)函数
        基类指针调用派生类对象的函数成员时，根据动态绑定规则，若调用的是虚函数，则调用派生类重写的虚函数
        基类的虚函数和派生类的虚函数必须具有相同的函数原型，即 函数类型、函数名、函数的参数列表，仅函数体不同
        Derived::fa     1.23    直接调用派生类重写的函数 Derived::fa(float)
        Base::fb        1.23    Derived::fb函数与调用的函数中参数类型不同，即不是对Base::fb的重写，则相当于没有重写，调用Base::fb函数
        Base::fc        1.23    派生类中没有fc函数，即直接调用基类的Base::fc函数
        Base::fd        1.23    若调用的不是虚函数，根据支配原则，调用从基类继承而来的普通函数
    */
}

//习题
//1
class Teacher{
protected:
    char* t_name;
    double m_salary;
    int c_time;
public:
    Teacher(char* name, int c_time){
        t_name = new char[strlen(name)+1];
        strcpy(t_name, name);
        this->c_time = c_time;
    }
    void print(){
        cout << "姓名：" << t_name << "\t授课时间为：" << c_time << "\t工资为：" << m_salary << endl;
    }
};

class Professor:public Teacher{
public:
    Professor(char *name, int time):Teacher(name, time){
        m_salary = 5000+time*50;
    }
};

class Lecturer:public Teacher{
public:
    Lecturer(char *name, int time):Teacher(name, time){
        m_salary = 3000+time*20;
    }
};

void test761(){
    Professor p("张三", 20);
    Lecturer l("李四", 60);
    Teacher *t1, *t2;
    t1 = &p;
    t2 = &l;
    t1->print();
    t2->print();
    p.print();
    l.print();
}

//2
class Point{
public:
    int x, y;
public:
    Point(int a=0, int b=0):x(a), y(b){}
    void print(){
        cout << "( " << x << " , " << y << " )";
    }
};
class Distance : public Point{
    Point p;
    float distance;
public:
    Distance(int a, int b, Point &t):Point(a, b){
        p=t;
    }
    void getDis(){
        distance = sqrt((p.x-x)*(p.x-x)+(p.y-y)*(p.y-y));
    }
    void print(){
        p.print(); cout << "到" ;
        Point::print(); 
        cout << "的距离为：" << distance << endl;
    }
};

void test762(){
    Point p(1,2);
    Distance d(4, 6, p);
    d.getDis();
    d.print();
}

//3
class Square{
protected:
    int b1;
    int c;
public:
    Square(int a=0):b1(a){
    }
    virtual int get_perimeter(){
        return 4*b1;
    }
    virtual void print(){
        cout << "边长为" << b1 << "的正方形的周长为：" << get_perimeter() << endl;
    }
};

class Rectangular:public Square{
    int b2;
public:
    Rectangular(int a, int b):Square(a){
        b2 = b;
    }
    int get_perimeter(){
        return 2*(b1+b2);
    }

    void print(){
        cout << "两边长度分别为" << b1 << "," << b2 << "的矩形的周长为：" << get_perimeter() << endl;
    }
};

void test763(){
    Rectangular r(3,4);
    Square *s=&r;
    int c = s->get_perimeter();
    cout << "c=" << c << endl;
    s->print();
}

//4
class Auto{
protected:
    int num; //牌号
    int count; //轮数
public:
    Auto(int num, int count){
        this->num = num;
        this->count = count;
    }
    virtual void print()=0;
};

class Car : public Auto{
    int r_num; //人数
public:
    Car(int num, int count, int a):Auto(num, count){
        r_num = a;
    }
    void print(){
        cout << "牌号：" << num << "\t轮子数：" << count << "\t核载人数：" << r_num << endl; 
    }
};

class Truck : public Auto{
    int dun; //吨位
public: 
    Truck(int a, int b, int t):Auto(a, b){
        dun = t;
    }
    void print(){
        cout << "牌号：" << num << "\t轮子数：" << count << "\t核载吨位：" << dun << endl; 
    }
};

void fun(Auto &a){
    a.print();
}

void test764(){
    Car car(1,2,3);
    Truck truck(3,4,5);
    fun(car);
    fun(truck);
}

int main(){
    // test72();
    // test74();
    // test75();
    // test76();
    // test78();
    // test79();
    // test710();
    // test711();
    // test712();
    // test713();
    // test714();
    // test715();
    // test761();
    //test762();
    // test763();
    test764();
    system("pause");
    return 0;
}