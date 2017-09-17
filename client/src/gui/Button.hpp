#pragma once

#include <SFML/Graphics/Text.hpp>

typedef std::function<void()> ButtonCallback;

class Button : public sf::Drawable {
	sf::Text text;
	sf::Rect<int> rect{};
	bool isHovering = false;

	ButtonCallback onHover = [](){};
	ButtonCallback onClick = [](){};

	void updateTextPosition();
public:
	void onMouseMove(int xPosition, int yPosition);
	void onMouseClick();

	void setOnButtonHover(ButtonCallback callback);
	void setOnButtonClick(ButtonCallback callback);

	void setTopLeftCorner(int x, int y);
	void setSize(int newWidth, int newHeight);

	void setText(std::string newText);
	void setTextSize(unsigned int size);
	void setTextColour(sf::Color color);
	void setFont(const sf::Font& font);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

