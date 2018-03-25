#include <stdio.h>
/*-----------------------------------------------------------------------------------------------------*/
/* Author: Sahil Malik  14/2/2018 */ 
void display()
{
	cout<<"\tNodes: "<<nodes<<"\tProcessor: "<<n_proc<<endl<<"\n\tProcessing Cost Matrix\n";
	for(int i=0;i<nodes;i++)
	{
		cout<<"\t";
		for(int j=0;j<n_proc;j++)
			cout<<weight[i][j]<<"\t";
		cout<<endl;
	}
	cout<<"\n\t-------------Adj Matrix-------------\n";
	for(int i=0;i<nodes;i++){
		cout<<"\t";
		for(int j=0;j<nodes;j++)
			cout<<adj[i][j]<<" ";
		cout<<endl;
	}
	cout<<"\n\t-------------Processor Matrix-------------\n";
	for (int i = 0; i <n_proc; i++){
		cout<<"\t";
		for(int j=0;j<n_proc;j++)
			cout<<identity[i][j]<<"\t";
		cout<<endl<<endl;
	}
}
/*-----------------------------------------------------------------------------------------------------*/
void show_PCT()
{
	cout<<"\n\t-------------PCT-------------\n";
	for(int i=0;i<nodes;i++)
	{
		cout<<"\tPROCESS "<<i+1;
		for(int j=0;j<n_proc;j++)
		{
			printf("\tP[%d]: %d\t",j+1,PCT[i][j]);
		}
		cout<<endl;
	}
}
/*-----------------------------------------------------------------------------------------------------*/
void show_RANK_PCT()
{
	cout<<endl<<"\t-------------RANK PCT-------------\n";
	for(int i=0;i<nodes;i++)
		printf("\tP[%d]: %d\n",i+1,RANK_PCT[i]);
}
/*-----------------------------------------------------------------------------------------------------*/
void show_AEST()
{
	cout<<endl<<"\t-------------AEST-------------\n";
	for(int i=0;i<nodes;i++)
		printf("\tP[%d]: %f\n",i+1,AEST[i]);

}
/*-----------------------------------------------------------------------------------------------------*/
void show_ALST()
{
	cout<<endl<<"\t-------------ALST-------------\n";
	for(int i=0;i<nodes;i++)
		printf("\tP[%d]: %f\n",i+1,ALST[i]);

}
/*-----------------------------------------------------------------------------------------------------*/
void show_CNCT()
{
	cout<<"\t-------------CNCT-------------\n";
	for(int i=0;i<nodes;i++)
	{
		cout<<"\tPROCESS "<<i+1;
		for(int j=0;j<n_proc;j++)
		{
			printf("\tP[%d]:%d\t",j+1,CNCT[i][j]);
		}
		cout<<endl<<endl;
	}
}
/*-----------------------------------------------------------------------------------------------------*/
void show_CNP()
{
	cout<<"\t-------------CNP-------------\n";
	for(int i=0;i<nodes;i++){
		printf("\tPROCESS[%d]:\t",i+1);
		if(CNP[i]==false)	cout<<"FALSE\n";
		else				cout<<"TRUE\n";
	}

}
/*-----------------------------------------------------------------------------------------------------*/
void show_EFT()
{
	cout<<"\t-------------EFT-------------\n";
	for(int i=0;i<nodes;i++){
		cout<<"\tPROCESS:"<<i+1<<"\t";
		for(int j=0;j<n_proc;j++)
			cout<<EFT[i][j]<<"\t";
		cout<<endl;
	}
}
/*-----------------------------------------------------------------------------------------------------*/
void show_EFT_CNCT()
{
	cout<<"\t-------------EFT CNCT-------------\n";
	for(int i=0;i<nodes;i++){
		cout<<"\tPROCESS:"<<i+1<<"\t";
		for(int j=0;j<n_proc;j++)
			cout<<EFT_CNCT[i][j]<<"\t";
		cout<<endl;
	}
}
