#include "lab4.hpp"

Figure::Figure(float x, float y) : x(x), y(y), dx(0.5 / 50), dy(0.5 / 50), angle(0), rotationSpeed(0.5 / 50) {}

void Figure::move(float screenWidth, float screenHeight, float centerX, float centerY) {
    x += dx;
    y += dy;

    if (x <= 0 || x >= screenWidth) dx = -dx;
    if (y <= 0 || y >= screenHeight) dy = -dy;
}

void Figure::rotate() {
    angle += rotationSpeed;
}

void Figure::input() {
    cout << "Введите координаты (x, y) и скорости по осям (dx, dy): ";
    cin >> x >> y >> dx >> dy;
    dx /= 50;
    dy /= 50;
}

void Figure::randomize() {
    x = rand() % 800;
    y = rand() % 600;
    dx = ((rand() % 3 + 1) * 0.5f * ((rand() % 2) ? 1 : -1)) / 50;
    dy = ((rand() % 3 + 1) * 0.5f * ((rand() % 2) ? 1 : -1)) / 50;
    rotationSpeed = ((rand() % 2 + 1) * 0.5f) / 50;
}

Line::Line(float x1, float y1, float x2, float y2) : Figure(x1, y1), x2(x2), y2(y2) {
    calculateLength();
}

void Line::calculateLength() {
    length = sqrt(pow(x2 - x, 2) + pow(y2 - y, 2));
}

float Line::getLength() const {
    return length;
}

void Line::draw(sf::RenderWindow& window) {
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(x, y)),
        sf::Vertex(sf::Vector2f(x2, y2))
    };
    window.draw(line, 2, sf::Lines);
}

void Line::move(float screenWidth, float screenHeight, float centerX, float centerY) {
    float lineCenterX = (x + x2) / 2;
    float lineCenterY = (y + y2) / 2;

    lineCenterX += dx;
    lineCenterY += dy;

    float halfLength = length / 2;
    float angleRadians = angle * 3.14159265358979323846 / 180.0;

    x = lineCenterX + halfLength * cos(angleRadians);
    y = lineCenterY + halfLength * sin(angleRadians);
    x2 = lineCenterX - halfLength * cos(angleRadians);
    y2 = lineCenterY - halfLength * sin(angleRadians);

    float distanceX = lineCenterX - centerX;
    float distanceY = lineCenterY - centerY;
    if (abs(distanceX) > screenWidth / 2) dx = -dx;
    if (abs(distanceY) > screenHeight / 2) dy = -dy;
}

void Line::rotate() {
    angle += rotationSpeed;
}

void Line::input() {
    cout << "Введите координаты начала (x, y) и конца линии (x2, y2): ";
    cin >> x >> y >> x2 >> y2;
    calculateLength();
}

void Line::randomize() {
    Figure::randomize();
    x2 = rand() % 800;
    y2 = rand() % 600;
    calculateLength();
}

Square::Square(float x, float y, float size) : Figure(x, y), size(size) {}

float Square::getPerimeter() const {
    return 4 * size;
}

float Square::getArea() const {
    return size * size;
}

void Square::draw(sf::RenderWindow& window) {
    sf::RectangleShape square(sf::Vector2f(size, size));
    square.setPosition(x + size / 2, y + size / 2);
    square.setRotation(angle);
    square.setFillColor(sf::Color::Green);
    window.draw(square);
}

void Square::input() {
    Figure::input();
    cout << "Введите размер стороны квадрата: ";
    cin >> size;
}

void Square::randomize() {
    Figure::randomize();
    size = rand() % 100 + 50;
}

void Square::rotate() {
    Figure::rotate();
}

Rectangle::Rectangle() : Figure(), width(100), height(50) {}

Rectangle::Rectangle(float x, float y, float width, float height) 
    : Figure(x, y), width(width), height(height) {}

float Rectangle::getPerimeter() const {
    return 2 * (width + height);
}

float Rectangle::getArea() const {
    return width * height;
}

void Rectangle::draw(sf::RenderWindow& window) {
    sf::RectangleShape rectangle(sf::Vector2f(width, height));
    rectangle.setPosition(x - width / 2, y - height / 2);
    rectangle.setRotation(angle);
    rectangle.setFillColor(sf::Color::Blue);
    window.draw(rectangle);
}

void Rectangle::input() {
    Figure::input();
    cout << "Введите ширину и высоту прямоугольника: ";
    cin >> width >> height;
}

void Rectangle::randomize() {
    Figure::randomize();
    width = rand() % 100 + 50;
    height = rand() % 100 + 50;
}

void Rectangle::rotate() {
    Figure::rotate();
}
