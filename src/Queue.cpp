//
// Created by ZackHu on 2023-10-07.
//

#include <sstream>
#include "Queue.h"
#include "Process.h"

Queue::Queue(int priority, int quantum) : priority(priority), quantum(quantum), len(0), processList() {}


Process* Queue::getFirstProcess() {
    if (processList.empty()) {
        return nullptr;
    } else {
        auto* p = processList[0];
        processList.pop_back();
        return p;
    }
}

void Queue::addProcess(Process* p) {
    processList.push_back(p);
}

void Queue::addProcessToHead(Process *p) {
    processList.insert(processList.begin(), p);
}

int Queue::getLength() {
    return static_cast<int>(processList.size());
}

std::string Queue::toString() {
    std::ostringstream oss;
    oss << "Queue " << priority << ": \n";
    for (const auto & i : processList) {
        oss << i->toString();
    }
    return oss.str();
}