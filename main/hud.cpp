#include "hud.h"

const std::string defaultFontFile = "font1.ttf";

sf::Font loadDefaultFont() {
  sf::Font font;
  font.loadFromFile(defaultFontFile);
  return font;
}

sf::Font defaultFont = loadDefaultFont();

Bar::Bar(sf::Color barColor, Point origin, Size size, Meter meter) : meter(meter) {
  back.setSize(size);
  back.setFillColor(sf::Color::Black);
  back.setPosition(origin);

  bar.setSize(size);
  bar.setFillColor(barColor);
  bar.setPosition(origin);

  // curr = 50;

  update();
}

HUDItem::HUDItem(std::string text, sf::Color barColor, Point origin, Size size, Meter meter) : label(text, defaultFont, 30), bar(barColor, origin , size, meter) {
  label.setPosition(origin);
  origin.x += 100;
  bar.setPosition(origin);
  label.setFillColor(sf::Color::White);
}

void Bar::setPosition(Point origin) {
  back.setPosition(origin);
  bar.setPosition(origin);
}

void Bar::update() {
  float per = (meter.max - meter.min) / meter.curr;
  sf::Vector2f barSize = back.getSize();
  barSize.x *= per;
  bar.setSize(barSize);
}

void Bar::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  // states.transform *= transform.getTransform();
  // target.draw(character, states);
  target.draw(back, states);
  target.draw(bar, states);
};

void HUDItem::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(label, states);
  target.draw(bar, states);
}

void HUD::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(health, states);
}
