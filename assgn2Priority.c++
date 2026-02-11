#include <iostream>
#include <vector>
using namespace std;

class task
{
public:
    int pid;
    int burst;
    string name;
    int arrival;
    int priority;

    task()
    {
        cout << "Enter Pid : " << endl;
        cin >> pid;
        cout << "Enter burst time : " << endl;
        cin >> burst;
        cout << "Enter name of process : " << endl;
        cin >> name;
        cout << "Enter arrival time of process : " << endl;
        cin >> arrival;
        cout << "Enter priority : " << endl;
        cin >> priority;
        cout << endl;
    }
};

class priority
{
public:
    vector<task> qtask;
    int num;
    priority()
    {
        cout << "How many processes: " << endl;
        cin >> num;
        for (int i = 0; i < num; i++)
        {
            task t;
            qtask.push_back(t);
        }
    }

    int top(vector<task> a)
    {
        task maxm = a[0];
        int max = 0;
        for (int i = 0; i < a.size(); i++)
        {
            if (maxm.priority < a[i].priority)
            {
                maxm = a[i];
                max = i;
            }
        }
        return max;
    }

    task pop(task t)
    {
        int x;
        for (int i = 0; i < qtask.size(); i++)
        {
            if (t.pid == qtask[i].pid)
            {
                x = i;
                break;
            }
        }
        task temp = qtask[x];
        qtask.erase(qtask.begin() + x);
        return temp;
    }

    void execute()
    {
        int time = 0;
        vector<task> doable;
        while (qtask.empty() != 1)
        {
            int flag = 0;
            for (int i = 0; i < qtask.size(); i++)
            {
                if (qtask[i].arrival <= time)
                {
                    doable.push_back(qtask[i]);
                    flag++;
                }
            }
            if (flag == 0)
            {
                time++;
                continue;
            }
            int x = top(doable);
            time += doable[x].burst;
            cout << "Task Completed " << doable[x].name << " current time " << time << endl;
            pop(doable[x]);
            doable.clear();
        }
    }
};

int main()
{
    priority p;
    p.execute();
}