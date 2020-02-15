# MyCplusplus
It's all about my C&amp;Cplusplus learning and config. A C++ SE should Know :) :)

----
[![996.ICU](https://img.shields.io/badge/link-996.icu-red.svg)](https://996.icu)
[![LICENSE](https://img.shields.io/badge/license-Anti%20996-blue.svg)](https://github.com/996icu/996.ICU/blob/master/LICENSE)
----
#### DIR: Pointer_On_C [C和指针]
 - Practices about Learning the BOOK[Pointer_On_C]
 - Experiences and Confusion in the learning C/C++ process
 - Some Project or Algorithm
 - nullptr
 
----
##### 
***Examine some unsafe features of the C language***
***Take an over view of things to think about when writing code***

- Buffer Overflow                           (缓冲溢出)
- Command injection                         (命令注入)
- Format String                             (格式化字符串)
- String Termination Error                  (字符串结尾错误)
- Password Management: Hardcoded Password   (口令管理)
- Privacy Violation                         (私密信息违规管理)
- Double Free                               (两次释放同一块内存)
- Memory Leak                               (内存泄露)

##### Buffer Overflow
 > 对所分配的内存块进行写操作时,没有对输入数据的大小作验证,造成输入数据的大小超出了目的内存的存储范围,使得临近目的内存块的数据被覆盖(Overflow)从而使程序崩溃,甚至导致执行恶意代码.
##### Command Injection
 > 执行命令时，命令将未验证的用户输入作为命令参数的一部分，导致应用可能遭受攻击.
##### Format String
 > 允许用户去控制格式化字符串的函数的参数，将导致黑客读取堆栈信息或者进行buffer overflow攻击
##### String Termination Error
 > 依赖于字符串终止符的操作有可能造成缓冲区溢
 > 字符串终止错误在以下两种情况下发生
    > 数据通过一个函数的输出进入另一个需要字符终止符输入的函数作操作,而作为输出函数的字符没有字符终止符.
    > 数据被传输到一个需要字符终止符的操作函数.但数据没有字符终止符结尾.
##### Privacy Violation
 > 不正确处理私有信息, 比如客户口令,社会保障代码可能危及用户的私密信息和违法律
 > 私密信息违法主要发生
    > 私人用户的信息进入程序
    > 这些信息写到外部其它地方, 比如控制台, 文件系统或者网
