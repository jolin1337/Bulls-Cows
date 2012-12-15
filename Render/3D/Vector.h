#pragma once

class Vector{
	public:
		double x,y;
		Vector():x(0),y(0){}
		Vector(double p1,double p2){this->x=p1;this->y=p2;}
		Vector(double p1){this->x=p1;this->y=0;}
		void operator ++(){
			this->x++;
			this->y++;
			return;
		}
		void operator --(){
			this->x--;
			this->y--;
			return;
		}
	protected:
};