#include "hud.h"
// #include <iostream>

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

  back.setOutlineThickness(2.5);
  back.setOutlineColor(sf::Color::White);

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
  float per = (meter.curr * 1.0) / ((meter.max - meter.min) * 1.0);
  // std::cerr <<"max: " << meter.max << "min: " << meter.min << "curr: " << meter.curr << "per: " << per << '\n';
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

void HUDItem::setValue(int val) {
  bar.set(val);
}
void HUDItem::changeRange(int maxValue, int currValue) {
  bar.set(maxValue, currValue);
}

void HUDItem::changeRange(int maxValue) {
  changeRange(maxValue, maxValue);
}

void HUDItem::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(label, states);
  target.draw(bar, states);
}

void HUD::setHealth(int hp) {
  health.setValue(hp);
}

void HUD::setHealthBar(int maxHP, int curr) {
  health.changeRange(maxHP, curr);
}

void HUD::setHealthBar(int maxHP) {
  setHealthBar(maxHP, maxHP);
}

void HUD::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(health, states);
}
