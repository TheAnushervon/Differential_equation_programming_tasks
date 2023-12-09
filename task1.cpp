#include <iostream> 
#include <vector> 
#include <string> 
#include <cstdlib> 
using namespace std; 

struct human_debt{
    string name = ""; 
    int amount = 0; 
    int to_whom; 
}; 
int main() { 
    srand(time(NULL)); 
vector<human_debt> debts;
vector<vector<int>> adj_list(10) ;
for (int i = 0 ; i < 10;i++) { 
    int first = rand()%10; 
    int second= rand()%10; 
    adj_list[first].push_back(second); 
    adj_list[second].push_back(first) ; 
}  
for (int i = 0 ; i < 10; i++) { 
    cout << "debts of "<< i << endl ; 
    for (int j = 0 ; j < adj_list[i].size();j++) { 
        cout << adj_list[i][j] << " "; 
    }
    cout << endl ; 
}
return 0 ; 
}

