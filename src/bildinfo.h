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
    int Posenarray[6];
    vector<vector<int> > Linienvektor;

public:
    Bildinfo();
    ~Bildinfo();

    //void setPose(float x, float y, float z, float r, float p, float ya);
    void setPosenarray(int aa, int bb, int cc, int dd, int ee, int ff);
//    void setPose(std::vector<int> Pose);
    int getLinienarray();
    void setLinienvektor(vector<vector<int> > vektor);
};

#endif
