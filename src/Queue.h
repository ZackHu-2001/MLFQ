//
// Created by ZackHu on 2023-10-07.
//

#ifndef MLFQ_QUEUE_H
#define MLFQ_QUEUE_H

#include "vector"

class Process;
class Queue {
public:
    Queue(int priority, int quantum);
    void addProcess(Process* p);
    void addProcessToHead(Process* p);
    int getLength();
    int getQuantum();
    int getPriority();
    Process* getFirstProcess();
    void setQuantum(int quantum);
    std::string toString();

private:
    int priority;
    int quantum;
    int len;
    std::vector<Process*> processList;

};


#endif //MLFQ_QUEUE_H
