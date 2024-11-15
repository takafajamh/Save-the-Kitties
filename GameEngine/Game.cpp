#include "Game.hpp"
#include "Scene.hpp"
#include "Scenes.hpp"

void Game::ChangeScene(Scene* s)
{
	toChange = s;
}

void Game::Update()
{
#ifdef ShowColliders
	ColliderRects.clear();
#endif

	currentScene->Update();
}

void Game::Draw()
{
	window.clear(sf::Color(140,130,140));
	currentScene->Draw();

#ifdef ShowColliders
	for (sf::FloatRect& ir : ColliderRects)
	{
		sf::RectangleShape r;
		r.setSize(sf::Vector2f(ir.width, ir.height));
		r.setPosition(ir.left, ir.top);
		r.setOutlineColor(sf::Color::Blue);
		r.setOutlineThickness(3);
		r.setFillColor(sf::Color::Transparent);


		window.draw(r);
	}
#endif


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