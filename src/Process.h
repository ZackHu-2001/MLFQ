//
// Created by ZackHu on 2023-10-07.
//

#ifndef MLFQ_PROCESS_H
#define MLFQ_PROCESS_H


class Process {
public:
    Process(int pid, int length, int ioFrequency, int arriveTime);
    int getAllotment() const;
    int getTotalRunTime() const;
    int getArriveTime() const;
    int* execute();
    void decreaseAllotment();
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
};


#endif //MLFQ_PROCESS_H
