#ifndef BILDINFO_H
#define BILDINFO_H

using namespace std;

class Bildinfo
{
private:
    //int x,y,z,r,p,ya;//Pose
    //int Linienanzahl;
    //int a=6;
    //int Linienarray[a];
//    std::vector<int> Pose(6);
    int Array[6];

public:
    Bildinfo();
    ~Bildinfo();

    //void setPose(float x, float y, float z, float r, float p, float ya);
    void setLinienarray(int aa, int bb, int cc, int dd, int ee, int ff);
//    void setPose(std::vector<int> Pose);
    int getLinienarray();
};

#endif
