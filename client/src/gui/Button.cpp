#include "Button.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

void Button::onMouseMove(int xPosition, int yPosition) {
	isHovering = rect.contains(xPosition, yPosition);
	if (isHovering) onHover();
}

void Button::onMouseClick() {
	if (isHovering) onClick();
}

void Button::setTopLeftCorner(int x, int y) {
	rect.left = x;
	rect.top = y;
	updateTextPosition();
}

void Button::setSize(int newWidth, int newHeight) {
	rect.width = newWidth;
	rect.height = newHeight;
	updateTextPosition();
}

void Button::setText(std::string newText) {
	text.setString(newText);
	updateTextPosition();
}

void Button::setFont(const sf::Font& font) {
	text.setFont(font);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(text);
	//TODO draw button background and border etc
}

void Button::updateTextPosition() {
	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
	text.setPosition(rect.width / 2, rect.height / 2);
}

void Button::setTextSize(unsigned int size) {
	text.setCharacterSize(size);
}

void Button::setTextColour(sf::Color color) {
	text.setFillColor(color);
	text.setOutlineColor(color);
}

void Button::setOnButtonHover(ButtonCallback callback) {
	onHover = callback;
}

void Button::setOnButtonClick(ButtonCallback callback) {
	onClick = callback;
}

