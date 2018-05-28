#include <cmath>
double ricker_wavelet_1(double freq, double t){
	double f;
	double pi=22.0/7.0;
    f = sin(2.0 * pi * freq * t) *exp(-4.0* (pi*freq*t)*(pi*freq*t)/ 16.0);
    return f;
}
double ricker_wavelet_2(double freq, double t){
	double f;
	double pi=22.0/7.0;
    f = -5.76*freq*freq*(1-16.0*(0.6*freq*t-1)*(0.6*freq*t-1)) *exp(-8.0* (0.6*freq*t-1)*(0.6*freq*t-1));
    return f;
}
