#pragma once

#include <SFML/graphics.hpp>

// Funktion, die die nächste Iteration der Kurve bestimmt
sf::VertexArray koch(sf::VertexArray& Knoten);

// VertexArray drehen
sf::VertexArray rotate(sf::VertexArray& Knoten, double angle_deg, sf::Vector2f center);