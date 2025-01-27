#ifdef _WIN32 // Check if compiling for Windows
#include <windows.h> // Include windows.h for window management (only for Windows)
#include <GL/glut.h>
#elif __APPLE__ // Check if compiling for macOS
#define GL_SILENCE_DEPRECATION // Define GL_SILENCE_DEPRECATION only for macOS to suppress warnings
#include <GLUT/glut.h> // Include GLUT header for OpenGL (for macOS)
#else // Assume Linux or other platforms
#include <GL/glut.h> // Include GLUT header for OpenGL (for Linux)
#endif

#include "ImageLoader.h"
#include "../include/Jupiter.h"


//Main Function
int main(int argc, char **argv) {
    glutInit(&argc, argv); // Initialize GLUT

    glutInitWindowSize(4000, 2500); // Set the window's initial width & height
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Jupiter");
    glutDisplayFunc(display);
    gluOrtho2D(0, 300, 0, 200); // for axis change
    glutMainLoop();

    return 0;
}
