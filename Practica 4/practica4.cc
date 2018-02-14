//**************************************************************************
// Práctica 2
//
// Domingo Martin Perandres 2013-2016
//
// GPL
//**************************************************************************

#include "stdlib.h"
#include "stdio.h"
#include <GLUT/glut.h>
#include <ctype.h>
#include "objetos.h"
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

// tamaño de los ejes
//const int AXIS_SIZE=5000;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=500,UI_window_height=500;

unsigned char tecla='l', figura = '1';

//Declaracion de objetos
_cubo cubito = _cubo(10.0);
_piramide piramidita = _piramide(5.0, 7.5);

_modeloPly objetito;
_modeloPlyRevolucion objetitoRev = _modeloPlyRevolucion();

_paloSelfie palito;

float estirado = 1, girado = 0, rotado = 0;
bool subiendo = true, girando = true, rotando = true, animado = false;
int velociE = 1, velociG = 5, velociR = 5;

//**************************************************************************
//
//***************************************************************************

void clear_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
//  Front_plane>0  Back_plane>PlanoDelantero)
glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects()
{

	switch(tecla){
		case 'p':
			if(figura=='1') cubito.draw_puntos(0.0, 0.0, 0.0, 3.0);
			else if(figura=='2') piramidita.draw_puntos(0.0, 0.0, 0.0, 3.0);
			else if(figura=='3') objetito.draw_puntos(1.0,0.0,0.0,4.0);
			else if(figura=='4') objetitoRev.draw_puntos(1.0,0.0,0.0,4.0);
			else if(figura=='5') palito.pintar(estirado, girado, rotado, 1);
			break;
		case 'l':
			if(figura=='1') cubito.draw_aristas(0.0, 0.0, 0.0, 1.0);
			else if(figura=='2') piramidita.draw_aristas(0.0, 0.0, 0.0, 1.0);
			else if(figura=='3') objetito.draw_aristas(1.0,0.0,0.0,1.0);
			else if(figura=='4') objetitoRev.draw_aristas(1.0,0.0,0.0,1.0);
			else if(figura=='5') palito.pintar(estirado, girado, rotado, 2);
			break;
		case 'f':
			if(figura=='1') cubito.draw_solido(1.0, 0.0, 0.0);
			else if(figura=='2') piramidita.draw_solido(1.0, 0.0, 0.0);
			else if(figura=='3') objetito.draw_solido(0.0,1.0,0.0);
			else if(figura=='4') objetitoRev.draw_solido(0.0,1.0,0.0);
			else if(figura=='5') palito.pintar(estirado, girado, rotado, 3);
			break;
		case 'c':
			if(figura=='1') cubito.draw_solido_ajedrez(1.0, 0.0, 0.0, 0.0, 1.0, 0.0);
			else if(figura=='2')piramidita.draw_solido_ajedrez(1.0, 0.0, 0.0, 0.0, 1.0, 0.0);
			else if(figura=='3') objetito.draw_solido_ajedrez(1.0,0.0,0.0,0.0,1.0,0.0);
			else if(figura=='4') objetitoRev.draw_solido_ajedrez(1.0,0.0,0.0,0.0,1.0,0.0);
			else if(figura=='5') palito.pintar(estirado, girado, rotado, 4);
			break;
		case 'w':
			if(figura=='1'){ 
				cubito.draw_aristas(0.0, 0.0, 0.0, 1.0);
				cubito.normalizarVectores();
				cubito.draw_normales_caras(0.0, 0.0, 0.0);
				cubito.draw_normales_vertices(0.0, 0.0, 0.0);
			}else if(figura=='2'){ 	
				piramidita.draw_aristas(0.0, 0.0, 0.0, 1.0);
				piramidita.normalizarVectores();
				piramidita.draw_normales_caras(0.0, 0.0, 0.0);
				piramidita.draw_normales_vertices(0.0, 0.0, 0.0);
			}else if(figura=='3'){ 
				objetito.draw_aristas(1.0,0.0,0.0,1.0);
				objetito.normalizarVectores();
				objetito.draw_normales_caras(0.0, 0.0, 0.0);
			}else if(figura=='4'){ 
				objetitoRev.draw_aristas(1.0,0.0,0.0,1.0);
				objetitoRev.normalizarVectores();
				objetitoRev.draw_normales_caras(0.0, 0.0, 0.0);
			}else if(figura=='5'){ 
				palito.pintar(estirado, girado, rotado, 2);
				palito.normalizarVectores();
				palito.draw_normales_caras(0.0, 0.0, 0.0);
			}
			break;
		case 'B':
		case 'b':
		case 'N':
		case 'n':
		case 'M':
		case 'm':
		case '.':
			if(figura=='5') palito.pintar(estirado, girado, rotado, 2);
			break;
	}

}


//**************************************************************************
//
//***************************************************************************

void draw_scene(void)
{

clear_window();
change_observer();
draw_axis();
draw_objects();
glutSwapBuffers();
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}


//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys(unsigned char Tecla1,int x,int y)
{

if (toupper(Tecla1)=='Q') exit(0);
else if (toupper(Tecla1)=='-') Observer_distance*=1.2;
else if (toupper(Tecla1)=='+') Observer_distance/=1.2;
else if (toupper(Tecla1)=='1') figura = '1';
else if (toupper(Tecla1)=='2') figura = '2';
else if (toupper(Tecla1)=='3') figura = '3';
else if (toupper(Tecla1)=='4') figura = '4';
else if (toupper(Tecla1)=='5') figura = '5';
else if (toupper(Tecla1)=='P') tecla = 'p';
else if (toupper(Tecla1)=='L') tecla = 'l';
else if (toupper(Tecla1)=='F') tecla = 'f';
else if (toupper(Tecla1)=='C') tecla = 'c';
else if (toupper(Tecla1)=='W') tecla = 'w';
else if (Tecla1=='Z'){ if(estirado<5) estirado++; }
else if (Tecla1=='z'){ if(estirado>1) estirado --; }
else if (Tecla1=='X'){ if(girado>-90) girado --; }
else if (Tecla1=='x'){ if(girado<90) girado ++; }
else if (Tecla1=='Y'){ if(rotado>-90) rotado --; }
else if (Tecla1=='y'){ if(rotado<90)  rotado++; }
else if (toupper(Tecla1)=='A') animado = !animado;
else if (Tecla1=='B') tecla = 'B';
else if (Tecla1=='b') tecla = 'b';
else if (Tecla1=='N') tecla = 'N';
else if (Tecla1=='n') tecla = 'n';
else if (Tecla1=='M') tecla = 'M';
else if (Tecla1=='m') tecla = 'm';

glutPostRedisplay();
}

void anima(){

	if(animado){

		if(tecla == 'B' && velociE<2) velociE++, tecla = '.';
		else if(tecla == 'b' && velociE>0) velociE--, tecla = '.';
		else if(tecla=='N' && velociG<10) velociG += 5, tecla = '.';
		else if(tecla=='n' && velociG>0) velociG -= 5, tecla = '.';
		else if(tecla=='M' && velociR<10) velociR += 5, tecla = '.';
		else if(tecla=='m' && velociR>0) velociR -= 5, tecla = '.';

		if(estirado < 6 && subiendo){
			estirado += velociE;
			if(estirado >= 6) subiendo = false;
		}
		else if(estirado > 1){
			estirado -= velociE;
			if(estirado <= 1) subiendo = true;
		}
		std::this_thread::sleep_for (std::chrono::milliseconds(50));

		if(girado < 90 && girando){
			girado = girado + velociG;
			if(girado >= 90) girando = false;
		}
		else if(girado > -90){
			girado = girado - velociG;
			if(girado <= -90) girando = true;
		}
		std::this_thread::sleep_for (std::chrono::milliseconds(50));

		if(rotado < 90 && rotando){
			rotado = rotado + velociR;
			if(rotado >= 90) rotando = false;
		}
		else if(rotado > -90){
			rotado = rotado - velociR;
			if(rotado <= -90) rotando = true;
		}
		std::this_thread::sleep_for (std::chrono::milliseconds(50));

	}

	glutPostRedisplay();

}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys(int Tecla1,int x,int y)
{

switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	//case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	//case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	}
glutPostRedisplay();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
// se inicalizan la ventana y los planos de corte
Window_width=5;
Window_height=5;
Front_plane=10;
Back_plane=1000;

// se inicia la posicion del observador, en el eje z
Observer_distance=2*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
//
change_projection();
//
glViewport(0,0,UI_window_width,UI_window_height);

_file_ply File_ply;

vector<_vertex3f> puntos;
vector<_vertex3i> triangulos;

File_ply.open("PLYs/peon.ply");
File_ply.read(puntos, triangulos);
File_ply.close();

objetitoRev = _modeloPlyRevolucion(puntos, 12);

}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{

// se llama a la inicialización de glut
glutInit(&argc, argv);

// se indica las caracteristicas que se desean para la visualización con OpenGL
// Las posibilidades son:
// GLUT_SIMPLE -> memoria de imagen simple
// GLUT_DOUBLE -> memoria de imagen doble
// GLUT_INDEX -> memoria de imagen con color indizado
// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
// GLUT_DEPTH -> memoria de profundidad o z-bufer
// GLUT_STENCIL -> memoria de estarcido
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

// posicion de la esquina inferior izquierdad de la ventana
glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(UI_window_width,UI_window_height);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("Práctica 2");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw_scene);
// asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "tecla_normal" al evento correspondiente
glutKeyboardFunc(normal_keys);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_keys);

glutIdleFunc(anima);

objetito.cargarPly("PLYs/big_dodge.ply");

// funcion de inicialización
initialize();

// inicio del bucle de eventos
glutMainLoop();
return 0;
}
