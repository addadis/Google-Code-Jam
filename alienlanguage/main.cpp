//Google Code Jam practice question A
//base conversion using map

#include <iostream>
#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
#include <fstream>
using namespace std;
int n;
string s, t;
int main()
{   ifstream input;
    ofstream output;
    output.open("output.txt");
    input.open("A-large-practice.in.txt");
    input >> n;
    string s, num;
    map<char, int> m;
    for (int i = 0; i < n; i++) {
        input >> num;
        input >> s;
        int len = s.size();
        m.clear();
        for (int j = 0; j < len; j++) {
            m[s[j]] = j;
        }
        long long sourceCode = 0;
        int power = 1;
        for (int j = num.size() - 1; j >= 0; j--) {
            sourceCode += m[num[j]] * power;
            power *= len;
        }
        input >> t;
        len = t.size();
        string ans;
        while (sourceCode) {
            ans += t[sourceCode % len];
            sourceCode /= len;
        }
        output << "Case #";
        output << (i+1);
        output << ": ";
        for (int j = ans.size() - 1; j >= 0; j--) {
            output << ans[j];
        }
        output << endl;

    }

    input.close();
    output.close();

    return 0;
}

