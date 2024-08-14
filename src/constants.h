#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define FALSE                  0
#define TRUE                   1
#define RELEASED               2

#define WINDOW_WIDTH           1920
#define WINDOW_HEIGHT          1080

#define FPS                    30
#define FRAME_TARGET_TIME      (1000 / FPS)

#define CAM_RATIO              16/9
#define DEF_TILES_PER_WIDTH    48  // in tile
#define MIN_TILES_PER_WIDTH    16  // in tile
#define MAX_TILES_PER_WIDTH    192 // in tile

// GENERAL
#define LOADSCREEN_CHANGE_BG   5  // in seconds
#define BACKGROUND_IMAGE_COUNT 12
#define KILL_ENEMIES_NEXT_DAY  0
#define DAY_IN_SECONDS         30
#define NIGHT_IN_SECONDS       6
#define MAX_BUILDINGS          200
#define MAX_TREES              200
#define NIGHT_DARKNESS         150 // 255 -> completly dark
#define FADE_OUT_SPEED         3
#define FADE_IN_SPEED          3

// MAP
#define MAP_WIDTH              192 // in tile
#define MAP_HEIGHT             108 // in tile

#define HOR_MARGIN             .1f // in percent 1 = 100%
#define VER_MARGIN             .1f // in percent 1 = 100%

// EMPIRE
#define START_MONEY            2000 // in coin

// BUILDING
#define ARCHER_TOWER_WIDTH     5   // in tile
#define ARCHER_TOWER_HEIGHT    5   // in tile
#define ARCHER_TOWER_HEALTH    300 // in hp
#define ARCHER_TOWER_DEMAGE    30  // in hp
#define ARCHER_TOWER_RANGE     26  // in tile
#define ARCHER_TOWER_COOLDOWN  .5  // in seconds
#define ARCHER_TOWER_COST      500 // in coin
#define ARCHER_TOWER_SELL_PER  .6  // in percent 1 = 100%

#define WIZARD_TOWER_WIDTH     5   // in tile
#define WIZARD_TOWER_HEIGHT    5   // in tile
#define WIZARD_TOWER_HEALTH    500 // in hp
#define WIZARD_TOWER_DEMAGE    25  // in hp
#define WIZARD_TOWER_DEM_AREA  1   // in tile
#define WIZARD_TOWER_RANGE     15  // in tile
#define WIZARD_TOWER_COOLDOWN  .9  // in seconds
#define WIZARD_TOWER_COST      800 // in coin
#define WIZARD_TOWER_SELL_PER  .6  // in percent 1 = 100%

#define WOODMAN_TOWER_WIDTH    3   // in tile
#define WOODMAN_TOWER_HEIGHT   3   // in tile
#define WOODMAN_TOWER_HEALTH   200 // in hp
#define WOODMAN_TOWER_COST     600 // in coin
#define WOODMAN_TOWER_SELL_PER .4  // in percent 1 = 100%

#define WOODMAN_MAX_SPEED      10  // in tile
#define WOODMAN_POWER          20  // in hp per second
#define WOODMAN_MAX_LOAD       130 // in hp
#define WOOD_PRICE             3   // in *coin

// TREE
#define TREE_WIDTH             2   // in tile
#define TREE_HEIGHT            2   // in tile
#define TREE_HEALTH            300 // in hp

// ARROW
#define ARROW_MAX_SPEED        30  // in tile per second

// MAGIC
#define MAGIC_MAX_SPEED        15  // in tile per second

// ENEMY
#define ENEMIES_AFTER_DAY(x)   (((x) + 1) * ((x) + 1) + 14)
#define ENEMY_DEMAGE           10  // hp per second
#define ENEMY_HEALTH           80  // hp
#define ENEMY_MAX_SPEED        5   // tile

// USER INTERFACE
#define PANEL_WIDTH            .1  // in percent 1 = 100% of WINDOW_WIDTH

#define SLOT_SIZE_PER          .4  // in percent 1 = 100% of PANEL_WIDTH
#define SLOT_LEFT_MARGIN_PER   .25 // in percent 1 = 100% of PANEL_WIDTH
#define SLOT_TOP_MARGIN_PER    .2  // in percent 1 = 100% of PANEL_WIDTH
#define SLOT_LEFT_MARGIN       WINDOW_WIDTH * PANEL_WIDTH * SLOT_LEFT_MARGIN_PER
#define SLOT_TOP_MARGIN        WINDOW_WIDTH * PANEL_WIDTH * SLOT_TOP_MARGIN_PER
#define SLOT_SIZE              WINDOW_WIDTH * PANEL_WIDTH * SLOT_SIZE_PER
#define SLOT_MID               WINDOW_WIDTH * PANEL_WIDTH * .5
#define BUILD_SLOTS_TOP_MARGIN 280 // in pixel