1. **熟练掌握程序设计的基础知识，包括数据类型、常量、变量、运算符与表达式、 选择结构、循环结构、程序组成等，理解变量的作用域和存储类型的概念；**

   **’①数据类型**

   基本内置类型

   bool char int float double void 宽字符型 wchar_t

   基本类型可以用一个或者多个类型修饰符进行修饰

   signed   unsigned   short   long

   | 类型               | 位            | 范围                                                         |
   | :----------------- | :------------ | :----------------------------------------------------------- |
   | char               | 1 个字节      | -128 到 127 或者 0 到 255                                    |
   | unsigned char      | 1 个字节      | 0 到 255                                                     |
   | signed char        | 1 个字节      | -128 到 127                                                  |
   | int                | 4 个字节      | -2147483648 到 2147483647                                    |
   | unsigned int       | 4 个字节      | 0 到 4294967295                                              |
   | signed int         | 4 个字节      | -2147483648 到 2147483647                                    |
   | short int          | 2 个字节      | -32768 到 32767                                              |
   | unsigned short int | 2 个字节      | 0 到 65,535                                                  |
   | signed short int   | 2 个字节      | -32768 到 32767                                              |
   | long int           | 8 个字节      | -9,223,372,036,854,775,808 到 9,223,372,036,854,775,807      |
   | signed long int    | 8 个字节      | -9,223,372,036,854,775,808 到 9,223,372,036,854,775,807      |
   | unsigned long int  | 8 个字节      | 0 到 18,446,744,073,709,551,615                              |
   | float              | 4 个字节      | 精度型占4个字节（32位）内存空间，+/- 3.4e +/- 38 (~7 个数字) |
   | double             | 8 个字节      | 双精度型占8 个字节（64位）内存空间，+/- 1.7e +/- 308 (~15 个数字) |
   | long double        | 16 个字节     | 长双精度型 16 个字节（128位）内存空间，可提供18-19位有效数字。 |
   | wchar_t            | 2 或 4 个字节 | 1 个宽字符                                                   |

   typedef type newname  为已有类型起一个新名字

   **枚举类型**

   枚举类型是c++中的一种派生的数据类型，它有用户定义的若干枚举常量的集合

   创建枚举，需要使用关键字enum。枚举类型的一般形式

   ```c++
   enum 枚举名{
       标识符[=整型常数],
       标识符[=整型常数],
       ...
   }枚举变量;
   //默认情况：第一个名称的值为0，第二个名称的值为1，第三个名称的值为2，以此类推
   enum color{red, green, blue} c;
   c = blue;
   //也可以自己赋值，后面的默认是比前面的大，blue=6，red仍然是0
   enum color {red, green=5,blue} c;
   ```

   **类型的转换**

   **静态类型转换（static_cast）** 是一种基本的类型转换，它在编译时进行，不提供运行时类型检查。它可以用于以下几种转换情况：

   1. **相关类型之间的转换**：例如基本数据类型之间的转换，如整数和浮点数之间的转换。
   2. **父子类指针或引用之间的转换**：可以将指向派生类的指针或引用转换为指向基类的指针或引用，但这可能在运行时引发问题，因此应该谨慎使用。
   3. **将枚举类型转换为整数类型**：可以将枚举类型转换为其底层的整数类型，反之亦然。
   4. **指针和整数类型之间的转换**：可以在一定条件下将指针类型转换为整数类型，或者将整数类型转换为指针类型（但要非常小心，以免引发未定义行为）。
   5. **自定义类型之间的转换**：可以使用构造函数和转换操作符来定义类型之间的转换规则。

   静态类型转换的语法如下：

   ```c++
   cppCopy code
   new_type = static_cast<new_type>(expression);
   ```

   其中，`new_type` 是要转换的目标类型，而 `expression` 是要转换的表达式。需要注意的是，静态转换并不会进行运行时类型检查，因此在使用静态转换时，你需要确保转换是安全的，以避免可能的问题。

   以下是一些示例：

   ```c++
   cppCopy code// 转换相关类型
   int num = 10;
   double doubleNum = static_cast<double>(num);
   
   // 父子类指针之间的转换
   class Base {};
   class Derived : public Base {};
   Base* basePtr = new Derived();
   Derived* derivedPtr = static_cast<Derived*>(basePtr);
   
   // 枚举类型转换为整数类型
   enum Color { Red, Green, Blue };
   int colorValue = static_cast<int>(Green);
   
   // 指针和整数类型之间的转换
   int* intptr = new int(42);
   intptr_t intAddress = reinterpret_cast<intptr_t>(intptr);
   
   // 自定义类型之间的转换
   class Distance {
   public:
       Distance(int meters) : meters_(meters) {}   
       operator int() const { return meters_; }
   
   private:
       int meters_;
   };
   
   Distance distance(1000);
   int meters = static_cast<int>(distance);
   ```

   要注意，在进行类型转换时，要尽量避免执行不安全的操作，因为静态转换不提供运行时类型检查，可能会导致程序运行时的错误或未定义行为。

   **动态转换**

   在 C++ 中，动态类型转换是一种在运行时进行的类型转换，用于处理类层次结构中的类型转换，尤其是在基类和派生类之间的转换。C++ 提供了 `dynamic_cast` 运算符来执行动态类型转换。

   `dynamic_cast` 主要用于以下场景：

   1. 将指向派生类对象的指针或引用转换为指向基类对象的指针或引用。
   2. 用于基类指针或引用，尝试将其转换为派生类指针或引用。如果基类指针或引用确实指向派生类对象，转换会成功；否则，如果指针或引用实际指向基类对象，转换将失败，返回一个空指针（对于指针）或抛出 `std::bad_cast` 异常（对于引 用）。

   `dynamic_cast` 使用起来需要满足以下条件：

   - 基类必须有虚函数，否则 `dynamic_cast` 无法工作。
   - 转换方向必须是从派生类到基类，或者从基类到派生类（在这种情况下，运行时类型检查可能失败）。

   需要注意的是，`dynamic_cast` 主要用于处理类层次结构中的转换，而静态类型转换（`static_cast`）通常用于非多态类型转换。使用 `dynamic_cast` 时要谨慎，确保类型转换是安全的，以避免可能的运行时错误。

   ```c++
   class Base {};
   class Derived : public Base {};
   Base* ptr_base = new Derived;
   Derived* ptr_derived = dynamic_cast<Derived*>(ptr_base); // 将基类指针转换为派生类指针
   ```

   **常量转换**

   在 C++ 中，常量转换是指通过 `const_cast` 运算符从一个表达式中移除 `const` 修饰符或者将 `volatile` 修饰符添加到一个表达式。常量转换允许你修改指向常量对象的指针或引用，或者使得指向非常量对象的指针或引用指向常量对象。但需要注意，常量转换可能会导致潜在的不安全行为，应该谨慎使用。

   `const_cast` 主要用于以下情况：

   1. **去除常量性**：你可以使用 `const_cast` 去除指向常量对象的指针或引用的 `const` 修饰符。这允许你修改原本被声明为常量的对象。

   2. **添加常量性**：你也可以使用 `const_cast` 将指向非常量对象的指针或引用转换为指向常量对象的指针或引用。这可以防止你意外地修改对象的值。

   需要注意的是，虽然 `const_cast` 允许你修改 `const` 对象或指针的值，但这种操作可能会导致未定义行为。在实际编程中，应该尽量避免使用 `const_cast`，除非你确实了解其影响并且有充分的理由这么做。

    **重新解释转换**（Reinterpret Cast）

   重新解释转换将一个数据类型的值重新解释为另一个数据类型的值，通常用于在不同的数据类型之间进行转换。

   重新解释转换不进行任何类型检查，因此可能会导致未定义的行为。

   ```c++
   int i = 10;
   float f = reinterpret_cast<float&>(i); // 重新解释将int类型转换为float类型
   ```

   **②常量**

   常量是固定值，在程序执行期间不会改变。这些固定的值，又叫做**字面量**。

   常量可以是任何的基本数据类型，可分为整型数字、浮点数字、字符、字符串和布尔值。

   常量就像是常规的变量，只不过常量的值在定义后不能进行修改。

   

   整数常量可以是十进制、八进制或十六进制的常量。前缀指定基数：0x 或 0X 表示十六进制，0 表示八进制，不带前缀则默认表示十进制。

   整数常量也可以带一个后缀，后缀是 U 和 L 的组合，U 表示无符号整数（unsigned），L 表示长整数（long）。后缀可以是大写，也可以是小写，U 和 L 的顺序任意。

   ```c++
   212         // 合法的
   215u        // 合法的
   0xFeeL      // 合法的
   078         // 非法的：8 不是八进制的数字
   032UU       // 非法的：不能重复后缀
   85         // 十进制
   0213       // 八进制 
   0x4b       // 十六进制 
   30         // 整数 
   30u        // 无符号整数 
   30l        // 长整数 
   30ul       // 无符号长整数
   ```

   

   浮点常量由整数部分、小数点、小数部分和指数部分组成。您可以使用小数形式或者指数形式来表示浮点常量。

   当使用小数形式表示时，必须包含整数部分、小数部分，或同时包含两者。当使用指数形式表示时， 必须包含小数点、指数，或同时包含两者。带符号的指数是用 e 或 E 引入的。

   ```c++
   3.14159       // 合法的 
   314159E-5L    // 合法的 
   510E          // 非法的：不完整的指数
   210f          // 非法的：没有小数或指数
   .e55          // 非法的：缺少整数或分数
   ```

   

   布尔常量共有两个，它们都是标准的 C++ 关键字：

   - **true** 值代表真。
   - **false** 值代表假。

   我们不应把 true 的值看成 1，把 false 的值看成 0。

   

   字符常量是括在单引号中。如果常量以 L（仅当大写时）开头，则表示它是一个宽字符常量（例如 L'x'），此时它必须存储在 **wchar_t** 类型的变量中。否则，它就是一个窄字符常量（例如 'x'），此时它可以存储在 **char** 类型的简单变量中。

   字符常量可以是一个普通的字符（例如 'x'）、一个转义序列（例如 '\t'），或一个通用的字符（例如 '\u02C0'）。

   在 C++ 中，有一些特定的字符，当它们前面有反斜杠时，它们就具有特殊的含义，被用来表示如换行符（\n）或制表符（\t）等。下表列出了一些这样的转义序列码：

   | \\         | \ 字符                     |
   | ---------- | -------------------------- |
   | \'         | ' 字符                     |
   | \"         | " 字符                     |
   | \?         | ? 字符                     |
   | \a         | 警报铃声                   |
   | \b         | 退格键                     |
   | \f         | 换页符                     |
   | \n         | 换行符                     |
   | \r         | 回车                       |
   | \t         | 水平制表符                 |
   | \v         | 垂直制表符                 |
   | \ooo       | 一到三位的八进制数         |
   | \xhh . . . | 一个或多个数字的十六进制数 |

   

   字符串字面值或常量是括在双引号 **""** 中的。一个字符串包含类似于字符常量的字符：普通的字符、转义序列和通用的字符。

   您可以使用 **\** 做分隔符，把一个很长的字符串常量进行分行。

   

   在 C++ 中，有两种简单的定义常量的方式：

   - 使用 **#define** 预处理器。
   - 使用 **const** 关键字。

   define 预处理器

   下面是使用 #define 预处理器定义常量的形式：

   ```c++
   #define identifier value
   ```

   

   const 关键字

   您可以使用 **const** 前缀声明指定类型的常量，如下所示

   ```c++
   const int  LENGTH = 10;
   const int  WIDTH  = 5;
   const char NEWLINE = '\n';
   ```

   

   **③变量**

   

   

   

   运算符与表达式、 

   选择结构

   循环结构

   程序组成

2. **熟练掌握函数的定义与使用，并能熟练使用一般数据类型、指针类型和引用类型 等作为函数参数；** 

   

3. **熟练掌握数组的定义与使用，熟练使用指针对数组进行各类操作，理解并能熟练 使用数组作为函数参数等；** 

   

4. **理解面向对象程序设计的基本思想和方法，理解并掌握类、对象的定义与使用， 熟悉构造函数和析构函数的概念、定义与使用，了解静态成员、常成员、this 指 针等相关概念；** 

   

5. **理解继承与派生的概念，掌握继承的方法及虚基类的定义和使用，熟悉赋值兼容、 同名冲突的机制和解决方法等；** 

   

6. **理解面向对象中的多态性概念，掌握虚函数的定义、特点和使用，理解纯虚函数 和抽象类的概念，熟练掌握 C++中的多态定义与实现；** 

   

7. **了解友元函数的定义与使用，理解 C++中运算符重载的目的，掌握 C++中主要运 算符的重载实现方法；**

   

8. **理解 C++的输入/输出系统和流库结构，初步掌握流库中的输入输出运算符，熟悉 文件的打开、关闭和读写方法；** 

   

9. **了解异常处理方法、模板和名字空间等概念与使用。** 

   

10. **熟练掌握程序设计思想和基本算法。**