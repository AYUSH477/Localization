#pragma once
//#include <opencv2/core/matx.hpp>
#include <vector>
#include "Matrix.h"
class Ray{
	public:
		float t;
		Vector<float> dir;
		Vector<float> org;
		float angle;
		Ray(Vector<float> o, Vector<float> d, float a): dir(d), org(o){
			t = INFINITY;
			angle = a*M_PI/180;
		}
		Ray(float a){
			org = Vector<float>(0,0);
			dir = Vector<float>(0,1);
			//dir[0]=0;
			//dir[1]=1;
			std::cout<<"ray cretaed: "<<dir[0]<<dir[1]<<std::endl;
			t = INFINITY;
			angle = a*M_PI/180;
			}
		void SetAngle(float a){
			angle = a*M_PI/180;
			
			}
		/*Ray(Ray &A){
			this->t =A.t;
			int i=0;
			while(i<A.dir.size()){
				dir[i]=A.dir[i];
				i++;
			}
			//dir=A.dir;
			org=A.org;
			angle=A.angle;
		}*/
	
	
	};