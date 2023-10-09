//
// Created by ZackHu on 2023-10-07.
//

#include <sstream>
#include "Queue.h"
#include "Process.h"

Queue::Queue(int priority, int quantum) : priority(priority), quantum(quantum), len(0), processList() {}

void Queue::addProcess(Process* p) {
    processList.push_back(p);
}

void Queue::addProcessToHead(Process *p) {
    processList.insert(processList.begin(), p);
}

int Queue::getLength() {
    return static_cast<int>(processList.size());
}

int Queue::getQuantum() {
    return quantum;
}

int Queue::getPriority() {
    return priority;
}

Process* Queue::getFirstProcess() {
    if (processList.empty()) {
        return nullptr;
    } else {
        auto* p = processList[0];
        processList.erase(processList.begin());
//        processList.pop_front();
        return p;
    }
}

void Queue::setQuantum(int quantum) {
    this->quantum = quantum;
}

std::string Queue::toString() {
    std::ostringstream oss;
    oss << "Queue " << priority << ": " << "  quantum = " << quantum << "   ";
    oss << "Process list: ";
    if (processList.empty()) {
        oss << "EMPTY\n";
    } else {
        oss << "\n";
        for (const auto & i : processList) {
            oss << i->toString();
        }
    }
    return oss.str();
}