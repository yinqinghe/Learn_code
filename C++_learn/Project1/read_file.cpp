#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ifstream file("D:\\Downloads\\tmp\\Eoffice.txt"); // �滻Ϊ���txt�ļ�·��

    if (file.is_open()) {
        string line;
        int lineCount = 1;

        while (std::getline(file, line)) {
            int start = 10;
            int end = 1900;

            if (lineCount >= start && lineCount <= end) {
                // ȥ��ĩβ�Ļ��з�
                if (!line.empty() && line[line.length() - 1] == '\n') {
                    line = line.substr(0, line.length() - 1);
                }
                std::cout << "����: " << lineCount << ", ����: " << line << std::endl;
            }
            lineCount++;

            if (lineCount > end) {
                break; // �ﵽ100�к�ֹͣ��ȡ
            }
        }

        file.close();
    }
    else {
        cout << "�޷����ļ�." << endl;
    }

    return 0;
}