#ifndef NUMB_H
#define NUMB_H 
class DistinktNumber{
	int num;
public:
	DistinktNumber():num(0){}
	DistinktNumber(int n):num(n){}
	int setNum(int n){
		num = n;
		return selectDistinkt();
	}
	int getNum(){return selectDistinkt();}
	int selectDistinkt(){
		num = DistinktNumber::selectDistinkt(num);
		return num;
	}
	static int getPos(int num, int pos, int len){
		pos = len - pos - 1;
		int in=1;
		for(int inj=0;inj<pos;inj++) in*=10;
		return (num%(in*10))/in;
	}
	static int length(int n){
		int l=1;
		for(int k = 0; k < n; k++)
			l *= 10;
		return l;
	}
	operator int(){
		return selectDistinkt();
	}
	int operator +(int i){
		num += i;
		return selectDistinkt();
	}
	static int selectDistinkt(int num){
		for(int i=0; i<4; i++)
			for(int j=0; j<4; j++)
				if(i != j && getPos(num, i+1, 5) == getPos(num, j+1, 5)){
					num += length(4-(j+1));
					if(getPos(num, 0, 5) != 5)
						return -1;
					i=0;j=0;
				}
		return num;
	}
};

#endif