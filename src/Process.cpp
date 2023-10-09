//
// Created by ZackHu on 2023-10-07.
//

#include <stdexcept>
#include <sstream>
#include "Process.h"

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

int Process::getAllotment() const {
    return allotment;
}

int Process::getTotalRunTime() const {
    return totalRunTime;
}

int Process::getArriveTime() const {
    return arriveTime;
}

// [finished?, IO?]
int* Process::execute() {
    int* result = new int[2];
    if (remainingTotalRunTime == 0) {
        result[0] = 1;
        result[1] = 0;
        return result;
    } else {
        runTime += 1;
        nextIO -= 1;
        if (nextIO == 0) {
            result[0] = 0;
            result[1] = 1;
        }
    }
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
