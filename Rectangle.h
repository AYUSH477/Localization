#pragma once
#include "Prim.h"
#include <opencv2/core/matx.hpp>
#include <vector>
#include <cmath>
class Rectangle: public Prim{
	public:
		Rectangle(cv::Vec2f v1, cv::Vec2f v2, cv::Vec2f v3, cv::Vec2f v4): Prim(), v1(v1),v2(v2), v3(v3), v4(v4) {}
		
		
		float vector (cv::Vec2f v1, cv::Vec2f v2) {
			return v1[0]*v2[1]-v1[1]*v2[0];
			
			}
		void updateMin(cv::Vec2f o, cv::Vec2f v1, cv::Vec2f diff1, Ray& ray, double& min){
			double d1, u1;
			if(std::isinf(1/(vector(diff1, ray.dir))))
				d1 = INFINITY;
			else{
				 u1 = vector(o-v1, ray.dir)/vector(diff1, ray.dir); //xmin
				 d1 = vector(v1-o, diff1)/vector(ray.dir, diff1); //xmin
			}
			if(!std::isinf(d1))
				if(d1>0 && u1>0 && u1<1){
					
					if(d1<min)
						min = d1;
					}
			
			}
		bool Intersect(Ray& ray){
			double min = INFINITY;
			double d1, d2, d3, d4, u1, u2,u3, u4;
			cv::Vec2f o(ray.org);
			cv::Vec2f diff1 = v2-v1; //a 
			cv::Vec2f diff2 = v4-v1; //d
			cv::Vec2f diff3 = v3-v4; //c
			cv::Vec2f diff4 = v3-v2; //b

			updateMin(o, v1, diff1, ray, min);

			updateMin(o, v4, diff3, ray, min);
		
			updateMin(o, v1, diff2, ray, min);	
			
			updateMin(o, v2, diff4, ray, min);
			if(ray.t>min)
				ray.t = min;
			return !std::isinf(min);
		}
	private:
		cv::Vec2f v1;
		cv::Vec2f v2;
		cv::Vec2f v3;
		cv::Vec2f v4;
	
};