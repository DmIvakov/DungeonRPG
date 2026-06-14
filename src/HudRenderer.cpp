#include "HudRenderer.h"
#include <string>
#include <sstream>
#include <stdexcept>

HudRenderer::HudRenderer()
    : statsText(font) 
{
    if (!font.openFromFile("assets/fonts/vecna/Vecna.otf")) {
        throw std::runtime_error("Failed to load font assets/fonts/vecna/Vecna.otf");
    }

    statsText.setCharacterSize(18);            
    statsText.setFillColor(sf::Color::White);   
    statsText.setPosition({15.f, 650.f});        
}


void HudRenderer::draw(sf::RenderWindow& window, const Player& player, const std::vector<Enemy>& enemies, const int currentFloor) {
    std::stringstream ss;
    ss << "FLOOR: " << currentFloor
    << "   |   HP: " << player.getHp() << "/" << player.getMaxHp()
    << "   |   XP: " << player.getExp()
    << "   |   LVL: " << player.getLevel()
    << "   |   ENEMIES: " << enemies.size();

    std::string hudString = ss.str();
    statsText.setString(hudString);

    window.draw(statsText);
}
