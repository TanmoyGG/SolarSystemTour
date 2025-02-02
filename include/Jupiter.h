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
#include <string>

int static currentScene = 0; // Current scene number

constexpr float PI = 3.14159265359;

//static int currentScene = 0; // Current scene number

//for starts
constexpr int numStars =400; // Number of stars
inline float starPositions[numStars][2]; // Array to store star positions
inline float starVelocities[numStars][2]; // Array to store star velocities

//for mainRocket
inline float rocketY = 55.0f; // Initial position
inline bool isMovingUp = false;  // True if moving up
inline bool isMovingDown = false; // True if moving down

//for miniRocket
inline float miniRocketY = 0.0f;
inline bool miniRocketUp = false;
inline bool miniRocketDown = false;

//for sun
inline float sunScale = 1.0f;
inline bool sunScalingUp = true;

//for redMoonLines
inline float redMoonLinesOffset = 0.0f;
constexpr float redMoonWidth = 28.43f; // Adjust based on precise calculation if needed

//for brownMoonLines
inline float brownMoonLinesOffset = 0.0f;
constexpr float brownMoonWidth = 41.278502652287; // Calculated width based on x-radius

//for car
inline float carX = -58.52988f; // Start off-screen left
inline float carSpeed = 1.0f;   // Adjust speed as needed

//for satellite
inline float satelliteX = 300.0f - 215.6f; // Initial position at the right edge
constexpr float satelliteRightmost = 245.64f; // Rightmost vertex's X coordinate

//for scence 0
inline float planetAngles[8] = {0}; // Angles for the planets



void Scene0();

struct RGB
{
    float r; ///< Red component (0.0 to 1.0)
    float g; ///< Green component (0.0 to 1.0)
    float b; ///< Blue component (0.0 to 1.0)
};

RGB HexToRGB(const std::string& hex);

void renderText(float x, float y, void* font, const char* text);

void initializeStars();

void drawStars();

void updateStars();

void drawCircle(float x, float y, float radius) ;

void drawFilledCircle(float x, float y, float radius);

void drawCircleWithColorFromPoints(float cx, float cy, float px, float py, const std::string& hexColor,
                                   int segments = 100);

void drawCircleWithColorFromPointsBorder(float cx, float cy, float px, float py, const std::string& hexColor,
                                   int segments = 100);

void Filled_circle(float radius, float xc, float yc, float r, float g, float b);

void Empty_circle(float radius, float xc, float yc, float r, float g, float b);

void car();

void igloo();

void sun();

void observatory();

void brownMoon();

void brownMoonLines();

void redMoon();

void redMoonLines();

void surface();

void miniRocket(float x, float y);

void mainRocket();

void satellite();

void brokenSatellite(float x, float y);

void handleKeyboard(unsigned char key, int x, int y);

void mouseClick(int button, int state, int x, int y);

void update(int value);

void display();



#endif //JUPITER_H
