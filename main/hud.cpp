#include "hud.h"


Bar::Bar(sf::Color barColor, Rect rect, Meter meter) {
  back.setSize(rect.size);
  back.setFillColor(sf::Color::Black);
  back.setPosition(rect.position);

  bar.setSize(rect.size);
  bar.setFillColor(barColor);
  bar.setPosition(rect.point);

  update();
}

void Bar::update() {
  int per = (max - min) / curr;
  Size barSize = back.getSize();
  barSize.x *= per;
  bar.setSize(barSize);
}

void Bar::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  // states.transform *= transform.getTransform();
  // target.draw(character, states);
  target.draw(back, states);
  target.draw(bar, states);
};
