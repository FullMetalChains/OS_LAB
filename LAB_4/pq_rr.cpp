#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <stdlib.h>   

using namespace std;

struct Process
{
    int index = 0, at = 0, bt = 0, priority = 0, ct = 0, tat = 0, wt = 0, rt = 0, qNo = 0;
};


bool sorter(Process&a, Process&b){
    if(a.at == b.at){
        return (a.priority < b.priority);
    }
    return (a.at < b.at);
}

auto comparator = [](Process&a, Process&b){
    if(a.priority != b.priority){
        return (a.priority < b.priority);
    }
    else{
        return (a.qNo > b.qNo);
    }
};

int main(){
    int n,tq;
    cout<<"Enter time quanta-> ";
    cin>>tq;
    cout<<"Enter the number of processes->  ";
    cin>>n;
    int qNo = 0;
    vector<Process>p(n), ans(n);
    vector<bool>first_occurance(n, true);
    for(int i = 0;i<n;i++){
        p[i].index = i;
        cin>>p[i].at>>p[i].bt>>p[i].priority;
        ans[i].index = p[i].index;
        ans[i].at = p[i].at;
        ans[i].bt = p[i].bt;
        ans[i].priority = p[i].priority;
    }
    sort(p.begin(), p.end(), sorter);
    int t = 0, i = 0;
    priority_queue<Process, vector<Process>, decltype(comparator)>pq(comparator);
    while(i < n || !pq.empty()){
        if(pq.empty()){
            t = p[i].at;
        }
        while(i < n && p[i].at <= t){
            Process prc = p[i];
            prc.qNo = qNo++;
            pq.push(prc);
            i++;
        }
        Process pr = pq.top();
        pq.pop();
        if(first_occurance[pr.index] == true){
            ans[pr.index].rt = t;
            first_occurance[pr.index] = false;
        }
        int sub = min(pr.bt, tq);
        cout<<"Process "<<pr.index + 1<<" run from "<<t<<" to "<<t + sub<<endl;
        pr.bt-=sub;
        t+=sub;
        while(i < n && p[i].at <= t){
            Process prc = p[i];
            prc.qNo = qNo++;
            pq.push(prc);
            i++;
        }
        if(pr.bt > 0){
            pr.qNo = qNo++;
            pq.push(pr);
        }
        else{
            int index = pr.index;
            ans[index].ct = t;
            ans[index].tat = ans[index].ct - ans[index].at;
            ans[index].wt = ans[index].tat - ans[index].bt;

        }
    }
    cout<<"Process\tAT\tBT\tPriority\tCT\tTAT\tWT\tRT\n";
    float avgtat = 0, avgrt = 0;
    for(int i = 0;i<n;i++){
        cout<<i + 1<<"\t"<<ans[i].at<<"\t"<<ans[i].bt<<"\t"<<ans[i].priority<<"\t\t"<<ans[i].ct<<"\t"<<ans[i].tat<<"\t"<<ans[i].wt<<"\t"<<ans[i].rt<<"\n";
        avgtat+=ans[i].tat;
        avgrt+=ans[i].rt;
    }
    cout<<"Average Turn Around Time is "<<avgtat/n<<endl;
    cout<<"Average Response Time is "<<avgrt/n<<endl;

}