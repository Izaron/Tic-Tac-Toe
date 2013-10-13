#include "Graphics.h"

Graphics::Graphics(int width, int height)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	Screen = SDL_SetVideoMode(width,height,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
}

Image* Graphics::NewImage(char* file)
{
	Image* image = new Image();
	image->surf = SDL_DisplayFormat(SDL_LoadBMP(file));

	return image;
}

Image* Graphics::NewImage(char* file, int r, int g, int b)
{
	Image* image = new Image();
	image->surf = SDL_DisplayFormat(SDL_LoadBMP(file));

	SDL_SetColorKey(image->surf, SDL_SRCCOLORKEY | SDL_RLEACCEL,
		SDL_MapRGB(image->surf->format, r, g, b));

	return image;
}

bool Graphics::DrawImage(Image* img, int x, int y)
{
	if(Screen == NULL || img->surf == NULL)
        return false;
 
    SDL_Rect Area;
    Area.x = x;
    Area.y = y;
 
    SDL_BlitSurface(img->surf, NULL, Screen, &Area);
 
	return true;
}

bool Graphics::DrawImage(Image* img, int x, int y, int startX, int startY, int endX, int endY)
{
	if(Screen == NULL || img->surf == NULL)
        return false;
 
    SDL_Rect Area;
    Area.x = x;
    Area.y = y;

    SDL_Rect SrcArea;
	SrcArea.x = startX;
	SrcArea.y = startY;
	SrcArea.w = endX;
	SrcArea.h = endY;

	SDL_BlitSurface(img->surf, &SrcArea, Screen, &Area);

	return true;
}

void Graphics::Flip()
{
	SDL_Flip(Screen);
	SDL_FillRect(Screen,NULL, 0x000000);
}