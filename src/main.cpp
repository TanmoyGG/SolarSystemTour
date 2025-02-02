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


void initializeStars();
void update(int i);
void handleKeyboard(unsigned char c, int i, int arg);
void mouseClick(int i, int arg, int i1, int arg1);
//Main Function
int main(int argc, char **argv) {
    glutInit(&argc, argv); // Initialize GLUT

    glutInitWindowSize(3000, 2000); // Set the window's initial width & height
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_STENCIL);
    glutCreateWindow("Jupiter");
    glutDisplayFunc(display);
    gluOrtho2D(0, 300, 0, 170); // for axis
    srand(static_cast<unsigned>(time(0))); // Seed for random stars
    initializeStars(); // Initialize star positions and velocities
    glutMouseFunc(mouseClick);
    glutKeyboardFunc(handleKeyboard);
    glutTimerFunc(16, update, 0);
    glutMainLoop();

    return 0;
}
