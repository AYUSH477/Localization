#pragma once
#include <opencv2/core/matx.hpp>
#include <vector>	
#include <memory>
#include "Prim.h"
#include "Robot.h"
#include <iostream>
class Scene {
	
	public:
		Scene(float a = 200, float b=200):x(a), y(a){
		}
		void Add(std::shared_ptr<Prim>obj){
			Objects.push_back(obj);
			
			}
		double* Trace (Robot& r){
			
			cv::Mat M(2,2,CV_32FC1);
			
			double * result = new double[r.Rays.size()+1];
			int i = 0;
			for(auto ray: r.Rays){
				cv::Mat M(2,2,CV_32FC1);
				M.at<float>(0,0) = cos(ray->angle);
				M.at<float>(0,1) = -sin(ray->angle);
				M.at<float>(1,0) = sin(ray->angle);
				M.at<float>(1,1) = cos(ray->angle);
				M = M*cv::Mat(r.dir);
				ray->org = r.pos;
				ray->dir = cv::Vec2f(M.at<float>(0,0), M.at<float>(1,0));
				ray->dir = normalize(ray->dir);
				ray->t = INFINITY;
				
				for(auto o: Objects){
					
					o->Intersect(*ray);
					}
				result[i] = ray->t;
				i++;
				
				}
				
			return result;
			
		}
		float getX(){
			return x;
			
			}
		float getY(){
			return y;
			
			}
	
	
	
	private:
		 std::vector<std::shared_ptr<Prim>> Objects;
		 float x,y;
		 
	
};