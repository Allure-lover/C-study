#include<iostream>
#include<cstring>
using namespace std;

//1题 递归计算函数的值
int px(int x, int n){
	if(n==1) return x;
	else return x+px(x, n-1)*(-1)*x;
} 

//2 二维数组实现字符串排序
void sort(char a[][20], int n){
	for(int i=0; i<n-1; i++){
		int k=i;
		for(int j=i+1; j<n-1; j++){
			if(strcmp(a[k], a[j])>0) k=j;
		}
		if(k!=i) {
			char temp[20];
			strcpy(temp, a[i]);
			strcpy(a[i], a[k]);
			strcpy(a[k], temp);
		}
	}
} 

void test01(){
	int n=3;
	cout << "结果为:" << px(2, n) << endl;
}

void test02(){
	char a[5][20];
	for(int i=0; i<5; i++){
		cin.getline(a[i], 20);
	}
	for(int i=0; i<5; i++){
		cout <<a[i] << endl;
	}
	cout << "排序后：" << endl;
	sort(a, 5);
	for(int i=0; i<5; i++){
		cout <<a[i] << endl;
	}
}


int main(){
	//test01();
	test02();
	return 0;
}

#include<iostream>
using namespace std;

//生成数列前n项 

int main(int argc, char *arg[]){
	//int n = int(argc);
	int n;
	cout << "请输入n: " ; 
	cin >> n;
	cout << endl;
	int a[n];
	a[0]=2,a[1]=3; 
	for(int i=2; i<n; i++){
		int temp = a[i-1]*a[i-2];
		if(temp < 10) a[i]=temp;
		else{
			a[i]=temp/10; a[++i]=temp%10;
		} 
	}	
	for(int i=0; i<n; i++){
		cout << a[i] << "\t";
	}
	cout << endl;
	return 0;
}



// 逆转链表
#include<iostream>
using namespace std;

typedef struct List{
	char data;
	struct List *next;
}List;


void print(List *head){
	while((head=head->next)) cout << head->data << "\t";
}

void reverse(List *head){
	int i=0, j=0, k=0;
	List *p=head->next, *q;
	int n=0;
	while(p){
		p=p->next;
		n++; 
	}
	for(; i<n/2; i++){
		p=head->next; q=head->next;
		for(j=0; j<i; j++) p=p->next;
		for(k=0; k<n-i-1; k++) q=q->next;
		char temp = p->data;
		p->data = q->data;
		q->data = temp;
	} 
}


int main(){
	//构建链表
	List *head = new List;
	List *p1 = new List;
	p1->data = 'a';
	List *p2 = new List;
	p2->data = 'b';
	head->next = p1;
	p1->next = p2;
	p1 = new List;
	p1->data = 'c';
	p2->next = p1;
	p1->next = NULL;
	print(head);
	cout << endl;
	reverse(head);
	cout << "逆转后：" << endl;
	print(head);
	
	return 0;
} 


 
