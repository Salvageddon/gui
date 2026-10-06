# gui
XML GUI library for C.

# warning
This library is under development. It BARELY has the *gui* part yet.

# instruction
1. init SDL using SDL_Init() or GUI_init()
2. create a GUI_window using GUI_createWindow()
3. set up an SDL update loop with events. An example one is in src/source/main.c
4. on quitting the program remember to first destroy any windows using GUI_destroyWindow()
5. then use SDL_Quit() or GUI_quit() to deinitialize SDL.

# important
I still don't take any responsobility for what you do with it, you know the drill :3
