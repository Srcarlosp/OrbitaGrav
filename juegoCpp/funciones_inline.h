#include <stdio.h>
#include <math.h>

inline float norma(float *v, bool prenorma = true, int dim = 3)
{
	float modulo = 0;
	for (int i=0; i<dim; i++)
		modulo += v[i] * v[i];
	modulo = (float)sqrt(modulo);
	if ((prenorma == true)&&(modulo < 0.0001))
		for (int i=0; i<dim; i++) 
			v[i] = v[i]/modulo;
	return modulo;
}