#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <iomanip>


struct Time {
    int hours = 0;
    int minutes = 0;
    int seconds = 0;
};

#pragma pack(push,1)
struct Task {
    std::string task_name = "";
    std::time_t task_begin = 0;
    std::time_t task_end = 0; 
    Time spent_time;
};
#pragma pack(pop)

void BeginTask(std::vector<Task>& tasks);
void EndTask(std::vector<Task>& tasks);
void StatusTask(const std::vector<Task>& tasks);
Time GetTimeFromSeconds(double diff);

int main() {
    std::vector<Task> tasks;

    while (true) {
        std::cout << "Enter the command (begin, end, status or exit): ";
        std::string command;
        getline(std::cin, command);

        if (command == "begin") {
            BeginTask(tasks);

        } else if (command == "end") {
            EndTask(tasks);

        } else if (command == "status") {
            StatusTask(tasks);

        } else if (command == "exit") {
            break;

        } else {
            std::cout << "Unknown command" << std::endl;
        }
    }

    return 0;
}

void BeginTask(std::vector<Task>& tasks) {
    if (!tasks.empty() && tasks.back().task_end == 0) {
        EndTask(tasks);
    }
    Task task;
    std::cout << "Enter the name of the task: ";
    getline(std::cin, task.task_name);
    task.task_begin = std::time(nullptr);
    tasks.push_back(task);
}

void EndTask(std::vector<Task>& tasks) {
    if (tasks.empty() || tasks.back().task_end != 0) return;
    tasks.back().task_end = std::time(nullptr);

    double diff = std::difftime(tasks.back().task_end, tasks.back().task_begin);
    tasks.back().spent_time = GetTimeFromSeconds(diff);
}

void StatusTask(const std::vector<Task>& tasks) {
    if (tasks.empty()) {
        std::cout << "No tasks" << std::endl;
        return;
    }

    for (const auto& task : tasks) {
        std::cout << "Task '" << task.task_name;
        if (task.task_end != 0) {
            std::cout << "' took: " << task.spent_time.hours << "h ";
            std::cout << task.spent_time.minutes << "m ";
            std::cout << task.spent_time.seconds << "s" << std::endl;
        } else {
            double diff = std::difftime(std::time(nullptr), task.task_begin);
            Time spent_time = GetTimeFromSeconds(diff);
            std::cout << "' in process: " << spent_time.hours << "h ";
            std::cout << spent_time.minutes << "m ";
            std::cout << spent_time.seconds << "s" << std::endl;
        }
    }
}

Time GetTimeFromSeconds(double diff) {
    int total_seconds = static_cast<int>(diff);
    int hours = total_seconds / 3600;
    total_seconds %= 3600;
    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    return {hours, minutes, seconds};
}
