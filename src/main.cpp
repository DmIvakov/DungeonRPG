#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

int main() {
    // Initialize the window according to the SFML 3 standard
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Dungeon RPG - SFML 3 Success");

    // Initialize and play background music
    sf::Music music;
    if (!music.openFromFile("assets/audio/DungeonRPG.ogg")) {
        std::cout << "Failed to load audio file!" << std::endl;
    } else {
        music.setLooping(true); // In SFML 3 release, setLooping is used precisely
        music.play();
    }

    // Main loop of the graphics engine
    while (window.isOpen()) {
        // Correct event handling syntax for SFML 3 using std::optional
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        // Clear the screen with a dark gray color
        window.clear(sf::Color(30, 30, 30));
        
        // Display the rendered frame on the screen
        window.display();
    }

    return 0;
}
