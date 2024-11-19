#include "kochsche-kurve.h"
#include <SFML/Graphics.hpp>
#include <cmath>

sf::VertexArray koch(sf::VertexArray& Knoten) {
	sf::VertexArray output(sf::LineStrip);

	for (int i = 0; i < Knoten.getVertexCount() - 1; i++) {
		// aktuellen punkt der liste anh�ngen
		output.append(Knoten[i]);

		// linie aus aktuellem und n�chsten punkt in der liste bilden
		sf::Vector2f X = Knoten[i].position;
		sf::Vector2f Y = Knoten[i + 1].position;

		// drittel punkte A und B bestimmen
		sf::Vector2f delta = Y - X;
		sf::Vector2f A = X + 1.0f * delta / 3.0f;
		sf::Vector2f B = X + 2.0f * delta / 3.0f;

		// mittelpunkt M bestimmen
		sf::Vector2f M = X + delta / 2.0f;

		// l�nge der strecke XA bestimmen
		double a = std::sqrt(pow(A.x - X.x, 2) + pow(A.y - X.y, 2));

		// h�he des neuen dreiecks
		double h = std::sqrt(3) / 2 * a;

		// zweiten vektor orthogonal zum ersten erstellen
		delta = sf::Vector2f(delta.y, -delta.x);
		// vektor normieren
		double deltaLen = sqrt(pow(delta.x, 2) + pow(delta.y, 2));
		delta = sf::Vector2f(1 / deltaLen * delta.x, 1 / deltaLen * delta.y);
		// vektor auf l�nge h bringen
		delta = sf::Vector2f(h * delta.x, h * delta.y);

		// neuen punkt C bestimmen
		sf::Vector2f C = M + delta;

		output.append(A);
		output.append(C);
		output.append(B);
	}

	// letzten punkt in der liste am vertex array anh�ngen
	output.append(Knoten[Knoten.getVertexCount() - 1]);

	return output;
}

sf::VertexArray rotate(sf::VertexArray& Knoten, double angle_deg, sf::Vector2f center) {
	sf::Transform transform;
	sf::VertexArray rotated(sf::LineStrip);

	// mittelpunkt und winkel f�r transform festlegen
	transform.translate(center);
	transform.rotate(angle_deg);
	transform.translate(-center);

	// transform anwenden
	for (std::size_t i = 0; i < Knoten.getVertexCount(); ++i) {
		rotated.append(transform.transformPoint(Knoten[i].position));
	}

	return rotated;
}