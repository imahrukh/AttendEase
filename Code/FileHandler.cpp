#include <fstream>
#include<iostream>

using namespace std;

class FileHandler {
public:
    static void saveData(const string& filename, const string& data) {
        ofstream file(filename);
        if (file.is_open()) {
            file << data;
            file.close();
            cout << "Data saved to " << filename << "\n";
        } else {
            cerr << "Error opening file.\n";
        }
    }

    static string loadData(const string& filename) {
        ifstream file(filename);
        string data, line;
        if (file.is_open()) {
            while (getline(file, line)) {
                data += line + "\n";
            }
            file.close();
        } else {
            cerr << "Error opening file.\n";
        }
        return data;
    }
};
