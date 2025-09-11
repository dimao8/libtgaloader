# TGA Loader v0.1 #

## Description of the TGALoader library ##

TGALoader is a lightweight library for TGA images manipulation. Here are main
capabilities and restrictions of this library.

----

TGA Loader has some advantages:
- Load TGA uncompressed images.
- Extract TGA header.
- Can flip image vertically for OpenGL usage.
- Can save RGB/RGBA images.
- Licensed under the GNU Lesser General Public License v3 (LGPLv3).

Also TGA Loader has some restrictions
- Can not load palette images.
- Can not load RLE compressed images.
- Can not read X-TARGA additional fields.

The main purpose of this library is to give simple interface to load textures
and images for OpenGL-based applications. It is also can be used to save
OpenGL framebuffer for debug purposes.

## Library interface ##

There are some new types, that defined by this library.

`tga_error_t`

This type is an enumerator for all TGALoader error codes. Here is the table of
values such type variable can have:

| Name | Description |
| --- | --- |
| `TGA_ERROR_OK` | 0 - No error. |
| `TGA_ERROR_NO_SUCH_FILE` | TGA file is missing or can not be read.|
| `TGA_ERROR_NOT_TGA` | File or stream is not a TGA image. |
| `TGA_ERROR_MALLOC` | Can not allocate memory. |
| `TGA_ERROR_EMPTY_IMAGE` | Image is empty, i.e. there is no image data. |
| `TGA_ERROR_NOT_SUPPORTED` | TGA format not supported by this version. |

`tga_header_t`

This type will contains TGA file header when TGA image will be loaded. Here
it's fields:

| Name | Type | Description |
| --- | --- | --- |
| `id_length` | `uint8_t` | Length of the TGA image description string. |
| `color_map_type` | `uint8_t` | Color type. Can be one of `tga_color_map_type_t` values. |
| `image_type` | `uint8_t` | Image map type. Can be one of `tga_image_type_t` values. |
| `color_map_specification` | `tga_color_map_t` | Color map descriptor. Has `tga_color_map_t` type. |
| `image_type_specification` | `tga_image_t` | Image type descriptor. Has `tga_image_t` type. |

`tga_color_map_type_t`

This type describes the color map of the TGA image. It can have one of the
follows values:

| Name | Description |
| --- | --- |
| `TGA_NO_COLOR_MAP` | There is no colom map. |
| `TGA_HAS_COLOR_MAP` | Color map is exists. |

`tga_image_type_t`

This type describes the image type of the TGA image, and can hold one of
values below:

| Name | Description |
| --- | --- |
| `TGA_NO_IMAGE` | TGA has no image (why this value can be used?) |
| `TGA_IMAGE_COLOR_MAPPED` | Color mapped image data. |
| `TGA_IMAGE_TRUECOLOR` | True color image data (RGB). |
| `TGA_IMAGE_GRAYSCALE` | Grayscale image data. |
| `TGA_IMAGE_RLE_COLOR_MAPPED` | Color mapped image data with RLE compression. |
| `TGA_IMAGE_RLE_TRUECOLOR` | True color image data with RLE compression. |
| `TGA_IMAGE_RLE_GRAYSCALE` | Grayscale image data with RLE compression. |

`tga_color_map_t`

This is the color map description structure.

| Name | Type | Description |
| --- | --- | --- |
| `first_entry_index` | `uint16_t` | Index of the first entry in color map table. |
| `color_map_length` | `uint16_t` | Number of the entries in color map table. |
| `color_map_entry_size` | `uint8_t` | Size of the color map entry. |

`tga_image_t`

This is the image description structure.

| Name | Type | Description |
| --- | --- | --- |
| `x_origin` | `uint16_t` | X origin position in the image. |
| `y_origin` | `uint16_t` | Y origin position in the image. |
| `width` | `uint16_t` | Width of the image. |
| `height` | `uint16_t` | Height of the image. |
| `pixel_depth` | `uint8_t` | Number of bits in the pixel. |
| `image_descriptor` | `uint8_t` | Some additional bitfields of image descriptor. |

-----

The TGALoader has function interface bellow.

```C
tga_error_t LoadTGAFromArray (const uint8_t* raw_data, size_t length, tga_header_t* header, uint8_t** data, bool flip)
```
This function allows to load TGA image from memory image, pointed by
`raw_data`. Size of the buffer is passed through `length` argument
in bytes. After successful loading of the image `header` will contain
header of the TGA file with full image description, `data` will point
to image array, and `TGA_NO_ERROR` will be returned.

You should not allocate memory for image array, pointed by `data`.
Function do this automatically. Image will be loaded from upper left corner
in any case of image origin position. To flip it vertically, just pass
`true` as `flip` argument.

Use `FreeTGA` to free any data, pointed by `data` argument after
successful image loading.

```C
tga_error_t LoadTGAFromFile (const char* file_name, tga_header_t* header, uint8_t** data, bool flip)
```
This function allows to load TGA image from file and works same as
`LoadTGAFromArray` function.

```C
void FreeTGA (uint8_t** data)
```
This function free memory, previously allocated by `LoadTGAFromArray` or
`LoadTGAFromFile`. Just pass pointer to the `data` array.

```C
tga_error_t SaveTGA (unsigned int width, unsigned int height, unsigned int bpp, const uint8_t* data, const char* file_name)
```
This function is used to save any pixel array to the TGA file. All you have
to do is determine size of the image (`width` and `height`), pixel
size in bytes `bpp` (can be 1, 2, 3 or 4), provide data array in
`data` argument and determine output file by it's `file_name`.

If argument `bpp` is out of range, or `data` is zero, or `width`
or `height` is zero, `SaveTGA` will return `TGA_ERROR_BAD_ARGUMENT` error.

```C
void TGALoaderVersion (char* str, size_t n)
```
`PNGLoaderVersion` function extract module version in N.N.N.N form,
where N is a number of version component. Version string will be copied into
`str` with null symbol at the end. To prevent buffer overflow `n`
argument must contain length of the buffer. Version strings are typically short
(for example 0.2.0.1); callers should pass the buffer length in `n`
to avoid overflow.
