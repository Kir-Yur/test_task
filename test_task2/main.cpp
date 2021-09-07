#include <vector>
#include <iostream>
#include <array>
#include <cmath>

using namespace std;

class Point3d
{
private:
    double x;
    double y;
    double z;

public:
    Point3d()
    {
        this->x = 0;
        this->y = 0;
        this->z = 0;
    }

    Point3d (double x, double y, double z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Point3d operator +(const Point3d &a)
    {
        Point3d temp;
        temp.x = this->x + a.x;
        temp.y = this->y + a.y;
        temp.z = this->z + a.z;

        return temp;
    }

    Point3d operator -(const Point3d &a)
    {
        Point3d temp;
        temp.x = this->x - a.x;
        temp.y = this->y - a.y;
        temp.z = this->z - a.z;

        return temp;
    }

    Point3d operator *(const Point3d &a)
    {
        Point3d temp;
        temp.x = this->x * a.x;
        temp.y = this->y * a.y;
        temp.z = this->z * a.z;

        return temp;
    }

    Point3d operator *(const double &koef)
    {
        Point3d temp;
        temp.x = this->x * koef;
        temp.y = this->y * koef;
        temp.z = this->z * koef;

        return temp;
    }

    friend ostream& operator <<(ostream &out, const Point3d &a);

    void setX(double x) {this->x = x;}
    void setY(double y) {this->y = y;}
    void setZ(double z) {this->z = z;}

    double getX(void) {return this->x;}
    double getY(void) {return this->y;}
    double getZ(void) {return this->z;}
};

ostream& operator <<(ostream &out, const Point3d &a)
{
    out << '(' << a.x << ", " << a.y << ", " << a.z <<')';

    return out;
}





class Triangle
{
public:
    array<Point3d, 3> triangle;

    friend ostream& operator <<(ostream &out, const Triangle &a);
};

ostream& operator <<(ostream &out, const Triangle &a)
{
    out << '{' << a.triangle[0] << ", " << a.triangle[1] << ", " << a.triangle[2] <<'}' << endl;

    return out;
}


void coneSegPoints(double rad, int segNum, vector<Point3d> &segPoints)
{
    double dt = M_PI*2/segNum;

    Point3d temp(0,0,0);

    for (int i = 0; i<segNum; i++)
    {
        temp.setX(rad * cos(dt*i));
        temp.setY(rad * sin(dt*i));
        segPoints.push_back(temp);
    }
}

void coneTriangNodes(double rad, double height, int segNum, vector<Triangle> &triangles)
{
    vector<Point3d> segPoints;
    coneSegPoints(rad, segNum, segPoints);

    Point3d heighPoint(0,0,height);

    Triangle temp;

    for (int i = 0; i < segNum; i++)
    {
        if(i == segNum-1)
        {
            temp.triangle.at(0) = segPoints.at(i);
            temp.triangle.at(1) = segPoints.at(0);
            temp.triangle.at(2) = heighPoint;
        }
        else
        {
            temp.triangle.at(0) = segPoints.at(i);
            temp.triangle.at(1) = segPoints.at(i+1);
            temp.triangle.at(2) = heighPoint;
        }

        triangles.push_back(temp);
    }
}


int main()
{
    vector<Triangle> triangles;
    coneTriangNodes(5, 10, 10, triangles);

    for (auto &elem : triangles)
    {
        cout << "Triangle " << elem;
    }

    return 0;
}

