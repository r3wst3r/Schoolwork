#ifndef _DEFINITIONS_H_
#define _DEFINITIONS_H_

#include <string>

const float SCREEN_WIDTH = 600.0f;
const float SCREEN_HEIGHT = 800.0f;
const std::string GAME_NAME = "My Game";

// File paths
const std::string GAME_BACKGROUND_FILEPATH = "resource/bitmaps/starfield.jpg";
const std::string HERO_SPACESHIP_FILEPATH = "resource/bitmaps/playerShip1_blue.png";
const std::string HERO_WEAPON_FILEPATH = "resource/bitmaps/laserBlue02.png";
const std::string ENEMY_WEAPON_LEVEL_1_FILEPATH = "resource/bitmaps/laserGreen03.png";
const std::string ENEMY_WEAPON_LEVEL_2_FILEPATH = "resource/bitmaps/laserGreen07.png";
const std::string ENEMY_WEAPON_LEVEL_3_FILEPATH = "resource/bitmaps/laserGreen16.png";
const std::string ENEMY_WEAPON_LEVEL_4_FILEPATH = "resource/bitmaps/laserRed13.png";
const std::string ENEMY_WEAPON_LEVEL_5_FILEPATH = "resource/bitmaps/laserRed01.png";
const std::string EXPLOSION_FILEPATH = "resource/bitmaps/Explosion_1.png";
const std::string HERO_EXPLOSION_FILEPATH = "resource/bitmaps/Explosion_2.png";
const std::string SMALL_EXPLOSION_FILEPATH = "resource/bitmaps/Small_Explosion.png";
const std::string HERO_WEAPON_SOUND_FILEPATH = "resource/sounds/sfx_laser1.ogg";
const std::string ENEMY_WEAPON_SOUND_FILEPATH = "resource/sounds/sfx_laser2.ogg";
const std::string ENEMY_EXPLOSION_SOUND_FILEPATH = "resource/sounds/Explosion_7.ogg";
const std::string HERO_EXPLOSION_SOUND_FILEPATH = "resource/sounds/Explosion_2.ogg";
const std::string SMALL_EXPLOSION_SOUND_FILEPATH = "resource/sounds/Small_Explosion.ogg";
const std::string REGULAR_FONT_FILEPATH = "resource/fonts/kenvector_future.ttf";
const std::string PLAYER_LIFE_FILEPATH = "resource/bitmaps/playerLife1_blue.png";
const std::string BUTTON_FILEPATH = "resource/bitmaps/buttonBlue.png";
/*
Music by Eric Matyas
www.soundimage.org
*/
const std::string GAME_BACKGROUND_MUSIC_FILEPATH = "resource/music/8-Bit-Mayhem.ogg";

const int NUM_ENEMY_SHIPS = 20;
const float GAMEOVER_PAUSE = 4.0f;

//const int MAX_ENEMY_SHIP_SPAWN = 5;

// Hero Ship Attributes
const int HERO_SPACESHIP_MAX_HULL_INTEGRITY = 100;
const int LIVES = 3;

// Speed
const float GAME_BACKGROUND_SPEED = 30.0f;
const float HERO_SPACESHIP_SPEED = 160.0f;
const float HERO_WEAPON_SPEED = 320.0f;
const float ENEMY_MISSILE_SLOW_SPEED = 180.0f;
const float ENEMY_MISSILE_MEDIUM_SPEED = 200.0f;
const float ENEMY_MISSILE_FAST_SPEED = 220.0f;

const float ENEMY_SPACESHIP_SLOW_SPEED = 35.0f;
const float ENEMY_SPACESHIP_MEDIUM_SPEED = 40.0f;
const float ENEMY_SPACESHIP_FAST_SPEED = 45.0f;

// Missile Damage
const int ENEMY_MISSILE_DAMAGE_LEVEL_1 = 4;
const int ENEMY_MISSILE_DAMAGE_LEVEL_2 = 8;
const int ENEMY_MISSILE_DAMAGE_LEVEL_3 = 12;
const int ENEMY_MISSILE_DAMAGE_LEVEL_4 = 16;
const int ENEMY_MISSILE_DAMAGE_LEVEL_5 = 20;

// Enemy Values (Points for destroying)
const int ENEMY_VALUE_LEVEL_1 = 25;
const int ENEMY_VALUE_LEVEL_2 = 50;
const int ENEMY_VALUE_LEVEL_3 = 75;
const int ENEMY_VALUE_LEVEL_4 = 100;
const int ENEMY_VALUE_LEVEL_5 = 150;

// Frequencies
const float HERO_WEAPON_FREQUENCY = 1.0f;
const float ENEMY_WAVE_FREQUENCY = 2.0f;
const float ENEMY_FIRE_FREQUENCY_LOW = 2.5f;
const float ENEMY_FIRE_FREQUENCY_MEDIUM = 1.75f;
const float ENEMY_FIRE_FREQUENCY_HIGH = 1.25f;

// Probabilities
const int ENEMY_SPAWN_PROBABILITY = 35;		// out of 100
const int ENEMY_WEAPON_FIRE_PROBABILITY_LOW = 4;
const int ENEMY_WEAPON_FIRE_PROBABILITY_MEDIUM = 8;
const int ENEMY_WEAPON_FIRE_PROBABILITY_HIGH = 12;
#endif // !_DEFINITIONS_H_

