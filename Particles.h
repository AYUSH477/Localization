
 
#pragma once
#include "Robot.h"
#include "Ray.h"
#include <iostream>
#include <random>
#include <chrono>
#include <cstdlib>
class Particles {
	
	private:
		int N; 
		double Xmin, Xmax, Ymin, Ymax;
		double * meanParticle;
		int bestParticle;
		double **particles;
		Scene* scene;
		Robot r1;

	public:
		
		Particles(int n, double Xmi, double Xma, double Ymi, double Yma, std::vector<std::shared_ptr<Ray>> &v, cv::Vec2f dir, Scene *s):N(n), Xmin(Xmi), Ymin(Ymi), 
		Xmax(Xma), Ymax(Yma){
			for(auto rays:v)
				r1.Rays.push_back(rays);
			scene = s;	
			r1.dir = dir;
			
			}
		void initialize() {
				meanParticle = new double[6];
				std::srand(std::time(0));
				particles = new double*[7];	
				for(int i = 0; i<7; i++)
					particles[i] = new double[N];
				for(int i=0;i<N;i++){
					//std::srand(std::time(0));
					particles[2][i]=0;
					particles[3][i]=0; 
					particles[4][i]=0;
					particles[5][i]=0;
					particles[0][i]=Xmin + ((double)rand()/(RAND_MAX))*(Xmax-Xmin);
					particles[1][i]=Ymin + (double)rand()/(RAND_MAX)*(Ymax-Ymin);
					particles[6][i]=1.0/N;
					
				}
				
			}
			
	   void updateWeights(const double *realPing){
			
			for(int i=0;i<N;i++){

				r1.pos = cv::Vec2f(particles[0][i], particles[1][i]);       	
				double* simulatedPing = scene->Trace(r1);
				double sumProb=0;
				int nScanWithHit=0;
				for (int k=0;k<r1.Rays.size();k++){
					if(simulatedPing[k]==0.0)
							simulatedPing[k]+=0.0001; //?
					double probK = 1/(0.5 * 1.772)*exp(-0.5*pow((simulatedPing[k]-realPing[k])/0.5,2)); //todo: replacement by constants
					sumProb = sumProb + probK;
					nScanWithHit++;            
				}
				
				
				if(nScanWithHit != 0){
					particles[6][i]=sumProb/ nScanWithHit;
				}
				else
					particles[6][i]=0.3;
			}
			std::cout<<"update weight finished"<<std::endl;
		}
		
		void normalize(){
			
			
			double sumWeights=0;
			for(int i=0;i<N;i++){
				sumWeights+=particles[6][i];
			}
			
			for(int i=0;i<N;i++){
				double previousWeight=particles[6][i];
				particles[6][i]=previousWeight/sumWeights;
			}    
		}
		
		void updateDir(cv::Vec2f v){
			r1.dir = v;
			}
		
		void resample(){
			std::srand(std::time(0));
			std::cout<<"starting resampling..."<<std::endl;
			//if(Const.SLEEP_IN_STEPS) Thread.sleep(3000);
			double** newGeneration;
			newGeneration = particles;      
			double* cumprob= new double[N];
			cumprob[0]=particles[6][0];
			for(int i=1;i<N;i++){
				cumprob[i]=cumprob[i-1]+particles[6][i];
			}
			unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
			std::default_random_engine generator(seed);
			std::normal_distribution<double> distribution(0.0,0.5);	
			for(int k=0;k<N;k++){  
				double q = (double)rand()/(RAND_MAX);  
				int index = -1;
				//std::cout
				for(int i=0;i<N;i++){
					if(cumprob[i]>q){
						index=i;
						break;
					}
				}
				newGeneration[0][k]=(particles[0][index] + distribution(generator));
				distribution.reset();
				newGeneration[1][k]=(particles[1][index] + distribution(generator));
				distribution.reset();
				newGeneration[2][k]=(particles[2][index] + distribution(generator));
				distribution.reset();
				newGeneration[3][k]=(particles[3][index] + distribution(generator));
				distribution.reset();
				newGeneration[4][k]=(particles[4][index] + distribution(generator));
				distribution.reset();
				newGeneration[5][k]=(particles[5][index] + distribution(generator));
				newGeneration[6][k]=(1.0/N);
			}
			particles=newGeneration;
			
		 
		}
		
	   void updateState(double dX,double dY,double dZ,double dRoll,double dPitch,double dYaw){
			for(int i=0;i<N;i++){
				//todo: add noise (?) check if already noisy
				
				particles[0][i] += dX;
				if(particles[0][i]<Xmin)
					particles[0][i] = Xmax;
				if(particles[0][i]>Xmax)
					particles[0][i] = Xmin;
				particles[1][i] += dY;
				if(particles[1][i]<Ymin)
					particles[1][i] = Ymax;
				if(particles[1][i]>Ymax)
					particles[1][i] = Ymin;
				particles[2][i] += dZ;            
				particles[3][i] += dRoll;            
				particles[4][i] += dPitch;            
				particles[5][i] += dYaw;            
			}        
		}
		
		
		

		void reinitializeMean(){
			for(int i = 0; i<sizeof(meanParticle); i++)
				meanParticle[i] = 0;
			
			}
		void printExpectedPosition(){
			//int indexMax=-1;
			//double weightMax=-1;
			double sumWeight=0;
			//reinitializeMean();
			bestParticle = 0;
			for(int i=0;i<N;i++){
				//std::cout<<"Best Particle"<<particles[6][i]<<std::endl;
				sumWeight+=particles[6][i];
				
				if(particles[6][i]>particles[6][bestParticle]){
					bestParticle=i;
				}
//				meanParticle[0] += particles[0][i]*particles[6][i];
//				meanParticle[1] += particles[1][i]*particles[6][i];
//				meanParticle[2] += particles[2][i]*particles[6][i];
//				meanParticle[3] += particles[3][i]*particles[6][i];
//				meanParticle[4] += particles[4][i]*particles[6][i];
//				meanParticle[5] += particles[5][i]*particles[6][i];
			}
//			meanParticle[0] /= sumWeight;
//			meanParticle[1] /= sumWeight;
//			meanParticle[2] /= sumWeight;
//			meanParticle[3] /= sumWeight;
//			meanParticle[4] /= sumWeight;
//			meanParticle[5] /= sumWeight;
//			
			std::cout<<"Best Particle (weight: "<<particles[6][bestParticle]<<"):"<<std::endl;
			std::cout<<"X: "<<particles[0][bestParticle]<<std::endl;
			std::cout<<"Y: "<<particles[1][bestParticle]<<std::endl;
			std::cout<<"Index: "<<bestParticle<<std::endl;
//			std::cout<<"------------------------------\nMean Particle:";
//			std::cout<<"X: "<<meanParticle[0]<<std::endl;
//			std::cout<<"Y: "<<meanParticle[1]<<std::endl;
		}

		double* getMeanParticle() {
			return meanParticle;
		}

	  /* public void setMeanParticle(Particle meanParticle) {
			this.meanParticle = meanParticle;
		}
	*/
	int getBestParticle(){
			return bestParticle;
		}
		~Particles(){
			for (int i = 0; i<7; i++)
				delete [] particles[i];
			delete [] particles;
			delete [] meanParticle;
			}
		
};
    /*
    public void setBestParticle(Particle bestParticle) {
        this.bestParticle = bestParticle;
    }
 */ 

    /*
    public void setEnvironment(){
        // coefficient describing the test setup (U environment) - paramenters got with Matlab
        double[][] lines = {{100,0,-50,0,50,0,-100,0},{0,-30,0,-40,0,-30,0,100},{0,3000,1500,2000,-3500,3000,10000,0},{0,0,30,30,70,70,100,0},{0,30,30,70,70,100,100,100},{0,100,50,50,50,100,0,0},{100,100,100,50,100,100,100,0}};
        simulatedSonar.setLines(lines);
        
   }
    
    public static void setEnvironment(SynteticSonar simulatedSonar){
        // coefficient describing the test setup (U environment) - paramenters got with Matlab
        double[][] lines = {{100,0,-50,0,50,0,-100,0},{0,-30,0,-40,0,-30,0,100},{0,3000,1500,2000,-3500,3000,10000,0},{0,0,30,30,70,70,100,0},{0,30,30,70,70,100,100,100},{0,100,50,50,50,100,0,0},{100,100,100,50,100,100,100,0}};
        simulatedSonar.setLines(lines);
        
   }
    
    public int getNParticles(){
        return particles[0].length;
    }
    
    public int getDimState(){
        return particles.length;
    }
    
    public double[][] getPositions(){
        double[][] positions = new double[Const.N][2];
        for(int i=0;i<particles[0].length;i++){            
            positions[i][0]=particles[0][i];
            positions[i][1]=particles[1][i];
        }
        return positions;
    }
    
    @Override
    protected Object clone(){
        Particles clone = new Particles(new double[particles.length][particles[0].length]);
        for(int i=0;i<particles.length;i++){
            for(int j=0;j<particles[0].length;j++){
                clone.particles[i][j]= particles[i][j]; //copy the same state of particles
            }
        }
        
        return clone;
    }
     
     
*/
