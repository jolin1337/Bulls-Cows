#pragma once
#include <vector>
#include <fstream>
#include <string>
using namespace std;
class Object_Import{
public:
	int color;
	Vector3 *position;
	vector<vector<int> > faces;
	vector<Vector3 * >vertices;
	Object_Import(string path){
		ifstream file(path);
		string content,temp;
		int i=0;
		while(file.good()){
			if(temp=="v" || temp=="V"){
				file>>temp;
				//int t = System::Convert::Double(temp);
				int x=(int)(temp[0]=='-'?temp[1]:temp[0])-48;
				x*=temp[0]=='-'?-1:1;
				file>>temp;
				int y=(int)(temp[0]=='-'?temp[1]:temp[0])-48;
				y*=temp[0]=='-'?-1:1;
				file>>temp;
				int z=(int)(temp[0]=='-'?temp[1]:temp[0])-48;
				z*=temp[0]=='-'?-1:1;
				vertices.push_back(new Vector3(x,y,z));//System::Convert::toInt32(temp)
			}
			else if(temp=="f" || temp=="F"){
				file>>temp;
				bool b=(int)(temp[0])>=48&&(int)(temp[0])<=57;
				faces.resize(i+1);
				while(b&&file.good()){
					faces[i].push_back((int)(temp[0])-48);
					file>>temp;
					b=(int)(temp[0])>=48&&(int)(temp[0])<=57;
				}
				i++;
			}
			else file>>temp;
			//faces
			content+=temp;
		}
		file.close();
	}
	vector<Vector3 *>getFace(int i, vector<Vector3 *> vert){
		vector<Vector3 *> fa;
		for(int j =0;j<4;j++){
			int l=((this->faces[i])[j])-1;
			fa.push_back(vert[l]);
		}//System::Windows::Forms::MessageBox::Show(System::Convert::ToString(ans[1]->z),"");
		return fa;
	}
	vector<vector<Vector3 * > >getPolygon(vector<Vector3 *> vert){
		vector<vector<Vector3 * > > gP;
		for(int i=0;i<6;i++){
			gP.push_back(this->getFace(i,vert));
		}
		return gP;
	}
};