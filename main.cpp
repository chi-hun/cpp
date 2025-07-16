// 10-3
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// struct is_odd {
//     bool operator()(const int a){
//         return (a % 2) == 1;
//     }
// };

bool odd(const int a){
        return (a % 2) == 1;
}


int main() {
    vector<int> what;

    what.push_back(3);
    what.push_back(2);
    what.push_back(1);
    what.push_back(4);
    what.push_back(5);

    for (auto ar : what) {
        cout << ar;
    }
    cout << endl;

    what.erase(remove_if(what.begin(), what.end(), odd), what.end());


    for (auto ar : what) {
        cout << ar ;
    }
    cout << endl;

    return 0;
}
