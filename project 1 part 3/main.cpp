#include <iostream>
#include <fstream>
#include <sstream>

int registerToNumber(std::string reg) {
    if (reg[0] != 'R' && reg[0] != 'r') {
        return 0;
    }
    reg.erase(remove(reg.begin(), reg.end(), 'r'), reg.end());
    reg.erase(remove(reg.begin(), reg.end(), 'R'), reg.end());
    reg.erase(remove(reg.begin(), reg.end(), ','), reg.end());
    return (int)std::stoul(reg, nullptr);
}

int main() {
    std::cout << std::hex << std::showbase;

    std::string line;
    std::string original[4];
    uint32_t output;
    uint32_t Rd[8] = {0,0,0,0,0,0,0,0};
    int flagN = 0, flagZ = 0, flagC = 0, flagV = 0;
    std::ifstream File("Programming-Project-3.txt");

    while (getline (File, line)) {
        std::string lineArr[4];
        int i = 0;
        std::stringstream ss(line);
        while (ss.good()){
            ss >> lineArr[i];
            ++i;
        }

        original[0] = lineArr[0];
        original[1] = lineArr[1];
        original[2] = lineArr[2];
        original[3] = lineArr[3];

        uint32_t first = registerToNumber(lineArr[1]);
        uint32_t second = registerToNumber(lineArr[2]);
        uint32_t third = registerToNumber(lineArr[3]);

        if (lineArr[0] == "ADD" || lineArr[0] == "ADDS" || lineArr[0] == "add" || lineArr[0] == "adds") {
            output = Rd[second] + Rd[third];
        } else if(lineArr[0] == "AND" || lineArr[0] == "ANDS" || lineArr[0] == "and" || lineArr[0] == "ands" || lineArr[0] == "TST" || lineArr[0] == "tst") {
            output = Rd[second] & Rd[third];
        } else if(lineArr[0] == "ASR" || lineArr[0] == "ASRS" || lineArr[0] == "asr" || lineArr[0] == "asrs") {
            std::string thirdStr = lineArr[3];
            thirdStr.erase(remove(thirdStr.begin(), thirdStr.end(), '#'), thirdStr.end());
            third = std::stoul(thirdStr, nullptr, 16);
            int32_t signedNum = registerToNumber(lineArr[2]);
            output = signedNum >> Rd[third];
        } else if(lineArr[0] == "LSR" || lineArr[0] == "LSRS" || lineArr[0] == "lsr" || lineArr[0] == "lsrs") {
            std::string thirdStr = lineArr[3];
            thirdStr.erase(remove(thirdStr.begin(), thirdStr.end(), '#'), thirdStr.end());
            third = std::stoul(thirdStr, nullptr, 16);
            output = Rd[second] >> Rd[third];
        } else if(lineArr[0] == "LSL" || lineArr[0] == "LSLS" || lineArr[0] == "lsl" || lineArr[0] == "lsls") {
            std::string thirdStr = lineArr[3];
            thirdStr.erase(remove(thirdStr.begin(), thirdStr.end(), '#'), thirdStr.end());
            third = std::stoul(thirdStr, nullptr, 16);
            output = Rd[second] << Rd[third];
        } else if(lineArr[0] == "NOT" || lineArr[0] == "NOTS" || lineArr[0] == "not" || lineArr[0] == "nots") {
            output = ~Rd[second];
        } else if(lineArr[0] == "ORR" || lineArr[0] == "ORRS" || lineArr[0] == "orr" || lineArr[0] == "orrs") {
            output = Rd[second] | Rd[third];
        } else if(lineArr[0] == "SUB" || lineArr[0] == "SUBS" || lineArr[0] == "sub" || lineArr[0] == "subs" || lineArr[0] == "CMP" || lineArr[0] == "cmp") {
            output = Rd[second] - Rd[third];
        } else if(lineArr[0] == "XOR" || lineArr[0] == "XORS" || lineArr[0] == "xor" || lineArr[0] == "xors") {
            output = Rd[second] ^ Rd[third];
        } else if(lineArr[0] == "MOV" || lineArr[0] == "mov") {
            std::string secondStr = lineArr[2];
            secondStr.erase(remove(secondStr.begin(), secondStr.end(), '#'), secondStr.end());
            second = std::stoul(secondStr, nullptr, 16);

            Rd[first] = second;

        } else {
            continue;
        }

        if (lineArr[0] != "MOV" && lineArr[0] != "mov" && lineArr[0] != "TST" && lineArr[0] != "tst" && lineArr[0] != "CMP" && lineArr[0] != "cmp") {
            Rd[first] = output;
        }

        if (lineArr[0].back() == 'S' || lineArr[0].back() == 's') {
            flagN = (int)output < 0;
            flagZ = (output == 0);
        }

        std::cout << original[0] << " " << original[1] << " " << original[2] << ": " << output << std::endl;
        std::cout << "R0: " << Rd[0] << " ";
        std::cout << "R1: " << Rd[1] << " ";
        std::cout << "R2: " << Rd[2] << " ";
        std::cout << "R3: " << Rd[3] << " " << std::endl;
        std::cout << "R4: " << Rd[4] << " ";
        std::cout << "R5: " << Rd[5] << " ";
        std::cout << "R6: " << Rd[6] << " ";
        std::cout << "R7: " << Rd[7] << " " << std::endl;
        std::cout << "N: " << flagN << " Z: " << flagZ << " C: " << flagC << " V: " << flagV << std::endl;
        std::cout << std::endl;
    }

    File.close();
    return 0;
}