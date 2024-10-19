#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace ::std;

// Class to represent a process
class Process
{
public:
    string name;           // Process name
    int pid;               // Process ID
    int arrivalTime;       // Time when the process arrives in the system
    int cpuBurst;          // Total time the process needs on the CPU
    int ioBurst;           // Time for which the process performs I/O each time
    int ioFrequency;       // How frequently the process performs I/O (after how much CPU usage)
    int remainingCpuBurst; // Remaining CPU burst time
    int priority;          // Priority of the process
    int waitingTime;       // Total waiting time of the process
    int turnaroundTime;    // Turnaround time (completion time - arrival time)
    int responseTime;      // Time between arrival and first CPU execution
    bool inIO;             // Flag to check if the process is performing I/O
    int lastCpuTime;       // Time when the process entered I/O
    int cpuSinceLastIO;    // How much CPU the process has run after its last I/O

    // Constructor to initialize process attributes
    Process(string n, int id, int at, int cb, int ib, int ifreq)
        : name(n), pid(id), arrivalTime(at), cpuBurst(cb), ioBurst(ib), ioFrequency(ifreq),
          remainingCpuBurst(cb), priority(0), waitingTime(0), turnaroundTime(0), responseTime(-1),
          inIO(false), lastCpuTime(at), cpuSinceLastIO(0) {}
};

// Custom comparator for priority queue to build a max heap
struct ProcessComparator
{
    // Comparator to prioritize higher priority, or earlier arrival in case of a tie
    bool operator()(Process *p1, Process *p2)
    {
        if (p1->priority == p2->priority)
        {
            return p1->arrivalTime > p2->arrivalTime; // Earlier arrival => higher priority
        }
        return p1->priority < p2->priority; // Higher priority gets higher precedence
    }
};

// Function to increase the priority of processes in the ready queue
void increase_priority(priority_queue<Process *, vector<Process *>, ProcessComparator> &ready_queue, int alpha)
{
    // Temporary vector to store processes for re-insertion after priority update
    vector<Process *> temp_queue;

    // Extract each process from the priority queue
    while (!ready_queue.empty())
    {
        Process *proc = ready_queue.top();
        ready_queue.pop();

        proc->priority += alpha; // Increase priority by alpha

        temp_queue.push_back(proc); // Store for re-insertion
    }

    // Re-insert all processes back into the priority queue
    for (Process *proc : temp_queue)
    {
        ready_queue.push(proc);
    }
}

// Class representing a preemptive priority scheduler
class Preemptive_Priority_Scheduler
{
public:
    vector<Process> processes;  // List of processes to be scheduled
    int alpha;                  // Increment for ready processes (waiting)
    int beta;                   // Increment for running processes
    int currentTime;            // Current time in the simulation
    int contextSwitches;        // Total number of context switches
    vector<Process *> finished_queue; // List of finished processes

    // Constructor to initialize the scheduler with process list, alpha, and beta
    Preemptive_Priority_Scheduler(vector<Process> &p, int a, int b) : processes(p), alpha(a), beta(b), currentTime(0), contextSwitches(0) {}

    // Function to run the scheduler
    void run()
    {
        priority_queue<Process *, vector<Process *>, ProcessComparator> ready_queue; // Priority queue for ready processes
        deque<Process *> io_queue; // Queue for processes performing I/O

        vector<Process *> proc_pointers; // Vector to store pointers to processes for easier access
        for (auto &proc : processes)
        {
            proc_pointers.push_back(&proc); // Store pointers to processes
        }

        Process *running_proc = NULL; // Pointer to the currently running process

        // Main loop to simulate the scheduler until all processes are finished
        while (!proc_pointers.empty() || !ready_queue.empty() || !io_queue.empty())
        {
            // Add processes to the ready queue if they have arrived
            for (auto it = proc_pointers.begin(); it != proc_pointers.end();)
            {
                if ((*it)->arrivalTime <= currentTime)
                {
                    (*it)->priority = 0;     // Reset priority on arrival
                    ready_queue.push(*it);   // Add to ready queue
                    it = proc_pointers.erase(it); // Remove from pending processes
                }
                else
                {
                    ++it; // Move to the next process
                }
            }

            // Handle processes in the I/O queue
            if (!io_queue.empty())
            {
                Process *io_proc = io_queue.front(); // Get the process at the front of the I/O queue
                if (currentTime - io_proc->lastCpuTime >= io_proc->ioBurst)
                {
                    io_proc->inIO = false;       // Mark the process as not in I/O
                    io_proc->cpuSinceLastIO = 0; // Reset CPU usage since last I/O
                    ready_queue.push(io_proc);   // Move the process back to the ready queue
                    io_queue.pop_front();        // Remove the process from the I/O queue
                }
            }

            // Execute the process with the highest priority from the ready queue
            if (!ready_queue.empty())
            {
                if (running_proc != NULL && running_proc != ready_queue.top())
                    contextSwitches++; // Increment context switches if switching to a new process

                running_proc = ready_queue.top(); // Get the highest priority process
                ready_queue.pop();                // Remove it from the ready queue

                increase_priority(ready_queue, alpha); // Increase priority for all other processes in the ready queue

                // If this is the first time the process is running, set its response time
                if (running_proc->responseTime == -1)
                {
                    running_proc->responseTime = currentTime - running_proc->arrivalTime;
                }

                running_proc->remainingCpuBurst--;   // Decrease remaining CPU burst
                running_proc->cpuSinceLastIO++;      // Increase CPU usage since last I/O
                running_proc->priority += beta;      // Increase the running process's priority

                // Check if the process needs to perform I/O
                if (running_proc->cpuSinceLastIO == running_proc->ioFrequency)
                {
                    running_proc->inIO = true;       // Mark process as in I/O
                    running_proc->cpuSinceLastIO = 0; // Reset CPU since last I/O
                    running_proc->lastCpuTime = currentTime; // Set the time when the process entered I/O
                    io_queue.push_back(running_proc); // Add the process to the I/O queue
                }

                // Check if the process has completed execution
                if (running_proc->remainingCpuBurst == 0)
                {
                    running_proc->turnaroundTime = currentTime - running_proc->arrivalTime; // Calculate turnaround time
                    running_proc->waitingTime = running_proc->turnaroundTime - running_proc->cpuBurst; // Calculate waiting time
                    finished_queue.push_back(running_proc); // Add the process to the finished queue
                }
                else if (find(io_queue.begin(), io_queue.end(), running_proc) == io_queue.end())
                {
                    // If the process hasn't completed and isn't in I/O, re-add it to the ready queue
                    ready_queue.push(running_proc);
                }
            }

            currentTime++; // Increment the current time
        }

        // If no processes have finished, print a message
        if (finished_queue.empty())
        {
            cout << "No processes finished." << endl;
        }
        else
        {
            printSummary(); // Print the summary of the finished processes
        }
    }

    // Function to print the summary of the scheduling
    void printSummary()
    {
        cout << "Process\tResponse Time\tTurnaround Time\tWaiting Time\n";
        for (const auto &proc : finished_queue)
        {
            cout << proc->name << "\t" << setw(12) << proc->responseTime
                 << "\t" << setw(15) << proc->turnaroundTime
                 << "\t" << setw(12) << proc->waitingTime << "\n";
        }
        cout << "Total Context Switches: " << contextSwitches << endl;
    }
};

int main()
{
    // Test with different values of alpha and beta

    // Scenario 1: Alpha > Beta, Beta = 0
    vector<Process> processes1 = {
        Process("P0", 0, 0, 18, 5, 5),
        Process("P1", 1, 3, 27, 6, 6),
        Process("P2", 2, 8, 44, 4, 6),
        Process("P3", 3, 12, 50, 3, 9)};
    Preemptive_Priority_Scheduler scheduler1(processes1, 2, 0); // alpha = 2, beta = 0
    cout << "Alpha > Beta, Beta = 0\n";
    scheduler1.run();

    // Scenario 2: Beta > Alpha > 0
    vector<Process> processes2 = {
        Process("P0", 0, 0, 18, 5, 5),
        Process("P1", 1, 3, 27, 6, 6),
        Process("P2", 2, 8, 44, 4, 6),
        Process("P3", 3, 12, 50, 3, 9)};
    Preemptive_Priority_Scheduler scheduler2(processes2, 1, 2); // alpha = 1, beta = 2
    cout << "\nBeta > Alpha > 0\n";
    scheduler2.run();

    // Scenario 3: Alpha > Beta > 0
    vector<Process> processes3 = {
        Process("P0", 0, 0, 18, 5, 5),
        Process("P1", 1, 3, 27, 6, 6),
        Process("P2", 2, 8, 44, 4, 6),
        Process("P3", 3, 12, 50, 3, 9)};
    Preemptive_Priority_Scheduler scheduler3(processes3, 2, 1); // alpha = 2, beta = 1
    cout << "\nAlpha > Beta > 0\n";
    scheduler3.run();

    return 0;
}
