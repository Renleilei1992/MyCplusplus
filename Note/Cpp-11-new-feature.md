C++11 总结
[toc]

---
#### C++11新特性

- 特别常用的如下:
    - auto & decltype 类型推导 
    - nullptr
    - lambda
    - to_string
    - for循环区间遍历
    - 列表初始化
    - thread
    - 条件变量
    - 智能指针
    - atomic
    - 时间chrono

- 参考文献:
- [30分钟了解C++11新特性](https://www.cnblogs.com/mengfanrong/p/5230558.html)
- [《深入理解C++ 11：C++11新特性解析和应用》读书笔记(一)](https://www.cnblogs.com/zc110747/p/5761037.html)
- [C++11特性划分为七大类](https://www.cnblogs.com/mydomain/p/10035418.html)
- [C++11 中值得关注的几大变化 酷壳2011](https://coolshell.cn/articles/5265.html)
- [C++11 新特性总结](https://www.cnblogs.com/George1994/p/6684989.html)
- [c++11 维基百科](https://zh.wikipedia.org/wiki/C%2B%2B11#-.7BA.7Czh-hans:.E5.8F.98.E9.95.BF.E5.8F.82.E6.95.B0.E6.A8.A1.E6.9D.BF.3B_zh-hant:.E4.B8.8D.E5.AE.9A.E9.95.B7.E5.8F.83.E6.95.B8.E6.A8.A1.E6.9D.BF.7D-)

---
###### 1. `nullptr`
- [174_test_nullptr.cpp](https://github.com/Renleilei1992/MyCplusplus/blob/master/Main/174_test_nullptr.cpp)
```c
    int *p1 = nullptr;  // 等价于 int *p1 = 0;
    int *p2 = 0;
    int *p3 = NULL;     // 等价于 int *p3 = 0;
    /*总结: 新标准下建议使用nullptr, 特殊类型的字面值, 可以转换为任意其他的指针类型, 当然其他方式也不算错*/
    
    // 可能会出现二义性的场景:
    void F(int a) {
        cout << a << endl;
    }
    
    void F(int *p) {
        assert(p != NULL);      // will assert, which means nullptr == NULL
        cout << p << endl;
    }
    
    int main() {
        int *p = nullptr;
        int *q = NULL;
        bool bEqual = (p == q); // true
        int a = nullptr;        // c++11 编译失败,无法转型成为int
        F(0);                   // c++98 编译失败, 有二义性, c++11中会调用F(int a)
        F(nullptr);             // c++11 会调用 F(int *p)
        F(NULL);                // call of overloaded ‘F(NULL)’ is ambiguous  编译失败
    }
```
###### 2. `long long`
- [184_test_long_long.cpp](https://github.com/Renleilei1992/MyCplusplus/blob/master/Main/184_test_long_long.cpp)
- `C99`将其引入标准C，`C++11`将其引入标准C++
- 在32位系统上, 一个`long long int`至少保有64位有效比特位
```
    #include <climits>      // #define LLONG_MIN & LLONG_MAX & ULLONG_MAX
    
    long long int lli1 = -900000000000LL;
    unsigned long long int ulli1 = 900000000000000000ULL;
    cout << "lli1: " << lli1 << endl;                       // -900000000000
    cout << "ulli1: " << ulli1 << endl;                     // 900000000000000000
    cout << "LLONG_MIN: " << LLONG_MIN << endl;             // -9223372036854775808
    cout << "LLONG_MAX: " << LLONG_MAX << endl;             // 9223372036854775807
    cout << "ULLONG_MAX: " << ULLONG_MAX << endl;           // 18446744073709551615
```
###### 3. `__func__`
```c
    void Foo() {
        std::cout << __func__ << std::endl;      // Foo()  获得当前函数名字符串的宏(Qt中也可以使用__FUNCTION__)
    }
```
###### 4. 新的字符串字面值
```c
    std::string str1 = R"(The String Data \ Stuff")";   // The String Data \ Stuff"   在括号中得字符串将不再需要转义即可正确展示
```
###### 5. 新的整型(长度不小于64位) `long long/ unsigned long long`   [暂未找到区别]
```c
    long long int lli1 = -900000000000LL;
    unsigned long long int ulli1 = 900000000000000000ULL;
    cout << "lli1: " << lli1 << endl;                       // -900000000000
    cout << "ulli1: " << ulli1 << endl;                     // 900000000000000000
    cout << "LLONG_MIN: " << LLONG_MIN << endl;             // -9223372036854775808
    cout << "LLONG_MAX: " << LLONG_MAX << endl;             // 9223372036854775807
    cout << "ULLONG_MAX: " << ULLONG_MAX << endl;           // 18446744073709551615
```
###### 6. 静态断言 `static_assert`
```
    // 新增的静态断言能在编译器即可返回错误信息
    static_assert(sizeof(b) == sizeof(a), "the paramters of bit_copy must have same width!")
    
    template< class T >
    struct Check
    {
      static_assert( sizeof(int) <= sizeof(T), "T is not big enough!" ) ;
    } ;
```
###### 7. 允许sizeof运算符直接作用在类的成员变量而不依赖对象
```c
    struct SomeType {
        int a;
        char b;
        char data[1000];
    }
    
    cout << sizeof(SomeType::a) << " " << sizeof(SomeType::b) << endl;  // 直接由SomeType型別取得非静态成员的大小，C++03不行。C++11允許
    
    // 初始化:
    SomeType st;
    memset(st.data, 0, sizeof(st.data));            // 原有的写法
    memset(st.data, 0, sizeof(SomeType::data));     // C++11合法
```
###### 8. 继承和重写 `final & override`  
- [186_test_override_final.cpp](https://github.com/Renleilei1992/MyCplusplus/blob/master/Main/186_test_override_final.cpp)
- `final` 关键字用于禁用继承和禁用重写
- `override` 关键字用于提示某个函数重写了基类的虚函数; 强制编译器检查某个函数是否重写基类虚函数(函数名、参数等校验)
```
class Base
{
public:
    virtual void basePrint() = 0;
    virtual void basePrint1() = 0;
    virtual void basePrint2() final { cout << __func__ << " Base: " << endl; }
};

class Split : public Base
{
    // 隔离接口
};

class Derived final : public Split
{
public:
    virtual void basePrint() override { cout << __func__ << " Derived: " << endl; }
    virtual void basePrint1() override { cout << __func__ << " Derived: " << endl; }
//  virtual void basePrint2() override { cout << __func__ << " Derived: " << endl; }        // final会导致此处继承编译出现错误
};

//class Derived1 : public Derived       // cannot derive from ‘final’ base ‘Derived’ in derived type ‘Derived1’
//{
//};

int main()
{
    Derived d1;
    d1.basePrint();         // basePrint Derived:
    d1.basePrint1();        // basePrint1 Derived:
    d1.basePrint2();        // basePrint2 Base:

    return 0;
}

```
###### 9. 使用和禁用对象的默认函数 
- `c++11`允许将某些默认函数定义为删除-以限制其被使用
- 当基类中删除某些默认函数后，其派生类中的对应函数也将相应地被删除[继承]
- [188_test_Non_default.cpp](https://github.com/Renleilei1992/MyCplusplus/blob/master/Main/188_test_Non_default.cpp)
- 简单示例如下：
```
class Base1
{
public:
    Base1() = default;                      // 显式声明需要默认构造函数
    Base1(int x) { cout << x << endl; }
    ~Base1() = default;

    virtual void print() final { cout << "Base1::" << __func__ << endl; }
};

class NonCopyAble
{
public:
    NonCopyAble & operator=(const NonCopyAble&) = delete;   // 禁用赋值运算符
    NonCopyAble(const NonCopyAble&) = delete;               // 禁用拷贝构造函数
    NonCopyAble() = default;
    
    void print() { cout << "NonCopyAble::" << __func__ << endl; }
};

class NonNewAble
{   
public:
    NonNewAble() = default;
    void *operator new(std::size_t) = delete;   // 禁止类使用new申请内存, 此种对象只能生成于stack栈中,无法直接配置于heap堆中
    void print() { cout << "NonNewAble::" << __func__ << endl; }
};

struct NonDouble
{   
    void foo(int i) { cout << "NonDouble::" << __func__ << " i = " << i << endl; }
    void foo(double i) = delete;
};

struct OnlyInt
{
    void foo(int i) { cout << "OnlyInt::" << __func__ << " i = " << i << endl; }
    template<class T> void foo(T) = delete;
};

class Sub/*: public NonCopyAble*/
{
public:
    Sub() {
        cout << "Sub::" << __func__ << endl;
    }
/*  Sub(const Sub& rhs):NonCopyAble(rhs){
        cout << "Sub::" << __func__ << endl;
    }
*/
};

int main()
{
    /* 测试禁止new申请堆内存的类 */
//  NonNewAble *nPtr = new NonNewAble();        // use of deleted function ‘static void* NonNewAble::operator new(std::size_t)’
//  if (nPtr == nullptr) { cout << "it's a nullptr!!" << endl; }
    NonNewAble nObj;
    nObj.print();

    /* 测试禁止拷贝构造的类 */
    NonCopyAble copyObj;
//  NonCopyAble c1(copyObj);    // error: use of deleted function ‘NonCopyAble::NonCopyAble(const NonCopyAble&)’
    copyObj.print();
//  c1.print();

    /* 测试禁止double形参的类 */
    NonDouble ndObj;
    int i = 10;
    double j = 20;
    ndObj.foo(i);
//  ndObj.foo(j);   // error: use of deleted function ‘void NonDouble::foo(double)’

    /* 测试仅使用int形参的类 */
    OnlyInt iObj;
    iObj.foo(i);
//  iObj.foo(j);    // error: use of deleted function ‘void OnlyInt::foo(T) [with T = double]’

    /* 测试删除默认拷贝构造函数之后的继承情形 */
    Sub subObj_1;
    Sub subObj_2(subObj_2);     // error: use of deleted function ‘Sub::Sub(const Sub&)’ [if you public NonCopyAble]

    return 0;
}


```
###### 10. 字符串和数值之间的转换: `std::to_string`; 
- [177_test_to_string.cpp](https://github.com/Renleilei1992/MyCplusplus/blob/master/Main/177_test_to_string.cpp)
```c
    double f1 = 23.43;
    double f2 = 1e-9;
    double f3 = 1e40;
    double f4 = 1e-40;
    double f5 = 123456789;

    std::string f1_str = std::to_string(f1);    // 23.430000
    std::string f2_str = std::to_string(f2);    // 0.000000
    std::string f3_str = std::to_string(f3);    // 10000000000000000303786028427003666890752.000000
    std::string f4_str = std::to_string(f4);    // 0.000000
    std::string f5_str = std::to_string(f5);    // 123456789.000000
```

###### 11. 元组(扩展std::pair) std::tuple & std::make_tuple 
- [178_test_tuple.cpp](https://github.com/Renleilei1992/MyCplusplus/blob/master/Main/178_test_tuple.cpp)
```c
    // 使用方法类似 std::pair 和 std::make_pair, 解决pair多重嵌套的场景
    auto t1 = std::make_tuple("str1", "str2", "str3", 4);       // std::tuple<string, string, string, int>
    for (int i = 0; i < 4; ++i) {
//      cout << __func__ << " t1[" << i << "]: " << std::get<i>(t1) << endl;        // get<1>(t1)   需要常量 constant value 
    }

    // 基于下标的访问
    cout << "t1[0]: " << std::get<0>(t1) << endl;
    cout << "t1[1]: " << std::get<1>(t1) << endl;
    cout << "t1[2]: " << std::get<2>(t1) << endl;
    cout << "t1[3]: " << std::get<3>(t1) << endl;

    auto i = std::get<3>(t1);
    decltype(i) j = i;
    cout << "j/2: " << j/2 << endl;
```

###### 12. using 代替 typedef;
```c
    typedef double dnum;    // 使复杂的类型名字变得简单明了和使用
    using dnum = double;    // c++11可以使用两种方式进行类型别名的更改
```
###### 13. constexpr
- [171_constexpr.cpp](https://github.com/Renleilei1992/MyCplusplus/blob/master/Main/171_constexpr.cpp)
- 1, constexpr 修饰常量表达式 而 const 修饰常量(未区分编译器常量和运行期常量)
- 2, constexpr 修饰的常量表达式限定在了编译期常量,(返回值不一定是编译期常量)
    - constexpr 修饰的函数:
        - 1,如果传入的参数可以在编译时期计算出来,那么这个函数就会产生编译时期的值,
        - 2,如果传入的参数在编译时期不能计算出来,那么constexpr修饰的函数就和普通的函数一致
- 3, 如何确定constexpr修饰的函数是否产生编译时期的值?
    - 可以使用std::array 需要编译器常值才能编译通过的小技巧,这样可以检测是否产生编译期常值
    - 合理使用constexpr修饰常量表达式用以帮助编译器优化代码
```c
    // 场景1:
    int i = 10;         // not ok 将会报错(the value of ‘i’ is not usable in a constant expression), 因为t不是常量
    const int i = 10;   // ok
    constexpr int j = i + 10;
    /* 总结: 如果认定变量时一个常量表达式, 那么可以将其声明为 constexpr 类型 */
    
    // 场景2:
    #include <iostream>
    #include <array>
    using namespace std;
    
    constexpr int foo(int i)
    {
        return i + 5;
    }

    int main()
    {
        cout << __func__ << endl;
        int i = 10;
        std::array<int, foo(5)> arr;        // ok
    
        foo(i);                             // ok
    
        // But..
        std::array<int, foo(i)> arr1;       // Error: ‘int i’ is not const
        return 0;
    }

```
###### 14. 类型推导 ***`auto`*** & `decltype`; 
- auto让编译器通过初始值推算变量的类型; decltype 可以获取变量类型
```c
    auto a = 1;
    std::vector<int> vec_01 = {1, 2, 3};
    for (auto iVec : vec_01) { /*...*/ }      // auto推导出iVec的类型为 int
    
    decltype(a) b = 2;  // 获取到变量a的类型为int
    
    // 编译器语义分析根据模板函数std::bind 对特定引用返回的类型
    auto f1 = std::bind([](int i, int j) { cout << __func__ << " i+j= " << i+j << endl;}, _1, _2);
    f1(99, 98);     // operator() i+j= 197
```
###### 15. 智能指针: `unique_ptr` `shared_ptr` `weak_ptr`
- [148_smart_pointer.cpp](https://github.com/Renleilei1992/MyCplusplus/blob/master/Main/148_smart_pointer.cpp)
- 关于智能指针的线程安全性 (引用计数线程不安全)
```c
    // 基础用法
    unique_ptr<int> iPtr1(new int(1));
    unique_ptr<int> iPtr2 = iPtr1;                  // error, 不能被复制
    unique_ptr<int> iPtr3 = std::move(iPtr1);       // ok   iPtr1 == nullptr
    iPtr3.reset();                                  // 显式内存释放 iPtr3 == nullptr
    
    shared_ptr<int> sPtr1(new int(2));      // 引用计数法实现GC (全局动态资源管理)
    shared_ptr<int> sPtr2 = sPtr1;          // ok, 引用计数+1
    weak_ptr<int> wPtr = sPtr1;             // ok, 引用计数不增加
    
    cout << "sPtr1: " << *sPtr1 << endl;    // sPtr1: 2
    cout << "sPtr2: " << *sPtr2 << endl;    // sPtr2: 2
    cout << "wPtr1: " << *wPtr << endl;     // wPtr1: 2
    
    sPtr1.reset();                              // 引用计数-1, 该内存区域不释放
    cout << "sPtr1: " << *sPtr1 << endl;        // Segmentation fault
    cout << "sPtr2: " << *sPtr2 << endl;        // sPtr2: 2
    cout << "wPtr1: " << *wPtr.lock() << endl;  // wPtr1: 2
    
    sPtr2.reset();                          // 引用计数-1，该内存区域被释放??
    if(!wPtr.expired()) { cout << "wp is not a nullptr!!" << endl; }        // 更推荐如此判断
    if(wPtr.lock() == nullptr) { cout << "wp is nullptr!!" <<endl; }        // wPtr is nullptr -多一次引用计数
```

- 自己实现 `shared_ptr`
```
#ifndef __SHARED_PTR_
#define __SHARED_PTR_

template <typename T>
class shared_ptr {
public:
    // 指针构造函数：保存指针，初始化引用计数为1
    shared_ptr(T* p) : count(new int(1)), _ptr(p) {}
    // 拷贝构造函数：保存指针，保存引用计数并+1
    shared_ptr(shared_ptr<T>& other) : count(&(++*other.count)), _ptr(other._ptr) {}
    // 重载->操作符
    T* operator->() { return _ptr; }
    // 重载*操作符
    T& operator*() { return *_ptr; }
    // 重载赋值运算符：自身引用计数-1，并检查是否delete
    // 保存其他指针，保存引用计数并+1
    shared_ptr<T>& operator=(shared_ptr<T>& other)
    {
        ++*other.count;
        if (this->_ptr && 0 == --*this->count)
        {
            delete count;
            delete _ptr;
            count = nullptr;
            _ptr = nullptr;
        }
        this->_ptr = other._ptr;
        this->count = other.count;
        return *this;
    }
    // 引用计数-1，并检查是否delete
    ~shared_ptr()
    {
        if (--*count == 0)
        {
            delete count;
            delete _ptr;
            count = nullptr;
            _ptr = nullptr;
        }
    }
    // 返回当前引用计数
    int getRef() { return *count; }
private:
    // 引用计数必须为指针，这样多个对象共享同一个引用计数
    int* count;
    // 保存目标指针
    T* _ptr;
};
#endif
```

- [shared_ptr/weak_ptr示例 一篇比较好的示例](https://blog.csdn.net/craftsman1970/article/details/80889084)
- 循环引用问题: [210_test_shared_ptr_loopRef.cpp](https://github.com/Renleilei1992/MyCplusplus/blob/master/Main/210_test_shared_ptr_loopRef.cpp)
```
class A;
class B;
class A {
public:
//  std::shared_ptr<B> pointer;     // 如果两个均为 shared_ptr 强引用会造成循环引用，两个引用计数均为2, 无法正确析构
    std::weak_ptr<B> pointer;       // 如果两个类中其中一个为 weak_ptr 弱引用, 不增加其引用计数
    ~A() {
        std::cout << "A 被销毁" << std::endl;
    }
};
class B {
public:
    std::shared_ptr<A> pointer;
    ~B() {
        std::cout << "B 被销毁" << std::endl;
    }
};
int main() {
    std::shared_ptr<A> a = std::make_shared<A>();
    std::shared_ptr<B> b = std::make_shared<B>();
    a->pointer = b;
    b->pointer = a;
    return 0;
}


// 或者 [动态内存与智能指针](https://blog.csdn.net/river_lethe/article/details/78733914)
class A
{
public:
    shared_ptr<A> pre;
    shared_ptr<A> next;
    ~A()
    {
        cout << "Destructed." << endl;
    }
};

int main()
{
    //一个作用域
    {
        shared_ptr<A> sp_a1(new A),sp_a2(new A);
        sp_a1->next = sp_a2;
        sp_a2->pre = sp_a1;
    }
    //我们期望在离开这个作用域之后，sp_a1和sp_a2会释放它们控制的内存
    return 0;
}
```

###### 16. 多线程及互斥同步
    - 1, c++11新增了四种锁(互斥对象): 
        - (1) std::mutex 普通互斥锁; 
        - (2) std::timed_mutex 带有超时机制的互斥锁; 
        - (3) std::recursive_mutex 允许被同一线程递归的lock和unlock锁; (递归类的锁单线程都是可以*重入*的)
        - (4) std::recursive_timed_mutex 超时机制; (递归类的锁单线程都是可以*重入*的)
    - 2, c++ 使用标准库提供的互斥对象管理类模板: 
        - (1)std::lock_guard; 
        - (2)**std::unique_lock**; 
        - (3)std::shared_lock(c++14);
    - 3, lock_guard 与 unique_lock 其实内部构造一致, unique_lock 更为灵活(可以指定加锁策略), 均可以指定构造时是否加锁
    - 4, 互斥对象管理类模板的4中加锁策略: 
        - (1)默认 请求锁,阻塞当前线程直至成功获得锁; 
        - (2)std::defer_lock 不请求锁; // 举例: std::unique_lock<std::mutex> lck(cMutex, std::defer_lock);
        - (3)std::try_to_lock 尝试请求锁,但不阻塞线程,锁不可用时也会立即返回; 
        - (4)std::adopt_lock 假使当前线程已经获得互斥对象的所有权, 所以不再请求锁;
    - 5, **std::condition_variable**
        ```
            // **条件变量配合互斥锁** 非常好的组合
            // 1, 作用域开始, 构造函数中将会调用 m_waitConMutex->lock()
            // 2, 作用域结束会析构lock, 析构自动调用m_waitConMutex->unlock()
            {
                std::unique_lock<std::mutex> lock(m_waitConMutex);
                std::condition_variable		m_waitCond;
                std::cv_status status = m_waitCond.wait_for(lock, realTick);    // 将会阻塞realTick时间段
            }
        ```
###### 17. 条件变量 condition_variable
- [193_test_condition_variable.cpp](https://github.com/Renleilei1992/MyCplusplus/blob/master/Main/193_test_condition_variable.cpp)
- [194_test_condition_variable_official.cpp](https://github.com/Renleilei1992/MyCplusplus/blob/master/Main/194_test_condition_variable_official.cpp)
- [195_test_cv_notify.cpp](https://github.com/Renleilei1992/MyCplusplus/blob/master/Main/195_test_cv_notify.cpp)
- 用于阻塞一个线程或者同时阻塞多个线程,直至另一线程修改共享变量(**条件**)并通知;
- 有意修改变量的线程必须:(即使变量是原子的,也必须在互斥条件下修改它,以正确地通知修改到等待的线程)
    - 获得 `std::mutex` (典型地通过 `std::lock_guard` 或者 `std::unique_lock`模板)
    - 在持有锁的时候进行修改
    - 在`std::condition_variable` 上执行 `notify_one` 或者 `notify_all`
- 准备阻塞在条件变量等待的线程必须:
    - 获得`std::unique_lock<std::mutex>`,互斥量用于保护共享变量
    - 执行`wait`、`wait_for`、`wait_until` 等待操作自动释放互斥锁(`unique_lock`会在`wait`的时候自动释放)，阻塞当前线程
    - 条件变量被通知时, 时限消失或者[虚假唤醒](https://en.wikipedia.org/wiki/Spurious_wakeup)发生时,线程被唤醒,且自动获得互斥锁,之后线程将检查条件,若唤醒是虚假唤醒,则将继续等待
- 条件变量的通知
    - 使用 `notify_one()` 或者 `notify_all()` 进行通知
    - `notify_one` 会随机对等待条件变量的线程中的一个线程进行通知
    - `notify_all` 会对等待条件变量的所有线程进行通知(非同时, 队列通知, 等待一个线程释放锁之后另外的线程才会获取到锁)
    ```c
    void waits(int idx) {
    //  {   // 这个花括号是为了测试此 lck 锁的生命周期, 如果析构之前睡眠, 会持续持有该锁, 如果析构之后睡眠, 则锁已经释放, 其他线程可以拿到该锁
        std::unique_lock<std::mutex> lck(mtx);
        cv.wait(lck, []{return i == 1;});       // wait操作会解锁lck锁, 阻塞当前线程
    //  }
        std::this_thread::sleep_for(std::chrono::seconds(1));   // 此行代码可以测试得出notify_all()其实是队列唤醒, 因为此处睡眠1s依旧持有mtx锁, 仅当作用域结束, lck析构后队列中的其它线程才会获取到锁并执行
    }
    ```
- 注意: *条件变量只能与 `std::unique_lock<std::mutex>` 一同使用*
- 使用示例:
```c
    std::condition_variable cv;
    std::mutex mtx;
    int i = 0;

    /* std::condition_variable::wait()的示例 */
    void waits() {
    	std::unique_lock<std::mutex> lk(mtx);
    	cv.wait(lk, []{return i == 1;});
    }

    /* std::condition_variable::wait_for()的示例 */
    void waitsFor(int idx) {
    	std::unique_lock<std::mutex> lck(mtx);
    	cv.wait_for(lck, std::chrono::milliseconds(100));       // 方式1: 等待100ms的超时时间
    	
    	if (cv.wait_for(lck, idx*100ms, []{return i == 1;})) {  // 方式2: 超时时间设定之后也要检测条件是否满足
    		// finished waiting...
    	} else {
    		// time out...
    	}
    }
    
    // 注意修改变量的时候要在互斥条件下修改, 作用域结束自动释放锁后再通知到等待的线程
    {
        std::lock_guard<std::mutex> lk(cv_m);
        i = 1;
    }
    cv.notify_one();    // 通知到一个等待的线程
    cv.notify_all();    // 通知到所有等待的线程
```

- 一个生产者消费者模型
```
    #include <iostream>
    #include <thread>				// std::thread  std::this_thread
    #include <condition_variable>	// std::condition_variable
    #include <memory>				// std::shared_ptr std::unique_ptr std::weak_ptr std::unique_lock & std::lock_guard 
    #include <queue>				// std::queue
    #include <chrono>				// std::chrono::seconds(5)
    #include <atomic>
    
    #define _MAX_QUEUE_SIZE 20
    
    using namespace std;
    
    std::queue<int>	q;
    std::mutex mtx;
    std::condition_variable producer_cv, consumer_cv;
    
    std::atomic<int> atom_NUM = { 100 };
    std::atomic<bool> atom_bool = { true };
    
    bool getRetVal() {
    	return atom_bool ? true : false;
    }
    
    void consumerFunc()
    {
    	cout << __func__ << " begin consume!!" << endl;
    	while(getRetVal()) {
    		std::this_thread::sleep_for(std::chrono::seconds(3));
    		std::unique_lock<mutex>	lck(mtx);
    		while(q.size() == 0) {  // 避免虚假唤醒
    			consumer_cv.wait(lck);			// 等待锁至while条件不满足
    		}
    
    		q.pop();
    		cout << __func__ << "::consumer id: " << std::this_thread::get_id() << " q.size: " << q.size() << "  当前任务队列头部任务编号: " << q.front() << endl;
    
    		producer_cv.notify_all();
    	}
    }
    
    void producerFunc()
    {
    	cout << __func__ << " begin produce!!" << endl;
    	while(getRetVal()) {
    		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    		std::unique_lock<mutex> lck(mtx);
    		while(q.size() == _MAX_QUEUE_SIZE) {
    			producer_cv.wait(lck);			// 等待锁至while条件不满足
    		}
    		
    		q.push(atom_NUM);
    		atom_NUM++;
    		cout << __func__ << "::producer id: " << std::this_thread::get_id() << " q.size: " << q.size() << " 当前任务队列尾部任务编号: " << q.back() << endl;
    		
    		consumer_cv.notify_all();
    	}
    }
    
    
    int main()
    {
    	std::thread t1(producerFunc);
    	std::thread t2(consumerFunc);
    	std::thread t3(consumerFunc);
    
    	std::vector<thread> vec;
    	vec.emplace_back(std::move(t1));
    	vec.emplace_back(std::move(t2));
    	vec.emplace_back(std::move(t3));
    	
    	std::this_thread::sleep_for(std::chrono::seconds(20));
    	atom_bool = false;
    
    	for (auto &iVec : vec) {
    		if (iVec.joinable()) {
    			cout << "id: " << iVec.get_id();
    			iVec.join();
    			cout << "join!!" << endl;
    		}
    	}
    
    	return 0;
    }
```

###### 18. `<atomic>` 原子类型及原子操作
- [175_test_atomic.cpp](https://github.com/Renleilei1992/MyCplusplus/blob/master/Main/175_test_atomic.cpp)
- [C++11 并发指南六( <atomic> 类型详解二 std::atomic )](https://www.cnblogs.com/haippy/p/3301408.html)
- 关于`atomic`原子变量的线程安全性?
- 多线程同步的可见性（原子性、有序性、可见性）
- 初始化方法:
```c
    std::atomic<bool> ready(false);
    std::atomic<bool> ready = { false };    // C++11列表初始化
```

###### 19. 列表初始化
- 普通对象列表初始化(`C++11`使用花括号来进行列表初始化) [`C++` Primer page 39]
```c
    int i = 0;
    int i = { 0 };      // 列表初始化
    int i{0};           // 列表初始化
    int i(0);
```
- vector 对象的列表初始化
```c
        std::vector<int> vec_01 = {1, 2, 3};    // 列表初始化
        std::vector<int> vec_02{1, 2, 3};       // 列表初始化
        std::vector<int> vec_03({1, 2, 3});     // 列表初始化
        std::vector<int> vec_04{10, 1};         // 列表初始化, 两个元素分别为10 和 1, 注意区别 vec_08
        
        // 注意下面的场景
        std::vector<std::string> vec_05{"hello world!"};    // 列表初始化
        std::vector<std::string> vec_06("hello world!");    // 非列表初始化, 不能使用字面值构建对象
        std::vector<std::string> vec_07{10};                // 非列表初始化, 代表有10个元素
        std::vector<std::string> vec_08{10, "hello world!"};    // 非列表初始化, 有10个hello world字符串的vector对象
        
```
###### 20. 算术运算
- 除法运算
```c
    int val = 23 / 6;       // val = 3 小数部分会被直接舍弃, 正负性遵循正常法则, 同则为正, 反则为负
```
- 取余运算
```c
    it val = 8 % 3;         // val = 2 此处注意除数和被除数均为整型, 结果的正负性与被除数相同
```

###### 21. 范围for循环语句 <区间遍历(迭代)>
```c
    std::vector<int> vec_01 = {1, 2, 3};

    // 1, 配合auto进行区间遍历(此处的iVec并不是迭代器类型,只是单纯的int类型)
    for (auto iVec : vec_01) {      // 也可以使用 auto &i
        cout << iVec << endl;
    }

    // 2, 引用区间遍历可以进行数据更改，避免拷贝
    for (int& i : vec_01) {
        i++;
    }

    // 3, 拷贝式遍历,其实同auto那个
    for (int i : vec_01) {
        cout << i << endl;
    }

    // 4, 迭代器遍历
    std::vector<int>::iterator it = vec_01.begin();
    for (it; it != vec_01.end(); ++it) {
        cout << *it << endl;
    }
    
    // 使用map看得更清楚一些
    std::map<int, string> map_01;
    map_01.insert(make_pair<int, string>(1, "hello world1!!"));
    map_01.insert(make_pair<int, string>(2, "hello world2!!"));
    map_01.insert(make_pair<int, string>(3, "hello world3!!"));

    for (auto iMap : map_01) {
        cout << iMap.first << " " << iMap.second << endl;
    }

    for (pair<int, string> iPair : map_01) {
        cout << iPair.first << " " << iPair.second << endl;
    }

```
###### 22. `std::cbegin & std::cend`
```c
    auto it1 = Container.begin();       // it1 is Container<T>::iterator
    auto it2 = Container.cbegin();      // it2 is Container<T>::const_iterator  // 不可用于修改元素
```
###### 23. `std::begin & std::end`
- 非成员函数的 `begin()` 和 `end()`, c++11中使用了initializer_list初始化
```c
    std::vector<int> vec_01 = {1, 2, 3};
    for_each(std::begin(vec_01), std::end(vec_01), [](int p){ cout << p << endl; });
```
###### 24. `initializer_list`
- 当初始化的时候使用的是大括号初始化, 被自动构造。包括函数调用时和复制
- 当设计到for(initializer : list), list被自动构造成initializer_list对象
- 总之: 考虑到C++11新增的通用初始化语法, 使用***大括号{}***而不是()来调用类的构造函数
- 另: 此模板类一般是容器或者默认构造函数会使用, 自己主动使用的场景很少
- 另: initializer_list的迭代器是const类型,不能修改其中的值
```c
    // 一个应用场景示例
    #include <iostream>
    #include <initializer_list>
    #include <algorithm>        // for_each
    
    using namespace std;
    
    double sum(std::initializer_list<double> i1);
    double average(const std::initializer_list<double> & ri1);
    
    int main()
    {
        cout << "program begin!!" << endl;
        cout << "List 1: sum = " << sum({1, 2, 3, 4}) << endl;
        return 0;
    }
    
    double sum(std::initializer_list<double> i1)
    {
        double tot = 0;
    /*
        for (auto p = i1.begin(); p != i1.end(); p++) {
            tot += *p;
        }
    */
    
        for_each(std::begin(i1), std::end(i1), [&](int p){
            tot += p;
        });
    
        return tot;
    }

```
###### 25. `std::vector<T,allocator>::emplace_back`
- `emplace_back`对比`push_back`有如下优势 （延申至 `emplace`）
    - 效率高
    - 减少不必要的操作(额外复制和移动操作)
    - 原因:
        - push_back: 创建一个局部临时对象(构造), 再将其压入容器内(移动构造)
        - emplace_back: 使用参数在容器管理的内存空间内直接构造(构造)   ------> 推荐使用
- [206_test_emplace.cpp](https://github.com/Renleilei1992/MyCplusplus/blob/master/Main/206_test_emplace.cpp)
```c
    std::vector<std::thread> threadVec;
    std::thread t1(func, 10);
    threadVec.push_back(t1);                        // 不合法
    threadVec.emplace_back(std::move(t1));          // c++11推荐使用
    threadVec.emplace_back(std::thread(func, 10));  // 效率最高, 仅有一次构造
    
    // 206.cpp 区别代码:
    cout << "-----------------------> emplace_back begin ------------------" << endl;
    vec_1.emplace_back(std::string("hello world!"));
    vec_1.emplace_back(std::string("hello world!"));
    cout << "-----------------------> emplace_back end ------------------" << endl;

    cout << endl;

    cout << "-----------------------> push_back begin ------------------" << endl;
    vec_2.push_back(std::string("hello world!"));
    vec_2.push_back(std::string("hello world!"));
    cout << "-----------------------> push_back end ------------------" << endl;

    
    // 206.cpp 执行结果:
    -----------------------> emplace_back begin ------------------
    Base::Base----> construction be called! 
    Base::Base----> construction be called! 
    Base::Base----> copy construction be called! 
    Base::~Base----> deconstruction be called! 
    -----------------------> emplace_back end ------------------
    
    -----------------------> push_back begin ------------------
    Base::Base----> construction be called! 
    Base::Base----> move construction be called! 
    Base::~Base----> deconstruction be called! 
    Base::Base----> construction be called! 
    Base::Base----> move construction be called! 
    Base::Base----> copy construction be called! 
    Base::~Base----> deconstruction be called! 
    Base::~Base----> deconstruction be called! 
    -----------------------> push_back end ------------------


```

###### 26. lambda 表达式
- [C++之Lambda表达式 参考文档](https://www.cnblogs.com/jimodetiantang/p/9016826.html)
- lambda大家都用得比较熟悉,不再赘述
```
// lambda函数的语法定义：（采用了追踪返回类型的方式声明其返回值)
// [capture](parameters) mutable -> return-type{statement;}
// []，捕捉列表，捕捉上下文中的变量以供lambda函数使用
/*[]    表示    空捕捉
 *[=]   表示值  传递方式捕捉所有父作用域的变量(包括this)
 *[&]   表示引用传递方式捕捉所有父作用域的变量(包括this)
 *[var] 表示值  传递方式捕捉变量var
 *[&var]表示引用传递方式捕捉变量var  
 *[this]表示值  传递方式捕捉当前this指针 (this。函数体内可以使用Lambda所在类中的成员变量。)
 *其它组合形式：
 * */
```

###### 27. 引入的时间标准库 `std::chrono`
- [214_test_chrono.cpp](https://github.com/Renleilei1992/MyCplusplus/blob/master/Main/214_test_chrono.cpp)
- 精度: 
- 时钟: `high_resolution_clock` `system_clock` `steady_clock`
    - 主要使用 `high_resolution_clock` 时钟的 `now()` 方法;
    ```
    std::chrono::high_resolution_clock::time_point pt1 = std::chrono::high_resolution_clock::now();
    auto pt2 = std::chrono::high_resolution_clock::now();
    
    // 常用来计算一段时间间隔, 比如:
    auto start = std::chrono::high_resolution_clock::now();
    // do something consume time.
    auto end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double, std::milli> elapsed = end - start;
    cout << "Waited: " << elapsed.count() << " ms\n";
    ```
    - `system_clock`：从系统获取的时钟；
    - `steady_clock`：不能被修改的时钟；
    - `high_resolution_clock`：高精度时钟，实际上是 `system_clock` 或者 `steady_clock` 的别名
- 时间段：`duration`
- 正常使用示例:
```
    using namespace std::chrono;
    using std::chrono::system_clock;

    // 1, now()         是当前时间 time_point
    // 2, to_time_t()   time_point转换为time_t秒
    // 3, from_time_t() 从time_t转换为time_point
    std::chrono::duration<int, std::ratio<60*60*24>> one_day(1);

    system_clock::time_point today = system_clock::now();
    system_clock::time_point tomorrow = today + one_day;

    std::time_t tt;
    tt = system_clock::to_time_t(today);
    cout << __func__ << ":: today is: " << ctime(&tt) << endl;

    tt = system_clock::to_time_t(tomorrow);
    cout << __func__ << ":: tomorrow will be: " << ctime(&tt) << endl;

```
###### 28. 强类型 `enum`
- [179_test_enum.cpp](https://github.com/Renleilei1992/MyCplusplus/blob/master/Main/179_test_enum.cpp)
- 1, `C++03`中枚举类型不是类型安全的,枚举类型被视为整数,两种枚举类型可以进行比较; `C++11`引入枚举类,此种枚举类型安全,不能隐式转换为整数,也无法与整数值进行比较,(`MyEnum_Val4 == 101` 会触发编译错误);
- 2, 枚举类默认类型为int, 倘若指定其他类型: `enum class MyEnum2 : unsigned int`
- 3, `C++11`允许给传统的枚举指定类型:` enum MyEnum3 : unsigned long`
- 4, 强作用域 `MyEnum::MyEnum_Val1`
- 5, `enum class` 与 `enum struct` 没有任何区别
- 6, `enum` 默认大小为4字节, 可以指定其大小为8字节
- 7, 目的可以用来节省内存空间和统一不同操作系统、应用不同版本的枚举值兼容
```
enum class MyEnum
{
    MyEnum_Val1,
    MyEnum_Val2,
    MyEnum_Val3 = 100,
    MyEnum_Val4 /* = 101 */,
};

enum Type : int         // 指定该枚举类型大小为4字节
{
    Type_General,
    Type_Light,
};

enum class SizeEnum01 : long long       // 指定该枚举类型大小为8个字节
{
    SizeEnum01_A = 0x123456789,
    SizeEnum01_B
};


int main()
{
//  cout << "MyEnum_Val1: " << MyEnum::MyEnum_Val1 << endl;     // 需要重载 << 
//  if (MyEnum::MyEnum_Val3 == 100) {                           // no match for ‘operator==’ (operand types are ‘MyEnum’ and ‘int’)
//      cout << "MyEnum_Val3 == 100!!" << endl;
//  }

    MyEnum e1 = MyEnum::MyEnum_Val3;

    switch(e1) {
    case MyEnum::MyEnum_Val1:
        cout << "MyEnum_Val1 match!!" << endl;
        break;
    case MyEnum::MyEnum_Val2:
        cout << "MyEnum_Val2 match!!" << endl;
        break;
    case MyEnum::MyEnum_Val3:
        cout << "MyEnum_Val3 match!!" << endl;                  // MyEnum_Val3 match!!
        break;
    case MyEnum::MyEnum_Val4:
        cout << "MyEnum_Val4 match!!" << endl;
        break;
    default:
        cout << "no match!!" << endl;
        break;
    }

    Type t1 = Type_General;
    Type t2 = Type::Type_Light;

    cout << "Type_General: " << t1 << endl;                     // 0

    cout << "MyEnum size: " << sizeof(MyEnum) << endl;          // 4
    cout << "Type enum size: " << sizeof(Type) << endl;         // 4
    cout << "SizeEnum01 size: " << sizeof(SizeEnum01) << endl;  // 8

    return 0;
}

    // 枚举类型前后对比
    // 旧版例子:
    enum LightColor {
        red,
        green,
        blue
    };
    enum PaintColor {
        red,
        yellow,
        blue
    }
    // red 和 blue 重复定义
    
    // 传统解决办法:
    namespace Light {
        enum color {
            red,
            green,
            blue
        }
    }
    
    namespace Paint {
        enum color {
            red,
            yellow,
            blue
        }
    }
    
    Light::Color lc = Light::red;
    Paint::Color Pc = Paint::red;
    
    // C++11解决方式:
    enum class ELight {
        red,
        green,
        blue
    };
    
    enum class EPaint {
        red,
        yellow,
        blue
    };
    
    ELight elc = Elight::read;
    EPaint epc = EPaint::read;

```
###### 29. 扩展union(允许含有定义了构造函数和拷贝构造函数的类类型成员)
- 参考 C++ primer 第五版 749页 19.6
- 略

###### 30. 标准库mem_fn类模板(函数适配器)
- [196_test_mem_fn.cpp](https://github.com/Renleilei1992/MyCplusplus/blob/master/Main/196_test_mem_fn.cpp)
- 可以用来将成员函数转为函数对象, `C++98`前身是`mem_fun` 与 `mem_fun_ref`
- 建议使用`std::bind`, 包含全部功能且更为通用
- 简单使用示例:
```
struct Foo {
    Foo(int val):data{val} {}
    bool compare(const Foo& t) const {
        return (data < t.data);
    }

    int data;
};

class FooPrint {
public:
    void print() { cout << __func__ << "::data = " << data << endl; }
    //void print(int i) { cout << __func__ << "::data = " << data << " i = " << i << endl; }

    int data{100};
};

// 把成员函数转为函数对象，使用对象指针或对象(引用)来进行绑定
void func01()
{
    std::vector<Foo> fv{1, 6, 3, 2, 8};
    for (auto ivec : fv) { cout << ivec.data; }
    cout << endl;

    // 多种方法可以进行排序

    // 普通方法1: 需要声明一个比较函数
//  sort(fv.begin(), fv.end(), compare);

    // 普通方法2: 也可以使用匿名函数进行比较
//  sort(fv.begin(), fv.end(), [](const Foo& f1, const Foo& f2){ return f1.compare(f2); });

    // 普通方法3: 使用C++11的function模板生成可以调用的对象
//  function<bool(const Foo&, const Foo&)> fcomp = &Foo::compare;
//  sort(fv.begin(), fv.end(), fcomp);

    // 普通方法4: 使用C++11的mem_fn生成调用对象
    sort(fv.begin(), fv.end(), mem_fn(&Foo::compare));
    for (auto ivec : fv) { cout << ivec.data; }
    cout << endl;
}


// 主要应用场景是配合for_each使用
void func02()
{
    cout << __func__ << "::obj for_each..." << endl;
    std::vector<FooPrint *> fpv;
    fpv.push_back(new FooPrint());
    fpv.push_back(new FooPrint());
    fpv.push_back(new FooPrint());
    fpv.push_back(new FooPrint());
    fpv.push_back(new FooPrint());

    for_each(fpv.begin(), fpv.end(), mem_fn(&FooPrint::print));

    for_each(fpv.begin(), fpv.end(), [&](FooPrint* fp){
        delete fp;
        fp = nullptr;
    });

    cout << __func__ << "::obj for_each..." << endl;
    std::vector<FooPrint> fv;
    fv.push_back(FooPrint());
    fv.push_back(FooPrint());
    fv.push_back(FooPrint());
    fv.push_back(FooPrint());
    fv.push_back(FooPrint());

    for_each(fv.begin(), fv.end(), mem_fn(&FooPrint::print));
}

```
###### 31. 随机数库 `<random>`
- `C++11`提供了标准随机数库
- [197_test_random.cpp](https://github.com/Renleilei1992/MyCplusplus/blob/master/Main/197_test_random.cpp)
- 简单使用示例:
```
    cout << __func__ << " be called! random number below: " << endl;
    std::default_random_engine eng;
    cout << "随机数引擎 最小值: " << eng.min() << endl;
    cout << "随机数引擎 最大值: " << eng.max() << endl;
    for (int i = 0; i < 10; ++i) {
        cout << "随机数引擎(无种子): " << i << ": " << eng() << endl;
    }
    
    // https://zh.cppreference.com/w/cpp/numeric/random 推荐用法
    std::random_device r;   // 以随机值播种[使用硬件熵源的非确定随机数生成器]
    
    // 选择 1~6 之间的随机数
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(1, 6);
    int mean = uniform_dist(e1);
    std::cout << "随机数引擎根据硬件熵种子得到的1~6之间的随机数: " << mean << endl;

    // 使用种子后的10个随机数
    for (int i = 0; i < 10; ++i) {
        cout << "随机数引擎(有种子): " << i << ": " << e1() << endl;
    }

```
###### 32. 继承的构造函数
- `c++11`提供了继承构造函数的简单写法
- [198_test_inherit.cpp](https://github.com/Renleilei1992/MyCplusplus/blob/master/Main/198_test_inherit.cpp)
- 注意多重继承可能引发的编译错误
- 简单使用示例:
```
    class Base
    {
    public:
        Base() = default;
        Base(int x) :m_x(x), m_y(0){}
        Base(int x, int y) :m_x(x), m_y(y){}
    public:
        int m_x = 0;
        int m_y = 0;
    };
    
    class Base_1
    {
    public:
        Base_1() = default;
        Base_1(int x) :m_valX(x), m_valY(0){}
        Base_1(int x, int y) :m_valX(x), m_valY(y){}
    public:
        int m_valX = 0;
        int m_valY = 0;
    };
    
    // 如果需要继承基类的所有构造函数 原有写法:
    class Sub : public Base
    {
    public:
        Sub():Base(){}
        Sub(int x) :Base(x){}
        Sub(int x, int y) :Base(x, y){}
    };
    
    // c++11 直接使用using可以完美继承
    class Sub_1 : public Base
    {
    public:
        using Base::Base;   // 一行代码即可实现完整继承到基类的所有构造函数, 不再和Sub类中的方法一样重复编写
    };
    
    // 坑: 多重继承
    class Sub_2 : public Base, public Base_1
    {
    public:
        using Base::Base;
        using Base_1::Base_1;
        
        // 解决编译错误 conflicts with version inherited
        // 显式调用基类的构造函数, 以避免二义性
        Sub_1(int x):Base(x), Base_1(x){}
        Sub_1(int x, int y):Base(x, y), Base_1(x, y){}
    };

```
###### 33. sizeof...运算符 (附带了c++11新特性中的可变参数模板使用 variadic template)
- `c++11`提供了此运算符用于查看形参包中的元素数量
- [199_test_sizeof.cpp](https://github.com/Renleilei1992/MyCplusplus/blob/master/Main/199_test_sizeof.cpp)
- 简单示例:
```
    template<typename T>
    void funcImpl(const T& s) {
        cout << s;
    }
    
    template<typename T,typename...Args>
    void funcImpl(const T& s, Args...args) {
        funcImpl(s);
        funcImpl(args...);
    }
    
    template<typename...Args>
    void funcImpl_1(Args...args) {
        const int arg_count = sizeof...(args);
        if (arg_count < 2 || arg_count > 5) {
            cout << __func__ << "::Arg count error! arg_count: " << arg_count << endl;
            return;
        }
    
        cout << __func__ << ": ";
        funcImpl(args...);
        cout << endl;
    }
    
    int main()
    {
        int i = 2019;
        int j = 2020;
        funcImpl_1("hello");
        funcImpl_1("hello", " world");
        funcImpl_1("hello", " world", "!");
        funcImpl_1("hello", " world", "! ", i);
        funcImpl_1("hello", " world", "!", " hello ", j);
        funcImpl_1("hello", " world", "!", " hello", " C", "++", "!");
    
        return 0;
    }
```
###### 34. bitset 的一部分新特性
- `c++11`对`bitset`新增了一部分操作, 它本身并不是`c++11`的新内容
- [200_test_bitset.cpp](https://github.com/Renleilei1992/MyCplusplus/blob/master/Main/200_test_bitset.cpp)
- `c++11`提供了3个实用的方法操作`bitset`
- 简单使用示例:
```
    bitset<4> t1(0x02);
    bitset<6> t2(0x3f);
    bitset<8> t3(0x00);
    cout << "t1: " << t1.to_string() << " t2: " << t2.to_string() << " t3: " << t3.to_string() << endl;

    // 测试是否存在1
    cout << "any?? " << t1.any() << " " << t2.any() << " " << t3.any() << endl;
    // 测试是否都是1
    cout << "all?? " << t1.all() << " " << t2.all() << " " << t3.all() << endl;
    // 测试是否没有1
    cout << "none?? " << t1.none() << " " << t2.none() << " " << t3.none() << endl;
    
    // 输出结果:
    t1: 0010 t2: 111111 t3: 00000000
    any?? 1 1 0
    all?? 0 1 0
    none?? 0 0 1

```
###### 35. 正则库 `std::regex`
- `C++11` 引入了标准的正则库 `<regex>`
- [201_test_regex.cpp](https://github.com/Renleilei1992/MyCplusplus/blob/master/Main/201_test_regex.cpp)
- 简单使用示例:
```
    std::string s = "Some people, when confronted with a problem, think "
                      "\"I know, I'll use regular expressions.\" "
                      "Now, they have two problems.";

    // 匹配
    void regex_match(string str)
    {   
        std::regex word_regex("(\\w+)");
        auto words_begin = std::sregex_iterator(str.begin(), str.end(), word_regex);
        auto words_end = std::sregex_iterator();
        
        std::cout << __func__ << "::Found: " << std::distance(words_begin, words_end) << " words\n";
        
        // 找到超过6个字符的单词
        const int N = 6;
        cout << "Words longer than " << N << " characters:\n";
        for(std::sregex_iterator iter = words_begin; iter != words_end; ++iter) {
            std::smatch match = *iter;
            std::string match_str = match.str();
            if (match_str.size() > N) {
                cout << " " << match_str << endl;
            }
        }
    }
    
    // 查找
    void regex_search(string str)
    {
        cout << str << endl;
        std::regex self_regex("REGULAR EXPRESSIONS", std::regex_constants::ECMAScript | std::regex_constants::icase);
        if (std::regex_search(str, self_regex)) {
            std::cout << "Text contains the phrase 'regular expressions'\n";
        }
    }
    
    // 替换
    void regex_replace(string str)
    {
        // 超过6个字符的单词加上中括号
        std::regex long_word_regex("(\\w{7,})");
        std::string new_s = std::regex_replace(str, long_word_regex, "[$&]");
        cout << __func__ << "::" << new_s << endl;
    
        // 超过6个字符的单词替换为 ****
        std::regex replace_regex("(\\w{7,})");
        std::string result_str = std::regex_replace(str, replace_regex, "****");
        cout << __func__ << "::" << result_str << endl;
    }
```
###### 36. explicit说明符的C++11新特性
- `explicit`说明符在`C++11`之前已存在,主要作用是用来指定构造函数(或转换函数)为显式,使其不能用于隐式转换和复制初始化
- `C++11`中影响到`explicit`的部分是将转换构造函数的概念扩充, 扩充参数个数的限制(旧有为单个参数)
- [203_text_explicit.cpp](https://github.com/Renleilei1992/MyCplusplus/blob/master/Main/203_text_explicit.cpp)
- 简单示例如下:
```
    /*
        转换构造函数: 不使用explicit说明符声明(且可以单个参数调用(C++11之前))的构造函数被称为转换构造函数;
        用途        : 可以用于复制初始化,可能出现隐式类型转换
    */
    struct Base1
    {
        Base1() { cout << "Base1:: 1" << __func__ << endl; }            // 转换构造函数 C++11 起
        Base1(int) { cout << "Base1:: 2" << __func__ << endl; }         // 转换构造函数 C++11之前
        Base1(int, int) { cout << "Base1:: 3" << __func__ << endl;}     // 转换构造函数 C++11 起
    };
    
    
    struct Base2
    {
        explicit Base2() { cout << "Base2:: 1" << __func__ << endl; }
        explicit Base2(int) { cout << "Base2:: 2" << __func__ << endl; }
        explicit Base2(int, int) { cout << "Base2:: 3" << __func__ << endl;}
    };
    int main(int argc, char** argv)
    {
        Base1 b1_0;                 // Base1:: 1Base1
        Base1 b1_1 = 100;           // Base1:: 2Base1
        Base1 b1_2(200);            // Base1:: 2Base1
        Base1 b1_3{300, 400};       // Base1:: 3Base1
        Base1 b1_4 = {300, 400};    // Base1:: 3Base1
        Base1 b1_5 = (Base1)500;    // Base1:: 2Base1
    
        cout << "-------------------------" << endl;
    
        Base2 b2_0;                 // Base2:: 1Base2
    //  Base2 b2_1 = 100;           // conversion from ‘int’ to non-scalar type ‘Base2’ requested   隐式转换编译不通过
        Base2 b2_2(200);            // Base2:: 2Base2
        Base2 b2_3{300, 400};       // Base2:: 3Base2
    //  Base2 b2_4 = {300, 400};    // converting to ‘Base2’ from initializer list would use explicit constructor ‘Base2::Base2(int, int)’  列表初始化的隐式转换编译不通过
        Base2 b2_5 = (Base2)500;    // Base2:: 2Base2   (显式转换)
        Base2 b2_6{};               // Base2:: 1Base2
    //  Base2 b2_7 = {};            // converting to ‘Base2’ from initializer list would use explicit constructor ‘Base2::Base2()’  列表初始化的隐式转换编译不通过
        Base2 b2_8 = static_cast<Base2>(600);   // Base2:: 2Base2   (显式转换)
    
        return 0;
    }
```
###### 37. 引用限定符的新特性 以及 `std::move`
- 
- 简单示例
```
    /*
    前置知识: (C++11)
        - 左值: 可以取地址,有名字的是左值;
        - 右值: 不可以取地址,没有名字的是右值(将亡值或者纯右值)
    */
    struct X {
        void foo() & {  // 引用限定符 &, 表明this对象指向着左值对象
            cout << "X:: 1 " << __func__ << endl;
        }
        void foo() && { // 引用限定符 &&, 表明this对象指向着右值对象
            cout << "X:: 2 " << __func__ << endl;
        }
    };
    
    int main()
    {
        X x;
        x.foo();    // X:: 1
        X().foo();  // X:: 2
        return 0;
    }

```
###### 38. std::error_code
- 概述: 
    > std::error_code 是依赖平台的错误码。每个 std::error_code 对象，保有一个源于操作系统或某些低层接口的错误码，和一个指向 std::error_category 类型对象的指针，它对应前述接口。错误码的值在错误类别之间可以不唯一
- 
###### 39. `std::bind`
- [176_test_bind.cpp](https://github.com/Renleilei1992/MyCplusplus/blob/master/Main/176_test_bind.cpp)
- 实际使用过程中可以节省一些重复代码，简洁;
- 实际使用示例:
```
    int main()
    {
        using namespace std::placeholders;      // for _1, _2, _3
    
        auto f1 = std::bind([](int i, int j) { cout << __func__ << " i+j= " << i+j << endl;}, _1, _2);
        f1(99, 98);     // operator() i+j= 197
    
        auto f2 = std::bind(print, _1, _2);
        f2(66, 88);
    
        Foo foo;
        auto f3 = std::bind(&Foo::data, _1);
        cout << __func__ << " " << f3(foo) << endl;
        auto f4 = std::bind(&Foo::print_sum, &foo, 99, _1);
        f4(1);
    
        return 0;
    }


    void GroupUsersMenuHandler::onDelMember()
    {
        CHECK_RETURN_VOID_ASSERT(0 != m_groupUsersMenuInfo.userID && m_groupUsersMenuInfo.userID != Util::Data::getMyselfID());
    
        checkFillTgroupUser();
    
        // std::function<void()> func   真实返回类型
        auto func = std::bind([=](){
            scoped_refptr<IMessageTgroup> messageTgroup = UtilHjBase::getMessageTgroup();
            CHECK_RETURN_VOID_ASSERT(messageTgroup);
            messageTgroup->RequestRemoveMemberTgroup(m_groupUsersMenuInfo.groupID, m_groupUsersMenuInfo.userID);
        });
    
        // tip [if the group is charge, no need this pop messagebox]
        ITgroupSimpleInfo* pSimpleInfo = Util::Data::getTgroupSimpleInfo(m_groupUsersMenuInfo.groupID);
        if (pSimpleInfo && pSimpleInfo->GetIsCharge()) {
            func();
        } else {
            CommonMessageBox* messageBox = new CommonMessageBox(QApplication::activeWindow(), MessageBox_Ok_Cancel);
            messageBox->setMessageBoxText(tr("Do you want to remove %1(%2)from this group?").arg(m_groupUsersMenuInfo.userShowName).arg(m_groupUsersMenuInfo.accountName));
            messageBox->showModal();
    
            QObject::connect(messageBox, &CommonMessageBox::onEndByClickedYes, this, [=](bool checkOperationResult) {
                Q_UNUSED(checkOperationResult);
    
                func();
            });
        }
    }
```
###### 40. `noexcept`
- 目的: 
    > 对于永远不会抛出异常的函数，可以声明为noexcept的。这一方面有助于程序员推断程序逻辑，另一方面编译器可以更好地优化代码
- [204_test_noexcept.cpp](https://github.com/Renleilei1992/MyCplusplus/blob/master/Main/204_test_noexcept.cpp)
- 简单示例:
```
    #include <iostream>
    #include <stdexcept>    // runtime_error
    
    using namespace std;
    
    class Tracer
    {
    public:
        Tracer() {}
        Tracer(const char* str):m_str(str) {}
    
        Tracer(Tracer& t):m_str(t.m_str) { throw runtime_error("copy exception!"); }
        Tracer(Tracer&& t) noexcept :m_str(std::move(t.m_str)) { throw runtime_error("move exception!"); }
    
    private:
        string m_str;
    };
    
    
    int main()
    {
        Tracer t("hello world!");
    
        // 测试拷贝构造函数抛出异常
        try {
            Tracer t1 = t;
        } catch (runtime_error e) {
            cout << "1 catch!! error: " << e.what() << endl;
        }
    
        // 测试使用了 noexcept 的移动构造函数是否会抛出异常
        try {
            Tracer t2 = std::move(t);
        } catch (runtime_error e) {
            cout << "2 catch!! error: " << e.what() << endl;
        }
        return 0;
    }

```

###### 41. `std::function` 函数模板
- [224_test_function.cpp](https://github.com/Renleilei1992/MyCplusplus/blob/master/Main/224_test_function.cpp)
- 使用`std::function`可以较为方便的管理可调用对象(函数指针)
```
// 加法函数
int add(int op1, int op2) {
    return op1 + op2;
}

// 减法 lambda表达式
auto minus_op = [](int op1, int op2) { return op1 - op2; };

// 函数对象
struct multiply_op {
    int operator()(int op1, int op2) {
        return op1 * op2;
    }   
};

// 除法函数
int devide(int op1, int op2, bool check0) {
    if (check0 && (op2 == 0)) {
        return 0;
    }   

    return op1 / op2;
}

// 参数绑定
auto dev_op = bind(devide, _1, _2, false);

// 自定义算法
auto diy_op = std::bind([](int op1, int op2) -> int { return op1 * op2 + 1000000; }, _1, _2);

int main()
{
    std::map<string, std::function<int(int, int)>> op = { 
        {"+", add},
        {"-", minus_op},
        {"*", multiply_op()},
        {"/", dev_op},
        {"diy", diy_op},
    };  

    cout << "测试加法: " << op["+"](1, 2) << endl;                  // 测试加法: 3
    cout << "测试减法: " << op["-"](3, 4) << endl;                  // 测试减法: -1
    cout << "测试乘法: " << op["*"](5, 6) << endl;                  // 测试乘法: 30
    cout << "测试除法: " << op["/"](7, 8) << endl;                  // 测试除法: 0
    cout << "测试自定义算法: " << op["diy"](100, 999) << endl;      // 测试自定义算法: 1099900

    return 0;
}

```

```C++
    // 绑定成员函数
    std::function<bool(const FeedbackWindow, int, const QString&)> callbackFunc = &FeedbackWindow::UpdateResult;
    
    // 绑定lambda表达式
    std::function<bool(int, const QString&)> callbackFunc1 = [&](int retcode, const QString& res) { return UpdateResult(retcode, res); };
```
---
