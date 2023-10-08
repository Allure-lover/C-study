#include<iostream>
#include<cstring>
using namespace std;

/*
结构体和简单链表
结构体是一种构造数据类型：格式： struct 结构体类型名{
                                        成员列表
                                };
    定义变量： ①先定义结构体，再定义变量 Student a1, a2;
              ②定义结构体的同时定义变量 struct Birthday{ int month, day, year;}b1, b2;
              ③直接定义结构体变量       struct {int second; char sex;}s1, s2;
    结构体类型的成员可以做另一个结构体的变量，也可以是自身类型的指针变量，不能是普通变量
    结构体变量的初始化：①定义变量的同时初始化 struct STU{
                                                char sex;
                                                char name[8];
                                                float score;
                                            }st1={'F', "LiNin", 80.5};
                        ②定义结构体变量时，用同类型的变量初始化
    结构体变量的引用：格式：结构体变量名.成员名
    结构体类型的指针变量：定义一个指针来存放该存储空间的首地址   STU *p = &st1;
                        格式：指针变量->成员名  （*指针变量).成员名
动态空间：
    new运算符：使用new来开辟动态内存空间，运算结果是动态申请空间的首地址
        格式： ①  指针变量 = new 数据类型;    int *pointer1; pointer1 = new int; 
               ② 赋初值 指针变量 = new 数据类型(数值); 只适用于基本数据类型 float *pointer2; poniter2 = new float(3.3);
               ③ 动态申请一维数组：指针变量 = new 数据类型[数组大小];
    delete运算符：使用delete运算符释放系统资源 
        格式：① delete 指针变量；  ② delete [] 指针变量； ③ delete [数组大小] 指针变量；
简单链表：
    基本操作：
        遍历链表：Node *p; p=head; while(p->next != NULL){ p=p->next; }
        删除一个节点：p1->next = p1->next->next; delete p;
        插入一个节点：Node *p1 = new Node;  p1->next = p->next; p->next = p1;
    应用：创建链表、输出链表、释放链表节点、删除具体指定节点、插入一个节点
共用体：
    格式： union 共用体类型名{ 成员列表 };
    定义：与结构体类似    union{ int i; char c; }sa1, sa2;
    引用：共用体变量名.成员名 sa1.i =1
    只能存放其中一个成员，后面存放的成员会顶掉前面的成员
    各成员都是共用一个地址
    不能定义变量的同时就对其进行初始化
    不能将共用体作为函数的参数
    共用体可以出现在结构体中，也可以定义共用体数组，结构体也可以出现在共用体类型定义中
*/

//5-1
// struct Stu
// {
//     int num;
//     char name[8];
//     float score;
// };

// //结构体引用的三种方式
// void test51(){
//     Stu stu_1;
//     Stu *p;
//     p=&stu_1;
//     stu_1.num = 17401;
//     strcpy(stu_1.name, "LiNing");
//     stu_1.score = 79.5;
//     cout << "NO: " << stu_1.num << '\t' << "name: " << stu_1.name << '\t' << "score: " << stu_1.score << endl;
//     cout << "No: " << p->num << '\t' << "name: " << p->name << '\t' << "score: " << p->score << endl;
//     cout << "NO: " << (*p).num << '\t' << "name: " << (*p).name << '\t' << "score: " << (*p).score << endl; 
// }

//5.2
struct Node{
    int num;
    Node * next;
};

Node * create(){
    Node * head = new Node;
    Node *p, *pend=head;
    int id;
    cout << "请输入学号(学号为0表示输入结束): ";
    cin >> id;
    while(id!=0){
        p = new Node;
        p->num=id;
        pend->next = p;
        pend = p;
        cout << "请输入学号：";
        cin >> id;
    }
    pend->next = NULL;
    return head;
}

void print(Node *head){
    Node *p = head->next;
    while(p != NULL){
        cout << p->num << '\t';
        p=p->next;
    }
    cout  << endl;
}

void release(Node *head){
    Node *p=head;
    while(head){
        p=head;
        head = head->next;
        delete p;
    }
    cout << "空间释放完毕！" << endl;
}

Node* deleteNode(Node * head, int id){
    Node *p1, *p2;
    p1=p2=head;
    while(p2->num!=id && p2->next!=NULL){
        p1=p2; p2=p2->next;
    }
    if(p2->num == id){
        p1->next = p2->next; delete p2;
    }else{
        cout << "没有找到节点" << endl;
    }
    return head;
}

Node *insert(Node *head, Node *p){
    Node *p1, *p2;
    if(head == 0){      //1链表是空表
        head = p;
        p->next = 0;
        return head;
    }

    if(head->num >= p->num){   //插入节点做头结点
        p->next = head;
        head = p;
        return head;
    }

    p2=p1=head;
    while(p2->next&&p2->num<p->num){     //插入节点做尾节点
        p1=p2;p2=p2->next;
    }
    if(p2->num < p->num){   //插入节点做中间节点
        p2->next=p;
        p->next=0;
    }else{
        p->next=p2;
        p1->next=p;
    }
    return head;
}

void test5234(){
    Node *head = create();
    print(head);

    cout << "删除学号：" ;
    int id;
    cin >> id;
    deleteNode(head, id);
    print(head);

    
    release(head);
}

union Un{
    int count;
    char ch;
};

void test57(){
    Un un;
    Un *p = &un;
    p->count = 0;
    p->ch = 'A';
    cout << p->count << endl;   //65
}

//5-8
struct Node58{
    char c;
    int count;
    Node58 * next;
};
Node58 *search(Node58 *head, char ch){    //建立链表
    Node58 *p;
    p=head;
    while(p){                           //查找含ch字符的节点
        if(p->c == ch){                 //诺找到，ch字符出现次数加一
            p->count++;                 
            break;            
        }
        p = p->next;
    }
    if(p==0){                           //若找不到，建立新节点，连接在表头
        p=new Node58;
        p->c = ch;
        p->count=1;
        if(head) p->next = head;        //若表不空
        else p->next = 0;               //表空
        head = p;
    }
    return head;
}

void print(Node58 *head){
    while(head){
        cout << "字符：" << head->c << " \t出现" << head->count << "次" << endl;
        head = head->next; 
    }
}

void dele(Node58 * head){
    Node58 *p;
    while(head){
        p=head;
        head=head->next;
        delete p;
    }
}


void test58(){
    Node58 *h=0;
    char s[300], *p=s;
    char c;
    cout << "请输入一个字符串：" ;
    cin.getline(s, 300);
    while(c=*p++){
        h=search(h,c);
    }
    print(h);
    dele(h);
}

//5-9
struct Node59{
    int data;
    Node59 *next;
};

Node59 *create59(){
    Node59 *head=0;
    Node59 *p;
    int a;
    cout << "请输入数据(0表示结束输入): ";
    cin >> a;
    while(a){
        p=new Node59;
        p->data = a;
        p->next = head;
        head = p;
        cin >> a;
    }
    return head;
}

Node59 *invert(Node59 *head){
    Node59 *p, *q;
    p=head->next;                //p指向第二个节点
    if(p){
        head->next = NULL;       //head 的 next 指针置空， head做尾节点
        do{
            q=p->next;          //q后移指向下一个节点
            p->next=head;       //p的下一节点指向head 表示p指点被移到head指针的前面
            head=p;             //然后head节点前移到刚才新加的节点
            p=q;                //p指针指向和q指针相同的节点
        }while(p);
    }
    return head;
}

void print(Node59 *head){
    if(head==0){
        cout << "链表为空！" << endl;
    }
    Node59 *p=head;
    cout << "链表的各节点为：" << endl;
    while(p){
        cout << p->data << '\t';
        p=p->next;
    }
    cout <<endl;
}

void release(Node59 *head){
    if(head==0) cout << "链表为空！\n";
    Node59 *p;
    while(head){
        p=head;
        head=head->next;
        delete p;
    }

    cout << "指针空间释放完毕！" << endl;
}

void test59(){
    Node59 *head;
    head = create59();
    print(head);
    head = invert(head);
    print(head);
    release(head);
}

//练习
//1
int sum561(Node59 *head){
    int sum=0;
    while(head){
        sum += head->data;
        head = head->next;
    }
    return sum;
}

void test561(){
    Node59 * head;
    head = create59();
    print(head);
    int sum = sum561(head);
    cout << "它们的和为：" << sum << endl;
}

//2
Node59 *create562(){
    Node59 *head=0;
    Node59 *p, *q;
    int a;
    cout << "请输入数据(0结束): ";
    cin >> a;
    while(a){
        p = new Node59;
        p->data = a;
        p->next=0;
        if(head==0){
            head=p;
            q=p;
        }else{
            q->next = p;
            q=p;
        }
        cout << "请输入数据: " ;
        cin >> a;
    }
    q->next=0;
    return head;
}

Node59* merge(Node59 *head1, Node59* head2){
    Node59 *head=nullptr;
    Node59 *p=nullptr, *q=nullptr;
    int d=0;
    while(head1!=nullptr && head2!=nullptr){
        if(head1->data < head2->data){
            d = head1->data;
            head1=head1->next;;
        }else{
            d = head2->data;
            head2=head2->next;
        }
        p=new Node59;
        p->data = d;
        if(!head){
            head = p;
            q=p;
        }else{
            q->next = p;
            q=p;
        }

    }

    while(head1){
        p=new Node59;
        p->data = head1->data;
        if(!head){
            head = p;
            q=p;
        }else{
            q->next = p;
            q=p;
        }
        head1=head1->next;
    }

    while(head2){
        p=new Node59;
        p->data = head2->data;
        if(!head){
            head = p;
            q=p;
        }else{
            q->next = p;
            q=p;
        }
        head2=head2->next;
    }
    q->next=NULL;
    return head;
}

void test562(){
    
    Node59* head1 = create562();

    Node59* head2 = create562();
    cout << "第一条链表：" ;
    print(head1);
    cout << "第二条链表：" ;
    print(head2);
    cout << "合并结果：" ;
    Node59 *head3 = merge(head1, head2);
    print(head3);
    release(head1);
    release(head2);
    release(head3);
}

//3
struct link{
    int data;
    link* next;
};
int dele563(link* h, int x){
    link *pre, *p;
    bool flag = false;
    if(h->data == x){
        p = h;
        h=h->next;
        delete p;
        flag = true;
    }
    while(h->next){    
        pre = h;
        h=h->next;
        while(h->data == x){    //找到了，删除
            flag = true;
            p = h;
            h = h->next;
            pre->next = h;
            delete p;
        }

    }
    return flag ? 0 : -1;
}

link *create563(){
    link* head=0, *p;
    int a[] = {1,2,3,4,5,6,6,6,7,8};
    for(int i=0; i<sizeof(a)/sizeof(int); i++){
        p=new link;
        p->data = a[i];
        p->next = head;
        head = p;
    }

    return p;
}

void print(link* head){
    while(head){
        cout << head->data << '\t';
        head = head->next;
    }
    cout << endl;
}

void dele(link* head){
    link* p;
    while(head){
        p = head;
        head = head->next;
        delete p;
    }
}

void test563(){
    link* head = create563();
    print(head);
    dele563(head, 6);
    print(head);
    dele(head);
}

//5.6-4
struct Stu{
    int num;
    char name[20];
    float class1;
    float class2;
    float class3;
    float ave;
    float sum;
};

Stu* createStu(){
    Stu stus[10];
    int num;
    char name[20];
    float class1;
    float class2;
    float class3;

    for(int i=0; i<10; i++){
        cout << "请输入学生学号：";
        cin  >> num;
        cout << "请输入姓名：";
        cin.getline(name, 20);
        cout << "请输入三门成绩，逗号隔开：";
        cin >> class1 >> class2  >> class3;
        stus[i].num = num;
        strcpy(stus[i].name, name);
        stus[i].class1 = class1;
        stus[i].class2 = class2;
        stus[i].class3 = class3;
        stus[i].sum = (class1+class2+class3);
        stus[i].ave = stus[i].sum/3;
    }

    return stus;
}

void print(Stu stus[], int n){
    for(int i=0; i<n; i++){
        cout << "学号: " << stus[i].num << "\t姓名: " << stus[i].name << "\t成绩1: " << stus[i].class1 <<  "\t成绩2: " << stus[i].class2 << "\t成绩3: " << stus[i].class3 << "\t平均成绩: " << stus[i].ave << "\t总成绩: " << stus[i].sum << endl;  
    }
}

Stu* getMax(Stu stus[], int n){
    Stu *max;
    max->sum = 0;
    for(int i=0; i<n; i++){
        if(max->sum < stus[i].sum){
            *max = stus[i];
        }
    }
    return max;
}


void test564(){
    Stu* stus = createStu();
    print(stus, 10);
    print(getMax(stus, 10), 1);
}

int main(){
    // test51();
    // test5234();
    // test57();
    // test58();
    // test59();
    // test561();
    // test562();
    // test563();
    test564();
    system("pause");
    return 0;
}