#include "gameobject.hpp"

Gameobject::Gameobject(SDL_Renderer * renderer) {
	m_log = new Logger(m_logfile_name);
	m_log->log("Created new gameobject");
	m_pos = new Position { 0,0,0 };
	m_sdl_renderer = renderer;
	m_texture = new Texture(m_sdl_renderer);
}
Gameobject::~Gameobject() {
	m_log->log("Running destructor of gameobject");
	delete m_log;
	delete m_pos;
}
void Gameobject::load_texture(const std::string & path) {
	m_log->log("Gameobject loading texture from " + path );
	if (!m_texture->load_from_file(path)) {
		m_log->log("Gameobject failed loading texture from " + path);
	}
}
void Gameobject::move_to(int x, int y) {
	move_to(x, y, m_pos->z);
}
void Gameobject::move_to(int x, int y, int z) {
	m_pos->x = x;
	m_pos->y = y;
	m_pos->z = z;
}

void Gameobject::move(int dx, int dy, int dz) {
	m_pos->x += dx;
	m_pos->y += dy;
	m_pos->z += dz;
}