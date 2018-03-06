#include<math.h>

float ricker_wavelet(float freq, float t){
	float f;
	float pi=22.0/7.0;
    f = sin(2.0 * pi * freq * t) *exp(-4.0* (pi*freq*t)*(pi*freq*t)/ 16.0);
    return f;
}
