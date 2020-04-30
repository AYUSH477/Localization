#include "Prim.h"
//#include "Triangle.h"
#include "Rectangle.h"
#include "Ray.h"
#include "Scene.h"
#include "Robot.h"
#include <cmath>
//#include <opencv2/core/matx.hpp>
#include <vector>
#include <memory>
#include <ctime>
#include <unistd.h>
#include "Particles.h"
#include "Matrix.h"

/**This function basically runs the simulation that
  uses particle filtering to know the location of the 
  robot in a given map.
   * @param r: the robot
   * @param scene: the map
 
**/
void RobotTest(Robot& r, Scene& scene){

	Particles p(100, 0, scene.getX(), 0, scene.getY(),r.Rays, r.dir, &scene); //Creating 100 particles within the dimensions of the map given by the scene object.
	p.initialize();
	double* p1; 
	for(int j = 0; j<50; j++){  
				std::cout<<"pre:"<<r.Rays[0]->dir[0]<<" "<<r.Rays[0]->dir[1]<<std::endl;
				//Ray directions altered by Scene.trace in the code using opencv only change by very small amounts
				//An actual rotation as I understand it would result in large changes to ray directions as in this code
				//Similar rotations done in test.cpp with a cv matrix also have the same changes as in this code 
		p1 = scene.Trace(r); //the sonar data is collected for the robot r: this is the actual sonar data collected by the sonar
				std::cout<<"post:"<<r.Rays[0]->dir[0]<<" "<<r.Rays[0]->dir[1]<<std::endl;
		r.pos[0]+=1; // the robot's actual position and angle are updated
		r.pos[1]+=1;
		r.dir[0] +=0.1f;
		r.dir[1] +=0.1f;
		r.dir.normalize();
		p.updateState(1,1,0,0,0,0); // the displacement by which the robot's position(Here '1') was updated is used to update the position of the particles.
		p.updateDir(r.dir);  // direction is updated for the particles
		p.updateWeights(p1); // weights is updated for the particles by providing the robot's actual sonar data p1: the particles with weight closest to p1 will have the highest weight
		p.normalize();
		p.resample(); // particles with the highest weight chosen and filtered.
		p.printExpectedPosition(); //prints one of the filtered particles (not updated completely) 
		//sleep(1);
		
	}
	std::cout<<r.pos[0]<<" "<<r.pos[1]<<std::endl;
	delete [] p1;
	
	}

int main(){
	Ray ra(45), rb(10), rc(-45); // three rays created
	Robot r1; // robot created
	Vector<float> d(1,1);
	//cv::Vec3f x = d.cross(d);
	//std::cout<<x[0]<<std::endl;
	//cv::Mat x = cv::Mat(d).cross(cv::Mat(d));
	//std::cout<<x.at<float>(0,0)<<std::endl;
	Scene scene(100, 100); //scene created: this is basically the map or the environment of the robot.
	r1.AddRay(std::make_shared<Ray>(ra)); // rays are added to the robot with the robot's origin as their origin.
	r1.AddRay(std::make_shared<Ray>(rb));
	r1.AddRay(std::make_shared<Ray>(rc));
	//scene.Add(std::make_shared<Triangle>(cv::Vec2f(1, 3),cv::Vec2f(2, 2),cv::Vec2f(3, 2.8)));
	//scene.Add(std::make_shared<Triangle>(cv::Vec2f(5, 10),cv::Vec2f(8, 13),cv::Vec2f(13, 10)));
	//scene.Add(std::make_shared<Rectangle>(cv::Vec2f(20, 25),cv::Vec2f(20, 30),cv::Vec2f(25, 30), cv::Vec2f(25, 20)));
	//scene.Add(std::make_shared<Rectangle>(cv::Vec2f(50, 50),cv::Vec2f(50, 70),cv::Vec2f(70, 70), cv::Vec2f(70, 50)));
	
	
	/*
	 * Right now, the only obstacle in the scene or the map is a bounding rectangle.
	 * */
	scene.Add(std::make_shared<Rectangle>(Vector<float>(0, 0),Vector<float>(scene.getX(), 0),Vector<float>(scene.getX(), scene.getY()), Vector<float>(0, scene.getY()))); // bounding rectangle
	RobotTest(r1, scene);
	return 0;
	
	}