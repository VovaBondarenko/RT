#include "../include/rt.h"

#include <stdio.h>

void	put_image(t_image *image, int x, int y, t_vec3 color)
{
	int pos;

	if (x >= 0 && x < DEFAULT_WIDTH && y >= 0 && y < DEFAULT_HEIGHT)
	{
		pos = (x * (image->bpp / 8) + (y * image->size_len));
		image->str[pos] = color.z * 255;
		image->str[pos + 1] = color.y * 255;
		image->str[pos + 2] = color.x * 255;
	}
}
