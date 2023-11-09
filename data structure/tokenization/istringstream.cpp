#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// 只有空格和数字
void streamingInteger()
{
    stringstream ss;
    string S;
    getline(cin, S);
    ss << S;
    int num;
    while (ss >> num)
    {
        cout << num << endl;
    }
}
// istringstream的使用方法
// istringstream默认通过空格或回车来分割字符串输入，如果字符串用逗号来分割，可以先把逗号替换成空格
void streamingExample()
{
    string s = "ab,cd,e,fg,h";
    int n = s.size();
    for (int i = 0; i < n; i++)
    {
        if (s[i] == ',')
        {
            s[i] = ' ';
        }
    }
    istringstream out(s);
    string str;
    while (out >> str)
    {
        cout << str << ' ';
    }
    cout << endl;
}

int main()
{
    streamingExample();
}