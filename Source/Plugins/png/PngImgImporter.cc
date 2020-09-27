#include "PngImgImporter.hh"
#include <png.h>
#include <fstream>

namespace Solis
{

PngImgImporter::PngImgImporter()
{

}

PngImgImporter::~PngImgImporter()
{

}

void ReadCallback(png_struct* png, png_byte* data, png_size_t len)
{
	auto fs = (std::ifstream*)png_get_io_ptr(png);
	fs->read((char*)data, len);
	if (fs->gcount() != len)
		png_error(png, "Reading Error");
}

SPtr<Image> PngImgImporter::Import(const String& path)
{
	std::ifstream file(path, std::ios::in | std::ios::binary);
	if (!file.is_open())
		return nullptr;


	png_structp pngPtr;
	png_infop pngInfo;

	if((pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr)) == nullptr)
		return nullptr;

	if ((pngInfo = png_create_info_struct(pngPtr)) == nullptr)
		return nullptr;

	if (setjmp(png_jmpbuf(pngPtr)))
		return nullptr;

	png_set_read_fn(pngPtr, &file, ReadCallback);
	png_read_info(pngPtr, pngInfo);
}

} // namespace Solis