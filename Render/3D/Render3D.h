#ifndef _SR3D_
#define _SR3D_

#ifdef _WIN32
#include <Windows.h>
#endif
#include "../ScreenRender.h"
#include "Quaternion.h"
namespace SR3D{
	using SR::ScreenRender;
	using std::vector;
	

	typedef Vector3 Vertex;//class{Vector3 position;} Vertex;

	typedef Vertex Line[2];

	typedef unsigned int Index;

	typedef Vertex Face4[4];
	typedef vector<Index > FaceIndex;
	typedef vector<Vertex > Face;

	typedef struct _PIX : SR::PIX { 
		double z;
	} PIX, *PPIX;
	//PIX **buffer;

	class Scene{
		vector<Vertex > vertices;
		vector<FaceIndex > indices;
		vector<PIX > colors;
	public:
		int addPoint(Vertex *v, PIX *c = 0){
			vertices.push_back(*v);
			FaceIndex face;
			face.push_back(vertices.size()-1);// index for previous added vertex = *v
			indices.push_back(face);
			if(c)
				colors.push_back(*c);
			else{
				PIX col;
				col.Attributes = BLACK;//min(max(17*(rand()%16),0x11),0xFF);
				colors.push_back(col);
			}
			return 0;
		}

		int addFace(Face *f, PIX * c = 0){
			FaceIndex face;
			for(Index i=0;i<f->size();i++){
				vertices.push_back(f->at(i));
				face.push_back(vertices.size()-1);
			}
			indices.push_back(face);
			if(c)
				colors.push_back(*c);
			else{
				PIX col;
				col.Attributes = BLACK;//min(max(17*(rand()%16),0x11),0xFF);
				colors.push_back(col);
			}
			return 0;
		}

		Vertex getVertex(Index i){
			if(vertices.size() > i && i >= 0)
				return vertices.at(i);
			else
				return vertices.at(0);
		}
		Index getIndex(Index c, Index i){
			return indices.at(c).at(i);
		}
		Face getFace(Index index){
			Index l = indices.at(index).size();
			Face res;
			for(Index i=0; i < l; i++)
				res.push_back(getIndex(index, i));
			return res;
		}

		Index getFacesLength(){
			return indices.size();
		}
		Index getFaceLength(Index i){
			return indices.at(i).size();
		}
		PIX *getColor(Index i){
			return &(colors.at(i));
		}
	};

	class Render3D : public ScreenRender {
		Scene scene;
		PIX **buffer;
	public:
		Render3D();

		int setPixel(int x, int y, double z, PIX *c);
		PIX *getPixel(int x, int y){
			if(!inBoundary(x,y))
				return NULL;
			return &(buffer[y][x]);
		}

		int render();
		bool pointInFace(Face f, double x, double y);
		int addPoint(Vertex *v);
		int addFace(Face *f);
		void rotateView(double d, Vector &a);
		int printString3D(Vertex v, const char*, int color= -1);
		Vector3 project(Vector3 *v);
	#ifdef _WIN32
	private:
		HANDLE console;
		COORD dwBufferSize;
		COORD dwBufferCoord;
		SMALL_RECT rcRegion;
	public:
	#endif
		Quaternion *rotation;
		~Render3D();
	};
};

#endif
