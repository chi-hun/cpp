// 10-4
#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;

struct User {
    string name;
    int level;

    User(string n, int l) : name(n), level(l) {}
    bool operator==(const User& u) {
        if (name == u.name && level == u.level) return true;
        return false;
    }
};

class Party {
    private:
        vector<User> users;

    public:
        bool add_player(string name, int level) {
            User new_user(name, level);
            if (find(users.begin(), users.end(), new_user) != users.end()) {
                return false;
            }
            users.push_back(new_user);
            return true;
        }

        bool able_dungeon (const int d_level) {
            return all_of(users.begin(), users.end(), [d_level](User& user) -> bool {
                return (user.level >= d_level);
                }
            );
        }

        bool use_item(const int i_level) {
            return any_of(users.begin(), users.end(), [i_level](User& user) -> bool {
                return (user.level >= i_level);
                }
            );
        }
};

int main() {
    Party party;
    party.add_player("kim", 10);
    party.add_player("lee", 20);
    party.add_player("park", 25);
    party.add_player("choi", 30);

    cout << boolalpha;

    cout << "20level dungeon : " << [&party](){if (party.able_dungeon(20)) return "able"; return "deable"; }() << endl;
    cout << "10level dungeon : " << party.able_dungeon(10) << endl;
    cout << "35level item : " << party.use_item(35) << endl;
    cout << "30level item : " << party.use_item(30) << endl;

    return 0;
}