#pragma once
#include <cmath>
#include <iostream>
template <typename T>
class Vector{
    public:
        T *data;
        int position;
        int dim;
        Vector(){
            data=new T[2];
            position= 0;
            dim=2;
        }
        Vector(T a, T b){
            data=new T[2];
            data[0]=a;
            data[1]=b;
            position=2;
            dim=2;
        }
        Vector(int n){
            data=new T[n];
            position=0;
            dim=n;
        }
        Vector(const Vector &A){
            data=new T[A.dim];
            int i=0;
            while(i<A.dim){
                data[i]=A.data[i];
                i++;
            }
            dim=A.dim;
            position=A.position;
        }
        void push_back(T a){
            if(position==dim){
                std::cout<<"Too many elements for this vector"<<std::endl;
                exit(1);
            }
            data[position]=a;
            position++;
        }
        T dot(Vector &a, Vector &b){
            if(a.dim!=b.dim){
                std::cout<<"Invalid dot product";
                exit(1);
            }
            Vector result(a.dim);
            int i=0;
            T store;
            while(i<a.dim){
                store=a.data[i]*b.data[i];
                result.push_back(store);
                i++;
            }
            i=0;
            store=0;
            while(i<a.dim){
                store+=result[i];
                i++;
            }
            return store;
        }
        int size(){
            return position;
        }
        T& operator [](int idx){
            return data[idx];
        }
        Vector operator -(Vector &A){
            if(A.dim!=this->dim){
                std::cout<<"Vector subtraction not possible"<<std::endl;
                exit(1);
            }
            int i=0;
            Vector result;
            while(i<position){
                result.data[i]=this->data[i]-A.data[i];
                i++;
            }
            result.position=this->position;
            return result;
        }
        Vector operator +(Vector &A){
            if(A.dim!=this->dim){
                std::cout<<"Vector addition not possible"<<std::endl;
                exit(1);
            }
            int i=0;
            Vector result;
            while(i<position){
                result.data[i]=this->data[i]+A.data[i];
                i++;
            }
            result.position=this->position;
            return result;
        }
        void operator =(Vector A){
            int i=0;
            while(i<A.position){
                this->data[i]=A.data[i];
                i++;
            }
            this->position=A.position;
        }
        void rotate(double a){
            if(this->dim!=2){
                std::cout<<"Rotate method for 2D vectors only"<<std::endl;
            }
            T x = data[0]*cos(a)-data[1]*sin(a);
            data[1]=data[0]*sin(a)+data[1]*cos(a);
            data[0]=x;
        }
        void normalize(){
            int i=0;
            float norm=0;
            float store;
            while(i<position){
                store=data[i]*data[i];
                norm+=store;
                i++;
            }
            norm=sqrt(norm);
            i=0;
            while(i<position){
                data[i]=data[i]/norm;
                i++;
            }
        }
        ~Vector(){
            delete[] data;
        }
};