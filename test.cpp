#include <opencv2/core/matx.hpp>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "Matrix.h"
#include <vector>
#include <memory>
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
};
class QRay{
	public:
		float t;
		cv::Vec2f dir;
		cv::Vec2f org;
		float angle;
		QRay(cv::Vec2f o, cv::Vec2f d, float a): dir(d), org(o){
			t = INFINITY;
			angle = a*M_PI/180;
		}
		QRay(float a){
			org = cv::Vec2f(0,0);
			dir = cv::Vec2f(0,1);
			t = INFINITY;
			angle = a*M_PI/180;
		}
};
class PRobot{
	public:
		Vector<float> pos;
		Vector<float> dir;
		std::vector<std::shared_ptr<Ray>> Rays;
		PRobot(){
			pos[0] = 0;
			pos[1] = 0;
			dir = Vector<float>(0,1);
		}
		void AddRay(std::shared_ptr<Ray> R){
			R->org = pos;
			Rays.push_back(R);
		}
};
class QRobot{
	public:
		cv::Vec2f pos;
		cv::Vec2f dir;
		std::vector<std::shared_ptr<QRay>> Rays;
		QRobot(){
			pos[0] = 0;
			pos[1] = 0;
			dir = cv::Vec2f(0,1);
		}
		void AddRay(std::shared_ptr<QRay> R){
			R->org = pos;
			Rays.push_back(R);
		}
};
void vm_edit(PRobot &r, float angle){
	std::cout<<"pre:"<<r.Rays[0]->dir[0]<<" "<<r.Rays[0]->dir[1]<<std::endl;
    r.Rays[0]->dir.rotate(r.Rays[0]->angle);
	//std::cout<<r.Rays[0]->angle<<std::endl;
    r.Rays[0]->dir.normalize();
	std::cout<<"post:"<<r.Rays[0]->dir[0]<<" "<<r.Rays[0]->dir[1]<<std::endl;
}
void cv_method(QRobot &r2, float angle){
	cv::Mat M(2,2,CV_32FC1);
	std::cout<<"pre:"<<r2.Rays[0]->dir[0]<<" "<<r2.Rays[0]->dir[1]<<std::endl;
	//std::cout<<r2.Rays[0]->angle<<std::endl;
	M.at<float>(0,0) = cos(r2.Rays[0]->angle);
	M.at<float>(0,1) = -sin(r2.Rays[0]->angle);
	M.at<float>(1,0) = sin(r2.Rays[0]->angle);
	M.at<float>(1,1) = cos(r2.Rays[0]->angle);
	M = M*cv::Mat(r2.Rays[0]->dir);
	//ray->org = r.pos;
	r2.Rays[0]->dir = cv::Vec2f(M.at<float>(0,0), M.at<float>(1,0));
	r2.Rays[0]->dir = cv::normalize(r2.Rays[0]->dir);
	std::cout<<"post:"<<r2.Rays[0]->dir[0]<<" "<<r2.Rays[0]->dir[1]<<std::endl;
} 
int main(){
    cv::Vec2f dir=cv::Vec2f(.5555, .67777);
    int angle=0.785398;
	//cv_method(dir, angle);
	PRobot r1;
	QRobot r2;
	Ray ra(45);
	ra.dir[0]=0;
	ra.dir[1]=1;
	QRay rb(45);
	rb.dir[0]=0;
	rb.dir[1]=1;
	r1.AddRay(std::make_shared<Ray> (ra));
	r2.AddRay(std::make_shared<QRay> (rb));
    Vector<float> dir2(.5555, .67777);
	vm_edit(r1, angle);
	cv_method(r2, angle);
	vm_edit(r1, angle);
	cv_method(r2, angle);
}