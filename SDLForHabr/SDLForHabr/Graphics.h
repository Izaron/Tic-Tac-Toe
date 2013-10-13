#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include "Project.h"

#include "Image.h"
class Image;

class Graphics
{
private:
	SDL_Surface* Screen;

public:
	Graphics(int width, int height);

	Image* NewImage(char* file);
	Image* NewImage(char* file, int r, int g, int b);
	bool DrawImage(Image* img, int x, int y);
	bool DrawImage(Image* img, int x, int y, int startX, int startY, int endX, int endY);

	void Flip();
};

#endif