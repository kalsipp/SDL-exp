#include "texture.hpp"

Texture::Texture(SDL_Renderer * rend) {
	m_log = new Logger(m_logfile_name);
	m_log->log("Texture constructed");
	m_sdl_renderer = rend;
}
Texture::~Texture() {
	free();
}

bool Texture::load_from_file(std::string path) {
	m_log->log("Loading new texture from file");
	free();
	SDL_Texture * new_texture = nullptr;
	SDL_Surface * loaded_surface = IMG_Load(path.c_str());
	if (loaded_surface == nullptr) {
		m_log->log("Unable to load image " + path + " SDL Error: " + SDL_GetError() + " (texture)");
	}
	else {
		//SDL_SetColorKey()
		new_texture = SDL_CreateTextureFromSurface(m_sdl_renderer, loaded_surface);
		if (new_texture == nullptr) {
			m_log->log("Unable to create texture from " + path + "! SDL Error: " + SDL_GetError());
		}
		else {
			m_width = loaded_surface->w;
			m_height = loaded_surface->h;
		}
		SDL_FreeSurface(loaded_surface);
		m_texture = new_texture;
	}
	return m_texture != nullptr;
}

void Texture::free() {
	if (m_texture != nullptr) {
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
		m_width = 0;
		m_height = 0;
	}
}

void Texture::render(int x, int y) {
	SDL_Rect renderquad = { x,y,m_width, m_height };
	SDL_RenderCopy(m_sdl_renderer, m_texture, 0, &renderquad);
}

int Texture::get_height() {
	return m_height;
}
int Texture::get_width() {
	return m_width;
}
