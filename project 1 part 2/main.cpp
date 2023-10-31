#include <cstdint>
#include <iostream>
#include <fstream>
#include <sstream>

int main() {
    std::cout << std::hex << std::showbase;

    std::string line;
    uint32_t output;
    int flagN, flagZ;
    std::ifstream File("Programming-Project-2.txt");

    while (getline (File, line)) {
        std::string lineArr[3];
        int i = 0;
        std::stringstream ss(line);
        while (ss.good()){
            ss >> lineArr[i];
            ++i;
        }

        uint32_t first = std::stoul(lineArr[1], nullptr, 16);
        uint32_t second = 0;
        try {
            second = std::stoul(lineArr[2], nullptr, 16);
        } catch (...) {}

        if (lineArr[0] == "ADD" || lineArr[0] == "ADDS") {
            output = first + second;
        } else if(lineArr[0] == "AND" || lineArr[0] == "ANDS") {
            output = first & second;
        } else if(lineArr[0] == "ASR" || lineArr[0] == "ASRS") {
            int32_t signedNum = std::stoul(lineArr[1], nullptr, 16);
            output = signedNum >> second;
        } else if(lineArr[0] == "LSR" || lineArr[0] == "LSRS") {
            output = first >> second;
        } else if(lineArr[0] == "LSL" || lineArr[0] == "LSLS") {
            output = first << second;
        } else if(lineArr[0] == "NOT" || lineArr[0] == "NOTS") {
            output = ~first;
        } else if(lineArr[0] == "ORR" || lineArr[0] == "ORRS") {
            output = first | second;
        } else if(lineArr[0] == "SUB" || lineArr[0] == "SUBS") {
            output = first - second;
        } else if(lineArr[0] == "XOR" || lineArr[0] == "XORS") {
            output = first ^ second;
        } else {
            continue;
        }

        if (lineArr[0].back() == 'S') {
            flagN = (int)output < 0;
            flagZ = (output == 0);
        }


        std::cout << lineArr[0] << " " << lineArr[1] << " " << lineArr[2] << ": " << output << std::endl;
        std::cout << "N: " << flagN << " Z: " << flagZ << std::endl;
        std::cout << std::endl << std::endl;
    }

    File.close();
    return 0;
}