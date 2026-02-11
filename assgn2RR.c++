#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class task
{
public:
    int pid;
    int burst;
    int remaining_burst; // Added to track progress
    string name;
    int arrival;

    task()
    {
        cout << "Enter Pid : ";
        cin >> pid;
        cout << "Enter burst time : ";
        cin >> burst;
        remaining_burst = burst; // Initially, remaining is the full burst
        cout << "Enter name of process : ";
        cin >> name;
        cout << "Enter arrival time of process : ";
        cin >> arrival;
        cout << endl;
    }
};

class RR
{
public:
    queue<task> all_tasks;
    int num, quanta;

    RR()
    {
        cout << "How many processes: ";
        cin >> num;
        for (int i = 0; i < num; i++)
        {
            task t;
            all_tasks.push(t);
        }
        cout << "Set Quanta : ";
        cin >> quanta;
    }

    void execute()
    {
        queue<int> ready_queue; // Stores indices of tasks
        int current_time = 0;
        int completed = 0;

        while (completed < num)
        {
            if (all_tasks.front().arrival > current_time)
            {
                task t = all_tasks.front();
                all_tasks.pop();
                all_tasks.push(t);
                current_time++;
                continue;
            }
            else
            {
                if (all_tasks.front().burst <= quanta)
                {
                    task t = all_tasks.front();
                    all_tasks.front().burst = 0;
                    completed++;
                    all_tasks.pop();
                    cout << "Task " << t.name << " has been completed at time" << current_time << endl;
                }
                else
                {
                    task t = all_tasks.front();
                    t.burst = t.burst - quanta;
                    all_tasks.pop();
                    all_tasks.push(t);
                    current_time += quanta;
                    // cout << " Task rounded " << t.name << " at time " << current_time << endl;
                }
            }
        }
    }
};

int main()
{
    RR scheduler;
    scheduler.execute();
    return 0;
}