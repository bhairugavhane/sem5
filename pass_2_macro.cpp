#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include<algorithm>

class Pass2 {
public:
    std::unordered_map<std::string, std::vector<int>> mnt;
    std::unordered_map<std::string, std::vector<std::string>> pntab;
    std::unordered_map<std::string, std::string> kpdt;
    std::string output;
    std::unordered_map<int, std::string> aptab;
    int current_macro;

    Pass2() : current_macro(0) {}

    void readFiles() {
        mnt = {
            {"M1", {2, 2, 1, 1}},
            {"M2", {2, 2, 6, 3}}
        };

        pntab = {
            {"M1", {"X", "Y", "A", "B"}},
            {"M2", {"P", "Q", "U", "V"}}
        };

        kpdt = {
            {"A", "AREG"},
            {"B", ""},
            {"U", "CREG"},
            {"V", "DREG"}
        };
    }

    void process() {
        std::ifstream icFile("intermediate.txt");
        std::ifstream mdtFile("mdt.txt");

        std::string line;

        while (std::getline(icFile, line)) {
            std::vector<std::string> word;
            std::istringstream iss(line);
            std::string token;

            while (iss >> token) {
                word.push_back(token);
            }

            if (mnt.find(word[0]) == mnt.end()) {
                output += line + "\n";
            } else {
                current_macro++;
                aptab.clear();
                auto MNT = mnt[word[0]];
                int pp = MNT[0];
                int kp = MNT[1];

                for (int i = 1; i <= pp; ++i) {
                    aptab[i] = word[i];
                }

                for (int i = pp + 1; i <= pp + kp; ++i) {
                    if (word[i].find('=') == std::string::npos) {
                        int parameter_index = std::stoi(word[i].substr(3));
                        aptab[i] = kpdt[word[i].substr(0, word[i].find('='))];
                    } else {
                        aptab[i] = word[i].substr(word[i].find('=') + 1);
                    }
                }

                while (std::getline(mdtFile, line)) {
                    std::istringstream mdtLine(line);
                    std::vector<std::string> wordMDT;
                    std::string tokenMDT;

                    while (mdtLine >> tokenMDT) {
                        wordMDT.push_back(tokenMDT);
                    }

                    if (wordMDT[0] != "MEND") {
                        output += wordMDT[0] + "\t";

                        for (size_t i = 1; i < wordMDT.size(); ++i) {
                            if (wordMDT[i].find('=') == std::string::npos) {
                                int parameter_index = std::stoi(wordMDT[i].substr(3));
                                output += aptab[parameter_index] + "\t";
                            } else {
                                output += wordMDT[i] + "\t";
                            }
                        }

                        output += "\n";
                    } else {
                        break;
                    }
                }
            }
        }

        std::cout << output;
    }
};

int main() {
    Pass2 test;
    test.readFiles();
    test.process();

    return 0;
}
