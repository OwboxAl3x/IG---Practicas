//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos.h"
#include <math.h>
#include <GLUT/glut.h>

//*************************************************************************
// clase punto
//*************************************************************************

_puntos3D::_puntos3D(){}

void _puntos3D::draw_puntos(float r, float g, float b, int grosor){

	glPointSize(grosor);
	glColor3f(r,g,b);
	glBegin(GL_POINTS);

	for(int i=0; i<vertices.size(); i++){

		glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);

	}
	glEnd();

}


//*************************************************************************
// clase triángulo
//*************************************************************************

_triangulos3D::_triangulos3D(){}

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor){

	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glPointSize(grosor);
	glColor3f(r,g,b);
	glBegin(GL_TRIANGLES);

	for(int i=0; i<caras.size(); i++){

		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);

	}

	glEnd();

}

void _triangulos3D::draw_solido(float r, float g, float b){

	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glColor3f(r,g,b);
	glBegin(GL_TRIANGLES);

	for(int i=0; i<caras.size(); i++){

		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);

	}

	glEnd();

}

void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2){

	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glBegin(GL_TRIANGLES);

	for(int i=0; i<caras.size(); i++){

		if(i%2==0){
			glColor3f(r1,g1,b1);
		}else{
			glColor3f(r2,g2,b2);
		}

		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);

	}

	glEnd();

}

float _triangulos3D::productoEscalar(const _vertex3f &a, const _vertex3f &b){

	float res;

	res = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);

	return res;

}

_vertex3f _triangulos3D::productoVectorial(const _vertex3f &a, const _vertex3f &b){

	_vertex3f res;

	res.x = (a.y * b.z - a.z * b.y);
	res.y = -(a.x * b.z - a.z * b.x);
	res.x = (a.x * b.y - a.y * b.x);

	return res;

}

void _triangulos3D::normalizar(_vertex3f &v){

	float modulo = sqrt(productoEscalar(v, v));

	v.x = v.x / modulo;
	v.y = v.y / modulo;
	v.z = v.z / modulo;

}

void _triangulos3D::draw_normales_caras(float r, float g, float b){

	_vertex3f v1, v2, v3, promedio, aux;

	glColor3f(r, g, b);
	glShadeModel(GL_FLAT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_LINES);

		for(int i=0; i<caras.size(); i++){

			v1 = vertices[caras[i].x];
			v2 = vertices[caras[i].y];
			v3 = vertices[caras[i].z];

			promedio.x = (v1.x + v2.x + v3.x) / 3.0;
			promedio.y = (v1.y + v2.y + v3.y) / 3.0;
			promedio.z = (v1.z + v2.z + v3.z) / 3.0;

			aux = caras_normalizadas[i] + promedio;

			glVertex3f(promedio.x, promedio.y, promedio.z);
			glVertex3f(aux.x, aux.y, aux.z);

		}

	glEnd();

}

void _triangulos3D::draw_normales_vertices(float r, float g, float b){

	_vertex3f aux;

	glColor3f(r, g, b);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_LINES);

		for(int i=0; i<vertices.size(); i++){

			aux = vertices_normalizados[i] + vertices[i];

			glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
			glVertex3f(aux.x, aux.y, aux.z);

		}

	glEnd();

}

void _triangulos3D::normalizarVectorCaras(){

	_vertex3f p, q, tri1, tri2, tri3, res;

	for(int i=0; i<caras.size(); i++){

		tri1 = vertices[caras[i].x];
		tri2 = vertices[caras[i].y];
		tri3 = vertices[caras[i].z];

		p.x = (tri2.x - tri1.x);
		p.y = (tri2.y - tri1.y);
		p.z = (tri2.z - tri1.z);

		q.x = (tri3.x - tri1.x);
		q.y = (tri3.y - tri1.y);
		q.z = (tri3.z - tri1.z);

		res = productoVectorial(p, q);

		normalizar(res);

		caras_normalizadas.push_back(res);

	}

}

void _triangulos3D::normalizarVectorVertices(){

	int tri1, tri2, tri3;

	vertices_normalizados.resize(vertices.size());

	for(int i=0; i<caras.size(); i++){

		tri1=caras[i].x;
		tri2=caras[i].y;
		tri3=caras[i].z;

		vertices_normalizados[tri1] = vertices_normalizados[tri1] + caras_normalizadas[i];
		vertices_normalizados[tri2] = vertices_normalizados[tri2] + caras_normalizadas[i];
		vertices_normalizados[tri3] = vertices_normalizados[tri3] + caras_normalizadas[i];

	}

	for(int i=0; i<vertices_normalizados.size(); i++)
		normalizar(vertices_normalizados[i]);

}

void _triangulos3D::normalizarVectores(){

	normalizarVectorCaras();
	normalizarVectorVertices();

}


//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam){

	_vertex3f v0, v1, v2, v3, v4, v5, v6, v7;

	v0.x = -0.5; v0.y = -0.5; v0.z = -0.5;
	v1.x = tam/2; v1.y = -0.5; v1.z = -0.5;
	v2.x = -0.5; v2.y = tam/2; v2.z = -0.5;
	v3.x = tam/2; v3.y = tam/2; v3.z = -0.5;
	v4.x = -0.5; v4.y = tam/2; v4.z = tam/2;
	v5.x = tam/2; v5.y = tam/2; v5.z = tam/2;
	v6.x = -0.5; v6.y = -0.5; v6.z = tam/2;
	v7.x = tam/2; v7.y = -0.5; v7.z = tam/2;

	vertices.push_back(v0);
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);
	vertices.push_back(v4);
	vertices.push_back(v5);
	vertices.push_back(v6);
	vertices.push_back(v7);

	_vertex3i c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11;

	c0.x = 2; c0.y = 1; c0.z = 0;
	c1.x = 2; c1.y = 3; c1.z = 1;
	c2.x = 3; c2.y = 5; c2.z = 1;
	c3.x = 5; c3.y = 7; c3.z = 1;
	c4.x = 7; c4.y = 5; c4.z = 6;
	c5.x = 5; c5.y = 4; c5.z = 6;
	c6.x = 6; c6.y = 4; c6.z = 0;
	c7.x = 2; c7.y = 0; c7.z = 4;
	c8.x = 2; c8.y = 4; c8.z = 5;
	c9.x = 2; c9.y = 5; c9.z = 3;
	c10.x = 7; c10.y = 6; c10.z = 0;
	c11.x = 1; c11.y = 7; c11.z = 0;

	caras.push_back(c0);
	caras.push_back(c1);
	caras.push_back(c2);
	caras.push_back(c3);
	caras.push_back(c4);
	caras.push_back(c5);
	caras.push_back(c6);
	caras.push_back(c7);
	caras.push_back(c8);
	caras.push_back(c9);
	caras.push_back(c10);
	caras.push_back(c11);

}


//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al){

	_vertex3f v0, v1, v2, v3, v4;

	// altBase es la altura del triangulo de base
	float altBase = sqrt(pow(tam, 2)-pow(tam/2, 2));

	// rCirculo es el radio de la circunferencia que pasa por todos los vertices del triangulo de la base
	float rCirculo = 2*altBase/3;

	// cenBase es el centro del triangulo de la base equidistante de sis tres vertices
	float cenBase = sqrt(pow(rCirculo, 2)-pow((tam/2), 2));

	v0.x = 0.0; v0.y = 0.0; v0.z = 0.0;
	v1.x = tam/2; v1.y = 0.0; v1.z = altBase;
	v2.x = tam; v2.y = 0.0; v2.z = 0.0;
	v3.x = tam/2; v3.y = al; v3.z = cenBase;

	vertices.push_back(v0);
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);

	_vertex3i c0, c1, c2, c3, c4, c5;

	c0.x = 0; c0.y = 1; c0.z = 2;
	c1.x = 0; c1.y = 3; c1.z = 1;
	c2.x = 1; c2.y = 3; c2.z = 2;
	c3.x = 0; c3.y = 3; c3.z = 2;

	caras.push_back(c0);
	caras.push_back(c1);
	caras.push_back(c2);
	caras.push_back(c3);

}


//*************************************************************************
// clase PLY
//*************************************************************************

_modeloPly::_modeloPly(){}

void _modeloPly::cargarPly (string nombre){

	_file_ply File_ply;

	vector<_vertex3f> puntos;
	vector<_vertex3i> triangulos;
	_vertex3f v;
	_vertex3i c;

	int i;

	File_ply.open(nombre);
	File_ply.read(puntos, triangulos);

	for (i = 0; i < puntos.size(); i++){
		v.x = puntos[i].x;
		v.y = puntos[i].y;
		v.z = puntos[i].z;
		vertices.push_back(v);
	}

	for (i = 0; i < triangulos.size(); i++){
		c.x = triangulos[i].x;
		c.y = triangulos[i].y;
		c.z = triangulos[i].z;

		caras.push_back(c);
	}

	File_ply.close();

}


//*************************************************************************
// clase revolucion
//*************************************************************************

_modeloPlyRevolucion::_modeloPlyRevolucion(){}

_modeloPlyRevolucion::_modeloPlyRevolucion(vector<_vertex3f> perfil, int lados){

	bool tapaArriba = false;
	bool tapaAbajo = false;
	_vertex3f verticeArriba;
	_vertex3f verticeAbajo;

	if(perfil.back().x == 0){

		tapaArriba = false;

	}else{

		tapaArriba = true;
		verticeArriba.x = 0;
		verticeArriba.y = perfil.back().y;
		verticeArriba.z = 0;

	}

	if(perfil[0].x == 0) {

		tapaAbajo = false;

	}else{

		tapaAbajo = true;
		verticeAbajo.x = 0;
		verticeAbajo.y = perfil[0].y;
		verticeAbajo.z = 0;

	}

	revolution(perfil, lados);

	if(tapaAbajo){

		vertices.push_back(verticeAbajo);

		for(int i = 0; i < vertices.size() - perfil.size(); i = i + perfil.size()){

			_vertex3i c;

			c.x = i + perfil.size();
			c.y = i;
			c.z = vertices.size() - 1;

			caras.push_back(c);

		}

	}

	if(tapaArriba){

		vertices.push_back(verticeArriba);

		for(int i = perfil.size() - 1; i < vertices.size() - perfil.size(); i = i + perfil.size()){

			_vertex3i c;

			c.x = i + perfil.size();
			c.y = i;
			c.z = vertices.size() - 1;

			caras.push_back(c);

		}

	}

}

void _modeloPlyRevolucion::revolution(vector<_vertex3f> perfil, int lados){

	vertices.clear();
	caras.clear();
	vertices = perfil; //Metemos en vertices lo leidos desde peon.ply

	double angulo = pasoRadianes(360.0 / lados);

	vertices.resize(perfil.size() * (lados + 1));
	int k = perfil.size();

	for(int i = 0; i < lados; i++){

		perfil[0] = rotar(perfil[0], angulo);
		vertices[k++] = perfil[0];

		for(int j = 1; j < perfil.size(); j++){

			perfil[j] = rotar(perfil[j], angulo);
			vertices[k] = perfil[j];

			_vertex3i c;

			c.x = k;
			c.y = k - perfil.size();
			c.z = k - perfil.size() - 1;

			caras.push_back(c);

			c.x = k;
			c.y = k - perfil.size() - 1;
			c.z = k - 1;

			caras.push_back(c);

			k++;

		}

	}

}

double _modeloPlyRevolucion::pasoRadianes(double grados){

	return grados * 3.14159 / 180;

}

_vertex3f _modeloPlyRevolucion::rotar(_vertex3f puntoAnt, float angulo){

	//Funcion para rotar cada punto segun el anterior
	_vertex3f puntoSig;
	puntoSig.x = cos(angulo)*puntoAnt.x + sin(angulo)*puntoAnt.z;
	puntoSig.y = puntoAnt.y;
	puntoSig.z = -sin(angulo)*puntoAnt.x + cos(angulo)*puntoAnt.z;

	return puntoSig;

}


//*************************************************************************
// clase Selfie
//*************************************************************************

_paloSelfie::_paloSelfie(){


}

void _paloSelfie::pintar(float e, float g, float r, int modo){

	//GLUquadricObj *obj = gluNewQuadric();
	//glutSolidSphere(0.5, 20, 20);
	//gluCylinder(obj, 1.0, 1, 3, 30, 30);

	glPushMatrix();

		glPushMatrix();

			glTranslatef(0.0, 2.0, 0.0);

			glRotatef(g, 0.0, 1.0, 0.0);

			glTranslatef(0.0, 0.5*e, 0.0);

			glPushMatrix();

				glTranslatef(0.0, 0.5*e, 0.0);

				glRotatef(r, 1.0 ,0.0, 0.0);

				glTranslatef(0.0, 0.25, 0.0);

				glPushMatrix();

					glTranslatef(0.0, 1.25, 0.0);

					glScalef(3.0, 2.0, 0.5);

					if(modo == 1){
						cubito.draw_puntos(0.0, 0.0, 0.0, 3.0);
					}else if(modo == 2){
						cubito.draw_aristas(0.0, 0.0, 0.0, 1.0);
					}else if(modo == 3){
						cubito.draw_solido(1.0, 0.0, 0.0);
					}else if(modo == 4){
						cubito.draw_solido_ajedrez(1.0, 0.0, 0.0, 0.0, 1.0, 0.0);
					}

				glPopMatrix();

				glPushMatrix();

					glScalef(0.5, 0.5, 0.5);

					if(modo == 1){
						cubito.draw_puntos(0.0, 0.0, 0.0, 3.0);
					}else if(modo == 2){
						cubito.draw_aristas(0.0, 0.0, 0.0, 1.0);
					}else if(modo == 3){
						cubito.draw_solido(1.0, 0.0, 0.0);
					}else if(modo == 4){
						cubito.draw_solido_ajedrez(1.0, 0.0, 0.0, 0.0, 1.0, 0.0);
					}

				glPopMatrix();

			glPopMatrix();

			glPushMatrix();

				glScalef(0.25, 1.0*e, 0.25);

				if(modo == 1){
					cubito.draw_puntos(0.0, 0.0, 0.0, 3.0);
				}else if(modo == 2){
					cubito.draw_aristas(0.0, 0.0, 0.0, 1.0);
				}else if(modo == 3){
					cubito.draw_solido(1.0, 0.0, 0.0);
				}else if(modo == 4){
					cubito.draw_solido_ajedrez(1.0, 0.0, 0.0, 0.0, 1.0, 0.0);
				}

			glPopMatrix();

		glPopMatrix();

		glPushMatrix();

			glScalef(0.5, 4.0, 0.5);

			if(modo == 1){
				cubito.draw_puntos(0.0, 0.0, 0.0, 3.0);
			}else if(modo == 2){
				cubito.draw_aristas(0.0, 0.0, 0.0, 1.0);
			}else if(modo == 3){
				cubito.draw_solido(1.0, 0.0, 0.0);
			}else if(modo == 4){
				cubito.draw_solido_ajedrez(1.0, 0.0, 0.0, 0.0, 1.0, 0.0);
			}

		glPopMatrix();

	glPopMatrix();

}
