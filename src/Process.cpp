//
// Created by ZackHu on 2023-10-07.
//

#include <stdexcept>
#include <sstream>
#include "Process.h"
#include "Queue.h"
#include "iostream"

Process::Process(int pid, int totalRunTime, int ioFrequency, int arriveTime)
    :pid(pid), totalRunTime(totalRunTime), remainingTotalRunTime(totalRunTime),
    ioFrequency(ioFrequency), arriveTime(arriveTime), runTime(0) {
    if (ioFrequency < 0) {
        throw std::invalid_argument("Illegal io frequency.");
    }
    if (ioFrequency == 0) {
        nextIO = -1;
    } else {
        nextIO = ioFrequency;
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

void Process::resetIOTime() {
    this->nextIO = ioFrequency;
}

void Process::setQueueBelongTo(Queue *q) {
    this->queueBelongTo = q;
}

void Process::setRemainQuantum(int quantum) {
    this->remainQuantum = quantum;
}

// [finished?, IO?]
int* Process::execute() {
    int* result = new int[3];

    runTime += 1;
    remainingTotalRunTime -= 1;
    remainQuantum -= 1;
    if (ioFrequency != 0) {
        nextIO -= 1;
    }
    std::cout << "Process " << pid << "   quantum: [" << remainQuantum << " / " << (queueBelongTo)->getQuantum() << "] ";
    std::cout << "  total run time: [" << totalRunTime - remainingTotalRunTime << " / "<< totalRunTime << "] ";
    std::cout << "  next IO: " << nextIO << "\n";

    result[0] = 0;
    result[1] = 0;
    result[2] = 0;

    if (remainingTotalRunTime == 0) {
        result[0] = 1;
        return result;
    }
    if (nextIO == 0) {
        nextIO = ioFrequency;
        allotment -= 1;
        result[1] = 1;
    }
    if (remainQuantum == 0) {
        result[2] = 1;
    }


    return result;

}

void Process::resetAllotment(int newAllotment) {
    this->allotment = newAllotment;
}

std::string Process::toString() const {
    std::ostringstream oss;
    oss << "Process " << pid << ": ";
    if (queueBelongTo != nullptr) {
        oss << "\n\tBelong to queue: \t" << queueBelongTo->getPriority();
    }
    oss << "\n\tArrive time: \t\t" << arriveTime;
    oss << "\n\tTotal run time: \t" << totalRunTime;
    oss << "\n\tRemaining run time: \t" << remainingTotalRunTime;
    oss << "\n\tIO Frequency: \t\t" << ioFrequency << "\n";
    return oss.str();
}
