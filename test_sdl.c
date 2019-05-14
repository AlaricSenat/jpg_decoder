/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:23:18 by asenat            #+#    #+#             */
/*   Updated: 2019/06/04 10:23:18 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL2/SDL.h>        
#include <string.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
extern "C" {
#include "includes/jpg_decode.h"
}

int main(int argc, char ** argv)
{
	bool quit = false;
	SDL_Event event;

	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window * window = SDL_CreateWindow("SDL2 Displaying Image",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 480, 360, 0);

	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
	int req_format = STBI_rgb;
	unsigned width, height;
	unsigned char* data = jpg_decode(argv[1], &width, &height);
	if(data == NULL) {
		SDL_Log("Loading image failed: %s", stbi_failure_reason());
		exit(1);
	}

	// Set up the pixel format color masks for RGB(A) byte arrays.
	// Only STBI_rgb (3) and STBI_rgb_alpha (4) are supported here!
	Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	int shift = (req_format == STBI_rgb) ? 8 : 0;
	rmask = 0xff000000 >> shift;
	gmask = 0x00ff0000 >> shift;
	bmask = 0x0000ff00 >> shift;
	amask = 0x000000ff >> shift;
#else // little endian, like x86
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = (req_format == STBI_rgb) ? 0 : 0xff000000;
#endif

	int depth, pitch;
	if (req_format == STBI_rgb) {
		depth = 24;
		pitch = 3*width; // 3 bytes per pixel * pixels per row
	} else { // STBI_rgb_alpha (RGBA)
		depth = 32;
		pitch = 4*width;
	}

	SDL_Surface* image = SDL_CreateRGBSurfaceFrom((void*)data, width, height, depth, pitch,
			rmask, gmask, bmask, amask);
	//image.userdata = jpg_decode("test.jpg", (unsigned*)&image.w, (unsigned*)&image.h);
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);

	while (!quit)
	{
		SDL_WaitEvent(&event);

		switch (event.type)
		{
			case SDL_QUIT:
				quit = true;
				break;
		}

		//SDL_Rect dstrect = { 5, 5, 320, 240 };
		//SDL_RenderCopy(renderer, texture, NULL, &dstrect);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(image);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}
