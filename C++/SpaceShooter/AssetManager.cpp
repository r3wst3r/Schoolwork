#include "AssetManager.h"

void ADS::AssetManager::loadTexture(std::string name, std::string fileName)
{
	sf::Texture texture;

	if (texture.loadFromFile(fileName))
	{
		mTextures[name] = texture;
	}
}

sf::Texture & ADS::AssetManager::getTexture(std::string name)
{
	return mTextures.at(name);
}

void ADS::AssetManager::loadFont(std::string name, std::string fileName)
{
	sf::Font font;

	if (font.loadFromFile(fileName))
	{
		mFonts[name] = font;
	}
}

sf::Font & ADS::AssetManager::getFont(std::string name)
{
	return mFonts.at(name);
}

void ADS::AssetManager::loadSound(std::string name, std::string fileName)
{
	sf::SoundBuffer soundBuffer;

	if (soundBuffer.loadFromFile(fileName))
	{
		mSounds[name] = soundBuffer;
	}
}

sf::SoundBuffer & ADS::AssetManager::getSound(std::string name)
{
	return mSounds.at(name);
}

void ADS::AssetManager::loadMusic(std::string name, std::string fileName)
{
	sf::Music* music = new sf::Music;

	if (music->openFromFile(fileName))
	{
		mMusic[name] = music;
	}
}

sf::Music & ADS::AssetManager::getMusic(std::string name)
{
	return *mMusic.at(name);
}
