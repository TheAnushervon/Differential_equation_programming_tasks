#include <iostream>
#include <vector> 
#include <cmath> 

using namespace std ; 
vector<double> val_xi = {1};
vector<double> val_yi = {2};
vector<double> val_ti ; 
double pi = 2 * acos(0.0);
const double t0= 0 ; 
const double b = pi;  
double h; 
int n, task ; 
void calc_ti() {
    for (int i = 0; i< n; i++) { 
        val_ti.push_back(pi/n) ; 
    }
}
void print_ti(){
    cout << "ti=\n"; 
    for (int i = 0 ; i<n ; i++) { 
        cout << val_ti[i] << " " ; 
    }
}
void first_task(){
    calc_ti() ; 
    print_ti(); 
    /*calc_euler_xi() ; 
    print_euler_xi() ; 
    calc_euler_yi(); 
    print_euler_yi() ; */
}
void second_task(){

}
void third_task() { 
    
}
int main() { 
cin >> n >> task ; 
switch (task){
    case 1: 
        first_task() ;
        break; 
    case 2: 
        second_task(); 
        break;
    case 3:
        third_task(); 
        break;   
}
}