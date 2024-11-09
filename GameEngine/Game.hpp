#pragma once

#include "Globals.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


// Music has to be moved and well done


class Scene;

class Game
{
private:
	Scene* currentScene = nullptr;
	sf::Clock dtClock;
	Scene* toChange = nullptr;

	void Update();

	void Draw();

	void dtTimer()
	{
		sf::Time dtTime = dtClock.restart();
		dt = dtTime.asSeconds();
	}

	void SFMLEvents()
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
	}

	void SceneChange();

	void Run()
	{
		while (window.isOpen())
		{
			dtTimer();
			SFMLEvents();

			if (currentScene == nullptr)
				continue;

			if (window.hasFocus())	
				Update();
			
			Draw();

			SceneChange();

		}
	}

public:
	sf::Music music;

	void Init();

	void ChangeScene(Scene* n);

};