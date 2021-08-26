//
// Created by chenda on 2021/3/30.
//


#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,p;
    cin>>n>>p;
    vector<int>nums(2*n,0);
    long long sum=0;
    for(int i=0;i<2*n;i++){
        cin>>nums[i];
        sum+=nums[i];
    }
    long long tmp=sum;
    sort(nums.begin(),nums.end());
    for(int i=0;i<n;i++){
        sum-=nums[i];
    }
    long long sum2=tmp-sum;
    long long ans=0;
    if(p>50){
        ans= (100-p)*tmp+(2*p-100)*sum2;
    }
    else{
        long long t=0;
        for(int i=1;i<2*n;i+=2){
            t+=nums[i];
        }
        ans= (100-p)*tmp+(2*p-100)*t;
    }
    if(ans%100==0){
        cout<<ans/100<<endl;
    }else{
        cout<<ans<<"%"<<endl;
    }
}