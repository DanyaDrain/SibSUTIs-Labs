#include <SFML/Graphics.hpp>
#include "tPoint.hpp"
#include <vector>

int main() {
    srand(static_cast<unsigned int>(time(0))); // Инициализация генератора случайных чисел

    const int numPoints = 100;
    const float screenWidth = 800;
    const float screenHeight = 600;

    std::vector<tPoint> points;
    for (int i = 0; i < numPoints; ++i) {
        // Инициализация точки со случайными параметрами
        points.emplace_back(rand() % static_cast<int>(screenWidth), rand() % static_cast<int>(screenHeight), static_cast<float>(rand() % 3 - 1), static_cast<float>(rand() % 3 - 1));
    }

    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Moving Points");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        // Движение и отрисовка точек
        for (auto& point : points) {
            point.moveLinear(screenWidth, screenHeight); // или point.moveRandom(screenWidth, screenHeight);
            point.draw(window);
        }

        window.display();
    }

    return 0;
}