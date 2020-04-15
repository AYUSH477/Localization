#define PI 3.14159265
#include <iostream>
#include "Matrix.h"
int main(){
    Vector<float> a(3);
    a.push_back(1);
    a.push_back(1);
    a.push_back(1);
    a.normalize();
    //a=a-a;
    std::cout<<a[0]<<" "<<a[1]<<" "<<a[2]<<std::endl;
    Vector<float> b;
    b.push_back(2);
    b.push_back(3);
    b.rotate(PI/2);
    std::cout<<b[0]<<" "<<b[1]<<std::endl;
    Vector<float> d(3);
    d.push_back(1);
    d.push_back(1);
    d.push_back(1);
    float c=a.dot(a,d);
    std::cout<<c<<std::endl;
    Matrix<float> m(3);
    m.add(1);
    m.add(1);
    m.add(1);
    m.add(1);
    m.add(1);
    m.add(1);
    m.add(1);
    m.add(2);
    m.add(1);
    m=m+m;
    a=m*a;
    std::cout<<a[0]<<" "<<a[1]<<" "<<a[2]<<std::endl;
    std::cout<<m[2][1]<<" "<<m[1][2]<<std::endl;
}