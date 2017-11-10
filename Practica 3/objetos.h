//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#include <vector>
#include "vertex.h"
#include <stdlib.h>
#include "file_ply_stl.h"

using namespace std;

const float AXIS_SIZE=5000;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
	public:


			_puntos3D();
		void 	draw_puntos(float r, float g, float b, int grosor);

		vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
	public:

			_triangulos3D();
		void 	draw_aristas(float r, float g, float b, int grosor);
		void    draw_solido(float r, float g, float b);
		void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);

		vector<_vertex3i> caras;

};


//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
	public:

		_cubo(float tam=1);

};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
	public:

		_piramide(float tam=0.5, float al=0.75);

};


//*************************************************************************
// clase PLY
//*************************************************************************
class _modeloPly: public _triangulos3D
{

	public:

		_modeloPly();
		void cargarPly (string nombre);

};

class _modeloPlyRevolucion: public _modeloPly
{

    public:

        _modeloPlyRevolucion();
				_modeloPlyRevolucion(vector<_vertex3f> perfil, int lados);
        void revolution(vector<_vertex3f> perfil, int lados);

        double pasoRadianes(double grados);
        _vertex3f rotar(_vertex3f y, float angulo);

};


//*************************************************************************
// clase Selfie
//*************************************************************************

class _paloSelfie: public _triangulos3D
{

	private:

		_cubo cubito;

	public:

		_paloSelfie();
		void pintar(float e, float g, float r, int modo);

};
