#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>
#include <fstream> 

class Observer {
public:
    virtual void update(const std::string& message) = 0;
};

class ConsoleObserver : public Observer {
public:
    void update(const std::string& message) override;
};

class FileObserver : public Observer {
private:
    std::ofstream logfile;
public:
    FileObserver(const std::string& filename);
    ~FileObserver();
    void update(const std::string& message) override;
};

#endif