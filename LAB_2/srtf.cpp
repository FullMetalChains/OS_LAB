#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Process
{
public:
    int processNum;
    int arrivalTime;
    int burstTime;
    int variableBurstTime;
    int completionTime;
    int turnArroundTime;
    int waitTime;
    int responseTime;
};

bool sortOnTheBasisOfArrivalTime(const Process &p1, const Process &p2)
{
    if (p1.arrivalTime == p2.arrivalTime)
    {
        return p1.burstTime < p2.burstTime;
    }

    return p1.arrivalTime < p2.arrivalTime;
}

class CompareRemainingTime
{
public:
    bool operator()(Process &p1, Process &p2)
    {
        if (p1.variableBurstTime == p2.variableBurstTime)
        {
            return p1.arrivalTime > p2.arrivalTime;
        }

        return p1.variableBurstTime > p2.variableBurstTime;
    }
};

int main()
{
    int n;
    cin >> n;

    int timeQuantum;
    cin >> timeQuantum;

    vector<Process> arr;
    vector<Process> temp;

    for (int i = 0; i < n; i++)
    {
        int at, bt;
        cin >> at >> bt;

        Process p;
        p.arrivalTime = at;
        p.burstTime = bt;
        p.variableBurstTime = bt;
        p.processNum = i + 1;

        arr.push_back(p);
        temp.push_back(p);
    }

    sort(temp.begin(), temp.end(), sortOnTheBasisOfArrivalTime);

    priority_queue<Process, vector<Process>, CompareRemainingTime> q;

    q.push(temp[0]);

    int time = 0;

    int i = 1;

    while (!q.empty())
    {
        Process p = q.top();

        q.pop();

        if (p.variableBurstTime <= timeQuantum)
        {
            if (p.variableBurstTime == p.burstTime)
            {
                arr[p.processNum - 1].responseTime = time;
            }
            time += p.variableBurstTime;

            p.variableBurstTime = 0;
            arr[p.processNum - 1].completionTime = time;

            while (i < n && temp[i].arrivalTime <= time)
            {
                q.push(temp[i++]);
            }
        }

        else
        {
            if (p.variableBurstTime == p.burstTime)
            {
                arr[p.processNum - 1].responseTime = time;
            }

            time += timeQuantum;
            p.variableBurstTime -= timeQuantum;

            while (i < n && temp[i].arrivalTime <= time)
            {
                q.push(temp[i++]);
            }

            q.push(p);
        }
    }

    for (int i = 0; i < n; i++)
    {
        arr[i].turnArroundTime = arr[i].completionTime - arr[i].arrivalTime;
        arr[i].waitTime = arr[i].turnArroundTime - arr[i].burstTime;
    }

    cout << "PNo  AT  BT  CT  TAT  WT  RT" << endl;

    for (int i = 0; i < n; i++)
    {
        cout << arr[i].processNum << "  " << arr[i].arrivalTime << "  " << arr[i].burstTime << "  " << arr[i].completionTime << "  " << arr[i].turnArroundTime << "  " << arr[i].waitTime << "  "
             << arr[i].responseTime << endl;
    }

    return 0;
}

/*
6
4
0 5
1 6
2 3
3 1
4 5
6 4


5
4
2 6
5 2
1 8
0 3
4 4
*/