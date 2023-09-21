#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ifstream file("D:\\Downloads\\tmp\\Eoffice.txt"); // 替换为你的txt文件路径

    if (file.is_open()) {
        string line;
        int lineCount = 1;

        while (std::getline(file, line)) {
            int start = 10;
            int end = 1900;

            if (lineCount >= start && lineCount <= end) {
                // 去除末尾的换行符
                if (!line.empty() && line[line.length() - 1] == '\n') {
                    line = line.substr(0, line.length() - 1);
                }
                std::cout << "行数: " << lineCount << ", 内容: " << line << std::endl;
            }
            lineCount++;

            if (lineCount > end) {
                break; // 达到100行后停止读取
            }
        }

        file.close();
    }
    else {
        cout << "无法打开文件." << endl;
    }

    return 0;
}