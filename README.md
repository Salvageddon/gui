# gui
XML GUI library for C.

# warning
This library is under development. It BARELY has the *gui* part yet.
More documentation for this project will be out along with a release.
For now please use the instruction below and src/pub/interface.xml for reference.

# instruction
1. init SDL using SDL_Init() or GUI_init()
2. create a GUI_window using GUI_createWindow()
3. read GUI from an .xml file using GUI_read() and store it in your GUI_window->guiBase
4. bake the GUI using GUI_bake(). Remember to ALWAYS bake the gui before calling GUI_render()
5. set up an SDL update loop with events. An example one is in src/source/main.c
6. render yout GUI on screen using GUI_render(). After that, call SDL_UpdateWindowSurface() with your GUI_window->win
7. on quitting the program remember to first destroy any windows using GUI_destroyWindow()
8. then use SDL_Quit() or GUI_quit() to deinitialize SDL.

# important
I still don't take any responsobility for what you do with it, you know the drill :3
