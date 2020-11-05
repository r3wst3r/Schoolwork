#include "Frame.h"

ADS::Frame::Frame(sf::Vector2i size, sf::Color color) : texture(&getDummyTexture()), area(sf::Vector2i(0, 0), size), color(color)
{
}

ADS::Frame::Frame(sf::Texture const & texture, sf::IntRect area, sf::Color color) : texture(&texture), area(area), color(color)
{
}

sf::Texture & ADS::Frame::getDummyTexture()
{
	return Singleton<DummyTexture>::getInstance().texture;
}
