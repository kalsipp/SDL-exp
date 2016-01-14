#include "texture.hpp"
#include <cassert>
Texture::Texture(SDL_Renderer * rend) {
	m_log = new Logger(m_logfile_name);
	m_log->log("Texture constructed");
	m_sdl_renderer = rend;
}
Texture::~Texture() {
	free();
	TTF_CloseFont(m_font);
}

bool Texture::load_from_file(const std::string & path) {
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
		//->setBlendMode(SDL_BLENDMODE_BLEND);

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

bool Texture::load_from_rendered_text(const std::string & texture_text, SDL_Color text_color) {
	free();

	SDL_Surface * textsurface = TTF_RenderText_Solid(m_font, texture_text.c_str(), text_color);
	if (textsurface == nullptr) {
		m_log->log("Unable to render text surface! SDL_ttf Error: " + std::string(TTF_GetError()));
	}
	else {
		m_texture = SDL_CreateTextureFromSurface(m_sdl_renderer, textsurface);
		if (m_texture == nullptr) {
			m_log->log("Unable to create texture from rendered text! SDL Error: " + std::string(SDL_GetError()));
		}
		else {
			m_width = textsurface->w;
			m_height = textsurface->h;
		}
		SDL_FreeSurface(textsurface);
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

void Texture::render(int x, int y, SDL_Rect * clip) {
	SDL_Rect renderquad = { x,y,m_width, m_height };

	if (clip != nullptr) {
		renderquad.w = clip->w;
		renderquad.h = clip->h;
	}

	SDL_RenderCopy(m_sdl_renderer, m_texture, clip, &renderquad);
}

int Texture::get_height() {
	return m_height;
}
int Texture::get_width() {
	return m_width;
}

void Texture::set_color(Uint8 red, Uint8 green, Uint8 blue) {
	SDL_SetTextureColorMod(m_texture, red, green, blue);
}

void Texture::set_alpha(Uint8 alpha) {
	SDL_SetTextureAlphaMod(m_texture, alpha);
}
void Texture::set_blendmode(SDL_BlendMode blending) {
	SDL_SetTextureBlendMode(m_texture, blending);
}
void Texture::set_font(const std::string & path) {
	if (m_font != nullptr) {
		TTF_CloseFont(m_font);
		m_font = nullptr;
	}
	m_font = TTF_OpenFont(("fonts\\" + path).c_str(), 28);
	if (m_font == nullptr)
	{
		m_log->log("Failed to load lazy font! SDL_ttf Error: " + std::string(TTF_GetError()));
	}
}
