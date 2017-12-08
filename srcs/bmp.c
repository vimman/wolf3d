/** BITMAP **/

#include "wolf.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma pack(push, 1)
typedef struct		s_pixel
{
  unsigned char		R;
  unsigned char		G;
  unsigned char		B;
}					t_pixel;
#pragma pack(pop)
#pragma pack(push, 1)
typedef struct		s_bitmap
{
    short			signature;
    int				size;
    short			reserved1;
    short			reserved2;
    int				dataoffSet;
    int				bitmapheadersize;
    int				width;
    int				height;
    short			planes;
    short			bitsperpixel;
    int				compression;
    int				sizeImage;
    int				xpixelspremeter;
    int				ypixelspremeter;
    int				colorsused;
    int				colorsimportant;
}					t_bitmap;
#pragma pack(pop)
/** END BITMAP **/

/**
BITMAP
**/
void *bitmap_to_img(char *filename, t_env *env)
{
	int				i;
	int				j;
	int				k;
	t_bitmap		source_info;
	t_pixel			source_pix;
	unsigned char *datas;

	FILE *fp;

	(void)env;
	if(!(fp=fopen(filename,"rb")) || sizeof(source_info) != 54)
		return (NULL);
	memset(&source_info, 0, sizeof(source_info));
	fread(&source_info, sizeof(source_info), 1, fp);
	if (source_info.width < 0 || source_info.width > 2000 || source_info.height > 2000 || source_info.height < 0)
		return (NULL);
	fseek(fp, source_info.dataoffSet, SEEK_SET);
	datas = (unsigned char *)malloc(sizeof(unsigned char) * source_info.width * source_info.height * 3);
	i = 0;
	j = 0;
	k = 0;
	while (i < source_info.height)
	{
		k = 0;
		while (k < source_info.width)
		{
			fread(&source_pix, sizeof(t_pixel), 1, fp);
			datas[j++] = source_pix.R;
			datas[j++] = source_pix.G;
			datas[j++] = source_pix.B;
			k++;
		}
		if (k % 4 != 0)
			fread(NULL, k % 4, 1, fp);
		i++;
	}
	int		*idatas;
	int		bpx;
	int		linesize;
	//int		indian;
	//idatas =  mlx_get_data_addr(img, &bpx, &linesize, &indian);
	//idatas = (int *)malloc(sizeof(int*) * source_info.width * source_info.height * 3);
	bpx = source_info.bitsperpixel;
	linesize = source_info.width * 4;
	idatas = malloc(sizeof(int*) * bpx * linesize * 128);
	i = 0;
	k = 0;
	while ((int)i < source_info.height)
	{
		j = 0;
		k = (source_info.height - 1 - i) * (source_info.width * 3);
		while ((int)j < source_info.width)
		{
			int index = i * linesize + ((j * bpx) >> 3);

			idatas[index] = datas[k++];
			idatas[++index] = datas[k++];
			idatas[++index] = datas[k++];
			j++;
		}
		i++;
	}
	free(datas);
	fclose(fp);
	return (idatas);
}
/** END BITMAP **/