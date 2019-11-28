#include <iostream>
#include <string>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <fstream>
#include <utility>
#include <chrono>    

using namespace std;

int main(int argc, char *argv[])
{
	int numMailUsers,numPhoneUsers;

	ifstream fin;
	fin.open("temp1.txt");
	fin>>numPhoneUsers;
	fin>>numMailUsers;
	fin.close();

	fin.open(string(argv[1])+".satoutput");//

	string s;
	fin>>s;

	ofstream fout;
	fout.open(string(argv[1])+".mapping");//

	if(s=="UNSAT")
	{
		fout<<"0\n";
		fin.close();
		fout.close();
		return 0;
	}

	int x;
	for(int i=0;i<numMailUsers*numPhoneUsers;i++)
	{
		fin>>x;
		if(x>0)
		{
			fout<<(to_string(((x-1)/numPhoneUsers) + 1) + " " + to_string(((x-1)%numPhoneUsers) + 1) + "\n" );
		}
	}
	fin.close();
	fout.close();

	return 0;

}