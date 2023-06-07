#include <tgaloader.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define PATTERN_SIZE 4
uint8_t pattern[PATTERN_SIZE] = {255, 0, 0, 255};

void version()
{
  char str[32];

  TGALoaderVersion(str, 32);

  printf("%s\n", str);
}

int main(int argc, char ** argv)
{
  uint8_t * data;
  tga_header_t hdr;
  int n, m;
  tga_error_t result;

  if (argc == 1)
    return -1;

  for (n = 1; n < argc; n++)
    {
      if (strcmp(argv[n], "--version") == 0)
        {
          version();
          return 0;
        }
      else
        {
          result = LoadTGAFromFile(argv[1], &hdr, &data, false);

          if (result != TGA_ERROR_OK)
            {
              printf("TGA error %i\n", result);
              return -1;
            }

          for (n = 0; n < PATTERN_SIZE; n++)
            {
              if (data[n] != pattern[n])
                {
                  printf(":");
                  for (m = 0; m < PATTERN_SIZE; m++)
                    {
                      printf(" %02lx", (unsigned long)data[m]);
                    }
                  printf("\n ");
                  for (m = 0; m < PATTERN_SIZE; m++)
                    {
                      if (m == n)
                        printf(" ^ ");
                      else
                        printf("   ");
                    }
                  printf("\nHave %02lx, expected %02lx\n", (unsigned long)data[n], (unsigned long)pattern[n]);
                  return -1;
                }
            }

          printf("\n");
        }
    }

  return result;
}
