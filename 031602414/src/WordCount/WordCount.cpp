#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>  
using namespace std;
int main(int argc, char* argv[])
{
	int characters =0;//字符个数
	int words = 0;    //单词个数
	int lines = 0;    //有效行数
	char ch;          //文本字符
	int lvalid = 0;   //判断行有效
	int process = 0;  //自动机状态
	ifstream fp(argv[1]);//打开文件
	string word;      //接收单词
    map<string,int> word_count;//构造map容器
	if (!fp)//判断文件是否打开
	{
		cout << "未能成功打开" << argv[1] << "，请检查文件是否存在";
		getchar();//给用户查看错误的时间
		exit(1);
	}
	while (fp.get(ch))//读到文件尾
	{
		if (ch >= 65 && ch <= 90) {	ch += 32;}//大写转为小写
		if (ch != ' '&&ch != '\n') { lvalid = 1; }//存在非空白字符，为有效行
		switch (process)//无穷自动机
			{
		case 0:if (ch >= 97 && ch <= 122) { word = word + ch; process++; }
			   else { word = ""; process = 0; }break;
		case 1:if (ch >= 97 && ch <= 122) { word = word + ch; process++; }
			   else { word = ""; process = 0; }break;
		case 2:if (ch >= 97 && ch <= 122) { word = word + ch; process++; }
			   else { word = ""; process = 0; }break;
		case 3:if (ch >= 97 && ch <= 122) { word = word + ch; process++; }
			   else { word = ""; process = 0; }break;
		case 4:if (ch != ' '&& ch != '\n') { word = word + ch; }
			   else { ++word_count[word]; process = 0; word = ""; words++; }break;
			}
		if (ch == '\n')//读到换行符,若为有效行则行数+1，lvalid置零
		{ 
			if(lvalid == 1){lines++; }
			lvalid = 0;
		}
		characters++;//字符数+1
	}
	int nSize = word_count.size(),i=1;
	multimap<int, string, greater<int> > mapt;

	for (map<string, int>::iterator it1 = word_count.begin(); it1 != word_count.end(); ++it1)
	{
		mapt.insert(pair<int, string>(it1->second, it1->first));//将word_count输入到mapt
	}
	
	fp.close();
	ofstream fout("result.txt");
	fout << "characters: "<<characters<< endl;
	fout << "words: " << words << endl;
	fout << "lines: " << lines << endl;
	if (nSize <= 10)
	{
		for (map<int, string>::iterator it2 = mapt.begin(); it2 != mapt.end(); ++it2)
		{
			fout << "<" << it2->second << ">: " << it2->first << endl;
		}
	}
	else
	{
		for (map<int, string>::iterator it2 = mapt.begin(); ; ++it2)
		{
			if (i > 10) { break; }
			i++;
			fout << "<" << it2->second << ">: " << it2->first << endl;
		}
    }
	fout.close();
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
