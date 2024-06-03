#include <iostream>
#include <ctime>
#include <iomanip>
#include <conio.h>

#define VERSION 2

int main() {
    std::cout << "Enter the countdown time (mm:ss): ";
    #if VERSION == 1
    std::tm countdown = {};
    std::cin >> std::get_time(&countdown, "%M:%S");

    int minutes = countdown.tm_min;
    int seconds = countdown.tm_sec;
    #endif

    #if VERSION == 2
    int minutes, seconds;
    char symbol;
    std::cin >> minutes >> symbol >> seconds;
    if (symbol != ':') {
        std::cerr << "Incorrect input";
        return 1;
    }
    #endif

    int total_seconds = minutes * 60 + seconds;

    std::time_t start = std::time(nullptr);
    
    while (total_seconds > 0) {
        std::time_t current = std::time(nullptr);
        double dif = std::difftime(current, start);

        if (dif > 1.0) {
            system("cls");
            start = current;
            --total_seconds;

            int remaining_min = total_seconds / 60;
            int remaining_sec = total_seconds % 60;

            std::cout << std::setw(2) << std::setfill('0') << remaining_min << ':';
            std::cout << std::setw(2) << std::setfill('0') << remaining_sec;
        }
    }
    
    std::cout << "DING! DING! DING!" << std::endl;
    return 0;
}