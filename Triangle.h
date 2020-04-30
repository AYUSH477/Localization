#pragma once
#include "Prim.h"
//#include <opencv2/core/mat.hpp>
#include <vector>
#include <cmath>
#include <iostream>
class Triangle:public Prim{
	public:
		Triangle(Vector<float> v1, Vector<float> v2, Vector<float> v3): Prim(), v1(v1),v2(v2), v3(v3) {}
		bool Intersect(Ray& ray){
			float t = INFINITY;
			//cv::Mat M(2,2, CV_32FC1);
			Matrix<float> M(2);
			Vector<float> o(ray.org);
			M[0][0]=v2[0]-v1[0];
			M[1][0]=v2[1] - v1[1];
			M[0][1]=-ray.dir[0];
			M[1][1]=-ray.dir[1];
			/*M.at<float>(0,0) = v2[0]-v1[0];
			
			M.at<float>(1,0) = v2[1] - v1[1];
			
			M.at<float>(0,1) = -ray.dir[0];
			
			M.at<float>(1,1) = -ray.dir[1];*/
			
			Vector<float> v(o[0]-v1[0], o[1]-v2[1]);
			
			//M = M.inv()*cv::Mat(v);
			
			Vector<float> r1(M[0][0], M[1][0]);
			
			M[0][0] = v3[0] -v1[0];
			M[1][0] = v3[1] -v1[1];
			v[1] = o[1] - v2[1];
			
			//M = M.inv()*cv::Mat(v);
			
			//cv::Vec2f r2 = cv::Vec2f(M);
			Vector<float> r2(M[0][0], M[1][0]);
			
			M[0][0]= v3[0] -v2[0];
			M[1][0]= v3[1] -v2[1];
			v[0] = o[0] -v2[0];
			v[1] = o[1] - v3[1];
			//M = M.inv()*cv::Mat(v);
			Vector<float> r3(M[0][0], M[1][0]);
			
			if(r1[0]>0 && r1[0]<1){
				if(r1[1]>0)
					t = r1[1];
				}
			if(r2[0]>0 && r2[0]<1){
				if(r2[1]>0 & r2[1]<t)
					t = r2[1];
				}
			
			if(r3[0]>0 && r3[0]<1){
				if(r3[1]>0 & r3[1]<t)
					t = r3[1];
				}
			ray.t = t;
			
			return !(std::isinf(t));
			
		}
	private:
		Vector<float> v1;
		Vector<float> v2;
		Vector<float> v3;
	
	
};