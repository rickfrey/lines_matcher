#include<vector>
#include<iostream>
#include<string>
#include"bildinfo.h"

using namespace std;

void Bildinfo::setPosenarray(int aa, int bb, int cc, int dd, int ee, int ff)
{
    this->Posenarray[0]=aa;
    this->Posenarray[1]=bb;
    this->Posenarray[2]=cc;
    this->Posenarray[3]=dd;
    this->Posenarray[4]=ee;
    this->Posenarray[5]=ff;
}
int Bildinfo::getLinienarray()
{
    return this->Posenarray[2];
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
