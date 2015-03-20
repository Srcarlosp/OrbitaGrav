#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>

#include "glut.h"
#include "Asteroide.h"
//#include "constantes.h"

void OnDraw(void);
void OnTimer(int value); 
void OnKeyboardDown(unsigned char key, int x, int y);

const int dim = 4;

struct ojos
{
	float o_x = 0, o_y = 100, o_z = 1;
} vista;

Elemento myElem;
Elemento e[dim];

//Secuencia de inicializacion
void inicializa(int argc, char* argv[])
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

//Definicion del motor gráfico
void motor(){
	for (int i = 0; i < dim; i++)
		myElem.doDraw(i, e);
}


int main(int argc,char* argv[])
{
	inicializa(argc, argv);

	for (int i = 0; i < dim; i++)
	{
		myElem.setZero(i, e);
		myElem.setColor(i, e);
	}

	e[0].setPos(0.0F, 0.0F, 0.0F);
	e[0].setVel(0.0F, 0.0F, 0.0F);
	e[0].setMass(10000000.0F);
	e[0].setColor(255, 255, 0);
	e[1].setPos(0.0F, 10.0F, 0.0F);
	e[1].setVel(0.01F, 0.0F, 0.05F);
	e[1].setMass(100000.0F);
	e[2].setPos(20.0F, 0.0F, 0.0F);
	e[2].setVel(0.0F, 0.0F, 0.01F);
	e[2].setMass(200.0F);
	e[3].setPos(0.0F, 0.0F, -30.0F);
	e[3].setVel(0.05F, 0.0F, 0.0F);
	e[3].setMass(10000.0F);

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
	motor();
	glutWireCube(100);

	glutSwapBuffers(); //Cambia los buffer de dibujo, no borrar esta linea ni poner nada despues
}

void OnTimer(int value) //poner aqui el codigo de animacion
{

	for (int i = 0; i < dim; i++)
		myElem.doCalculus(dim, i, e);
	for (int i = 0; i < dim; i++)
		myElem.doMove(i, e);

	glutTimerFunc(10,OnTimer,0); //Temporizador de actulizacion
	glutPostRedisplay(); //Actualizacion de pantalla

}

void OnKeyboardDown(unsigned char key, int x_t, int y_t)
{
	if (key == 'd') vista.o_x += 1;
	if (key == 'a') vista.o_x -= 1;
	if (key == 'w') vista.o_y += 1;
	if (key == 's') vista.o_y -= 1;
}