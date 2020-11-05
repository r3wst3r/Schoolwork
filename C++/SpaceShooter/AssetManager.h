#ifndef _ASSETMANAGER_H_
#define _ASSETMANAGER_H_

#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace ADS
{
	class AssetManager
	{
	public:
		AssetManager() {}
		~AssetManager() {}

		void loadTexture(std::string name, std::string fileName);
		sf::Texture& getTexture(std::string name);

		void loadFont(std::string name, std::string fileName);
		sf::Font& getFont(std::string name);

		void loadSound(std::string name, std::string fileName);
		sf::SoundBuffer& getSound(std::string name);

		void loadMusic(std::string name, std::string fileName);
		sf::Music& getMusic(std::string name);

	private:
		std::map<std::string, sf::Texture> mTextures;
		std::map<std::string, sf::Font> mFonts;
		std::map<std::string, sf::SoundBuffer> mSounds;
		std::map<std::string, sf::Music*> mMusic;

	};
}

#endif // !_ASSETMANAGER_H_

