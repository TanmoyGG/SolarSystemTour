#include "Jupiter.h"
#include "ImageLoader.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <cmath>
#include <cstdlib>
#include <ctime>


//funtion for text
void renderText(float x, float y, void* font, const char* text) {
    glRasterPos2f(x, y); // Set the position
    while (*text) {
        glutBitmapCharacter(font, *text); // Render each character
        text++;
    }
}

// Function to initialize star positions and velocities
void initializeStars() {
    float speedFactor = 5.0f; // Increase this value to make stars move faster

    for (int i = 0; i < numStars; ++i) {
        starPositions[i][0] = (rand() % 300 - 150) / 1.0f; // Random x between -150 and 150
        starPositions[i][1] = (rand() % 200 - 100) / 1.0f; // Random y between -100 and 100

        starVelocities[i][0] = ((rand() % 20 - 10) / 1000.0f) * speedFactor; // Increase speed
        starVelocities[i][1] = ((rand() % 20 - 10) / 1000.0f) * speedFactor; // Increase speed
    }
}
// Function to draw stars
void drawStars() {
    glPointSize(6.0f); //width of the starts
    glBegin(GL_POINTS);
    glColor3f(1.0, 1.0, 1.0); // White color for stars
    for (int i = 0; i < numStars; ++i) {
        glVertex2f(starPositions[i][0] + 150, starPositions[i][1] + 100); // Adjusting for new origin
    }
    glEnd();
}

// Function to update star positions
void updateStars() {
    for (int i = 0; i < numStars; ++i) {
        starPositions[i][0] += starVelocities[i][0];
        starPositions[i][1] += starVelocities[i][1];

        // Wrap around if the star moves out of bounds
        if (starPositions[i][0] > 300) starPositions[i][0] = 0;
        // if (starPositions[i][0] < 0) starPositions[i][0] = 300;
        if (starPositions[i][1] > 200) starPositions[i][1] = 0;
        //if (starPositions[i][1] < 0) starPositions[i][1] = 200;
    }
}

// Function to draw a circle (used for orbits and planets)
void drawCircle(float x, float y, float radius) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; ++i) {
        float angle = i * PI / 180.0f;
        glVertex2f(x + cos(angle) * radius, y + sin(angle) * radius);
    }
    glEnd();
}

void drawFilledCircle(float x, float y, float radius) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // Center
    for (int i = 0; i <= 360; ++i) {
        float angle = i * PI / 180.0f;
        glVertex2f(x + cos(angle) * radius, y + sin(angle) * radius);
    }
    glEnd();
}


void Scene0() {
    // Draw stars
    drawStars();

    // Draw the Sun
    glColor3f(1.0, 1.0, 0.0); // Yellow color
    drawFilledCircle(150, 100, 5); // Adjusted position for new origin

    // Draw orbits and planets
    float orbitRadii[8] = {15, 25, 35, 45, 55, 65, 75, 85};
    float planetSizes[8] = {2, 2.5, 3, 2.8, 3.5, 3, 2.5, 2};
    glColor3f(0.5, 0.5, 0.5); // Gray color for orbits
    for (int i = 0; i < 8; ++i) {
        drawCircle(150, 100, orbitRadii[i]); // Adjusted position for new origin
    }

    // Draw planets
    for (int i = 0; i < 8; ++i)
    {
        float x = 150 + orbitRadii[i] * cos(planetAngles[i]); // Adjusted for new origin
        float y = 100 + orbitRadii[i] * sin(planetAngles[i]); // Adjusted for new origin
        //
        glColor3ub(50 + i * 20, 100 + i * 15, 200 - i * 10); // Unique colors for planets

        drawFilledCircle(x, y, planetSizes[i]);
    }
}

RGB HexToRGB(const std::string& hex)
{
    if (hex.empty() || hex[0] != '#' || hex.length() != 7)
    {
        throw std::invalid_argument("Invalid hex color format");
    }

    RGB rgb = {0.0f, 0.0f, 0.0f};
    std::stringstream ss;
    ss << std::hex << hex.substr(1);
    unsigned int hexValue;
    ss >> hexValue;

    rgb.r = ((hexValue >> 16) & 0xFF) / 255.0f;
    rgb.g = ((hexValue >> 8) & 0xFF) / 255.0f;
    rgb.b = (hexValue & 0xFF) / 255.0f;

    return rgb;
}

// Function to draw a circle with a specified color in hex format
void drawCircleWithColorFromPoints(float cx, float cy, float px, float py, const std::string& hexColor,
                                   int segments)
{
    RGB rgb = HexToRGB(hexColor);
    float radius = sqrt((px - cx) * (px - cx) + (py - cy) * (py - cy));
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(cx, cy);
    for (int i = 0; i <= segments; i++)
    {
        float theta = 2.0f * PI * float(i) / float(segments);
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}


void drawCircleWithColorFromPointsBorder(float cx, float cy, float px, float py, const std::string& hexColor,
                                   int segments)
{
    RGB rgb = HexToRGB(hexColor);
    float radius = sqrt((px - cx) * (px - cx) + (py - cy) * (py - cy));
    glLineWidth(5);
    glBegin(GL_LINE_LOOP);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(cx, cy);
    for (int i = 0; i <= segments; i++)
    {
        float theta = 2.0f * PI * float(i) / float(segments);
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}


void Filled_circle(float radius, float xc, float yc, float r, float g, float b)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < 200; i++)
    {
        glColor3ub(r, g, b);
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = radius;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x + xc, y + yc);
    }
    glEnd();
}

void Empty_circle(float radius, float xc, float yc, float r, float g, float b)
{
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 200; i++)
    {
        glColor3ub(r, g, b);
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = radius;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x + xc, y + yc);
    }
    glEnd();
}

void car()
{
    glPushMatrix();
    glTranslatef(carX, 0.0f, 0.0f); // Move the car horizontally
    //body
    glBegin(GL_POLYGON);
    glColor3ub(164, 171, 163);
    glVertex2f(2.2456800477, 31.673194240562);
    glVertex2f(2.2456800477, 33.9179114106088);
    glVertex2f(10.725722690074, 46.4802571933545);
    glVertex2f(57.3777979492327, 46.4802571933545);
    glVertex2f(58.5298846446336, 31.8394695864914);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(192, 201, 196);
    glVertex2f(6.3335424635594, 40.4912873156903);
    glVertex2f(10.725722690074004, 47.30307675792473);
    glVertex2f(33.2370564758544, 46.9060362026951);
    glVertex2f(30.1943046682655, 40.4912873156903);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(192, 201, 196);
    glVertex2f(2.2456800477, 31.673194240562);
    glVertex2f(2.2456800477, 33.9179114106088);
    glVertex2f(4.6431744737678, 37.5833974459764);
    glVertex2f(30.3913992157656, 37.5833974459764);
    glVertex2f(38.0006534064064, 31.77882193143);
    glEnd();

    //windows
    glBegin(GL_POLYGON);
    drawCircleWithColorFromPoints(6.3293296132683, 34.2754748508397, 5.3163821110982, 33.0977217943002, "#a4aba3");
    drawCircleWithColorFromPoints(11.6919511684047, 34.3446699676804, 10.6790036662345, 33.1669169111409, "#a4aba3");
    drawCircleWithColorFromPoints(16.8224577627067, 34.31007240926, 15.8095102605366, 33.1323193527205, "#a4aba3");
    drawCircleWithColorFromPoints(22.0020235776346, 34.3446699676804, 20.9890760754645, 33.1669169111409, "#a4aba3");
    drawCircleWithColorFromPoints(27.3992426911912, 34.517657759782, 26.3862951890211, 33.3399047032425, "#a4aba3");

    //back tires
    Filled_circle(5.8516166302363, 29.7235031805977, 24.1918044803513, 76, 81, 83);
    Filled_circle(5.8516166302363, 17.0594111800268, 24.5784943124309, 76, 81, 83);

    //left lower part
    glBegin(GL_POLYGON);
    glColor3ub(164, 171, 163);
    glVertex2f(2.2456800477, 31.673194240562);
    glVertex2f(40.0006666667, 32.673194240562);
    glVertex2f(40.0814082004037, 28.9862651795987);
    glVertex2f(35.8329180468516, 27.4339322388732);
    glVertex2f(34.9452256264859, 25.8953826113703);
    glVertex2f(11.7233747656474, 26.4355208437862);
    glVertex2f(2.2456800477, 31.673194240562);
    glEnd();

    Filled_circle(5.8516166302363, 52.3187201296691, 23.8401133016048, 76, 81, 83);
    //lower right part
    glBegin(GL_POLYGON);
    glColor3ub(164, 171, 163);
    glVertex2f(42.0006666667, 32.673194240562);
    glVertex2f(56.3400532111126, 32.8458258598826);
    glVertex2f(56.3809040779737, 25.9633010318701);
    glVertex2f(42, 26);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(49, 74, 111);
    glVertex2f(30.2936189462574, 40.4196662346431);
    glVertex2f(49.290578053485, 40.3746497438675);
    glVertex2f(49.3806110350359, 37.5386108250078);
    glVertex2f(30.3386354370328, 37.6736602973345);
    glEnd();

    //window
    glClear(GL_STENCIL_BUFFER_BIT);
    glEnable(GL_STENCIL_TEST);
    glStencilMask(0xFF); // Allow writing to stencil buffer

    // Step 1: Create the mask (big circle)
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); // Disable color writing
    glStencilFunc(GL_ALWAYS, 1, 0xFF); // Always pass stencil test
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE); // Replace stencil buffer with 1

    drawCircleWithColorFromPoints(55.3325506918578, 39.3348986162824, 62.6036306198917, 36.4951792725143, "#53a7bc");

    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); // Re-enable color writing
    glStencilFunc(GL_EQUAL, 1, 0xFF); // Only draw where stencil is 1
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); // Keep stencil values unchanged

    // Step 2: Draw objects inside the mask
    drawCircleWithColorFromPoints(55.3325506918578, 39.3348986162824, 62.6036306198917, 36.4951792725143, "#53a7bc");
    drawCircleWithColorFromPoints(54.2493606569666, 42.552162352394, 60.3412503389444, 38.2311708337692, "#68c2dd");
    drawCircleWithColorFromPoints(54.249360656966616, 42.55216235239397, 52.2659547139971, 40.7104282624883, "#8ccee4");
    drawCircleWithColorFromPoints(55.3289553122442, 41.1444835254431, 55.4958718031845, 39.9343389661228, "#c4e6f2");

    glDisable(GL_STENCIL_TEST); // Disable stencil test when done

    //window border
    drawCircleWithColorFromPointsBorder(55.3325506918578, 39.3348986162824, 62.6036306198917, 36.4951792725143, "#314c72");

    //front tires
    Filled_circle(5.8516166302363, 10.9751357089674, 24.0245283278101, 1, 1, 1);
    Filled_circle(1.5067841239815343899919067043631, 10.9751357089674, 24.0245283278101, 36, 132, 160);

    Filled_circle(5.8516166302363, 23.612061999563977, 23.775115308915964, 1, 1, 1);
    Filled_circle(1.5067841239815343899919067043631, 23.612061999563977, 23.775115308915964, 36, 132, 160);

    Filled_circle(5.8516166302363, 45.72668300810807, 23.691977635951268, 1, 1, 1);
    Filled_circle(1.5067841239815343899919067043631, 45.72668300810807, 23.691977635951268, 36, 132, 160);

    glPopMatrix();
}

void igloo()
{
    RGB rgb;


    glClear(GL_STENCIL_BUFFER_BIT);
    glEnable(GL_STENCIL_TEST);
    glStencilMask(0xFF); // Allow writing to stencil buffer

    // Step 1: Create the mask (big circle)
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); // Disable color writing
    glStencilFunc(GL_ALWAYS, 1, 0xFF); // Always pass stencil test
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE); // Replace stencil buffer with 1

    drawCircleWithColorFromPoints(268.7595688908884f, 31.9843087701877f, 295.6259712753029f, 19.8104701897144f,
                                  "#777e77");

    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); // Re-enable color writing
    glStencilFunc(GL_EQUAL, 1, 0xFF); // Only draw where stencil is 1
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); // Keep stencil values unchanged

    // Step 2: Draw objects inside the mask
    drawCircleWithColorFromPoints(268.7595688908884f, 31.9843087701877f, 295.6259712753029f, 19.8104701897144f,
                                  "#777e77");
    drawCircleWithColorFromPoints(253.2274300123989, 56.1920567520483, 284.1517785902925, 24.7079914577209, "#8c918b");
    drawCircleWithColorFromPoints(257.1454470267926, 50.8747479467841, 274.4966652333936, 28.6260084721261, "#a6ada5");

    glDisable(GL_STENCIL_TEST); // Disable stencil test when done

    glBegin(GL_POLYGON);
    glColor3ub(166, 173, 165);
    glVertex2f(210.6986149514534, 46.8506872913749);
    glVertex2f(257.2853762058782, 46.6768725742072);
    glVertex2f(258.3719534431812, 18.3467191006796);
    glVertex2f(204.1151288692091, 18.498557229152);
    glEnd();

    drawCircleWithColorFromPoints(211.6474435887148, 39.4498239207145, 210.8288887494949, 46.8168017532931, "#c1cbc2");

    glBegin(GL_POLYGON);
    rgb = HexToRGB("#c1cbc2");
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(204.0636686565655, 40.187540393378);
    glVertex2f(219.1989938704833, 40.3886742832646);
    glVertex2f(219.0481434530689, 18.3142298682169);
    glVertex2f(204.21451907398, 18.3645133406886);
    glEnd();

    glClear(GL_STENCIL_BUFFER_BIT);
    glEnable(GL_STENCIL_TEST);
    glStencilMask(0xFF); // Allow writing to stencil buffer

    // Step 1: Create the mask (big circle)
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); // Disable color writing
    glStencilFunc(GL_ALWAYS, 1, 0xFF); // Always pass stencil test
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE); // Replace stencil buffer with 1

    drawCircleWithColorFromPoints(211.6474435887148, 34.7056807343938, 211.2046568913262, 40.5884182854315, "#585f58");
    glBegin(GL_POLYGON);
    glVertex2f(205.7853482824004, 35.7574911655125);
    glVertex2f(217.3756587557582, 35.7574911655125);
    glVertex2f(217.3250460462676, 18.4479445196612);
    glVertex2f(205.6335101539284, 18.4479445196612);
    glEnd();

    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); // Re-enable color writing
    glStencilFunc(GL_EQUAL, 1, 0xFF); // Only draw where stencil is 1
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); // Keep stencil values unchanged

    // Step 2: Draw objects inside the mask
    drawCircleWithColorFromPoints(211.6474435887148, 34.7056807343938, 211.2046568913262, 40.5884182854315, "#585f58");
    rgb = HexToRGB("#585f58");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(205.7853482824004, 35.7574911655125);
    glVertex2f(217.3756587557582, 35.7574911655125);
    glVertex2f(217.3250460462676, 18.4479445196612);
    glVertex2f(205.6335101539284, 18.4479445196612);
    glEnd();

    drawCircleWithColorFromPoints(214.3674190155307, 34.3894045219724, 211.6474435887148, 39.4498239207145, "#717670");

    glBegin(GL_POLYGON);
    rgb = HexToRGB("#717670");
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(208.337763816642, 35.5614609259876);
    glVertex2f(217.3756587557582, 35.7574911655125);
    glVertex2f(217.3250460462676, 18.4479445196612);
    glVertex2f(208.4886142340564, 18.4147968131602);
    glEnd();


    glDisable(GL_STENCIL_TEST); // Disable stencil test when done

    // Shadow
    // Enable Stencil Test
    glClear(GL_STENCIL_BUFFER_BIT);
    glEnable(GL_STENCIL_TEST);

    glStencilMask(0xFF); // Allow writing to stencil buffer

    // Step 1: Create the mask (big polygon)
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); // Disable color writing
    glStencilFunc(GL_ALWAYS, 1, 0xFF); // Always pass stencil test
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE); // Replace stencil buffer with 1

    glBegin(GL_POLYGON);
    glVertex2f(204.2648025464663, 18.4650802856318);
    glVertex2f(297.5155022448433, 18.5148609233787);
    glVertex2f(298.2456182651294, 0.0794314111033);
    glVertex2f(205, 0);
    glEnd();

    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); // Re-enable color writing

    // Step 2: Draw objects inside the masked area
    glStencilFunc(GL_EQUAL, 1, 0xFF); // Only draw where stencil is 1
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); // Keep stencil values unchanged

    drawCircleWithColorFromPoints(268.6150764418572, 30.9876762699677, 273.4216735754071, 1.4788204499889, "#c76447");

    glBegin(GL_POLYGON);
    rgb = HexToRGB("#c76447");
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(204.2648025464663, 18.4650802856318);
    glVertex2f(249.0844728992055, 18.271488916616);
    glVertex2f(249.3886879076578, 8.5974516477982);
    glVertex2f(204.2648025464663, 9.0117874609645);
    glEnd();

    // Disable Stencil Test
    glDisable(GL_STENCIL_TEST);


    glBegin(GL_POLYGON);
    rgb = HexToRGB("#239da7");
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(234.3037179811817, 32.1711773928383);
    glVertex2f(258.1298248271819, 32.3725247746361);
    glVertex2f(258.3311722089791, 31.0302088959844);
    glVertex2f(234.3708337751141, 30.9630931020518);
    glEnd();

    glBegin(GL_POLYGON);
    rgb = HexToRGB("#239da7");
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(234.0352548054522, 29.8221246051978);
    glVertex2f(258.0627090332495, 29.956356193063);
    glVertex2f(257.9955932393171, 28.8825034901416);
    glVertex2f(234.2366021872493, 28.7482719022764);
    glEnd();

    glBegin(GL_POLYGON);
    rgb = HexToRGB("#239da7");
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(234.2366021872493, 27.5401876114899);
    glVertex2f(258.1298248271818, 27.5401876114899);
    glVertex2f(257.9284774453847, 26.4663349085685);
    glVertex2f(234.0352548054522, 26.4663349085685);
    glEnd();

    glBegin(GL_POLYGON);
    rgb = HexToRGB("#239da7");
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(234.3037179811817, 32.1711773928383);
    glVertex2f(234.3708337751141, 30.9630931020518);
    glVertex2f(234.2366021872493, 28.7482719022764);
    glVertex2f(234.0352548054522, 26.4663349085685);
    glEnd();
}

void sun()
{

    glPushMatrix();
    // Translate to the sun's center, scale, then translate back
    glTranslatef(28.5453790294203, 142.4141173973897, 0.0f);
    glScalef(sunScale, sunScale, 1.0f);
    glTranslatef(-28.5453790294203, -142.4141173973897, 0.0f);

    drawCircleWithColorFromPoints(28.5453790294203, 142.4141173973897, 52.8075467215715, 130.3690696069257, "#f4b12d");
    drawCircleWithColorFromPoints(28.5453790294203, 142.4141173973897, 46.9160736752048, 133.7192955225103, "#ffde02");
    drawCircleWithColorFromPoints(28.5453790294203, 142.4141173973897, 42.4832200440603, 138.1123146150812, "#fcc52a");

    glPopMatrix();
}

void observatory()
{
    glClear(GL_STENCIL_BUFFER_BIT);
    glEnable(GL_STENCIL_TEST);
    glStencilMask(0xFF); // Allow writing to stencil buffer

    // Step 1: Create the mask (big circle)
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); // Disable color writing
    glStencilFunc(GL_ALWAYS, 1, 0xFF); // Always pass stencil test
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE); // Replace stencil buffer with 1

    drawCircleWithColorFromPoints(177.029381182655, 67.1894061421685, 195.613169202175, 73.5560742599852, "#a6ada6");

    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); // Re-enable color writing
    glStencilFunc(GL_EQUAL, 1, 0xFF); // Only draw where stencil is 1
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); // Keep stencil values unchanged

    // Step 2: Draw objects inside the mask
    drawCircleWithColorFromPoints(177.029381182655, 67.1894061421685, 195.613169202175, 73.5560742599852, "#a6ada6");
    drawCircleWithColorFromPoints(170.6627130648565, 78.0299491535861, 186.6654194149987, 71.4912089244771, "#c1cbc2");

    glDisable(GL_STENCIL_TEST); // Disable stencil test when done

    //border
    Empty_circle(19.60358194339553599938864885008,177.0962338826327, 67.1100767437935,0,0,0);

    //lines
    RGB rgb;
    rgb = HexToRGB("#c0cbc5");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(157.4458781726765, 58.9128778102893);
    glVertex2f(196.6408671134627, 58.9128778102893);
    glVertex2f(196.0527754913188, 57.0910754658431);
    glVertex2f(157.8621437174844, 57.0910754658431);
    glEnd();

    //lines
    rgb = HexToRGB("#0fa1b0");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(159.4440720128654, 57.2380983713795);
    glVertex2f(194.8167807959704, 57.1717512244105);
    glVertex2f(194.6373208700283, 55.9841126228599);
    glVertex2f(159.4407528241695, 55.8220409357719);
    glEnd();

    //stand
    rgb = HexToRGB("#656e69");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(172.7570429547883, 56.0611620008663);
    glVertex2f(182.4027332424741, 56.0611620008663);
    glVertex2f(190.7091929308247, 43.5992387759877);
    glVertex2f(163.4948120841024, 43.5992387759877);
    glEnd();

    //stand
    rgb = HexToRGB("#c2cac3");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(157.3427093108958, 43.5327113771561);
    glVertex2f(196.6796414575864, 43.5327113771561);
    glVertex2f(196.2424173102948, 41.5678131670386);
    glVertex2f(157.9430661649192, 41.5362329107357);
    glEnd();

    //stand
    rgb = HexToRGB("#0da1b2");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(159.438432826516, 41.6232186659512);
    glVertex2f(194.7553943392681, 41.6730583965663);
    glVertex2f(194.7750308368109, 40.5773315673932);
    glVertex2f(159.4371037682445, 40.5608760910941);
    glEnd();

    //stand
    rgb = HexToRGB("#c1cbc2");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(161.1826044383416, 33.0247657394193);
    glVertex2f(161.1826044383416, 40.7042096810933);
    glVertex2f(193.0734987801221, 40.7042096810933);
    glVertex2f(193.0734987801221, 33.0247657394193);
    glEnd();

}

void brownMoon()
{
    glClear(GL_STENCIL_BUFFER_BIT);
    glEnable(GL_STENCIL_TEST);
    glStencilMask(0xFF); // Allow writing to stencil buffer

    // Step 1: Create the mask (big circle)
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); // Disable color writing
    glStencilFunc(GL_ALWAYS, 1, 0xFF); // Always pass stencil test
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE); // Replace stencil buffer with 1

    drawCircleWithColorFromPoints(63.6338598413246, 57.381295798505, 79.2924219688832, 43.2713826725329, "#92692c");

    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); // Re-enable color writing
    glStencilFunc(GL_EQUAL, 1, 0xFF); // Only draw where stencil is 1
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); // Keep stencil values unchanged

    // Step 2: Draw objects inside the mask
    drawCircleWithColorFromPoints(63.6338598413246, 57.381295798505, 79.2924219688832, 43.2713826725329, "#92692c");
    drawCircleWithColorFromPoints(58.6437686138609, 62.0272428033983, 75.6789076317543, 46.1966085645027, "#b7823c");
    drawCircleWithColorFromPoints(53.6536773863972, 64.9524686953681, 70, 50, "#e7a54f");

    glDisable(GL_STENCIL_TEST); // Disable stencil test when done
    glEnd();
}

void brownMoonLines()
{
    RGB rgb;
    rgb = HexToRGB("#d4884a");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(45.8336511494115, 68.0086987193219);
    glVertex2f(57.1362091904049, 68.0086987193219);
    glVertex2f(58.2664649945042, 66.313315013168);
    glVertex2f(62.5049242598768, 66.2568022229629);
    glVertex2f(63.2395905325413, 64.2223417755781);
    glVertex2f(65.7826660917648, 64.1093161951679);
    glVertex2f(65.9522044623797, 61.5097278457318);
    glVertex2f(43.1775500097781, 61.4532150555267);
    glEnd();

    rgb = HexToRGB("#aa6d2f");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(58.3794905749142, 77.3333091031686);
    glVertex2f(67.4215370077089, 77.5593602639892);
    glVertex2f(74.090046251895, 75.2988486557839);
    glVertex2f(78.2719927270625, 71.455978921835);
    glVertex2f(70.9253300004168, 71.455978921835);
    glVertex2f(70.4732276787771, 73.8295161104505);
    glVertex2f(64.0307695954109, 73.9425416908607);
    glVertex2f(63.5786672737711, 74.7902335439377);
    glVertex2f(63.861231224796, 76.4291044598865);
    glVertex2f(58.4925161553241, 76.203053299066);
    glEnd();

    rgb = HexToRGB("#d4884b");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(42.7254476881383, 58.571062755065);
    glVertex2f(54.4235952605665, 58.3450115942444);
    glVertex2f(54.8756975822062, 56.9887046293213);
    glVertex2f(56.6275940785602, 56.7061406782956);
    glVertex2f(57.1927219806099, 55.1802953427571);
    glVertex2f(56.2320045471254, 54.0500395386544);
    glVertex2f(43.1210372195731, 54.1630651190647);
    glEnd();

    rgb = HexToRGB("#d5894f");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(83.8102461671493, 61.7357790065523);
    glVertex2f(71.7165090632864, 61.9618301673729);
    glVertex2f(71.4904579024665, 59.4752673983471);
    glVertex2f(68.1562032803735, 59.3622418179368);
    glVertex2f(68.0996904901685, 57.2147557901418);
    glVertex2f(65.2740509799201, 57.1017302097315);
    glVertex2f(65.7261533015599, 54.5586546505006);
    glVertex2f(74.2595846225099, 54.3891162798852);
    glVertex2f(74.9942508951745, 53.0328093149621);
    glVertex2f(83.7537333769443, 52.8067581541415);
    glEnd();

    rgb = HexToRGB("#d4884a");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(43.5166267510079, 51.6765023500389);
    glVertex2f(61.0921045047526, 51.5634767696287);
    glVertex2f(61.5442068263923, 49.9246058536798);
    glVertex2f(64.0872823856158, 49.7550674830644);
    glVertex2f(64.8219486582804, 47.9466581965002);
    glVertex2f(68.2692288607834, 47.6075814552694);
    glVertex2f(68.890869553038, 45.6296337980898);
    glVertex2f(65.6696405113549, 43.143071029064);
    glVertex2f(47.74996717692, 42.1408865877326);
    glEnd();
}

void redMoon()
{

    glClear(GL_STENCIL_BUFFER_BIT);
    glEnable(GL_STENCIL_TEST);
    glStencilMask(0xFF);

    // Step 1: Create the mask (big circle)
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);

    drawCircleWithColorFromPoints(274.2507, 142.6, 283.3073, 134.6850, "#98524d");

    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glStencilFunc(GL_EQUAL, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

    // Step 2: Draw objects inside the mask
    drawCircleWithColorFromPoints(274.2507, 142.6, 283.3073, 134.6850, "#98524d");
    drawCircleWithColorFromPoints(271.3587, 145.1115, 283.0029, 138.2620, "#bd6762");
    drawCircleWithColorFromPoints(270.2171, 145.8726, 280, 140, "#ed847e");

    glDisable(GL_STENCIL_TEST);

}

void redMoonLines()
{
    RGB rgb;
    rgb = HexToRGB("#bb575b");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(274.4942679907466, 152.3750600161717);
    glVertex2f(280.944047594181, 152.3264539075606);
    glVertex2f(282.3835904296724, 151.0726402022352);
    glVertex2f(275, 151);
    glEnd();

    rgb = HexToRGB("#e97178");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(263.203309198139, 146.4141907094423);
    glVertex2f(280.7389882168257, 146.3195737363197);
    glVertex2f(280.4866762884993, 144.9633971215611);
    glVertex2f(262.9042364283356, 144.9806103908639);
    glEnd();

    rgb = HexToRGB("#b05757");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(262.5222252377746, 143.4075755773427);
    glVertex2f(273.6979815509181, 143.4358350219836);
   glVertex2f(273.4475944371701, 141.9752435251154);
    glVertex2f(262.4720868917959, 142.1165131683863);
    glEnd();

    rgb = HexToRGB("#b65b5a");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(274.4371261639793, 141.1557992384803);
    glVertex2f(286.0212089491178, 141.0691892737314);
    glVertex2f(285.6314641077486, 139.6834298377482);
    glVertex2f(274.6753035670382, 139.8566497672461);
    glEnd();

    rgb = HexToRGB("#e97276");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(263.6325330615792, 138.4275853488884);
    glVertex2f(273.657636481241, 138.3842803665139);
    glVertex2f(274.025728831423, 137.7130531397096);
    glVertex2f(280.0884263638319, 137.6047906837734);
    glVertex2f(278.2912695952964, 135.2230166531772);
    glVertex2f(265.6297717787707, 135.0357958568862);
    glEnd();


}

void surface()
{
    RGB rgb;
    rgb = HexToRGB("#ea7554");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(0, 0);
    glVertex2f(-0.2443229834633, 42.2326691420568);
    glVertex2f(300.3363317851818, 41.5541009747976);
    glVertex2f(300, 0);
    glEnd();

    //left mountain
    rgb = HexToRGB("#ea7554");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(0, 70);
    glVertex2f(2.6487600739838, 67.3639411120418);
    glVertex2f(14.2453045994443, 66.3331371542201);
    glVertex2f(30.6522675947255, 62.7253233018441);
    glVertex2f(47.74996717692, 42.1408865877326);
    glVertex2f(0.0034292797742, 42.0617936586308);
    glEnd();

    //shadow
    rgb = HexToRGB("#c76447");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(1.7732658657762, 67.1009594368954);
    glVertex2f(34.4982119304786, 44.921725446534);
    glVertex2f(9.508802516343, 44.2267358255826);
    glVertex2f(10.0224904970447, 57.1595861632865);
    glVertex2f(1.7732658657762, 67.1009594368954);
    glEnd();

    //shadow
    rgb = HexToRGB("#ed8558");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(14.2453045994443, 66.3331371542201);
    glVertex2f(28.1711269275791, 63.2709144433124);
    glVertex2f(32.7028567392024, 51.5389927876575);
    glVertex2f(14.2453045994443, 66.3331371542201);
    glEnd();

    //shadow
    rgb = HexToRGB("#c76447");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(0.026828736948, 33.1811079913854);
    glVertex2f(41.1615755927083, 29.4012387497841);
    glVertex2f(41.3137929107465, 23.4267090167641);
    glVertex2f(-0.4419632755503, 15.9583270911503);
    glVertex2f(0.026828736948, 33.1811079913854);
    glEnd();


    //right mountain
    rgb = HexToRGB("#ea7554");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(300, 81.757975488795);
    glVertex2f(298.5343358210881, 82.5502349826301);
    glVertex2f(285.8047911386735, 67.2325256137049);
    glVertex2f(273.2865252061744, 66.1761318641238);
    glVertex2f(258.4441930246037, 62.6900324905064);
    glVertex2f(250.5740595902477, 54.0276037439417);
    glVertex2f(300, 39.2133602072858);
    glEnd();

    //shadow
    rgb = HexToRGB("#ef835c");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(300, 72.6828738060462);
    glVertex2f(299.2116432933565, 73.7741922412696);
    glVertex2f(292.2544882688276, 66.8170372167206);
    glVertex2f(300, 68.2493926629513);
    glEnd();

    //shadow
    rgb = HexToRGB("#c76447");;
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(300, 68.2493926629513);
    glVertex2f(293.141184497444, 61.0876154317978);
    glVertex2f(286.4568590817202, 58.4957341481423);
    glVertex2f(300, 61.0194080295964);
    glEnd();

    //center mountain
    rgb = HexToRGB("#ea7554");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(150.448028622562,39.1316526153955);
    glVertex2f(154.7412430279955, 48.0639924387138);
    glVertex2f(165.718730242198, 47.02238608093);
    glVertex2f(161.0471338174915, 39.1462342502969);
    glEnd();

    rgb = HexToRGB("#ea7554");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(134.0609576782596, 48.211528004898);
    glVertex2f(154.7412430279955, 48.0639924387138);
    glVertex2f(150.448028622562,39.1316526153955);
    glVertex2f(138.978073073702, 39.1316526153955);
    glEnd();

    rgb = HexToRGB("#ea7554");
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(134.0609576782596, 48.211528004898);
    glVertex2f(144.3881684219334, 55.8210517107848);
    glVertex2f(154.7412430279955, 48.0639924387138);
    glEnd();

    rgb = HexToRGB("#ea7554");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(105.2286354150147, 39.1462342502969);
    glVertex2f(117.2112980438445, 46.6896232637206);
    glVertex2f(134.0609576782596, 48.211528004898);
    glVertex2f(138.978073073702, 39.1316526153955);
    glEnd();

    //shadow
    rgb = HexToRGB("#c86548");
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(138.4557429897135,39.1462342502969);
    glVertex2f(144.2973072393179, 55.8185112537901);
    glVertex2f(149.980991374068,39.1462342502969);
    glEnd();

    //shadow
    rgb = HexToRGB("#c86548");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(117.2112980438445, 46.6896232637206);
    glVertex2f(138.4557429897135,39.1462342502969);
    glVertex2f(112.5847418647414,39.1462342502969);
    glEnd();

    rgb = HexToRGB("#c86548");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(149.980991374068,39.1462342502969);
    glVertex2f(161.1331461965221, 43.0013411746172);
    glVertex2f(161.0471338174915, 39.1462342502969);
    glEnd();

}

void miniRocket(float x, float y)
{
    RGB rgb;


    // Left stand
    rgb = HexToRGB("#c1cbc2");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(x + 172.4777, y + 10.0695);
    glVertex2f(x + 171.5640, y + 15.0678);
    glVertex2f(x + 173.8750, y + 19.7437);
    glVertex2f(x + 176.5086, y + 19.6899);
    glVertex2f(x + 175.9711, y + 10.2815);
    glEnd();

    // Right stand
    rgb = HexToRGB("#c1cbc2");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(x + 180.3707, y + 19.4785);
    glVertex2f(x + 183.2395, y + 19.5348);
    glVertex2f(x + 185.3208, y + 14.8660);
    glVertex2f(x + 184.5051, y + 10.1972);
    glVertex2f(x + 180.7926, y + 10.2815);
    glEnd();

    // Middle part
    rgb = HexToRGB("#c1cbc2");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(x + 174.0532, y + 14.2941);
    glVertex2f(x + 183.1355, y + 14.4280);
    glVertex2f(x + 182.0420, y + 11.5270);
    glVertex2f(x + 175.0351, y + 11.4601);
    glEnd();

    // Body
    rgb = HexToRGB("#3ab0b9");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(x + 174.7450, y + 13.5354);
    glVertex2f(x + 173.5400, y + 16.8380);
    glVertex2f(x + 176.1285, y + 22.3722);
    glVertex2f(x + 180.9040, y + 22.4391);
    glVertex2f(x + 183.4702, y + 17.0166);
    glVertex2f(x + 182.2875, y + 13.4908);
    glEnd();

    rgb = HexToRGB("#3ab0b9");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(x + 175.1382, y + 12.5587);
    glVertex2f(x + 181.8858, y + 12.5312);
    glVertex2f(x + 181.4842, y + 11.3485);
    glVertex2f(x + 175.5930, y + 11.3485);
    glEnd();

    // Upper part
    rgb = HexToRGB("#097473");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(x + 176.1285, y + 22.3722);
    glVertex2f(x + 175.7940, y + 23.1572);
    glVertex2f(x + 181.2744, y + 23.2054);
    glVertex2f(x + 180.9040, y + 22.4391);
    glEnd();

    rgb = HexToRGB("#3ab0b9");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(x + 175.7940, y + 23.1572);
    glVertex2f(x + 176.5747, y + 24.0105);
    glVertex2f(x + 180.4709, y + 24.0105);
    glVertex2f(x + 181.2744, y + 23.1572);
    glEnd();

    rgb = HexToRGB("#3ab0b9");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(x + 176.6472, y + 23.1555);
    glVertex2f(x + 175.8498, y + 26.0039);
    glVertex2f(x + 177.2633, y + 28.6860);
    glVertex2f(x + 179.7642, y + 28.7404);
    glVertex2f(x + 181.2502, y + 26.0039);
    glVertex2f(x + 180.4709, y + 23.1555);
    glEnd();



}

void mainRocket()
{
    RGB rgb;

    glPushMatrix(); // Save the current transformation matrix
    glTranslatef(0.0f, rocketY - 55.0f, 0.0f); // Move the rocket along the Y-axis

    //top
    rgb = HexToRGB("#777e77");
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(135.8031052320075, 92.3487645107568);
    glVertex2f(144.2630937257898, 104.3442705840647);
    glVertex2f(152.2811425221358, 92.3487645107568);
    glEnd();

    //middle
    rgb = HexToRGB("#c2cbc0");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(135.8031052320075, 92.3487645107568);
    glVertex2f(152.2811425221358, 92.3487645107568);
    glVertex2f(152.2811425221358, 74.1076658805292);
    glVertex2f(135.8031052320075, 74.1076658805292);
    glEnd();

    //window
    drawCircleWithColorFromPoints(144.2809765121756, 84.5933632722262,145.5989243302151, 80.9784206855929,"#777e77");
    drawCircleWithColorFromPoints(144.2809765121756, 84.5933632722262,145.5236130263271, 82.2587128516922,"#33999e");

    //bottom
    rgb = HexToRGB("#c2cbc0");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(135.8031052320075, 74.1076658805292);
    glVertex2f(152.2811425221358, 74.1076658805292);
    glVertex2f(147.8482537347534, 58.0212410116164);
    glVertex2f(140.5188964687487, 58.0212410116164);
    glEnd();

    //stand
    rgb = HexToRGB("#777e77");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(140.5188964687487, 58.0212410116164);
    glVertex2f(147.8482537347534, 58.0212410116164);
    glVertex2f(149.1766900307746, 54.1532584508624);
    glVertex2f(148.6208870805167, 53.4423477005305);
    glVertex2f(147.392950329947, 52.886544750271);
    glVertex2f(145.7643184291913, 52.511700900096);
    glVertex2f(143.8254709282917, 52.4082957000477);
    glVertex2f(142.222690327548, 52.5504778501141);
    glVertex2f(140.7233149268522, 52.9382473502951);
    glVertex2f(139.7668168264084, 53.4294220505244);
    glVertex2f(139.3357110492813, 54.1532584508624);
    glEnd();

    //left wing
    rgb = HexToRGB("#777e77");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(126.9011770407888, 64.9485032696217);
    glVertex2f(135.9151852615734, 74.1362810259386);
    glVertex2f(139.77094652980287,60.8546106818646);
    glVertex2f(126.9011770407888, 51.4377753765275);
    glEnd();

    //right wing
    rgb = HexToRGB("#777e77");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(152.4275876959927, 74.1076658805292);
    glVertex2f(161.6031067296031, 64.6837031048236);
    glVertex2f(161.5423245706006, 51.5796471531204);
    glVertex2f(148.6725550815865, 60.8546106818646);
    glEnd();

    glPopMatrix(); // Restore the previous transformation matrix
}

void satellite()
{
    glPushMatrix();
    glTranslatef(satelliteX, 0.0f, 0.0f); // Move the car horizontally
    RGB rgb;

    rgb = HexToRGB("#656563");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(222.6213055828083, 129.2189087279487);
    glVertex2f(223.8115614478859, 130.0984081356441);
    glVertex2f(225.8695900618872, 128.2338693913298);
    glVertex2f(224.1985411872708, 126.8383969977864);
    glEnd();

    //circle
    drawCircleWithColorFromPoints(222.0837647259606, 130.9737165725237,220.4760138015321, 129.6751485181738,"#65271c");
    drawCircleWithColorFromPoints(222.0837647259606, 130.9737165725237,222.6402938921089, 129.4278022221072,"#ef841e");

    rgb = HexToRGB("#708073");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(220.723360097598, 124.2335300047076);
    glVertex2f(229.1331341638394, 131.1592262945737);
    glVertex2f(230, 126);
    glVertex2f(225.7321225929329, 122.5639425062578);
    glEnd();

    //left wing
    rgb = HexToRGB("#73c2e5");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(215.6000625706736, 113.8225628997327);
    glVertex2f(224.2568256862487, 121.1861995748285);
    glVertex2f(229.7526130583774, 114.5409664777909);
    glVertex2f(221.1676903006078, 107.2132499815981);
    glEnd();

    //left wing lines
    rgb = HexToRGB("#140503");
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(218.4808245410041, 116.0242313152582);
    glVertex2f(223.6719289298906, 109.6936162068415);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(221.6470259699173, 118.7539654991658);
    glVertex2f(226.8903255562238, 112.4031240216154);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(217.4551902043942, 111.8984213876379);
    glVertex2f(225.8108227002195, 118.7679850167763);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(219.558117845961, 109.4730448410238);
    glVertex2f(227.7875746832923, 116.3285889525516);
    glEnd();

    //left wing connect
    rgb = HexToRGB("#656563");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(225.3754276335193, 119.4512828507738);
    glVertex2f(227.3356937588205, 121.0711434812669);
    glVertex2f(230.1997951634521, 117.4323261229128);
    glVertex2f(228.3216958817264, 115.9181085770171);
    glEnd();


    //right wing
    rgb = HexToRGB("#73c2e5");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(231.3901691154409, 127.170767270499);
    glVertex2f(240.2018809127894, 134.4056464304484);
    glVertex2f(245.6434994262397, 127.7891330106656);
    glVertex2f(236.8317876288912, 120.5542538507162);
    glEnd();

    //right wing lines
    rgb = HexToRGB("#140503");
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(234.2584149748443, 129.3822849315301);
    glVertex2f(239.6501470678752, 122.8845565117046);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(237.5369040863576, 132.0287761420365);
    glVertex2f(242.7903866385415, 125.6890471974652);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(233.5671672706096, 125.3137984437366);
    glVertex2f(241.7831399837995, 132.2262754861042);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(235.5816605800937, 122.8648065772979);
    glVertex2f(243.8371331620969, 129.7772836196654);
    glEnd();

    //right wing connect
    rgb = HexToRGB("#656563");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(231.1036304427826, 124.2991266217424);
    glVertex2f(232.9230391219543, 125.754653565084);
    glVertex2f(235.8223548881182, 122.2097411708165);
    glVertex2f(234.0264224499681, 120.6955236249207);
    glEnd();

    //body
    rgb = HexToRGB("#d5e7f2");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(225.7321225929329, 122.5639425062578);
    glVertex2f(230, 126);
    glVertex2f(236.5535230458171, 117.8643628809915);
    glVertex2f(232.4723091607293, 114.3705964490501);
    glEnd();

    //lower body
    rgb = HexToRGB("#ad453a");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(232.4723091607293, 114.3705964490501);
    glVertex2f(236.5535230458171, 117.8643628809915);
    glVertex2f(237.3105289732236, 115.6098340300043);
    glVertex2f(234.5129161032732, 113.2266198297419);
    glEnd();

    glPopMatrix();


}

void brokenSatellite(float x, float y)
{

    RGB rgb;


    rgb = HexToRGB("#656563");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(x + 222.6213055828083, y + 129.2189087279487);
    glVertex2f(x + 223.8115614478859, y + 130.0984081356441);
    glVertex2f(x + 225.8695900618872, y + 128.2338693913298);
    glVertex2f(x + 224.1985411872708, y + 126.8383969977864);
    glEnd();

    // Circles
    drawCircleWithColorFromPoints(x + 222.0837647259606, y + 130.9737165725237,
                                  x + 220.4760138015321, y + 129.6751485181738, "#65271c");
    drawCircleWithColorFromPoints(x + 222.0837647259606, y + 130.9737165725237,
                                  x + 222.6402938921089, y + 129.4278022221072, "#ef841e");

    rgb = HexToRGB("#708073");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(x + 220.723360097598, y + 124.2335300047076);
    glVertex2f(x + 229.1331341638394, y + 131.1592262945737);
    glVertex2f(x + 230.0, y + 126.0); // Assuming 126 was a typo and should be 126.0
    glVertex2f(x + 225.7321225929329, y + 122.5639425062578);
    glEnd();

    /*// Left wing
    rgb = HexToRGB("#73c2e5");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(x + 215.6000625706736, y + 113.8225628997327);
    glVertex2f(x + 224.2568256862487, y + 121.1861995748285);
    glVertex2f(x + 229.7526130583774, y + 114.5409664777909);
    glVertex2f(x + 221.1676903006078, y + 107.2132499815981);
    glEnd();

    // Left wing lines
    rgb = HexToRGB("#140503");
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(x + 218.4808245410041, y + 116.0242313152582);
    glVertex2f(x + 223.6719289298906, y + 109.6936162068415);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(x + 221.6470259699173, y + 118.7539654991658);
    glVertex2f(x + 226.8903255562238, y + 112.4031240216154);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(x + 217.4551902043942, y + 111.8984213876379);
    glVertex2f(x + 225.8108227002195, y + 118.7679850167763);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(x + 219.558117845961, y + 109.4730448410238);
    glVertex2f(x + 227.7875746832923, y + 116.3285889525516);
    glEnd();*/

    // Left wing connect
    rgb = HexToRGB("#656563");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(x + 225.3754276335193, y + 119.4512828507738);
    glVertex2f(x + 227.3356937588205, y + 121.0711434812669);
    glVertex2f(x + 230.1997951634521, y + 117.4323261229128);
    glVertex2f(x + 228.3216958817264, y + 115.9181085770171);
    glEnd();

    // Right wing
    rgb = HexToRGB("#73c2e5");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(x + 231.3901691154409, y + 127.170767270499);
    glVertex2f(x + 240.2018809127894, y + 134.4056464304484);
    glVertex2f(x + 245.6434994262397, y + 127.7891330106656);
    glVertex2f(x + 236.8317876288912, y + 120.5542538507162);
    glEnd();

    /*// Right wing lines
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(x + 234.2584149748443, y + 129.3822849315301);
    glVertex2f(x + 239.6501470678752, y + 122.8845565117046);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(x + 237.5369040863576, y + 132.0287761420365);
    glVertex2f(x + 242.7903866385415, y + 125.6890471974652);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(x + 233.5671672706096, y + 125.3137984437366);
    glVertex2f(x + 241.7831399837995, y + 132.2262754861042);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(x + 235.5816605800937, y + 122.8648065772979);
    glVertex2f(x + 243.8371331620969, y + 129.7772836196654);
    glEnd();*/

    // Right wing connect
    rgb = HexToRGB("#656563");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(x + 231.1036304427826, y + 124.2991266217424);
    glVertex2f(x + 232.9230391219543, y + 125.754653565084);
    glVertex2f(x + 235.8223548881182, y + 122.2097411708165);
    glVertex2f(x + 234.0264224499681, y + 120.6955236249207);
    glEnd();

    // Body
    rgb = HexToRGB("#d5e7f2");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(x + 225.7321225929329, y + 122.5639425062578);
    glVertex2f(x + 230.0, y + 126.0);
    glVertex2f(x + 236.5535230458171, y + 117.8643628809915);
    glVertex2f(x + 232.4723091607293, y + 114.3705964490501);
    glEnd();

    // Lower body
    rgb = HexToRGB("#ad453a");
    glBegin(GL_POLYGON);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(x + 232.4723091607293, y + 114.3705964490501);
    glVertex2f(x + 236.5535230458171, y + 117.8643628809915);
    glVertex2f(x + 237.3105289732236, y + 115.6098340300043);
    glVertex2f(x + 234.5129161032732, y + 113.2266198297419);
    glEnd();

}

// for keyboard inputs
void handleKeyboard(unsigned char key, int x, int y)
{
    if (key == 'w' || key == 'W')
    {
        if (!isMovingUp && !isMovingDown)
        { // Prevent restarting mid-movement
            isMovingUp = true;
        }
    }
    if (key == 's' || key == 'S') {
        if (!isMovingUp && !isMovingDown)
        { // Prevent restarting mid-movement
            rocketY = 210.0f; // Start from off-screen
            isMovingDown = true;
        }
    }
    if (key == '0' || key == 'B')
    {
        currentScene = 0;
    }
    if (key == '1' || key == 'J' || key == 'j')
    {
        currentScene = 1;
    }
    glutPostRedisplay(); // Redraw scene
}

// for mouse clicks
void mouseClick(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON)
        {
            miniRocketUp = true;
            miniRocketDown = false;
        } else if (button == GLUT_RIGHT_BUTTON)
        {
            miniRocketDown = true;
            miniRocketUp = false;
        }
    }
}


void update(int value)
{
    // Main rocket movement
    if (isMovingUp) {
        rocketY += 1.0f;
        if (rocketY > 210.0f) {
            isMovingUp = false;
        }
    }
    if (isMovingDown) {
        rocketY -= 1.0f;
        if (rocketY <= 55.0f) {
            rocketY = 55.0f;
            isMovingDown = false;
        }
    }

    // Mini rocket movement
    if (miniRocketUp) {
        miniRocketY += 1.0f;
        if (miniRocketY > 210.0f) {
            miniRocketUp = false;
        }
    }
    if (miniRocketDown) {
        miniRocketY -= 1.0f;
        if (miniRocketY <= 0.0f) {
            miniRocketY = 0.0f;
            miniRocketDown = false;
        }
    }

    //redMoodLines animation
    redMoonLinesOffset += 0.5f; // Adjust speed as needed
    if (redMoonLinesOffset > redMoonWidth) {
        redMoonLinesOffset -= redMoonWidth;
    }

    // Sun scaling animation
    if (sunScalingUp) {
        sunScale += 0.005f; // Adjust speed by changing this value
        if (sunScale >= 1.05f) { // Scale up to 5% larger
            sunScalingUp = false;
        }
    } else {
        sunScale -= 0.005f;
        if (sunScale <= 0.5f) { // Scale down to 5% smaller
            sunScalingUp = true;
        }
    }

    //brownMoonLines animation
    brownMoonLinesOffset += 0.5f; // Adjust speed as needed
    if (brownMoonLinesOffset > brownMoonWidth) {
        brownMoonLinesOffset -= brownMoonWidth;
    }

    // Car movement
    carX += carSpeed;
    if (carX + 58.52988f > 300.0f) { // Check if car exits right
        carX = -58.52988f;           // Reset to left
    }

    // Satellite movement
    satelliteX -= 1.0f; // Adjust the speed as needed
    if (satelliteX + satelliteRightmost < 0.0f) {
        satelliteX = 300.0f - 215.6f; // Reset to the right edge
    }

    // Update planet angles to create rotation
    for (int i = 0; i < 8; ++i) {
        planetAngles[7 - i] += 0.01f * (i + 1); // Different speeds for each planet
        if (planetAngles[i] > 2 * PI) {
            planetAngles[i] -= 2 * PI;
        }
    }

    updateStars();
    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // 60 FPS update
}



void display()
{
    glPointSize(5.0);

    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer (background)

    if (currentScene == 0)
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        renderText(10.0f, 170.0f, GLUT_BITMAP_HELVETICA_18, "Hello!!!");
        renderText(10.0f, 165.0f, GLUT_BITMAP_HELVETICA_18, "Press '1' or 'J' to go to Jupiter");
        Scene0();

    }
    else if (currentScene ==1)
    {
        glClearColor(0.24313725490196078f, 0.25882352941176473f, 0.29411764705882354f, 1.0f);



        // Draw stars in the background
        drawStars();

        brownMoon();
        // Enable stencil test to clip lines to the brown moon's shape
        glEnable(GL_STENCIL_TEST);
        glStencilFunc(GL_EQUAL, 1, 0xFF);
        glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

        // Draw two instances of brownMoonLines for seamless scrolling
        glPushMatrix();
        glTranslatef(brownMoonLinesOffset - brownMoonWidth, 0.0f, 0.0f);
        brownMoonLines();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(brownMoonLinesOffset, 0.0f, 0.0f);
        brownMoonLines();
        glPopMatrix();

        glDisable(GL_STENCIL_TEST);

        surface();

        brokenSatellite(-190,-80);

        mainRocket();

        observatory();

        car();

        igloo();

        redMoon();
        // Enable stencil test to clip lines within the Red Moon's shape
        glEnable(GL_STENCIL_TEST);
        glStencilFunc(GL_EQUAL, 1, 0xFF);
        glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

        // Draw lines twice for seamless scrolling
        glPushMatrix();
        glTranslatef(redMoonLinesOffset - redMoonWidth, 0.0f, 0.0f);
        redMoonLines();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(redMoonLinesOffset, 0.0f, 0.0f);
        redMoonLines();
        glPopMatrix();

        glDisable(GL_STENCIL_TEST);


        miniRocket(0, miniRocketY);

        miniRocket(90, miniRocketY - 3);

        miniRocket(-100, miniRocketY - 4);

        sun();

        satellite();

        glColor3ub(0,0,0);
        renderText(120.0f, 25.0f, GLUT_BITMAP_HELVETICA_18, "Press '0' or 'B' to go back to the main menu");
        renderText(120.0f, 20.0f, GLUT_BITMAP_HELVETICA_18, "Press 'W' to move the rocket up");
        renderText(120.0f, 15.0f, GLUT_BITMAP_HELVETICA_18, "Press 'S' to move the rocket down");
        renderText(120.0f, 10.0f, GLUT_BITMAP_HELVETICA_18, "Left click to move the mini rocket up");
        renderText(120.0f, 5.0f, GLUT_BITMAP_HELVETICA_18, "Right click to move the mini rocket down");
    }


    glutSwapBuffers(); // Swap the front and back frame buffers (double buffering)
}