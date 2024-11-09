#include "Scene.hpp"
#include "Object.hpp"
#include "Globals.hpp"


struct less_than_key
{
	inline bool operator() (const Object* ob1, const Object* ob2)
	{
		return (ob1->Layer < ob2->Layer);
	}
};

void Scene::Draw()
{
	if (m_objects.size() == 0)
		return;

	if (!sorted)
		std::sort(m_objects.begin(), m_objects.end(), less_than_key());

	sorted = true;

	for (auto o : m_objects)
	{
		o->Draw();
	}
}

void Scene::Update()
{
	for (size_t i = 0; i < m_objects.size(); i++)
	{
		m_objects[i]->Update();

		if (m_objects[i]->KillMePlease)
		{
			delete m_objects[i];
			m_objects[i] = nullptr;
			m_objects.erase(m_objects.begin() + i);
			i--;
		}
	}

}

Object* Scene::AddObject(Object* o)
{
	o->SetScene(this);
	GetObjects().push_back(o);
	return o;
}
Object* Scene::CreateObject()
{
	Object* o = new Object();
	AddObject(o);
	return o;
}
Object* Scene::CreateObject(sf::Texture* tex)
{
	Object* o = new Object();
	o->me.setTexture(*tex);
	AddObject(o);
	return o;
}
Object* Scene::CreateObject(std::string path)
{
	sf::Texture* tex = CreateTexture(path);

	Object* o = new Object();
	o->me.setTexture(*tex);
	AddObject(o);
	return o;
}

std::vector<Object*>& Scene::GetObjects()
{
	sorted = false;
	return m_objects;
}

sf::Texture* Scene::CreateTexture(std::string path)
{
	sf::Texture* tex = new sf::Texture();
	tex->loadFromFile(path);
	AddTexture(tex);
	return tex;
}
sf::Texture* Scene::AddTexture(sf::Texture* tex)
{
	m_textures.push_back(tex);
	return tex;
}


void Scene::SetGame(Game* g)
{
	m_game = g;
}
Game* Scene::GetGame()
{
	return m_game;
}

Scene::Scene(Game* g)
{
	m_game = g;
}

Scene::~Scene()
{
	for (Object* o : m_objects)
	{
		delete o;
	}
	m_objects.clear();

	for (auto o : m_textures)
	{
		delete o;
	}
	m_textures.clear();
}
