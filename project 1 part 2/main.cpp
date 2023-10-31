#include <cstdint>
#include <iostream>
#include <fstream>
#include <sstream>

class Simulator {
public:
    void run(const std::string& fileName);
    void ADD(std::string lineArr[], uint32_t* output);
    void AND(std::string lineArr[], uint32_t* output);
    void ASR(std::string lineArr[], uint32_t* output);
    void LSR(std::string lineArr[], uint32_t* output);
    void LSL(std::string lineArr[], uint32_t* output);
    void NOT(std::string lineArr[], uint32_t* output);
    void ORR(std::string lineArr[], uint32_t* output);
    void SUB(std::string lineArr[], uint32_t* output);
    void XOR(std::string lineArr[], uint32_t* output);
};

void Simulator::run(const std::string& fileName) {
    std::cout << std::hex << std::showbase;

    std::string line;
    uint32_t output;
    int flagN, flagZ;
    std::ifstream File(fileName);

    while (getline (File, line)) {
        std::string lineArr[3];
        int i = 0;
        std::stringstream ss(line);
        while (ss.good()){
            ss >> lineArr[i];
            ++i;
        }

        if (lineArr[0] == "ADD" || lineArr[0] == "ADDS") {
            Simulator::ADD(lineArr, &output);
        } else if(lineArr[0] == "AND" || lineArr[0] == "ANDS") {
            Simulator::AND(lineArr, &output);
        } else if(lineArr[0] == "ASR" || lineArr[0] == "ASRS") {
            Simulator::ASR(lineArr, &output);
        } else if(lineArr[0] == "LSR" || lineArr[0] == "LSRS") {
            Simulator::LSR(lineArr, &output);
        } else if(lineArr[0] == "LSL" || lineArr[0] == "LSLS") {
            Simulator::LSL(lineArr, &output);
        } else if(lineArr[0] == "NOT" || lineArr[0] == "NOTS") {
            Simulator::NOT(lineArr, &output);
        } else if(lineArr[0] == "ORR" || lineArr[0] == "ORRS") {
            Simulator::ORR(lineArr, &output);
        } else if(lineArr[0] == "SUB" || lineArr[0] == "SUBS") {
            Simulator::SUB(lineArr, &output);
        } else if(lineArr[0] == "XOR" || lineArr[0] == "XORS") {
            Simulator::XOR(lineArr, &output);
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
}

void Simulator::ADD(std::string lineArr[], uint32_t* output) {
    uint32_t first = std::stoul(lineArr[1], nullptr, 16);
    uint32_t second = std::stoul(lineArr[2], nullptr, 16);
    *output = first + second;
}

void Simulator::AND(std::string lineArr[], uint32_t* output) {
    uint32_t first = std::stoul(lineArr[1], nullptr, 16);
    uint32_t second = std::stoul(lineArr[2], nullptr, 16);
    *output = first & second;
}

void Simulator::ASR(std::string *lineArr, uint32_t *output) {
    uint32_t first = std::stoul(lineArr[1], nullptr, 16);
    *output = (int)first >> 1;
}

void Simulator::LSR(std::string *lineArr, uint32_t *output) {
    uint32_t first = std::stoul(lineArr[1], nullptr, 16);
    *output = first >> 1;
}

void Simulator::LSL(std::string *lineArr, uint32_t *output) {
    uint32_t first = std::stoul(lineArr[1], nullptr, 16);
    *output = first << 1;
}

void Simulator::NOT(std::string *lineArr, uint32_t *output) {
    uint32_t first = std::stoul(lineArr[1], nullptr, 16);
    *output = ~first;
}

void Simulator::ORR(std::string *lineArr, uint32_t *output) {
    uint32_t first = std::stoul(lineArr[1], nullptr, 16);
    uint32_t second = std::stoul(lineArr[2], nullptr, 16);
    *output = first | second;
}

void Simulator::SUB(std::string *lineArr, uint32_t *output) {
    uint32_t first = std::stoul(lineArr[1], nullptr, 16);
    uint32_t second = std::stoul(lineArr[2], nullptr, 16);
    *output = first - second;
}

void Simulator::XOR(std::string *lineArr, uint32_t *output) {
    uint32_t first = std::stoul(lineArr[1], nullptr, 16);
    uint32_t second = std::stoul(lineArr[2], nullptr, 16);
    *output = first ^ second;
}

int main() {
    Simulator simulator;
    simulator.run("Programming-Project-2.txt");
    return 0;
}