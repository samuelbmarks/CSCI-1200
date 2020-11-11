#include <string>
#include <vector>
#include "utilities.h"

using namespace std;

class Polygon {
    public:
        // Constructor
        Polygon(string name, std::vector<Point> vertices) : name_(name), vertices_(vertices) {
            // Not enough sides to be a polygon
            if (vertices_.size() < 3) {
                throw 1;
            }
        }
        
        // Destructor
        virtual ~Polygon() {
            vertices_.clear();
            name_ = "";
        }
        
        // Accessor
        string getName() const {
            return name_;
        }

        // Checks
        bool HasAllEqualSides() const {
            Vector temp(vertices_[0],vertices_[1]);
            double check = temp.Length();
            bool equal = true;
            
            for (unsigned int i = 0; i < vertices_.size() - 1; ++i) {
                temp = Vector(vertices_[i],vertices_[i+1]);
                if (!EqualSides(temp.Length(),check)) {
                    equal = false;
                }
            }
            
            return equal;
        }

        bool HasAllEqualAngles() const {
            double check = Angle(vertices_[vertices_.size()-1],vertices_[0],vertices_[1]);
            bool equal = true;
            
            for (unsigned int i = 0; i < vertices_.size() - 2; ++i){
                // For when it need to check last angle
                if (i == vertices_.size() - 3) {
                    if (!EqualAngles(check,Angle(vertices_[i],vertices_[i+1],vertices_[i+2]))) {
                        equal = false;
                    }
                    else if (!EqualAngles(check,Angle(vertices_[i+1],vertices_[i+2],vertices_[0]))) {
                        equal = false;
                    }
                }
                else {
                    if (!EqualAngles(check,Angle(vertices_[i],vertices_[i+1],vertices_[i+2]))) {
                        equal = false;
                    }
                }
            }
            
            return equal;
        }

        bool HasARightAngle() const {
            bool right = false;
            
            for (unsigned int i = 0; i < vertices_.size() - 2; ++i) {
                // For when it need to check last angle
                if (i == vertices_.size() - 3) {
                    if (RightAngle(Angle(vertices_[i],vertices_[i+1],vertices_[i+2]))) {
                        right = true;
                    }
                    else if (RightAngle(Angle(vertices_[i+1],vertices_[i+2],vertices_[0]))) {
                        right = true;
                    }
                    else if (RightAngle(Angle(vertices_[i+2],vertices_[0],vertices_[1]))) {
                        right = true;
                    }
                } 
                else {
                    if (RightAngle(Angle(vertices_[i],vertices_[i+1],vertices_[i+2]))) {
                        right = true;
                    }
                }
            }
            
            return right;
        }

    protected:
        string name_;
        std::vector<Point> vertices_;
};

class Triangle: public Polygon {
    public:
        Triangle(string name_, std::vector<Point> vertices_) : Polygon(name_, vertices_) {
            // Needs 3 sides
            if (vertices_.size() != 3) {
                throw 1;
            }
        }
};

class IsoscelesTriangle: virtual public Triangle {
    public:
        IsoscelesTriangle(string name_, std::vector<Point> vertices_) : Triangle(name_, vertices_) {
            Vector temp(vertices_[0],vertices_[1]);
            Vector temp2(vertices_[0],vertices_[2]);
            Vector temp3(vertices_[1],vertices_[2]);
            
            // Needs at least two equal sides
            if (!EqualSides(temp.Length(),temp2.Length())) {
                if (!EqualSides(temp.Length(),temp3.Length())) {
                    if (!EqualSides(temp2.Length(),temp3.Length())) {
                        throw 1;
                    }
                }
            }
        }
};

class RightTriangle: virtual public Triangle {
    public:
        RightTriangle(string name_, std::vector<Point> vertices_) : Triangle(name_, vertices_) {
            // Needs a right angle
            if(!HasARightAngle()) {
                throw 1;
            }
        }
};


class EquilateralTriangle: public IsoscelesTriangle {
    public:
        EquilateralTriangle(string name_, std::vector<Point> vertices_) : Triangle(name_, vertices_), IsoscelesTriangle(name_, vertices_) {
            // Need all equal sides
            if (!HasAllEqualSides()) {
                throw 1;
            }
        }
};

class IsoscelesRightTriangle: public IsoscelesTriangle, public RightTriangle {
    public:
        IsoscelesRightTriangle(string name_, std::vector<Point> vertices_) : Triangle(name_, vertices_), IsoscelesTriangle(name_, vertices_), RightTriangle(name_, vertices_) {}
};