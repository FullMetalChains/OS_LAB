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
    return (a.at <= b.at);
}

int main(){
    int n;
    cout<<"Enter the number of processes--> ";
    cin>>n;
    vector<Process>p(n);
    for(int i = 0;i<n;i++){
        p[i].index = i + 1;
        cin>>p[i].at>>p[i].bt;
    }
    sort(p.begin(), p.end(), sorter);
    int time = 0;
    int i = 0;
    while(i < n){
        if(time < p[i].at){
            time = p[i].at;
        }
        time+=p[i].bt;
        p[i].ct = time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        p[i].rt = p[i].wt;
        i++;
    }
    float avgwt = 0, avgct = 0;
    cout<<"Total time spent = "<<time<<endl;
    cout<<"Process - AT - BT - CT - TAT - WT - RT\n";
    for(auto&q : p){
        cout<<q.index<<" "<<q.at<<" "<<q.bt<<" "<<q.ct<<" "<<q.tat<<" "<<q.wt<<" "<<q.rt<<endl;
        avgwt+=q.wt;
        avgct+=q.ct;
    }
    cout<<"Average completion time is "<<avgct/n<<endl;
    cout<<"Average waiting time is "<<avgwt/n<<endl;
}