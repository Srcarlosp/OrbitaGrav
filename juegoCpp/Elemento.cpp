#include <math.h>
#include <stdlib.h>

#include "Elemento.h"
#include "glut.h"
#include "funciones_inline.h"

float G = 6.67384F * powf(10.0F, -11.0F);
float time_scale = 1.0F;

#define TRACE_LONG 3000

void Elemento::setColor(unsigned char r, unsigned char v, unsigned char a)
{
	colorVec[rojo] = r;
	colorVec[verde] = v;
	colorVec[azul] = a;
}

void Elemento::setColor(int elem, Elemento *e, unsigned char r, unsigned char v, unsigned char a)
{
	e[elem].colorVec[rojo] = r;
	e[elem].colorVec[verde] = v;
	e[elem].colorVec[azul] = a;
}

void Elemento::setRad(float r)
{
	rad = r;
}

void Elemento::setMass(float m)
{
	mass = m;
	rad = logf(m)/7;
	colorVec[0] -= (unsigned int) 25*log10f(m);
	//colorVec[1] -= (unsigned int) 25*log10f(m);
	//colorVec[2] -= (unsigned int) 25*log10f(m);
}

void Elemento::setPos(float xx, float yy, float zz)
{
	posVec[x] = xx;
	posVec[y] = yy;
	posVec[z] = zz;
}

void Elemento::setVel(float xx, float yy, float zz)
{
	velVec[x] = xx;
	velVec[y] = yy;
	velVec[z] = zz;
}

void Elemento::setAcc(float xx, float yy, float zz)
{
	accVec[x] = xx;
	accVec[y] = yy;
	accVec[z] = zz;
}

void Elemento::setFor(float xx, float yy, float zz)
{
	forVec[x] = xx;
	forVec[y] = yy;
	forVec[z] = zz;
}

void Elemento::setZero(int elem, Elemento *e)
{
	e[elem].setPos(0.0F, 0.0F, 0.0F);
	e[elem].setVel(0.0F, 0.0F, 0.0F);
	e[elem].setAcc(0.0F, 0.0F, 0.0F);
	e[elem].setFor(0.0F, 0.0F, 0.0F);
	for (int i = 0; i < 1000; i++)
		for (int ii = 0; ii < 3; ii++)
			e[elem].trace[i][ii] = 0;
}

void Elemento::doCalculus(int dim, int elem, Elemento *e)
{
	for (int ii = 0; ii < 3; ii++)
		e[elem].forVec[ii] = 0;
	for (int i = 0; i < dim; i++)
	{
		if (i != elem)
		{
			float tempDist[3];
			float tempModu;
			for (int ii = 0; ii < 3; ii++)
				tempDist[ii] = e[elem].posVec[ii] - e[i].posVec[ii];
			tempModu = norma(tempDist);
			for (int ii = 0; ii < 3; ii++)
				e[elem].forVec[ii] += -G * ((e[elem].mass * e[i].mass) / tempModu) * tempDist[ii];
		}
	}
	for (int ii = 0; ii < 3; ii++)
		e[elem].accVec[ii] = e[elem].forVec[ii] / e[elem].mass;
}

void Elemento::doMove(int elem, Elemento *e)
{
	if (tracePT >= TRACE_LONG) tracePT = 0;
	e[elem].velVec[x] = e[elem].accVec[x] * time_scale + e[elem].velVec[x];
	e[elem].velVec[y] = e[elem].accVec[y] * time_scale + e[elem].velVec[y];
	e[elem].velVec[z] = e[elem].accVec[z] * time_scale + e[elem].velVec[z];
	e[elem].posVec[x] = e[elem].velVec[x] * time_scale + e[elem].posVec[x];
	e[elem].posVec[y] = e[elem].velVec[y] * time_scale + e[elem].posVec[y];
	e[elem].posVec[z] = e[elem].velVec[z] * time_scale + e[elem].posVec[z];
	e[elem].trace[tracePT][x] = e[elem].posVec[x];
	e[elem].trace[tracePT][y] = e[elem].posVec[y];
	e[elem].trace[tracePT][z] = e[elem].posVec[z];
	tracePT++;
}

void Elemento::doDraw(int elem, Elemento *e)
{
	glColor3ub(e[elem].colorVec[rojo], e[elem].colorVec[verde], e[elem].colorVec[azul]);
	glTranslatef(e[elem].posVec[x], e[elem].posVec[y], e[elem].posVec[z]);
	glutSolidSphere(e[elem].rad, 20, 20);
	glTranslatef(-e[elem].posVec[x], -e[elem].posVec[y], -e[elem].posVec[z]);
	glDisable(GL_LIGHTING);
	for (int i = 0; i < TRACE_LONG; i++)
	{
		glBegin(GL_POINTS);
		glVertex3f(e[elem].trace[i][x], e[elem].trace[i][y], e[elem].trace[i][z]);
		glEnd();
	}
	glEnable(GL_LIGHTING);
}