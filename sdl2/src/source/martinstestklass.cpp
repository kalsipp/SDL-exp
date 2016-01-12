#include "martinstestklass.hpp"

	void Martinstestklass::run(){
		bool running = true;
		SDL_Event events;
		SDL_StartTextInput();
		Texture texture(m_sdl_renderer);
		assert(texture.load_from_file("media\\test.png"));
		texture.set_blendmode(SDL_BLENDMODE_BLEND);
		int x = 0; int y = 0;

		while(running){

			while(SDL_PollEvent(&events) != 0){ 
				switch(events.type){

					case SDL_QUIT:
					running = false;
					break; 

					case SDL_TEXTINPUT:
					    if(events.text.text[0] == 'q'){
					    	running = false;
					    }
					}
				}
				SDL_GetMouseState(&x, &y);
				SDL_SetRenderDrawColor(m_sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(m_sdl_renderer);
				SDL_Rect clipper = { 10, 10, 200, 200 };
				texture.set_alpha(x);
				texture.set_color(x, y, x);
				texture.render(x - texture.get_width()/2, y - texture.get_height()/2, &clipper);
				SDL_RenderPresent(m_sdl_renderer);
			}
			SDL_StopTextInput();
		}

		void Martinstestklass::render(){
			/*
			SDL_RenderClear(m_sdl_renderer);
			SDL_RenderCopy(m_sdl_renderer, image, 0, 0);
			SDL_RenderPresent(m_sdl_renderer);
			*/
		}
		void Martinstestklass::renderingtest(){

		}

		void Martinstestklass::load_texture(SDL_Texture *& text, std::string path) {
			text = nullptr;
			SDL_Surface * loaded = IMG_Load(path.c_str());
			if (loaded == nullptr) {
				m_log->log("Unable to load image " + path + " SDL Error: " + SDL_GetError() + " (texture)");
			}
			else {
				text = SDL_CreateTextureFromSurface(m_sdl_renderer, loaded);
				if (text == nullptr) {
					m_log->log("Unable to create texture from " + path + "! SDL Error: " + SDL_GetError());
				}
				SDL_FreeSurface(loaded);
			}
		}

		void Martinstestklass::load_image(SDL_Surface *& surf, std::string path){
			
			SDL_Surface * loaded = IMG_Load(path.c_str());
			if(loaded == nullptr){
				m_log->log( "Unable to load image to surface "+path+" SDL Error: " + SDL_GetError() );
			}else{
				surf = SDL_ConvertSurface(loaded, m_sdl_surface->format, 0);
				if(surf == nullptr){
					m_log->log("Unable to optimize image " + path + "! SDL Error: " + SDL_GetError());
				}else{
					m_log->log("Loading of "+ path+ " successful");
				}
				SDL_FreeSurface(loaded);
			}
		}
		Martinstestklass::Martinstestklass(){
			m_log = new Logger(m_logfile_name);
			if(init()){
				
				if(init_gl()){
					m_successful_init = true;
				}else{
					m_log->log("Could not initialize OpenGL.");
				}
				
			}else {
				m_log->log("Could not initialize SDL.");
			}
		}

		Martinstestklass::~Martinstestklass(){
			unload();
			delete m_log;
		}


		bool Martinstestklass::init(){


			m_log->log("Initializing of " + m_window_name);
			bool success = true;
			if(SDL_Init(SDL_INIT_VIDEO) < 0){
				m_log->log( "SDL could not initialize! SDL_Error: " + std::string(SDL_GetError()) );
				success = false;
			}else{

				if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
				{
					m_log->log("Warning: Linear texture filtering not enabled!");
				}

				m_sdl_window = SDL_CreateWindow(
					m_window_name.c_str(),
					SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED,
					m_screen_width,
					m_screen_height,
					SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
				if(m_sdl_window  == nullptr){
					m_log->log( "SDL could not initialize! SDL_Error: " + std::string(SDL_GetError()) );
					success = false;
				}else{
					m_sdl_glcontext = SDL_GL_CreateContext(m_sdl_window);
					if(m_sdl_glcontext == 0){
						m_log->log("OpenGL context could not be created! SDL Error: " + std::string(SDL_GetError()));
						success = false;
					}else{
						if(SDL_GL_SetSwapInterval(1) < 0){
							m_log->log("Warning: Unable to set VSync! SDL Error: " + std::string(SDL_GetError()) );
							success = false;
						}
						/*
						if(!init_gl()){
							m_log->log("Unable to initialize OpenGL!");
							success = false;
						}
						*/
						
					}
					m_sdl_surface = SDL_GetWindowSurface(m_sdl_window);

					m_sdl_renderer = SDL_CreateRenderer(m_sdl_window, -1, SDL_RENDERER_ACCELERATED);
					if(m_sdl_renderer == nullptr){
						m_log->log("Renderer could not be created! SDL Error: " + std::string(SDL_GetError()) );
						success = false;
					}else{
						SDL_SetRenderDrawColor(m_sdl_renderer, 0xff, 0xff, 0xff, 0xff);
						int img_flags = IMG_INIT_PNG;
						if(!(IMG_Init(img_flags) & img_flags)){
							m_log->log("SDL_image could not initialize! SDL_image Error: " + std::string(IMG_GetError()) );
							success = false;
						}
					}

				}
			}
			m_log->log("Done initializing of " + m_window_name);
			return success;
		}

		void Martinstestklass::unload(){
			m_log->log("Unloading all components " + m_window_name);
			SDL_DestroyRenderer(m_sdl_renderer);
			SDL_DestroyWindow(m_sdl_window);
			SDL_Quit();
			IMG_Quit();
		}
		
		bool Martinstestklass::init_gl(){
			bool success = true;
			GLenum error = GL_NO_ERROR;
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			error = glGetError();
			if(error != GL_NO_ERROR){
				success = false;
			}

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			error = glGetError();
			if(error != GL_NO_ERROR){
				success = false;
			}

			glClearColor(0.f, 0.f, 0.f, 1.f);

			error = glGetError();
			if(error != GL_NO_ERROR){
				success = false;
			}

			return success;
		}
		