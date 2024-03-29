#include <cstdint>
#include <iostream>
#include <fstream>
#include <sstream>

void ADD(std::string lineArr[3]) {
    uint32_t first = std::stoul(lineArr[1], nullptr, 16);
    uint32_t second = std::stoul(lineArr[2], nullptr, 16);
    uint32_t sum = first + second;
    std::cout << lineArr[0] << " " << lineArr[1] << " " << lineArr[2] << ": " << sum << std::endl;
    std::cout << "Overflow: ";
    if (sum < first || sum < second) {
        std::cout << "yes";
    } else {
        std::cout << "no";
    }

    std::cout << std::endl << std::endl;
}

void readInput(const std::string& fileName) {
    std::string line;

    std::ifstream File(fileName);

    while (getline (File, line)) {
        std::string lineArr[3];
        int i = 0;
        std::stringstream ss(line);
        while (ss.good()){
            ss >> lineArr[i];
            ++i;
        }

        if (lineArr[0] == "ADD") {
            ADD(lineArr);
        }
    }

    File.close();
}

int main() {
    std::cout << std::hex << std::showbase;
    readInput("Programming-Project-1.txt");
    return 0;
}