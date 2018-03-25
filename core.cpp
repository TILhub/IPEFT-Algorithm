/*-----------------------------------------------------------------------------------------------------*/
#include <iostream>
#include <vector>
#include <fstream>
#include <climits>
#include <set>
#include <algorithm>
#define MAX 700
using namespace std;
int nodes,n_proc,weight[MAX][MAX],identity[MAX][MAX],adj[MAX][MAX],PCT[MAX][MAX],RANK_PCT[MAX],CNCT[MAX][MAX],EST[MAX][MAX]={0},EFT[MAX][MAX]={0};
int AFT[MAX],tp[MAX],processor_assigned[MAX],EFT_CNCT[MAX][MAX]={0};
float AEST[MAX],ALST[MAX];
bool CNP[MAX];
set<int> arr;
void init()
{
	for(int i=0;i<nodes;i++)	
		for(int j=0;j<nodes;j++)
			cout<<EFT[i][j];
}
/*-----------------------------------------------------------------------------------------------------*/
int round(float var)
{
    int value = (int)(var * 100 + .5);
    return value / 100;
}
/*-----------------------------------------------------------------------------------------------------*/
void read(char* file_name)
{
	fstream ifs;
	ifs.open(file_name);
	ifs>>nodes;
	ifs>>n_proc;
	for(int i=0;i<nodes;i++)
		for(int j=0;j<n_proc;j++)
			ifs>>weight[i][j];
	for (int i = 0; i <n_proc; i++)
		for(int j=0;j<n_proc;j++)
			ifs>>identity[i][j];
	for(int i=0;i<nodes;i++)
		for(int j=0;j<nodes;j++)
			ifs>>adj[i][j];
	cout<<"\n\tFile Name Supplied: "<<file_name<<endl;
	cout<<"\n\tGraph Supplied Nodes: "<<nodes<<"\n\n\tWith Discrete Processors: "<<n_proc<<endl<<endl;
}
/*-----------------------------------------------------------------------------------------------------*/
inline bool check_exit_node(int p)
{
	bool flag=true;
	for(int i=0;i<nodes;i++)
		if(adj[p][i]!=-1)	return false;
	return flag;
}
/*-----------------------------------------------------------------------------------------------------*/
void pct(int p)
{
	if(check_exit_node(p)==true){					/* Handling PCT of Exit Nodes*/
		for(int i=0;i<n_proc;i++)	
			PCT[p][i]=0;
		int temp=0;
		for(int i=0;i<n_proc;i++)
			temp+=weight[p][i];
		temp/=n_proc;
		RANK_PCT[p]=temp;
		return;
	}
	for(int i=0;i<nodes;i++)
	{
		
		if(adj[p][i]!=-1)					/*If a successor of current node*/
		{
			int max=0;
			for(int j=0;j<n_proc;j++){
				for(int k=0;k<n_proc;k++){
					max=PCT[i][j]+weight[i][j]+adj[p][i]*identity[j][k];
					if(PCT[p][k]<max)	PCT[p][k]=max;		
				}
			}
		}
		
	}
	float temp=0;
		for(int i=0;i<n_proc;i++)	temp=temp+PCT[p][i]+weight[p][i];
		temp/=n_proc;
	RANK_PCT[p]=round(temp);
}
/*-----------------------------------------------------------------------------------------------------*/
inline bool check_entry_node(int p)
{
	for(int i=0;i<nodes;i++)
		if(adj[i][p]!=-1)	return false;
	return true;
}
/*-----------------------------------------------------------------------------------------------------*/
void aest(int p)
{
	AEST[p]=0.0;
	if(check_entry_node(p))	return;
	for(int i=0;i<nodes;i++)
	{
		float max=0;
		float temp=0;
		if(adj[i][p]!=-1){
			for(int j=0;j<n_proc;j++)	
				temp+=float(weight[i][j]);
			temp=temp/n_proc;
			temp=round(temp);
			max=round(AEST[i]+adj[i][p]+temp);
			if(max>AEST[p])	AEST[p]=round(max);
		}
	}
}
/*-----------------------------------------------------------------------------------------------------*/
void alst(int p)
{
	CNP[p]=true;
	if(check_exit_node(p)){
		ALST[p]=round(AEST[p]);
		return;
	}
	ALST[p]=INT_MAX;
	float min=INT_MAX;
	for(int i=0;i<nodes;i++){
		if(adj[p][i]!=-1){
			min=round(ALST[i]-adj[p][i]);
			if(min<ALST[p])	ALST[p]=round(min);
		}
	}
	float temp=0;
	for(int j=0;j<n_proc;j++)	temp+=float(weight[p][j]);
	temp/=n_proc;
	temp=round(temp);
	ALST[p]-=temp;
	ALST[p]=round(ALST[p]);
}
/*-----------------------------------------------------------------------------------------------------*/
void cnct(int p)
{
	if(check_exit_node(p)==true){					/* Handling PCT of Exit Nodes*/
		for(int i=0;i<n_proc;i++)	
			CNCT[p][i]=0;
		return;
	}
	int temp_arr[MAX][MAX],nos=0;
	for(int i=0;i<nodes;i++)
		for(int j=0;j<n_proc;j++)
			temp_arr[i][j]=INT_MAX;
	
	for(int i=0;i<nodes;i++){
		if(adj[p][i]!=-1)			/*if a successor of CN*/
		{
			nos++;
			for(int j=0;j<n_proc;j++)
				for(int k=0;k<n_proc;k++)	
					temp_arr[j][k]=CNCT[i][j]+weight[i][j]+adj[p][i]*identity[j][k];
			for(int j=0;j<n_proc;j++)
			{
				int min=INT_MAX;
				for(int k=0;k<n_proc;k++)
					if(temp_arr[k][j]<min)	min=temp_arr[k][j];
				if(CNCT[p][j]<min)	CNCT[p][j]=min;
			}
		}
	}
}
/*-----------------------------------------------------------------------------------------------------*/
void cnp(int p){
	if(abs(ALST[p]-AEST[p])==0){
		CNP[p]=false;
		arr.insert(p);
		return;
	}
	for(int i=0;i<nodes;i++)
		if(adj[p][i]!=-1 ){
			if(CNP[i]==true && arr.find(i)!=arr.end()){
				CNP[p]=true;
				return ;
			}
			else if(arr.find(i)!=arr.end())	CNP[p]=true;	
			else CNP[p]		=false;
		}
}
/*-----------------------------------------------------------------------------------------------------*/
inline int eft(int ni,int pj){
	return (EST[ni][pj]+weight[ni][pj]);
}
/*-----------------------------------------------------------------------------------------------------*/
void est(int ni)
{
	int temp[MAX]={0};	
	for(int i=0;i<n_proc;i++)	temp[i]=0;
	register int mt=0;		
	for(int i=0;i<nodes;i++)
	{
		if(adj[i][ni]!=-1){	
			for(int j=0;j<n_proc;j++){	
				mt=AFT[i]+identity[processor_assigned[i]][j]*adj[i][ni];	
				if(temp[j]<=mt)		temp[j]=mt;
			}
		}
	}	
	for(int i=0;i<n_proc;i++){	
		if(tp[i]>temp[i])	EST[ni][i]=tp[i];	
		else	EST[ni][i]=temp[i];	
	}		
}
/*-----------------------------------------------------------------------------------------------------*/
bool f(int i,int j){return RANK_PCT[i]<RANK_PCT[j];}
void ipeft_algorithm()
{	
	//CNCT[0][0]=67;
	vector<int> ready_list;
	for(int i=0;i<nodes;i++)	ready_list.push_back(i);
	sort(ready_list.begin(),ready_list.end(),f);
	while(ready_list.size()){		
		int curr=ready_list.back();			
		est(curr);
		for(int i=0;i<n_proc;i++)	
			EFT[curr][i]=eft(curr,i);
		//cout<<EFT[curr][0]<<" "<<EFT[curr][1]<<" "<<EFT[curr][2]<<" "<<endl;
		if(CNP[curr]==true)		
			for(int i=0;i<n_proc;i++)	
				EFT_CNCT[curr][i]=EFT[curr][i];
		else
			for(int i=0;i<n_proc;i++)
				EFT_CNCT[curr][i]=EFT[curr][i]+CNCT[curr][i];
		int min=INT_MAX;
		int pro=0;
		for(int i=0;i<n_proc;i++)
			if(min>EFT_CNCT[curr][i])
			{
				pro=i;
				min=EFT_CNCT[curr][i];
			}
		processor_assigned[curr]=pro;
		AFT[curr]=EFT[curr][pro];
		tp[pro]=EFT[curr][pro];
		cout<<"\tProcess:"<<curr+1<<" Processor: "<<pro<<" AFT: "<<AFT[curr]<<endl;
		ready_list.pop_back();
	}
}
/*-----------------------------------------------------------------------------------------------------*/
