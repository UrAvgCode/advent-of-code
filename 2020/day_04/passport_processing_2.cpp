// --- Day 4: Passport Processing --- Part Two ---

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

bool validatePassport(const unordered_map<string, string> &passport) {
    int birthYear = stoi(passport.at("byr"));
    if (birthYear < 1920 || birthYear > 2002) return false;

    int issueYear = stoi(passport.at("iyr"));
    if (issueYear < 2010 || issueYear > 2020) return false;

    int expirationYear = stoi(passport.at("eyr"));
    if (expirationYear < 2020 || expirationYear > 2030) return false;

    string hgt = passport.at("hgt");
    string unit = hgt.substr(hgt.size() - 2, 2);
    int height = stoi(hgt.substr(0, hgt.size() - 2));

    if (unit == "cm" && (height < 150 || height > 193)) return false;
    if (unit == "in" && (height < 59 || height > 76)) return false;
    if (unit != "in" && unit != "cm") return false;

    string hairColor = passport.at("hcl");
    if (hairColor[0] != '#') return false;
    for (unsigned char c: hairColor.substr(1, hairColor.size() - 1)) {
        int ascii = int(c);
        if ((ascii < 48 || ascii > 57) && (ascii < 97 || ascii > 102)) return false;
    }

    unordered_set<string> possibleColors = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
    string eyeColor = passport.at("ecl");
    if (possibleColors.find(eyeColor) == possibleColors.end()) return false;

    string passportID = passport.at("pid");
    if (passportID.size() != 9) return false;
    for (char c: passportID) {
        if (!isdigit(c)) return false;
    }

    return true;
}

int main() {
    int validPassportCount = 0;

    ifstream fileReader("2020/day_04/passport_processing_input");

    string line;
    unordered_map<string, string> passport;
    while (getline(fileReader, line)) {
        if (line.empty()) {
            if (passport.size() == 7 && validatePassport(passport)) {
                validPassportCount++;
            }
            passport.clear();
        } else {
            line += " ";
            while (!line.empty()) {
                int colonIndex = (int) line.find(':');
                int spaceIndex = (int) line.find(' ');

                string field = line.substr(0, colonIndex);
                string value = line.substr(colonIndex + 1, spaceIndex - (colonIndex + 1));

                if (field != "cid") passport[field] = value;

                line = line.substr(spaceIndex + 1, line.size() - (spaceIndex + 1));
            }
        }
    }

    cout << "Part 2: " << validPassportCount << "\n";

    fileReader.close();
}
