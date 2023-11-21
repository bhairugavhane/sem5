#include<bits/stdc++.h>
using namespace std;
class Pass1 {
public:
    int count_pp;
    int count_kp;
    string mnt;
    string pntab;
    int mdtp;
    int kptp;
    string kpdt;
    int macro_count;
    string ic;
    string mdt;

    Pass1() : count_pp(0), count_kp(0), mdtp(1), kptp(1), macro_count(0) {}

    void process() {
        bool NEXT_MACRO = false;
        bool IS_START = false;
        ifstream file("input.asm");
        string line;
        
        while (getline(file, line)) {
            if (line.find("START") != string::npos || IS_START) {
                ic += line;
                IS_START = true;
            } else {
                vector<std::string> word;
                istringstream iss(line);
                string token;
                while (iss >> token) {
                    word.push_back(token);
                }

                if (NEXT_MACRO) {
                    count_kp = 0;
                    count_pp = 0;
                    string macro_name = word[0];
                    pntab += macro_name + "\t";
                    //-------------------------------------------------------------------------
                    for (size_t i = 1; i < word.size(); ++i) {
                        if (word[i].find("=") != string::npos) {
                            count_kp++;
                            string parameter_name = word[i].substr(0, word[i].find("="));
                            string given_name = word[i].substr(word[i].find("=") + 1);
                            pntab += parameter_name + "\t";
                            kpdt += parameter_name + "\t" + given_name + "\n";
                        } else {
                            pntab += word[i] + "\t";
                            count_pp++;
                        }
                    }
                    //---------------------------------------------------------------------------

                    pntab += "\n";
                    mnt += macro_name + "\t" + to_string(count_pp) + "\t" + to_string(count_kp)
                        + "\t" + to_string(mdtp) + "\t" + to_string(kptp) + "\n";
                    kptp += count_kp;
                    NEXT_MACRO = false;

                } else if (word[0] == "MACRO") {
                    macro_count++;
                    NEXT_MACRO = true;

                } else {
                    std::string string = word[0] + "\t";
                    vector<std::string> parameters;
                    istringstream pntabStream(pntab);
                    std::string pntabLine ;
                
                    while (getline(pntabStream, pntabLine)) {
                        istringstream pntabLineStream(pntabLine);
                        std::string param;
                        while (pntabLineStream >> param) {
                            parameters.push_back(param);
                        }
                    }

                    for (size_t i = 1; i < word.size(); ++i) {
                        if (word[i].find('=') != string::npos) {
                            string += word[i] + "\t";
                        } else {
                            auto index = std::find(parameters.begin(), parameters.end(), word[i]) - parameters.begin();
                            string += "(P," + std::to_string(index) + ")\t";
                        }
                        
                    }

                    mdtp++;
                    string += "\n";
                    mdt += string;
                }
            }
        }

        cout << string(8, '*') << "MDT" << string(8, '*') << endl;
        cout << mdt;
        cout << string(8, '*') << "MNT" << string(8, '*') << endl;
        cout << mnt;
        cout << string(8, '*') << "PNTAB" << string(8, '*') << endl;
        cout << pntab;
        cout << string(8, '*') << "KPDT" << string(8, '*') << endl;
        cout << kpdt;
        cout << string(8, '*') << "IC" << string(8, '*') << endl;
        cout << ic;
    }
};

int main() {
    Pass1 test;
    test.process();

    return 0;
}
