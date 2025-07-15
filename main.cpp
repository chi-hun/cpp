// 10-2
#include <iostream>
#include <map>

using namespace std;


int main() {
    map<string, int> mm;
    mm.insert(make_pair("one", 1));
    mm.insert(pair<string, int>("two", 2));
    mm.insert(pair<string, int>("three", 3));

    for (auto ar : mm) {
        cout << ar.first << " " << ar.second << endl;
    }

    return 0;
}
