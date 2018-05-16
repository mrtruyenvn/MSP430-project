#include <math.h>

float S = 0;
float T = 0;

float getDistances(double siglvl, double freq)
{
	return pow(10.0, (27.55 - (20 * log10(freq)) + siglvl) / 20.0);
}

float getTrilateration(float *x,float *y, float x1,float y1, float x2, float y2, float x3, float y3, float r1, float r2, float r3 )
{
      S = (pow(x3, 2.) - pow(x2, 2.) + pow(y3, 2.) - pow(y2, 2.) + pow(r2, 2.) - pow(r3, 2.)) / 2.0;
     T = (pow(x3, 2.) - pow(x2, 2.) + pow(y1, 2.) - pow(y2, 2.) + pow(r2, 2.) - pow(r1, 2.)) / 2.0;

     *y = ((T * (x2 - x3)) - (S * (x2 - x1))) / (((y1 - y2) * (x2 - x3)) - ((y3 - y2) * (x2 - x1)));
     *x = ((*y * (y1 - y2)) - T) / (x2 - x1);

     return 1;

 }
