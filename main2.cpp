#include <iostream>
#include <vector> 
#include <cmath> 
#include <iomanip> 
using namespace std ; 
vector<double> val_xi = {1};
vector<double> val_yi = {2};
vector<double> val_ti = {0}; 
vector<double> improved_value_xi; 
vector<double> improved_value_yi; 
vector<double> k1_for_xi; 
vector<double> k1_for_yi; 
vector<double> k2_for_xi; 
vector<double> k2_for_yi; 
double pi = 2 * acos(0.0);
const double t0= 0 ; 
const double b = pi;  
int n, task ; 
double h ;  
double func_calc(double ti, double xi, double yi, char which_func) { 
    if (which_func == 'x'){
        return yi ; 
    }
    else return -4*xi; 
    
}
void calc_ti() {
    h = (pi)/(n-1);
    for (int i = 1; i < n; ++i) {
        val_ti.push_back(val_ti[0]+i*h); 
    }
}
void calc_euler_for_xi_and_yi(){ 
for (int i = 0 ; i < n-1 ; i++) { 
    double func_res_xi = h*func_calc(val_ti[i], val_xi[i], val_yi[i], 'x'); 
    double func_res_yi = h*func_calc(val_ti[i], val_xi[i], val_yi[i], 'y'); 
    double value_x = val_xi[i]+func_res_xi;
    double value_y = val_yi[i]+ func_res_yi;  
    val_xi.push_back(value_x); 
    val_yi.push_back(value_y) ; 
}
}
void calc_k1(int i){
        k1_for_xi.push_back(func_calc(val_ti[i], val_xi[i], val_yi[i], 'x')); 
        k1_for_yi.push_back(func_calc(val_ti[i], val_xi[i], val_yi[i], 'y')); 
    
}
void calc_k2(int i){
 
        k2_for_xi.push_back(func_calc(val_ti[i+1], val_xi[i]+h*k1_for_xi[i], val_yi[i]+h*k1_for_yi[i], 'x')); 
       
        k2_for_yi.push_back(func_calc(val_ti[i+1], val_xi[i]+h*k1_for_xi[i], val_yi[i]+h*k1_for_yi[i], 'y')); 

}
void calc_improved_euler_for_xi_and_yi(){
    improved_value_xi.push_back(1); 
    improved_value_yi.push_back(2); 
    double h_div = h/2 ; 
    for (int  i= 0 ; i < n-1 ; i ++) { 
        calc_k1(i); 
        calc_k2(i);

        double value_for_xi = improved_value_xi[i]+h_div*(k1_for_xi[i]+k2_for_xi[i]); 
        double value_for_yi = improved_value_yi[i]+h_div*(k1_for_yi[i]+k2_for_yi[i]); 
        improved_value_xi.push_back(value_for_xi); 
        improved_value_yi.push_back(value_for_yi); 
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
void print_improved_euler(char which_output){
    if (which_output == 'x'){
        cout << "iEuler_xi=\n"; 
        for (int i = 0 ;i < n ; i++) { 
            cout<< improved_value_xi[i] << " "; 
        }
    }else {
        cout << "iEuler_yi=\n"; 
        for (int i = 0 ; i< n ;i++){
            cout << improved_value_yi[i]<< " "; 
        }
    }
}
void first_task(){
    calc_ti() ; 
    print_ti(); 
    cout << endl ; 
    calc_euler_for_xi_and_yi() ; 
    print_euler('x') ;
    cout << endl ;
    print_euler('y');  
   /*calc_euler_yi(); 
    print_euler_yi() ; */
}
void second_task(){
calc_ti(); 
print_ti(); 
cout << endl ; 
calc_improved_euler_for_xi_and_yi(); 
print_improved_euler('x'); 
cout << endl; 
print_improved_euler('y'); 
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