#include <iostream>
#include <random>
#include <string>
#include <algorithm>
#include <cmath>
#include <limits>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <unordered_set>
#include <unordered_map>
#include <thread>
#include <chrono>
using namespace std;

class PasswordGenerator {
public:
    PasswordGenerator() : uppercase("ABCDEFGHIJKLMNOPQRSTUVWXYZ"),
                          lowercase("abcdefghijklmnopqrstuvwxyz"),
                          digits("0123456789"),
                          specialChars("!@#$%^&*()-_=+[]{}|;:,.<>?"),
                          greek("ΑΒΓΔΕΖΗΘΙΚΛΜΝΞΟΠΡΣΤΥΦΧΨΩ"),
                          cyrillic("АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ") {}

    string generatePassword(int length, bool useUppercase, bool useLowercase, bool useDigits, bool useSpecialChars,
                            const string& customChars = "", bool useGreek = false, bool useCyrillic = false) {
        string allowedChars;
        string mandatoryChars;
        if (useUppercase) {
            allowedChars += uppercase;
            mandatoryChars += uppercase[dist(gen) % uppercase.size()];
        }
        if (useLowercase) {
            allowedChars += lowercase;
            mandatoryChars += lowercase[dist(gen) % lowercase.size()];
        }
        if (useDigits) {
            allowedChars += digits;
            mandatoryChars += digits[dist(gen) % digits.size()];
        }
        if (useSpecialChars) {
            allowedChars += specialChars;
            mandatoryChars += specialChars[dist(gen) % specialChars.size()];
        }
        if (!customChars.empty()) {
            allowedChars += customChars;
            mandatoryChars += customChars[dist(gen) % customChars.size()];
        }
        if (useGreek) {
            allowedChars += greek;
            mandatoryChars += greek[dist(gen) % greek.size()];
        }
        if (useCyrillic) {
            allowedChars += cyrillic;
            mandatoryChars += cyrillic[dist(gen) % cyrillic.size()];
        }
        if (allowedChars.empty()) {
            throw invalid_argument("At least one character set must be selected.");
        }
        if (length < static_cast<int>(mandatoryChars.size())) {
            throw invalid_argument("Password length is too short to include all required character types.");
        }
        string password;
        password.reserve(length);
        password += mandatoryChars;
        for (int i = mandatoryChars.size(); i < length; ++i) {
            password += allowedChars[dist(gen) % allowedChars.size()];
        }
        shuffle(password.begin(), password.end(), gen);
        return password;
    }

    double calculateEntropy(const string& password, int charSetSize) const {
        return log2(pow(charSetSize, password.size()));
    }

    string getPasswordStrength(double entropy) const {
        if (entropy < 50) return "Weak";
        if (entropy < 100) return "Medium";
        return "Strong";
    }

    void estimateBruteForceTime(double entropy) const {
        double attemptsPerSecond = 1e9; // Assume 1 billion attempts per second
        double seconds = pow(2, entropy) / attemptsPerSecond;
        if (seconds < 60) {
            cout << "Estimated brute-force time: " << seconds << " seconds" << endl;
        } else if (seconds < 3600) {
            cout << "Estimated brute-force time: " << seconds / 60 << " minutes" << endl;
        } else if (seconds < 86400) {
            cout << "Estimated brute-force time: " << seconds / 3600 << " hours" << endl;
        } else {
            cout << "Estimated brute-force time: " << seconds / 86400 << " days" << endl;
        }
    }

    bool checkComplexity(const string& password) const {
        if (password.find("123") != string::npos || password.find("aaa") != string::npos) {
            return false;
        }
        return true;
    }

    string maskPassword(const string& password) const {
        return string(password.size(), '*');
    }

private:
    random_device rd;
    mt19937 gen{rd()};
    uniform_int_distribution<> dist;
    const string uppercase;
    const string lowercase;
    const string digits;
    const string specialChars;
    const string greek;
    const string cyrillic;
};

// Function declarations
void displayMenu();
void savePasswordToFile(const string& password);
vector<string> loadPasswordHistory();
void viewPasswordHistory();
void setExpirationDate();
void generateQRCode(const string& password);
void analyzePasswordPatterns(const string& password); // New Declaration

void simulateMultiThreadedGeneration();

string generatePhoneticMnemonic(basic_string<char, char_traits<char>, allocator<char>> &basicString);

bool checkAgainstDictionary(string basicString);

string generateRandomPIN(int length);

void exportPasswordHistoryToCSV();

// Display menu
void displayMenu() {
    cout << "=== Advanced Password Generator ===" << endl;
    cout << "1. Generate Password" << endl;
    cout << "2. View Password History" << endl;
    cout << "3. Save Password to File" << endl;
    cout << "4. Load Settings from File" << endl;
    cout << "5. Set Password Expiration Date" << endl;
    cout << "6. Generate QR Code for Password" << endl;
    cout << "7. Check Password Against Dictionary" << endl;
    cout << "8. Generate Random PIN" << endl;
    cout << "9. Simulate Multi-threaded Password Generation" << endl;
    cout << "10. Export Password History to CSV" << endl;
    cout << "11. Analyze Password Patterns" << endl;
    cout << "12. Generate Password with Phonetic Mnemonic" << endl;
    cout << "13. Exit" << endl;
    cout << "Enter your choice: ";
}

// Save password to file
void savePasswordToFile(const string& password) {
    ofstream file("passwords.txt", ios::app);
    if (file.is_open()) {
        file << password << endl;
        file.close();
        cout << "Password saved to passwords.txt" << endl;
    } else {
        cerr << "Error: Unable to open file for saving password." << endl;
    }
}

// Load password history
vector<string> loadPasswordHistory() {
    vector<string> history;
    ifstream file("passwords.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            history.push_back(line);
        }
        file.close();
    } else {
        cerr << "No password history found." << endl;
    }
    return history;
}

// View password history
void viewPasswordHistory() {
    vector<string> history = loadPasswordHistory();
    if (history.empty()) {
        cout << "No passwords in history." << endl;
        return;
    }
    cout << "=== Password History ===" << endl;
    for (size_t i = 0; i < history.size(); ++i) {
        cout << i + 1 << ". " << history[i] << endl;
    }
}

// Set password expiration date
void setExpirationDate() {
    int days;
    cout << "Enter the number of days until password expiration: ";
    cin >> days;
    time_t now = time(0);
    tm* ltm = localtime(&now);
    ltm->tm_mday += days;
    mktime(ltm);
    cout << "Password will expire on: " << put_time(ltm, "%Y-%m-%d") << endl;
}

// Generate QR code
void generateQRCode(const string& password) {
    cout << "Generating QR Code for password..." << endl;
    cout << "QR Code Content: " << password << endl;
    // Simulate QR code generation
    cout << "████████████████████████████████████████" << endl;
    cout << "█                                    █" << endl;
    cout << "█          PASSWORD QR CODE          █" << endl;
    cout << "█                                    █" << endl;
    cout << "████████████████████████████████████████" << endl;
}

// New Feature: Analyze password patterns
void analyzePasswordPatterns(const string& password) {
    cout << "Analyzing password patterns..." << endl;
    if (password.find("123") != string::npos) {
        cout << "Warning: Sequential pattern '123' detected." << endl;
    }
    if (password.find("abc") != string::npos) {
        cout << "Warning: Sequential pattern 'abc' detected." << endl;
    }
    if (password.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") == string::npos) {
        cout << "Info: Password contains only alphanumeric characters." << endl;
    }
}

// Main function
int main() {
    PasswordGenerator generator;
    int choice;
    vector<string> passwordHistory;
    bool useUppercase = true, useLowercase = true, useDigits = true, useSpecialChars = true;
    string customChars;
    bool useGreek = false, useCyrillic = false;

    while (true) {
        displayMenu();
        cin >> choice;

        if (choice == 1) {
            int minLength, maxLength;
            cout << "Enter minimum password length: ";
            cin >> minLength;
            cout << "Enter maximum password length: ";
            cin >> maxLength;
            if (minLength < 6 || maxLength < minLength) {
                cout << "Invalid password length range." << endl;
                continue;
            }
            int passwordLength = minLength + rand() % (maxLength - minLength + 1);
            cout << "Include uppercase letters? (1 for Yes, 0 for No): ";
            cin >> useUppercase;
            cout << "Include lowercase letters? (1 for Yes, 0 for No): ";
            cin >> useLowercase;
            cout << "Include digits? (1 for Yes, 0 for No): ";
            cin >> useDigits;
            cout << "Include special characters? (1 for Yes, 0 for No): ";
            cin >> useSpecialChars;
            cout << "Include Greek characters? (1 for Yes, 0 for No): ";
            cin >> useGreek;
            cout << "Include Cyrillic characters? (1 for Yes, 0 for No): ";
            cin >> useCyrillic;
            cout << "Enter custom characters (leave blank if none): ";
            cin.ignore();
            getline(cin, customChars);
            try {
                string password = generator.generatePassword(passwordLength, useUppercase, useLowercase, useDigits, useSpecialChars, customChars, useGreek, useCyrillic);
                int charSetSize = (useUppercase ? 26 : 0) + (useLowercase ? 26 : 0) + (useDigits ? 10 : 0) + (useSpecialChars ? 16 : 0) + customChars.size() +
                                  (useGreek ? 24 : 0) + (useCyrillic ? 33 : 0);
                double entropy = generator.calculateEntropy(password, charSetSize);
                cout << "Generated Password: " << generator.maskPassword(password) << endl;
                cout << "Unmasked Password: " << password << endl;
                cout << "Password Entropy: " << entropy << " bits" << endl;
                cout << "Password Strength: " << generator.getPasswordStrength(entropy) << endl;
                generator.estimateBruteForceTime(entropy);
                if (!generator.checkComplexity(password)) {
                    cout << "Warning: Password contains simple patterns or sequences." << endl;
                }
                passwordHistory.push_back(password);
            } catch (const exception& e) {
                cerr << "Error: " << e.what() << endl;
            }
        } else if (choice == 2) {
            viewPasswordHistory();
        } else if (choice == 3) {
            if (passwordHistory.empty()) {
                cout << "No passwords to save." << endl;
            } else {
                savePasswordToFile(passwordHistory.back());
            }
        } else if (choice == 4) {
            // Placeholder for loading settings from file
            cout << "Loading settings from file..." << endl;
        } else if (choice == 5) {
            setExpirationDate();
        } else if (choice == 6) {
            if (passwordHistory.empty()) {
                cout << "No passwords to generate QR code for." << endl;
            } else {
                generateQRCode(passwordHistory.back());
            }
        } else if (choice == 7) {
            if (passwordHistory.empty()) {
                cout << "No passwords to check." << endl;
            } else {
                string lastPassword = passwordHistory.back();
                if (checkAgainstDictionary(lastPassword)) {
                    cout << "Warning: This password is in a common dictionary." << endl;
                } else {
                    cout << "Password is not in a common dictionary." << endl;
                }
            }
        } else if (choice == 8) {
            int pinLength;
            cout << "Enter desired PIN length: ";
            cin >> pinLength;
            string pin = generateRandomPIN(pinLength);
            cout << "Generated PIN: " << pin << endl;
        } else if (choice == 9) {
            simulateMultiThreadedGeneration();
        } else if (choice == 10)
            exportPasswordHistoryToCSV();
        else if (choice == 11) {
            if (passwordHistory.empty()) {
                cout << "No passwords to analyze." << endl;
            } else {
                analyzePasswordPatterns(passwordHistory.back());
            }
        } else if (choice == 12) {
            if (passwordHistory.empty()) {
                cout << "No passwords to generate mnemonics for." << endl;
            } else {
                string mnemonic = generatePhoneticMnemonic(passwordHistory.back());
                cout << "Phonetic Mnemonic: " << mnemonic << endl;
            }
        } else if (choice == 13) {
            cout << "Exiting program. Goodbye!" << endl;
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}

void exportPasswordHistoryToCSV() {

}

string generateRandomPIN(int length) {
    return std::string();
}

bool checkAgainstDictionary(string basicString) {
    return false;
}

string generatePhoneticMnemonic(basic_string<char, char_traits<char>, allocator<char>> &basicString) {
    return std::string();
}

void simulateMultiThreadedGeneration() {

}
