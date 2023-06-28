#ifndef __TPE_H__
#define __TPE_H__

// For debugging purposes
// #define TPE_IMPL

#ifndef TPE_W
#define TPE_W 200
#endif // TPE_W
#ifndef TPE_H
#define TPE_H 152
#endif // TPE_H
#ifndef TPE_PIXEL_SIZE
#define TPE_PIXEL_SIZE 5
#endif // TPE_PIXEL_SIZE

#include <stdio.h>
#include <stdbool.h>
#include "external/glad/include/glad/glad.h"

#ifdef TPE_IMPL
#ifdef __cplusplus
extern "C" {
#endif
#include "external/font8x8/font8x8_basic.h"
#ifdef __cplusplus
}
#endif
#include "external/glad/src/glad.c"
#include "ex-impl/glfw-impl.h"
#include "external/stb/stb_vorbis.c"
#define CM_USE_STB_VORBIS
GLFWbool _glfwConnectNull(int platformID, _GLFWplatform* platform) {return (1 == 2);}
#else
#define GLFW_INCLUDE_ES2
#endif // TPE_IMPL
#include "external/glfw/include/GLFW/glfw3.h"
#ifdef __cplusplus
#define T(T) T
#define KEY(K) KEY_##K = GLFW_KEY_##K
#define TPE_KEY(K) GLFW_KEY_##K
#define INLINE extern inline
namespace tpe {
extern "C" {
#else
#define T(T) tpe_##T
#define TPE_KEY(K) GLFW_KEY_##K
#define INLINE extern inline
#endif // __cplusplus
	
	typedef struct {
		GLFWwindow* window;
		unsigned int vao, vbo, ebo, shaders, screen;
		// This is dumb
		GLubyte pixels[TPE_W * TPE_H * 3];
		GLubyte clearPixels[TPE_W * TPE_H * 3];
		GLubyte prevPixels[TPE_W * TPE_H * 3];
	} T(Context);

	typedef cm_Source* T(Audio);

	INLINE void T(init) (T(Context) * ctx, const char* winName);
	INLINE bool T(shouldClose)(T(Context) ctx);
	INLINE void T(display)(T(Context) ctx);
	INLINE void T(close)(T(Context) * ctx);
	INLINE void T(clear)(T(Context) * ctx);
	INLINE void T(clearColor)(T(Context) * ctx,
		const unsigned char r,
		const unsigned char g,
		const unsigned char b);
	void T(putPixel)(T(Context) * ctx, int x, int y, unsigned char r, unsigned char g, unsigned char b );
	INLINE float T(time)();
	void T(drawBuffer)(T(Context) * ctx, unsigned char* buf, unsigned short x, unsigned short y, unsigned short w, unsigned short h);
	void T(drawBufferColorkey)(T(Context) * ctx, unsigned char* buf, unsigned short x, unsigned short y, unsigned short w, unsigned short h, unsigned char r, unsigned char g, unsigned b);
	INLINE bool T(keyDown)(T(Context) ctx, unsigned char k);
	void T(drawGlyph)(T(Context) * ctx, char* glyph, unsigned short x, unsigned short y, unsigned char r, unsigned char g, unsigned char b);
	void T(drawText)(T(Context) * ctx, const char* text, unsigned short x, unsigned short y, unsigned char r, unsigned char g, unsigned char b);
	void T(drawRect)(T(Context) * ctx, unsigned short x, unsigned short y, unsigned short w, unsigned short h, unsigned char r, unsigned char g, unsigned char b);
	T(Audio) T(loadSound)(const char* path);
	void T(playSound)(T(Audio) a);

#ifdef TPE_IMPL
	INLINE void T(init) (T(Context) * ctx, const char* winName) {
		T(clearColor)(ctx, 0, 0, 0);
		// Intialise glfw
		if(!glfwInit()) {
			printf("Could not initialse glfw.\n");
			exit(-1);
		}
		glfwWindowHint(GLFW_SAMPLES, 0);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		ctx->window = glfwCreateWindow(TPE_W * TPE_PIXEL_SIZE, TPE_H * TPE_PIXEL_SIZE, winName, NULL, NULL);
		if (!ctx->window) {
			printf("Could not create GLFWwindow.\n");
			glfwTerminate();
			exit(-1);
		}
		glfwMakeContextCurrent(ctx->window);
		glfwSwapInterval(1);
		if (!gladLoadGLES2Loader((GLADloadproc)glfwGetProcAddress)){
			printf("Failed to initialise GLAD.\n");
			exit(-1);
		}

		glDisable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);
		// glDisable(GL_TEXTURE_2D);
		// VERTEX SHADER
		const char* vertexShaderSource = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"out vec2 texPos;\n"
			"void main()\n"
			"{\n"
			"gl_Position = vec4(aPos.x * 2 - 1, aPos.y  * 2 - 1, aPos.z, 1.0);\n"
			"texPos = vec2(aPos.x, abs(aPos.y - 1));\n"
			"}\0";
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);

		// FRAGMENT SHADER
		const char* fragmentShaderSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"in vec2 texPos;\n"
			"uniform sampler2D screen;\n"
			"void main()\n"
			"{\n"
			"FragColor = vec4(texture(screen, texPos).rgb, 1.0f);\n"
			"}\0";
		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);

		// Shader program
		ctx->shaders = glCreateProgram();
		glAttachShader(ctx->shaders, vertexShader);
		glAttachShader(ctx->shaders, fragmentShader);
		glLinkProgram(ctx->shaders);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		// VAO stuff
		float verts[] = {
			 1.f,  1.f, 0.0f,  // top right
			 1.f,  0.f, 0.0f,  // bottom right
			 0.f,  0.f, 0.0f,  // bottom left
			 0.f,  1.f, 0.0f   // top left 
		};
		unsigned int indices[] = {
			0, 1, 3,  // first Triangle
			1, 2, 3   // second Triangle
		};
		glGenVertexArrays(1, &ctx->vao);
		glGenBuffers(1, &ctx->vbo);
		glGenBuffers(1, &ctx->ebo);
		glBindVertexArray(ctx->vao);
		glBindBuffer(GL_ARRAY_BUFFER, ctx->vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ctx->ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		glGenTextures(1, &ctx->screen);
		glBindTexture(GL_TEXTURE1, ctx->screen);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		// Audio
		cm_init(44100);
	}

	INLINE bool T(shouldClose)(T(Context) ctx) {
		return glfwWindowShouldClose(ctx.window);
	}

	INLINE void T(display)(T(Context) ctx) {
		glClearColor(1.f, .25f, .25f, 1.f);
		glClear( GL_COLOR_BUFFER_BIT );

		glUseProgram(ctx.shaders);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TPE_W,
                	TPE_H, 0, GL_RGB, GL_UNSIGNED_BYTE, ctx.pixels);
		// glGenerateMipmap(GL_TEXTURE_2D);
		glUniform1i(glGetUniformLocation(ctx.shaders, "screen"), 1);
		glBindVertexArray(ctx.vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glUseProgram(0);

		glfwSwapBuffers(ctx.window);
		glfwPollEvents();
	}

	INLINE void T(close)(T(Context) * ctx) {
		glDeleteVertexArrays(1, &ctx->vao);
		glDeleteBuffers(1, &ctx->vbo);
		glDeleteBuffers(1, &ctx->ebo);
		glDeleteProgram(ctx->shaders);
		glDeleteTextures(1, &ctx->screen);
		glfwTerminate();
	}

	void T(putPixel)(T(Context) * ctx, int x, int y, unsigned char r, unsigned char g, unsigned char b ) {
		unsigned int pixelIndex =
			((y * TPE_W) + x)*3;
		ctx->pixels[pixelIndex] = r;
		ctx->pixels[pixelIndex + 1] = g;
		ctx->pixels[pixelIndex + 2] = b;

	}

	INLINE void T(clear)(T(Context) * ctx) {
		memcpy(&ctx->pixels, ctx->clearPixels, TPE_W*TPE_H*3);
		// memset(&ctx->pixels, ctx->)
	}

	INLINE void T(clearColor)(T(Context) * ctx,
		const unsigned char r,
		const unsigned char g,
		const unsigned char b) {
		for (int i = 0; i < sizeof(ctx->clearPixels); i += 3) {
			ctx->clearPixels[i]   = r;
			ctx->clearPixels[i+1] = g;
			ctx->clearPixels[i+2] = b;
		}

	}

	INLINE float T(time)() {
		return glfwGetTime();
	}
	
	void T(drawBuffer)(T(Context) * ctx, unsigned char* buf, unsigned short x, unsigned short y, unsigned short w, unsigned short h) {
		for (int i = 0; i < h; ++i)
			memcpy(ctx->pixels + (((y+i) * TPE_W) + x) * 3, buf + i * w * 3, w * 3);
	}

	void T(drawBufferColorkey)(T(Context) * ctx, unsigned char* buf, unsigned short x, unsigned short y, unsigned short w, unsigned short h, unsigned char r, unsigned char g, unsigned b) {
		memcpy(ctx->prevPixels, ctx->pixels, sizeof(ctx->pixels));
		for (int i = 0; i < h; ++i)
			memcpy(ctx->pixels + (((y+i) * TPE_W) + x) * 3, buf + i * w * 3, w * 3);
		for (int i = y; i < y + h * 3; ++i)
			for (int j = x; j < x + w * 3; ++j) {
				unsigned short p = ((i * TPE_W) + j)*3;
				if (
					ctx->pixels[p] == r &&
					ctx->pixels[p + 1] == g &&
					ctx->pixels[p + 2] == b
				) {
				ctx->pixels[p] = ctx->prevPixels[p];
				ctx->pixels[p + 1] = ctx->prevPixels[p + 1];
				ctx->pixels[p + 2] = ctx->prevPixels[p + 2];
			}
		}

	}

	INLINE bool T(keyDown)(T(Context) ctx, unsigned char k) {
		return glfwGetKey(ctx.window, k) != GLFW_RELEASE;
	}

	void T(drawGlyph)(T(Context) * ctx, char* glyph, unsigned short x, unsigned short y, unsigned char r, unsigned char g, unsigned char b) {
		unsigned char my = 0;
		for (unsigned char rx=0; rx < 8; ++rx) {
			for (unsigned char ry=0; ry < 8; ++ry) {
        			if (glyph[rx] & 1 << ry)
					T(putPixel)(ctx, ry + x, rx + y, r, g, b);
			}
			++my;
		}
	}
	
	void T(drawText)(T(Context) * ctx, const char* text, unsigned short x, unsigned short y, unsigned char r, unsigned char g, unsigned char b) {
	for (unsigned short t = 0; t < strlen(text); ++t)
		T(drawGlyph)(
			ctx, font8x8_basic[text[t]], x + t * 8, y, r, g, b);
	}
	
	void T(drawRect)(T(Context) * ctx, unsigned short x, unsigned short y, unsigned short w, unsigned short h, unsigned char r, unsigned char g, unsigned char b) {
		for (unsigned short dx = 0; dx < w; ++dx)
			for (unsigned short dy = 0; dy < h; ++dy)
				T(putPixel)(ctx, x + dx, y + dy, r, g, b);
	}

	T(Audio) T(loadSound)(const char* path) {
	}
	
	void T(playSound)(T(Audio) a) {
	}
	
#endif // TPE_IMPL

#ifdef __cplusplus
}}
#endif // __cplusplus

#undef T
#undef INLINE

#endif // __TPE_H__
