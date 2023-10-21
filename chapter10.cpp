#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
using namespace std;

/*
输入输出流
    两种类型的流：文本流和二进制流
    标准流通过重载运算符：<< 和 >> 执行输入和输出操作    >> （从流中提取）提取操作  << （插入流中）插入操作
    基本流类体系的构成：平行基类 streambuf    ios;
        streambuf:提供对缓冲区的低级操作，设置缓冲区、缓冲区指针、向缓冲区存/取字符等
        iso:及其派生类提供用户使用流类的接口，支持对streambuf缓冲区I/O的格式化或非格式化转化
        cout 是ostream的对象 cin是istream的对象
        I/O流类库的类层次：     iso
                        istream      ostream
        istream_withassign    iostream     ostream_withassign
        基类ios派生出istream 和 ostream ，所有基本流类的基类
        istream负责提供输入（提取）操作的成员函数，派生出istream_withassign  cin是istream_withassign定义的对象
        ostream负责提供输出（插入）操作的成员函数，派生出ostream_withassign  cout是ostream_withassign定义的对象
        iostream是istream和ostream的公有派生的，没有提供新的成员函数，只是将istream和ostream组合起来
    标准输入输出流： 流类库预定义了4个标准流对象：cin cout cerr clog
            对象         对应设备
    输入    cin          键盘               属于缓冲流
    输出    cout         显示器             属于缓冲流     也可以被定向的输出到磁盘
            cerr         显示器             错误信息输出流    非缓冲流
            clog         显示器             错误信息输出流    属于缓冲流
        这四个标准，系统会自动完成数据类型转换
    使用流输入/输出
        控制数据的格式：使用I/O控制符和ios成员函数
        控制符                  功能                    适用于              流成员函数
        dec                     设置整数的基数10        I/O                 
        hex                     设置整数的基数16        I/O
        oct                     设置整数的基数8         I/O
        setfill(c)              设置填充字符            O                   fill(c)
        setw(n)                 设置字段宽度n字符       O                   width(n)
        setprecision(n)         设置实数的精度n位       O                   precision(n)
        setiosflags(flag)       设置flag中指定标志位    I/O                 setf()
        resetionsflags(flag)    清除flag中指定的标志位  I/O                 unsetf()

        常用的设置格式状态的功能格式标志
        ios::left              输出数据在本域宽范围内左对齐
        ios::right             输出数据在本域宽范围内右对齐
        ios::dec               设置整数的基数10
        ios::oct               设置整数的基数为8
        ios::hex               设置整数的基数为16
        ios::showpoint         强制输出浮点数的小数点和尾数0
        ios::fixed             浮点数以定点格式（小数形式）输出
        用户自定义操作符控制输入/输出格式
            格式：ostream &操作符名(ostream &stream) { ... return stream; }
                 istream &操作符名(istream &stream) { ... return stream; }
        getline()成员函数：格式：istream &getline(char *pch, int nCount, char delim='\n); 读取多个字符        
                                cin.getline(line, 100, '\t');
        get()成员函数：char istream::get();  只输入单个字符
                    istream& istream::get(char *, int, char delim='\n');   可以读一系列字符
        put()成员函数：输出单个字符  cout.put('E');
                       连续输出  cout.put(letter).put('\n);
    文件的输入输出：
        文件流类库：        ios
                istream           ostream
        ifstream        iostream        ofstream
                        fstream
        文件的基本操作：    
            步骤：建立一个文件流（文件流对象）                 ifstream  infile;  ofstream outfile; iostream iofile;
                 将建立的文件流对象与相应的文件关联            infile.open("data.DAT");
                    使用成员函数open打开 对象名.open(文件名，打开方式);
                    ios::in  读（输入）方式打开
                    ios::out 写（输出）方式打开，默认的
                    ios::app 追加（输出）方式打开
                    ios::ate 打开已有文件，文件指针指向文件末尾
                    ios::trunc 打开一个文件，若文件存在，删除全部数据，若不存在，建立新文件 如指定ios::out，未指定ios::app\ios::ate\ios::in，默认此方式
                    ios::binary 二进制方式打开，如不指定此方式，默认ASCLL方式
                    ios::noreplace 若文件不存在，则创建新文件，若存在，则操作失败。不更新原有文件
                    ios::in|ios::out i/o方式打开，文件可读写
                    ios::out|ios::binary 二进制写方式打开文件
                    ios::in|ios::binary 二进制读方式打开文件
                    使用构造函数打开文件    流类 对象名(文件名，方式);
                    打开文件都需要判断是否打开成功
                        格式：ifstream infile("data.txt");
                              if(!infile){
                                    cout << "open error!" << endl;
                                    exit(1);
                              }
                              ifstream infile;
                              infile.open("data.txt");
                              if(!infile){
                                    cout << "open error!" << endl;
                                    exit(1);
                              }
                 对文件的读写操作
                    使用运算符进行读写操作      infile >> ch;  outfile << ch;
                    成员函数进行读写操作        infile.get(ch); outfule.put(ch);                              
                 关闭文件流
                    对象名.close();     infile.close();
            文本文件的操作：通过提取运算符或者插入运算符来操作
            二进制文件操作：只能通过read和write来实现
                read()函数： istream &istream::read(char *, int);   char* 指向内存一块存储空间，int指定读入内存的字节数
                write()函数：ostream &ostream::write(const char *, int);  char* 指向内存内的一块连续空间，int 指定字节数
                测试文件结束函数 eof(): int ios::eof(); 当指向文件结束位置时，返回非0值（真），否则返回0（假）
                随机访问二进制文件：
                    gcount(): 返回最后一次读入的字节数     ifstream
                    tellg(): 返回文件读指针的当前位置       ifstream
                    seekg(long pos): 将文件读指针移到指定位置       ifstream
                    seekg(long off, ios::seek_dir): 将文件读指针以参照位置为基准移到指定位置        ifstream
                    tellp(): 返回当前写指针的位置       ofstream
                    seekp(long pos): 将文件的写指针移动到指定位置       ofstream
                    seekp(long off, ios::seek_dir): 将文件写指针以参照位置为基准移到指定位置        ofstream
                    ios::pos : ios::beg 文件起始位置  ios::cur 当前指针位置  ios::end 文件尾部位置
                    

*/
//10-1用控制符控制I/O格式
void test101(){
    int num = 100, a, b, c;
    double pi = 3.14159;
    cout << "输入：";
    cin >> hex >> a >> dec >> b >> oct >> c;    // EA 45 654
    cout << a << "\t" << b << '\t' << c << endl;       // 234 45 428
    cout << "hex:" << hex << num << endl;             //16进制格式输出   64
    cout << "dec:" << dec << setw(6) <<  setfill('#') << num << endl;   //设置填充符#    ###100
    cout << "pi = " << pi << endl;                                 //浮点数默认输出      3.14159  小数精度默认6位有效数字，不足按实际输出
    cout << "pi = " << setiosflags(ios::fixed) << pi << endl;      //设置固定小数        3.141590   小数精度默认小数点后6位
    cout << resetiosflags(ios::fixed);                             //清除fixed标志位     
    cout << "pi = " << setprecision(4) << pi << endl;               //指定精度输出      3.152    单独使用setprecison只能设置精度有效数字
    cout << "pi = " << setprecision(4) << setiosflags(ios::fixed) << pi << endl;        //联合使用才能控制小数点后的精度位数  3.1416
    cout << "pi = " << setw(10) << setprecision(4) << setiosflags(ios::fixed | ios::right) << pi << endl;       //####3.1416
}

//10-2
void test102(){
    int num=100;
    double pi = 3.14159;
    cout.unsetf(ios::dec);
    cout.setf(ios::hex);                        //设置16进制输出格式
    cout << "hex:" << num << endl;             
    cout.unsetf(ios::hex);                      //恢复16进制输出格式
    cout << "dec:";
    cout.width(6);                              //设置输出宽度
    cout.fill('#');                             //设置填充符#
    cout << num << endl;
    cout << "pi = " << pi << endl;              //浮点数默认输出
    cout.setf(ios::fixed);                      //设置固定小数
    cout << "pi = " << pi << endl;
    cout.unsetf(ios::fixed);                    //清除fixed标志位
    cout << "pi = " << pi << endl;
    cout.precision(4);                          //设置精度
    cout << "pi = " << pi << endl;
    cout.setf(ios::fixed);
    cout << "pi = " << pi << endl;
    cout << "pi = ";
    cout.width(10);
    cout.setf(ios::right);                      //设置右对齐输出
    cout << pi << endl;
}

//10-3
class PhoneNumber;
ostream &operator<<(ostream &output, const PhoneNumber &s);
istream &operator>>(istream &input, PhoneNumber &s);
class PhoneNumber{
public:
    char nationCode[4];
    char areaCode[4];
    char phoneCode[8];
    friend ostream& operator<<(ostream&, PhoneNumber&);
    friend istream& operator>>(istream&, PhoneNumber&);
};
ostream& operator<<(ostream& output, PhoneNumber &num){
    output << "(" << num.nationCode << ")" << num.areaCode << "-" << num.phoneCode;
    return output;
}

istream& operator>>(istream& input, PhoneNumber &num){
    input.ignore();                          //忽视(
    input.getline(num.nationCode, 4);
    input.ignore();                          //忽视)
    input.getline(num.areaCode, 4); 
    input.ignore();                          //忽视-
    input.getline(num.phoneCode, 8);
    return input;
}

void test103(){
    PhoneNumber phone;
    cout << "输入形式如(086)025-8445431的电话号码" << endl;
    if (cin >> phone) {
        cout << "输入的电话号码是：" << endl << phone << endl;
    } else {
        cout << "输入的电话号码格式不正确，请重新输入。" << endl;
        cin.clear(); // 清除输入缓冲区的错误状态
        // cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略错误的输入
    }

}

//10-8  写数据 10个学生成绩
void test108(){
    float score[10];
    ofstream outfile;     //创建一个输出流
    outfile.open("score.txt", ios::out);  //打开文件
    if(!outfile){                         //判断是否打开成功
        cerr << "文件打开失败" << endl;
        exit(1);
    }
    cout << "请输入10个学生的C++课程成绩：\n";    //开始写入数据
    for(int i=0; i<10; i++){
        cin >> score[i];
        // outfile.put(score[i]);
        outfile << score[i] << "  "; 
    }
    outfile.close();             //关闭文件
    cout << "保存成功" << endl;

}

//10-9
void test109(){
    float score[10];
    float max, min, sum=0;
    double ave;
    fstream infile;
    infile.open("score.txt", ios::in);
    if(!infile){
        cerr << "open error!" << endl;
        exit(1);
    }
    cout << "学生成绩" << endl;
    for(int i=0; i<10; i++){
        infile >> score[i];
        cout << score[i] << '\t';
    }
    cout << endl;
    max = min = score[0];
    for(int i=0; i<10; i++){
        sum+=score[i];
        if(score[i] < min) min = score[i];
        if(score[i] > max) max = score[i];
    }
    ave = sum/10.0;
    cout << "最高分：" << max << endl;
    cout << "最低分：" << min << endl;
    cout << "平均分：" << ave << endl;
    infile.close();
}

//10-10 建立一个文件记录学生信息    二进制
struct student
{
    int num;
    char name[20];
    float score;
};

void test1010(){
    student stu[5]={{1001, "zhang", 90}, {1002, "wang", 88}, {1003, "wu", 92}, {1004, "li", 85}, {1005, "Chen", 90}};
    ofstream outfile;
    outfile.open("stud.dat", ios::out|ios::binary);
    if(!outfile){
        cerr << "open error!" << endl;
        exit(1);
    }
    for(int i=0; i<5; i++){
        outfile.write((char*)&stu[i], sizeof(stu[i]));
    }
    outfile.close();
}

//10-11
void test1011(){
    student stu[5];
    ifstream infile;
    infile.open("stud.dat", ios::in|ios::binary);
    if(!infile){
        cerr << "open error!" << endl;
        exit(1);
    }
    for(int i=0; i<5; i++){
        infile.read((char*)&stu[i], sizeof(stu[i]));
        cout << stu[i].num << '\t' << stu[i].name << '\t' << stu[i].score << endl;
    }
    infile.close();
}

//10-12 文件随机读写示例
void test1012(){
    student stu[5]={{1001, "zhang", 90}, {1002, "wang", 88}, {1003, "wu", 92}, {1004, "li", 85}, {1005, "Chen", 90}};
    ofstream outfile("stud.bin", ios::out|ios::binary);
    if(!outfile){
        cerr << "open error!" << endl;
        exit(1);
    }
    for(int i=0; i<5; i++){
        outfile.write((char*)&stu[i], sizeof(stu[i]));
    }
    student newstu = {1008, "zhu", 83};
    outfile.seekp(2*sizeof(student));
    outfile.write((char *)&newstu, sizeof(newstu));
    outfile.close();
    fstream infile("stud.bin", ios::in|ios::binary);
    if(!infile){
        cerr << "open error!" << endl;
        exit(1);
    }
    student st[5];
    for(int i=0; i<5; i++){
        infile.read((char*)&st[i], sizeof(st[i]));
        cout << st[i].num << "\t" << st[i].name << "\t" << st[i].score << endl;
    }
    student nst;
    infile.seekg(sizeof(student)*2, ios::beg);
    infile.read((char *)&nst, sizeof(student));
    cout << "新生信息：\n" << nst.num << "\t" << nst.name << "\t" << nst.score << endl;
    infile.close();
}

//程序举例
//10-13 建立学生成绩文件，输出不及格学生
void test1013(){
    char fileName[30], name[30], s[80];
    int number, score;
    ofstream outstuf;
    cout << "请输入要建立的文件名：" << endl;
    cin >> fileName;
    outstuf.open(fileName, ios::out);
    if(!outstuf){
        cerr << "open error!" << endl;
        abort();
    }
    outstuf << "学生成绩文件\n" ;
    cout << "输入学号、姓名、成绩: 按ctrl-z 结束\n";
    while(cin >> number >> name >> score)
        outstuf << number << ' ' << name << ' ' << score << "\n";
    outstuf.close();
    fstream instuf("d:\\test\123.txt", ios::in);
    if(!instuf){
        cerr << "open error!" << endl;
        abort();
    }
    instuf.getline(s, 80);
    cout << "\n不及格的学生为: " << endl;
    while(instuf >> number >> name >> score){
        if(score <60){
            cout << number << '\t' << name << '\t' << score << endl;
        }
    }
    instuf.close();
}

//10-14 复制f1 到 f2
void test1014(){
    char ch;
    ifstream f1("d:\\test\f1.txt");
    if(!f1){
        cerr << "open error!" << endl;
        return;
    }
    ofstream f2("d:\\test\f2.txt");
    if(!f2){
        cerr << "open error! " << endl;
        return ;
    }
    while(f1 && f1.get(ch)){
        f2.put(ch);
    }
    f1.close();
    f2.close();
    cout << "完成！" << endl;
}

//10-15 文件名作为参数浏览文件示例
void browseFile(char *, int);
void test1015(){
    char fileName[80];
    cout << "请输入要打开的文件名：";
    cin >> fileName;
    browseFile(fileName, 1);
}

void browseFile(char *fileName, int delLine){
    ifstream inf(fileName, ios::in);
    char s[80];
    for(int i=1; i<=delLine; i++){
        inf.getline(s, 80);
    }
    while(!inf.eof()){
        inf.getline(s, 80);
        cout << s << endl;
    }
    inf.close();
}

//习题
//1
void test1051(){
    cout << "12345" << setw(10) << setfill('$') << 10000 << endl;  //12345$$$$$10000
    cout << setw(8) << setprecision(3) << 1024.987654 << endl;  //  1.02e+03
    cout << oct << 99 << endl << hex << 99 << endl;   // 143  \n 63
}

//2 摄氏度和华氏度转换
void test1052(){
    float fahrenheit;
    cout << "请输入华氏度：";
    cin >> fahrenheit;
    float celsius = 5.0/9.0*(fahrenheit-32);
    cout << setw(6) << setiosflags(ios::fixed) << setprecision(2) << celsius << endl; 
}

//3. 将二维数组输入到文本文件中
void test1053(){
    ofstream outfile("shuzu.txt");
    if(!outfile){
        cerr << "open error! " << endl;
        exit(1);
    }
    int a[5][5];
    cout << "请输入元素值：" << endl;
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            cin >> a[i][j];
            outfile << a[i][j] << "  ";
        }
    }
    outfile.close();
}

//4.求出2-100的素数，并将其分别送到文本文件和二进制文件
bool judge(int num);
void test1054(){
    ofstream outfile("sushu.txt");
    if(!outfile){
        cerr << "open error!" << endl;
        exit(1);
    }
    ofstream outfile2;
    outfile2.open("sushu.bin", ios::out|ios::binary);
    if(!outfile2){
        cerr << "open error!" << endl;
        exit(1);
    }
   
    for(int i=2, j=0; i<200; i++){
        if(judge(i)){
            j++;
            outfile.width(10);
            outfile << i;
            outfile2.write(reinterpret_cast<const char*>(&i), sizeof(int));
            if(j%5 == 0){
                outfile << "\n";
            }
        }
    }
    outfile.close();
    outfile2.close();
}

bool judge(int num){
    for(int i=2; i<sqrt(num); i++){
        if(num % i==0) return false;
    }   
    return true;
}

 bool is_prime(int num) {
    if (num < 2) return false;
    for (int i = 2; i*i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

void test10542(){
    ofstream txt_file("prime.txt");
    ofstream dat_file("prime.dat", ios::binary);

    if (!txt_file.is_open() || !dat_file.is_open()) {
        cerr << "Error opening files." << endl;
        exit(1);
    }

    int count = 0;
    for (int i = 2; i <= 200; i++) {
        if (is_prime(i)) {
            txt_file.width(10);
            txt_file << i;

            dat_file.write(reinterpret_cast<const char*>(&i), sizeof(int));

            count++;
            if (count % 5 == 0) {
                txt_file << endl;
            } else {
                txt_file << ' ';
            }
        }
    }

    txt_file.close();
    dat_file.close();
}

//5 从文本文件读取数据，并计算平均值
void test1055(){
    ifstream infile;
    infile.open("suijishu.txt");
    if(!infile){
        cerr << "open error!" << endl;
        exit(1);
    }
    int score[7];
    int count=0, sum=0;
    for(int i=0;infile >> score[i]; i++){    //以读取是否成功作为循环的判断条件
        sum+=score[i];
        count++;
    }

    cout << "数据：" << endl;
    for(int i=0; i<7; i++){
        cout << score[i] << "  ";
    }

    cout << "\n个数为：" << count << endl;
    cout << "总和为：" << sum << endl;
    cout << "平均值为：" << (sum/count) << endl;
    infile.close();
}
//示例

void tes10552(){
    ifstream input_file("data.txt");
    
    if (!input_file.is_open()) {
        cerr << "Error opening file." << endl;
        exit(1);
    }

    int num;
    int sum = 0;
    int count = 0;

    while (input_file >> num) {
        sum += num;
        count++;
    }

    input_file.close();

    if (count > 0) {
        double average = static_cast<double>(sum) / count;
        cout << "Total numbers: " << count << endl;
        cout << "Average: " << average << endl;
    } else {
        cout << "No data found." << endl;
    }
    input_file.close();
}

//6 产生一个求出5-1000所有奇数的文件（二进制），将文件中的第20-30中的数度出输出，要求移动指针类实现文件的随机读取
void test1056(){
    ofstream outfile("jishu.dat", ios::out|ios::binary);
    if(!outfile){
        cerr << "open error!" << endl;
        exit(1);
    }
    for(int i=5; i<=1000; i++){
        if(i%2!=0){
            outfile.write(reinterpret_cast<const char *>(&i), sizeof(int));
        }
    }
    outfile.close();
    ifstream infile;
    infile.open("jishu.dat", ios::in|ios::binary);
    if(!infile){
        cerr << "open error!" << endl;
        exit(1);
    }
    infile.seekg(sizeof(int)*19);
    int data;
    for(int i=0; i<11; i++){
        infile.read((char *)&data, sizeof(int));
        cout << data << "  ";
    }
    infile.close();
    cout << endl;
}

//答案
void test10562(){
    // 创建并打开二进制文件
    ofstream binary_file("odd_numbers.dat", ios::binary);

    if (!binary_file.is_open()) {
        cerr << "Error opening file." << endl;
        exit(1);
    }

    // 生成奇数并写入文件
    for (int i = 5; i <= 1000; i += 2) {
        binary_file.write(reinterpret_cast<const char*>(&i), sizeof(int));
    }

    binary_file.close();

    // 打开文件以进行随机读取
    ifstream read_file("odd_numbers.dat", ios::binary);

    if (!read_file.is_open()) {
        cerr << "Error opening file for reading." << endl;
        exit(1);
    }

    // 设置指针位置
    read_file.seekg(19 * sizeof(int), ios::beg);

    // 读取并输出第20到30个数
    for (int i = 1; i < 12; ++i) {
        int num;
        read_file.read(reinterpret_cast<char*>(&num), sizeof(int));
        cout << num << endl;
    }

    read_file.close();
}


int main(){
    // test101();
    // test102();
    // test103();
    // test108();
    // test109();
    // test1010();
    // test1011();
    // test1012();
    // test1013();
    // test1014();
    // test1015();
    // test1051();
    // test1052();
    // test1053();
    // test1054();
    // test10542();
    // test1055();
    test1056();
    test10562();
    system("pause");
    return 0;
}