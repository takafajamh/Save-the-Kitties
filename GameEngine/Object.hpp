#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Layers.hpp"

class Scene;
class Component;



class Object
{
protected:
	Scene* m_scene = nullptr;
	std::vector<Component*> m_components;


public:

	Object(){}
	Object(Scene* scene);

	void SetScene(Scene* scene);
	Scene* GetScene();

	std::vector<Component*>& GetComponents();
	Component* AddComponent(Component* c);

	Layer Layer = Layer::Player;
	bool KillMePlease = false;


	sf::Sprite me;


	virtual void Update();
	virtual void Draw();
	virtual ~Object();
};