#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>


class Object;
class Game;



class Scene
{
private:
	std::vector<Object*> m_objects;
	std::vector<sf::Texture*> m_textures;
	Game* m_game = nullptr;




public:
	bool sorted = false;

	Scene(){}
	Scene(Game* g);

	void SetGame(Game* g);
	Game* GetGame();


	Object* CreateObject();
	Object* CreateObject(sf::Texture* t);
	Object* CreateObject(std::string path);

	sf::Texture* CreateTexture(std::string path);
	sf::Texture* AddTexture(sf::Texture* tex);

	std::vector<Object*>& GetObjects();

	Object* AddObject(Object* o);

	virtual void Create() = 0;
	virtual void Update();
	virtual void Draw();

	virtual ~Scene();

};