#include<iostream>
using namespace std;

void test1(){
    int a[12]={8}, *p[3], **pp=p, i;
    for(i=0; i<3;i++)   p[i]=&a[i*4];
    cout << "输出a:\n";
    for(i=0; i<12; i++) cout << a[i] << "  ";
    cout << endl;

    cout << "输出p:\n";
    for(int i=0; i<3; i++){
        for(int j=0; j<4; j++){
            cout << p[i][j] << "  ";
        }
        cout << endl;
    }
    
    cout << "输出pp:\n" ;
    for(i=0; i<3; i++){
        for(int j=0; j<4; j++){
            cout << pp[i][j] << "  ";
        }
        cout << endl;
    }

}

#include<cmath>

bool prime(int n){
    for(int i=2; i<=sqrt(n); i++){
        if(n%i==0){
            return false;
        }
    }
    return true;
}

void gotbaha(int n){
    if(n%2!=0) exit(1);
    for(int i=2; i<=n/2; i++){
        if(prime(i) && prime(n-i)){
            cout << n << "=" << i << "+" << n-i << endl; break;
        }
    }
}

void test2(){
    int n = 11;
    gotbaha(n);
}


void test3(){
    int a[][2] = {1,2,3,4,5,6};
    cout << "a的地址为：" << &a << endl;
    cout << "a[0]的地址为：" << &a[0] << endl;
    cout << "a[0][0]的地址为：" << &a[0][0] << endl;
}

class MyClass {
    int x;

public:
    MyClass(int value) : x(value) {}
    int getX() const {
        return x;
    }

    int getX() {
        return x + 1;
    }
};

void test4(){
    MyClass obj1(10);  // 声明一个非 const 对象
    const MyClass obj2(20);  // 声明一个 const 对象

    int value1 = obj1.getX(); // 调用非 const 函数，返回 x + 1
    int value2 = obj2.getX(); // 调用 const 函数，返回 x
    cout << value1 << "  " << value2 << endl;
}

int main(){
    // test1();
    // test2();
    // test3();    
    test4();
    
    system("pause");
    return 0;
}