#ifndef TPOINT_HPP
#define TPOINT_HPP

#include <SFML/Graphics.hpp>
#include <cstdlib> // для rand()
#include <ctime> // для time()

class tPoint {
private:
    float x, y;          // Позиция точки
    float velocityX, velocityY; // Скорость движения по оси X и Y
    sf::Color color;     // Цвет точки

public:
    // Конструктор по умолчанию
    tPoint() : x(0), y(0), velocityX(0), velocityY(0), color(sf::Color::White) {
        // Инициализация случайным цветом
        color = sf::Color(rand() % 256, rand() % 256, rand() % 256);
    }

    // Конструктор с параметрами
    tPoint(float x, float y, float vX, float vY) : x(x), y(y), velocityX(vX), velocityY(vY) {
        color = sf::Color(rand() % 256, rand() % 256, rand() % 256);
    }

    // Геттеры и сеттеры
    float getX() const { return x; }
    float getY() const { return y; }
    sf::Color getColor() const { return color; }

    void setPosition(float newX, float newY) { x = newX; y = newY; }
    void setVelocity(float newVX, float newVY) { velocityX = newVX; velocityY = newVY; }

    // Метод для отрисовки точки
    void draw(sf::RenderWindow& window) {
        sf::CircleShape pointShape(5); // Размер точки
        pointShape.setPosition(x, y);
        pointShape.setFillColor(color);
        window.draw(pointShape);
    }

    // Метод для прямолинейного движения с отражением от стенок
    void moveLinear(float screenWidth, float screenHeight) {
        x += velocityX;
        y += velocityY;

        // Проверка на столкновение со стенами
        if (x < 0 || x > screenWidth) {
            velocityX = -velocityX; // Отразить по оси X
        }
        if (y < 0 || y > screenHeight) {
            velocityY = -velocityY; // Отразить по оси Y
        }
    }

    // Метод для случайного движения с отражением
    void moveRandom(float screenWidth, float screenHeight) {
        x += (rand() % 3 - 1); // Random move in x direction
        y += (rand() % 3 - 1); // Random move in y direction

        // Проверка на столкновение со стенами
        if (x < 0 || x > screenWidth) {
            x = std::max(0.0f, std::min(x, screenWidth)); // Ограничить в пределах
        }
        if (y < 0 || y > screenHeight) {
            y = std::max(0.0f, std::min(y, screenHeight)); // Ограничить в пределах
        }
    }
};

#endif // TPOINT_HPP