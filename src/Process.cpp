//
// Created by ZackHu on 2023-10-07.
//

#include <stdexcept>
#include "Process.h"

Process::Process(int pid, int length, int ioFrequency, int allotment)
    :pid(pid), length(length), ioFrequency(ioFrequency), allotment(allotment) {
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

int Process::getLength() const {
    return length;
}

void Process::resetAllotment(int newAllotment) {
    this->allotment = newAllotment;
}

