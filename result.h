// week7.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//

/*
ʹ��˵����
���в�ѯ���ɵ���һ����ǰ��ڵ������������ݰ������������� father���������ݵ����� son���÷� score����̽�� next��ǰ�ڵ� front
ʹ�õ������ռ�Ϊ��namespace finder_zzw
���ò��ҽ���ʵĹ���Ϊ��
1.	������һ��mod�ڵ㣺 finder_zzw::mod x = new mod;
2.	���ú���searcher() ��ʽΪ�� x=searcher(char* st) ���������stΪ����Ҫ������

����ڵ�ĺ���Ϊ��
print_mod(mod*) ֱ�ӵ��ú������������ɵĺ���

�������Ľڵ㺯��Ϊ��
1.	������һ��mod�ڵ㣺 finder_zzw::mod maxer = new mod;
2.	���ú���find_max() ��ʽΪ�� maxer=searcher(mod*x) ���������xΪ���ҵ��Ĺ�ϵ��
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

	int createXML(const char* xmlPath);//����һ����׼��xml��ȡ��

	int addXML(XMLElement* &item, char* n);//��������ڵ���� ����Ĳ���Ϊ�����ڵ㣬�Լ��ýڵ������

	int addleaves(XMLElement* &item, char* n);//����Ҷ�ӽڵ㸳ֵ �������Ϊ���ýڵ㣬�ڵ��ֵ

	void change_xml(char *&str);//�ں���changer�ڲ����ã����ڽ���ȡ����xml�еĴ����\��׺ȥ��


	/*
	���tinyxml��ȡutf-8���ĵ��������⣬����ȡ��xml�ļ��ڵ�utf-8��ʽת��Ϊwchar��
	��ת��Ϊchar����������Ϊ��ת������ı�������ת��ǰ�ı���
	*/
	void changer(char *& xmler, const char* xmle);

	/*
	���в��Ҳ�������Ҫ��������һ�������Ǳ����������ĸ��ڵ��ַ���ڶ��������ǻ��xml�ı���·��
	*/
	int selectXML(mod *&moders, const char* xmlPath, char *st);

	/*
	��ʼ�����Ҳ����ĺ�����ֻ��Ҫ��������Ҫ���ı����ݼ���,�������������е���
	*/
	mod *searcher(char *st);

	/*
	��������ƥ����������ʣ�����ĸ�ʽΪһ���ڵ㡣
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

		//�����������ʹ����������
		XMLDeclaration* declaration = doc.NewDeclaration();
		doc.InsertFirstChild(declaration);

		XMLElement* root = doc.NewElement("collection");
		doc.InsertEndChild(root);


		XMLElement* item = doc.NewElement("item");
		root->InsertEndChild(item);

		XMLElement* name = doc.NewElement("name");
		/*�������*/

		name->InsertFirstChild(doc.NewText("����"));
		item->InsertFirstChild(name);

		XMLElement* son = doc.NewElement("son");

		XMLElement* son_item = doc.NewElement("son_item");
		XMLElement* son_name = doc.NewElement("son_name");
		XMLElement* son_rank = doc.NewElement("son_rank");
		XMLElement* son_score = doc.NewElement("son_score");
		son_name->InsertFirstChild(doc.NewText("����"));
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
		son_name1->InsertFirstChild(doc.NewText("�칫��"));
		son_rank1->InsertFirstChild(doc.NewText("2"));
		son_score1->InsertFirstChild(doc.NewText("0.7436968492911772"));

		son_item1->InsertEndChild(son_name1);
		son_item1->InsertEndChild(son_rank1);
		son_item1->InsertEndChild(son_score1);
		son->InsertEndChild(son_item1);
		item->InsertEndChild(son);

		return doc.SaveFile(xmlPath);
	}

	int addXML(XMLElement* &item, char* n)//�����µ�xml�ڵ��Լ��½ڵ�������ַ���n
	{
		tinyxml2::XMLDocument doc;
		//string s = n;
		XMLElement* son_item = doc.NewElement(n);
		item->InsertEndChild(son_item);
		return 1;
	}

	int addleaves(XMLElement* &item, char* n)//ΪҶ�ӽڵ㸳ֵ �ַ���n
	{
		tinyxml2::XMLDocument doc;
		item->InsertFirstChild(doc.NewText(n));
		return 1;
	}

	void change_xml(char *&str)//ɾ��xml�������Ĵ�׺
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

	void changer(char *& xmler, const char* xmle)//�������������ת���ɲ��������
	{
		//char *xmler;
		strcpy(xmler, xmle);
		change_xml(xmler);//ɾ����׺
		wchar_t *buffer;//���ԣ�1
		int buffer_len;//���ԣ�1
		buffer_len = MultiByteToWideChar(CP_UTF8, 0, xmler, -1, NULL, 0);//����1
		buffer = new wchar_t[buffer_len];//����1
		MultiByteToWideChar(CP_UTF8, 0, xmler, -1, buffer, buffer_len);//
		int iSize;//����1
		char* pszMultiByte;
		iSize = WideCharToMultiByte(CP_ACP, 0, buffer, -1, NULL, 0, NULL, NULL); //iSize =wcslen(pwsUnicode)+1=6
		pszMultiByte = (char*)malloc(iSize * sizeof(char)); //����Ҫ pszMultiByte = (char*)malloc(iSize*sizeof(char)+1);
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
				//���ԣ�1
				wchar_t *buffer;//���ԣ�1
				int buffer_len;//���ԣ�1

				XMLElement* son_item = son->FirstChildElement("son_item");
				XMLElement* son_name = son_item->FirstChildElement("son_name");
				XMLElement* son_score = son_item->FirstChildElement("son_score");
				char *son_name_xml = new char[200];
				memset(son_name_xml, 0, sizeof(son_name_xml));
				//strcpy(chr_xml, son_name->GetText());
				changer(son_name_xml, son_name->GetText());
				//cout << chr_xml << endl;
				string str_son_name = son_name_xml;

				char *son_score_xml = new char[200]; //����ת���ͽ��нڵ�����ĸ�ֵ
				memset(son_score_xml, 0, sizeof(son_score_xml));
				changer(son_score_xml, son_score->GetText());
				string str_son_score = son_score_xml; //���ڽ��бȽ��ж�

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
		std::cout << "print����" << endl;
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
			sscanf(first->score, "%f",&scorer);//char ת double
			if (max_score < scorer) {
				strcpy(maxer->father, first->father);
				strcpy(maxer->son, first->son);
				strcpy(maxer->score, first->score);
				max_score = scorer;
				//maxer->next = first->next;
			}
				first = first->next;
		}
		//std::cout << "print����" << endl;
		return maxe;
	}

	mod *searcher(const char *st)
	{
		/*std::cout << "��������Ҫ�Ĵ�" << endl;
		char st[200];
		std::cin >> st;*/
		mod *moders = new mod;
		moders->next = NULL;
		selectXML(moders, "./item.xml",st);/*��liangbaikai����Ϣ��ӡ����*/
		//print_mod(moders);
		return moders;
	}
}



