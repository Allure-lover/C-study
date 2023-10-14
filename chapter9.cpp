#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;

/*
模板和函数处理：用于表达相同逻辑结构，但具体数据元素类型不同的数据对象通用行为
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
}

int main(){
    // test91();
    // test92();
    test93();
    system("pause");
    return 0;
}


