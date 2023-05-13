#include <tgaloader.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define PATTERN_SIZE 16
uint8_t pattern[PATTERN_SIZE] = {
  255, 0, 0, 255,
  0, 255, 0, 255,
  0, 0, 255, 255,
  255, 255, 0, 255};

int main(int argc, char ** argv)
{
  int n;

  SaveTGA(2, 2, 4, pattern, "result.tga");

  return 0;
}