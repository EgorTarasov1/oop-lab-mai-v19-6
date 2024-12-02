#include "Observer.h"
#include <iostream>

void ConsoleObserver::update(const std::string& message) {
    std::cout << message << std::endl;
}

FileObserver::FileObserver(const std::string& filename) {
    logfile.open(filename, std::ios::app);
}

FileObserver::~FileObserver() {
    if (logfile.is_open()) {
        logfile.close();
    }
}

void FileObserver::update(const std::string& message) {
    if (logfile.is_open()) {
        logfile << message << std::endl;
    }
}