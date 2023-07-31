# Thicc Pixel Engine
A header-only C/C++ framework for making games with *thicc* pixels.
## Building
WARN: WASM build doesn't work.
<br>
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
 - [STB](https://github.com/nothings/stb)

## Usage
There's examples in the demo folder. You need to generate the assets witht he python script in there.

### Post-processing shader
You can do something similar to this:
```C
#define TPE_FRAGMENT_SHADER myShaderSource
#define TPE_IMPL
#include "tpe.h"

...

int main() {
 ...
 myShaderSource = "#version " TPE_SHADER_VERSION "\n" // + The rest of your source.
 tpe_Context ctx;
	tpe_init(&ctx, "Game Window");
	...
}
```
<br>
The default shader looks like such:
<br>
```
out vec4 FragColor;
in vec2 texPos;
uniform sampler2D screen;
void main() {
 FragColor = vec4(texture(screen, texPos).rgb, 1.0f);
}
```
