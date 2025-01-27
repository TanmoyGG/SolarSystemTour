
#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <memory>
#include <GL/gl.h>
#include <GL/glut.h>
#include <windows.h>
#include <mmsystem.h>
#include <bits/stl_algo.h>

using namespace std;

class TextureInfo {
public:
    int imageWidth = 0;
    int imageHeight = 0;
    unique_ptr<GLubyte[]> imageData;
    GLuint textureID = 0;

    explicit TextureInfo(const string& filename) {// if (!file) {
        //     cerr << "Error opening file: " << filename << endl;
        //     exit(1);
        // }
        std::ifstream file(filename, std::ios::binary);


        file.seekg(18, std::ios::beg);
        file.read(reinterpret_cast<char*>(&imageWidth), sizeof(int));
        file.read(reinterpret_cast<char*>(&imageHeight), sizeof(int));

        int imageSize = imageWidth * imageHeight * 3;
        imageData = std::make_unique<GLubyte[]>(imageSize);

        file.seekg(54, std::ios::beg); // Skip the header
        file.read(reinterpret_cast<char*>(imageData.get()), imageSize);

        // Swap red and blue channels
        for (int i = 0; i < imageSize; i += 3) {
            std::swap(imageData[i], imageData[i + 2]);
        }

        file.close();

        glEnable(GL_TEXTURE_2D);
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData.get());
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
    }
};

inline vector<TextureInfo> textures;

inline void loadImageAndStore(const string& filename) {
    textures.emplace_back(filename);
}

inline void ApplyTexture(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, GLuint texture) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2f(x1, y1);
    glTexCoord2f(1.0, 1.0); glVertex2f(x2, y2);
    glTexCoord2f(1.0, 0.0); glVertex2f(x3, y3);
    glTexCoord2f(0.0, 0.0); glVertex2f(x4, y4);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}




#endif
