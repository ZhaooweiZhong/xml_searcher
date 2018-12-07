#   终于第一部分集成完成了，词法项目部分！
>>咱个老百姓啊，今个真高兴

<font size='4' face='楷体'>
&#160;&#160;&#160;&#160;整个xml在库内的查找模式很简单，已经进行了封装，环境配置如下：

```
1.将三个文件放到目录文件下
2.引入三个头文件：result.h tinyxml2.h tinyxml.h 一个xml文件：item.xml
3.#include "result.h"
4.使用命名空间 finder_zzw
5.预编译时 _CRT_SECURE_NO_WARNINGS
```
&#160;&#160;&#160;&#160;在这个result.h库中，主要的一些功能实现已经写在了注释中，考虑到二进制或utf-8打开有乱码，在这里再写一下：

-----
>使用说明：
>>进行查询生成的是一个有前后节点的树，书的内容包括：父亲名字 father，查找内容的名字 son，得分 score，后继结点 next，前节点 front
使用的命名空间为：namespace finder_zzw
调用查找近义词的功能为：
>>>1.	先声明一个mod节点： finder_zzw::mod x = new mod;
>>>2.	调用函数searcher() 格式为： x=searcher(char* st) 输入的内容st为所需要的名词

>>输出节点的函数为：
print_mod(mod*) 直接调用函数并输入生成的函数

>>查找最大的节点函数为：
>>>1.	先声明一个mod节点： finder_zzw::mod maxer = new mod;
>>>2.	调用函数find_max() 格式为： maxer=searcher(mod*x) 输入的内容x为查找到的关系树

&#160;&#160;&#160;&#160;贴了一个极简单的测试代码，就是文件夹下的try_use.cpp：
```c++
#include "pch.h"
#include <iostream>
#include "result.h"
using namespace finder_zzw;

int main()
{
	mod* try_mod = new mod;
	try_mod = searcher("桌子");

	print_mod(try_mod);

	mod* maxer = new mod;
	maxer = find_max(try_mod);
	print_mod(maxer);

	return 0;
}
```
</font>