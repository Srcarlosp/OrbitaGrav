#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>

#include "glut.h"
#include "Elemento.h"
#include "Ojos.h"

void OnDraw(void);
void OnTimer(int value); 
void OnKeyboardDown(unsigned char key, int x, int y);

const int dim = 3;
//Objetos Primarios
Elemento myElem;
Elemento e[dim];
Ojos vista;

float scale = 1;

//Secuencia de inicializacion
void inicializaVentana(int argc, char* argv[])
{
	//Inicializar el gestor de ventanas GLUT 
	//y crear la ventana 
	glutInit(&argc, argv);
	glutInitWindowSize(1600, 1000);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("MiJuego");
	//habilitar luces y definir perspectiva 
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(40.0, 1600 / 1000.0f, 0.1, 1000); //Registrar los callbacks
	glutDisplayFunc(OnDraw);
	glutTimerFunc(10, OnTimer, 0); //10 ms
	glutKeyboardFunc(OnKeyboardDown);
	srand(time(NULL));
}

void inicializaObjetos()
{
	for (int i = 0; i < dim; i++)
	{
		myElem.setZero(i, e);
		myElem.setColor(i, e);
	}

	scale = 1.496*pow(10.0, 10);

	e[0].setPos(0.0F, 0.0F, 0.0F);
	e[0].setVel(0.0F, 0.0F, 0.0F);
	e[0].setMass(1.988*pow(10.0,30));
	e[0].setRad(1.0F);
	e[0].setColor(255, 255, 0);

	e[1].setPos(1.496*pow(10.0,11), 0.0F, 0.0F);
	e[1].setVel(0.0F, 0.0F, 29780*pow(10.0, 0));
	e[1].setMass(5.972*pow(10.0,24));
	e[1].setRad(0.02F);

	e[2].setPos(1.496*pow(10.0, 11)-384399000, 0.0F, 0.0F);
	e[2].setVel(0.0F, 0.0F, 29780 * pow(10.0, 0) + 1022 * pow(10.0, 0));
	e[2].setMass(7.3477*pow(10.0, 22));
	e[2].setRad(0.01F);
	
	/*
	e[3].setPos(-50.0F, 0.0F, 0.0F);
	e[3].setVel(0.0F, 0.0F, 0.05F);
	e[3].setMass(100.0F);

	e[4].setPos(-50.0F, 20.0F, 20.0F);
	e[4].setVel(0.0F, 0.2F, 0.5F);
	e[4].setMass(500.0F);

	e[5].setPos(10.0F, 0.0F, 10.0F);
	e[5].setVel(0.5F, 0.0F, -0.5F);
	e[5].setMass(500.0F);
	*/
}


void inicializaObjetosCC()
{
	for (int i = 0; i < dim; i++)
	{
		myElem.setZero(i, e);
		myElem.setColor(i, e);
	}

	e[0].setPos(0.0F, 0.0F, 0.0F);
	e[0].setVel(0.0F, 0.0F, -0.0F);
	e[0].setMass(20000000000.0F);
	e[0].setColor(255, 255, 0);

	e[1].setPos(70.0F, 10.0F, 20.0F);
	e[1].setVel(0.01F, 0.0F, 1.0);
	e[1].setMass(5000.0F);

	e[2].setPos(60.0F, 0.0F, 0.0F);
	e[2].setVel(-0.7F, 0.3F, 0.7F);
	e[2].setMass(5000.0F);

	e[3].setPos(-80.0F, 0.0F, 0.0F);
	e[3].setVel(0.0F, 0.0F, 1.0F);
	e[3].setMass(50000000.0F);

	e[4].setPos(-75.0F, 0.0F, 0.0F);
	e[4].setVel(0.0F, 0.0F, 1.1F);
	e[4].setMass(100000.0F);

	e[5].setPos(10.0F, 0.0F, 10.0F);
	e[5].setVel(0.75F, 0.0F, -0.75F);
	e[5].setMass(500000.0F);
}

void inicializaObjetosLunasEstables()
{
	for (int i = 0; i < dim; i++)
	{
		myElem.setZero(i, e);
		myElem.setColor(i, e);
	}

	e[0].setPos(50.0F, 0.0F, 0.0F);
	e[0].setVel(0.0F, 0.0F, -0.5F);
	e[0].setMass(10000000000.0F);
	e[0].setColor(255, 255, 0);

	e[1].setPos(50.0F, 10.0F, 20.0F);
	e[1].setVel(0.01F, 0.0F, 0.5F);
	e[1].setMass(5000.0F);

	e[2].setPos(40.0F, 0.0F, 0.0F);
	e[2].setVel(-0.1F, 0.0F, 0.51F);
	e[2].setMass(5000.0F);

	e[3].setPos(-50.0F, 0.0F, 0.0F);
	e[3].setVel(0.0F, 0.0F, 0.5F);
	e[3].setMass(10000000000.0F);

	e[4].setPos(-50.0F, 20.0F, 20.0F);
	e[4].setVel(0.0F, 0.2F, 0.5F);
	e[4].setMass(50000.0F);

	e[5].setPos(10.0F, 0.0F, 10.0F);
	e[5].setVel(0.5F, 0.0F, -0.5F);
	e[5].setMass(500000.0F);
}

void inicializaObjetosLunaInestable()
{
	for (int i = 0; i < dim; i++)
	{
		myElem.setZero(i, e);
		myElem.setColor(i, e);
	}

	e[0].setPos(50.0F, 0.0F, 0.0F);
	e[0].setVel(0.0F, 0.0F, -0.05F);
	e[0].setMass(10000000000.0F);
	e[0].setColor(255, 255, 0);

	e[1].setPos(50.0F, 10.0F, 20.0F);
	e[1].setVel(0.01F, 0.0F, 0.5F);
	e[1].setMass(5000.0F);

	e[2].setPos(40.0F, 0.0F, 0.0F);
	e[2].setVel(-0.1F, 0.0F, 0.51F);
	e[2].setMass(5000.0F);

	e[3].setPos(-50.0F, 0.0F, 0.0F);
	e[3].setVel(0.0F, 0.0F, 0.05F);
	e[3].setMass(10000000000.0F);

	e[4].setPos(-50.0F, 20.0F, 20.0F);
	e[4].setVel(0.0F, 0.2F, 0.5F);
	e[4].setMass(50000.0F);

	e[5].setPos(10.0F, 0.0F, 10.0F);
	e[5].setVel(0.5F, 0.0F, -0.5F);
	e[5].setMass(500000.0F);
}

int main(int argc,char* argv[])
{
	//Abre la ventana y GL
	inicializaVentana(argc, argv);
	//Crea los objetos
	inicializaObjetos();
	//pasarle el control a GLUT,que llamara a los callbacks 
	glutMainLoop(); 

	return 0; 
} 

void OnDraw(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Para definir el punto de vista
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity(); 
	gluLookAt(vista.o_x, vista.o_y, vista.o_z, // posicion del ojo
			  0.0, 0.0, 0.0, // hacia que punto mira (0,0,0) 
			  0.0, 1.0, 0.0); // definimos hacia arriba (eje Y)

	//aqui es donde hay que poner el código de dibujo
	for (int i = 0; i < dim; i++)
		myElem.doDraw(i, e, scale);

	glutWireCube(100);

	glutSwapBuffers(); //Cambia los buffer de dibujo, no borrar esta linea ni poner nada despues
}

void OnTimer(int value) //poner aqui el codigo de animacion
{

	for (int i = 0; i < dim; i++)
		myElem.doCalculus(dim, i, e);
	for (int i = 0; i < dim; i++)
		myElem.doMove(i, e);
	vista.orbita();

	glutTimerFunc(10,OnTimer,0); //Temporizador de actulizacion
	glutPostRedisplay(); //Actualizacion de pantalla

}

void OnKeyboardDown(unsigned char key, int x_t, int y_t)
{
	if (key == 'r') vista.dif -= 0.001;
	if (key == 'f') vista.dif += 0.001;
	if (key == 't') vista.d += 1;
	if (key == 'g') vista.d -= 1;
	if (key == 'w') vista.o_y += 1;
	if (key == 's') vista.o_y -= 1;
}