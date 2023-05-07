#include <tgaloader.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

enum tga_origin_tag
{
  TGA_ORIGIN_LEFT_BOTTOM = 0x00,
  TGA_ORIGIN_RIGHT_BOTTOM = 0x10,
  TGA_ORIGIN_LEFT_TOP = 0x20,
  TGA_ORIGIN_RIGHT_TOP = 0x30
};

typedef enum tga_origin_tag tga_origin_t;

#define TGA_ORIGIN_BITS_Msk 0x30

/* ******************************** letobel ******************************** */

uint32_t
letobel (uint32_t u32)
{
#if defined(WORDS_BIGENDIAN)
  return ((u32 >> 24) & 0xFF) | ((u32 >> 8) & 0xFF00) | ((u32 << 8) & 0xFF0000)
         | ((u32 << 24) & 0xFF000000);
#else
  return u32;
#endif // defined
}

/* ******************************** letobes ******************************** */

uint32_t
letobes (uint16_t u16)
{
#if defined(WORDS_BIGENDIAN)
  return ((u16 >> 8) & 0xFF) | (u16 & 0xFF00);
#else
  return u16;
#endif // defined
}

/* **************************** LoadTGAFromArray *************************** */

tga_error_t
LoadTGAFromArray (const uint8_t *raw_data, size_t length, tga_header_t *header,
                  uint8_t **data, bool flip)
{
  uintptr_t offset = 0;

  // Get header
  if (offset + sizeof (tga_header_t) >= length)
    return TGA_ERROR_NOT_TGA;

  memcpy (header, raw_data, sizeof (tga_header_t));
  offset += sizeof (tga_header_t);

  printf ("1\n");

  // Rotate header words
  header->color_map_specification.color_map_length
      = letobes (header->color_map_specification.color_map_length);
  header->color_map_specification.first_entry_index
      = letobes (header->color_map_specification.first_entry_index);

  header->image_type_specification.x_origin
      = letobes (header->image_type_specification.x_origin);
  header->image_type_specification.y_origin
      = letobes (header->image_type_specification.y_origin);
  header->image_type_specification.width
      = letobes (header->image_type_specification.width);

  // Check out header
  if (header->image_type != TGA_IMAGE_GRAYSCALE
      && header->image_type != TGA_IMAGE_TRUECOLOR)
    {
      return TGA_ERROR_NOT_SUPPORTED;
    }

  if (((header->image_type_specification.image_descriptor
        & TGA_ORIGIN_BITS_Msk)
       == TGA_ORIGIN_RIGHT_BOTTOM)
      || ((header->image_type_specification.image_descriptor
           & TGA_ORIGIN_BITS_Msk)
          == TGA_ORIGIN_RIGHT_TOP))
    return TGA_ERROR_NOT_SUPPORTED;

  size_t bpp = (header->image_type_specification.pixel_depth + 7) / 8;
  size_t bpl = header->image_type_specification.width * bpp;

  // Skip ID
  if (offset + header->id_length >= length)
    return TGA_ERROR_NOT_TGA;
  else
    offset += header->id_length;

  // Skip color map
  if (header->color_map_type == TGA_HAS_COLOR_MAP)
    {
      size_t color_map_size
          = header->color_map_specification.color_map_length
            * ((header->color_map_specification.color_map_entry_size + 7) / 8);
      if (offset + color_map_size >= length)
        return TGA_ERROR_NOT_TGA;
      else
        offset += color_map_size;
    }

  // Get data
  *data = (uint8_t *)malloc (bpl * header->image_type_specification.height);
  if (*data == NULL)
    return TGA_ERROR_MALLOC;

  printf ("2\n");

  if ((flip
       && (header->image_type_specification.image_descriptor
           & TGA_ORIGIN_BITS_Msk)
              == TGA_ORIGIN_LEFT_BOTTOM)
      || (!flip
          && (header->image_type_specification.image_descriptor
              & TGA_ORIGIN_BITS_Msk)
                 == TGA_ORIGIN_LEFT_TOP))
    {
      memcpy (*data, raw_data + offset,
              bpl * header->image_type_specification.height);
    }
  else
    {
      for (size_t n = 0; n < header->image_type_specification.height; n++)
        {
          memcpy (
              *data + bpl * n,
              raw_data + offset
                  + bpl * (n - header->image_type_specification.height + 1),
              bpl);
        }
    }

  printf ("3\n");

  // Rotate data (we expect RED, GREEN, BLUE, ALPHA)
  // switch (bpp)
  //   {

  //   case 2:

  //   }

  return TGA_ERROR_OK;
}

/* **************************** LoadTGAFromFile **************************** */

tga_error_t
LoadTGAFromFile (const char *file_name, tga_header_t *header, uint8_t **data,
                 bool flip)
{
  tga_error_t result;

  uint8_t *raw_data;
  size_t length;

  FILE *file = fopen (file_name, "rb");
  if (file == 0)
    return TGA_ERROR_NO_SUCH_FILE;

  fseek (file, 0, SEEK_END);
  length = ftell (file);
  fseek (file, 0, SEEK_SET);
  raw_data = (uint8_t *)malloc (length);
  if (raw_data == 0)
    {
      fclose (file);
      return TGA_ERROR_MALLOC;
    }
  fread (raw_data, length, 1, file);
  fclose (file);

  result = LoadTGAFromArray (raw_data, length, header, data, flip);
  free (raw_data);

  return result;
}

/* ******************************** FreeTGA ******************************** */

void
FreeTGA (uint8_t **data)
{
  if (data == NULL)
    return;

  if (*data != NULL)
    free (*data);
}

/* **************************** TGALoaderVersion *************************** */

void
TGALoaderVersion (char *str, size_t n)
{
  strncpy (str, VERSION, n);
}
