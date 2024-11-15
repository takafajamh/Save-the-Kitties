#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#define tell(x) std::cout<<x<<std::endl
#define say(x) std::cout<<x

#define ShowCollidersOff
#define MapLoaderOff
#define StateLevelOff


#ifdef StateLevel
inline bool ShowedColliders = false;;
#endif // StateLevel


#ifdef ShowColliders
inline std::vector<sf::FloatRect> ColliderRects;
#endif // ShowColliders



const inline bool F_MemoryEff = true;

inline sf::RenderWindow window;
inline float dt;

inline int RandomInt(int min, int max)
{
	return min + std::rand() % (max - min + 1);
}

template<typename T>
T clamp(T value, T min, T max)
{
	return std::max(min, std::min(value, max));
}

inline float Vec2fDistance(const sf::Vector2f& point)
{
	return std::sqrt(point.x * point.x + point.y * point.y);
}

inline sf::Vector2f normalize(const sf::Vector2f& vec) {
    float length = std::sqrt(vec.x * vec.x + vec.y * vec.y);
    if (length != 0.0f) {
        return sf::Vector2f(vec.x / length, vec.y / length);
    }
    return vec; // return the original vector if length is zero to avoid division by zero
}