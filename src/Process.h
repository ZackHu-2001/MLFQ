//
// Created by ZackHu on 2023-10-07.
//

#ifndef MLFQ_PROCESS_H
#define MLFQ_PROCESS_H


class Process {
public:
    Process(int pid, int length, int ioFrequency, int allotment);
    int getAllotment() const;
    int getLength() const;
    void decreaseAllotment();
    void resetAllotment(int allotment);
private:
    const int pid;
    const int length;
    const int ioFrequency;
    int allotment;
};


#endif //MLFQ_PROCESS_H
