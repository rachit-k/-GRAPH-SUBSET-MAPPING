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
    //std::chrono::time_point<std::chrono::system_clock> begin = std::chrono::system_clock::now();
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
    //cout<< (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - begin)).count()<<endl;
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
    //cout<< (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - begin)).count()<<endl;
    for(int i=0;i<inp1.size();i=i+2)
    {
        A[inp1[i]-1][inp1[i+1]-1]=1;
    }
    for(int i=0;i<inp2.size()-1;i=i+2)
    {
        B[inp2[i]-1][inp2[i+1]-1]=1;
    }

    int numMailUsers=n2;
    int numPhoneUsers=n1;

    ofstream fout;
    fout.open("temp1.txt");
    fout<<n1<<" "<<n2<<"\n";
    fout.close();

    //int numClauses = 0;
    //vector<string> clauses;
    //string clauses="";

    //cout<< (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - begin)).count()<<endl;
    fout.open(string(argv[1]) + ".satinput");
    // for(int i=0; i<numMailUsers; i++)
    // {
    //     for(int j=0;j<numMailUsers;j++)
    //     {
    //         if(i!=j)
    //         {
    //             if(B[i][j]==1)
    //             {
    //                 for(int k=0; k<numPhoneUsers; k++)
    //                 {
    //                     for(int l=0;l<numPhoneUsers;l++)
    //                     {
    //                         if(k!=l)
    //                         {
    //                             if(A[k][l]!=1)
    //                             {
    //                                 fout<<"-"<<i*numPhoneUsers +k+1<<" -"<<j*numPhoneUsers +l+1<<" 0\n";
    //                                 numClauses++;
    //                             }
    //                         }
    //                     }
    //                 }
    //             }
    //             else
    //             {
    //                 for(int k=0; k<numPhoneUsers; k++)
    //                 {
    //                     for(int l=0;l<numPhoneUsers;l++)
    //                     {
    //                             if(A[k][l]==1)
    //                             {
    //                                 fout<<"-"<<i*numPhoneUsers +k+1<<" -" <<j*numPhoneUsers +l+1<<" 0\n";
    //                                 numClauses++;
    //                             }
    //                     }
    //                 }
    //             }
    //         }
    //     }
    // }
    for(int i=0; i<numMailUsers; i++)
    {
        for(int k=0; k<numPhoneUsers; k++)
        {
            int t1=0,t2=0;
            int t3=0,t4=0;
            for(int l=0;l<numPhoneUsers;l++)
            {
                if(A[k][l]==1)
                    t1++;
                if(A[l][k]==1)
                    t3++;
            }
            for(int l=0;l<numMailUsers;l++)
            {
                if(B[i][l]==1)
                    t2++;
                if(B[l][i]==1)
                    t4++;
            }
            if(t1<t2||t3<t4)
            {
                fout<<"-"<<i*numPhoneUsers +k+1<<" 0\n";
                continue;
            }
            for(int j=0;j<numMailUsers;j++)
            {
                for(int l=0;l<numPhoneUsers;l++)
                {
                    if(k!=l)
                    {
                        if((A[k][l]!=1&&B[i][j]==1&&(i!=j))||(A[k][l]==1&&B[i][j]!=1&&(i==j)))
                        {
                            fout<<"-"<<i*numPhoneUsers +k+1<<" -"<<j*numPhoneUsers +l+1<<" 0\n";
                            //numClauses++;
                        }
                    }
                }
            }
        }
    }
    //cout<< (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - begin)).count()<<endl;
    for(int i=0; i<numMailUsers; i++)
    {
        for(int j=0; j<numPhoneUsers; j++)
        {
            for (int k=j+1; k<numPhoneUsers; k++)
            {
                    fout<<"-"<<i*numPhoneUsers+j+1<<" -"<<i*numPhoneUsers +k+1<<" 0\n";
                    //numClauses++;
            }
        }
    }

    for(int i=0; i<numMailUsers; i++)
    {
        for(int j=i+1; j<numMailUsers; j++)
        {
            for (int k=0; k < numPhoneUsers; k++)
            {
                    fout<<"-"<<i*numPhoneUsers +k+1<<" -"<<j*numPhoneUsers +k+1<<" 0\n";
                    //numClauses++;
            }
        }
    }

    for(int i=0; i < numMailUsers; i++)
    {
        for(int j=0; j < numPhoneUsers; j++)
        {
            fout<<i*numPhoneUsers +j+1<< " ";
        }
        fout<<"0\n";
        //numClauses++;
    }
    //cout<< (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - begin)).count()<<endl;
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
            fout<<"-" <<it*numPhoneUsers +it1+1<<" 0\n";
            //numClauses++;
        }
    }
    //cout<< (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - begin)).count()<<endl;
    //ofstream fout;
    

    //fout<<"p cnf "<<numMailUsers*numPhoneUsers<<" "<<numClauses<<"\n";
    //for(auto it:clauses)
    //    fout<<it;

    fout.close();  
    //cout<< (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - begin)).count()<<endl;          
    return 0;
}