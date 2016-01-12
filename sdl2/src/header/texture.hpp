#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "logger.hpp"
class Texture {
public:
	Texture(SDL_Renderer *);
	~Texture();
	bool load_from_file(std::string path);
	void free();
	void render(int x, int y);
	int get_width();
	int get_height();

private:
	SDL_Texture * m_texture = nullptr;
	int m_width = 0;
	int m_height = 0;
	Logger * m_log = nullptr;
	SDL_Renderer * m_sdl_renderer;
	std::string m_logfile_name = "log_martinstester.txt";

};