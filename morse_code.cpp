#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>

using namespace std;

map<char, string> morse_code_mappings = {
    {'A', ".-"},
    {'B', "-..."},
    {'C', "-.-."},
    {'D', "-.."},
    {'E', "."},
    {'F', "..-."},
    {'G', "--."},
    {'H', "...."},
    {'I', ".."},
    {'J', ".---"},
    {'K', "-.-"},
    {'L', ".-.."},
    {'M', "--"},
    {'N', "-."},
    {'O', "---"},
    {'P', ".--."},
    {'Q', "--.-"},
    {'R', ".-."},
    {'S', "..."},
    {'T', "-"},
    {'U', "..-"},
    {'V', "...-"},
    {'W', ".--"},
    {'X', "-..-"},
    {'Y', "-.--"},
    {'Z', "--.."},
    {'0', "------"},
    {'1', ".-----"},
    {'2', "..---"},
    {'3', "...--"},
    {'4', "....-"},
    {'5', "....."},
    {'6', "-...."},
    {'7', "--..."},
    {'8', "---.."},
    {'9', "----."}
};

vector<string> context_words = {
    "AN",
    "EARTHQUAKE",
    "EAT",
    "GOD",
    "HATH",
    "IM",
    "READY",
    "TO",
    "WHAT",
    "WROTH"
};

vector<string> input_morse_codes = {
    ".--.....-- .....--....",
    "--.----.. .--.-.----..",
    ".--.....-- .--.",
    "..-.-.-....--.-..-.--.-.",
    "..-- .-...--..-.--",
    "---- ..--"
};

vector<set<char>> get_raw_matched_words(const string &morse_code_line) {
    int i, j, line_len = morse_code_line.length();
    vector<set<char>> possible_char_list;
    for(i = 0; i < line_len; i++) {
        set<char> possible_char;
        for (j = i; j < line_len - i; j++) {
            string temp = morse_code_line.substr(i, j);
            for (auto it = morse_code_mappings.begin(); it != morse_code_mappings.end(); ++it) {
                if (it->second == temp) {
                    possible_char.insert(it->first);
                    break;
                }
            }
        }
        possible_char_list.push_back(possible_char);
    }
    return possible_char_list;
}

int main()
{
    vector<vector<set<char>>> matched_words;
    

    return 0;
}
