#pragma once
#include <opencv2/core/matx.hpp>
#include <vector>
class Ray{
	public:
		float t;
		cv::Vec2f dir;
		cv::Vec2f org;
		float angle;
		Ray(cv::Vec2f o, cv::Vec2f d, float a):org(o), dir(d){
			t = INFINITY;
			angle = a*M_PI/180;
		}
		Ray(float a){
			org = cv::Vec2f(0,0);
			dir = cv::Vec2f(0,1);
			t = INFINITY;
			angle = a*M_PI/180;
			}
		void SetAngle(float a){
			angle = a*M_PI/180;
			
			}
	
	
	};