#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <ctime>
#include <iomanip>
#include <limits>

std::ostream& operator<<(std::ostream& os, const std::tm& t) {
    os << std::put_time(&t, "%Y-%m-%d");
    return os;
}

bool operator<(const std::tm& lhs, const std::tm& rhs) {
    if (lhs.tm_year != rhs.tm_year) return lhs.tm_year < rhs.tm_year;
    if (lhs.tm_mon != rhs.tm_mon) return lhs.tm_mon < rhs.tm_mon;
    return lhs.tm_mday < rhs.tm_mday;
}

void PrintMessage(const std::map<std::tm, std::vector<std::string>>& friends, bool is_today = false) {
    for (const auto& pair : friends) {
        if (is_today) {
            std::cout << "Today is " << pair.first << ". Happy birthday to: ";
            for (const auto& name : pair.second) {
                std::cout << name << " ";
            }
            std::cout << std::endl;
        } else {
            std::cout << "Next birthday is on " << pair.first << " will be celebrated by: ";
            for (const auto& name : pair.second) {
                std::cout << name << " ";
            }
            std::cout << std::endl;
        }
    }
}

int main() {
    std::map<std::tm, std::vector<std::string>> friends;
    std::string input;

    while (true) {
        std::cout << "Enter friend's name and birthday (YYYY/MM/DD) or type 'end' to finish: ";
        std::string name;
        std::cin >> name;
        if (name == "end") break;

        std::tm date = {};
        std::cin >> std::get_time(&date, "%Y/%m/%d");
        if (std::cin.fail()) {
            std::cerr << "Invalid date format. Please try again." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        friends[date].push_back(name);
    }

    std::time_t current_time = std::time(nullptr);
    std::tm* current_tm = std::localtime(&current_time);

    std::map<std::tm, std::vector<std::string>> today_birthdays;
    std::map<std::tm, std::vector<std::string>> upcoming_birthdays;

    for (const auto& fr : friends) {
        if (fr.first.tm_mon == current_tm->tm_mon && fr.first.tm_mday == current_tm->tm_mday) {
            today_birthdays[fr.first] = fr.second;
        } else if (fr.first.tm_mon > current_tm->tm_mon || (fr.first.tm_mon == current_tm->tm_mon && fr.first.tm_mday > current_tm->tm_mday)) {
            upcoming_birthdays[fr.first] = fr.second;
        }
    }

    if (!today_birthdays.empty()) {
        PrintMessage(today_birthdays, true);
    }

    if (!upcoming_birthdays.empty()) {
        PrintMessage(upcoming_birthdays);
    } else {
        std::cout << "No upcoming birthdays found." << std::endl;
    }

    return 0;
}
