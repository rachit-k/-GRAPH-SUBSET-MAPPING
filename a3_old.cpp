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
    std::chrono::time_point<std::chrono::system_clock> begin = std::chrono::system_clock::now();
    ifstream fin;
    fin.open(string(argv[1])+".graphs");

    vector<int> inp1;
    vector<int> inp2;
    int n=0;

    int temp;
    fin>>temp;
    int n1=temp;
    while(temp!=0)
    {
        inp1.push_back(temp);
        fin>>temp;  
        if(temp>n1)
        {
            n1=temp;
        }      
    }
    fin>>temp;
    int n2=temp;
    while(fin)
    {
        fin>>temp;
        if(temp>n2)
        {
            n2=temp;
        } 
        inp2.push_back(temp);
    }

    fin.close();
    cout<< (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - begin)).count()<<endl;
    int **A = new int*[n1];
    for(int i = 0; i < n1; i++) 
    {
        A[i] = new int[n1];
    }
    int **B = new int*[n2];
    for(int i = 0; i < n2; i++) 
    {
        B[i] = new int[n2];
    }

    for(int i=0;i<n1;i++)
    {
        for(int j=0;j<n1;j++)
        {
            A[i][j]=0; 
        }
    }
    for(int i=0;i<n2;i++)
    {
        for(int j=0;j<n2;j++)
        {
            B[i][j]=0;
        }
    }
    vector<pair<int,int>> G;
    vector<pair<int,int>> G_dash;

    for(int i=0;i<inp1.size();i=i+2)
    {
        G.push_back(make_pair(inp1[i]-1,inp1[i+1]-1));
        A[inp1[i]-1][inp1[i+1]-1]=1;
    }
    for(int i=0;i<inp2.size()-1;i=i+2)
    {
        G_dash.push_back(make_pair(inp2[i]-1,inp2[i+1]-1));
        B[inp2[i]-1][inp2[i+1]-1]=1;
    }


    int numMailUsers=n2;
    int numPhoneUsers=n1;

    ofstream fout;
    fout.open("temp1.txt");
    fout<<n1<<" "<<n2<<"\n";
    fout.close();

    int numClauses = 0;
    vector<string> clauses;
    //string clauses="";

    cout<< (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - begin)).count()<<endl;
    for(auto it:G_dash)
    {
        int i=it.first;
        int j=it.second;
        for(int k=0; k<numPhoneUsers; k++)
        {
            for(int l=0;l<numPhoneUsers;l++)
            {
                if(k!=l)
                {
                    if(A[k][l]!=1)
                    {
                        clauses.push_back("-" + to_string(i*numPhoneUsers +k+1) + " -" + to_string(j*numPhoneUsers +l+1) + " 0\n");
                        numClauses++;                                    
                    }
                }
            }
        }       
        
    }
    for(int i=0; i<numMailUsers; i++)
    {
        for(int j=0;j<numMailUsers;j++)
        {
            if(i!=j)
            {
                if(B[i][j]!=1)
                {
                    for(auto it:G)
                    {
                        int k=it.first;
                        int l=it.second;                    
                        clauses.push_back("-" + to_string(i*numPhoneUsers +k+1) + " -" + to_string(j*numPhoneUsers +l+1) + " 0\n");
                        numClauses++;                            
                    }
                }
            }
        }
    }
    
    cout<< (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - begin)).count()<<endl;
    for(int i=0; i<numMailUsers; i++)
    {
        for(int j=0; j<numPhoneUsers; j++)
        {
            for (int k=j+1; k<numPhoneUsers; k++)
            {
                    clauses.push_back("-" + to_string(i*numPhoneUsers +j+1) + " -" + to_string(i*numPhoneUsers +k+1) + " 0\n");
                    numClauses++;
            }
        }
    }

    for(int i=0; i<numMailUsers; i++)
    {
        for(int j=i+1; j<numMailUsers; j++)
        {
            for (int k=0; k < numPhoneUsers; k++)
            {
                    clauses.push_back("-" + to_string(i*numPhoneUsers +k+1) + " -" + to_string(j*numPhoneUsers +k+1) + " 0\n");
                    numClauses++;
            }
        }
    }
 
    for(int i=0; i < numMailUsers; i++)
    {
        for(int j=0; j < numPhoneUsers; j++)
        {
            clauses.push_back(to_string(i*numPhoneUsers +j+1) + " ");
        }
        clauses.push_back("0\n");
        numClauses++;
    }
    cout<< (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - begin)).count()<<endl;
    vector<int> set1;
    vector<int> set2;

    for(int i=0;i<numMailUsers; i++)
    {
        int flag=0;
        for(int j=0;j<numMailUsers;j++)
        {
            if(B[i][j]!=0||B[j][i]!=0)
                flag++;
        }
        if(flag==0)
        {
            set1.push_back(i);
        }
    }
    for(int i=0;i<numPhoneUsers; i++)
    {
        int flag=0;
        for(int j=0;j<numPhoneUsers;j++)
        {
            if(A[i][j]!=0||A[j][i]!=0)
                flag++;
        }
        if(flag!=0)
        {
            set2.push_back(i);
        }
    }

    for(auto it:set1)
    {
        for(auto it1:set2)
        {
            clauses .push_back("-" + to_string(it*numPhoneUsers +it1+1) + " 0\n");
            //numClauses++;
        }
    }
    cout<< (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - begin)).count()<<endl;
    //ofstream fout;
    fout.open(string(argv[1]) + ".satinput");//,

    fout<<"p cnf "<<numMailUsers*numPhoneUsers<<" "<<numClauses<<"\n";
    for(auto it:clauses)
        fout<<it;

    fout.close();
    cout<< (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - begin)).count()<<endl;          
    return 0;
}