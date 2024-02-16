#include <bits/stdc++.h>
using namespace std;

struct process
{
    int arrival;
    int burst;
    int no;
    int priority;
};

class comp
{
public:
    bool operator()(process a, process b)
    {
        return a.priority == b.priority? a.arrival < b.arrival : a.priority < b.priority;
    }
};

int main()
{
    cout << "Enter no of Processes\n";
    int n;
    cin >> n;
    vector<process> arr(n);
    for (int i = 0;i<n;i++){
        arr[i].no = i + 1;
        cin >> arr[i].priority>>arr[i].arrival>>arr[i].burst;
    }
    sort(arr.begin(), arr.end(), [](process a, process b)
         { return a.arrival < b.arrival; });
    int time = arr[0].arrival, avgTT = 0;
    int avgWT = accumulate(arr.begin(), arr.end(), 0, [](int sum, process p)
                           { return sum + p.burst; });
    priority_queue<process, vector<process>, comp> q;
    for (int i = 0; time <= arr[n - 1].arrival; time++)
    {
        if (q.size())
        {
            process p = q.top();
            q.pop();
            p.burst--;
            if (p.burst)
                q.push(p);
            else
            {
                cout << "Process " << p.no << " completed at " << time << '\n';
                avgTT += time - p.arrival;
            }
        }
        while (i < n && arr[i].arrival <= time)
            q.push(arr[i++]);
    }
    while (q.size())
    {
        process p = q.top();
        time += p.burst;
        avgTT += time - p.arrival;
        cout << "Process " << p.no << " completed at " << time << '\n';
        q.pop();
    }
    cout << "\nAverage Turn-Around Time is " << (double)avgTT / (double)n << '\n';
    cout << "Average Wait Time is " << (double)(avgTT - avgWT) / (double)n << '\n';
}