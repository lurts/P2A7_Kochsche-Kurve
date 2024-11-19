#include "kochsche-kurve.h"
#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>

const int window_height = 1000;
const int window_width = window_height;
const int padding = window_width / 20;
const int max_iterations = 5; // wird sehr schnell sehr gro�
const int delta_time = 1;
const bool snowflake = true;
const bool loop = true;
const bool rotation = false;

sf::VertexArray setupArray() {
    sf::VertexArray Knoten(sf::LineStrip);

    if (snowflake == true) {
        // drei punkte f�r dreieck bestimmen
        sf::Vector2f A(padding, window_height - 6 * padding);
        sf::Vector2f B(window_width - padding, window_height - 6 * padding);
        sf::Vector2f C(window_width / 2, padding);
        sf::Vector2f D = A;

        Knoten.append(D);
        Knoten.append(C);
        Knoten.append(B);
        Knoten.append(A);
    }
    else {
        // zwei punkte f�r einfache linie bestimmen
        Knoten.append(sf::Vector2f(padding, window_height - padding));
        Knoten.append(sf::Vector2f(window_width - padding, window_height - padding));
    }

    return Knoten;
}

int main() {
    sf::VertexArray Knoten(sf::LineStrip);

    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Kochsche Kurve");

    Knoten = setupArray();

    time_t last_run = time(NULL);
    unsigned int iterations = 0;

    // Haupt-Event-Loop
    while (window.isOpen())
    {
        // SFML even handler logik
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // l�sst die iterationen langsam nacheinander laufen statt alle auf einmal
        // sieht ganz cool aus
        // wenn loop = true wird das vertex array nach der letzten iteration zur�ckgesetzt
        if ((time(NULL) - last_run >= delta_time) && (iterations <= max_iterations)) {
            last_run = time(NULL);
            iterations++;

            Knoten = koch(Knoten);
            //std::cout << "Ran Koch iteration\n";
        }
        else if ((iterations > max_iterations) && (loop == true)) {
            Knoten = setupArray();
            iterations = 0;
        }

        // dreht die kochsche kurve. sieht auch ganz cool aus
        if (rotation) {
            Knoten = rotate(Knoten, 0.1f, sf::Vector2f(window_width / 2, window_height / 2));
        }

        // fenster aktualisieren und alles neu anzeigen
        window.clear();
        window.draw(Knoten);
        window.display();
    }
}