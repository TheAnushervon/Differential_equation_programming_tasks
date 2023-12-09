#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
#include <string>
#include <iomanip>
using namespace std;

double epsilon = numeric_limits<double>::epsilon();
vector<double> xi_val = {0};
vector<double> yi_val = {0};
vector<double> euler_yi;
vector<double> ieuler_yi; 
vector<double> k1_i; 
vector<double> k2_i; 
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
    for (int i = 1; i <= n; i++)
    {
        xi_val.push_back(xi_val[0] + i * h);
    }

    return xi_val;
}
vector<double> yi_calc(int n)
{
    for (int i = 1; i <= n; i++)
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
void variant_first(int n)
{
    xi_calc(n);
    print_xi(n);

    cout << endl;
    yi_calc(n);
    print_yi(n);
}
double func_calc(double xi_val, double yi_val)
{
    double result;
    result = cos(xi_val);
    return result;
}
void calc_Euler_yi(int n)
{
    euler_yi.push_back(xi_val[0]);
    double val;
    for (int i = 1; i <= n; i++)
    {
        val = euler_yi[i - 1] + h * func_calc(xi_val[i - 1], yi_val[i - 1]);
        euler_yi.push_back(val);
    }
}
void calc_k1(vector<double> xi_val, vector<double> yi_val, int n){
    for (int i = 0 ; i < n ; i++) { 
       k1_i.push_back(func_calc(xi_val[i], yi_val[i])); 
    }
}
void calc_k2(vector<double> xi_val, vector<double> yi_val, int n){
    for (int i = 0 ; i < n ; i++) { 
       k2_i.push_back(func_calc(xi_val[i]+h, (yi_val[i]+h*k1_i[i]))); 
    }
}
void calc_iEuler_yi(int n) { 
    calc_k1(xi_val, yi_val, n) ; 
    calc_k2(xi_val, yi_val, n) ;
    ieuler_yi.push_back(yi_val[0]+(h/2)*(k1_i[0] + k2_i[0]));  
    double result ; 
    for (int i = 0 ; i < n-1; i++) { 
        result = ieuler_yi[i] + (h/2)*(k1_i[i]*k2_i[i]); 
        ieuler_yi.push_back(result) ; 
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
void print_iEuler_yi(int n) { 
    cout << "iEuler_yi=\n"; 
    for (int i = 0 ; i < n ; i++) { 
        cout << fixed<< setprecision(5) << ieuler_yi[i] << " "; 
    }
}
void variant_second(int n)
{
    xi_calc(n);
    print_xi(n);
    cout << endl;
    calc_Euler_yi(n);
    print_Euler_yi(n);
}
void variant_third(int n){ 
xi_calc(n) ; 
print_xi(n) ; 
cout << endl ; 
calc_iEuler_yi(n);
print_iEuler_yi(n) ; 
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
    }
}