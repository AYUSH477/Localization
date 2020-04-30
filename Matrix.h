#pragma once
#include "Vector.h"
#include <cmath>
#include <iostream>
#define PI 3.14159265
template <typename T>
class Matrix{
    public:
        T **data;
        int r;
        int c;
        int size;
        Matrix(int n){
            size=n;
            int i=0;
            data=new T*[n];
            while(i<n){
                data[i]=new T[n];
                i++;
            }
            r=0;
            c=0;
        }
        void add(T a){
            data[r][c]=a;
            c++;
            if(r==size && c==size){
                std::cout<<"Too many inputs for matrix of size "<<size<<"by "<<size<<std::endl;
                exit(1);
            } else if(c==size){
                r++;
                c=0;
            }
        }
        T* operator[](int r){
            return data[r];
        }
        Vector<T> operator*(Vector<T> &a){
            Vector<T> result(size);
            try{
                if(size!=a.dim){
                    throw 1;
                }
                int i=0;
                T store=0;
                int i2=0;
                T sum=0;
                while(i<size){
                    while(i2<size){
                        store=data[i][i2]*a[i2];
                        sum+=store;
                        i2++;
                    }
                    result.push_back(sum);
                    sum=0;
                    store=0;
                    i++;
                    i2=0;
                }
                return result;
            }catch(int){
                std::cout<<"Matrix vector multiplication not possible"<<std::endl;
                exit(1);
            }
        }
        Matrix<T> operator+(Matrix &a){
            if(a.size!=this->size){
                std::cout<<"Matrix addition not possible"<<std::endl;
                exit(1);
            }
            int i=0, i2=0;
            Matrix<T> result(size);
            while(i<size){
                while(i2<size){
                    result.data[i][i2]=this->data[i][i2]+a.data[i][i2];
                    i2++;
                }
                i2=0;
                i++;
            }
            result.r=this->r;
            result.c=this->c;
            result.size=this->size;
            return result;
        }
        Matrix<T> operator-(Matrix &a){
            if(a.size!=this->size){
                std::cout<<"Matrix subtraction not possible"<<std::endl;
                exit(1);
            }
            int i=0;
            int i2=0;
            Matrix<T> result(size);
            while(i<size){
                while(i2<size){
                    result.data[i][i2]=this->data[i][i2]-a.data[i][i2];
                    i2++;
                }
                i2=0;
                i++;
            }
            result.r=this->r;
            result.c=this->c;
            result.size=this->size;
            return result;
        }
        void operator =(Matrix A){
            int i=0, i2=0;
            while(i<size){
                while(i2<size){
                    this->data[i][i2]=A.data[i][i2];
                    i2++;
                }
                i2=0;
                i++;
            }
            this->r=A.r;
            this->c=A.c;
            this->size=A.size;
        }
        ~Matrix(){
            int i=0;
            while(i<size){
                delete[] data[i];
                i++;
            }
        }
};