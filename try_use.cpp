// try_use.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

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


