#ifndef BILDINFO_H
#define BILDINFO_H

using namespace std;

class Bildinfo
{
private:
    //int x,y,z,r,p,ya;//Pose
    int Linienanzahl;
    int Linienarray;
//    std::vector<int> Pose(6);


public:
    Bildinfo();
    ~Bildinfo();

    //void setPose(float x, float y, float z, float r, float p, float ya);
    void setLinienarray();
    void setPose(std::vector<int> Pose);

};

#endif
