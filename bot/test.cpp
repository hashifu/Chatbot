#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int main78()
{
                                                                                                                            
 cout<< "                                                      ::;i;;;;;:,,                            " << endl;                          
 cout<< "                                               :1LC008880000008800@08G1:   .                  " << endl;                          
 cout<< "                                           .1888880008GLfti11tfLC80880880C1.                  " << endl;                          
 cout<< "                                        .1C8000Cf;                  ,;fC@000Ci.               " << endl;                          
 cout<< "                                       f8008Ci                          ,1G0088t.             " << endl;                          
 cout<< "                                    ,t8000t  .                             .t0080f            " << endl;                          
 cout<< "                                  .iC@@C;                                     1800C;          " << endl;                          
 cout<< "                                  L0001.                                       .t800f         " << endl;                          
 cout<< "                                 L00G:                                           :C80f.       " << endl;                          
 cout<< "                               ,G0@f.                                             :L00L       " << endl;                          
 cout<< "                               f@8G                                                ,G801      " << endl;                          
 cout<< "                              :8@G,       .  iC88C.                .,L88C;.         ,00C;     " << endl;                          
 cout<< "                              L00i          :80000C,               .C08080,          f@0f     " << endl;                          
 cout<< "                             :C0C.          ,G0000f                 t@800G.          i08C     " << endl;                          
 cout<< "                             :00f             :i;.                  .:f1;.           ,C0G.    " << endl;                            
 cout<< "                             ;80t                                                    .C0G.    " << endl;
 cout<< "                             ;80t                                                    .00G     " << endl;
 cout<< "                             :00L                                                    :008.    " << endl;
 cout<< "                             .G08:                                                  .t00t     " << endl;
 cout<< "                              t88f              .                                   ,808:     " << endl;
 cout<< "                              .G88;           .i,                     ;:.          .t@0i      " << endl;
 cout<< "                               ;80C:          ,L0t                  iG0f          .t00f       " << endl;
 cout<< "                                i00G:          ,t00t,.           .;L@C; .        .t88L        " << endl;
 cout<< "                                 ;888t           :t8@88G1;::;iLG800Gi           :L@0f         " << endl;
 cout<< "                                  ,G00C:           .;fC808800080L:  .         ,f808i          " << endl;
 cout<< "                                    ;8@8f:                                  :fC80t.           " << endl;
 cout<< "                                     .:C0081 .                           .:G@88L              " << endl;
 cout<< "                                       .iG@@CCi,                      .;fC808t                " << endl;
 cout<< "                                          .iG8C808Li.         .   :1G8808Gt, .                " << endl;
 cout<< "                                             .;tC0008000000888CCCCCCCf1:                      " << endl;
 cout<< "                                                   .:iLLLLLLLLf1:.       .                    " << endl;
                                                                                                                            
                                                                                                                            
	return 1;
}
int main4()
{	
	string s = "imagine.txt";
	ifstream ima(s);
	string buffer;
	while (getline(ima, buffer))
	{
		cout << buffer << endl;
	}
	return 4;
}
int Matches(string& s, string& p)
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

int main456(void) {

	string s = "上山打老虎";
	string p = "盒";
	cout << Matches(s, p) << endl;
	return 0;
}
int main56()
{
	ifstream fin("test.txt");
	string s;
	getline(fin, s);
	cout << s <<  "1" << endl;
	getline(fin, s);
	cout << s <<  "2" << endl;
	getline(fin, s);
	cout << s <<  "3" << endl;
	
}