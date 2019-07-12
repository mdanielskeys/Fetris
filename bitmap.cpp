#include "bitmap.h"
#include "bograph.h"


bitmapfile::~bitmapfile()
{
    // deallocate memory
    delete[] image.data;
}

bitmapfile::bitmapfile(char *filename)
{
  FILE *fp;
  long index;
  word num_colors;
  int x;

  /* open the file */
  if ((fp = fopen(filename,"rb")) == NULL)
  {
    printf("Error opening file %s.\n",filename);
    return;
  }

  /* check to see if it is a valid bitmap file */
  if (fgetc(fp)!='B' || fgetc(fp)!='M')
  {
    fclose(fp);
    printf("%s is not a bitmap file.\n",filename);
    return;
  }

  /* read in the width and height of the image, and the
     number of colors used; ignore the rest */
  fskip(fp,16);
  fread(&image.width, sizeof(word), 1, fp);
  fskip(fp,2);
  fread(&image.height,sizeof(word), 1, fp);
  fskip(fp,22);
  fread(&num_colors,sizeof(word), 1, fp);
  fskip(fp,6);

  /* assume we are working with an 8-bit file */
  if (num_colors==0) num_colors=256;


  /* try to allocate memory */
  if ((image.data = new byte[image.width*image.height]) == NULL)
  {
    fclose(fp);
    printf("Error allocating memory for file %s.\n",filename);
    return;
  }

  /* Ignore the palette information for now.
     See palette.c for code to read the palette info. */
  fskip(fp,num_colors*4);

  /* read the bitmap */
  for(index=(image.height-1)*image.width;index>=0;index-=image.width)
    for(x=0;x<image.width;x++)
      image.data[(word)index+x]=(byte)fgetc(fp);

  fclose(fp);
}

void bitmapfile::fskip(FILE *fp, int num_bytes)
{
   int i;
   for (i=0; i<num_bytes; i++)
      fgetc(fp);
}

void bitmapfile::DrawImage(BoGraphics& graphics)
{
    graphics.ScreenCopy((char *)image.data);
}