#pragma once
#include <vector>
using namespace std;
class Cube{
public:
	int color;
	Vector3 *position;
	vector<vector<int> > faces;
	vector<Vector3 * >vertices;
	Cube(double x,double y,double z,double size,int color){
		unsigned int f[6][4]={0,4,6,2, 1,3,7,5, 0,1,5,4, 2,6,7,3, 0,2,3,1, 4,5,7,6};
		this->position=new Vector3(x,y,z);
		this->faces.resize(6);
		for(int i=0;i<6;i++){
			this->faces[i].resize(4);
			for(int j=0;j<4;j++)
				this->faces[i][j]=(f[i][j]);
		}
		for(int i=0;i<8;i++){
			Vector3 *t=new Vector3(0,0,0);
			t->x=this->position->y+this->getBit(i,0)*(size/2);
			t->y=this->position->y+this->getBit(i,1)*(size/2);
			t->z=this->position->z+this->getBit(i,2)*(size/2);
			this->vertices.push_back(t);
		}
		this->color=color;
	}
	int getBit(int n,int i){
			int a= ((n >> i) & 1);
			if(!a)return -1;
			return 1;
	}
	Cube(Vector3 *v,double size,int color){

	}
	vector<Vector3 *>getFace(int i, vector<Vector3 *> vert){
		vector<Vector3 *> ans;
		ans.resize(4);
		for(int j =0;j<4;j++){
			int l=this->faces[i][j];
			if(0){
				ans[j]=this->vertices[l];
			}
			else
				ans[j]=vert[l];
		}
		return ans;
	}
	vector<vector<Vector3 * > >getPolygon(vector<Vector3 *> vert){
		vector<vector<Vector3 * > > ans;
		ans.resize(6);
		for(int i=0;i<6;i++){
			ans[i]=this->getFace(i,vert);
		}
		return ans;
	}
};