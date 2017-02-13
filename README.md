﻿# 简单计算器
---
## 描述
用语法分析器、词法分析器、语法制导翻译实现一个简单计算器，所用语言为 C++

## 词法分析
首先将输入的数学表达式识别为一个个词法单元，得到词法单元的序列，识别过程会跳过空白字符，得到的词法单元（Token）有两种类型：运算符和运算数，若识别出错，则给出错误位置等相关信息

## 语法分析
语法分析接受词法分析得到的Token序列作为输入，利用SLR分析表进行语法分析，判断输入是否符合数学表达式的语法

数学表达式的上下文无关文法为
```
E->E+E
  |E-E
  |T
T->F*F
  |F/F
  |F
F->(E)
  |n

 // n 表示数字（number）
```
上述语法规则具有二义性，为了消除二义性，将其改写如下（增加了`S->E`方便进行语法分析）：
```
// 无二义性的增广文法
0: S -> E
1: E -> E+T
2:     |E-T
3:     |T
4: T -> T*F
5:     |T/F
6:     |F
7: F -> (E)
8:     |n

// n 表示数字（number）
```
为了使用SLR分析算法，先计算First集和Follow集（$表示结束标志）

非终结符|First|Follow
--------|-----|-------
S       |(, n |\$
E       |(, n |\$, +, -, )
T       |(, n |\$, +, -, *, /, )
F       |(, n |\$, +, -, *, /, )

画出状态转换图后得到如下状态转换表：

state|+ |- |* |/ |( |) |n |$ |E |T |F
-----|--|--|--|--|--|--|--|--|--|--|--
0    |  |  |  |  |s9|  |s14|  |g1|g2|g13
1    |s3|s4|  |  |  |  |  |acc|  |  |
2    |r3|r3|s5|s6|  |r3|  |r3|  |  |
3    |  |  |  |  |s9|  |s14|  |  |g10|g13
4    |  |  |  |  |s9|  |s14|  |  |g11|g13
5    |  |  |  |  |s9|  |s14|  |  |  |g7
6    |  |  |  |  |s9|  |s14|  |  |  |g8
7    |r4|r4|r4|r4|  |r4|  |r4|  |  |
8    |r5|r5|r5|r5|  |r5|  |r5|  |  |
9    |  |  |  |  |s9|  |s14|  |g12|g2|g13
10   |r1|r1|s5|s6|  |r1|  |r1|  |  |
11   |r2|r2|s5|s6|  |r2|  |r2|  |  |
12   |s3|s4|  |  |  |s15|  |  |  |  |
13   |r6|r6|r6|r6|  |r6|  |r6|  |  |
14   |r8|r8|r8|r8|  |r8|  |r8|  |  |
15   |r7|r7|r7|r7|  |r7|  |r7|  |  |
>（最后3列是GOTO表，前面8列是ACTION表）

表项说明如下：

* s3 表示移进到状态3
* r3 表示按第三条产生式规则做归约
* g3 表示前进到状态3
* acc 表示接受状态，即识别成功

## 语法制导翻译
用于计算数学表达式的值，此过程是在语法分析中进行。对于每个语法符号，增加一个属性值val，在语法分析过程中，维护更新分析栈中语法符号的val值，分析结束后栈顶 E 的val值即为表达式的值

产生式|语法制导翻译求值
------|-----
E -> E+T | E.val = E.val + T.val
E -> E-T | E.val = E.val - T.val
E -> T | E.val = T.val
T -> T*F | T.val = T.val * F.val
T -> T/F | T.val = T.val / F.val
T -> F | T.val = F.val
F -> (E) | F.val = E.val
F -> n | F.val = getVal(n)

> getVal(n)为词法分析器得到的整数的值

上述求值动作发生在语法分析的归约时，如当按照 `E->E+T`进行归约时，将会执行
`E.val = E.val + T.val`
然后再把 E+T三个符号弹出栈，压入已经得到新val值的左部的E







