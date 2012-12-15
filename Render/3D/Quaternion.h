#ifndef _QU_
#define _QU_

#include "Vector3.h"
#include <exception>
class Quaternion{
	Vector3 * u;
	double x;
public:
	~Quaternion(){
		if(u!=0){
			delete u;
			u = 0;
		}
	}
	Quaternion(){u = 0;}
	Quaternion(double x,double y,double z,double w){
		this->u= new Vector3(x,y,z);
		set(w);
	}
	Quaternion(double w,Vector3 v){
		this->u = new Vector3(v.x, v.y, v.z);
		set(w);
	}
	
	void set(Quaternion *d){
		set(d->x);
		set(d->u);
	}
	void set(double x,double y,double z,double w){
		set(x,y,z);
		set(w);
	}
	void set(double w, Vector3 v){
		set(w);
		set(v);
	}
	void set(double w=0){
		this->x = w;
	}
	void set(Vector3 v){
		if(u == 0)
			this->u = new Vector3(v.x, v.y, v.z);
		else{
			this->u->x = v.x;
			this->u->y = v.y;
			this->u->z = v.z;
		}
	}
	void set(double x, double y, double z){
		if(u == 0)
			this->u = new Vector3(x, y, z);
		else{
			this->u->x = x;
			this->u->y = y;
			this->u->z = z;
		}
	}

	void mult(Quaternion *q, Quaternion * res){
		double z = this->x*q->x - this->u->dot(q->u);
		res->x = z;
		res->set(this->u->cross(q->u));
		Vector3 vt = Vector3::mult(q->u,this->x);
		res->u->add(&vt);
		vt = Vector3::mult(this->u,q->x);
		res->u->add(&vt);
	}

	void scalarMult(double s, Quaternion *res){
		res->set(
			this->u->x*s,
			this->u->y*s,
			this->u->z*s,
			this->x*s);
	}/*
	void set(double d, Vector3 *v){
		this->x=d;
		this->u = v;
	}*/
	double angle(){return 2.0*acos(this->x);};
	void power(double p, Quaternion *res){
		double t=acos(this->x);
		t *= p;
		Vector3 U= Vector3(this->u->x,this->u->y,this->u->z);
		U.normalize();
		U.mult(sin(t));
		res->set(cos(t), U);
	}
	void copy(Quaternion *res){
		res->set(this->x, *(this->u));
	}
	void inverse(Quaternion *res){
		double L = this->x*this->x + this->u->dot(this->u);
		double z = this->x/L;
		Vector3 w = Vector3(-this->u->x/L,-this->u->y/L,-this->u->z/L);
		res->set(z,w);
	}
	void conjugate(Quaternion *q, Quaternion *res){
		Quaternion qt, qti;
		q->inverse(&qti);		// set qti to the innvers quater
		q->mult(this, &qt);		// set multiplied quater to qt
		qt.mult(&qti, res);		// save result in res
	}
	void rotatePoint(Vector3 v, Vector3 *res){
		Quaternion *a = new Quaternion(v.x, v.y, v.z, 0);
		Quaternion r;
		a->conjugate(this, &r);
		//delete a;
		res->x = r.u->x;
		res->y = r.u->y;
		res->z = r.u->z;
	}
	void normalize(Quaternion *res){
		double s = 1/sqrt(
			this->x*this->x + 
			this->u->x*this->u->x + 
			this->u->y*this->u->y + 
			this->u->z*this->u->z
		);
		Vector3 v=this->u->get();
		v.mult(s);
		res->set(this->x*s, v);
	}
	double length(){return sqrt(this->u->dot(this->u) +this->x*this->x);}
};
#endif
