#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// Process class definition, representing each process
class Process
{
public:
    string name; // Process name
    int pid; // Process ID
    int arrivalTime; // Time when the process arrives
    int cpuBurst; // Total CPU time needed by the process
    int ioBurst; // Time for each I/O operation
    int ioFrequency; // How often I/O occurs (after how many CPU bursts)
    int remainingCpuBurst; // Remaining CPU time
    int priority; // Priority level of the process
    int waitingTime; // Waiting time for the process
    int turnaroundTime; // Turnaround time for the process
    int responseTime; // Response time for the process (first CPU access)
    bool inIO; // Whether the process is currently performing I/O
    int lastCpuTime; // Last time the process used CPU
    int cpuSinceLastIO; // How long the CPU ran since the last I/O operation

    // Constructor to initialize process attributes
    Process(string n, int id, int at, int cb, int ib, int ifreq, int p)
        : name(n), pid(id), arrivalTime(at), cpuBurst(cb), ioBurst(ib), ioFrequency(ifreq),
          remainingCpuBurst(cb), priority(p), waitingTime(0), turnaroundTime(0), responseTime(-1),
          inIO(false), lastCpuTime(at), cpuSinceLastIO(0) {}
};

// Queue class representing a priority queue
class Queue
{
public:
    int priority; // Priority of the queue
    int timeSlice; // Time slice (quantum) for the queue
    queue<Process *> processes; // Queue of processes at this priority

    // Default constructor
    Queue() : priority(0), timeSlice(0) {}

    // Parameterized constructor
    Queue(int p, int t, queue<Process *> &qp) : priority(p), timeSlice(t), processes(qp) {}
};

// Multi-Level Queue Scheduler class definition
class Multi_Level_Queue_Scheduler
{
public:
    int numQueues; // Number of priority queues
    vector<Queue> queues; // Vector of queues representing different priority levels
    int currentTime; // Current time in the simulation
    int contextSwitches; // Total number of context switches
    vector<Process *> completedProcesses; // List of completed processes
    deque<Process *> io_queue; // Queue for processes currently performing I/O

    // Constructor to initialize the scheduler
    Multi_Level_Queue_Scheduler(int num, vector<Queue> &vq) : numQueues(num), queues(vq), currentTime(0), contextSwitches(0) {}

    // Main function to run the scheduler
    void run()
    {
        while (true)
        {
            // Check if all queues are empty, and I/O queue is also empty, then exit
            bool allQueuesEmpty = true;
            for (int i = 0; i < numQueues; i++)
            {
                if (!queues[i].processes.empty())
                {
                    allQueuesEmpty = false;
                    break;
                }
            }
            if (allQueuesEmpty)
            {
                if (io_queue.empty())
                {
                    break;
                }
                else
                {
                    // Jump ahead in time to when an I/O operation completes
                    currentTime += io_queue.front()->cpuSinceLastIO + io_queue.front()->ioBurst;
                }
            }

            // Handle I/O completion
            if (!io_queue.empty())
            {
                Process *io_proc = io_queue.front();
                while (io_proc != NULL && currentTime - io_proc->lastCpuTime >= io_proc->ioBurst)
                {
                    io_proc->inIO = false;
                    io_proc->cpuSinceLastIO = 0; // Reset CPU counter after coming out of I/O
                    // Move process back to its respective priority queue
                    if (io_proc->priority == 4)
                    {
                        queues[2].processes.push(io_proc); // Lower priority queue
                    }
                    else if (io_proc->priority == 3)
                    {
                        queues[1].processes.push(io_proc);
                    }
                    else
                    {
                        queues[0].processes.push(io_proc);
                    }
                    io_queue.pop_front(); // Remove process from I/O queue
                    if (!io_queue.empty())
                    {
                        io_proc = io_queue.front();
                    }
                    else
                    {
                        io_proc = NULL;
                    }
                }
            }

            // Find the highest priority queue with a process ready to run
            int highestPriorityQueue = -1;
            for (int i = 0; i < numQueues; i++)
            {
                if (!queues[i].processes.empty() && (highestPriorityQueue == -1 || queues[i].priority > queues[highestPriorityQueue].priority))
                {
                    highestPriorityQueue = i;
                }
            }

            // Get the process from the highest priority queue
            Process *currentProcess = queues[highestPriorityQueue].processes.front();
            queues[highestPriorityQueue].processes.pop();

            // If process is running for the first time, record its response time
            if (currentProcess->responseTime == -1)
            {
                currentProcess->responseTime = currentTime - currentProcess->arrivalTime;
            }

            // Determine how long the process will run (minimum of time slice, remaining CPU time, and time before I/O)
            int timeToRun = min(queues[highestPriorityQueue].timeSlice, min(currentProcess->remainingCpuBurst, currentProcess->ioFrequency - currentProcess->cpuSinceLastIO));

            currentTime += timeToRun; // Advance the current time
            currentProcess->remainingCpuBurst -= timeToRun; // Subtract the time from remaining CPU burst
            currentProcess->cpuSinceLastIO += timeToRun; // Update CPU time since last I/O

            // Check if the process needs I/O or should be put back in the queue
            if (currentProcess->remainingCpuBurst > 0)
            {
                if (currentProcess->cpuSinceLastIO == currentProcess->ioFrequency)
                {
                    // Process moves to I/O
                    currentProcess->inIO = true;
                    currentProcess->cpuSinceLastIO = 0; // Reset the counter after moving to I/O
                    currentProcess->lastCpuTime = currentTime;
                    io_queue.push_back(currentProcess);
                }
                else
                {
                    // Put the process back in the same queue
                    queues[highestPriorityQueue].processes.push(currentProcess);
                }
            }
            else
            {
                // Process has completed
                currentProcess->turnaroundTime = currentTime - currentProcess->arrivalTime;
                currentProcess->waitingTime = currentProcess->turnaroundTime - currentProcess->cpuBurst;
                completedProcesses.push_back(currentProcess);
            }

            contextSwitches++; // Increment context switches count
        }

        printSummary(); // Print the summary after scheduling completes
    }

    // Print the summary of the scheduling
    void printSummary()
    {
        cout << "Process\t\tPriority\tResponse Time\tTurnaround Time\t\tWaiting Time\n";
        for (const auto &proc : completedProcesses)
        {
            cout << proc->name << "\t" << setw(12) << proc->priority << "\t" << setw(17) << proc->responseTime
                 << "\t" << setw(12) << proc->turnaroundTime
                 << "\t" << setw(15) << proc->waitingTime << "\n";
        }
        cout << "Total Context Switches: " << contextSwitches << endl;
    }
};

int main()
{
    // Define the processes
    vector<Process> processes = {
        Process("P0", 0, 0, 18, 5, 5, 4),
        Process("P1", 1, 0, 27, 6, 6, 4),
        Process("P2", 2, 0, 44, 4, 6, 3),
        Process("P3", 3, 0, 50, 3, 9, 2)};

    // Empty queues for each priority level
    queue<Process *> emptyQueue1, emptyQueue2, emptyQueue3;

    // Define the queues with different priorities and time slices
    vector<Queue> queues = {
        Queue(2, 9, emptyQueue1),
        Queue(3, 6, emptyQueue2),
        Queue(4, 3, emptyQueue3)};

    // Assign processes to queues based on their priority
    for (int i = 0; i < 4; i++)
    {
        if (processes[i].priority == 4)
        {
            queues[2].processes.push(&processes[i]);
        }
        else if (processes[i].priority == 3)
        {
            queues[1].processes.push(&processes[i]);
        }
        else
        {
            queues[0].processes.push(&processes[i]);
        }
    }

    // Create and run the scheduler
    Multi_Level_Queue_Scheduler scheduler(3, queues);
    scheduler.run(); // Run the scheduler
    return 0;
}
