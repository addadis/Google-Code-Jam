#include <iostream>
#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
#include <fstream>
using namespace std;
int n;
string entranceToExit, exitToEntrance;
int x, y, maxx, maxy, minx, miny, movex, movey, cnt;
map<pair<int, int>, int> m;

ofstream output;

void update() {
    maxx = max(maxx, x);
    maxy = max(maxy, y);
    minx = min(minx, x);
    miny = min(miny, y);
}

void updateDirection(char c) {
    if (movex == 0 && movey == 1) {
        movex = c == 'L' ? -1 : 1;
        movey = 0;
    } else if (movex == 1 && movey == 0) {
        movey = c == 'L' ? 1 : -1;
        movex = 0;
    } else if (movex == 0 && movey == -1) {
        movex = c == 'L' ? 1 : -1;
        movey = 0;
    } else {
        movey = c == 'L' ? -1 : 1;
        movex = 0;
    }
}

int getInd(int movex, int movey) {
    int ind = 0;
    if (movex == 0 && movey == -1) {
        ind = 0;
    } else if (movex == 0 && movey == 1) {
        ind = 1;
    } else if (movex == 1 && movey == 0) {
        ind = 2;
    } else {
        ind = 3;
    }
    return ind;
}

void updateBlock() {
    int tmpx = movex, tmpy = movey;
    m[make_pair(x, y)] |= (1 << getInd(tmpx, tmpy));
    m[make_pair(x + tmpx, y + tmpy)] |= (1 << getInd(-tmpx, -tmpy));
}


void solve() {
    m.clear();
    x = 0, y = 0, maxx = 0, maxy = 0, minx = 100000, miny = 100000, movex = 0, movey = 1;
    m[make_pair(0, 0)] = 1;
    for (int i = 1; i < entranceToExit.size() - 1; i++) {
        if (entranceToExit[i] == 'W') {
            updateBlock();
            x += movex, y += movey;
            update();
        } else {
            updateDirection(entranceToExit[i]);
        }
    }
    updateBlock();
    movex = 0 - movex;
    movey = 0 - movey;

    for (int i = 1; i < exitToEntrance.size() - 1; i++) {
        if (exitToEntrance[i] == 'W') {
            updateBlock();
            x += movex, y += movey;
            update();
        } else {
            updateDirection(exitToEntrance[i]);
        }
    }
    if (minx == 100000) {
        minx = 0;
    }
    if (miny == 100000) {
        miny = 0;
    }
    int r = maxy + 1;
    int c = maxx - minx + 1;
    output << "Case #";
    output << ++cnt;
    output << ":" << endl;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            int nx = maxx - j;
            int res = m[make_pair(nx, i)];
            if (res < 10) {
                output << res;
            } else {
                char c = 'a' + res - 10;
                output << c;
            }
        }
        output << endl;
    }

}

int main()
{
    ifstream input;
    input.open("B-large-practice.in.txt");
    output.open("output.txt");
    input >> n;
    while (n--) {
        input >> entranceToExit >> exitToEntrance;
        solve();
    }
    input.close();
    output.close();
    return 0;
}

