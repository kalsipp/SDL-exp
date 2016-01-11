#include "martinstestklass.hpp"
/*
//Temp Getting image to show
	pelle  = SDL_LoadBMP("media/test.bmp");
	if(pelle == nullptr) assert(false);
	pelle = SDL_ConvertSurface(pelle, m_sdl_surface->format, 0);
	SDL_BlitSurface( pelle, NULL, m_sdl_surface, NULL );
	SDL_UpdateWindowSurface(m_sdl_window);
*/
	void Martinstestklass::run(){
		//if(m_successful_init){
		bool running = true;
		SDL_Event events;
		SDL_StartTextInput();

		SDL_Surface * image = nullptr;
		load_image(image, "media/test.png");
		assert(image != nullptr);
		SDL_BlitSurface(image, 0, m_sdl_surface, 0);
		SDL_UpdateWindowSurface(m_sdl_window);
		while(running){

			while(SDL_PollEvent(&events) != 0){ 
				switch(events.type){

					case SDL_QUIT:
					running = false;
					break; 

					case SDL_TEXTINPUT:
					int x = 0, y = 0;
					    SDL_GetMouseState(&x, &y); //doesn't use this atm contains mousepos


					    if(events.text.text[0] == 'q'){
					    	running = false;
					    }
					}
				}


			//render();
			//g.update();
			}
			SDL_StopTextInput();
		//}
		}

		void Martinstestklass::render(){

		}
		void Martinstestklass::renderingtest(){

		}
		void Martinstestklass::load_image(SDL_Surface *& surf, std::string path){
			
			SDL_Surface * loaded = IMG_Load(path.c_str());
			if(loaded == nullptr){
				m_log->log( "Unable to load image "+path+" SDL Error: " + SDL_GetError() );
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
						
						if(!init_gl()){
							m_log->log("Unable to initialize OpenGL!");
							success = false;
						}
						
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
			m_log->log("Running destructor of " + m_window_name);
			SDL_DestroyWindow(m_sdl_window);
			SDL_Quit();
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
		