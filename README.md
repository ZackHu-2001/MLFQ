Options:
-h, --help            show this help message and exit
-s SEED, --seed=SEED  the random seed
-n NUMQUEUES, --numQueues=NUMQUEUES
number of queues in MLFQ (if not using -Q)
-q QUANTUM, --quantum=QUANTUM
length of time slice (if not using -Q)
-a ALLOTMENT, --allotment=ALLOTMENT
length of allotment (if not using -A)
-Q QUANTUMLIST, --quantumList=QUANTUMLIST
length of time slice per queue level, specified as
x,y,z,... where x is the quantum length for the
highest priority queue, y the next highest, and so
forth
-A ALLOTMENTLIST, --allotmentList=ALLOTMENTLIST
length of time allotment per queue level, specified as
x,y,z,... where x is the # of time slices for the
highest priority queue, y the next highest, and so
forth
-j NUMJOBS, --numJobs=NUMJOBS
number of jobs in the system
-m MAXLEN, --maxlen=MAXLEN
max run-time of a job (if randomly generating)
-M MAXIO, --maxio=MAXIO
max I/O frequency of a job (if randomly generating)
-B BOOST, --boost=BOOST
how often to boost the priority of all jobs back to
high priority
-i IOTIME, --iotime=IOTIME
how long an I/O should last (fixed constant)
-S, --stay            reset and stay at same priority level when issuing I/O
-I, --iobump          if specified, jobs that finished I/O move immediately
to front of current queue
-l JLIST, --jlist=JLIST
a comma-separated list of jobs to run, in the form
x1,y1,z1:x2,y2,z2:... where x is start time, y is run
time, and z is how often the job issues an I/O request
-c                    compute answers for me