#define TPE_IMPL
#include "../tpe.h"

#include "./testspr.h"

int main() {
	tpe_Context ctx;
	tpe_init(&ctx, "Game Window");

	tpe_clearColor(&ctx, 255, 255, 255);

	float now, prev = 0.f;

	tpe_Audio audio = tpe_loadSound("demo/chomp.ogg");
	tpe_playSound(audio);

	while (!tpe_shouldClose(ctx)) {
		bool show = tpe_keyDown(ctx, TPE_KEY(SPACE));
		tpe_clear(&ctx);
		// Draw the sprite with a colourkey
		tpe_drawBufferColorkey(&ctx, TESTSPR_IMG, 6, 6, 16, 16, 255, 0, 255);
		if (show)
			tpe_drawBufferColorkey(&ctx, TESTSPR_IMG, 12, 12, 16, 16, 255, 0, 255);
		// Draw the sprite without a colourkey
		tpe_drawBuffer(&ctx, TESTSPR_IMG, 32, 32, 16, 16);
		for (int i = 0; i < 16; ++i)
			tpe_putPixel(&ctx, i + 16, i, 255, 66, 0);
		tpe_drawText(&ctx, "Hello world!", 55, 55, 0, 0, 0);
		tpe_drawRect(&ctx, 0, 64, 200, 3, 255, 0, 0);
		tpe_drawRect(&ctx, 64, 64, 32, 32, 255, 255, 0);
		now = tpe_time();
		float dt = (now - prev);
		prev = now;
		tpe_display(ctx);
	}
	tpe_close(&ctx);
	return 0;
}
