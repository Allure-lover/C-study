#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;

/*
模板和异常处理：用于表达相同逻辑结构，但具体数据元素类型不同的数据对象通用行为
    函数模板：格式：template <typename T>                     template<typename T1, typename T2>
                   void fun(T a){}     typename = class      void fun(T1 a, T2 b){}
            调用：函数名(实参列表)
        template <class T>
        T GetMax(class a, class b) { return (a>b)?a:b; }
        template<class a, class b) { retunr (a>b)?a:b; }
        参数模板设置默认值：template<typename T = value>
        调用原则：
            先找最符合函数名和参数类型的函数，若找到则调用它，否则寻找函数模板，将其实例化产生一个匹配的模板函数
            若上述失败，则使用函数的重载的方法，通过类型转换产生参数匹配，若找到就调用它
            若依然没找到，则报错
    类模板：template<class T>
            class 类名{};
            类外定义函数，必须是模板函数，格式：template <typename T>
                                              函数类型 类名<T> :: 成员函数名(形参列表){}
                         类模板的使用：格式：  类名<类型实参列表> 对象名(实参列);
    异常处理：
        异常处理机制：抛出异常、捕获异常、处理异常
        使用throw抛出异常   try catch捕获并处理异常
        处理过程：设置异常代码块抛出，将可能出现错误或异常的代码块设置成被监视代码块，在发生异常时，使用throw抛出
                 将被监视的代码块放到try结构中监视
                 若监视代码块抛出异常，则进入catch结构处理
        格式： throw <表达式>;
                try{ ... }catch(异常类型名 异常对象名){ ... }
                try ... catch 只能有一个try，但可以有多个catch
                catch(...)表示捕获所有类型的异常，并且只能位于同级别的catch最后位置
                try catch 可以嵌套
                throw; 表示不处理这个异常，交给上级处理，即将正在处理的异常信息再次抛出，让其上一层的catch处理
        注意点：
            避免一直没有函数捕获的异常，否则会一直上传到C++系统，导致程序终止
            一般载异常排除后资源可以被正常的释放，但是例外是，载构造函数中抛出异常，系统不会掉用它的析构函数，解决：抛出异常前先释放资源
            异常处理只通过类型检查来匹配，所以catch块的参数可以只有类型
            函数原型中的异常说明要和实现中一场说明一致，否则引起异常冲突                    
            catch块参数建议采用地址传递，可以提高效率，充分利用对象的多态。派生类的异常捕获应该放在基类异常捕获的前面，否则派生类的异常无法捕获
            确保派生类成员函数的异常说明和基类成员函数的异常说明一致

*/

//9-1 冒泡排序模板
template<typename ElementType>
void SortBubble(ElementType *a, int size){
    int i,work;
    ElementType temp;
    for(int pass =1; pass <size; pass++){
        work=1;
        for(int i=0; i<size-pass; i++){
            if(a[i]>a[i+1]){
                temp = a[i];
                a[i]=a[i+1];
                a[i+1] = temp;
                work=0;
                if(work) break;
            }
        }
    }
}

void test91(){
    int b[5]={7,5,2,8,1};
    char c[] = "xkdwzeopb";
    SortBubble(b, 5);
    for(int i=0; i<5; i++){
        cout << b[i] << '\t';
    }
    cout << endl;
    SortBubble(c, strlen(c));
    cout << c << endl; 
}


//9-2重载函数模板
template<typename T>
T Max(T a, T b){ return (a>b) ? a : b; }
template<typename T>
T Max(T a, T b, T c){
    T t = Max(a, b);
    return Max(t, c);
}

int Max(int a, char b){ return (a>b)?a:b; }
void test92(){
    cout << "Max(3, 'a') is " << Max(3, 'a') << endl;
    cout << "Max(9.3, 0.5) is " << Max(9.3, 0.5) << endl;
    cout << "Max(9, 5, 23) is " << Max(9, 5, 23) << endl; 
}

//9-3
template<class T1, class T2>
class AA{
private:
    T1 i;
    T2 j;
public: 
    AA(T1 a, T2 b);
    void print();
};

template<class T1,class T2>
AA<T1, T2>::AA(T1 a, T2 b):i(a), j(b){}
template<class T1, class T2>
void AA<T1,T2>::print(){cout << "i=" << i << ", j=" << j << endl; }

void test93(){
    AA<int, int> a(1,2);
    a.print();
    AA<int, char> a2(4, 'a');
    a2.print();
    AA<double, int> a3(2.9, 10);
    a3.print();
}

//9-5 异常处理
void test95(){
    try{
        cout << "This is a Test! " << endl; 
        throw 1;
        cout << "It can not show!" << endl; 
    }catch(char a){
        cout << "********" << endl;
    }catch(int a){
        cout << "++++++++" << endl;
        cout << "a=" << a << endl;
    }catch(...){
        cout << "catch all type!" << endl;
    }
    cout << "This is an end!" << endl; 
}

//程序举例
//9-6
template<class T, int SIZE>
class Array{
    T data[SIZE];
    Array(const Array& other);
public:
    Array(){};
    T &operator[](int i){
        return data[i];
    }
    const T &getelem(int i)const{
        return data[i];
    }

    void setelem(int i, const T& value){
        data[i] = value;
    }
    operator T*(){   //转化指针
        return data;
    }
};

void test96(){
    Array<int, 20> aa;
    for(int i=0; i<20; i++){
        aa.setelem(i, 2*i);
        // aa[i]=2*i;
    }
    int firstElem = aa.getelem(0);
    int *begin=aa;   //转化指针的作用
    for(int i=0; i<20; i++){
        cout << begin[i] << '\t';
    }
    cout << endl;
}

//9-7
template<class T>
class Vector{
    T *v;
    int sz;
public:
    Vector(T a[], int s){
        v=new T[s];
        sz=s;
        for(int i=0; i<sz; i++){
            v[i] = a[i];
        }
    }
    void print(){
        for(int i=0; i<sz; i++)
            cout << v[i] << '\t';
        cout << '\n';
    }

    int size(){ return sz; }
    T &elem(int i){ return v[i]; }
    template<class U>
    friend void sort(Vector<U> &w);
};

template<class T>
void sort(Vector<T> &w){
    int n=w.size();
    for(int i=0; i<n-1; i++){
        for(int j=i+1; j<n; j++){
            if(w.v[j] < w.v[i]){
                T temp = w.v[i];
                w.v[i] = w.v[j];
                w.v[j] = temp;
            }
        }
    }
}

void test97(){
    int b[6]={5,8,2,7,4,3};
    Vector<int> aa(b, 6);
    cout << "Before Sort:";
    aa.print();
    sort(aa);
    cout << "After sorted:";
    aa.print();
    char str[]={"ueDSHture"};
    Vector<char> ss(str, strlen(str));
    cout << "char before sort:";
    ss.print();
    sort(ss);
    cout << "char after sorted:";
    ss.print();
}

//9-8
void test98(){
    try{
        try{
            throw 'a';
            cout << "First" << endl;
        }catch(char){
            throw;
            cout << "Second" << endl;
        }
    }catch(...){
        cout << "抛出异常" << endl;
    }
}

//9-9
double fun(double x, double y){
    if(y==0){
        throw y;
    }
    return x/y;
}

void test99(){
    double es;
    try{
        double res = fun(2,3);
        cout << 2 << "/" << 3 << " = " << res << endl;
        res = fun(4,0);
        cout << 4 << "/" << 0 << " = " << res << endl;
    }catch(double){
        cerr << "分母为0" << endl; 
        system("pause");
        exit(1);
    }
}

//9-10
#define MAX 200
#define MIN 100
int data;
double di;
class except{
    char *message;
public:
    except(char *ptr){ message = ptr; }
    const char *what(){ return message; }
    virtual void handling(){
        cout << "请再次输入被除数：" ;
        cin >> di;
    }
    void action(){
        cout << "异常为：" << what() << endl;
        handling();
    }
};

class except_derive:public except{
public:
    except_derive(char *ptr):except(ptr){}
    virtual void handling(){
        if(data > MAX){
            cout << "启动数据转换， 将数据减少至" << (data/2) << endl; 
        }else{
            cout << "启动数据转换， 将数据增加到" << (data*2) << endl;
        }
    }
};

double quotient(double m, double n){
    if(n==0){
        throw except("除数为0的错误抛出!");
    }
    return m/n;
}

void test910(){
    double n, result;
    int flag =1;
    char * mess_low = {"数据太小！超出范围！"};
    char * mess_high = {"数据太大！超出范围！"};
    cout << "请输入转换数据：";
    cin >> data;
    cout << "请输入除数和被除数：";
    cin >> n >> di;
    while(flag){
        try{
            if((data > MAX)||(data < MIN)){
                throw except_derive((data>MAX)?(mess_high):(mess_low));
            }
            result = quotient(n, di);
            cout << "二数相除的结果为：" << result << endl;
            flag = 0;
        }catch(except_derive ex){ ex.action(); }
        catch( except ex){ ex.action(); }
    }
}

//习题
//1
template<class T>
T getMin(T t1, T t2){
    return (t1<t2) ? t1 : t2;
}
template<>
const char* getMin(const char* t1, const char* t2){
    return (strcmp(t1, t2) < 0) ? t1 : t2;
}

void test951(){
    int a=1, b=2;
    cout << "Min = " << getMin(a, b) << endl;
    char c = 'a';
    char d = 'b';
    cout << "Min = " << getMin(c, d) << endl;
    const char *s = "dccca";
    const char *s2 = "dcadc";
    cout << "Min = " << getMin(s, s2) << endl;
}


//2
template<typename T>
T getMax(T a[], int n){
    if(n<=0) return 0;
    T max=a[0];
    for(int i=0; i<n ; i++){
        if(a[i] > max) max = a[i];
    }
    return max;
}

void test952(){
    int a[3]={2,5,3};
    cout << "Max = " << getMax(a, 3) << endl;
    char c[3]= {'a', 'c', 'b'};
    cout << "Max = " << getMax(c, 3) << endl;
}

//3
/*
在C++中，异常（Exception）是一种程序执行过程中出现的意外或错误情况。它们可以表示程序无法处理的状况，比如除以零、访问不存在的内存、文件无法打开等。异常提供了一种机制来在异常发生时跳出当前的程序执行流程，转而执行一些特定的处理代码。

异常处理（Exception Handling）是一种机制，用于在程序中处理异常情况。它允许程序员在代码中指定如何处理可能出现的异常，而不是在异常发生时导致程序崩溃或产生不可预知的结果。

在C++中，异常处理通常包括以下几个关键词和机制：

try：try 块用于包含可能会引发异常的代码段。

throw：throw 用于在 try 块中抛出一个异常，指示发生了一个特定的错误情况。

catch：catch 块用于捕获并处理特定类型的异常。当在 try 块中抛出一个异常时，程序会在 catch 块中寻找匹配的异常处理代码。

exception：exception 是一个通用的异常基类，其他特定类型的异常都可以从它派生。

总的来说，异常提供了一种可靠的方式来处理程序中可能会发生的错误情况，而不会导致程序崩溃。它允许你在发生异常时执行特定的代码，
以便进行错误恢复或采取其他必要的措施。
*/

//4
/*
在C++中，throw 语句用于抛出异常，它实际上是在程序中的某个地方引发了一个异常，并且可以传递一个值（即异常对象）作为参数。

理解为“带有实参的跳转”可以通过以下几个方面来理解：

抛出异常：throw 关键字的目的是抛出一个异常，以指示在程序的当前执行点发生了错误或意外情况。

异常对象：你可以在 throw 后面跟随一个表达式，这个表达式的结果就是要抛出的异常对象。这个对象可以是任意类型，通常是一个派生自 std::exception 或 std::exception 的类型。

跳转：一旦抛出了异常，程序会尝试在当前作用域内查找匹配的 catch 块来处理异常。这个过程被称为“异常处理”。

如果找到匹配的 catch 块，程序会跳转到该块，开始执行与异常匹配的代码。

如果没有找到匹配的 catch 块，程序会继续在调用堆栈中查找，直到找到匹配的 catch 块为止。如果没有找到任何匹配的 catch 块，程序会终止，并显示一个未处理的异常消息。

总的来说，throw 语句的作用是在程序中的某个地方引发异常，并且可以将一个异常对象作为参数传递给 catch 块。这使得程序能够在异常发生时执行特定的处理代码，而不会导致程序崩溃。
*/


int main(){
    // test91();
    // test92();
    // test93();
    // test95();
    // test96();
    // test97();
    // test98();
    // test99();
    // test910();
    // test951();
    test952();
    system("pause");
    return 0;
}


