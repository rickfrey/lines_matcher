#include<vector>
#include<iostream>
#include<string>
#include"bildinfo.h"

using namespace std;

void Bildinfo::setLinienarray(int aa, int bb, int cc, int dd, int ee, int ff)
{
    this->Array[0]=aa;
    this->Array[1]=bb;
    this->Array[2]=cc;
    this->Array[3]=dd;
    this->Array[4]=ee;
    this->Array[5]=ff;
}
int Bildinfo::getLinienarray()
{
    return this->Array[2];
}
/*
void Bildinfo::setPose(float x, float y, float z, float r, float p, float ya)
{
    this->x=x;
    this->y=y;
    this->z=z;
    this->r=r;
    this->p=p;
    this->ya=ya;
}
*/
/*
void Bildinfo::setPose(std::vector<int> Pose)
{
//this->
}
*/

Bildinfo::Bildinfo()
{}
Bildinfo::~Bildinfo()
{}
