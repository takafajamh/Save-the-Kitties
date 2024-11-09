#include "Game.hpp"
#include "Scene.hpp"
#include "Scenes.hpp"

void Game::ChangeScene(Scene* s)
{
	toChange = s;
}

void Game::Update()
{
	currentScene->Update();
}

void Game::Draw()
{
	window.clear(sf::Color(140,130,140));
	currentScene->Draw();
	window.display();
}
void Game::SceneChange()
{
	if (toChange == nullptr)
		return;

	delete currentScene;

	currentScene = toChange;
	toChange = nullptr;

	sf::View v = window.getDefaultView();
	window.setView(v);

	currentScene->SetGame(this);
	currentScene->Create();
	

}

void Game::Init()
{
	window.setFramerateLimit(120);

	currentScene = new Menu();
	currentScene->SetGame(this);
	currentScene->Create();
	

	music.openFromFile("Music/ost.ogg");
	music.setLoop(true);
	music.play();

	Run();
}