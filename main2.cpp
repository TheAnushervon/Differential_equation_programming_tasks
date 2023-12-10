#include <iostream>
#include <vector> 
#include <cmath> 
#include <iomanip> 
using namespace std ; 
vector<double> val_xi = {1};
vector<double> val_yi = {2};
vector<double> val_ti ; 
double pi = 2 * acos(0.0);
const double t0= 0 ; 
const double b = pi;  
int n, task ; 
double h ;  
double func_calc(double ti, double xi, double yi, char which_func) { 
    if (which_func == 'g'){
        return yi ; 
    }
    else {
        return -4*xi; 
    }
}
void calc_ti() {
    h = (b - t0)/(n-1);
    for (int i = 0; i <= n; ++i) {
        double ti = i*h;
        val_ti.push_back(ti);
    }
}
void calc_euler_xi(){ 
for (int i = 0 ; i < n-1 ; i++) { 
    double func_res = h*func_calc(val_ti[i], val_xi[i], val_yi[i], 'f'); 
    double value = val_xi[i]+func_res; 
    val_xi.push_back(value); 
}
}
void print_ti(){
    cout << "ti=\n"; 
    for (int i = 0 ; i<n ; i++) { 
        cout<<fixed<< setprecision(5)<< val_ti[i] << " " ; 
    }
}
void print_euler(char which_points){
    if (which_points == 'x'){
        cout << "Euler_xi=\n"; 
        for (int i = 0 ; i < n ; i ++ ) { 
            cout<< val_xi[i] << " "; 
        }
    }
    else {
        cout << "Euler_yi=\n"; 
        for (int i = 0 ; i < n ; i ++) { 
            cout << val_yi[i] << " "; 
        }
    }
}
void first_task(){
    calc_ti() ; 
    print_ti(); 
    cout << endl ; 
    calc_euler_xi() ; 
    print_euler('x') ; 
   /*calc_euler_yi(); 
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