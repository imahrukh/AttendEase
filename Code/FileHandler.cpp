#include <fstream>

class FileHandler {
public:
    static void saveData(const std::string& filename, const std::string& data) {
        ofstream file(filename);
        if (file.is_open()) {
            file << data;
            file.close();
            std::cout << "Data saved to " << filename << "\n";
        } else {
            std::cerr << "Error opening file.\n";
        }
    }

    static string loadData(const std::string& filename) {
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
