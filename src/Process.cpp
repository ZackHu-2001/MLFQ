//
// Created by ZackHu on 2023-10-07.
//

#include <stdexcept>
#include <sstream>
#include "Process.h"
#include "iostream"

Process::Process(int pid, int totalRunTime, int ioFrequency, int arriveTime)
    :pid(pid), totalRunTime(totalRunTime), remainingTotalRunTime(totalRunTime),
    ioFrequency(ioFrequency), nextIO(ioFrequency), arriveTime(arriveTime), runTime(0) {
    if (ioFrequency < 0) {
        throw std::invalid_argument("Illegal io frequency.");
    }
}

void Process::decreaseAllotment() {
    allotment -= 1;
}

int Process::getPid() const {
    return pid;
}

int Process::getAllotment() const {
    return allotment;
}

int Process::getTotalRunTime() const {
    return totalRunTime;
}

int Process::getArriveTime() const {
    return arriveTime;
}

Queue* Process::getQueueBelongTo() const {
    return queueBelongTo;
}

void Process::setFinishTime(int currentTime) {
    this->finishTime = currentTime;
}

void Process::setQueueBelongTo(Queue *q) {
    this->queueBelongTo = q;
}

// [finished?, IO?]
int* Process::execute() {
    int* result = new int[2];

    runTime += 1;
    remainingTotalRunTime -= 1;
    if (ioFrequency != 0) {
        nextIO -= 1;
    }
    std::cout << "Process " << pid << "[" << totalRunTime - remainingTotalRunTime << " / "<< remainingTotalRunTime << "]";

    result[0] = 0;
    result[1] = 0;

    if (remainingTotalRunTime == 0) {
        result[0] = 1;
        return result;
    }
    if (nextIO == 0) {
        nextIO = ioFrequency;
        allotment -= 1;
        result[1] = 1;
        return result;
    }
    return result;

}

void Process::resetAllotment(int newAllotment) {
    this->allotment = newAllotment;
}

std::string Process::toString() const {
    std::ostringstream oss;
    oss << "Process " << pid << ": ";
    oss << "\n\tArrive time: " << arriveTime;
    oss << "\n\tTotal run time: " << totalRunTime;
    oss << "\n\tRemaining time: " << remainingTotalRunTime;
    oss << "\n\tIO Frequency: " << ioFrequency << "\n";
    return oss.str();
}
