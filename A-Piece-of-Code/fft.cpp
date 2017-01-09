#include <bits/stdc++.h>

using namespace std;

// fft
const double pi=acos(-1.0); 
const int maxn=(1<<16)+5; 
struct Complex{
    double re,im;
    Complex(){}; 
    Complex(double _re,double _im) {re=_re;im=_im;} 
}; 
int n,id; 
Complex tmp[maxn],P[maxn],PB[maxn]; 
void fft(int s[], int L, int oper) { 
    int h = __builtin_ctz(n);
    for (int i = 0; i < L; ++i) P[i] = Complex(s[i],0);
    for (int i = L; i < n; ++i) P[i] = Complex(0,0);
    for (int i = 0; i < n; ++i) {
        int rev = 0;
        for (int j = 0; j < h; ++j) {
            rev = (rev << 1) | (i >> j & 1);
        }
        if (i < rev) {
            swap(P[i], P[rev]);
        }
    }

    for (int s = 2; s <= n; s <<= 1) {
        int nt = s >> 1;
        double p0=2*pi/(double)(s)*(double)(oper); 
        double sinp0=sin(p0); 
        double cosp0=cos(p0); 
        for (int j = 0; j < n; j += s) {
            double sinp=0, cosp=1; 
            for (int t = j; t < j + nt; ++t) {
                int jp = t + nt;
                double re = cosp * P[jp].re - sinp * P[jp].im; 
                double im = cosp * P[jp].im + sinp * P[jp].re; 
                P[jp].re = P[t].re - re; 
                P[jp].im = P[t].im - im; 
                P[t].re += re; 
                P[t].im += im;  
                double tsinp=sinp; 
                sinp=sinp*cosp0+ cosp*sinp0; 
                cosp=cosp*cosp0-tsinp*sinp0;   
            } 
        } 
    } 

    if (oper == -1) {
        for (int i = 0; i < n; ++i) {
            P[i].re /= n;
            P[i].im /= n;
        }
    }
} 
void fft(int oper) { 
    int h = __builtin_ctz(n);
    for (int i = 0; i < n; ++i) {
        int rev = 0;
        for (int j = 0; j < h; ++j) {
            rev = (rev << 1) | (i >> j & 1);
        }
        if (i < rev) {
            swap(P[i], P[rev]);
        }
    }

    for (int s = 2; s <= n; s <<= 1) {
        int nt = s >> 1;
        double p0=2*pi/(double)(s)*(double)(oper); 
        double sinp0=sin(p0); 
        double cosp0=cos(p0); 
        for (int j = 0; j < n; j += s) {
            double sinp=0, cosp=1; 
            for (int t = j; t < j + nt; ++t) {
                int jp = t + nt;
                double re = cosp * P[jp].re - sinp * P[jp].im; 
                double im = cosp * P[jp].im + sinp * P[jp].re; 
                P[jp].re = P[t].re - re; 
                P[jp].im = P[t].im - im; 
                P[t].re += re; 
                P[t].im += im;  
                double tsinp=sinp; 
                sinp=sinp*cosp0+ cosp*sinp0; 
                cosp=cosp*cosp0-tsinp*sinp0;   
            } 
        } 
    } 

    if (oper == -1) {
        for (int i = 0; i < n; ++i) {
            P[i].re /= n;
            P[i].im /= n;
        }
    }
}
void convolute(int s1[], int L1, int s2[], int L2, int result[]) {
    for (n = 1; n < L1 + L2; n <<= 1);
    fft(s1, L1, 1); 
    for (int i = 0; i < n; ++i) PB[i] = P[i]; 
    fft(s2, L2, 1); 
    for (int i = 0; i < n; ++i) { 
        tmp[i].re = P[i].re * PB[i].re - P[i].im * PB[i].im; 
        tmp[i].im = P[i].re * PB[i].im + P[i].im * PB[i].re; 
    } 
    for (int i = 0; i < n; ++i) P[i] = tmp[i]; 
    fft(-1); 
    for (int i = 0; i < n; ++i) {
        result[i] = (int)(P[i].re + 0.5);
    }
}

// random test
int a[maxn], b[maxn], res[maxn];

int main() {
    const int len = 30000;
    for (int _ = 0; _ < 10; ++_) {
        for (int i = 0; i < len; ++i) {
            a[i] = rand() % 10;
            b[i] = rand() % 10;
        }
        convolute(a, len, b, len, res);
        for (int i = 0; i < len; ++i) {
            for (int j = 0; j < len; ++j) {
                res[i + j] -= a[i] * b[j];
            }
        }
        for (int i = 0; i < len * 2; ++i) {
            if (res[i]) {
                cout << _ << ": no" << endl;
                return 0;
            }
        }
        cout << _ << ": ok" << endl;
        cerr << fixed << setprecision(10) << "time elpased = " << clock() / (double)(CLOCKS_PER_SEC) << " seconds." << endl;
    }
}
