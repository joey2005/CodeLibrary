#include <bits/stdc++.h>

using namespace std;

// fft
const double pi=acos(-1.0); 
const int maxn=(1<<19)+5; 
template<class T> inline T lowbit(T n){return (n^(n-1))&n;} 
struct Complex{
    double a,b;  
    Complex(){}; 
    Complex(double _a,double _b) {a=_a;b=_b;} 
}; 
int n,id; 
Complex tmp[maxn],P[maxn],PB[maxn]; 
void fill(int s[],int L,int m,int d) { 
    if (m==n)
        P[d]=Complex(id==L?0:s[id++],0); 
    else { 
        fill(s,L,m*2,d); 
        fill(s,L,m*2,d+m); 
    } 
} 
void fill2(int m,int d) { 
    if (m==n) 
        P[d]=tmp[id++]; 
    else { 
        fill2(m*2,d); 
        fill2(m*2,d+m); 
    } 
} 
void fft(int oper) { 
    for (int d=0;(1<<d)<n;++d) { 
        int i,m=(1<<d); 
        double p0=2*pi/double(m*2)*double(oper); 
        double sinp0=sin(p0); 
        double cosp0=cos(p0); 
        for (i=0;i<n;i+=(m*2)) { 
            double sinp=0, cosp=1; 
            for (int j=0;j<m;j++) { 
                double ta=cosp*P[i+j+m].a-sinp*P[i+j+m].b; 
                double tb=cosp*P[i+j+m].b+sinp*P[i+j+m].a; 
                P[i+j+m].a=P[i+j].a-ta; 
                P[i+j+m].b=P[i+j].b-tb; 
                P[i+j].a+=ta; 
                P[i+j].b+=tb;   
                double tsinp=sinp; 
                sinp=sinp*cosp0+ cosp*sinp0; 
                cosp=cosp*cosp0-tsinp*sinp0;   
            } 
        } 
    } 
} 
void findConvolution(int s1[], int L1, int s2[], int L2, double result[]) {
    for (n=L1+L2;n!=lowbit(n);n+=lowbit(n)); 
    id=0; fill(s1,L1,1,0); fft(1); 
    for (int i = 0; i < n; ++i) PB[i]=P[i]; 
    id=0; fill(s2,L2,1,0); fft(1); 
    for (int i = 0; i < n; ++i) { 
        tmp[i].a=P[i].a*PB[i].a-P[i].b*PB[i].b; 
        tmp[i].b=P[i].a*PB[i].b+P[i].b*PB[i].a; 
    } 
    id=0; fill2(1,0); fft(-1); 
    for (int i = 0; i < n; ++i) {
        result[i]=P[i].a/(double)n;
    }
}

int main() {
}
