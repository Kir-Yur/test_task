#include <iostream>
#include <vector>
#include <cmath>

#define UNUSED(x) (void)(x)

#define EPS 0.0000001

using namespace std;

class Point
{
private:
    double x;
    double y;

public:
    Point()
    {
        this->x = 0;
        this->y = 0;
    }

    Point (double x, double y)
    {
        this->x = x;
        this->y = y;
    }

    Point operator +(const Point &a)
    {
        Point temp;
        temp.x = this->x + a.x;
        temp.y = this->y + a.y;

        return temp;
    }

    Point operator -(const Point &a)
    {
        Point temp;
        temp.x = this->x - a.x;
        temp.y = this->y - a.y;

        return temp;
    }

    Point operator *(const Point &a)
    {
        Point temp;
        temp.x = this->x * a.x;
        temp.y = this->y * a.y;

        return temp;
    }

    Point operator *(const double &koef)
    {
        Point temp;
        temp.x = this->x * koef;
        temp.y = this->y * koef;

        return temp;
    }

    friend ostream& operator <<(ostream &out, const Point &a);

    void setX(double x) {this->x = x;}

    void setY(double y) {this->y = y;}

    double getX(void) {return this->x;}

    double getY(void) {return this->y;}
};

ostream& operator <<(ostream &out, const Point &a)
{
    out << '(' << a.x << ',' << a.y << ')' << endl;

    return out;
}


class Curve
{
protected:
    vector<Point> points;

public:

    virtual Point diff(double t) = 0;
    virtual Point retPoint(double t) = 0;
};

class Line : public Curve
{
private:
    Point direction;
    Point startPoint;

public:
    Line(Point startPoint, Point direction, double t)
    {
        int i = 0;
        double t_l = 0;

        if(t >= 0)
        {
            while (t_l-EPS <= t)
            {
                this->points.push_back(startPoint + direction*t_l);
                t_l+=0.005;
                i++;
            }
        }
        else
        {
            while (t_l+EPS > t)
            {
                this->points.push_back(startPoint + direction*t_l);
                t_l-=0.005;
                i++;
            }
        }


        this->direction = direction;
        this->startPoint = startPoint;
    }

    Point diff(double t) override
    {
        UNUSED(t);
        return this->direction;
    }

    Point retPoint(double t) override
    {
        return startPoint + direction*t;
    }
};

class Elipse : public Curve
{
private:
    Point radius;
    Point startPoint;

public:
    Elipse(double radX, double radY, Point startPoint)
    {
        Point temp;
        int i = 0;
        double t = 0;

        if (radX >=0 && radY >=0)
        {
            while (t-EPS <= M_PI*2)
            {
                temp.setX((radX * cos(t)) + startPoint.getX());
                temp.setY((radY * sin(t)) + startPoint.getY());
                this->points.push_back(temp);
                t+=0.005;
                i++;
            }

            this->radius.setX(radX);
            this->radius.setY(radY);
            this->startPoint = startPoint;
        }
        else
        {
            cout << "invalid radius" << endl;
            exit(0);
        }
    }

    Point diff(double t) override
    {
        Point temp;

        temp.setX(this->radius.getX() * -1 * sin(t));
        temp.setY(this->radius.getY() * cos(t));

        return temp;
    }

    Point retPoint(double t) override
    {
        Point temp;

        temp.setX((this->radius.getX() * cos(t)) + this->startPoint.getX());
        temp.setY((this->radius.getY() * sin(t)) + this->startPoint.getY());

        return temp;
    }
};

int main()
{
    vector<Line> lines;
    lines.push_back(Line ({0,0}, {0,-1}, 1));
    lines.push_back(Line ({0,0}, {1,2}, 2));
    lines.push_back(Line ({0,0}, {1,2}, -2));
    lines.push_back(Line ({1,1}, {4,5}, 1));
    lines.push_back(Line ({0,0}, {1,1}, 0.5));
    lines.push_back(Line ({0,0}, {1,1}, 0));

    vector<Elipse> elipses;
    elipses.push_back(Elipse (2, 4, {1,1}));
    elipses.push_back(Elipse (2, 4, {0,0}));
    elipses.push_back(Elipse (3, 5, {1,1}));
    elipses.push_back(Elipse (0, 0, {0,0}));
    elipses.push_back(Elipse (1, 1, {0,0}));

    vector<Curve*> curves;

    for (auto &elem : lines)
    {
        curves.push_back(&elem);
    }
    for (auto &elem : elipses)
    {
        curves.push_back(&elem);
    }

    double t = M_PI_4;
    for (auto &elem : curves)
    {
        cout << "Point " << elem->retPoint(t);
        cout << "Differential " << elem->diff(t) << endl;
    }

    return 0;
}





