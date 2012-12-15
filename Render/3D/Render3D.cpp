#include "Render3D.h"
#ifndef _WIN32
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#endif
namespace SR3D{
	
	using namespace SR;
	Render3D::Render3D() {
	#ifdef TIOCGSIZE
		struct ttysize ts;
		ioctl(STDIN_FILENO, TIOCGSIZE, &ts);
		width = ts.ts_cols;
		height = ts.ts_lines;
	#elif defined(TIOCGWINSZ)
		struct winsize ts;
		ioctl(STDIN_FILENO, TIOCGWINSZ, &ts);
		width = ts.ws_col;
		height = ts.ws_row;
	#else
		console = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO csbi;
	
	
		//SetConsoleDisplayMode(console, CONSOLE_FULLSCREEN_MODE, NULL);
		//SetWindowLong(GetConsoleWindow(), 0, WS_EX_WINDOWEDGE);

		GetConsoleScreenBufferInfo(console, &csbi);
		width = 1 + csbi.srWindow.Right - csbi.srWindow.Left;
		height = csbi.srWindow.Bottom - csbi.srWindow.Top;
	#endif /* TIOCGSIZE */

		// reading console screen
		dwBufferSize.X = width;
		dwBufferSize.Y = height; 
		dwBufferCoord.X = 0;
		dwBufferCoord.Y = 0; 
		rcRegion.Left = 0;
		rcRegion.Right = width-1;
		rcRegion.Top = 0;
		rcRegion.Bottom = height-1; 

		//ReadConsoleOutput( console, (PCHAR_INFO)buffer, dwBufferSize, dwBufferCoord, &rcRegion ); 
		PIX color;
		color.Char.AsciiChar = ' ';
		color.Attributes = BLACK;
		
		buffer = new PIX*[height];
		for(int i=0;i<height;i++)
			buffer[i] = new PIX[width];

		for(int i=0;i<height;i++)
			for(int j=0;j<width;j++){
				buffer[i][j].Char.UnicodeChar = ' ';
				buffer[i][j].Attributes = YELLOW;
			}
		rotation = new Quaternion(-90, Vector3(-45,45/2,-45));
	}
	
	int Render3D::addFace(Face *f){
		return scene.addFace(f);
	}

	int Render3D::addPoint(Vertex *v){
		return scene.addPoint(v);
	}

	int Render3D::setPixel(int x, int y, double z, PIX *c){

		int r = ScreenRender::setPixel(x,y,c);
		if( r != -1 )
			buffer[y][x].z = z;
		return r;
	}

	int Render3D::render(){
		clearScreen();
		PIX p;

		Index size = scene.getFacesLength();
		Quaternion invr;
		rotation->inverse(&invr);

		for(Index i=0; i< size; i++){
			p.Attributes = BLACK;//min(max(17*(rand()%16),0x11),0xFF);
			p.Char.AsciiChar = 'A';
			
			Index fSize = scene.getFaceLength(i);
			Index x,y;
			if(fSize > 1){
				Index l = scene.getFaceLength(i);
				Face f,pf;
				for(Index j=0; j < l; j++){
					Vertex v = scene.getVertex(scene.getIndex(i, j));
					Vector3 v1r;
					rotation->rotatePoint(v, &v1r);
					f.push_back(v1r);
					Vector3 v1p = project(&v1r);
					v1p.x = (int)v1p.x + width/2;
					if (useRelativePositins)
						v1p.y = (int)(v1p.y*rel) + height/2;
					else
						v1p.y = (int)v1p.y;
					pf.push_back(v1p);
				}
				Vector3 v1=Vector3(f.at(1));
				v1.sub(&(f.at(0)));				//V1
				Vector3 v2=Vector3(f.at(2));
				v2.sub(&(f.at(0)));				//V2
				Vector3 n=v1.cross(v2);			// a, b, c
				// normal calc: www.cecs.csulb.edu/~pnguyen/cecs449/lectures/fillalgorithm.pdf+&hl=sv&gl=se&pid=bl&srcid=ADGEESijDi57JqWU3CxepGfk-XDJPxgr8nE2RpJLplt8YtOodrWnbSGTTRwArTcQGsu1Yo-S9fmwVRxzXOaYI1OiD_i1_ZKB4QCi97nIaP5krIWvrgaBDuw6F7NSlUtMQt23fv8x3Q4Y&sig=AHIEtbRwci8M6UTTLWMNWY6IiFI76nFO3Q
				// polyfill, scan-line: www.cs.rit.edu/~icss571/filling/
				//						www.alienryderflex.com/polygon/
				for(int j=0;j < height; j++){
					for(int k=0;k < width; k++){
						if(pointInFace(pf, k, j) && inBoundary(k,j) ){// && getPixel(x,y)->z < v1p.z){
							Vertex fl = f.at(0);
							Vertex testpoint = Vertex(k,j, 0);
							Vertex testpointCenter = Vector3((fl.x + v1.x + v2.x)/3,(fl.y + v1.y + v2.y)/3, (fl.z + v1.z + v2.z)/3);
							Quaternion test;
							Vector3 from = Vector3(0,0,1), H = Vector3(n);
							//H.add(&n);
							//from.normalize();
							
							H.normalize();
							test.set( // BUGG!!
								from.y*H.z - from.z*H.y, 
								from.z*H.x - from.x*H.z,
								from.x*H.y - from.y*H.z,
								from.dot(&H));
							rotation->inverse(&test);
							test.rotatePoint(testpoint, &testpoint);
							double konst = n.x*fl.x + n.y*fl.y + n.z*fl.z; // ax + by + cz = konst
							double z = (konst - n.x*testpoint.x - n.y*testpoint.y )/n.z; // z = (konst - ax - by)/c
							/*Line l = {
								Vector3(0,0,1),
								Vector3(k,j,500)
							};
							invr.rotatePoint(l[1], &(l[1]));
							double denom = l[0].dot(&n);
							Vector3 fnum = Vector3(f.at(0));
							invr.rotatePoint(fnum, &fnum);
							fnum.sub(&(l[1]));*/
							double num = z;//fnum.dot(&n);
							if( inBoundary(k,j) && (getPixel(k,j)->z < num ))
								setPixel(k, j, num, scene.getColor(i));
							
						}
					}
				}
				
				/*p.Attributes = 0xFF;
				p.Char.AsciiChar = 'A';
				for(Index j=0; j < l; j++){
					Vertex vp = pf.at(j);
					if(inBoundary((int)vp.x, (int)vp.y) )
						setPixel((int)vp.x, (int)vp.y, (int)vp.z, &p);
				}*/
			}
			else{
				for(Index j=0; j< fSize; j++){
					Index vi = scene.getIndex(i,j);
					Vector3 v1r;
					rotation->rotatePoint(scene.getVertex(vi), &v1r);
					Vector3 v1p = project(&v1r);
					x = (int)v1p.x + width/2;
					if (useRelativePositins)
						y = (int)(v1p.y*rel) + height/2;
					else
						y = (int)v1p.y;
					if( inBoundary(x,y) )// && getPixel(x,y)->z < v1p.z )
						setPixel(x, y, v1p.z, &p);
				}
			}
		}
		return ScreenRender::render();
	}
	bool Render3D::pointInFace(Face f, double x, double y) {
		Index i, j=f.size()-1;
		bool oddNodes=false;

		for (i=0; i<f.size(); i++) {
			if ((f.at(i).y< y && f.at(j).y >= y
				||   f.at(j).y < y && f.at(i).y >= y)
				&&  (f.at(i).x <= x || f.at(j).x <= x)) {
					if (f[i].x+(y-f[i].y)/(f[j].y-f[i].y)*(f[j].x-f[i].x)<x)
						oddNodes=!oddNodes;
			}
			j=i;
		}

		return oddNodes; 
	}

	Vector3 Render3D::project(Vector3 *v){
		double x,y,z;
		x = v->x * 500/(500-v->z);
		y = v->y * 500/(500-v->z);
		z = v->z;
		return Vector3(x,y,z);
	}
	void Render3D::rotateView(double d, Vector &a){
		//rotation->
	}

	Render3D::~Render3D() {
		delete rotation;
		for(int i=0; i< height; i++)
			delete [] buffer[i];
		delete []buffer;
	}
};
