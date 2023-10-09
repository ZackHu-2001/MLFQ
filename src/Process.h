//
// Created by ZackHu on 2023-10-07.
//

#ifndef MLFQ_PROCESS_H
#define MLFQ_PROCESS_H

class Queue;
class Process {
public:
    Process(int pid, int length, int ioFrequency, int arriveTime);
    int getPid() const;
    int getAllotment() const;
    int getTotalRunTime() const;
    int getArriveTime() const;
    Queue* getQueueBelongTo() const;
    int* execute();
    void setFinishTime(int currentTime);
    void setQueueBelongTo(Queue* q);
    void setRemainQuantum(int quantum);
    void decreaseAllotment();
    void resetIOTime();
    void resetAllotment(int allotment);
    std::string toString() const;

private:
    const int pid;
    const int totalRunTime;
    int remainingTotalRunTime;
    const int ioFrequency;
    const int arriveTime;
    int finishTime;
    int allotment;
    int runTime;
    int nextIO;
    int remainQuantum;
    Queue* queueBelongTo;
};


#endif //MLFQ_PROCESS_H
