#include "infowindow.h"

void InfoWindow::drawWindow() {
  ImGui::Begin("Info Window");
  ImGui::Text("Player position:");
  ImGui::Text("x:"); ImGui::SameLine(); ImGui::TextUnformatted(std::to_string(playerPosition.x).c_str());
  ImGui::SameLine(); ImGui::Text(" "); ImGui::SameLine();
  ImGui::Text("y:"); ImGui::SameLine(); ImGui::TextUnformatted(std::to_string(playerPosition.y).c_str());

  ImGui::End();
}
