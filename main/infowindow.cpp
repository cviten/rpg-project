#include "infowindow.h"

void InfoWindow::drawWindow() {
  ImGui::Begin("Info Window");
  //-------------------
  ImGui::Text("Player position:");
  ImGui::Text("x:"); ImGui::SameLine(); ImGui::TextUnformatted(std::to_string(playerPosition.x).c_str());
  ImGui::SameLine(); ImGui::Text(" "); ImGui::SameLine();
  ImGui::Text("y:"); ImGui::SameLine(); ImGui::TextUnformatted(std::to_string(playerPosition.y).c_str());
  //-------------------
  ImGui::Text(" ");
  //-------------------
  ImGui::Text("Player Status:");
  ImGui::Text("Name:"); ImGui::SameLine(); ImGui::TextUnformatted(plStatus.name.c_str());
  ImGui::Text("HP:"); ImGui::SameLine(); ImGui::TextUnformatted(std::to_string(plStatus.hp).c_str());
  ImGui::SameLine(); ImGui::Text("/"); ImGui::SameLine(); ImGui::TextUnformatted(std::to_string(plStatus.maxhp).c_str());
  ImGui::Text("Attack:"); ImGui::SameLine(); ImGui::TextUnformatted(std::to_string(plStatus.atk).c_str());

  ImGui::End();
}
