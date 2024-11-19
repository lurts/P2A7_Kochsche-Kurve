#include "kochsche-kurve.h"
#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>

const int max_iterations = 5; // wird sehr schnell sehr gro�
const int delta_time = 1;
const bool snowflake = true;
const bool loop = true;
const bool rotation = false;

#ifdef _WIN32
// Windows-Pfad für die Schriftart
#define FONT "C:/Windows/Fonts/arial.ttf"
#elif __linux__
// Linux-Pfad für die Schriftart
#define FONT "/usr/share/fonts/google-noto/NotoSans-Black.ttf"
#endif

sf::VertexArray setupArray(unsigned int window_width, unsigned int window_height, unsigned int padding = 0, bool triangle = 0) {
    sf::VertexArray Knoten(sf::LineStrip);

    if (triangle == true) {
        // drei punkte f�r dreieck bestimmen
        // vierter punkt wird benötigt um dreieck zu schließen
        sf::Vector2f A(padding, window_height - 6 * padding);
        sf::Vector2f B(window_height - padding, window_height - 6 * padding);
        sf::Vector2f C(window_height / 2, padding);
        sf::Vector2f D = A;

        // offset damit schneeflocke in der mitte vom bildschirm angezeigt wird
        float offset = (window_width - window_height) / 2.0f;

        Knoten.append(sf::Vector2f(D.x + offset, D.y));
        Knoten.append(sf::Vector2f(C.x + offset, C.y));
        Knoten.append(sf::Vector2f(B.x + offset, B.y));
        Knoten.append(sf::Vector2f(A.x + offset, A.y));
    }
    else {
        // zwei punkte f�r einfache linie bestimmen
        Knoten.append(sf::Vector2f(padding, window_height - 2 * padding));
        Knoten.append(sf::Vector2f(window_width - padding, window_height - 2 * padding));
    }

    return Knoten;
}

int main() {
    sf::VertexArray Knoten(sf::LineStrip);

    // fenstergröße auf maximale auflösung des bildschirms setzen
    unsigned int window_width = sf::VideoMode::getDesktopMode().width;
    unsigned int window_height= sf::VideoMode::getDesktopMode().height;
    // padding damit ein wenig platz zum bildschirmrand bleibt
    unsigned int padding = window_height / 20;

    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Kochsche Kurve", sf::Style::Fullscreen);

    // declare font:
    /* --Lade Schrift aus Datei. */
    sf::Font font;
    if (!font.loadFromFile(FONT))
    {
        return -1;
    }

    // neues array anlegen
    Knoten = setupArray(window_width, window_height, padding, snowflake);

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

            // Esc soll fenster schließen und programm beenden
            if (event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
        }
        window.setFramerateLimit(30);

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
            Knoten = setupArray(window_width, window_height, padding, snowflake);
            iterations = 0;
        }

        // dreht die kochsche kurve. sieht auch ganz cool aus
        if (rotation) {
            Knoten = rotate(Knoten, 0.1f, sf::Vector2f(window_width / 2, window_height / 2));
        }

        sf::Text vertCount(std::to_string(Knoten.getVertexCount()), font);
        vertCount.setCharacterSize(20);
        vertCount.setFillColor(sf::Color::White);

        // fenster aktualisieren und alles neu anzeigen
        window.clear();
        window.draw(Knoten);
        window.draw(vertCount);
        window.display();
    }
}