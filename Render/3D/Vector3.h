#pragma once

#include "Vector.h"
#include <math.h>
#include <string>
class Vector3:public Vector{
	public:
		Vector3():z(0){}
		Vector3(double p1,double p2,double p3){this->x=p1;this->y=p2;this->z=p3;}
		Vector3(double p1,double p2){this->x=p1;this->y=p2;this->z=0;}
		Vector3(double p1){this->x=p1;this->y=0;this->z=0;}
		Vector3(Vector *c){this->x=c->x;this->y=c->y;this->z=0;}
		Vector3(Vector3 *c){this->x=c->x;this->y=c->y;this->z=c->z;}
		void operator ++(){
			this->x++;
			this->y++;
			this->z++;
			return;
		}
		void operator --(){
			this->x--;
			this->y--;
			this->z--;
			return;
		}
		Vector3 get(){return Vector3(this->x,this->y,this->z);}
		double mag(){return sqrt(this->x*this->x + this->y*this->y + this->z*this->z);}
		void add(double p1,double p2,double p3){this->x += p1;this->y += p2;this->z += p3;}
		void add(Vector3 *v3){this->x += v3->x;this->y += v3->y;this->z += v3->z;}
		void sub(double p1,double p2,double p3){this->x -= p1;this->y -= p2;this->z -= p3;}
		void sub(Vector3 *v3){this->x -= v3->x;this->y -= v3->y;this->z -= v3->z;}
		void mult(Vector3 *v3){this->x *= v3->x;this->y *= v3->y;this->z *= v3->z;}
		void mult(double v3){this->x *= v3;this->y *= v3;this->z *= v3;}
		void div(Vector3 *v3){this->x /= v3->x;this->y /= v3->y;this->z /= v3->z;}
		void div(double v3){this->x /= v3;this->y /= v3;this->z /= v3;}
		double distance(Vector3 *v3){
			double dx = this->x - v3->x,
				dy = this->y - v3->y,
				dz = this->z - v3->z;
			return sqrt(dx*dx + dy*dy + dz*dz);
		}
		double dot(double v1,double v2,double v3){
			return (this->x*v1 + this->y*v2 + this->z*v3);
		}
		double dot(Vector3 *v){
			return (this->x*v->x + this->y*v->y + this->z*v->z);
		}
		Vector3 cross(Vector3 v){
			return Vector3(this->y*v.z - v.y*this->z,
				this->z*v.x - v.z*this->x,
				this->x*v.y - v.x*this->y);
		}
		void normalize(){
			double m = this->mag();
			if( m>0 )
				this->div(m);
		}
		void limit(double highV){
			if(this->mag() > highV){
				this->normalize();
				this->mult(highV);
			}
		}
		/*const char * toString(){
			return "[ "+x+", "+y+", "+z+" ]";
		}*/
		static double dot(Vector3 *v,Vector3 *w){
			return (w->x*v->x + w->y*v->y + w->z*v->z);
		}
		static Vector3 mult(Vector3 *v,double w){
			Vector3 e= Vector3(v->x, v->y, v->z);
			e.x *= w;
			e.y *= w;
			e.z *= w;
			return e;
		}
		double z;
};
