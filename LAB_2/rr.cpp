// Round Robin

#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
// #include <stl_algobase.h>

int min(int a, int b){
    if(a <= b){
        return a;
    }
    else{
        return b;
    }
}

int main(){
    int tu;
    std::cout<<"Enter the time quanta--> ";
    std::cin>>tu;

    int n;
    std::cout<<"Enter the number of processes---> ";
    std::cin>>n;


    //[process index, arrival time, burst time]
    std::vector<std::vector<int>>p(n, std::vector<int>(3));
    //[completion time, turn around time, waiting time, response time]
    std::vector<std::vector<int>>ans(n + 1, std::vector<int>(4, 1e9));
    for(int i = 0;i<n;i++){
        p[i][0] = i + 1;
        std::cin>>p[i][1]>>p[i][2];
    }
    int t = 0, ptr = 0;
    std::queue<std::vector<int>>q;
    while(ptr < n || !q.empty()){
        // std::cout<<"Running"<<std::endl;
        if(q.empty() && t <= p[ptr][1]){
            t = p[ptr][1];
            q.push(p[ptr]);
            ptr++;
            continue;
        }
        int change = min(tu, (q.front())[2]);
        int new_time = t + change;
        while(ptr < n && p[ptr][1] <= new_time){
            q.push(p[ptr]);
            ptr++;
        }
        std::vector<int>process = q.front();
        //put response time
        q.pop();
        ans[process[0]][3] = min(ans[process[0]][3], t - process[1]); 
        std::cout<<"Process "<<process[0]<<" run from "<<t<<" to "<<new_time<<std::endl;
        if(process[2] - change > 0){
            process[2]-=change;
            q.push(process);
        }
        else{
            ans[process[0]][0] = new_time;
            ans[process[0]][1] = ans[process[0]][0] - process[1];
            ans[process[0]][2] = ans[process[0]][1] - p[process[0] - 1][2];
        }

        t = new_time;
    }

    std::cout<<"Final results -> \n";
    std::cout<<"Process - CT - TRT - WT - RT\n";
    for(int i = 1;i<=n;i++){
        std::cout<<i<<" "<<ans[i][0]<<" "<<ans[i][1]<<" "<<ans[i][2]<<" "<<ans[i][3]<<std::endl;
    }


}