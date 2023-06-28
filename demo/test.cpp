#define TPE_IMPL
#include "../tpe.h"
#include <iostream>

#include "./testspr.h"

int main() {
	tpe::Context ctx;
	tpe::init(&ctx, "Game Window");

	tpe::clearColor(&ctx, 255, 255, 255);
	
	float now, prev = 0.f;

	while (!tpe::shouldClose(ctx)) {
		bool show = tpe::keyDown(ctx, TPE_KEY(SPACE));
		tpe::clear(&ctx);
		// Draw the sprite with a colourkey
		tpe::drawBufferColorkey(&ctx, TESTSPR_IMG, 6, 6, 16, 16, 255, 0, 255);
		if (show)
			tpe::drawBufferColorkey(&ctx, TESTSPR_IMG, 12, 12, 16, 16, 255, 0, 255);
		// Draw the sprite without a colourkey
		tpe::drawBuffer(&ctx, TESTSPR_IMG, 32, 32, 16, 16);
		for (int i = 0; i < 16; ++i)
			tpe::putPixel(&ctx, i + 16, i, 255, 66, 0);
		tpe::drawText(&ctx, "Hello world!", 55, 55, 0, 0, 0);
		tpe::drawRect(&ctx, 0, 64, 200, 3, 255, 0, 0);
		tpe::drawRect(&ctx, 64, 64, 32, 32, 255, 255, 0);
		now = tpe::time();
		float dt = now - prev;
		prev = now;
		// std::cout << "Delta Time: " << dt << std::endl;
		tpe::display(ctx);
	}
	return 0;
}
