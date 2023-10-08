#include<iostream>
#include<cstring>
using namespace std;


/* 数组
一维数组、二维数组：下标从0开始
字符数组：数据类型为字符型的数组，存放一个字符在内存里占用一个字节，可整体使用
         字符串是字符常量的集合，而字符数组是字符变量的集合
         字符数组的使用：可以操作单个元素，也可以对字符数组进行整体操作
         字符数组的输入：cin >> 字符数组名  cin.getline(字符数组，数组大小);    输出：cout << 字符数组名
字符串处理函数：存放在<cstring>头文件中
    字符拷贝函数：char * strcpy(char * , char *);  将第二个参数赋值给第一个函数
    字符串拼接函数：char * stract(char *, char *);  将第二个字符串拼接到第一个之后 ，第一字符串必须有结束标记
    字符比较函数：int strcmp(char *, char *);  比较两个字符串或字符数组的大小，返回值为整数  =0  >1   <-1
    求字符串长度的函数： int strlen(char *);  返回值是字符串长度 以结束标志结尾
    字符串查找函数： char * strstr(char *, char *); 第一个参数母串 第二个参数子串，返回子串首次在母串出现的起始地址
数组与指针
    指针变量的运算：赋值运算--对指针本身赋值运算时改变指针所指的位置，对指针所指的内存空间的赋值运算时改变指针所指对象的内容
                            指针在所指的对象不明确之前不能对其所指的内存空间进行赋值
                   算数运算--对指针所指的内存空间的算数运算东等同于变量的算数运算
                            指针本身的运算通常局限于指针加上或减去一个整数，表示其前后整数个存储单元的地址，两指针相减，表示相隔多少个存储单元
                   关系运算--指针变量可以参加所有的关系运算，用于判断指针所指的位置关系
                   逻辑运算--当指针悬空时，即为NULL，相当于逻辑假；当指针不悬空时，相当于逻辑真
    一维数组和指针：一维数组的数组名是第一个元素的地址
    二维数组和指针：二维数组的数组名是 数组名[0]的地址，不是 数组名[0][0] 的地址，是行地址
                   行指针：p2+i &p2[i]   元素指针  *(p2+i)+j p2[i]+j  
    字符数组和指针：字符指针变量可以直接指向字符串  char *s1 = "sdasdasd";  char *s2;  s2 = "dsadsd";
                   直接因引用字符型指针变量所指向的字符数组   char str[50], *s3 = str;  cin.getline(s3,50);  cout << s3; strcpy(s3,s1); *s3 = *s2;
数组与函数
    传普通一维数组： 函数类型 函数名(数据类型* 指针名, int 变量名); 或者 函数类型 函数名(数据类型* 指针名[], int 变量名);



*/

//4-4 插入字符串
void insert(){
    char str1[] = "We China", str2[] = "love ", str[50];
    strcpy(str, str1+3);
    strcpy(str1+3, str2);
    strcat(str1, str);
    cout << str1 << endl;
}

//4-5指针遍历数组
void print(){
    int arr[] = {1,2,3,4,5,6,7,8};
    int *p = arr;
    int len = sizeof(arr)/sizeof(int);
    for(int i=0; i< len; i++){
        cout << p[i] << "\t";
    }
    cout << endl;
    for(int i=0;i<len;i++){
        cout << *p << '\t';
        p++;
    }
    cout << endl;
}

//4-6 输出二维数组
void print2(){
    int b[3][5]={{2,3,1,4,10}, {6,2,5,8,3}, {7,8,9,6,12}}, sum=0;
    int (*p1)[5] = b, *p2 = &b[0][0], i, j;
    cout << "二维数组为：" << endl;
    for(i=0; i< 3;i++){
        for(j=0; j<5;j++){
            cout << p1[i][j] << '\t';
        }
        cout << endl;
    }
    for(i=0;i<3*5;i++){
        sum+=p2[i];
    }
    cout << "各元素之和为："  << sum << endl;

    for(i=0; i<3;i++){
        for(j=0;j<5;j++){
            cout << *(*p1+j) << '\t';
        }
        cout << '\n';
        p1++;
    }
    for(i=0;i<3*5;i++){
        sum+=*p2;
        p2++;
    }
}

//4-7 逆序字符串
void reverse(){
    char str[100], *s1 = str, *s2 = str, t;
    cout << "请输入一个字符串：" ;
    cin.getline(s1,100);
    cout << "输入的字符是：" << s1 << endl;
    while(*s2)
        s2++;
    s2--;
    while(s1 < s2){
        t = *s1, *s1 = *s2, *s2 = t;
        s1++, s2--;
    }
    cout << "逆序后的字符串为：" << str << endl;
}

//4-8 指针数组
void pointshuzu(){
    double d[6] = {1.0, 1.1, 1.2, 1.3, 1.4, 1.5};
    double * p[6];
    for(int i=0; i<6;i++){
        p[i]=&d[i];
    }
    for(int j=0; j < 6;j++){
        cout << *p[j] << " , ";
    }
}

//4-9 函数输出一维数组
void input(int* p, int n){
    for(int i=0; i<n;i++){
        cout << "请输入第" << i+1 << "个元素：" ;
        cin >> (*p);
        p++;
    }
}

void output(int p[], int n){
    for(int i=0; i< n; i++){
        cout << p[i] << '\t';
        if((i+1)%5==0) cout << endl;
    }
}


void test412(){
    int a[10] = {5,9,2,6,10,8,1,7,4,3};
    for(int i=0; i<9;i++){
        for(int j=i+1; j<10;j++){
            if(a[i] > a[j]){
                int t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
        }
    }

    for(int i=0; i<10;i++){
        cout << a[i] << '\t';
    }
}


void print(int p[], int n){
    for(int i=0; i< n;i++){
        cout << p[i] << '\t';
    }
    cout << endl;
}

int search(int *p, int low, int high, int k){
    if(low > high){
        return -1;
    }
    int mid = (low+high)/2;
    if(p[mid] == k ) return mid;
    else if(p[mid]>k) return search(p, mid+1, high, k);
    else{ return search(p, low, mid-1,k);}
}

void test413(){
    int num[8] = {10,5,3,0,-3,-5,-9,-12};
    print(num, 8);
    int k = -9;
    int pow = search(num, 0 ,8, k);
    cout << pow;
}

void test49(){
    int arr[10],n=10;
    input(arr, n);
    output(arr, n);
}


void create(int p[][5], int n){
    for(int i=0;i<n;i++){
        for(int j=0; j<5;j++){
            *(*(p+i)+j) = rand()%100;
        }
    }
}

void print2(int (*p)[5], int n){
    for(int i=0; i<n; i++){
        for(int j=0; j<5;j++){
            cout << p[i][j] << "\t";
        }
        cout << endl;
    }
}
void test414(){
    int b[4][5];
    create(b, 4);
    print2(b,4);
}


void f1(int p1[][3], int n, int (*p2)[4]){
    for(int i=0;i<n;i++){
        for(int j=0; j<3;j++){
            p2[j][i] = p1[i][j]; 
        }
    }        
}

void print3(int p[][3], int n){
    for(int i=0;i<n;i++){
        for(int j=0; j<3;j++){
            cout << p[i][j] << '\t';
        }
        cout << endl;
    }
}

void print4(int p[][4], int n){
    for(int i=0;i<n;i++){
        for(int j=0; j<4;j++){
            cout << p[i][j] << '\t';
        }
        cout << endl;
    }
}

void test415(){
    int b1[4][3] = {1,2,3,4,5,6,7,8,9,10,11,12}, b2[3][4];
    cout << "原序列：" << endl;
    print3(b1, 4);
    cout << "后：" << endl;
    f1(b1, 4, b2);
    print4(b2, 3);
}


void f16(char *s){
    for(int i=0;s[i];i++){
        if(s[i]==' '){
            if(s[i+1]>='a' && s[i+1]<='z')
                s[i+1] -=32;
        }
    }
}
void test416(){
    char str[100];
    cout << "请输入一个带空格的字符串：";
    cin.getline(str,100);
    f16(str);
    cout << "修改后的字符串为：";
    cout << str << endl;
}

char *fun(char *s){
    char *s1 = s, *s2;
    while(*s1){
        if(*s1 == ' '){
            s2 = s1;
            while(*s2){
                *s2 = *(s2+1);
                s2++;
            }
        }else {
            s1++;
        }
    }
    return s2;
}

char* fun2(char *s){
    char *s1 = s, *s2;
    while(*s1){
        if(*s1 != ' '){
            *s2 = *s1;
            s2++;
        }
        s1++;
    }
    *s2 = '\0';
    return s2;
}

void test417(){
    char s[100];
    cin.getline(s, 100);
    char* s1 = fun(s);
    cout << *s1;
}

void test418(){
    char season[4][10] = {"Spring", "Summer", "Automn", "Winter"};
    for(int i=0; i< 4;i++){
        cout << season[i] << endl;
    }

    for(int i=0;i<4;i++){
        cout << *season[i] << endl;
    }
}

//习题
//4.6-1
int max(int *num, int n){
    int max=0;
    for(int i=0;i<n;i++){
        if(num[i] > max){
            max = num[i];
        }
    }
    cout << "下标为：" ;
    for(int i=0; i< n;i++){
        if(num[i] == max){
            cout << i << ", ";
        }
    }
    cout << endl;
    return max;
}

void test461(){
    int a[] = {3,5,2,7,6,1,7,4,7,5};
    max(a, 10);
}

//4.6-2
void f462(double p[], int n, double &ave){
    for(int i=0; i<n;i++){
        ave += *p;
        p++;
    }
    ave/=n;
}

void test462(){
    double p[] = {1.1, 2.2, 3.3, 2.3, 4.5, 6.1, 3.4, 9.9};
    int n=8;
    double ave;
    f462(p, n, ave);
    int facha = 0;
    for(int i=0; i<n;i++){
        facha += (p[i]-ave)*(p[i]-ave);
    }
    cout << "平均值为：" << ave << endl;
    cout << "方差值为：" << facha << endl;
}

//4.6-3
void print463(float p[][5], int n){
    for(int i=0; i< n; i++){
        for(int j=0; j<5;j++){
            cout << p[i][j] << '\t';
        }
        cout << endl;
    }
}

void fun463_1(float (*p)[5], int n, float*s){
    for(int i=0; i<n; i++){
        for(int j=0 ; j<5;j++){
            *s += *(*(p+i)+j);
        }
    }
}

void test463(){
    float p[][5]={{2.6, 5, 8, 6.3, 1},{4, 12, 9, 4.5, 9.6},{7.2, 3.8, 11, 7.9, 10}};
    cout << "数据为：" << endl;
    print463(p, 3);
    float s=0;
    fun463_1(p, 3, &s);
    cout << "求和为：" << s << endl;
}

#define N 5
//4.6.4
void create464(int p[][N], int n){
    for(int i=0; i<n; i++)
        for(int j=0; j<N; j++)
            if(j==0 || i==j){
                p[i][j] = 1;
            }
    for(int i=0; i<n; i++){
        for(int j=0;j<i;j++){
            if(j!=0){
                p[i][j] = p[i-1][j-1]+p[i-1][j];
            }
        }
    }
}

void print464(int (*p)[N], int n){
    for(int i=0; i<n;i++){
        for(int j=0; j<=i; j++){
            cout << p[i][j] << '\t';
        }
        cout << endl;
    }
}

void test464(){
    int p[N][N];
    create464(p, N);
    print464(p, N);
}


//4.6-5
char * copy(char *s1, char *s2){
    char *ret = s1;
    while(*s2){    
        *s1 = *s2;
        s1++;
        s2++;
    }
    *s1 = '\0';
    return ret;
}

void test465(){
    char s2[10] = "eweaeaeaw";
    char s1[10] = "mmmnnnm";
    cout << copy(s1, s2) << endl;
}

//4.6-6
int count466(char *s){
    int count=0;
    bool isWord = false;
    while(*s){
        if(*s == ' '){
            isWord = false;
        }else{
            if(!isWord){
                count++;
                isWord=true;
            }
        }
        s++;
    }
    return count;
}

void test466(){
    char str[100];
    cout << "请输入语句：" ;
    cin.getline(str, 100);
    int count = count466(str);
    cout << count << endl;
}


int main(){
    // insert();
    // print();
    // print2();
    // reverse();
    // pointshuzu();
    //test49();
    // test412();
    // test413();
    // test414();
    //test415();
    // test416();
    // test417();
    // test418();
    // test461();
    // test462();
    // test463();
    // test464();
    // test465();
    test466();
    system("pause");
    return 0;
}