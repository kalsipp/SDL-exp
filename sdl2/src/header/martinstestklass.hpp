#pragma once
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <string>
#include <cassert>
#include <iostream> 

#include "logger.hpp"
#include "texture.hpp"
class Martinstestklass{
public:
	Martinstestklass();
	~Martinstestklass();
	bool init();
	bool init_gl();
	void unload();
	void run();
	void render();
	void load_image(SDL_Surface *& surf, std::string path);
	void load_texture(SDL_Texture *& text, std::string path);
	void renderingtest();
	bool m_successful_init = true;
	int m_screen_width = 640;
	int m_screen_height = 480;
	SDL_Window * m_sdl_window = nullptr;
	SDL_Surface * m_sdl_surface = nullptr;
	SDL_Renderer * m_sdl_renderer = nullptr;
	SDL_GLContext m_sdl_glcontext;
	std::string m_window_name = "Martins testfonster";
	std::string m_logfile_name = "log_martinstester.txt";
	Logger * m_log;

};