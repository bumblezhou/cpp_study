#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

class Cube {
    public:
        Cube(const string side_colors) {
            if (side_colors.length() != 6) {
                throw "Invalid args";
            }
            this->top = side_colors[0];
            this->front = side_colors[1];
            this->right = side_colors[2];
            this->left = side_colors[3];
            this->back = side_colors[4];
            this->bottom = side_colors[5];
        }
        
        bool is_the_same_way_cube(Cube c) {
            vector<string> possible_strings = c.get_possible_strings();
            // sort(possible_strings.begin(), possible_strings.end());
            // for (auto &str: possible_strings)
            //     std::cout << str << " ";
            // std::cout << std::endl;
            vector<string> self_possible_strings = get_possible_strings();
            // sort(self_possible_strings.begin(), self_possible_strings.end());
            // for (auto &str: self_possible_strings)
            //     std::cout << str << " ";
            // std::cout << std::endl;
            bool result = true;
            for (auto &str : possible_strings) {
                if (find(self_possible_strings.begin(), self_possible_strings.end(), str) == self_possible_strings.end()) {
                    result = false;
                    break;
                }
            }
            return result;
        }
        
        ~Cube(){}

    private:
        string top, front, right, left, back, bottom;
        
        vector<string> get_possible_strings() {
            vector<string> result;
            string rotatable_sides = string(front) + string(left) + string(back) + string(right);
            int i;
            for(i = 0; i < 4; i++) {
                rotatable_sides = rotate_string(rotatable_sides, 1);
                result.push_back(top + rotatable_sides + bottom);
            }
            return result;
        }
        
        string rotate_string(const string& str, int amount) {
            amount %= str.size();
            if (amount < 0) {
                amount += str.size();
            }
            return str.substr(amount) + str.substr(0, amount);
        }
};

int main()
{
    auto input_lines = vector<string>({
        "rbgggrrggbgr",
        "rrrbbbrrbbbr",
        "rbgrbgrrrrrg"
    });
    for (auto &line : input_lines) {
        Cube cube_a(line.substr(6));
        Cube cube_b(line.substr(0, 6));
        bool is_the_same_way_cube = cube_b.is_the_same_way_cube(cube_a);
        if(is_the_same_way_cube) {
            std::cout << line << " is the same way cubes" << std::endl;
        } else {
            std::cout << line << " is NOT the same way cubes" << std::endl;
        }
    }
    
    return 0;
}