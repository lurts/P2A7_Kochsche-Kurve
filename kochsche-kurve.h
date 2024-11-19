#pragma once

#include <SFML/Graphics.hpp>

// Funktion, die die n�chste Iteration der Kurve bestimmt
sf::VertexArray koch(sf::VertexArray& Knoten);

// VertexArray drehen
sf::VertexArray rotate(sf::VertexArray& Knoten, double angle_deg, sf::Vector2f center);