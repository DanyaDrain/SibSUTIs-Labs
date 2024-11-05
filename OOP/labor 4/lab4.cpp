#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <cstdlib>
using namespace std;

class Figure {
protected:
    float x, y;            
    float dx, dy;          
    float angle;
    float rotationSpeed;
public:
    Figure(float x = 0, float y = 0);

    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void move(float screenWidth, float screenHeight, float centerX, float centerY);
    virtual void rotate();
    virtual void input();
    virtual void randomize();
    ~Figure() {}
};

class Line : public Figure {
private:
    float x2, y2;
    float length;
public:
    Line(float x1, float y1, float x2, float y2);

    void calculateLength();
    float getLength() const;
    void draw(sf::RenderWindow& window) override;

    void move(float screenWidth, float screenHeight, float centerX, float centerY) override;
    void input() override;
    void randomize() override;
    void rotate() override;
};

class Square : public Figure {
protected:
    float size;
public:
    Square(float x, float y, float size);

    float getPerimeter() const;
    float getArea() const;
    void draw(sf::RenderWindow& window) override;

    void input() override;
    void randomize() override;
    void rotate() override;
};

class Rectangle : public Figure {
protected:
    float width, height;
public:
    Rectangle();
    Rectangle(float x, float y, float width, float height);

    float getPerimeter() const;
    float getArea() const;
    void draw(sf::RenderWindow& window) override;

    void input() override;
    void randomize() override;
    void rotate() override;
};