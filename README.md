# Thicc Pixel Engine
A header-only C/C++ framework for making games with *thicc* pixels.
## Building
NOTE: In C++ you need to add `-fpermissive` and use a C++ compiler.
<br> 
<br>
On Linux and C:
```sh
gcc -lX11 -lXcursor -lGL -ldl -lm -pthread myfile.c
```
On Windows and Mingw the following *should* work:
```sh
gcc -lkernel32 -luser32 -lshell32 -lgdi32 -ladvapi32 -lopengl32 myfile.c
```
## Inspired by (/steals code from)
 - [Gunslinger](https://github.com/MrFrenik/gunslinger)
 - [cbEngine](https://github.com/Ceebox/cbEngine)
 - [Fenster](https://github.com/zserge/fenster)
 - [Font8x8](https://github.com/daveythacher/font8x8)
 - [GLFW](https://github.com/glfw/glfw)
 - [GLAD](https://github.com/Dav1dde/glad)
