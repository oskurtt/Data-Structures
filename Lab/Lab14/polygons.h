#include <iostream>
#include <string>
#include <vector>
#include "utilities.h"

class Polygon{
    public:
    Polygon (const std::string& name_, const std::vector <Point>& points_) : name(name_), points(points_) {}
    virtual ~Polygon() {}
    std::string getName() {return name;}

    bool HasAllEqualSides(){
        double side_1, side_2;
        for (unsigned int i=0;i<points.size()-1;i++) {
            if (i==points.size()-2) {
                side_1 = DistanceBetween(points[i],points[i+1]);
                side_2 = DistanceBetween(points[i+1],points[0]);
            }
            else {
                side_1 = DistanceBetween(points[i],points[i+1]);
                side_2 = DistanceBetween(points[i+1],points[i+2]);
            }
            if (!EqualSides(side_1,side_2)) return false;
        }
    return true;
    }
    protected:
    std::string name;
    std::vector <Point> points;
};

class Triangle : public Polygon{
    public:
    Triangle (const std::string name_, const std::vector <Point>& points_)
    : Polygon (name_, points_){
        if (points.size() != 3) throw 0;
    }
};

class IsoscelesTriangle : public Triangle{
    public:
    IsoscelesTriangle (const std::string name_, const std::vector <Point>& points_)
    : Triangle (name_, points_){
        Vector v1(points[0], points[1]);
        Vector v2 (points[0], points[2]);
        Vector v3 (points[1], points[2]);
        if (!EqualSides(v1.Length(), v2.Length())){
            if (!EqualSides(v1.Length(), v3.Length())){
                if (!EqualSides(v2.Length(), v3.Length())){
                    throw 0;
                }
            }

        }
    }
};

class EquilateralTriangle : public IsoscelesTriangle {
    public:
    EquilateralTriangle (const std::string name_, const std::vector <Point>& points_)
    : IsoscelesTriangle (name_, points_){
        Vector v1(points[0], points[1]);
        Vector v2 (points[0], points[2]);
        Vector v3 (points[1], points[2]);
        if (!EqualSides(v1.Length(), v2.Length())) throw 0;
        else if (!EqualSides(v1.Length(), v3.Length())) throw 0;
        else if (!EqualSides(v2.Length(), v3.Length())) throw 0;
    }

};

class Quadrilateral : public Polygon{
    public:
    Quadrilateral (const std::string name_, const std::vector <Point>& points_)
    : Polygon (name_, points_){
        if (points.size() != 4) throw 0;
    }
};

class Rectangle : public Quadrilateral{
    public:
    Rectangle (const std::string name_, const std::vector <Point>& points_)
    : Quadrilateral (name_, points_){
        Vector v1(points[0], points[1]);
        Vector v2(points[1], points[2]);
        Vector v3(points[2], points[3]);
        Vector v4(points[3], points[0]);
        if (!EqualSides(v1.Length(), v3.Length())) throw 0;
        if (!EqualSides(v2.Length(), v4.Length())) throw 0;
    }

};

class Square : public Rectangle{
    public:
    Square (const std::string name_, const std::vector <Point>& points_)
    : Rectangle (name_, points_){
        Vector v1(points[0], points[1]);
        Vector v2(points[1], points[2]);
        Vector v3(points[2], points[3]);
        Vector v4(points[3], points[0]);
        if (!EqualSides(v1.Length(), v2.Length())) throw 0;
        if (!EqualSides(v2.Length(), v3.Length())) throw 0;
        if (!EqualSides(v3.Length(), v4.Length())) throw 0;
        if (!EqualSides(v4.Length(), v1.Length())) throw 0;
    }
};
