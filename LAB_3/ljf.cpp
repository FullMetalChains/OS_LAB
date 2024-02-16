// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef struct Process{
    int index;
    int at;
    int bt;
    int ct;
    int tat;
    int rt;
    int wt;
}Process;


bool sorter(Process&a, Process&b){
    if(a.at == b.at){
        return (a.index < b.index);
    }
    return (a.at < b.at);
};


struct comparator
{
    bool operator()(Process& a, Process& b)
    {
        if(a.bt == b.bt){
            return (a.at < b.at);
        }
        else{
            return (a.bt < b.bt);
        }
    }
};



int main(){
    int n; 
    cout<<"Enter the number of process--> ";                                                               
    cin>>n;
    vector<Process>p(n);
    for(int i = 0;i<n;i++){
        p[i].index = i + 1;
        cin>>p[i].at>>p[i].bt;
    }
    sort(p.begin(), p.end(), sorter);
    priority_queue<Process, vector<Process>, comparator>q;
    int time = 0, i = 0;
    float avgtat = 0, avgrt = 0;
    cout<<"Process\tAT\tBT\tCT\tTAT\tWT\tRT\n";
    while(i < n || !q.empty()){
        if(q.empty() && time < p[i].at){
            time = p[i].at;
        }
        while(i < n && p[i].at  <= time){
            q.push(p[i]);
            i++;
        }
        Process c = q.top();
        q.pop();
        time+=c.bt;
        c.ct = time;
        c.tat = c.ct - c.at;
        c.wt = c.tat - c.bt;
        c.rt = c.wt;
        avgtat+=c.tat;
        avgrt +=c.rt;
        cout<<c.index<<"\t"<<c.at<<"\t"<<c.bt<<"\t"<<c.ct<<"\t"<<c.tat<<"\t"<<c.wt<<"\t"<<c.rt<<endl;
    }
    cout<<"Average Turn Around Time is "<<avgtat/n<<endl;
    cout<<"Average Response Time is "<<avgrt/n<<endl;
}