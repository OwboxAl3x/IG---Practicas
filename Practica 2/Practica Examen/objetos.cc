//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos.h"
#include <math.h>

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


//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam){

	_vertex3f v0, v1, v2, v3, v4, v5, v6, v7;

	v0.x = 0.0; v0.y = 0.0; v0.z = 0.0;
	v1.x = 0.0; v1.y = tam; v1.z = 0.0;
	v2.x = 0.0; v2.y = tam; v2.z = tam;
	v3.x = 0.0; v3.y = 0.0; v3.z = tam;
	v4.x = tam; v4.y = 0.0; v4.z = tam;
	v5.x = tam; v5.y = 0.0; v5.z = 0.0;
	v6.x = tam; v6.y = tam; v6.z = 0.0;
	v7.x = tam; v7.y = tam; v7.z = tam;

	vertices.push_back(v0);
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);
	vertices.push_back(v4);
	vertices.push_back(v5);
	vertices.push_back(v6);
	vertices.push_back(v7);

	_vertex3i c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11;

	c0.x = 1; c0.y = 0; c0.z = 3;
	c1.x = 1; c1.y = 2; c1.z = 3;
	c2.x = 3; c2.y = 2; c2.z = 4;
	c3.x = 7; c3.y = 2; c3.z = 4;
	c4.x = 7; c4.y = 4; c4.z = 5;
	c5.x = 7; c5.y = 6; c5.z = 5;
	c6.x = 0; c6.y = 5; c6.z = 6;
	c7.x = 0; c7.y = 1; c7.z = 6;
	c8.x = 1; c8.y = 6; c8.z = 7;
	c9.x = 1; c9.y = 2; c9.z = 7;
	c10.x = 3; c10.y = 5; c10.z = 4;
	c11.x = 3; c11.y = 5; c11.z = 0;

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

		for(int i = perfil.size() - 1; i < vertices.size()/2 - perfil.size(); i = i + perfil.size()){

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
	vertices = perfil; //Metemos en vertices lo leidos desde peonza.ply

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

			if(i % 2== 0 && vertices[k].y>=0.0 && vertices[k-perfil.size()].y>=0.0 && vertices[k - perfil.size() - 1].y>=0.0  && vertices[k-1].y>=0.0){

				c.x = k;
				c.y = k - perfil.size();
				c.z = k - perfil.size() - 1;


				caras.push_back(c);


				c.x = k;
				c.y = k - perfil.size() - 1;
				c.z = k - 1;

				caras.push_back(c);

			}

			if(i % 2!=0 && vertices[k].y<=0.0 && vertices[k-perfil.size()].y<=0.0 && vertices[k - perfil.size() - 1].y<=0.0  && vertices[k-1].y<=0.0){

				c.x = k;
				c.y = k - perfil.size();
				c.z = k - perfil.size() - 1;

				caras.push_back(c);

				c.x = k;
				c.y = k - perfil.size() - 1;
				c.z = k - 1;

				caras.push_back(c);

			}

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
