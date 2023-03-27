#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<fstream>
#include <Windows.h>
#include<time.h>
#include<stdio.h>
#include<string.h>
#include<conio.h>
#include"Python.h"
using namespace std;

//全局变量
SYSTEMTIME sys;
string name;
string sex;
int year, month, day;

//函数引用
void my_clear();
void my_clear(string s);
void getID();


int Match(string& s, string& p)
{
	int sLen = s.size();
	int pLen = p.size();

	int i = 0;
	int j = 0;
	while (i < sLen && j < pLen)
	{
		if (s[i] == p[j])
		{
			//①如果当前字符匹配成功（即S[i] == P[j]），则i++，j++    
			i++;
			j++;
		}
		else
		{
			//②如果失配（即S[i]! = P[j]），令i = i - (j - 1)，j = 0    
			i = i - j + 1;
			j = 0;
		}
	}
	//匹配成功，返回模式串p在文本串s中的位置，否则返回-1
	if (j == pLen)
		return i - j;
	else
		return -1;
}
string UTF8ToGB(const char* str)
{
	string result;
	WCHAR *strSrc;
	LPSTR szRes;

	//获得临时变量的大小
	int i = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	strSrc = new WCHAR[i + 1];
	MultiByteToWideChar(CP_UTF8, 0, str, -1, strSrc, i);

	//获得临时变量的大小
	i = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, NULL, 0, NULL, NULL);
	szRes = new CHAR[i + 1];
	WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i, NULL, NULL);

	result = szRes;
	delete[]strSrc;
	delete[]szRes;

	return result;
}
string GBKToUTF8(const std::string& strGBK)
{
	string strOutUTF8 = "";
	WCHAR * str1;
	int n = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);
	str1 = new WCHAR[n];
	MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, str1, n); n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
	char * str2 = new char[n];
	WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);
	strOutUTF8 = str2;
	delete[]str1;
	str1 = NULL;
	delete[]str2;
	str2 = NULL;
	return strOutUTF8;
}
void init()
{
	my_clear();
	printf("欢迎初次使用bot，下边进行初始设置\n");
	system("pause");
	ofstream data("data.txt");
	string buffer;
	cout << "请输入对您的称呼:" << endl;
	cin >> buffer;
	data << buffer << endl;
	cout << "请输入您的性别:" << endl;
	cin >> buffer;
	data << buffer << endl;
	cout << "请输入您的出生年月日:" << endl;
	int a, b, c;
	char d;
	cin >> a;
	d = getchar();
	cin >> b;
	d = getchar();
	cin >> c;
	data << a << endl;
	data << b << endl;
	data << c << endl;
	getID();
}
void getstate(ifstream &data, string &name, string &sex, int &year, int &month, int &day)
{
	getline(data, name);
	getline(data, sex);
	string buffer;
	getline(data, buffer);
	year = atoi(buffer.c_str());
	getline(data, buffer);
	month = atoi(buffer.c_str());
	getline(data, buffer);
	day = atoi(buffer.c_str());
}
void gettime()
{
	GetLocalTime(&sys);
	//printf("%4d/%02d/%02d %02d:%02d:%02d.%03d 星期%1d\n", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds, sys.wDayOfWeek);
}
void getID()
{
	char username[500];
	char password[1000];
	printf("请输入你的用户名\n");
	cin >> username;
	printf("请输入你的密码\n");
	int i = 0;
	char c = _getch();
	do {
		password[i] = c;
		printf("*");
		i++;
		c = _getch();
	} while (c != '\r');
	password[i] = '\0';
	ofstream data("config.py");
	data << "STUID = \"" << username << '\"' << endl << "PASSWORD = \"" << password << '\"' << endl;
	data.close();
	return;
}
void ran_out(string s1)
{
	ifstream fin(s1);
	string s;
	int count = 0;
	while (getline(fin, s))
	{
		count++;
	}
	srand(time(NULL));
	int randnum = rand() % count;
	fin.clear();
	fin.seekg(0, ios::beg);
	for (int i = 0; i <= randnum; i++)
		getline(fin, s);
	string line = UTF8ToGB(s.c_str()).c_str();
	cout << line << endl;
	fin.close();
}
void happybirthday(int a)
{
	my_clear("cake.txt");
	cout << "今天是你的第" << sys.wYear - a << "岁生日" << endl << endl;
	string s1 = "hap_bir.txt";
	ran_out(s1);
	cout << endl << endl;
	system("pause");
}
void outima(string s)
{
	ifstream ima(s);
	string buffer;
	while (getline(ima, buffer))
	{
		cout << buffer << endl;
	}
	ima.close();
}
void outall(string s1)
{
	ifstream fin(s1);
	string s;
	while (getline(fin, s))
	{
		string line = UTF8ToGB(s.c_str()).c_str();
		cout << line << endl;
	}
	fin.close();
	
}
void my_clear()
{
	system("cls");
	outima("xiaolian.txt");
	cout << endl << endl;
}
void my_clear(string s)
{
	system("cls");
	outima(s);
	cout << endl << endl;
}
int judge_null(ifstream &fin)
{
	fin.seekg(0, ios::end); //将文件指针指向文件末端
	streampos fp = fin.tellg(); //fp为文件指针的偏移量
	if (int(fp) == 0) // 偏移量为0，证明文件为空，为首次进入系统
		return 1;
	else return 0;
}
void menu()
{

	my_clear();
	outall("menu.txt");
}
void bot_help()
{
	my_clear("wenhao.txt");
	outall("help.txt");
	system("pause");
}
void bot_reset()
{
	ofstream fin("data.txt");
	fin.close();
	ofstream fin2("config.py");
	fin2.close();
	exit(1);
}
void bot_about()
{
	my_clear();
	outall("about.txt");
	system("pause");
}
void bot_time()
{
	my_clear("clock.txt");
	gettime(); 
	outall("time.txt");
	printf("%4d/%02d/%02d %02d:%02d:%02d 星期%1d\n\n\n", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, sys.wDayOfWeek);
	system("pause");
}
void jr()
{
	my_clear("tushe.txt");
	system("start https://space.bilibili.com/672328094");
	outall("jr.txt");
	Sleep(5000);
	system("pause");
}
void  xiaohua()
{
	my_clear("xiao.txt");
	ran_out("xiaohua.txt");
	system("pause");
}
void qiuqian()
{
	my_clear("qiantong.txt");
	cout << "正在抽签中……";
	Sleep(5000);
	srand(time(NULL));
	string s;
	ifstream fin("qianres.txt");
	int result;
	int randnum = rand() % 100;
	if (randnum >= 90) result = 0;
	if (randnum >= 60 && randnum <90) result = 1;
	if (randnum >= 40 && randnum <60) result = 2;
	if (randnum >= 10 && randnum <30) result = 3;
	if (randnum < 10) result = 4;
	for (int i = 0; i <= result; i++)
		getline(fin, s);
	string line = UTF8ToGB(s.c_str()).c_str();
	cout << line << endl;
	system("pause");
}
void getinfo()
{
	Py_Initialize(); /*初始化python解释器,告诉编译器要用的python编译器*/
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('./')");
	PyRun_SimpleString("import getinfo"); /*调用python文件*/
	Py_Finalize(); /*结束python解释器，释放资源*/
	system("pause");
}
void getscore()
{
	Py_Initialize(); 
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('./')");
	PyRun_SimpleString("import getscore"); 
	Py_Finalize(); 
	system("pause");
}
void getteacher()
{
	Py_Initialize(); 
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('./')");
	PyRun_SimpleString("import getteacher"); 
	Py_Finalize(); 
	system("pause");
}
void youxiang()
{
	Py_Initialize();
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('./')");
	PyRun_SimpleString("import get_email");
	Py_Finalize();
	system("pause");
}
void tuichu()
{
	my_clear("88.txt");
	cout << "期待与你再次相遇喵" << endl;
	Sleep(3000);
	exit(1);
}
int main_func(string sin)
{
	ifstream fin("func.txt");
	int count = 0;
	string s;
	while (getline(fin, s))
	{
		string line = UTF8ToGB(s.c_str()).c_str();
		if (sin == line) break;
		count++;
	}
	if (count == 0) { bot_help(); return 1; }
	if (count == 1) { bot_reset(); return 1; }
	if (count == 2) { bot_about(); return 1; }
	if (count == 3) { bot_time(); return 1; }
	if (count == 4) { jr(); return 1; }
	if (count == 5) { xiaohua(); return 1; }
	if (count == 6) { qiuqian(); return 1; }
	if (count == 7) { getinfo(); return 1; }
	if (count == 8) { getscore(); return 1; }
	if (count == 9) { getteacher(); return 1; }
	if (count == 10) { youxiang(); return 1; }
	if (count == 11) { tuichu(); return 1; }

	return 0;
}
string getstr(int num, string sin)
{
	int len = sin.length();
	int head = 0;
	int tail = -1;
	int count = 0;
	string s2 = "";
	for (int i = 0; i < len; i++)
	{
		if (sin[i] == ',') 
		{
			head = tail + 1;
			tail = i;
			count++;
			if (count == num)
			{
				s2 = sin.substr(head, tail - head);
				return s2;
			}
		}
	}
	cout << "您输入的数字过大或过小，请重新输入" << endl;
	return s2;
}
void notunder(string sin)
{
	my_clear("ku.txt");
	cout << "虽然我听不懂，但你可能想找这些：" << endl;
	Py_Initialize(); /*初始化python解释器,告诉编译器要用的python编译器*/
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('./')");
	PyObject* pModule = NULL;//声明变量
	PyObject* pFunc = NULL;// 声明变量
	pModule = PyImport_ImportModule("do_search");
	pFunc = PyObject_GetAttrString(pModule, "my_search");
	PyObject* args = PyTuple_New(1); 
	string s2 = GBKToUTF8(sin);
	PyObject* arg1 = PyUnicode_FromString(&s2[0]); 
	PyTuple_SetItem(args, 0, arg1);
	PyObject* pRet = PyObject_CallObject(pFunc, args);
	s2 = PyUnicode_AsUTF8(pRet);
	s2 = UTF8ToGB(&s2[0]);
	Py_Finalize(); /*结束python解释器，释放资源*/
	cout << endl << "输入网址对应序号来访问网址吧,输入0则取消搜索" << endl;
	int num;
getnum: cin >> num;
	if (num == 0) return;
	sin = getstr(num, s2);
	if (sin == "") goto getnum;
	sin = "start " + sin;
	system(&sin[0]);
	goto getnum;
}
int talk(string sin)
{
	ifstream fin("talkmenu.txt");
	int count = 0;
	string s;
	while (getline(fin, s))
	{
		string line = UTF8ToGB(s.c_str()).c_str();
		if (Match(sin,line)!= -1) break; 
		count++;
	}
	if (count <= 1) { bot_time(); return 1; }
	if (count == 2) { xiaohua(); return 1; }
	return 0;
}
int ciku(string sin)
{
	ifstream fin("ciku.txt");
	string s;
	while (getline(fin, s))
	{
		if (Match(sin, s) != -1)
		{
			getline(fin, s);
			cout << s << endl;
			system("pause");
			return 1;
		}
		else
		{
			getline(fin, s);
			getline(fin, s);
		}
	}
	return 0;
}
void bot_in()
{
	string s;
	cin >> s;
	if (main_func(s))
		return;
	else if (talk(s))
		return;
	else if (ciku(s))
		return;
	else notunder(s);

}
void sayhello()
{
	if (sys.wHour <= 5 || sys.wHour >= 23)
	{
		my_clear("moon.txt");
		cout << name << "，" << "晚上好" << "这么晚了，还在忙吗" << endl;
	}
	if (sys.wHour >= 6 && sys.wHour <= 11)
	{
		my_clear("sun.txt");
		cout << name << "，" << "早上好～(＞ω＜)☆";
	}
	if (sys.wHour >= 12 && sys.wHour <= 13)
	{
		my_clear("sun.txt");
		cout << name << "，" << "中午好～(＞ω＜)☆";
	}
	if (sys.wHour >= 14 && sys.wHour <= 18)
	{
		my_clear("sun.txt");
		cout << name << "，" << "下午好～(＞ω＜)☆";
	}
	if (sys.wHour >= 19 && sys.wHour <= 22)
	{
		my_clear("moon.txt");
		cout << name << "，" << "晚上好～(＞ω＜)☆";
	}
	cout << endl << endl;
	system("pause");
}
int main()
{
	begin:ifstream data("data.txt");
	if (!data.is_open())
	{
		data.close();
		init();
		goto begin;
	}
	else
	if (judge_null(data) == 1)
	{
		data.close();
		init();
		goto begin;
	}
	data.close();
	data.open("data.txt");
	getstate(data, name, sex, year, month, day);
	data.close();
	gettime();
	if (sys.wMonth == month && sys.wDay == day) happybirthday(year);
	sayhello();
	menu_pos:menu();
	bot_in();
	goto menu_pos;
	return 1;
}