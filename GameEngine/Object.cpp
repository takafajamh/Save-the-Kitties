#include "Object.hpp"
#include "Component.hpp"
#include "Globals.hpp"

Component* Object::AddComponent(Component* c)
{
	c->Holder = this;
	GetComponents().push_back(c);
	return c;
}

void Object::Update()
{
	for (int i = 0; i<GetComponents().size(); i++)
	{
		Component* c = GetComponents().at(i);
		c->Update();

		if (c->KillMeIBegYou)
		{
			delete c;
			GetComponents().erase(GetComponents().begin() + i);
			i--;
		}
	}
}
void Object::Draw()
{
	window.draw(me);
}


void Object::SetScene(Scene* scene)
{
	m_scene = scene;
}
Scene* Object::GetScene()
{
	return m_scene;
}

std::vector<Component*>& Object::GetComponents()
{
	return m_components;
}

Object::Object(Scene* scene)
{
	SetScene(scene);
}
Object::~Object()
{
	auto& comp = GetComponents();

	for (int i = 0; i < comp.size(); i++)
	{
		if (comp[i] != nullptr)
		{
			delete comp[i];
			comp[i] = nullptr;
		}
	}
	GetComponents().clear();
}