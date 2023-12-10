#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;

double epsilon = numeric_limits<double>::epsilon();
vector<double> xi_val = {0};
vector<double> yi_val = {0};
vector<double> euler_yi;
vector<double> ieuler_yi;
vector<double> k1_i;
vector<double> k2_i;
vector<double> k3_i; 
vector<double> k4_i; 
vector<double> euler_le_xi;
vector<double> ni_val; 
vector<double> impr_euler_le_xi; 
vector<double> euler_global_error; 
vector<double> euler_improved_global_error; 
vector<double> runge_kutta_sol; 
vector<double>runge_kutta_local_errors; 
vector<double> runge_kutta_global_errors; 
double h;
double pi = 2 * acos(0.0);

double calculate_function(double x, double y)
{
    double value = pow(x, 3) * pow(epsilon, -2 * x) - 2 * y;
    return value;
}

vector<double> xi_calc(int n)
{
    h = (pi) / (n - 1);
    for (int i = 1; i < n; i++)
    {
        xi_val.push_back(xi_val[0] + i * h);
    }

    return xi_val;
}
vector<double> yi_calc(int n)
{
    for (int i = 1; i < n; i++)
    {
        yi_val.push_back(sin(xi_val[i]));
    }
    return yi_val;
}
void print_xi(int n)
{
    cout << "xi=\n";
    for (int i = 0; i < n; i++)
    {
        cout << fixed << setprecision(5) << xi_val[i] << " ";
    }
}
void print_yi(int n)
{
    cout << "y(xi)=\n";
    for (int i = 0; i < n; i++)
    {
        cout << fixed << setprecision(5) << yi_val[i] << " ";
    }
}
// real func calculation
double func_calc(double xi_val, double yi_val)
{
    double result;
    result = cos(xi_val);
    return result;
}
// calc yi with euler method 
void calc_Euler_yi(int n)
{
    euler_yi.push_back(xi_val[0]);
    double val;
    for (int i = 1; i < n; i++)
    {
        val = euler_yi[i - 1] + h * func_calc(xi_val[i - 1], yi_val[i - 1]);
        euler_yi.push_back(val);
    }
}
void calc_k1(vector<double> xi_val, vector<double> yi_val, int n)
{
    for (int i = 0; i < n; i++)
    {
        k1_i.push_back(func_calc(xi_val[i], yi_val[i]));
    }
}
void calc_k2(vector<double> xi_val, vector<double> yi_val, int n)
{
    for (int i = 0; i < n; i++)
    {
        k2_i.push_back(func_calc(xi_val[i] + h, (yi_val[i] + h * k1_i[i])));
    }
}

void calc_k3(vector<double> xi_val, vector<double> yi_val, int n) {
   
    for (int i = 0; i < n; i++)
    {
        k2_i.push_back(func_calc(xi_val[i] + (h/2), (yi_val[i] + (h/2) * k1_i[i])));
    }

    double h_div = h/2 ; 
    for (int i = 0 ;i < n ; i ++) {
        k3_i.push_back(func_calc(xi_val[i]+h_div, yi_val[i]+h_div*k2_i[i])); 
    }
}
void calc_k4(vector<double> xi_val, vector<double> yi_val, int n) { 
    for (int i = 0 ; i < n; i++) { 
        k4_i.push_back(func_calc(xi_val[i]+h, yi_val[i]+h*k3_i[i])); 
    }
}
// problem with k1[i] and k2[i] - out of range
void calc_iEuler_yi(int n)
{
    yi_calc(n); 
    double result;
    double yi = 0 ; 
    calc_k1(xi_val, yi_val, n) ; 
    calc_k2(xi_val, yi_val, n) ; 
    double k1; 
    double k2 ; 
    ieuler_yi.push_back(yi_val[0]); 
    for (int i = 0; i < n - 1; i++)
    {
        yi = ieuler_yi[i] + (h / 2) * (k1_i[i]+k2_i[i]);
        ieuler_yi.push_back(yi);
    }
}
void print_Euler_yi(int n)
{
    cout << "Euler_yi=\n";
    for (int i = 0; i < n; i++)
    {
        cout << fixed << setprecision(5) << euler_yi[i] << " ";
    }
}
void print_iEuler_yi(int n)
{
    cout << "iEuler_yi=\n";
    for (int i = 0; i < n; i++)
    {
        cout << fixed << setprecision(5) << ieuler_yi[i] << " ";
    }
}
// calculate local error for euler method 
void calc_Euler_LE_xi(int n)
{
    xi_calc(n) ; 
    yi_calc(n);
    // euler for yi
    calc_Euler_yi(n) ; 
    vector<double> check ;  
    for (int i = 0; i < n; i++)
    {  
        euler_le_xi.push_back(abs(euler_yi[i]- yi_val[i]));
    }
}
// calculating error for improved euler method
void calc_imprEuler_LE_xi(int n)
{

    calc_iEuler_yi(n) ; 
    vector<double> check ;  
    for (int i = 0; i < n; i++)
    {  
        // probably mistake in function ieuler_yi
        impr_euler_le_xi.push_back(abs(ieuler_yi[i]- yi_val[i]));
    }
}
void calc_runge_kutta_sol(int n){
    yi_calc(n); 
    calc_k1(xi_val, yi_val, n); 
    calc_k3(xi_val, yi_val, n); 
    calc_k4(xi_val, yi_val, n); 
    runge_kutta_sol.push_back(yi_val[0]); 
    double rks = 0 ; 
    for (int i = 0 ; i < n-1; i++) { 
        rks = runge_kutta_sol[i] + (h/6)*(k1_i[i]+2*k2_i[i]+ 2*k3_i[i]+k4_i[i]); 
        runge_kutta_sol.push_back(rks); 
    }
    
}
void print_Euler_LE_xi(int n) { 
        cout << "Euler_LE(xi)=\n"; 
    for (int i = 0 ;i < n ; i++) {
        cout << euler_le_xi[i] << " " ; 
    }
}
void print_imprEuler_LE_xi(int n) { 
        cout << "iEuler_LE(xi)=\n"; 
    for (int i = 0 ;i < n ; i++) {
        cout << impr_euler_le_xi[i] << " " ; 
    }
}
void variant_first(int n)
{
    xi_calc(n);
    print_xi(n);

    cout << endl;
    yi_calc(n);
    print_yi(n);
}
void variant_second(int n)
{
    xi_calc(n);
    print_xi(n);
    cout << endl;
    calc_Euler_yi(n);
    print_Euler_yi(n);
}
void print_ni(int n) {
    cout << "ni=\n" ; 
    for (int i = 0 ; i <= n; i++) { 
        cout << ni_val[i] << " " ; 
    }
}
void calc_ni (int n, int n1, int n2) { 
    for (int i = 0; i <= n; i++) { 
        ni_val.push_back(n1+i); 
    }
}
void variant_third(int n)
{
    xi_calc(n);
    print_xi(n);
    cout << endl;
    // problem in this funciton
    calc_iEuler_yi(n);
    print_iEuler_yi(n);
}
void variant_fourth(int n) { 
    xi_calc(n) ; 
    print_xi(n); 
    cout << endl ; 

    calc_runge_kutta_sol(n); 
    cout << "RK4_yi=\n"; 
    for (int i = 0; i < n; i++){
        cout << runge_kutta_sol[i]<< " " ; 
    }
}
void calc_RK_Local_error(int n){
    //xi_calc(n); 
    calc_runge_kutta_sol(n); 
    for (int i = 0 ;i < n; i++) {
        runge_kutta_local_errors.push_back(abs(runge_kutta_sol[i]-yi_val[i])); 
    }
}
void variant_fifth(int n)
{
    xi_calc(n);
    print_xi(n);
    cout << endl;
    calc_Euler_LE_xi(n);
    print_Euler_LE_xi(n);
}
void variant_six(int n) { 
    xi_calc(n); 
    print_xi(n);
    cout << endl ; 
    calc_imprEuler_LE_xi( n) ; 
    print_imprEuler_LE_xi(n) ; 
}
void variant_seven(int n){
    xi_calc(n); 
    print_xi(n); 
    cout << endl ; 
    calc_RK_Local_error(n);
    cout << "RK4_LE(xi)=\n";  
    for (int i = 0 ;i < n ; i++){
        cout << runge_kutta_local_errors[i]<< " "; 
    }

}
void variant_eighth(int n, int n1, int n2) { 
    calc_ni(n, n1, n2);
    print_ni(n) ; 
    cout << endl ;
    euler_global_error.resize(n+1) ;  
    for (int i = 0 ;i < n+1; i++) { 
        calc_Euler_LE_xi(ni_val[i]); 
       
        euler_global_error[i] = (*max_element(euler_le_xi.begin(), euler_le_xi.end())); 
        euler_le_xi.clear(); 
        xi_val.clear(); 
        yi_val.clear(); 
        euler_yi.clear(); 
        xi_val.push_back(0) ; 
        yi_val.push_back(0) ; 
    }
    cout << "Euler_GE(n)=\n"; 
    for (int i = 0 ;i < euler_global_error.size(); i++) { 
        cout<< fixed<< setprecision(5) << euler_global_error[i] << " " ; 
    }
}
void variant_nine(int n, int n1, int n2) { 
    calc_ni(n, n1, n2);
    print_ni(n) ; 
    cout << endl ;
    euler_improved_global_error.resize(n+1) ;  
    for (int i = 0 ;i < n+1; i++) { 
        // from this part change 
        xi_calc(ni_val[i]); 
        calc_imprEuler_LE_xi(ni_val[i]); 
        
       
        euler_improved_global_error[i] = (*max_element(impr_euler_le_xi.begin(), impr_euler_le_xi.end())); 
        euler_le_xi.clear(); 
        xi_val.clear(); 
        yi_val.clear(); 
        k1_i.clear(); 
        k2_i.clear(); 
        //euler_yi.clear();
        impr_euler_le_xi.clear();  
        ieuler_yi.clear(); 
        xi_val.push_back(0) ; 
        yi_val.push_back(0) ; 
        // till this part change 
    }
    cout << "iEuler_GE(n)=\n"; 
    for (int i = 0 ;i < euler_improved_global_error.size(); i++) { 
        cout<< fixed<< setprecision(5) << euler_improved_global_error[i] << " " ; 
    }
}
void variant_ten(int n, int n1, int n2) { 
    calc_ni(n,n1,n2); 
    print_ni(n); 
    cout << endl; 
    
    runge_kutta_global_errors.resize(n+1); 
    for (int i = 0 ; i < n+1;i++){
        xi_calc(ni_val[i]); 
        calc_RK_Local_error(ni_val[i]); 
       
        runge_kutta_global_errors[i] = (*max_element(runge_kutta_local_errors.begin(), runge_kutta_local_errors.end())); 
        xi_val.clear(); 
        yi_val.clear(); 
        runge_kutta_sol.clear(); 
        runge_kutta_local_errors.clear(); 
        k1_i.clear(); 
        k2_i.clear();
        k3_i.clear(); 
        k4_i.clear();  
        xi_val.push_back(0); 
        yi_val.push_back(0); 
    }
    cout << "RK4_GE(n)=\n"; 
    for (int i = 0 ; i < runge_kutta_global_errors.size() ;i++){
        cout << fixed<<setprecision(5)<<runge_kutta_global_errors[i]<< " "; 
    }
}
int main()
{

    double n, n1, n2;
    int number_task;
    cin >> n >> n1 >> n2;
    cin >> number_task;

    cout << endl;
    switch (number_task)
    {
    case 1:
        variant_first(n); 
        break;

    case 2:
        variant_second(n);  
        break;
    case 3:
        variant_third(n); 
        break;
    case 4:
        variant_fourth(n); 
        break;
    case 5:
        variant_fifth(n);  
        break;
    case 6: 
        variant_six(n) ;  
        break; 
    case 7: 
        variant_seven(n);  
        break;
    case 8: 
        variant_eighth(n, n1, n2) ;   
        break; 
    case 9:
        variant_nine(n, n1, n2); 
        break; 
    case 10: 
        variant_ten(n, n1, n2);  

    }
}