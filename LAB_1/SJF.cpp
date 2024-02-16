#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>

bool comparator(std::vector<int>&a, std::vector<int>&b){
    return (a[1] < b[1]);
}


struct my_comparator
{
    bool operator()(std::vector<int>& a, std::vector<int>& b)
    {
        if(a[2] == b[2]){
            return (a[1] > b[1]);
        }
        else{
            return (a[2] > b[2]);
        }
    }
};

int main(){
    int n;          
    std::cout<<"Enter number of processes--> ";                                                      
    std::cin>>n;
    //[process number, arrival time, burst 6 time]
    std::vector<std::vector<int>>jobs(n,std::vector<int>(3));
    //[complete time, turnaround time]
    std::vector<std::vector<int>>ans(n + 1, std::vector<int>(2));
    for(int i =0;i<n;i++){
        jobs[i][0] = i + 1;
        std::cin>>jobs[i][1]>>jobs[i][2];
    }
    // std::cout<<"Working"<<std::endl;
    sort(jobs.begin(), jobs.end(), comparator);
    int time = 0, index = 0;
    std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, my_comparator> pq;
    while(index < jobs.size()){
        if(!pq.empty()){
            std::cout<<"index is "<<index<<std::endl;
            std::vector<int>top = pq.top();
            pq.pop();
            time+=top[2];
            ans[top[0]][0] = time;
            ans[top[0]][1] = time - top[1];

        }
        if(time < jobs[index][1]){
            time = jobs[index][1];
        }
        while(index < jobs.size() && jobs[index][1] <= time){
            pq.push(jobs[index]);
            index++;
        }
    }
    while(!pq.empty()){
        std::vector<int>top = pq.top();
        pq.pop();
        time+=top[2];
        ans[top[0]][0] = time;
        ans[top[0]][1] = time - top[1];
    }
    std::cout<<"Process - CompletionTime - TurnaroundTime\n";
    for(int i = 1;i<=n;i++){
        std::cout<<i<<" "<<ans[i][0]<<" "<<ans[i][1]<<std::endl;
    }
}