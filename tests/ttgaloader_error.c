#include <tgaloader.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char ** argv)
{
  uint8_t * data;
  tga_header_t hdr;
  int n;
  tga_error_t result;
  int r;

  if (argc == 1)
    return -1;

  for (n = 1; n < argc; n++)
    {
      if (strncmp(argv[n], "--except=", 9) == 0)
        {
          sscanf(argv[n], "--except=%i", &r);
        }
      else
        {
					printf("%s\n", argv[n]);
          result = LoadTGAFromFile(argv[n], &hdr, &data, false);
        }
    }

  switch (result)
    {

    case TGA_ERROR_OK:
      printf("No error\n");
      break;

    case TGA_ERROR_NO_SUCH_FILE:
      printf("No such file\n");
      break;

    case TGA_ERROR_NOT_SUPPORTED:
      printf("Not supported\n");
      break;

    case TGA_ERROR_EMPTY_IMAGE:
      printf("Empty image\n");
      break;

    case TGA_ERROR_MALLOC:
      printf("Malloc/Realloc\n");
      break;

    case TGA_ERROR_NOT_TGA:
      printf("Not a TGA\n");
      break;

    default:
      printf("Unknown error value\n");
      break;

    }

  return (r == result) ? -1 : 0;
}
