// week7.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

/*
使用说明：
进行查询生成的是一个有前后节点的树，书的内容包括：父亲名字 father，查找内容的名字 son，得分 score，后继结点 next，前节点 front
使用的命名空间为：namespace finder_zzw
调用查找近义词的功能为：
1.	先声明一个mod节点： finder_zzw::mod x = new mod;
2.	调用函数searcher() 格式为： x=searcher(char* st) 输入的内容st为所需要的名词

输出节点的函数为：
print_mod(mod*) 直接调用函数并输入生成的函数

查找最大的节点函数为：
1.	先声明一个mod节点： finder_zzw::mod maxer = new mod;
2.	调用函数find_max() 格式为： maxer=searcher(mod*x) 输入的内容x为查找到的关系树
*/

#include "pch.h"
#include <iostream> 
#include "tinyxml2.h"
#include<string>
#include <locale>         // std::wstring_convert
#include <codecvt>        // std::codecvt_utf8
#include <cstdint>        // std::uint_least32_t
#include <windows.h>
#include <algorithm>
#include<stdio.h>


using namespace tinyxml2;
using namespace std;

using F = std::codecvt_byname<wchar_t, char, std::mbstate_t>;

namespace finder_zzw {
	struct mod {
		char father[200];
		char son[200];
		char score[200];
		mod* next;
		mod* front;
	};

	int createXML(const char* xmlPath);//创建一个标准的xml读取树

	int addXML(XMLElement* &item, char* n);//进行增添节点操作 输入的参数为：父节点，以及该节点的名字

	int addleaves(XMLElement* &item, char* n);//进行叶子节点赋值 输入参数为：该节点，节点的值

	void change_xml(char *&str);//在函数changer内部调用，用于将读取到的xml中的词语的\后缀去掉


	/*
	解决tinyxml读取utf-8中文的乱码问题，将读取的xml文件内的utf-8格式转化为wchar，
	再转化为char，输入内容为：转化后的文本变量，转化前的变量
	*/
	void changer(char *& xmler, const char* xmle);

	/*
	进行查找操作的主要函数。第一个参数是保存结果的树的根节点地址，第二个参数是获得xml文本的路径
	*/
	int selectXML(mod *&moders, const char* xmlPath, char *st);

	/*
	初始化查找操作的函数，只需要输入所需要的文本内容即可,可以在主函数中调用
	*/
	mod *searcher(char *st);

	/*
	用来查找匹配度最大的名词，输出的格式为一个节点。
	*/
	mod *find_max(mod* moder);


	int createXML(const char* xmlPath)
	{
		tinyxml2::XMLDocument doc;
		if (3 != doc.LoadFile(xmlPath))
		{
			std::cout << "file has been existed !" << endl;
			return 0;
		}

		//添加申明可以使用如下两行
		XMLDeclaration* declaration = doc.NewDeclaration();
		doc.InsertFirstChild(declaration);

		XMLElement* root = doc.NewElement("collection");
		doc.InsertEndChild(root);


		XMLElement* item = doc.NewElement("item");
		root->InsertEndChild(item);

		XMLElement* name = doc.NewElement("name");
		/*添加属性*/

		name->InsertFirstChild(doc.NewText("桌子"));
		item->InsertFirstChild(name);

		XMLElement* son = doc.NewElement("son");

		XMLElement* son_item = doc.NewElement("son_item");
		XMLElement* son_name = doc.NewElement("son_name");
		XMLElement* son_rank = doc.NewElement("son_rank");
		XMLElement* son_score = doc.NewElement("son_score");
		son_name->InsertFirstChild(doc.NewText("桌子"));
		son_rank->InsertFirstChild(doc.NewText("1"));
		son_score->InsertFirstChild(doc.NewText("0.9999999999999992"));

		son_item->InsertEndChild(son_name);
		son_item->InsertEndChild(son_rank);
		son_item->InsertEndChild(son_score);
		son->InsertEndChild(son_item);

		XMLElement* son_item1 = doc.NewElement("son_item");
		XMLElement* son_name1 = doc.NewElement("son_name");
		XMLElement* son_rank1 = doc.NewElement("son_rank");
		XMLElement* son_score1 = doc.NewElement("son_score");
		son_name1->InsertFirstChild(doc.NewText("办公桌"));
		son_rank1->InsertFirstChild(doc.NewText("2"));
		son_score1->InsertFirstChild(doc.NewText("0.7436968492911772"));

		son_item1->InsertEndChild(son_name1);
		son_item1->InsertEndChild(son_rank1);
		son_item1->InsertEndChild(son_score1);
		son->InsertEndChild(son_item1);
		item->InsertEndChild(son);

		return doc.SaveFile(xmlPath);
	}

	int addXML(XMLElement* &item, char* n)//插入新的xml节点以及新节点的名字字符串n
	{
		tinyxml2::XMLDocument doc;
		//string s = n;
		XMLElement* son_item = doc.NewElement(n);
		item->InsertEndChild(son_item);
		return 1;
	}

	int addleaves(XMLElement* &item, char* n)//为叶子节点赋值 字符串n
	{
		tinyxml2::XMLDocument doc;
		item->InsertFirstChild(doc.NewText(n));
		return 1;
	}

	void change_xml(char *&str)//删除xml词语后面的词缀
	{
		int index = 0;
		int flag = 0;
		while (str[index] != 0)
		{
			if (str[index] == '/')
			{
				flag = 1;
			}
			if (flag)
			{
				str[index] = 0;
			}
			index++;
		}
	}

	void changer(char *& xmler, const char* xmle)//将输进来的乱码转化成不是乱码的
	{
		//char *xmler;
		strcpy(xmler, xmle);
		change_xml(xmler);//删除后缀
		wchar_t *buffer;//测试：1
		int buffer_len;//测试：1
		buffer_len = MultiByteToWideChar(CP_UTF8, 0, xmler, -1, NULL, 0);//测试1
		buffer = new wchar_t[buffer_len];//测试1
		MultiByteToWideChar(CP_UTF8, 0, xmler, -1, buffer, buffer_len);//
		int iSize;//测试1
		char* pszMultiByte;
		iSize = WideCharToMultiByte(CP_ACP, 0, buffer, -1, NULL, 0, NULL, NULL); //iSize =wcslen(pwsUnicode)+1=6
		pszMultiByte = (char*)malloc(iSize * sizeof(char)); //不需要 pszMultiByte = (char*)malloc(iSize*sizeof(char)+1);
		WideCharToMultiByte(CP_ACP, 0, buffer, -1, pszMultiByte, iSize, NULL, NULL);
		strcpy(xmler, pszMultiByte);
		return;
	}

	int selectXML(finder_zzw::mod *&moders, const char* xmlPath,const char *st)
	{
		int test_flag = 5;
		int index = 0;
		mod *son1 = moders;
		//mod *son2;
		tinyxml2::XMLDocument doc;
		if (doc.LoadFile(xmlPath) != 0)
		{
			std::cout << "load xml file failed" << endl;
			return false;

		}
		XMLElement* root = doc.RootElement();
		XMLElement* item = root->FirstChildElement("item");
		string st_str = st;
		while (item != NULL)
		{
			XMLElement* son = item->FirstChildElement("son");
			while (son != NULL)
			{
				//测试：1
				wchar_t *buffer;//测试：1
				int buffer_len;//测试：1

				XMLElement* son_item = son->FirstChildElement("son_item");
				XMLElement* son_name = son_item->FirstChildElement("son_name");
				XMLElement* son_score = son_item->FirstChildElement("son_score");
				char *son_name_xml = new char[200];
				memset(son_name_xml, 0, sizeof(son_name_xml));
				//strcpy(chr_xml, son_name->GetText());
				changer(son_name_xml, son_name->GetText());
				//cout << chr_xml << endl;
				string str_son_name = son_name_xml;

				char *son_score_xml = new char[200]; //用于转化和进行节点链表的赋值
				memset(son_score_xml, 0, sizeof(son_score_xml));
				changer(son_score_xml, son_score->GetText());
				string str_son_score = son_score_xml; //用于进行比较判断

				char *father_name_xml = new char[200];
				memset(father_name_xml, 0, sizeof(father_name_xml));
				changer(father_name_xml, item->FirstChildElement("name")->GetText());
				string str_father_name = father_name_xml;
				if (st_str == str_son_name)
				{
					mod *son2 = new mod;
					/*std::cout << str_father_name << endl;
					std::cout << str_son_name << endl;
					std::cout << str_son_score << endl;*/
					strcpy(son2->father, father_name_xml);
					strcpy(son2->son, son_name_xml);
					strcpy(son2->score, son_score_xml);
					son1->next = son2;
					son2->front = son1;
					son2->next = NULL;
					son1 = son1->next;
					index++;
					break;
				}

				son = son->NextSiblingElement();
			}
			item = item->NextSiblingElement();
		}
		return 0;
	}

	void print_mod(mod* moder)
	{
		mod *first = moder;
		first = first->next;
		int x = 1;
		while (first != NULL)
		{
			
			std::cout << x << endl;
			std::cout << first->father << endl;
			std::cout << first->son << endl;
			std::cout << first->score << endl;
			std::cout << endl;
			first = first->next;
			x++;
		}
		std::cout << "print结束" << endl;
		return;
	}

	mod *find_max(mod* moder) {
		mod *first = moder;
		mod *maxe = new mod;
		maxe->next = new mod;
		mod *maxer = maxe->next;
		maxer->next = NULL;
		first = first->next;
		float max_score=-1;
		float scorer = -1.0;
		while (first != NULL)
		{
			sscanf(first->score, "%f",&scorer);//char 转 double
			if (max_score < scorer) {
				strcpy(maxer->father, first->father);
				strcpy(maxer->son, first->son);
				strcpy(maxer->score, first->score);
				max_score = scorer;
				//maxer->next = first->next;
			}
				first = first->next;
		}
		//std::cout << "print结束" << endl;
		return maxe;
	}

	mod *searcher(const char *st)
	{
		/*std::cout << "请输入想要的词" << endl;
		char st[200];
		std::cin >> st;*/
		mod *moders = new mod;
		moders->next = NULL;
		selectXML(moders, "./item.xml",st);/*将liangbaikai的信息打印出来*/
		//print_mod(moders);
		return moders;
	}
}



