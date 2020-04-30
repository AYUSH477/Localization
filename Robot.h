#pragma once
#include <memory>
//#include <opencv2/core/matx.hpp>
#include <vector>
class Robot {
	public:
		Vector<float> pos;
		Vector<float> dir;
		std::vector<std::shared_ptr<Ray>> Rays;
		Robot(){
			pos[0] = 0;
			pos[1] = 0;
			dir = Vector<float>(0,1);
			}
			
		Robot (Vector<float>& p, Vector<float>& d){
			pos[0] = p[0];
			pos[1] = p[1];
			dir = d;
			
			}
		
		void AddRay(std::shared_ptr<Ray> R){
			R->org = pos;
			std::cout<<"Adding ray"<<std::endl;
			std::cout<<"Ray dir "<<R->dir[0]<<R->dir[1]<<std::endl;
			std::cout<<"Ray angle "<<R->angle<<std::endl;
			Rays.push_back(R);
		}
	
	private:
		
	};