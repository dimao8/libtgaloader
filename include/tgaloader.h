///
/// \file tgaloader.h
///

#ifndef TGALOADER_H
#define TGALOADER_H

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#if defined(_WIN32_)
#define EXPORT __declspec (dllexport)
#else
#define EXPORT
#endif // _WIN32_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

  ///
  /// \brief TGA error codes
  ///
  enum tga_error_tag
  {
    TGA_ERROR_OK = 0,           /// There is no errors
    TGA_ERROR_NO_SUCH_FILE = 1, /// TGA file is missing or can not be read
    TGA_ERROR_NOT_TGA = 2,      /// File or stream is not a TGA image
    TGA_ERROR_MALLOC = 4,       /// Can not allocate memory
    TGA_ERROR_EMPTY_IMAGE = 5,  /// Image is empty, i.e. there is no image data
    TGA_ERROR_NOT_SUPPORTED = 6 /// TGA format not supported by this version
  };

  typedef enum tga_error_tag tga_error_t;

  ///
  /// \brief Color map types
  ///
  enum tga_color_map_type_tag
  {
    TGA_NO_COLOR_MAP = 0, /// There is no color map
    TGA_HAS_COLOR_MAP = 1 /// Color map is present
  };

  typedef enum tga_color_map_type_tag tga_color_map_type_t;

  ///
  /// \brief TGA image types
  ///
  enum tga_image_type_tag
  {
    TGA_NO_IMAGE = 0,               /// No image data
    TGA_IMAGE_COLOR_MAPPED = 1,     /// Color mapped image data
    TGA_IMAGE_TRUECOLOR = 2,        /// True color image data (RGB)
    TGA_IMAGE_GRAYSCALE = 3,        /// Grayscale image data
    TGA_IMAGE_RLE_COLOR_MAPPED = 9, /// Color mapped RLE image data
    TGA_IMAGE_RLE_TRUECOLOR = 10,   /// True color RLE image data
    TGA_IMAGE_RLE_GRAYSCALE = 11    /// Grayscale RLE image data
  };

  typedef enum tga_image_type_tag tga_image_type_t;

#pragma pack(push, 1)
  ///
  /// \brief Color map specification struct
  ///
  struct tga_color_map_tag
  {
    uint16_t first_entry_index;   /// First entry index
    uint16_t color_map_length;    /// Color map length
    uint8_t color_map_entry_size; /// Color map entry size
  };

  typedef struct tga_color_map_tag tga_color_map_t;

  ///
  /// \brief Image specification struct
  ///
  struct tga_image_tag
  {
    uint16_t x_origin;        /// X origin position in the image
    uint16_t y_origin;        /// Y origin position in the image
    uint16_t width;           /// Width of the image
    uint16_t height;          /// Height of the image
    uint8_t pixel_depth;      /// Pixel bit depth. Can be 8, 16, 24 or 32
    uint8_t image_descriptor; /// Image descriptor. Contains alpha depth and
                              /// scan position
  };

  typedef struct tga_image_tag tga_image_t;

  ///
  /// \brief TGA file header struct
  ///
  struct tga_header_tag
  {
    uint8_t id_length;      /// Length of the ID field
    uint8_t color_map_type; /// Color map type. Can be one of
                            /// (Color Map Types)[color_map_type_tag]
    uint8_t image_type;     /// Image type. Can be one of
                            /// (Image Types)[image_type_tag]
    tga_color_map_t color_map_specification; /// Color map specification
    tga_image_t image_type_specification;    /// Image type specification
  };

  typedef struct tga_header_tag tga_header_t;
#pragma pack(pop)

  ///
  /// \brief LoadTGAFromArray
  /// \param [in] data      -- Array with image data
  /// \param [out] header   -- TGA header with image info
  /// \param [out] data     -- TGA image data
  /// \param [in] flip      -- Set to flip image over x
  /// \return Return result of TGA loading
  ///
  /// Load TGA file and store TGA header info and image bites into user defined
  /// buffer. Image can be flipped by x axis.
  ///
  tga_error_t EXPORT LoadTGAFromArray (const uint8_t *raw_data, size_t length,
                                       tga_header_t *header, uint8_t **data,
                                       bool flip);

  ///
  /// \brief LoadTGAFromFile
  /// \param [in] file_name -- Path and name of the PNG file
  /// \param [out] header   -- TGA header with image info
  /// \param [out] data     -- TGA image data
  /// \param [in] flip      -- Set to flip image over x
  /// \return Return result of TGA loading
  ///
  /// Load TGA file and store TGA header info and image bites into user defined
  /// buffer. Image can be flipped by x axis.
  ///
  tga_error_t EXPORT LoadTGAFromFile (const char *file_name,
                                      tga_header_t *header, uint8_t **data,
                                      bool flip);

  ///
  /// \brief FreeTGA
  /// \param [in] data -- Pointer to the data, received by LoadTGA.
  ///
  /// This function is only way to free data array, received from TGA file by
  /// LoadTGA function.
  ///
  void EXPORT FreeTGA (uint8_t **data);

  ///
  /// \brief TGALoaderVersion
  /// \param [out] str -- Buffer for version string
  /// \param [in] n    -- Length of the buffer
  ///
  /// Copy version string into user buffer.
  ///
  void EXPORT TGALoaderVersion (char *str, size_t n);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // TGALOADER_H
