#include<iostream>
#include<fstream>
#include<sstream>
#include<string>

std::string decodeLine(const std::string& line) {
    std::string result;
    int col = 0;
    for (int i = 0; i < line.size(); ) {
        unsigned char c = line[i];

        if (c >= 0x80) {
            int bytes = (c >= 0xF0) ? 4 : (c >= 0xE0) ? 3 : 2;
            result += line.substr(i, bytes);
            i += bytes;
        }
        else {
            if (c >= 0x20 && c <= 0x7E)
                result += (char)((c - 0x20 + col) % 0x5F + 0x20);
            else
                result += c;
            i++;
            col++;
        }
    }
    return result;
}

int main() {
    std::string path;
    std::cout << "path? ";
    std::cin >> path;
    std::string line;
    std::ifstream ogFile(path);

    while (std::getline(ogFile, line)) {
        std::string decoded = decodeLine(line);
        std::cout << "<p>" << std::endl 
        << decoded << std::endl << 
        "</p>" << std::endl;
    }

    return 0;
}
