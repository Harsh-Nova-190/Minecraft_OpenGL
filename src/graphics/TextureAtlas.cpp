//#include "TextureAtlas.h";
//#define STB_IMAGE_IMPLEMENTATION
//#include <stb_image.h>
//
//TextureAtlas::TextureAtlas(const char* path)
//{
//    glGenTextures(1, &textureID);
//    glBindTexture(GL_TEXTURE_2D, textureID);
//
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//
//    int width, height, channels;
//
//    unsigned char* data = stbi_load(path, &width, &height, &channels, 0);
//
//    if (data)
//    {
//        GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;
//
//        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//    }
//
//    stbi_image_free(data);
//}
//
//void TextureAtlas::bind() const
//{
//    glBindTexture(GL_TEXTURE_2D, textureID);
//}