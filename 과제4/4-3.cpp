#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
map<string, int> word;
map<string, int>::iterator iter;

int main() {
    string line;
    string buffer;

    ifstream file("datafile.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            // split the line into words with blank
            istringstream iss(line);
            while (getline(iss, buffer, ' ')) {
                // remove , and " and . and : and ; and ? and ! from the buffer
                buffer.erase(remove(buffer.begin(), buffer.end(), ','), buffer.end());
                buffer.erase(remove(buffer.begin(), buffer.end(), '"'), buffer.end());
                buffer.erase(remove(buffer.begin(), buffer.end(), '.'), buffer.end());
                buffer.erase(remove(buffer.begin(), buffer.end(), ':'), buffer.end());
                buffer.erase(remove(buffer.begin(), buffer.end(), ';'), buffer.end());
                buffer.erase(remove(buffer.begin(), buffer.end(), '?'), buffer.end());
                buffer.erase(remove(buffer.begin(), buffer.end(), '!'), buffer.end());
                // if the word is not in the map, insert it
                if (word.find(buffer) == word.end()) {
                    word[buffer] = 1;
                } else {
                    word[buffer]++;
                }
            }
            // cout << line << endl;
        }
        file.close();
    } else {
        cout << "Unable to open file";
        return 1;
    }

    // print the result
    for (iter = word.begin(); iter != word.end(); iter++) {
        cout << iter->first << " " << iter->second << endl;
    }
    return 0;
}