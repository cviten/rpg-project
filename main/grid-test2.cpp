// #include <iostream>
// #include <stdexcept>

#include "gamemanager.h"

int main(int argc, char const *argv[]) {
  sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "Grid movement", sf::Style::Titlebar | sf::Style::Close);
  ImGui::SFML::Init(window);
  sf::Clock clock;
  // float deltaTime;

  // Map map;
  // map.setPosition(100,100);

  GameManager gm;

  while (window.isOpen())
  {
    // gm.setup();

    sf::Event event;
    while (window.pollEvent(event))
    {
      ImGui::SFML::ProcessEvent(event);

      if ((event.type == sf::Event::Closed) || ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))) {
        window.close();
      }
      if ((event.type == sf::Event::KeyPressed) ) {
        // std::cout << "In key event" << '\n';
        gm.readEventKey(event.key.code);
      }
      // if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space)) {
      //   gm.readEventKey(event.key.code);
      // }
    }
    ImGui::SFML::Update(window, clock.restart());
    // deltaTime = clock.restart().asSeconds();
    // gm.process();
    // gm.process(deltaTime);

    gm.postTurn();
    window.clear();


    // window.draw(gm);
    window.draw(gm);
    gm.drawInfo();
    ImGui::SFML::Render(window);

    window.display();
    // gm.cleanup();
  }

  return 0;
}
