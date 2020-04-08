#pragma once
#include <memory>
#include <opencv2/core/matx.hpp>
#include <vector>
class Robot {
	public:
		cv::Vec2f pos;
		cv::Vec2f dir;
		std::vector<std::shared_ptr<Ray>> Rays;
		Robot(){
			pos[0] = 0;
			pos[1] = 0;
			dir = cv::Vec2f(0,1);
			}
			
		Robot (cv::Vec2f& p, cv::Vec2f& d){
			pos[0] = p[0];
			pos[1] = p[1];
			dir = d;
			
			}
		
		void AddRay(std::shared_ptr<Ray> R){
			R->org = pos;
			Rays.push_back(R);
		}
	
	private:
		
	};