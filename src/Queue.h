//
// Created by ZackHu on 2023-10-07.
//
#include "vector"
#include "Process.h"

#ifndef MLFQ_QUEUE_H
#define MLFQ_QUEUE_H


class Queue {
public:

private:
    int priority;
    int quantum;
    std::vector<Process> processList;

};


#endif //MLFQ_QUEUE_H
