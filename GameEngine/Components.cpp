#include "Components.hpp"
#include "Scenes.hpp"



void PlayButton::onClick()
{
	GetScene()->GetGame()->ChangeScene(new MainScene());

}
void QuitButton::onClick()
{
	window.close();
}

template <class T>
void LevelButton<T>::onClick()
{
	GetScene()->GetGame()->ChamgeScene(new T());
}


void LaserObstacle::Do() 
{
	Holder->GetScene()->GetGame()->ChangeScene(new MainScene());
}
void DeadObstacle::Do()
{
	Holder->GetScene()->GetGame()->ChangeScene(new MainScene());
}

void winObstacle::Do()
{
	Holder->GetScene()->GetGame()->ChangeScene(new MainScene());
}

void ChangeToMenu::Go()
{
	GetScene()->GetGame()->ChangeScene(new Menu());
}