// NetWise
// Computer Ethics - CPTR123
//
// Group project:
// Each group will design a game or app that teaches or applies ethical
// principles in computing and digital life.
// 
// Your design should be to:
// Reward ethical decisions and discourage unethical ones
#include "raylib.h"
#include "raymath.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

// Screen dimensions
#define WIDTH 1920
#define HEIGHT 1080

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

enum {
    COLOUR_Dark_Navy, // Screen background
    COLOUR_Slate_Navy, // Panels and cards
    COLOUR_Deep_Slate, // Borders and dividers
    COLOUR_Cyan, // Buttons, accents, active nav item, links
    COLOUR_Purple, // Achievements and followers highlights
    COLOUR_Green, // Positive: good choices, income, supportive comments, trust
    COLOUR_Amber, // Warnings, balance and money highlights
    COLOUR_Red, // Negative: bad choices, expenses, critics and trolls
    COLOUR_Off_white, // Main text
    COLOUR_Cool_Grey // Secondary text and labels
};

enum {
    LAYOUT_Shared_shell_4_6_HUD_Followers_card,
    LAYOUT_Shared_shell_4_6_HUD_Trust_card,
    LAYOUT_Shared_shell_4_6_HUD_Balance_card,
    LAYOUT_Shared_shell_4_6_HUD_Day_card,
    LAYOUT_Shared_shell_4_6_Left_navigation_panel,
    LAYOUT_Shared_shell_4_6_Nav_item_Home,
    LAYOUT_Shared_shell_4_6_Nav_item_Feed,
    LAYOUT_Shared_shell_4_6_Nav_item_Decisions,
    LAYOUT_Shared_shell_4_6_Nav_item_Finances,
    LAYOUT_Shared_shell_4_6_Nav_item_Achievements,
    LAYOUT_Shared_shell_4_6_Main_content_area,
    LAYOUT_1_Splash_Background_artwork,
    LAYOUT_1_Splash_Title_NETWISE,
    LAYOUT_1_Splash_Tagline_A_SOCIAL_MEDIA_ETHICS_SIMULATION,
    LAYOUT_1_Splash_Slogan_Your_choices_Your_audience_Your_future,
    LAYOUT_1_Splash_Loading_label,
    LAYOUT_1_Splash_Loading_bar,
    LAYOUT_2_Intro_Phone_illustration,
    LAYOUT_2_Intro_Phone_chat_pill_Think_before_you_post,
    LAYOUT_2_Intro_Value_row_Privacy,
    LAYOUT_2_Intro_Value_row_Truth,
    LAYOUT_2_Intro_Value_row_Kindness,
    LAYOUT_2_Intro_Value_row_Respect,
    LAYOUT_2_Intro_Value_row_Responsibility,
    LAYOUT_2_Intro_Title_Welcome_to_Post_Consequence,
    LAYOUT_2_Intro_Body_paragraph_1,
    LAYOUT_2_Intro_Body_paragraph_2,
    LAYOUT_2_Intro_Continue_button,
    LAYOUT_2_Intro_Footer_Every_post_has_a_consequence,
    LAYOUT_3_Main_Menu_Background_artwork,
    LAYOUT_3_Main_Menu_Logo_icon_wordmark,
    LAYOUT_3_Main_Menu_Tagline_Every_post_has_a_consequence,
    LAYOUT_3_Main_Menu_Button_New_Game,
    LAYOUT_3_Main_Menu_Button_Continue_Game,
    LAYOUT_3_Main_Menu_Button_How_to_Play,
    LAYOUT_3_Main_Menu_Button_Ethics_Guide,
    LAYOUT_3_Main_Menu_Button_Settings,
    LAYOUT_3_Main_Menu_Button_Exit,
    LAYOUT_4_Gameplay_Event_card,
    LAYOUT_4_Gameplay_Event_icon_warning,
    LAYOUT_4_Gameplay_Event_title,
    LAYOUT_4_Gameplay_Event_description,
    LAYOUT_4_Gameplay_Prompt_WHAT_WILL_YOU_DO,
    LAYOUT_4_Gameplay_Option_A_card,
    LAYOUT_4_Gameplay_Option_B_card,
    LAYOUT_4_Gameplay_Option_C_card,
    LAYOUT_4_Gameplay_Progress_card,
    LAYOUT_4_Gameplay_Quick_Stats_card,
    LAYOUT_4_Gameplay_Quick_stat_row_Ethics,
    LAYOUT_4_Gameplay_Quick_stat_row_Trust,
    LAYOUT_4_Gameplay_Quick_stat_row_Followers,
    LAYOUT_4_Gameplay_Quick_stat_row_Money,
    LAYOUT_5_Feed_Heading_Your_Feed,
    LAYOUT_5_Feed_Tab_All,
    LAYOUT_5_Feed_Tab_Following,
    LAYOUT_5_Feed_Tab_Trending,
    LAYOUT_5_Feed_Post_card,
    LAYOUT_5_Feed_Post_header_avatar_name_time,
    LAYOUT_5_Feed_Post_image,
    LAYOUT_5_Feed_Reactions_row_likes_comments_shares,
    LAYOUT_5_Feed_Comment_row_IslandVibes,
    LAYOUT_5_Feed_Comment_row_RealTalk876,
    LAYOUT_5_Feed_Comment_row_PositiveMind,
    LAYOUT_5_Feed_Comment_row_TrollMaster,
    LAYOUT_5_Feed_Comments_Reactions_card,
    LAYOUT_5_Feed_Reaction_row_Supportive,
    LAYOUT_5_Feed_Reaction_row_Neutral,
    LAYOUT_5_Feed_Reaction_row_Critics,
    LAYOUT_5_Feed_Reaction_row_Trolls,
    LAYOUT_5_Feed_Latest_Follower_Types_card,
    LAYOUT_5_Feed_Follower_type_row_Loyal,
    LAYOUT_5_Feed_Follower_type_row_Hype,
    LAYOUT_6_Finances_Your_Finances_card,
    LAYOUT_6_Finances_Stat_tile_Income_today,
    LAYOUT_6_Finances_Stat_tile_Expenses_today,
    LAYOUT_6_Finances_Stat_tile_Balance,
    LAYOUT_6_Finances_Heading_Monthly_Expenses,
    LAYOUT_6_Finances_Expense_row_Rent,
    LAYOUT_6_Finances_Expense_row_Food,
    LAYOUT_6_Finances_Expense_row_Transport,
    LAYOUT_6_Finances_Expense_row_Entertainment,
    LAYOUT_6_Finances_Heading_Life_Events,
    LAYOUT_6_Finances_Event_card_Sponsorship_Offer,
    LAYOUT_6_Finances_Button_View_Deal,
    LAYOUT_6_Finances_Button_Ignore,
    LAYOUT_6_Finances_Event_card_Unexpected_Expense,
    LAYOUT_6_Finances_Button_Pay_Now,
    LAYOUT_7_Ethics_Report_Title_Your_Month_Online,
    LAYOUT_7_Ethics_Report_Subtitle,
    LAYOUT_7_Ethics_Report_Card_Ethics_Score,
    LAYOUT_7_Ethics_Report_Card_Audience_Trust,
    LAYOUT_7_Ethics_Report_Card_Total_Followers,
    LAYOUT_7_Ethics_Report_Card_Total_Balance,
    LAYOUT_7_Ethics_Report_Panel_Ethics_Profile,
    LAYOUT_7_Ethics_Report_Profile_row_Privacy_Consent,
    LAYOUT_7_Ethics_Report_Profile_row_Honesty_Misinformation,
    LAYOUT_7_Ethics_Report_Profile_row_Harassment_Kindness,
    LAYOUT_7_Ethics_Report_Profile_row_Copyright_Credit,
    LAYOUT_7_Ethics_Report_Profile_row_Online_Safety,
    LAYOUT_7_Ethics_Report_Footnote_5_more_categories,
    LAYOUT_7_Ethics_Report_Panel_Achievements,
    LAYOUT_7_Ethics_Report_Achievement_badge,
    LAYOUT_7_Ethics_Report_Achievement_title,
    LAYOUT_7_Ethics_Report_Achievement_description,
    LAYOUT_7_Ethics_Report_Button_View_All_Achievements,
    LAYOUT_7_Ethics_Report_Panel_Reflection,
    LAYOUT_7_Ethics_Report_Reflection_prompt_1,
    LAYOUT_7_Ethics_Report_Reflection_prompt_2,
    LAYOUT_7_Ethics_Report_Reflection_prompt_3,
    LAYOUT_7_Ethics_Report_Button_Play_Again,
    LAYOUT_8_Credits_Background_artwork,
    LAYOUT_8_Credits_Logo_icon_wordmark,
    LAYOUT_8_Credits_Heading_Game_Development_Team,
    LAYOUT_8_Credits_Credit_role_Lead_Developer,
    LAYOUT_8_Credits_Credit_name_1,
    LAYOUT_8_Credits_Credit_role_Game_Designer,
    LAYOUT_8_Credits_Credit_name_2,
    LAYOUT_8_Credits_Credit_role_UI_UX_Designer,
    LAYOUT_8_Credits_Credit_name_3,
    LAYOUT_8_Credits_Credit_role_Content_Data,
    LAYOUT_8_Credits_Credit_name_4,
    LAYOUT_8_Credits_Credit_role_Testing_Feedback,
    LAYOUT_8_Credits_Credit_name_5,
    LAYOUT_8_Credits_Special_thanks_text,
    LAYOUT_8_Credits_Slogan_Every_post_has_a_consequence,
    LAYOUT_8_Credits_Version_label,
    LAYOUT_8_Credits_Social_icons_heart_comment_send,
    LAYOUT_A1_HUD_Popularity_Option_A_Popularity_card_replaces_Trust_same_slot,
    LAYOUT_A1_HUD_Popularity_Popularity_icon_box,
    LAYOUT_A1_HUD_Popularity_Popularity_label,
    LAYOUT_A1_HUD_Popularity_Popularity_value,
    LAYOUT_A1_HUD_Popularity_Popularity_trend_arrow,
    LAYOUT_A1_HUD_Popularity_Popularity_meter_bar,
    LAYOUT_A1b_HUD_five_card_option_Option_B_five_cards_Followers,
    LAYOUT_A1b_HUD_five_card_option_Option_B_five_cards_Popularity,
    LAYOUT_A1b_HUD_five_card_option_Option_B_five_cards_Trust,
    LAYOUT_A1b_HUD_five_card_option_Option_B_five_cards_Balance,
    LAYOUT_A1b_HUD_five_card_option_Option_B_five_cards_Day,
    LAYOUT_A2_Debt_state_Balance_card_debt_state,
    LAYOUT_A2_Debt_state_Debt_badge_DEBT,
    LAYOUT_A2_Debt_state_Finances_debt_banner,
    LAYOUT_A2_Debt_state_Debt_banner_icon,
    LAYOUT_A2_Debt_state_Debt_banner_text,
    LAYOUT_A2_Debt_state_Debt_banner_button_See_options,
    LAYOUT_A3_Blowback_modal_Overlay_dims_the_game,
    LAYOUT_A3_Blowback_modal_Blowback_card,
    LAYOUT_A3_Blowback_modal_Blowback_icon,
    LAYOUT_A3_Blowback_modal_Blowback_title,
    LAYOUT_A3_Blowback_modal_Blowback_subtitle,
    LAYOUT_A3_Blowback_modal_Cause_box_It_started_with,
    LAYOUT_A3_Blowback_modal_Damage_row_1_Followers_lost,
    LAYOUT_A3_Blowback_modal_Damage_row_2_Fallout_bill,
    LAYOUT_A3_Blowback_modal_Damage_row_3_Sponsors_paused,
    LAYOUT_A3_Blowback_modal_Button_View_Details,
    LAYOUT_A3_Blowback_modal_Button_Continue,
    LAYOUT_A4_Bankruptcy_modal_Bankruptcy_card,
    LAYOUT_A4_Bankruptcy_modal_Bankruptcy_icon,
    LAYOUT_A4_Bankruptcy_modal_Bankruptcy_title,
    LAYOUT_A4_Bankruptcy_modal_Bankruptcy_subtitle,
    LAYOUT_A4_Bankruptcy_modal_Balance_display,
    LAYOUT_A4_Bankruptcy_modal_Tip_row_1,
    LAYOUT_A4_Bankruptcy_modal_Tip_row_2,
    LAYOUT_A4_Bankruptcy_modal_Tip_row_3,
    LAYOUT_A4_Bankruptcy_modal_Button_See_Life_Events,
    LAYOUT_A4_Bankruptcy_modal_Button_Keep_Going,
    LAYOUT_A5_Fan_Support_card_Event_card_Fan_Support,
    LAYOUT_A5_Fan_Support_card_Fan_Support_icon,
    LAYOUT_A5_Fan_Support_card_Fan_Support_title,
    LAYOUT_A5_Fan_Support_card_Fan_Support_amount,
    LAYOUT_A5_Fan_Support_card_Fan_Support_body,
    LAYOUT_A5_Fan_Support_card_Button_Accept
};

enum {
    SIZE_Logo_title, // Splash screen
    SIZE_Screen_title, // Intro welcome, Ethics Report title
    SIZE_Large_value, // Big numbers on the Ethics Report cards
    SIZE_H1, // HUD values, Feed heading
    SIZE_H2, // Card titles, Life Events heading
    SIZE_H3, // Option titles, menu buttons, credits heading
    SIZE_Body, // Paragraph text, event description
    SIZE_Body_small, // Sub-lines, comments, credits names
    SIZE_Label, // HUD labels, nav labels, captions
    SIZE_Caption, // Sub-lines like Loyal / Hype, footnotes
    SIZE_Minimum, // Never go smaller than this at 1080p
};

enum {
    SIZE_Side_margin,
    SIZE_Top_margin,
    SIZE_Bottom_margin,
    SIZE_Standard_gap_between_panels,
    SIZE_Panel_padding,
    SIZE_Progress_bar_height,
};

enum {
    SIZE_Card_corner_radius,
    SIZE_Button_corner_radius,
    SIZE_Card_border_width,
};

// Starting screen
static Screen screen = SCREEN_0;

// Enable debug info
static int debug = 0;

// Variables controlling the frame rate
static float elapsedTime, lagTime;
static const float FPS = 60.0f;
static const float MPF = 1.0f/FPS;

// Variable for scaling elements
static float scaleFactor = 0.0f;

int activeToggle, screenWidth, screenHeight;

int option_cards_bg_alpha_switch[3] = {
    LAYOUT_4_Gameplay_Option_A_card,
    LAYOUT_4_Gameplay_Option_B_card,
    LAYOUT_4_Gameplay_Option_C_card,
};

static Color colours[10] = {
    (Color){ 16, 24, 39, 255 },
    (Color){ 30, 41, 59, 255 },
    (Color){ 51, 65, 85, 255 },
    (Color){ 34, 211, 238, 255 },
    (Color){ 167, 139, 250, 255 },
    (Color){ 34, 197, 94, 255 },
    (Color){ 251, 191, 36, 255 },
    (Color){ 248, 113, 113, 255 },
    (Color){ 248, 250, 252, 255 },
    (Color){ 203, 213, 225, 255 },
};

static Rectangle layout[170] = {
    (Rectangle){ 48, 32, 408, 120 },
    (Rectangle){ 480, 32, 408, 120 },
    (Rectangle){ 912, 32, 408, 120 },
    (Rectangle){ 1344, 32, 528, 120 },
    (Rectangle){ 48, 176, 240, 856 },
    (Rectangle){ 64, 200, 208, 104 },
    (Rectangle){ 64, 312, 208, 104 },
    (Rectangle){ 64, 424, 208, 104 },
    (Rectangle){ 64, 536, 208, 104 },
    (Rectangle){ 64, 648, 208, 104 },
    (Rectangle){ 312, 176, 1560, 856 },
    (Rectangle){ 0, 0, 1920, 1080 },
    (Rectangle){ 960, 232, 896, 272 },
    (Rectangle){ 960, 536, 896, 40 },
    (Rectangle){ 960, 648, 896, 40 },
    (Rectangle){ 1376, 960, 480, 32 },
    (Rectangle){ 1376, 1008, 480, 12 },
    (Rectangle){ 96, 64, 640, 952 },
    (Rectangle){ 160, 216, 464, 64 },
    (Rectangle){ 176, 352, 480, 72 },
    (Rectangle){ 176, 448, 480, 72 },
    (Rectangle){ 176, 544, 480, 72 },
    (Rectangle){ 176, 640, 480, 72 },
    (Rectangle){ 176, 736, 480, 72 },
    (Rectangle){ 912, 176, 912, 144 },
    (Rectangle){ 912, 352, 864, 152 },
    (Rectangle){ 912, 536, 864, 80 },
    (Rectangle){ 912, 768, 704, 96 },
    (Rectangle){ 912, 960, 704, 32 },
    (Rectangle){ 0, 0, 1920, 1080 },
    (Rectangle){ 104, 48, 768, 176 },
    (Rectangle){ 232, 232, 592, 32 },
    (Rectangle){ 104, 352, 720, 88 },
    (Rectangle){ 104, 464, 720, 88 },
    (Rectangle){ 104, 576, 720, 88 },
    (Rectangle){ 104, 688, 720, 88 },
    (Rectangle){ 104, 800, 720, 88 },
    (Rectangle){ 104, 912, 720, 88 },
    (Rectangle){ 312, 176, 1104, 856 },
    (Rectangle){ 344, 208, 64, 64 },
    (Rectangle){ 424, 208, 960, 48 },
    (Rectangle){ 424, 264, 960, 112 },
    (Rectangle){ 344, 392, 400, 28 },
    (Rectangle){ 344, 440, 1040, 168 },
    (Rectangle){ 344, 628, 1040, 168 },
    (Rectangle){ 344, 816, 1040, 168 },
    (Rectangle){ 1448, 176, 424, 152 },
    (Rectangle){ 1448, 344, 424, 368 },
    (Rectangle){ 1472, 416, 376, 64 },
    (Rectangle){ 1472, 488, 376, 64 },
    (Rectangle){ 1472, 560, 376, 64 },
    (Rectangle){ 1472, 632, 376, 64 },
    (Rectangle){ 312, 176, 960, 48 },
    (Rectangle){ 312, 240, 120, 48 },
    (Rectangle){ 448, 240, 176, 48 },
    (Rectangle){ 640, 240, 160, 48 },
    (Rectangle){ 312, 304, 960, 728 },
    (Rectangle){ 344, 328, 896, 72 },
    (Rectangle){ 344, 416, 896, 256 },
    (Rectangle){ 344, 688, 896, 56 },
    (Rectangle){ 344, 760, 896, 56 },
    (Rectangle){ 344, 820, 896, 56 },
    (Rectangle){ 344, 880, 896, 56 },
    (Rectangle){ 344, 940, 896, 56 },
    (Rectangle){ 1304, 176, 568, 440 },
    (Rectangle){ 1328, 248, 520, 80 },
    (Rectangle){ 1328, 336, 520, 80 },
    (Rectangle){ 1328, 424, 520, 80 },
    (Rectangle){ 1328, 512, 520, 80 },
    (Rectangle){ 1304, 632, 568, 224 },
    (Rectangle){ 1328, 696, 520, 72 },
    (Rectangle){ 1328, 776, 520, 72 },
    (Rectangle){ 312, 176, 864, 688 },
    (Rectangle){ 344, 240, 256, 120 },
    (Rectangle){ 616, 240, 256, 120 },
    (Rectangle){ 888, 240, 256, 120 },
    (Rectangle){ 344, 392, 400, 32 },
    (Rectangle){ 344, 440, 800, 80 },
    (Rectangle){ 344, 536, 800, 80 },
    (Rectangle){ 344, 632, 800, 80 },
    (Rectangle){ 344, 728, 800, 80 },
    (Rectangle){ 1208, 176, 664, 48 },
    (Rectangle){ 1208, 240, 664, 248 },
    (Rectangle){ 1240, 408, 168, 48 },
    (Rectangle){ 1424, 408, 144, 48 },
    (Rectangle){ 1208, 504, 664, 216 },
    (Rectangle){ 1240, 640, 168, 48 },
    (Rectangle){ 48, 48, 1824, 64 },
    (Rectangle){ 48, 120, 1824, 32 },
    (Rectangle){ 48, 184, 438, 176 },
    (Rectangle){ 510, 184, 438, 176 },
    (Rectangle){ 972, 184, 438, 176 },
    (Rectangle){ 1434, 184, 438, 176 },
    (Rectangle){ 48, 392, 704, 640 },
    (Rectangle){ 80, 464, 640, 72 },
    (Rectangle){ 80, 552, 640, 72 },
    (Rectangle){ 80, 640, 640, 72 },
    (Rectangle){ 80, 728, 640, 72 },
    (Rectangle){ 80, 816, 640, 72 },
    (Rectangle){ 80, 960, 640, 28 },
    (Rectangle){ 776, 392, 560, 640 },
    (Rectangle){ 800, 472, 112, 112 },
    (Rectangle){ 936, 480, 376, 40 },
    (Rectangle){ 800, 608, 512, 120 },
    (Rectangle){ 800, 952, 512, 64 },
    (Rectangle){ 1360, 392, 512, 640 },
    (Rectangle){ 1392, 464, 448, 120 },
    (Rectangle){ 1392, 600, 448, 120 },
    (Rectangle){ 1392, 736, 448, 120 },
    (Rectangle){ 1392, 952, 448, 64 },
    (Rectangle){ 0, 0, 1920, 1080 },
    (Rectangle){ 344, 64, 560, 144 },
    (Rectangle){ 96, 264, 1056, 40 },
    (Rectangle){ 288, 336, 336, 48 },
    (Rectangle){ 648, 336, 480, 48 },
    (Rectangle){ 288, 400, 336, 48 },
    (Rectangle){ 648, 400, 480, 48 },
    (Rectangle){ 288, 464, 336, 48 },
    (Rectangle){ 648, 464, 480, 48 },
    (Rectangle){ 288, 528, 336, 48 },
    (Rectangle){ 648, 528, 480, 48 },
    (Rectangle){ 288, 592, 336, 48 },
    (Rectangle){ 648, 592, 480, 48 },
    (Rectangle){ 96, 704, 1056, 64 },
    (Rectangle){ 96, 800, 1056, 40 },
    (Rectangle){ 64, 1000, 240, 24 },
    (Rectangle){ 1704, 976, 168, 48 },
    (Rectangle){ 480, 32, 408, 120 },
    (Rectangle){ 504, 56, 72, 72 },
    (Rectangle){ 600, 48, 264, 28 },
    (Rectangle){ 600, 76, 160, 48 },
    (Rectangle){ 776, 84, 88, 32 },
    (Rectangle){ 600, 128, 264, 12 },
    (Rectangle){ 48, 32, 344, 120 },
    (Rectangle){ 416, 32, 344, 120 },
    (Rectangle){ 784, 32, 344, 120 },
    (Rectangle){ 1152, 32, 344, 120 },
    (Rectangle){ 1520, 32, 352, 120 },
    (Rectangle){ 912, 32, 408, 120 },
    (Rectangle){ 1208, 44, 96, 32 },
    (Rectangle){ 312, 176, 1560, 80 },
    (Rectangle){ 344, 192, 48, 48 },
    (Rectangle){ 408, 192, 1248, 48 },
    (Rectangle){ 1672, 192, 168, 48 },
    (Rectangle){ 0, 0, 1920, 1080 },
    (Rectangle){ 480, 220, 960, 640 },
    (Rectangle){ 528, 252, 80, 80 },
    (Rectangle){ 640, 252, 720, 64 },
    (Rectangle){ 640, 324, 720, 36 },
    (Rectangle){ 528, 388, 864, 72 },
    (Rectangle){ 528, 476, 864, 56 },
    (Rectangle){ 528, 540, 864, 56 },
    (Rectangle){ 528, 604, 864, 56 },
    (Rectangle){ 736, 764, 320, 64 },
    (Rectangle){ 1072, 764, 320, 64 },
    (Rectangle){ 480, 220, 960, 640 },
    (Rectangle){ 528, 252, 80, 80 },
    (Rectangle){ 640, 252, 720, 64 },
    (Rectangle){ 640, 324, 720, 36 },
    (Rectangle){ 528, 388, 864, 120 },
    (Rectangle){ 528, 528, 864, 56 },
    (Rectangle){ 528, 592, 864, 56 },
    (Rectangle){ 528, 656, 864, 56 },
    (Rectangle){ 736, 764, 320, 64 },
    (Rectangle){ 1072, 764, 320, 64 },
    (Rectangle){ 1208, 736, 664, 240 },
    (Rectangle){ 1240, 768, 56, 56 },
    (Rectangle){ 1312, 768, 328, 40 },
    (Rectangle){ 1664, 768, 176, 40 },
    (Rectangle){ 1240, 824, 600, 72 },
    (Rectangle){ 1240, 904, 168, 48 },
};

static int sizes_font[11] = {
    128, //	Splash screen
    56, //	Intro welcome, Ethics Report title
    56, //	Big numbers on the Ethics Report cards
    40, //	HUD values, Feed heading
    32, //	Card titles, Life Events heading
    28, //	Option titles, menu buttons, credits heading
    24, //	Paragraph text, event description
    22, //	Sub-lines, comments, credits names
    20, //	HUD labels, nav labels, captions
    18, //	Sub-lines like Loyal / Hype, footnotes
    16, //	Never go smaller than this at 1080p
};

static float sizes_element[9] = {
    48,	// Left and right
    32,	// Above the HUD
    48,	// Below the content
    24,	// Use 16 for tight groups, 32 for major sections
    32,	// Inside cards
    16,	// Bar radius = half the height
};

static float sizes_border_radius[3] = {
    0.05f,	// Big Panels and cards
    0.20f,	// Buttons and option cards
    0.2f	// Accent border; use 1 for subtle dividers
};

static int buttons[170] = { 0 };

// Main game functions
static void Init(void);
static void InitScreen(Screen s);
static void Update(float t);
static void Draw(void);
static void UpdateDraw(void);

// Helper functions
static float Min(float a, float b);
static float ScaleFactor(int w, int h);
static Rectangle ScaleRect(Rectangle rect);
static void DrawActiveCard(int activeCard);

// Cards
void DrawCardHome();
void DrawCardFeed();
void DrawCardFinances();
void DrawCardAchievements();

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
    SetWindowState(FLAG_FULLSCREEN_MODE);
    SetTargetFPS(60);
    Init();
    
    while(!WindowShouldClose()) {
        UpdateDraw();
    }
    
    CloseWindow();
    return 0;
}

void Init(void) {
    lagTime = 0;
    
    InitScreen(SCREEN_0);
}

void InitScreen(Screen s) {
    screen = s;
    
    switch(screen) {
        case SCREEN_0:
            InitScreen0();
            break;
        case SCREEN_1:
            InitScreen1();
            break;
        case SCREEN_2:
            InitScreen2();
            break;
        case SCREEN_3:
            InitScreen3();
            break;
        case SCREEN_4:
            InitScreen4();
            break;
        case SCREEN_5:
            InitScreen5();
            break;
        case SCREEN_6:
            InitScreen6();
            break;
        case SCREEN_7:
            InitScreen7();
            break;
    }
}

void Update(float t) {
    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();
    scaleFactor = ScaleFactor(screenWidth, screenHeight);
    
    switch(screen) {
        case SCREEN_0:
            UpdateScreen0(t);
            break;
        case SCREEN_1:
            UpdateScreen1(t);
            break;
        case SCREEN_2:
            UpdateScreen2(t);
            break;
        case SCREEN_3:
            UpdateScreen3(t);
            break;
        case SCREEN_4:
            UpdateScreen4(t);
            break;
        case SCREEN_5:
            UpdateScreen5(t);
            break;
        case SCREEN_6:
            UpdateScreen6(t);
            break;
        case SCREEN_7:
            UpdateScreen7(t);
            break;
    }
}
void Draw(void) {
    BeginDrawing();
        ClearBackground(colours[COLOUR_Dark_Navy]);

        switch(screen) {
            case SCREEN_0:
                DrawScreen0();
                break;
            case SCREEN_1:
                DrawScreen1();
                break;
            case SCREEN_2:
                DrawScreen2();
                break;
            case SCREEN_3:
                DrawScreen3();
                break;
            case SCREEN_4:
                DrawScreen4();
                break;
            case SCREEN_5:
                DrawScreen5();
                break;
            case SCREEN_6:
                DrawScreen6();
                break;
            case SCREEN_7:
                DrawScreen7();
                break;
        }
    EndDrawing();
}
void UpdateDraw(void) {
    elapsedTime = GetFrameTime();
    lagTime += elapsedTime;
    
    while(lagTime >= MPF) {
        lagTime -= MPF;
        Update(elapsedTime);
    }
    
    Draw();
}

// Helper functions
float Min(float a, float b) {
    return a < b ? a : b;
}

float ScaleFactor(int w, int h) {
    float sx, sy;
    sx = (float)w / (float)WIDTH;
    sy = (float)h / (float)HEIGHT;
    return Min(sx, sy);
}

Rectangle ScaleRect(Rectangle rect) {
    return (Rectangle){rect.x * scaleFactor, rect.y * scaleFactor, rect.width * scaleFactor, rect.height * scaleFactor};
}

void DrawActiveCard(int activeCard) {
    // Depending on which tab is active, draw the card for that tab;
    switch(activeCard) {
        case 0: // home tab
            DrawCardHome();
            break;
        case 1: // feed tab
            DrawCardFeed();
            break;
        case 2:
            DrawCardFinances();
            break;
        case 3:
            break;
        case 4:
            break;
    }
}

// Cards
void DrawCardHome() {
    DrawRectangleRounded(
                layout[LAYOUT_4_Gameplay_Event_card],
                sizes_border_radius[SIZE_Card_corner_radius],
                8,
                colours[COLOUR_Slate_Navy]
            );
            DrawRectangleRounded(
                layout[LAYOUT_4_Gameplay_Progress_card],
                sizes_border_radius[SIZE_Button_corner_radius],
                8,
                colours[COLOUR_Slate_Navy]
            );
            DrawRectangleRounded(
                layout[LAYOUT_4_Gameplay_Quick_Stats_card],
                sizes_border_radius[SIZE_Button_corner_radius],
                8,
                colours[COLOUR_Slate_Navy]
            );
            
            DrawRectangleRounded(
                layout[LAYOUT_4_Gameplay_Option_A_card],
                sizes_border_radius[SIZE_Button_corner_radius],
                8,
                (Color){ 248, 113, 113, option_cards_bg_alpha_switch[0] }
            );
            DrawRectangleRoundedLines(
                layout[LAYOUT_4_Gameplay_Option_A_card],
                sizes_border_radius[SIZE_Button_corner_radius],
                8,
                colours[COLOUR_Red]
            );
            DrawRectangleRounded(
                layout[LAYOUT_4_Gameplay_Option_B_card],
                sizes_border_radius[SIZE_Button_corner_radius],
                8,
                (Color){ 34, 197, 94, option_cards_bg_alpha_switch[1] }
            );
            DrawRectangleRoundedLines(
                layout[LAYOUT_4_Gameplay_Option_B_card],
                sizes_border_radius[SIZE_Button_corner_radius],
                8,
                colours[COLOUR_Green]
            );
            DrawRectangleRounded(
                layout[LAYOUT_4_Gameplay_Option_C_card],
                sizes_border_radius[SIZE_Button_corner_radius],
                8,
                (Color){ 34, 211, 238, option_cards_bg_alpha_switch[2] }
            );
            DrawRectangleRoundedLines(
                layout[LAYOUT_4_Gameplay_Option_C_card],
                sizes_border_radius[SIZE_Button_corner_radius],
                8,
                colours[COLOUR_Cyan]
            );
}

void DrawCardFeed() {
    DrawRectangleRounded(
                layout[LAYOUT_5_Feed_Post_card],
                sizes_border_radius[SIZE_Card_corner_radius],
                8,
                colours[COLOUR_Slate_Navy]
            );
            DrawRectangleRounded(
                layout[LAYOUT_5_Feed_Comments_Reactions_card],
                sizes_border_radius[SIZE_Button_corner_radius],
                8,
                colours[COLOUR_Slate_Navy]
            );
            DrawRectangleRounded(
                layout[LAYOUT_5_Feed_Latest_Follower_Types_card],
                sizes_border_radius[SIZE_Button_corner_radius],
                8,
                colours[COLOUR_Slate_Navy]
            );
}

void DrawCardFinances() {
    DrawRectangleRounded(
                layout[LAYOUT_6_Finances_Your_Finances_card],
                sizes_border_radius[SIZE_Card_corner_radius],
                8,
                colours[COLOUR_Slate_Navy]
            );
}

void DrawCardAchievements() {}

// Screen 0
void InitScreen0(void) {
    InitScreen(SCREEN_1);
}

void UpdateScreen0(float t) {
    
}

void DrawScreen0(void) {}

// Screen 1
void InitScreen1(void) {}


void UpdateScreen1(float t) {
    if(buttons[LAYOUT_2_Intro_Continue_button]) {
        InitScreen(SCREEN_2);
    }
}

void DrawScreen1(void) {
    DrawText("Welcome To:\nNETWISE", 
        layout[LAYOUT_1_Splash_Title_NETWISE].x * scaleFactor,
        layout[LAYOUT_1_Splash_Title_NETWISE].y * scaleFactor,
        sizes_font[SIZE_Large_value] * scaleFactor,
        colours[COLOUR_Off_white]
    );
    DrawText(
        "In this game, you'll step into the life of a\n"
        "content creator. Every Post, comment and\n"
        "choice you make affects your followers, trust, finances and future.", 
        layout[LAYOUT_2_Intro_Body_paragraph_1].x * scaleFactor,
        layout[LAYOUT_2_Intro_Body_paragraph_1].y * scaleFactor,
        sizes_font[SIZE_Body] * scaleFactor,
        colours[COLOUR_Off_white]
    );
    DrawText(
        "It's not just about being popular...\n"
        "It's about doing what's right.\n", 
        layout[LAYOUT_2_Intro_Body_paragraph_2].x * scaleFactor,
        layout[LAYOUT_2_Intro_Body_paragraph_2].y * scaleFactor,
        sizes_font[SIZE_Body] * scaleFactor,
        colours[COLOUR_Off_white]
    );
    buttons[LAYOUT_2_Intro_Continue_button] = GuiButton(ScaleRect(layout[LAYOUT_2_Intro_Continue_button]), "Continue ->");
    DrawText(
        "Every post has a consequence.",
        layout[LAYOUT_2_Intro_Footer_Every_post_has_a_consequence].x * scaleFactor,
        layout[LAYOUT_2_Intro_Footer_Every_post_has_a_consequence].y * scaleFactor,
        sizes_font[SIZE_Body_small] * scaleFactor,
        colours[COLOUR_Off_white]
    );
}

// Screen 2
void InitScreen2(void) {}

void UpdateScreen2(float t) {
    if(buttons[LAYOUT_3_Main_Menu_Button_New_Game]) {
        InitScreen(SCREEN_3);
    }
}

void DrawScreen2(void) {
    DrawText(
        "Every Post has a consequence", 
        layout[LAYOUT_3_Main_Menu_Tagline_Every_post_has_a_consequence].x * scaleFactor,
        layout[LAYOUT_3_Main_Menu_Tagline_Every_post_has_a_consequence].y * scaleFactor,
        sizes_font[SIZE_H1] * scaleFactor,
        colours[COLOUR_Off_white]
    );
    buttons[LAYOUT_3_Main_Menu_Button_New_Game] = GuiButton(layout[LAYOUT_3_Main_Menu_Button_New_Game], "New");
    buttons[LAYOUT_3_Main_Menu_Button_Continue_Game] = GuiButton(layout[LAYOUT_3_Main_Menu_Button_Continue_Game], "Continue");
    buttons[LAYOUT_3_Main_Menu_Button_How_to_Play] = GuiButton(layout[LAYOUT_3_Main_Menu_Button_How_to_Play], "How to Play");
    buttons[LAYOUT_3_Main_Menu_Button_Ethics_Guide] = GuiButton(layout[LAYOUT_3_Main_Menu_Button_Ethics_Guide], "Ethics Guide");
    buttons[LAYOUT_3_Main_Menu_Button_Settings] = GuiButton(layout[LAYOUT_3_Main_Menu_Button_Settings], "Settings");
    buttons[LAYOUT_3_Main_Menu_Button_Exit] = GuiButton(layout[LAYOUT_3_Main_Menu_Button_Exit], "Exit");
}

// Screen 3
void InitScreen3(void) {}

void UpdateScreen3(float t) {
    // Set initial values for option card backgrounds
    int i;
    for(i = 0; i < 3; ++i) {
        option_cards_bg_alpha_switch[i] = 10;
    }
    // Check if mouse is hovering and do stuff (like increase bg color)
    Vector2 mouse_pos = GetMousePosition();
    if(CheckCollisionPointRec(
        mouse_pos, 
        layout[LAYOUT_4_Gameplay_Option_A_card]
    )) {
        option_cards_bg_alpha_switch[0] = 20;
    }
    if(CheckCollisionPointRec(
        mouse_pos, 
        layout[LAYOUT_4_Gameplay_Option_B_card]
    )) {
        option_cards_bg_alpha_switch[1] = 20;
    }
    if(CheckCollisionPointRec(
        mouse_pos, 
        layout[LAYOUT_4_Gameplay_Option_C_card]
    )) {
        option_cards_bg_alpha_switch[2] = 20;
    }
}


void DrawScreen3(void) {
    DrawRectangleRounded(
        layout[LAYOUT_Shared_shell_4_6_HUD_Followers_card],
        sizes_border_radius[SIZE_Button_corner_radius],
        8,
        colours[COLOUR_Slate_Navy]
    );
    DrawRectangleRounded(
        layout[LAYOUT_Shared_shell_4_6_HUD_Trust_card],
        sizes_border_radius[SIZE_Button_corner_radius],
        8,
        colours[COLOUR_Slate_Navy]
    );
    DrawRectangleRounded(
        layout[LAYOUT_Shared_shell_4_6_HUD_Balance_card],
        sizes_border_radius[SIZE_Button_corner_radius],
        8,
        colours[COLOUR_Slate_Navy]
    );
    DrawRectangleRounded(
        layout[LAYOUT_Shared_shell_4_6_HUD_Day_card],
        sizes_border_radius[SIZE_Button_corner_radius],
        8,
        colours[COLOUR_Slate_Navy]
    );
    
    GuiSetStyle(TOGGLE, GROUP_PADDING, 8);
    GuiToggleGroup(layout[LAYOUT_Shared_shell_4_6_Nav_item_Home], "Home\nFeed\nFinances\nAchievements", &activeToggle);
    
    DrawActiveCard(activeToggle);
}

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