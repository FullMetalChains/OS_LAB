#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Process
{
public:
    int processNum, at, bt, qNo, variablebt, ct, tat, wt, rt;
};

bool sortOnTheBasisOfArrivalTime(const Process &p1, const Process &p2)
{
    if (p1.at == p2.at)
    {
        if (p1.qNo == p2.qNo)
        {
            return p1.processNum < p2.processNum;
        }

        return p1.qNo > p2.qNo;
    }

    return p1.at < p2.at;
}

class compInReadyQueue
{
public:
    bool operator()(Process &p1, Process &p2)
    {
        return p1.qNo < p2.qNo;
    }
};

bool compareWithQNo(const Process &p1, const Process &p2)
{
    return p1.qNo > p2.qNo;
}

int main()
{
    int n;
    cin >> n;

    Process arr[n];
    Process temp[n];

    for (int i = 0; i < n; i++)
    {
        int at, bt, qNo;
        cin >> at >> bt >> qNo;

        arr[i].at = at;
        arr[i].bt = bt;
        arr[i].qNo = qNo;
        arr[i].variablebt = bt;
        arr[i].processNum = i + 1;

        temp[i] = arr[i];
    }

    sort(temp, temp + n, sortOnTheBasisOfArrivalTime);

    priority_queue<Process, vector<Process>, compInReadyQueue> pq;

    int time = 0;
    int i = 0;

    while (i < n)
    {
        pq.push(temp[i]);
        i++;
        while (pq.size())
        {
            Process p = pq.top();
            cout << p.processNum << endl;
            pq.pop();

            if (p.at > time)
            {
                time = p.at;
            }

            time += p.bt;
            arr[p.processNum - 1].ct = time;

            while (i < n && temp[i].at <= time)
            {
                pq.push(temp[i++]);
            }

            // cout << time << endl;
        }
    }

    double avgWT = 0;
    double avgTAT = 0;

    for (int i = 0; i < n; i++)
    {
        arr[i].tat = arr[i].ct - arr[i].at;
        arr[i].wt = arr[i].tat - arr[i].bt;
        arr[i].rt = arr[i].wt;
        avgWT += arr[i].wt;
        avgTAT += arr[i].tat;
    }

    cout << "PNo\tAT\tqNo\tBT\tCT\tTAT\tWT\tRT" << endl;

    for (int i = 0; i < n; i++)
    {
        cout << arr[i].processNum << "\t" << arr[i].at << "\t" << arr[i].bt << "\t" << arr[i].qNo << "\t" << arr[i].ct << "\t" << arr[i].tat << "\t" << arr[i].wt << "\t"
             << arr[i].rt << endl;
    }

    avgWT = (avgWT) / (1.0 * n);
    avgTAT = (avgTAT) / (1.0 * n);

    cout << endl;

    cout << "Average turn arround time is : " << avgTAT << endl;
    cout << "Average waiting time is : " << avgWT << endl;
}

/*

7
0 3 2
2 5 6
1 4 3
4 2 5
6 9 7
5 4 4
7 10 10

*/