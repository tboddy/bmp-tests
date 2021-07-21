#include <genesis.h>
#include <resources.h>

#define GAME_WIDTH 256
#define GAME_HEIGHT 160

#define GAME_WIDTH_16 FIX16(256)
#define GAME_HEIGHT_16 FIX16(160)

char currentColor;

#define BULLET_COUNT 512
#define BULLET_SPEED FIX16(0.5)

#define BULLET_PIXELS 2

Vect2D_f16 bullets[BULLET_COUNT][BULLET_PIXELS];

void loadGame(){
	currentColor = 0xFF;
	for(s16 i = 0; i < BULLET_COUNT; i++){
		for(s16 j = 0; j < BULLET_PIXELS; j++){
			bullets[i][j].x = random() % GAME_WIDTH_16;
			bullets[i][j].y = random() % GAME_HEIGHT_16;
		}
	}
}

void updateBullet(s16 i){
	for(s16 j = 0; j < BULLET_PIXELS; j++){
		bullets[i][j].x = fix16Add(bullets[i][j].x, BULLET_SPEED);
		if(bullets[i][j].x >= GAME_WIDTH_16) bullets[i][j].x = 0;
	}
}

void updateGame(){
	for(s16 i = 0; i < BULLET_COUNT; i++) updateBullet(i);
}

void drawBullet(s16 i){
	BMP_setPixelFast(fix16ToInt(bullets[i][0].x), fix16ToInt(bullets[i][0].y), currentColor);
}

void drawGame(){
	for(s16 i = 0; i < BULLET_COUNT; i++) drawBullet(i);
}

int main() {
	VDP_loadTileSet(frame1.tileset, 8, DMA);
	VDP_setPalette(PAL1, frame1.palette -> data);
	VDP_setScreenWidth256();
  VDP_setHInterrupt(0);
  VDP_setHilightShadow(0);
  DMA_setBufferSize(2048);
  BMP_init(TRUE, BG_A, PAL1, FALSE);
  loadGame();
	while(1){
		updateGame();
		BMP_waitWhileFlipRequestPending();
		BMP_showFPS(2);
		BMP_clear();
		drawGame();
		BMP_flip(1);
	}
	return (0);
}