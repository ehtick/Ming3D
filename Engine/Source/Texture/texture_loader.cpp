#include "texture_loader.h"
#include "stb_image.h"

namespace Ming3D
{
    Texture* TextureLoader::LoadTextureData(const std::string inFilePath)
    {
        int texWidth, texHeight, channels;
        unsigned char* pixels = stbi_load(inFilePath.c_str(), &texWidth, &texHeight, &channels, 0);

        if (pixels == nullptr)
            return nullptr;

        Texture* texture = new Texture();

        unsigned int bytesPerPixel = static_cast<unsigned int>(channels);
        PixelFormat pixelFormat = (channels == 4) ? PixelFormat::RGBA : PixelFormat::RGB;

        const size_t textureSize = 4 * texWidth * texHeight; // Force 32 bit
        uint8_t* textureData = new uint8_t[textureSize];

        if (pixelFormat == PixelFormat::RGB && bytesPerPixel == 3)
        {
            pixelFormat = PixelFormat::RGBA;
            bytesPerPixel = 4;

            size_t destTextureIndex = 0;
            size_t sourceTextureIndex = 0;
            size_t destTextureSize = static_cast<size_t>(texWidth * texHeight * 4);
            while (destTextureIndex < destTextureSize)
            {
                textureData[destTextureIndex++] = pixels[sourceTextureIndex++];
                textureData[destTextureIndex++] = pixels[sourceTextureIndex++];
                textureData[destTextureIndex++] = pixels[sourceTextureIndex++];
                textureData[destTextureIndex++] = 255;
            }
        }
        else
        {
            memcpy(&textureData[0], pixels, textureSize);
        }

        texture->SetTextureData(textureData, bytesPerPixel, pixelFormat, texWidth, texHeight);

        delete[] textureData;
        stbi_image_free(pixels);
        return texture;
    }

    void TextureLoader::CreateEmptyTexture(Texture* outTexture)
    {
        const int bytesPerPixel = 4;
        const int textureWidth = 64;
        const int textureHeight = 64;
        uint8_t textureData[textureWidth * textureHeight];
        for (size_t iPixel = 0; iPixel < textureWidth * textureHeight; iPixel++)
            textureData[iPixel] = 255;

        outTexture->SetTextureData(textureData, bytesPerPixel, Ming3D::PixelFormat::RGBA, textureWidth, textureHeight);
    }
}
