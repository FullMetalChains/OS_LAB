#include <stdio.h>


void sort(int* arr, int n){
    for(int i = 0;i< n;i++){
        int index = i;
        for(int j = i + 1;j < n;j++){
            if(arr[j] < arr[index]){
                index = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[index];
        arr[index] = temp;
    }
}

int main(){
    int n;
    scanf("%d", &n);
    int arr[n];
    for(int i = 0;i<n;i++){
        scanf("%d", &arr[i]);
    }
    sort(arr, n);
    for(int i = 0;i<n;i++){
        printf("%d ", arr[i]);
    }
}