#include <iostream>
#include <stack>
#include <string>
using namespace std;

int getPriority(char c)
{
    if (c == '*' || c == '\\')
    {
        return 2;
    }
    else if (c == '+' || c == '-')
    {
        return 1;
    }
    return 0;
}

// a+b*c+(d*e+f)*g  ==> abc*+de*f+g*+
int main()
{
    stack<char> st;
    string s;
    cin >> s;
    string output;
    for (int i = 0; i < s.length(); i++)
    {
        if (isalpha(s[i]))
        {
            output += s[i];
        }
        else
        {
            if (s[i] == '(')
            {
                st.push('(');
            }
            else if (s[i] == ')')
            {
                while (!st.empty() && st.top() != '(')
                {
                    output += st.top();
                    st.pop();
                }
                st.pop();
            }
            else if (st.empty() || getPriority(s[i]) > getPriority(st.top()))
            {
                st.push(s[i]);
            }
            else
            {
                // 注意这个地方的小于等于
                while (!st.empty() && getPriority(s[i]) <= getPriority(st.top()))
                {
                    output += st.top();
                    st.pop();
                }
                st.push(s[i]);
            }
        }
    }
    while (!st.empty())
    {
        output += st.top();
        st.pop();
    }
    cout << output;
}