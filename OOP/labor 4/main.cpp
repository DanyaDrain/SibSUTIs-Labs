#include "lab4.hpp"

int getUserChoice(const string& figureName) {
    int choice;
    cout << "Выберите способ инициализации для " << figureName << ":" << endl;
    cout << "1. Ввод с клавиатуры" << endl;
    cout << "2. Случайные значения" << endl;
    cout << "Ваш выбор: ";
    cin >> choice;
    return choice;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Graphics Figures");
    float centerX = window.getSize().x / 2;
    float centerY = window.getSize().y / 2;

    Line line(100, 100, 300, 300);
    Square square(400, 300, 100);
    Rectangle rect(600, 400, 150, 80);

    int choice = getUserChoice("линии");
    if (choice == 1) {
        cout << "Введите параметры для линии:" << endl;
        line.input();
    } else {
        cout << "Используются случайные значения для линии." << endl;
        line.randomize();
    }
    cout << "Длина линии: " << line.getLength() << endl;

    choice = getUserChoice("квадрата");
    if (choice == 1) {
        cout << "Введите параметры для квадрата:" << endl;
        square.input();
    } else {
        cout << "Используются случайные значения для квадрата." << endl;
        square.randomize();
    }
    cout << "Периметр квадрата: " << square.getPerimeter() << endl;
    cout << "Площадь квадрата: " << square.getArea() << endl;

    choice = getUserChoice("прямоугольника");
    if (choice == 1) {
        cout << "Введите параметры для прямоугольника:" << endl;
        rect.input();
    } else {
        cout << "Используются случайные значения для прямоугольника." << endl;
        rect.randomize();
    }
    cout << "Периметр прямоугольника: " << rect.getPerimeter() << endl;
    cout << "Площадь прямоугольника: " << rect.getArea() << endl;

    Rectangle* rectArray = new Rectangle[3];
    for (int i = 0; i < 3; ++i) {
        cout << "Выберите способ инициализации для прямоугольника " << i + 1 << ":" << endl;
        choice = getUserChoice("прямоугольника " + to_string(i + 1));
        if (choice == 1) {
            rectArray[i].input();
        } else {
            rectArray[i].randomize();
        }
        cout << "Прямоугольник " << i + 1 << ": Периметр = " << rectArray[i].getPerimeter()
                  << ", Площадь = " << rectArray[i].getArea() << endl;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        line.move(800, 600, centerX, centerY);
        square.move(800, 600, centerX, centerY);
        rect.move(800, 600, centerX, centerY);

        line.rotate();
        square.rotate();
        rect.rotate();

        line.draw(window);
        square.draw(window);
        rect.draw(window);

        for (int i = 0; i < 3; ++i) {
            rectArray[i].move(800, 600, centerX, centerY);
            rectArray[i].rotate();
            rectArray[i].draw(window);
        }

        window.display();
    }

    delete[] rectArray;

    return 0;
}
