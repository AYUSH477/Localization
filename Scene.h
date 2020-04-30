#pragma once
//#include <opencv2/core/matx.hpp>
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
		double* Trace (Robot &r){
			
			
			double * result = new double[r.Rays.size()+1];
			int i = 0;
			for(auto ray: r.Rays){
				//std::cout<<"pre in trace:"<<ray->dir[0]<<" "<<ray->dir[1]<<std::endl;
				ray->dir.rotate(ray->angle);
				//std::cout<<"post in trace:"<<ray->dir[0]<<" "<<ray->dir[1]<<std::endl;
				ray->dir.normalize();
				ray->t = INFINITY;
				ray->org = r.pos;
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