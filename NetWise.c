// NetWise
// Computer Ethics - CPTR123
//
// Group project:
// Each group will design a game or app that teaches or applies ethical
// principles in computing and digital life.
// 
// Your design should be to:
// Reward ethical decisions and discourage unethical ones

#include <stdint.h>
#include <stdio.h>

#include "raylib.h"
#include "raymath.h"

// Screen dimensions
#define WIDTH 1920
#define HEIGHT 1080

// Element sizes
//      UI component	            Reference value	    Scaled value
#define MAIN_SCREEN_MARGIN	        40  	            // 40 * S
#define HEADER_HEIGHT	            80  	            // 80 * S
#define SIDEBAR_WIDTH	            240 	            // 240 * S
#define MAIN_CONTENT_PADDING	    32  	            // 32 * S
#define GAP_BETWEEN_CARDS	        20	                // 20 * S
#define CARD_PADDING	            24	                // 24 * S
#define CARD_CORNER_RADIUS	        14	                // 14 * S
#define PRIMARY_BUTTON_WIDTH	    280	                // 280 * S
#define PRIMARY_BUTTON_HEIGHT	    60	                // 60 * S
#define STANDARD_CARD_WIDTH	        420	                // 420 * S
#define STANDARD_CARD_HEIGHT	    260	                // 260 * S
#define DECISION_CARD_WIDTH	        800	                // 800 * S
#define DECISION_CARD_HEIGHT	    125	                // 125 * S
#define NAVIGATION_ICON	            26	                // 26 * S
#define MAIN_HEADING	            38	                // 38 * S
#define BODY_TEXT	                22	                // 22 * S
#define BUTTON_TEXT	                20	                // 20 * S
#define SECONDARY_TEXT	            16	                // 16 * S

// Icon type	                    Native size	        Typical use
#define SMALL_UI_ICONS	            16 // × 16 px	    Inline indicators
#define STANDARD_UI_ICONS	        24 // × 24 px	    Buttons and navigation
#define GAMEPLAY_ICONS	            32 // × 32 px	    Ethics decisions, social actions
#define LARGE_ICONS	                48 // × 48 px	    Cards and dashboard panels
#define ACHIEVMENT_ICONS	        64 // × 64 px	    Rewards and milestones

// Colors
// Backgrounds                                                  UI element	            Colour
#define COLOR_BACKGROUND        ((Color){16, 24, 39, 255})      // Main background	    Dark Navy
#define COLOR_PANEL             ((Color){30, 41, 59, 255})      // Panels and cards	    Slate Navy
#define COLOR_BORDER            ((Color){51, 65, 85, 255})      // Borders and dividers	Deep Slate

// Accents
#define COLOR_CYAN              ((Color){34, 211, 238, 255})    // Primary accent	    Electric Cyan
#define COLOR_PURPLE            ((Color){167, 139, 250, 255})   // Secondary accent	    Purple

// Feedback
#define COLOR_SUCCESS           ((Color){34, 197, 94, 255})     // Positive feedback	Green
#define COLOR_WARNING           ((Color){251, 191, 36, 255})    // Warning	            Amber
#define COLOR_DANGER            ((Color){248, 113, 113, 255})   // Negative feedback	Red

// Text
#define COLOR_TEXT              ((Color){248, 250, 252, 255})   // Main text	        Off-White
#define COLOR_TEXT_SECONDARY    ((Color){203, 213, 225, 255})   // Secondary text	    Cool Grey
#define COLOR_TEXT_MUTED        ((Color){148, 163, 184, 255})   // Muted text	        Blue Grey

// Additional UI states
#define COLOR_OVERLAY           ((Color){0, 0, 0, 150})         // Transparent overlay	Black
#define COLOR_DISABLED          ((Color){71, 85, 105, 255})     // Disabled element     Muted Slate


// Enum for controlling the screen that is shown
typedef enum Screen {
    SCREEN_0,
    SCREEN_1,
    SCREEN_2,
    SCREEN_3,
    
    SCREEN_4,
    SCREEN_5,
    SCREEN_6,
    SCREEN_7
} Screen;

// Starting screen
static Screen screen = SCREEN_0;

// Enable debug info
static int debug = 0;

// Variables controlling the frame rate
static float prevTime, currTime, elapsedTime, lagTime;
static const float FPS = 60;
static const float FRAME_TIME = 1/FPS;
static const float MPF = FRAME_TIME * 1000;

// Main game functions
static void Init(void);
static void InitScreen(Screen s);
static void Update(float t);
static void Draw(void);
static void UpdateDraw(void);

// Helper functions
static int Min(int a, int b);
static float ScaleFactor(float w, float h);

// Screen 0
void InitScreen0(void);
void UpdateScreen0(float t);
void DrawScreen0(void);

// Screen 1
void InitScreen1(void);
void UpdateScreen1(float t);
void DrawScreen1(void);

// Screen 2
void InitScreen2(void);
void UpdateScreen2(float t);
void DrawScreen2(void);

// Screen 3
void InitScreen3(void);
void UpdateScreen3(float t);
void DrawScreen3(void);

// Screen 4
void InitScreen4(void);
void UpdateScreen4(float t);
void DrawScreen4(void);

// Screen 5
void InitScreen5(void);
void UpdateScreen5(float t);
void DrawScreen5(void);

// Screen 6
void InitScreen6(void);
void UpdateScreen6(float t);
void DrawScreen6(void);

// Screen 7
void InitScreen7(void);
void UpdateScreen7(float t);
void DrawScreen7(void);

int main(void) {
    
    InitWindow(WIDTH, HEIGHT, "NetWise");
    SetTargetFPS(60);
    SetWindowState(FLAG_FULLSCREEN_MODE);
    Init();
    
    while(!WindowShouldClose()) {
        UpdateDraw();
    }
    
    CloseWindow();
    return 0;
}

void Init(void) {
    prevTime = GetFrameTime();
    lagTime = 0;
    
    InitScreen(SCREEN_0);
}

void InitScreen(Screen s) {
    screen = s;
    
    switch(screen) {
        case SCREEN_0:
            InitScreen0();
            break;
    }
}

void Update(float t) {
    switch(screen) {
        case SCREEN_0:
            UpdateScreen0(t);
            break;
    }
}
void Draw(void) {
    BeginDrawing();
        ClearBackground(COLOR_BACKGROUND);
        
        switch(screen) {
        case SCREEN_0:
            DrawScreen0();
            break;
        }
    EndDrawing();
}
void UpdateDraw(void) {
    currTime = GetFrameTime();
    elapsedTime = currTime - prevTime;
    prevTime = currTime;
    lagTime += elapsedTime;
    
    while(lagTime >= MPF) {
        lagTime -= MPF;
        Update(elapsedTime);
    }
    
    Draw();
}

// Helper functions
int Min(int a, int b) {
    return a < b ? a : b;
}

float ScaleFactor(float w, float h) {
    float sx, sy;
    sx = w / WIDTH;
    sy = h / HEIGHT;
    return Min(sx, sy);
}

// Screen 0
void InitScreen0(void) {}

void UpdateScreen0(float t) {}

void DrawScreen0(void) {}

// Screen 1
void InitScreen1(void) {}

void UpdateScreen1(float t) {}

void DrawScreen1(void) {}

// Screen 2
void InitScreen2(void) {}

void UpdateScreen2(float t) {}

void DrawScreen2(void) {}

// Screen 3
void InitScreen3(void) {}

void UpdateScreen3(float t) {}

void DrawScreen3(void) {}

// Screen 4
void InitScreen4(void) {}

void UpdateScreen4(float t) {}

void DrawScreen4(void) {}

// Screen 5
void InitScreen5(void) {}

void UpdateScreen5(float t) {}

void DrawScreen5(void) {}

// Screen 6
void InitScreen6(void) {}

void UpdateScreen6(float t) {}

void DrawScreen6(void) {}

// Screen 7
void InitScreen7(void) {}

void UpdateScreen7(float t) {}

void DrawScreen7(void) {}