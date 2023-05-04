#include <tgaloader.h>.

#include <memory>

/* **************************** LoadTGAFromArray *************************** */

tga_error_t
LoadTGAFromArray (const uint8_t *raw_data, size_t length, tga_header_t *header,
                  uint8_t **data, bool flip)
{
  uintptr_t offset = 0;


}