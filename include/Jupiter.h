#ifndef JUPITER_H
#define JUPITER_H
#ifdef _WIN32 // Check if compiling for Windows
#include <windows.h> // Include windows.h for window management (only for Windows)
#include <GL/glut.h>
#elif __APPLE__ // Check if compiling for macOS
#define GL_SILENCE_DEPRECATION // Define GL_SILENCE_DEPRECATION only for macOS to suppress warnings
#include <GLUT/glut.h> // Include GLUT header for OpenGL (for macOS)
#else // Assume Linux or other platforms
#include <GL/glut.h> // Include GLUT header for OpenGL (for Linux)
#endif
#include <cmath>


void Filled_circle(float radius, float xc, float yc, float r, float g, float b);

void rock1(float x_location, float y_location, float scale);

void Building1(float x_location, float y_location, float scale);

void display();

void road();

#endif //JUPITER_H
