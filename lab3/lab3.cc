#include <iostream>
#include <vector>
#include <fstream>
#include <set>
using namespace std;
int main() {
    vector<int> num;
    do {
        int i;
        cin >> i;
        if (i == 0) {
            break;
        }
        num.push_back(i);
    }while (1);
    cout << "vector: ";
    for (size_t i = 0; i < num.size(); i++) {
        if (i != 0) {
            cout << ",";
        }
        cout << num[i];
    }
    cout << "\n";
    string str;
    char ch;
    fstream fin("/etc/resolv.conf", fstream::in);
    while (fin >> skipws >> ch) {
        str.push_back(ch);
    }
    multiset<char> ms;
    for (size_t i = 0; i < str.size(); i++) {
        ms.insert(str[i]);
    }
    set<char> s;
    for (auto val : ms) {
        s.insert(val);
    }
    cout << "Set size: " << s.size() << "| " << "Multiset size: " << ms.size() << "\n";
    cout << "Set: ";
    for (auto val : s) {
        cout << val << ",";
    }
    cout << "\n";
    cout << "Multiset: ";
    for (auto val : ms) {
        cout << val << ",";
    }
    cout << "\n";
}
