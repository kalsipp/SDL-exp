#pragma once
#include <initializer_list>
#include <vector>
#include "texture.hpp"
struct Position
{
	Position(std::initializer_list<int> init) {
		std::vector<int> pos = init;
		x = pos[0];
		y = pos[1];
		z = pos[2];
	}
	int x = 0;
	int y = 0;
	int z = 0;
};
class Gameobject {
public:
	Gameobject(SDL_Renderer * renderer);
	~Gameobject();
	void move_to(int x, int y);
	void move_to(int x, int y, int z);
	void move(int dx, int dy, int dz = 0);
	void load_texture(const std::string & path);
private:
	Position * m_pos = nullptr;
	Texture * m_texture = nullptr;
	Logger * m_log = nullptr;
	SDL_Renderer * m_sdl_renderer = nullptr;
	std::string m_logfile_name = "gameobject.txt";
};