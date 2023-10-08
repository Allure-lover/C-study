#include<iostream>
#include<cstring>
#include<cmath>
#include<time.h>
using namespace std;

/*
面向对象的程序设计：
    类：类成员默认访问特性是私有的 
    格式：class 类名{
            pulic: 
                公有成员列表；
            protected：
                保护成员列表；
            private:
                私有成员列表；
        };
    对象：类是抽象而对象是具体
    构造函数和析构函数：
        构造函数：系统会有默认构造函数，如果你定义了构造函数，则系统不会生成默认函数无参构造函数不能这样使用  H h1(); 系统会把它和函数弄混
        析构函数：执行撤销对象的一些清理工作，和构造函数类似，如果没有定义，系统会自动生成一个，但是区别是不能重载
        拷贝构造函数：用一个已经存在的对象初始化新建的对象，系统会自动生成一个默认的拷贝构造函数，操作是依次将值赋值进去，但是有时会有bug，需要自己定义
        构造函数和成员列表初始化：注意初始化的顺序 先要完成参数列表的成员初始化，再执行函数体中的语句初始化
    this指针：this指针指向当前对象，各个非静态的成员函数中隐含的被施加了一个指针常量this
    静态成员：静态数据成员：为所有的类对象所共享
             静态成员函数：静态成员函数内部没有系统提供给的this指针，因此静态成员函数只能访问静态成员
注意： 
    定义指针时不会生成该类的对象，但是定义数组时会生成对象
    引用成员和常量成员必须在成员初始化列表中进行初始化，因为它们不能在构造函数体内被赋值。
*/



//6-1
class REC{
    int a,b;
public:
    REC(int t1, int t2){
        a=t1; 
        b=t2;
    }
    int circum(){
        return 2*(a+b);
    }

    int area(){
        return a*b;
    }
};

void test61(){
    int a, b;
    cout << "请输入矩形的边长：";
    cin >> a >> b;
    REC r1(a, b);
    cout << "边长为：" << r1.circum() << endl;
    cout << "面积为：" << r1.area() << endl;
}

//6-5
class J{
    int a,b;
public:
    J(int t1=0, int t2=0){
        a = t1;
        b = t2;
    }

    void print(){
        cout << a << '\t' << b << endl;
    }
};

void test65(){
    J j1, j2(1,2);
    j1.print();
    j2.print();
}

//6-6
class G{
    char *s;
public:
    G(char *p){
        int n = strlen(p);
        s = new char[n+1];
        strcpy(s, p);
        cout << "调用构造函数" << endl;
    }

    ~G(){
        delete[] s;
        cout << "调用了析构函数" << endl;
    }
    void print(){
        cout << s << endl;
    }
};

void test66(){
    G g1("Visual C++ program.");
    g1.print();
}

//6-7
class K{
    char *s;
public:
    K(char *p){
        int n =strlen(p);
        s = new char[n+1];
        strcpy(s,p);
    }
    K(K &t){
        int n = strlen(t.s);
        s = new char[n+1];
        strcpy(s, t.s);
    }

    ~K(){
        delete [] s;
    }
    void print(){
        cout << s << endl;
    }
};

void test67(){
    K k1("Visual C++ Program.");
    k1.print();
    K k2(k1);
    k2.print();
}

//6-8
class M{
    int a;
public:
    M(int t){ a = t;}
    int geta(){ return a;}
};

class N{
    int a,b;
    const int c;
    int &d;
    M m1;
public:
    N(int t):m1(++t), d(b), c(++t), a(++t){
        b=2*t;
    }
    void print(){
        cout << "当前对象的数据成员：" << endl;
        cout << "m1.a = " << m1.geta() << endl;
        cout << "a = " << a << endl;
        cout << "b = " << b << endl;
        cout << "c = " << c << endl;
        cout << "d = " << d << endl; 
    }
};

void test68(){
    N n1(1);
    n1.print();
}

class Q{
    int a,b;
public:
    Q(int t1, int t2){
        a = t1;
        b = t2;
    }
    void print(){
        cout << a << '\t' << b << endl;
    }
    Q add(int a, Q &t){
        this->a = this->a + a + t.a;
        b = b + a + t.b;
        return *this;
    }
};

void test69(){
    Q q1(1,2), q2(0,0);
    q1.print();
    q2.print();
    q1 = q2.add(5, q1);

    q1.print();
    q2.print();
}

//6-10
class R{
    int a;
    static int b, c;
public:
    R(int t) { a = t;}
    void add(){
        a++; b++; c++;
    }
    void print(){
        cout << a << '\t' << b << '\t' << R::c << endl;
    }
};

int R::b, R::c=5;

void test610(){
    R r1(0), r2(3);
    r1.print();
    r2.print();
    r1.add();
    r1.print();
    r2.print();

}




//6-11
class S{
    int a;
    static int b;
public:
    S(int t) { a=t; }
    static void add(){
        // a++;    //报错，只能使用静态成员
        b++;
    }
    static void add2(S t){
        t.a++;
        b++;
    }
    void print(){
        cout << a << '\t' << b << endl;
    }
};

int S::b=5;
void test611(){
    S::add();
    S s1(0);
    s1.print();
    s1.add2(s1);
    s1.print();
}

//程序举例
//6-12  定义直角三角形类，计算斜边和面积
class Triangle{
    float a,b;
public:
    Triangle(float x=0, float y=0){
        a = x;
        b = y;
    }
    float f1(){
        return sqrt(a*a + b*b);
    }
    float f2(){
        return a*b/2;
    }
};

void test612(){
    float s,t;
    cout << "输入直角三角形的两条直角边：";
    cin >> s  >> t;
    Triangle aa(s,t);
    cout << "直角三角形斜边长度为：" << aa.f1() << '\n';
    cout << "直角三角形的面积为：" << aa.f2() << endl;
}



//6-13 数组类 实现二维数组各行元素排序，各列元素排序， 全体元素按内存顺序排序

class Array{
    int a[4][5];
public:
    Array(int t[][5], int n){
        for(int i=0; i<n; i++){
            for(int j=0; j<5; j++){
                a[i][j]=t[i][j];
            }
        }
    }
    void print(){
        for(int i=0; i<4; i++){
            for(int j=0; j<5; j++){
                cout << a[i][j] << '\t';
            }
            cout << endl;
        }
    }

    void fun1();   //行排序
    void fun2();   //列排序
    void fun3();   //按内存排序
};

void Array::fun1(){
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            int t=j;
            for(int k=j+1; k<5; k++){
                if(a[i][j] > a[i][k]){
                    t = k;
                }
            }
            if(j != t){
                int temp = a[i][j];
                a[i][j] = a[i][t];
                a[i][t] = temp;
            }
            
        }
    }
}

void Array::fun2(){
    for(int i=0; i<5; i++){
        for(int j=0; j<3; j++){
            int t = j;
            for(int k=j+1; k<4; k++){
                if(a[j][i] > a[k][i]){
                    t = k;
                }
            }
            if(t != j){
                int temp = a[j][i];
                a[j][i] = a[t][i];
                a[t][i] = temp;
            }
            
        }
    }
}

void Array::fun3(){     //这就是按内存顺序排序， 好豆芽
    int *p=&a[0][0];
    int n=4*5;
    for(int i=0; i< n-1; i++){
        for(int j=i+1; j<n; j++){
            if(*(p+i)>*(p+j)){
                int t = *(p+i);
                *(p+i) = *(p+j);
                *(p+j) = t;
            }
        }
    }
}

void test613(){
    int data[4][5];
    for(int i=0; i<4; i++){
        for(int j=0; j<5; j++){
            data[i][j] = rand()%100;
        }
    }

    Array a1(data,4), a2(data, 4);
    cout << "原数组：\n";
    a1.print();
    a1.fun1();
    cout << "\n行排序: \n";
    a1.print();
    a1 = a2;
    cout << "\n列排序: \n";
    a1.fun2();
    a1.print();
    cout << "\n内存顺序排序: \n";
    a1.fun3();
    a1.print();
}

//6-14定义一个类，该类可以将一组数据按给定的行列表示成一个二维数组
class Array614{
    int *p;
    int m, n;
public:
    Array614(int *t, int a, int b):m(a), n(b){
        p = new int[m*n];
        for(int i=0; i<m*n; i++){  //初始化指针成员
            *(p+i) = *(t+i);        //操作依据：数组是一片连续的内存
        }
    }
    ~Array614(){ delete p; }
    int get(int i, int j){   //取小标为[i][j]的元素
        return *(p+i*n+j);
    }

    void print(){
        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++){
                cout << get(i, j) << '\t';
            }
            cout << endl;
        }
    }

};
void test614(){
    int *data, i0, j0;
    cout << "请输入二维数组的行数和列数: ";
    cin >> i0 >> j0;
    data = new int[i0*j0];
    for(int i=0; i<i0; i++){
        for(int j=0; j<j0; j++){
            *(data+i*j0+j) = rand()%100;
        }
    }
    Array614 a1(data, i0, j0);
    a1.print();
    delete [] data;
}

//6-15 定义一个学生类，将一组学生的数据存入对象数组，并根据学生成绩信息排序，要求每一位学生的信息中均含有该班成绩的总分和屏均分
//这题想要实现每个对象都有总分和平均成绩，而且这两个数据都是一样的，有两种思想，就是每个对象都有一个独立的指两个属性，每次新增对
//象都更新这些对象独立的这些属性，这是相当麻烦的
//但是，我们可能到这些成员的数据都是一样的，我们就可以想到静态数据成员，它是一个类所有的对象所共享的，这是很方便，
//只需要在新增对象是更新这个静态数据成员变量即可

class STU{
    float score;
    char name[15];
    static int count;      //这里的count是计数学生的数量用的 分别在构造函数调用的时候+1 在调用析构函数的时候-1，这样可以及时的记录学生的数量
    static float sum, average;
public:
    STU(){ count++; }
    ~STU() { count--; }
    void input(){
        cout << "请输入学生的姓名和成绩：" ;
        cin >> name >> score;
        sum += score;
        average = sum/count;
    }

    void print(){
        cout << name << ":" << score << endl;
    }

    static int get_count(){ return count; }
    static float get_sum() { return sum; }
    static float get_average(){ return average; }
    float get_score() { return score; }
};

//系统会自动初始化
int STU::count;
float STU::sum, STU::average;

void input(STU t[]){
    for(int i=0; i<STU::get_count(); i++){
        t[i].input();
    }
}

void sort(STU *p[]){
    for(int i=0; i<STU::get_count()-1; i++){
        for(int j=0; j<STU::get_count(); j++){
            if(p[i]->get_score() <p[j]->get_score()){
                STU *t = p[i];
                p[i] = p[j];
                p[j] = t;
            }
        }
    }
}

void print(STU *t[]){
    for(int i=0; i<STU::get_count(); i++){
        t[i]->print();
    }
    cout << "\n学生数: " << STU::get_count() << endl;
    cout << "总 分: " << STU::get_sum() << endl;
    cout << "平均分: " << STU::get_average() << endl;
}

void test615(){
    STU *p[5], s[5];
    input(s);
    for(int i=0; i<STU::get_count(); i++){
        p[i] = s+i;
    }
    sort(p);
    print(p);
}

//练习
/*
1.问题：为什么实现拷贝函数的参数应该使用引用类型？
如果拷贝构造函数的参数是按值传递的，也就是说会创建参数 other 的一个拷贝。这意味着在拷贝构造函数中，会有一个额外的拷贝操作。当类的成员
变量较多或包含复杂的数据结构时，这样的额外拷贝可能会导致性能问题。
拷贝构造函数可能会出现以下问题：
1）.无限递归调用：如果拷贝构造函数的参数是按值传递的，而不是按引用传递，那么在调用拷贝构造函数时，会创建一个新的对象，这将导致无限递归调用。
2）.浅拷贝问题：如果类中包含动态分配的资源（如堆内存），并且拷贝构造函数未正确实现，可能会导致多个对象共享同一块内存，这称为浅拷贝问题。
3）.未正确初始化成员变量：如果拷贝构造函数没有正确地初始化所有成员变量，可能会导致对象在复制后处于一个不稳定的状态。
将拷贝构造函数的参数定义为引用类型可以提高效率，避免不必要的拷贝操作，并且符合了 C++ 中传递对象的常用做法。

2. 在类的成员函数中，如何返回调用该函数的当前对象
return *this;

3 在C++中，对于以下定义：

    A a1, a2[3], *pa, *pb[3];

会调用A类的构造函数几次取决于A类的默认构造函数是否存在以及是否被调用。

具体情况如下：

1. A a1;：会调用A类的构造函数一次，创建一个名为a1的对象。
2. A a2[3];：会调用A类的构造函数三次，分别创建一个数组a2[0]、a2[1]和a2[2]。
3. A* pa;：这里只是声明了一个指针pa，没有调用A类的构造函数。
4. A* pb[3];：这里只是声明了一个指针数组pb，没有调用A类的构造函数。

总结起来，对于给定的定义，会调用A类的构造函数四次。需要注意的是，只有在对象被创建时才会调用构造函数，声明一个指针并不会触发构造函数的调用。

4. 当类中含有引用成员，常量成员，对象成员，其构造函数是何形式
一个类中包含引用成员、常量成员和对象成员时，它的构造函数应该使用成员初始化列表来进行初始化。
成员初始化列表允许你在构造函数体之前对成员进行初始化。
请注意，引用成员和常量成员必须在成员初始化列表中进行初始化，因为它们不能在构造函数体内被赋值

*/
//5
class Point{
    int x, y;
public:
    Point(int a, int b):x(a), y(b){}
    int get_x(){ return x; }
    int get_y(){ return y; }
    void print(){
        cout << "顶点坐标为：" << '(' << get_x() << ',' << get_y() << ')' << endl;
    }
};

class Rectangle{
    Point *p1;
    Point *p2;
    Point *p3;
    Point *p4;
    int area;
public:
    Rectangle(Point *a, Point *b, Point *c, Point *d){
        p1 = a;
        p2 = b;
        p3 = c;
        p4 = d;
    }

    void print(){
        int a = p1->get_x() != p2->get_x() ? abs(p1->get_x() - p2->get_x()) : abs(p1->get_x() - p3->get_x());
        int b = p1->get_y() != p2->get_y() ? abs(p1->get_y() - p2->get_y()) : abs(p1->get_y() - p3->get_x());
        area = a*b;
        p1->print();
        p2->print();
        p3->print();
        p4->print();
        cout << "面积为：" << area << endl;
    }

};

void test695(){
    Point p1(1,5);
    Point p2(1,2);
    Point p3(4,5);
    Point p4(4,2);
    Rectangle r(&p1, &p2, &p3, &p4);
    r.print();
}

//答案：：：：
class Point1 {
private:
    int x, y;

public:
    Point1(int xCoord = 0, int yCoord = 0) : x(xCoord), y(yCoord) {}

    void setCoordinates(int xCoord, int yCoord) {
        x = xCoord;
        y = yCoord;
    }

    void getCoordinates() const {
        cout << "x = " << x << ", y = " << y << endl;
    }

    int getX()const  { return x; }
    int getY()const  { return y; }
};

class Rectangle1 {
private:
    Point1 topLeft;
    Point1 bottomRight;

public:
    Rectangle1(int x1, int y1, int x2, int y2)
        : topLeft(x1, y1), bottomRight(x2, y2) {}

    void displayCoordinates() const {
        cout << "Top Left: ";
        topLeft.getCoordinates();
        cout << "Bottom Right: ";
        bottomRight.getCoordinates();
    }

    int calculateArea() const {
        int width = bottomRight.getX() - topLeft.getX();
        int height = topLeft.getY() - bottomRight.getY();
        return width * height;
    }
};

void test6952() {
    Rectangle1 rect(1, 4, 6, 1);

    rect.displayCoordinates();

    int area = rect.calculateArea();
    cout << "Area of the rectangle: " << area << endl;
}



//6.9-6
class NJ{
    int n;
    int nj;
public:
    NJ(){
        nj=1;
    }
    void set_N(int a){
        n = a;
    }

    void computeNj(){
        for(int i=1; i<=n; i++){
            nj *= i;
        }
    }

    void print(){
        cout << n << "! = " << nj << endl;
    }
};

void test696(){
    NJ nj;
    nj.set_N(6);
    nj.computeNj();
    nj.print();
}

int main(){
    srand((unsigned int)time(NULL));
    // test61();
    // test65();
    // test66();
    // test67();
    // test68();
    // test69();
    // test610();
    // test611();
    // test612();
    // test613();  //这个内存排序挺好
    // test614(); //这个有操作，要再看一下
    // test615();
    // test695();
    test6952();
    // test696();
    system("pause");
    return 0;
}