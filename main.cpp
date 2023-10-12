#include <iostream>
#include "cstring"
#include "src/Queue.h"
#include "src/Process.h"
#include "random"

int main(int argc, char** argv) {
    int numQueues = 0;
    int quantum = 0;
    int allotment = 10;
    int boost = 0;
    int jobNum = 0;
    int ioTime = 5;
    bool showResult = false;
    bool ioBump = false;
    unsigned int seed = 0;
    int* returnValue;

    std::mt19937 gen(seed); // 使用 Mersenne Twister 作为随机数生成器
    std::uniform_int_distribution<int> distribution(1, 10000);

    std::vector<int> allotmentList;
    std::vector<int> quantumList;
    std::vector<Process*> incomingProcessList;
    std::vector<Process*> finishedProcessList;

    // parse argument
    int i = 1;
    while (i < argc) {
        if (strcmp(argv[i], "-a") == 0) {
            if (i + 1 < argc) {
                allotment = std::stoi(argv[i + 1]);
            } else {
                std::cerr << "Missing argument after -a" << std::endl;
                return 1;
            }
        } else if (strcmp(argv[i], "-b") == 0) {
            if (i + 1 < argc) {
                boost = std::stoi(argv[i + 1]);
            } else {
                std::cerr << "Missing argument after -b" << std::endl;
                return 1;
            }
        } else if (strcmp(argv[i], "-c") == 0) {
            if (i + 1 < argc) {
                if (strcmp(argv[i + 1], "true") == 0) {
                    showResult = true;
                }
            } else {
                std::cerr << "Missing argument after -c" << std::endl;
                return 1;
            }
        } else if (strcmp(argv[i], "-i") == 0) {
            if (i + 1 < argc) {
                ioTime = std::stoi(argv[i + 1]);
            } else {
                std::cerr << "Missing argument after -i" << std::endl;
                return 1;
            }
        } else if (strcmp(argv[i], "-n") == 0) {
            if (i + 1 < argc) {
                numQueues = std::stoi(argv[i + 1]);
            } else {
                std::cerr << "Missing argument after -n" << std::endl;
                return 1;
            }
        } else if (strcmp(argv[i], "-q") == 0) {
            if (i + 1 < argc) {
                quantum = std::stoi(argv[i + 1]);
            } else {
                std::cerr << "Missing argument after -q" << std::endl;
                return 1;
            }
        } else if (strcmp(argv[i], "-s") == 0) {
            if (i + 1 < argc) {
                seed = std::stoul(argv[i + 1]);
                gen.seed(seed);
            } else {
                std::cerr << "Missing argument after -s" << std::endl;
                return 1;
            }
        } else if (strcmp(argv[i], "-A") == 0) {
            if (i + 1 < argc) {
                int j = 0;
                int tmp = 0;
                while (j < strlen(argv[i + 1])) {
                    if (argv[i + 1][j] == ',') {
                        allotmentList.push_back(tmp);
                        tmp = 0;
                        j += 1;
                        continue;
                    } else {
                        tmp *= 10;
                        tmp += argv[i + 1][j] - 48;
                        j += 1;
                    }
                }
                allotmentList.push_back(tmp);
            } else {
                std::cerr << "Missing argument after -A" << std::endl;
                return 1;
            }
        } else if (strcmp(argv[i], "-I") == 0) {
            if (i + 1 < argc) {
                if (std::strcmp(argv[i+1], "true") == 0) {
                    ioBump = true;
                } else if ((std::strcmp(argv[i+1], "false") == 0)) {
                    ioBump = false;
                }
            } else {
                std::cerr << "Missing argument after -A" << std::endl;
                return 1;
            }
        } else if (strcmp(argv[i], "-L") == 0) {
            if (i + 1 < argc) {
                int j = 0;
                int arriveTime = 0;
                int length = 0;
                int ioFreq = 0;
                int cnt = 0;
                while (j < strlen(argv[i + 1])) {
                    if (argv[i + 1][j] == ';') {
                        Process *tmp = new Process(60000 + distribution(gen), length, ioFreq, arriveTime);
                        incomingProcessList.push_back(tmp);
                        arriveTime = 0;
                        length = 0;
                        ioFreq = 0;
                        cnt = 0;
                        j += 1;
                        jobNum += 1;
                        continue;
                    } else if (argv[i + 1][j] == ',') {
                        cnt += 1;
                        j += 1;
                        continue;
                    } else {
                        if (cnt == 0) {
                            arriveTime *= 10;
                            arriveTime += argv[i + 1][j] - 48;
                        } else if (cnt == 1) {
                            length *= 10;
                            length += argv[i + 1][j] - 48;
                        } else {
                            ioFreq *= 10;
                            ioFreq += argv[i + 1][j] - 48;
                        }
                        j += 1;
                    }
                }
                Process *tmp = new Process(60000 + distribution(gen), length, ioFreq, arriveTime);
                incomingProcessList.push_back(tmp);

                jobNum += 1;
            } else {
                std::cerr << "Missing argument after -A" << std::endl;
                return 1;
            }
        } else if (strcmp(argv[i], "-Q") == 0) {
            if (i + 1 < argc) {
                int j = 0;
                int tmp = 0;
                while (j < strlen(argv[i + 1])) {
                    if (argv[i + 1][j] == ',') {
                        quantumList.push_back(tmp);
                        tmp = 0;
                        j += 1;
                        continue;
                    } else {
                        tmp *= 10;
                        tmp += argv[i + 1][j] - 48;
                        j += 1;
                    }
                }
                quantumList.push_back(tmp);
            } else {
                std::cerr << "Missing argument after -Q" << std::endl;
                return 1;
            }
        }
        i += 2;
    }

    // print configurations
    std::cout << "Successfully read in Configurations:";
    std::cout << "\n\tNumber of Queue:\t" << numQueues;
    if (! quantumList.empty()) {
        std::cout << "\n\tQuantum:\t\t";
        for (int q: quantumList) {
            std::cout << q << " ";
        }
    }
    if (! allotmentList.empty()) {
        std::cout << "\n\tAllotment:\t\t";
        for (int a: allotmentList) {
            std::cout << a << " ";
        }
    } else {
        std::cout << "\n\tAllotment:\t\t\t" << allotment;
    }
    std::cout << "\n\tRandom Seed:\t\t" << seed;
    std::cout << "\n\tBoost:\t\t\t" << boost;
    std::cout << "\n\tIO duration:\t\t" << ioTime;
    std::cout << "\n\n";
    std::cout << "Incoming process:\n";
    std::cout << incomingProcessList[0]->toString();
    std::cout << incomingProcessList[1]->toString();
    std::cout << incomingProcessList[2]->toString();

    // initialize run time configuration
    int currentTime = 0;
    int finishedJob = 0;
    int boostCounter = 0;
    Process *currentProcess = nullptr;
    std::vector<std::vector<Process*>> IOQueue(ioTime);
    std::vector<Queue *> queueList;
    queueList.reserve(numQueues);

    // initialize queues
    for (i = 0; i < numQueues; i++) {
        queueList.emplace_back(new Queue(numQueues - i - 1, quantumList[i]));
    }

    std::cout << "\n\n";
    // main loop for the scheduler
    while (finishedJob < jobNum) {
        // check if have new job incoming
        for (Process *p: incomingProcessList) {
            if (p->getArriveTime() == currentTime) {
                queueList[0]->addProcess(p);
                std::cout << "Process " << p->getPid() << " comes\n";
            }
        }

        // check if have io finished job
        std::vector<Process*>& ioQueue0 = IOQueue[0]; // 获取对第一个容器的引用

        for (auto it = ioQueue0.begin(); it != ioQueue0.end();) {
            Process* p = *it; // 获取当前元素的指针
            std::cout << "Process " << p->getPid() << " IO finished.\n";
            p->resetIOTime();

            // 向前移动一格
            if (ioBump) {
                Queue* belongTo = p->getQueueBelongTo();
                belongTo->addProcessToHead(p);
            } else {
                Queue* belongTo = p->getQueueBelongTo();
                if (belongTo)
                belongTo->addProcess(p);
            }

            // 删除当前元素，并将迭代器指向下一个元素
            it = ioQueue0.erase(it);
        }


        for (int j = 1; j < ioTime; j++) {
            IOQueue[j-1] = std::move(IOQueue[j]);
        }
        // 重新初始化一个空的list
        IOQueue[ioTime-1] = std::vector<Process*>();
        IOQueue[4].clear();


        // check for Boost
        if (boostCounter == boost) {
            // do boost
        }
        boostCounter += 1;

        // select the process to run
        if (currentProcess == nullptr) {

            // check which queue have remaining task, then fetch and execute
            for (Queue *queue: queueList) {
                if (queue->getLength() != 0) {

                    // print current queues' status
//                    std::cout << "Current queue status:\n";
//                    for (Queue* q: queueList) {
//                        std::cout << q->toString();
//                    }

                    currentProcess = queue->getFirstProcess();
                    currentProcess->setFirstRunTime(currentTime);
                    currentProcess->setQueueBelongTo(queue);
                    currentProcess->setRemainQuantum(queue->getQuantum());
                    break;
                }
            }
        }

        // error check if no process selected
        if (currentProcess == nullptr) {
            std::cout << "Time " << currentTime << " empty run: No available Process in queues.\n";
            currentTime += 1;
            continue;
        }

        // execute process and respond to the return value
        std::cout << "Time " << currentTime << " execute: ";
        returnValue = currentProcess->execute();

        // if process finished
        if (returnValue[0] == 1) {
            // put the process to finished process queue
            currentProcess->setFinishTime(currentTime);
            finishedProcessList.push_back(currentProcess);
            currentProcess = nullptr;
            finishedJob += 1;
        }

        // if process starts an IO
        if (returnValue[1] == 1) {

            std::cout << "Process " << currentProcess->getPid() << " starts IO, ";
            std::cout << "switch to another process.\n";

            // push the process to the end of the IOQueue list
            currentProcess->setQueueBelongTo(currentProcess->getQueueBelongTo());
            IOQueue[ioTime-1].push_back(currentProcess);
            currentProcess = nullptr;
        } else if (returnValue[2] == 1) {
            // if process used up quantum
            std::cout << "Process " << currentProcess->getPid() << " used up its quantum, ";
            std::cout << "switch to another process.\n";

            Queue* q = currentProcess->getQueueBelongTo();
            if (q->getPriority() != 0) {
                queueList[numQueues - q->getPriority()]->addProcess(currentProcess);
            } else {
                q->addProcess(currentProcess);
            }
            currentProcess = nullptr;
        }

        currentTime += 1;
    }

    int totalResponseTime = 0;
    int totalTurnaroundTime = 0;

    // all processes finished and calculate average turnaround time
    for (Process* p: finishedProcessList) {
        p->get
    }

    // free all blocks
    for (Queue* q: queueList) {
        delete(q);
    }
    for (Process* p: incomingProcessList) {
        delete(p);
    }
    delete[] returnValue;
    return 0;

}