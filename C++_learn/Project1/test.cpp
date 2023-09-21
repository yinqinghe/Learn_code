#include <vector>
#include <string>
#include <iostream>
using namespace std;
// Global vector
std::vector<std::string> globalVector;

// Function to add string to global vector
void addStringToVector(const std::string& str) {
    globalVector.push_back(str);
}

int main() {
    addStringToVector("Hello");
    addStringToVector("World");

    // Print all strings in the vector
    for (const auto& str : globalVector) {
        cout << str << endl;
    }

    return 0;
}