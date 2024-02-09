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

// vector<vector<set<char>>> get_raw_matched_words(const string &morse_code_line) {

// }

int main()
{
    vector<vector<set<char>>> matched_words;
    

    return 0;
}
