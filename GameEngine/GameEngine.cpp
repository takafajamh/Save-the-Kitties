#include <iostream>
#include <SFML/Graphics.hpp>

#include "Globals.hpp"
#include "Scene.hpp"
#include "Scenes.hpp"
#include "Game.hpp"


int main()
{

    window.create(sf::VideoMode(1280, 720),"Save the cats!");

    // Load the icon image
    sf::Image icon;
    if (!icon.loadFromFile("GPX/icon.png")) {

    }

    // Set the window icon
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());


    Game* g = new Game();
    g->Init();


}
