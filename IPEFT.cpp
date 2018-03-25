#include "core.cpp"
#include "debug.cpp"
#include <fstream>
/* Author: Sahil Malik  14/2/2018 */ 
int main(int argc,char* argv[])
{
	//system("cls");
	if(argv[1]==NULL){
		cout<<"\n\tError! No Input File Supplied.\n\n";
		cout<<"\tProgram Will Now Exit\n\n";
		getchar();
		exit(0);
	}

	read(argv[1]);
	//display();
	for(int i=nodes-1;i>=0;i--)	pct(i);
	//show_PCT();
	//show_RANK_PCT();
	for(int i=nodes-1;i>=0;i--)	cnct(i);
	//	CNCT[0][0]=67;
	//show_CNCT();
	for(int i=0;i<nodes;i++)
		aest(i);
	for(int i=nodes-1;i>=0;i--)
	{	alst(i);
		cnp(i);
	}
	ipeft_algorithm();
	//show_AEST();
	//show_ALST();
	//show_CNP();
	//show_EFT();
	//show_EFT_CNCT();
	ofstream ofs;
	ofs.open("IPEFT.txt",ios_base::app);
	ofs<<AFT[nodes-1]<<"\n";
	return 0;
}
