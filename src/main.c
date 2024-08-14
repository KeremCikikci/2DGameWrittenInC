#include <stdio.h>   
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "./constants.h"

SDL_Surface * TEXTURES_Surface_Map          = NULL;
SDL_Texture * TEXTURES_Texture_Map          = NULL;
SDL_Surface * TEXTURES_Surface_archerTower  = NULL;
SDL_Texture * TEXTURES_Texture_archerTower  = NULL;
SDL_Texture * TEXTURES_Texture_wizardTower  = NULL;
SDL_Surface * TEXTURES_Surface_wizardTower  = NULL;
SDL_Surface * TEXTURES_Surface_woodManTower = NULL;
SDL_Texture * TEXTURES_Texture_woodManTower = NULL;
SDL_Texture * TEXTURES_Texture_allPropBuild = NULL;

SDL_Surface * TEXTURES_Surface_tree         = NULL;
SDL_Texture * TEXTURES_Texture_tree         = NULL;

SDL_Surface * TEXTURES_Surface_woodMan      = NULL;
SDL_Texture * TEXTURES_Texture_woodMan      = NULL;

SDL_Surface * TEXTURES_Surface_arrow        = NULL;
SDL_Texture * TEXTURES_Texture_arrow        = NULL;
SDL_Surface * TEXTURES_Surface_magic        = NULL;
SDL_Texture * TEXTURES_Texture_magic        = NULL;

SDL_Surface * TEXTURES_Surface_loadScreen   = NULL;
SDL_Texture * TEXTURES_Texture_loadScreen   = NULL;

SDL_Surface * moneyTextSurface              = NULL;
SDL_Texture * moneyTextTexture              = NULL;
SDL_Surface * clockTextSurface              = NULL;
SDL_Texture * clockTextTexture              = NULL;
SDL_Surface * dayTextSurface                = NULL;
SDL_Texture * dayTextTexture                = NULL;
SDL_Surface * coordinatesTextSurface        = NULL;
SDL_Texture * coordinatesTextTexture        = NULL;
SDL_Surface * archerTextSurface             = NULL;
SDL_Texture * archerTextTexture             = NULL;
SDL_Surface * wizardTextSurface             = NULL;
SDL_Texture * wizardTextTexture             = NULL;
SDL_Surface * woodManTextSurface            = NULL;
SDL_Texture * woodManTextTexture            = NULL;
SDL_Surface * sellTextSurface               = NULL;
SDL_Texture * sellTextTexture               = NULL;

SDL_Surface * loadTextSurface               = NULL;
SDL_Texture * loadTextTexture               = NULL;

TTF_Font    * font                          = NULL;
TTF_Font    * loadFont                      = NULL;

SDL_Rect _256x256                           = {0,0,256,256};
SDL_Rect _1725x1078                         = {0,0,1725,1078};
SDL_Color textColor                         = {0, 0, 0};
SDL_Color whiteColor                         = {230, 230, 230};

char moneyText2render[30];
char clockText2render[30];
char dayText2render[30];
char coordinatesText2render[30];
char archerText2render[30];
char wizardText2render[30];
char woodManText2render[30];
char sellText2render[30];

int game_is_running                         = FALSE;
SDL_Window* window                          = NULL;
SDL_Renderer* renderer                      = NULL;

int last_frame_time                         = 0;

int tilesPerWidth                           = DEF_TILES_PER_WIDTH;
int tileSize                                = (int)(WINDOW_WIDTH / DEF_TILES_PER_WIDTH);
int tileMaxSize                             = (int)(WINDOW_WIDTH / MIN_TILES_PER_WIDTH);
int tileMinSize                             = (int)(WINDOW_WIDTH / MAX_TILES_PER_WIDTH);

int mapWidth; // in pixel
int mapHeight; // in pixel

int horMargin                               = (int)(WINDOW_WIDTH * HOR_MARGIN);
int	verMargin                               = (int)(WINDOW_HEIGHT * VER_MARGIN);

int isBuilding                              = FALSE;

float lightLevel                            = 255;

// Empire
struct empires{
	int money; // in coin
}empire;

// MAP
typedef struct{
	float x;
	float y;
	float width;
	float height;
} maps;
maps map;

// COORDINATE
typedef struct{
	int x;
	int y;
}coordinates; // in tile

// STORE KEY BOOLEANS (ON PRESS)
struct keys{
	// KEYBOARD
	int a;
	int s;
	int d;
	int w;

	int c;

	int space;

	int ctrl;
	int shift;

	int plus;
	int minus;

	int _1;
	int _2;
	int _3;

	// MOUSE
	int left;
	int right;
	int scroll;
}key;

// INFO
struct mousePosition{
  int x;
  int y;
} mouse;

coordinates mouseCoordinate;

struct buildingScratchs{
	int visible;
	int x;
	int y;
	int width;
	int height;
	int isOnAnotherBuild;
	int isOutside;
	int enoughMoney;
}buildingScratch; // in tile

struct building{
	int reserve;
	struct enemy* target;
	int type;
	int x;
	int y;
	int width; // in tile
	int height; // in tile
	float health; // in hp
	float healthPercentage; // in percantage 1 = 100%
	float range; // in tile
	int demage; // in hp
	int demageArea; // in tile
	float coolDown; // in second
	int cost; // in coin
	float sellPercentage; // in percentage 1 = 100%
	int isHover;
}buildingDef;

enum buildTypes {ARCHERTOWER, WIZARDTOWER, WOODMANTOWER};
enum buildTypes currentBuilding;

struct archerTower{
	int reserve;
	struct enemy* target;
	int width; // in tile
	int height; // in tile
	float health; // in hp
	float healthPercentage; // in percantage 1 = 100%
	float range; // in tile
	int demage; // in hp
	float coolDown; // in second
	int cost; // in coin
	float sellPercentage; // in percentage 1 = 100%
}archerTowerDef;

struct arrow{
	int reserve;
	struct enemy* target;
	float x;
	float y;
	float speedX;
	float speedY;
	float velX;
	float velY;
	float angle;
}arrowDef;

struct magic{
	int reserve;
	struct enemy* target;
	float x;
	float y;
	float speedX;
	float speedY;
	float velX;
	float velY;
}magicDef;

struct wizardTower{
	int reserve;
	int width; // in tile
	int height; // in tile
	float health; // in hp
	float healthPercentage; // in percantage 1 = 100%
	float range; // in tile
	int demage; // in hp
	float demageArea; // in tile
	float coolDown; // in second
	int cost; // in coin
	float sellPercentage; // in percentage 1 = 100%
}wizardTowerDef;

struct woodManTower{
	int reserve;
	int width; // in tile
	int height; // in tile
	float health; // in hp
	float healthPercentage; // in percantage 1 = 100%
	int cost; // in coin
	float sellPercentage; // in percentage 1 = 100%
}woodManTowerDef;

struct enemy{
	int reserve;
	struct building* target;
	float health; // in hp
	float healthPercentage; // in hp
	int state;
	int demage;
	float x; // in tile
	float y; // in tile
	float speedX; // in tile
	float speedY; // in tile
	float velX; // in tile
	float velY; // in tile
}enemyDef;

enum enemyState {GOING, ATTACKING};

struct tree{
	int reserve;
	int owned;
	float x;
	float y;
	float width;
	float height;
	float health;
	float healthPercentage;
}treeDef;
int treeCount;

struct woodMan{
	int reserve;
	struct tree* target;
	int state;
	struct building* home;
	float x; // in tile
	float y; // in tile
	float speedX; // in tile
	float speedY; // in tile
	float velX; // in tile
	float velY; // in tile
	float load;
	float loadPercentage; // in percentage 1 = 100%
}woodManDef;

enum woodManState {_GOING, ONTREE, COMING}; // GOING is already defined

struct building builds[MAX_BUILDINGS];
struct enemy enemies[400];
struct arrow arrows[500];
struct magic magics[500];
struct tree trees[MAX_TREES];
struct woodMan woodMans[MAX_BUILDINGS];

float _time = 0;
int day = 0;
enum dayState {DAYLIGHT, NIGHT};
enum dayState currentDayState;

enum gameState {LOADSCREEN, GAME, PAUSED};
enum gameState currentGameState;

float transition = LOADSCREEN_CHANGE_BG;
int bg_index;
char bgPath[30];

// HELPER FUNCTIONS
void getCoordinates(maps map, int x, int y){
	if(mouse.x >= map.x && mouse.x <= map.x + map.width && mouse.y >= map.y && mouse.y <= map.y + map.height){
		mouseCoordinate.x = (int)((float)(mouse.x - map.x) / tileSize);
		mouseCoordinate.y = (int)((float)(mouse.y - map.y) / tileSize);
	}
}

int collisionCheck(float ax,float ay, float awidth, float aheight,float bx,float by,float bwidth,float bheight){
	return ax+awidth > bx && bx+bwidth > ax && ay+aheight > by && by+bheight > ay;
}

void drawCircle(SDL_Renderer *renderer, int centerX, int centerY, int radius, int thickness) {
    int x, y;
    for (int r = radius - thickness + 1; r <= radius; r++) {
        for (y = -r; y <= r; y++) {
            x = (int)sqrt(r * r - y * y);
            SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
            SDL_RenderDrawPoint(renderer, centerX - x, centerY + y);
            SDL_RenderDrawPoint(renderer, centerX + x, centerY - y);
            SDL_RenderDrawPoint(renderer, centerX - x, centerY - y);
        }
    }
}

void updateMoney(){
	sprintf(moneyText2render, "Money: %d", empire.money);
    
	moneyTextSurface = TTF_RenderText_Solid(font, moneyText2render, textColor);

	moneyTextTexture = SDL_CreateTextureFromSurface(renderer, moneyTextSurface);
}

void updateClock(){
	int hour = _time / ((float)DAY_IN_SECONDS / 24);
	int min = fmod(_time, (float)DAY_IN_SECONDS / 24) * 60 / ((float)DAY_IN_SECONDS / 24);
	sprintf(clockText2render, "%d:%d O'clock", hour, min);
    
	clockTextSurface = TTF_RenderText_Solid(font, clockText2render, textColor);

	clockTextTexture = SDL_CreateTextureFromSurface(renderer, clockTextSurface);
}

void updateDay(){
	sprintf(dayText2render, "Survived Day: %d", day);
    
	dayTextSurface = TTF_RenderText_Solid(font, dayText2render, textColor);

	dayTextTexture = SDL_CreateTextureFromSurface(renderer, dayTextSurface);
}

void updateCoordinates(){
	sprintf(coordinatesText2render, "%d:%d", mouseCoordinate.x, mouseCoordinate.y);

	coordinatesTextSurface = TTF_RenderText_Solid(font, coordinatesText2render, textColor);
	
	coordinatesTextTexture = SDL_CreateTextureFromSurface(renderer, coordinatesTextSurface);
}

void updateBG(int bg_index){
	sprintf(bgPath, "assets/bg/%d.jpg", bg_index);
	
	TEXTURES_Surface_loadScreen = IMG_Load(bgPath);
	
	TEXTURES_Texture_loadScreen = SDL_CreateTextureFromSurface(renderer,TEXTURES_Surface_loadScreen);
}

void showHealthBar(struct building obj){
	float health = 0;
	if(obj.type == ARCHERTOWER)
		health = (float)ARCHER_TOWER_HEALTH;
	else if(obj.type == WIZARDTOWER)
		health = (float)WIZARD_TOWER_HEALTH;
	else if(obj.type == WOODMANTOWER)
		health = (float)WOODMAN_TOWER_HEALTH;

	obj.healthPercentage = obj.health / health;

	SDL_Rect border2render = {
		(int)(obj.x * tileSize + map.x - obj.width * tileSize * .5),
		(int)((obj.y + obj.height + 0.2) * tileSize + map.y - obj.height * tileSize * .5),
		(int)(obj.width * tileSize),
		(int)(tileSize * .3)
	};

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, &border2render);

	SDL_Rect health2render = {
		(int)((obj.x + 0.05) * tileSize + map.x - obj.width * tileSize * .5),
		(int)((obj.y + obj.height + 0.25) * tileSize + map.y - obj.height * tileSize * .5),
		(int)((obj.width - 0.1) * tileSize * obj.healthPercentage),
		(int)(tileSize * .2)
	};

	SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);
	SDL_RenderFillRect(renderer, &health2render);
}

void showSellText(struct building obj){
	SDL_Rect sell2render = {
		(int)(obj.x * tileSize + map.x - obj.width * tileSize * .5),
		(int)((obj.y + obj.height + 0.7) * tileSize + map.y - obj.height * tileSize * .5),
		(int)(obj.width * tileSize),
		(int)(tileSize * .3)
	};
	SDL_RenderCopy(renderer, sellTextTexture, NULL, &sell2render);
}

void selectBuildingType(){
	if(currentBuilding == ARCHERTOWER){
		buildingDef.type = ARCHERTOWER;
		buildingDef.width = archerTowerDef.width;
		buildingDef.height = archerTowerDef.height;
		buildingDef.health = archerTowerDef.health;
		buildingDef.healthPercentage = archerTowerDef.healthPercentage;
		buildingDef.range = archerTowerDef.range;
		buildingDef.demage = archerTowerDef.demage;
		buildingDef.coolDown = archerTowerDef.coolDown;
		buildingDef.cost = archerTowerDef.cost;
		buildingDef.sellPercentage = archerTowerDef.sellPercentage;
	}
	else if(currentBuilding == WIZARDTOWER){
		buildingDef.type = WIZARDTOWER;
		buildingDef.width = wizardTowerDef.width;
		buildingDef.height = wizardTowerDef.height;
		buildingDef.health = wizardTowerDef.health;
		buildingDef.healthPercentage = wizardTowerDef.healthPercentage;
		buildingDef.range = wizardTowerDef.range;
		buildingDef.demage = wizardTowerDef.demage;
		buildingDef.coolDown = wizardTowerDef.coolDown;
		buildingDef.cost = wizardTowerDef.cost;
		buildingDef.demageArea = wizardTowerDef.demageArea;
		buildingDef.sellPercentage = wizardTowerDef.sellPercentage;
	}
	else if(currentBuilding == WOODMANTOWER){
		buildingDef.type = WOODMANTOWER;
		buildingDef.width = woodManTowerDef.width;
		buildingDef.height = woodManTowerDef.height;
		buildingDef.health = woodManTowerDef.health;
		buildingDef.healthPercentage = woodManTowerDef.healthPercentage;
		buildingDef.cost = woodManTowerDef.cost;
		buildingDef.sellPercentage = woodManTowerDef.sellPercentage;
	}
}

int initialize_window(void){
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		fprintf(stderr, "Error initializing SDL.\n");
		return FALSE;
	}
	window = SDL_CreateWindow(
			NULL,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			WINDOW_WIDTH,
			WINDOW_HEIGHT,
			SDL_WINDOW_BORDERLESS
			);
	if (!window) {
		fprintf(stderr, "Error creating SDL Window. \n");
		return FALSE;
	}
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		fprintf(stderr, "Error creating SDL Renderer. \n");
		return FALSE;
	}

	TEXTURES_Surface_archerTower = IMG_Load("assets/archerTower.png");
	TEXTURES_Texture_archerTower = SDL_CreateTextureFromSurface(renderer, TEXTURES_Surface_archerTower);
	TEXTURES_Surface_wizardTower = IMG_Load("assets/wizardTower.png");
	TEXTURES_Texture_wizardTower = SDL_CreateTextureFromSurface(renderer, TEXTURES_Surface_wizardTower);
	TEXTURES_Surface_woodManTower = IMG_Load("assets/woodManTower.png");
	TEXTURES_Texture_woodManTower = SDL_CreateTextureFromSurface(renderer, TEXTURES_Surface_woodManTower);
	TEXTURES_Surface_Map = IMG_Load("assets/map.png");
	TEXTURES_Texture_Map = SDL_CreateTextureFromSurface(renderer,TEXTURES_Surface_Map);
	TEXTURES_Surface_tree = IMG_Load("assets/tree.png");
	TEXTURES_Texture_tree = SDL_CreateTextureFromSurface(renderer,TEXTURES_Surface_tree);
	TEXTURES_Surface_woodMan = IMG_Load("assets/woodMan.png");
	TEXTURES_Texture_woodMan = SDL_CreateTextureFromSurface(renderer,TEXTURES_Surface_woodMan);
	TEXTURES_Surface_arrow = IMG_Load("assets/arrow.png");
	TEXTURES_Texture_arrow = SDL_CreateTextureFromSurface(renderer,TEXTURES_Surface_arrow);
	TEXTURES_Surface_magic = IMG_Load("assets/magic.png");
	TEXTURES_Texture_magic = SDL_CreateTextureFromSurface(renderer,TEXTURES_Surface_magic);
	
	SDL_FreeSurface(TEXTURES_Surface_archerTower);
	SDL_FreeSurface(TEXTURES_Surface_wizardTower);
	SDL_FreeSurface(TEXTURES_Surface_woodManTower);
	SDL_FreeSurface(TEXTURES_Surface_Map);
	SDL_FreeSurface(TEXTURES_Surface_tree);
	SDL_FreeSurface(TEXTURES_Surface_woodMan);
	SDL_FreeSurface(TEXTURES_Surface_arrow);
	SDL_FreeSurface(TEXTURES_Surface_magic);

	TTF_Init();

    font = TTF_OpenFont("assets/Roboto-Medium.ttf", 24);
    loadFont = TTF_OpenFont("assets/Roboto-Medium.ttf", 148);

    if (!font || !loadFont) {
        printf("Font could not be loaded! TTF_Error: %s\n", TTF_GetError());
        return FALSE;
    }

	return TRUE;
}

void setup(){
	// GENERAL INIT
	srand(time(NULL));

	SDL_GetMouseState(&mouse.x, &mouse.y);
	getCoordinates(map, mouse.x, mouse.y);
	updateCoordinates();
	updateBG(0);

	sprintf(archerText2render, "%d / %d", ARCHER_TOWER_COST, (int)(ARCHER_TOWER_COST * ARCHER_TOWER_SELL_PER));
	sprintf(wizardText2render, " %d / %d", WIZARD_TOWER_COST, (int)(WIZARD_TOWER_COST * WIZARD_TOWER_SELL_PER));
	sprintf(woodManText2render, " %d / %d", WOODMAN_TOWER_COST, (int)(WOODMAN_TOWER_COST * WOODMAN_TOWER_SELL_PER));
	sprintf(sellText2render, "CTRL + S TO SELL BUILDING");

	_time                            = NIGHT_IN_SECONDS;

	currentBuilding                  = ARCHERTOWER;
	currentDayState                  = DAYLIGHT;
	currentGameState                 = LOADSCREEN;

	// MAP INIT
	mapWidth                         = (int)(tileSize * MAP_WIDTH);
	mapHeight                        = (int)(tileSize * MAP_HEIGHT);

	map.x                            = horMargin;
	map.y                            = verMargin;
	map.width                        = mapWidth;
	map.height                       = mapHeight;

	// CONTROL INIT
	key.a                            = FALSE;
	key.s                            = FALSE;
	key.d                            = FALSE;
	key.w                            = FALSE;
	key.c                            = FALSE;
	key.space                        = FALSE;
	key._1                           = FALSE;
	key._2                           = FALSE;
	key._3                           = FALSE;
	key.ctrl                         = FALSE;
	key.plus                         = FALSE;
	key.minus                        = FALSE;
	key.left                         = FALSE;
	key.right                        = FALSE;

	// EMPIRE INIT
	empire.money                     = START_MONEY;
	updateMoney();
	updateClock();
	updateDay();
	updateCoordinates();

	archerTextSurface                = TTF_RenderText_Solid(font, archerText2render, textColor);
	archerTextTexture                = SDL_CreateTextureFromSurface(renderer, archerTextSurface);
	wizardTextSurface                = TTF_RenderText_Solid(font, wizardText2render, textColor);
	wizardTextTexture                = SDL_CreateTextureFromSurface(renderer, wizardTextSurface);
	woodManTextSurface               = TTF_RenderText_Solid(font, woodManText2render, textColor);
	woodManTextTexture               = SDL_CreateTextureFromSurface(renderer, woodManTextSurface);
	sellTextSurface                  = TTF_RenderText_Solid(font, sellText2render, textColor);
	sellTextTexture                  = SDL_CreateTextureFromSurface(renderer, sellTextSurface);
	loadTextSurface                  = TTF_RenderText_Solid(loadFont, "LOAD", whiteColor);
	loadTextTexture                  = SDL_CreateTextureFromSurface(renderer, loadTextSurface);

	// BUILDING INIT
	buildingScratch.visible          = FALSE;
	buildingScratch.isOnAnotherBuild = FALSE;
	buildingScratch.isOutside        = FALSE;
	buildingScratch.enoughMoney      = TRUE;

	archerTowerDef.reserve           = FALSE;
	archerTowerDef.target            = NULL;
	archerTowerDef.width             = ARCHER_TOWER_WIDTH;
	archerTowerDef.height            = ARCHER_TOWER_HEIGHT;
	archerTowerDef.health            = ARCHER_TOWER_HEALTH;
	archerTowerDef.healthPercentage  = TRUE;
	archerTowerDef.demage            = ARCHER_TOWER_DEMAGE;
	archerTowerDef.range             = ARCHER_TOWER_RANGE;
	archerTowerDef.coolDown          = ARCHER_TOWER_COOLDOWN;
	archerTowerDef.cost              = ARCHER_TOWER_COST;
	archerTowerDef.sellPercentage    = ARCHER_TOWER_SELL_PER;

	wizardTowerDef.reserve           = FALSE;
	wizardTowerDef.width             = WIZARD_TOWER_WIDTH;
	wizardTowerDef.height            = WIZARD_TOWER_HEIGHT;
	wizardTowerDef.health            = WIZARD_TOWER_HEALTH;
	wizardTowerDef.healthPercentage  = TRUE;
	wizardTowerDef.range             = WIZARD_TOWER_RANGE;
	wizardTowerDef.demage            = WIZARD_TOWER_DEMAGE;
	wizardTowerDef.demageArea        = WIZARD_TOWER_DEM_AREA;
	wizardTowerDef.cost              = WIZARD_TOWER_COST;
	wizardTowerDef.coolDown          = WIZARD_TOWER_COOLDOWN;
	wizardTowerDef.sellPercentage    = WIZARD_TOWER_SELL_PER;

	woodManTowerDef.reserve          = FALSE;
	woodManTowerDef.width            = WOODMAN_TOWER_WIDTH;
	woodManTowerDef.height           = WOODMAN_TOWER_HEIGHT;
	woodManTowerDef.health           = WOODMAN_TOWER_HEALTH;
	woodManTowerDef.healthPercentage = TRUE;
	woodManTowerDef.cost             = WOODMAN_TOWER_COST;
	woodManTowerDef.sellPercentage   = WOODMAN_TOWER_SELL_PER;

	// WOODMAN INIT
	woodManDef.reserve               = FALSE;
	woodManDef.target                = NULL;
	woodManDef.home                  = NULL;
	woodManDef.state                 = GOING;
	woodManDef.speedX                = FALSE;
	woodManDef.speedY                = FALSE;
	woodManDef.velX                  = FALSE;
	woodManDef.velY                  = FALSE;
	woodManDef.load                  = FALSE;
	woodManDef.loadPercentage        = FALSE;

	// TREE INIT
	treeDef.reserve                  = FALSE;
	treeDef.owned                    = FALSE;
	treeDef.width                    = TREE_WIDTH;
	treeDef.height                   = TREE_HEIGHT;
	treeDef.health                   = TREE_HEALTH;
	treeDef.healthPercentage         = TRUE;

	treeCount                        = FALSE;

	// ENEMY INIT
	enemyDef.reserve                 = FALSE;
	enemyDef.target                  = NULL;
	enemyDef.state                   = GOING;
	enemyDef.health                  = ENEMY_HEALTH;
	enemyDef.healthPercentage        = TRUE;
	enemyDef.demage                  = ENEMY_DEMAGE;
	enemyDef.speedX                  = FALSE;
	enemyDef.speedY                  = FALSE;
	enemyDef.velX                    = FALSE;
	enemyDef.velY                    = FALSE;
	
	// ARROW INIT
	arrowDef.reserve                 = FALSE;
	arrowDef.target                  = NULL;
	arrowDef.speedX                  = FALSE;
	arrowDef.speedY                  = FALSE;
	arrowDef.velX                    = FALSE;
	arrowDef.velY                    = FALSE;
	arrowDef.angle                   = FALSE;

	// MAGIC INIT
	magicDef.reserve                 = FALSE;
	magicDef.target                  = NULL;
	magicDef.speedX                  = FALSE;
	magicDef.speedY                  = FALSE;
	magicDef.velX                    = FALSE;
	magicDef.velY                    = FALSE;
}

void process_input(void) {
    SDL_Event event;
    SDL_Keymod mod = SDL_GetModState();

    int isReleasedC = FALSE;
	int isReleasedLeft = FALSE;
	int isReleasedRight = FALSE;
	int isReleasedSpace = FALSE;

    while (SDL_PollEvent(&event)) {
        // Check for quit event or escape key
        if ((event.type == SDL_QUIT) || (event.key.keysym.sym == SDLK_ESCAPE)) {
            game_is_running = FALSE;
        }

        if (event.type == SDL_KEYDOWN) {
            if (mod & KMOD_SHIFT) key.shift = TRUE;
            switch(event.key.keysym.sym) {
                case SDLK_a: key.a                         = TRUE; break;
                case SDLK_s: key.s                         = TRUE; break;
                case SDLK_d: key.d                         = TRUE; break;
                case SDLK_w: key.w                         = TRUE; break;
                case SDLK_c: key.c                         = TRUE; break;
                case SDLK_SPACE: key.space                 = TRUE; break;
                case SDLK_LCTRL:
                case SDLK_RCTRL: key.ctrl                  = TRUE; break;
                case SDLK_PLUS: key.plus                   = TRUE; break;
                case SDLK_MINUS: key.minus                 = TRUE; break;
                case SDLK_1: key._1                        = TRUE; break;
                case SDLK_2: key._2                        = TRUE; break;
                case SDLK_3: key._3                        = TRUE; break;
            }
        }

        if (event.type == SDL_KEYUP) {
            if (event.key.keysym.sym == SDLK_LSHIFT || event.key.keysym.sym == SDLK_RSHIFT) key.shift = FALSE;
            switch(event.key.keysym.sym) {
                case SDLK_a: key.a                         = FALSE; break;
                case SDLK_s: key.s                         = FALSE; break;
                case SDLK_d: key.d                         = FALSE; break;
                case SDLK_w: key.w                         = FALSE; break;
                case SDLK_c: key.c                         = RELEASED; isReleasedC = TRUE; break;
                case SDLK_SPACE: key.space                 = RELEASED; isReleasedSpace = TRUE; break;
                case SDLK_LCTRL:
                case SDLK_RCTRL: key.ctrl                  = FALSE; break;
                case SDLK_PLUS: key.plus                   = FALSE; break;
                case SDLK_MINUS: key.minus                 = FALSE; break;
                case SDLK_1: key._1                        = FALSE; break;
                case SDLK_2: key._2                        = FALSE; break;
                case SDLK_3: key._3                        = FALSE; break;
            }
        }

		SDL_GetMouseState(&mouse.x, &mouse.y);
		getCoordinates(map, mouse.x, mouse.y);
		updateCoordinates();

		if(event.type == SDL_MOUSEBUTTONDOWN){
			if(event.button.button == SDL_BUTTON_LEFT) key.left = TRUE;
			if(event.button.button == SDL_BUTTON_RIGHT) key.right = TRUE;
		}
		if(event.type == SDL_MOUSEBUTTONUP){
			if(event.button.button == SDL_BUTTON_LEFT){
				key.left = RELEASED;
				isReleasedLeft = TRUE;
			}
			if(event.button.button == SDL_BUTTON_RIGHT){
				key.right = RELEASED;
				isReleasedRight = TRUE;
			}
		}
		if (event.type == SDL_MOUSEWHEEL)
			key.scroll = event.wheel.y;
    }

    // Reset key.c if it was released and no further release event has occurred
    if (key.c == RELEASED && !isReleasedC) {
        key.c = FALSE;
    }
    if (key.space == RELEASED && !isReleasedSpace) {
        key.space = FALSE;
    }
	if(key.left == RELEASED && !isReleasedLeft){
		key.left = FALSE;
	}
	if(key.right == RELEASED && !isReleasedRight){
		key.right = FALSE;
	}
}

void update(void){
	int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);
		
	if(time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME)
		SDL_Delay(time_to_wait);

	float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;

	last_frame_time = SDL_GetTicks();

	if(currentGameState == LOADSCREEN){
		if(transition > 0)
			transition -= delta_time;
		else{
			transition = LOADSCREEN_CHANGE_BG;
			bg_index = rand() % BACKGROUND_IMAGE_COUNT;
			updateBG(bg_index);
		}

		if(key.left == RELEASED || key.space == RELEASED)
			currentGameState = GAME;
	}
	if(currentGameState == GAME){
		// UPDATE TIMER
		_time += delta_time;
		updateClock();
		if(_time >= DAY_IN_SECONDS){
			day++;
			updateDay();
			_time = 0;

			// KILL OLD ENEMIES AND SPAWN NEW ONES
			int spawnedEnemies = 0;
			for(size_t i = 0; i < sizeof(enemies) / sizeof(enemies[0]); i++){
				if(spawnedEnemies < ENEMIES_AFTER_DAY(day)){
					if(!KILL_ENEMIES_NEXT_DAY)
						if(enemies[i].reserve)
							continue;
					enemies[i] = enemyDef;
					enemies[i].reserve = TRUE;

					int x, y;

					while(1==1){
						x = rand() % MAP_WIDTH;
						y = rand() % MAP_HEIGHT;
						int isOnBuilding = FALSE;
						int isOnTree = FALSE;

						// CHECK BUILDINGS
						for(size_t j = 0; j < sizeof(builds) / sizeof(builds[0]); j++){
							if(builds[j].reserve)
								isOnBuilding = collisionCheck(builds[j].x, builds[j].y, builds[j].width, builds[j].height, x, y, 0, 0);
						}
						// CHECK TREES
						for(size_t j = 0; j < sizeof(trees) / sizeof(trees[0]); j++){
							if(trees[j].reserve)
								isOnTree = (trees[j].x == x && trees[j].y == y) ? 1 : 0;
						}

						if(!isOnBuilding && !isOnTree) break;
						
					}
					enemies[i].x = x;
					enemies[i].y = y;

					spawnedEnemies++;
				}
				else{
					enemies[i].reserve = FALSE;
				}
			}

			// CLEAN BUILD TARGETS
			for(size_t i = 0; i < sizeof(builds) / sizeof(builds[0]); i++){
				builds[i].target = NULL;
			}
			// CLEAN ARROWS
			for(size_t i = 0; i < sizeof(arrows) / sizeof(arrows[0]); i++){
				arrows[i].reserve = FALSE;
			}
			// CLEAN MAGICS
			for(size_t i = 0; i < sizeof(magics) / sizeof(magics[0]); i++){
				magics[i].reserve = FALSE;
			}
		}
		if(_time < NIGHT_IN_SECONDS){
			currentDayState = NIGHT;
		}
		else{
			currentDayState = DAYLIGHT;
		}

		// BUILDING
		if(key.c == RELEASED) isBuilding ^= 1;

		if(isBuilding){
			if(key._1) currentBuilding = ARCHERTOWER;
			if(key._2) currentBuilding = WIZARDTOWER;
			if(key._3) currentBuilding = WOODMANTOWER;
			selectBuildingType();
			buildingScratch.width = buildingDef.width;
			buildingScratch.height = buildingDef.height;
			
			// CHECK BOUNDRIES
			if(mouseCoordinate.x >= 0 && mouseCoordinate.y >= 0 && mouseCoordinate.x <= MAP_WIDTH - buildingScratch.width && mouseCoordinate.y <= MAP_HEIGHT - buildingScratch.height){
				buildingScratch.x = mouseCoordinate.x;
				buildingScratch.y = mouseCoordinate.y;

				// CHECK OTHER BUILDINGS
				int isOnAnotherBuilding = FALSE;
				for(size_t i = 0; i < sizeof(builds) / sizeof(builds[0]); i++){
					if(builds[i].reserve == TRUE){
						if(collisionCheck(builds[i].x, builds[i].y, builds[i].width, builds[i].height, buildingScratch.x, buildingScratch.y, buildingScratch.width, buildingScratch.height)){
							isOnAnotherBuilding = TRUE;
							break;
						}
					}
				}

				// CHECK MAP BOUNDRIES
				int isOutside = FALSE;
				if((buildingScratch.x - ceil(buildingScratch.width / 2) <= 0) || (buildingScratch.y - ceil(buildingScratch.height / 2) <= 0) || (buildingScratch.x + ceil(buildingScratch.width / 2) > MAP_WIDTH) || (buildingScratch.y + ceil(buildingScratch.height / 2) > MAP_HEIGHT))
					isOutside = TRUE;

				// CHECK MONEY
				int enoughMoney = TRUE;
				if(buildingDef.cost > empire.money)
					enoughMoney = FALSE;

				buildingScratch.isOnAnotherBuild = isOnAnotherBuilding;
				buildingScratch.visible          = TRUE;
				buildingScratch.isOutside        = isOutside;
				buildingScratch.enoughMoney      = enoughMoney;

				// BUILD IT
				if(key.left == RELEASED && buildingScratch.visible && !buildingScratch.isOnAnotherBuild && !buildingScratch.isOutside && empire.money >= buildingDef.cost){
					for(size_t i = 0; i < sizeof(builds) / sizeof(builds[0]); i++){
						if(builds[i].reserve != TRUE){
							builds[i] = buildingDef;
							builds[i].reserve = TRUE;
							builds[i].type = currentBuilding;
							builds[i].x = mouseCoordinate.x;
							builds[i].y = mouseCoordinate.y;
							builds[i].isHover = FALSE;
							empire.money -= buildingDef.cost;
							updateMoney();
							isBuilding = FALSE;
					
							// CREATE WOODMAN IF NEEDED
							if(currentBuilding == WOODMANTOWER){
								for(size_t j = 0; j < sizeof(woodMans) / sizeof(woodMans[0]); j++){
									if(!woodMans[j].reserve){
										woodMans[j] = woodManDef;
										woodMans[j].x = builds[i].x + builds[i].width / 2;
										woodMans[j].y = builds[i].y + builds[i].height / 2;
										woodMans[j].reserve = TRUE;
										woodMans[j].home = &builds[i];
										break;
									}
								}
							}
							break;
						}
					}
				}
			}
		}
		else{
			buildingScratch.visible = FALSE;
		}

		// HOVER
		for(size_t i = 0; i < sizeof(builds) / sizeof(builds[0]); i++){
			if(builds[i].reserve){
				builds[i].isHover = collisionCheck(mouseCoordinate.x, mouseCoordinate.y, 0, 0, builds[i].x - builds[i].width * .5, builds[i].y - builds[i].height * .5, builds[i].width, builds[i].height);
			}
			// SELL BUILDING
			if(builds[i].isHover && builds[i].reserve){
				if(key.s && key.ctrl){
					empire.money += (int)(builds[i].cost * builds[i].sellPercentage);
					updateMoney();
					builds[i].reserve = FALSE;

					// REMOVE WOODMAN
					if(builds[i].type == WOODMANTOWER)
						for(size_t j = 0; j < sizeof(woodMans) / sizeof(woodMans[0]); j++)
							if(woodMans[j].reserve)
								if(woodMans[j].home == &builds[i])
									woodMans[j].reserve = FALSE;			
				}
				break;
			}
		}

		// TREES
		while(treeCount <= MAX_TREES){
			int x = rand() % (int)(MAP_WIDTH - floor(TREE_WIDTH * .5)) + ceil(TREE_WIDTH / 2);
			int y = rand() % (int)(MAP_HEIGHT - floor(TREE_HEIGHT * .5)) + ceil(TREE_HEIGHT / 2);
			int freePlaceInTrees = -1;
			int isOnTree = FALSE;
			int isOnBuilding = FALSE;

			// CHECK OTHER TREES
			for(size_t i = 0; i < sizeof(trees) / sizeof(trees[0]); i++){
				if(freePlaceInTrees == -1 && trees[i].reserve != TRUE){
					freePlaceInTrees = i;
				}
				else if(trees[i].reserve == TRUE){
					if(collisionCheck(x, y, TREE_WIDTH, TREE_HEIGHT, trees[i].x, trees[i].y, TREE_WIDTH, TREE_HEIGHT)){
						isOnTree = TRUE;
						break;
					}
				}
			}
			// CHECK BUILDINGS
			if(!isOnTree){
				for (int i = 0; i < sizeof(builds) / sizeof(builds[0]); i++)
				{
					if(builds[i].reserve == TRUE){
						isOnBuilding = collisionCheck(x, y, TREE_WIDTH, TREE_HEIGHT, builds[i].x, builds[i].y, builds[i].width, builds[i].height);
						if(isOnBuilding)
							break;
					}
				}
			}
			// CREATE IT
			if(!isOnTree && !isOnBuilding){
				treeCount++;
				trees[freePlaceInTrees] = treeDef;
				trees[freePlaceInTrees].reserve = TRUE;
				trees[freePlaceInTrees].x = x;
				trees[freePlaceInTrees].y = y;
			}	
		}

		// FIRE
		for(size_t i = 0; i < sizeof(builds) / sizeof(builds[0]); i++){
			if(builds[i].reserve){
				if(builds[i].range > 0){
					// COOLDOWN
					builds[i].coolDown = builds[i].coolDown > 0 ? builds[i].coolDown - delta_time : 0;

					// FIND A TARGET
					if(builds[i].target == NULL){
						float deltaX = 999;
						float deltaY = 999;
						float distance = 999;
						size_t index;

						// FIND CLOSEST ENEMY
						for(size_t j = 0; j < sizeof(enemies) / sizeof(enemies[0]); j++){
							if(enemies[j].reserve){
								deltaX = enemies[j].x - builds[i].x;
								deltaY = enemies[j].y - builds[i].y;
								if(distance > sqrt(deltaX * deltaX + deltaY * deltaY)){
									distance = sqrt(deltaX * deltaX + deltaY * deltaY);
									index = j;
								}
							}
						}
						if(distance <= builds[i].range){
							builds[i].target = &enemies[index];
						}
						else{
							builds[i].target = NULL;
						}
					}
					else{
						// CHECK IF TARGET IS ALIVE
						if(builds[i].target->reserve == FALSE){
							builds[i].target = NULL;
						}
							
						else{
							// CREATE AN ARROW
							if(builds[i].type == ARCHERTOWER){
								if(builds[i].coolDown == 0){
									for(size_t j = 0; j < sizeof(arrows) / sizeof(arrows[0]); j++){
										if(!arrows[j].reserve){
											arrows[j].reserve = TRUE;
											arrows[j].x = builds[i].x;
											arrows[j].y = builds[i].y;
											arrows[j].target = builds[i].target;

											builds[i].coolDown = ARCHER_TOWER_COOLDOWN;
											break;
										}
									}
								}
							}
							// CREATE A MAGIC
							else if(builds[i].type == WIZARDTOWER){
								if(builds[i].coolDown == 0){
									for(size_t j = 0; j < sizeof(magics) / sizeof(magics[0]); j++){
										if(!magics[j].reserve){
											magics[j].reserve = TRUE;
											magics[j].x = builds[i].x;
											magics[j].y = builds[i].y;
											magics[j].target = builds[i].target;

											builds[i].coolDown = WIZARD_TOWER_COOLDOWN;
											break;
										}
									}
								}
							}
						}
					}
				}
			}
		}

		// ARROWS
		for(size_t i = 0; i < sizeof(arrows) / sizeof(arrows[0]); i++){
			if(arrows[i].reserve){
				if(arrows[i].target != NULL){
					float deltaX = arrows[i].target->x - arrows[i].x;				
					float deltaY = arrows[i].target->y - arrows[i].y;
					float distance = sqrt(deltaX * deltaX + deltaY * deltaY);
					
					arrows[i].speedX = (deltaX / distance) * ARROW_MAX_SPEED;
					arrows[i].speedY = (deltaY / distance) * ARROW_MAX_SPEED;

					arrows[i].x += arrows[i].speedX * delta_time;
					arrows[i].y += arrows[i].speedY * delta_time;
					arrows[i].angle = atan2(deltaY, deltaX) * (180.0 / M_PI) + 90;

					if(distance < ARROW_MAX_SPEED * delta_time){
						arrows[i].x = arrows[i].target->x;
						arrows[i].y = arrows[i].target->y;
						distance = 0;
					}
					if(distance == 0){
						arrows[i].target->health -= ARCHER_TOWER_DEMAGE;
						arrows[i].reserve = FALSE;
					}
				}
			}
		}

		// MAGICS
		for(size_t i = 0; i < sizeof(magics) / sizeof(magics[0]); i++){
			if(magics[i].reserve){
				if(magics[i].target != NULL){
					float deltaX = magics[i].target->x - magics[i].x;				
					float deltaY = magics[i].target->y - magics[i].y;
					float distance = sqrt(deltaX * deltaX + deltaY * deltaY);
					
					magics[i].speedX = (deltaX / distance) * MAGIC_MAX_SPEED;
					magics[i].speedY = (deltaY / distance) * MAGIC_MAX_SPEED;

					magics[i].x += magics[i].speedX * delta_time;
					magics[i].y += magics[i].speedY * delta_time;

					if(distance < MAGIC_MAX_SPEED * delta_time){
						magics[i].x = magics[i].target->x;
						magics[i].y = magics[i].target->y;
						distance = 0;
					}
					if(distance == 0){
						// EXPLOSION DEMAGE
						for(size_t j = 0; j < sizeof(enemies) / sizeof(enemies[0]); j++)
							if(collisionCheck(magics[i].x - WIZARD_TOWER_DEM_AREA / 2, magics[i].y - WIZARD_TOWER_DEM_AREA / 2, WIZARD_TOWER_DEM_AREA, WIZARD_TOWER_DEM_AREA, enemies[j].x, enemies[j].y, WIZARD_TOWER_DEM_AREA, WIZARD_TOWER_DEM_AREA))
								enemies[j].health -= WIZARD_TOWER_DEMAGE;
						
						magics[i].reserve = FALSE;
					}
				}
			}
		}

		// WOODMAN
		for(size_t i = 0; i < sizeof(woodMans) / sizeof(woodMans[0]); i++){
			if(woodMans[i].reserve == TRUE){
				if(woodMans[i].state == GOING){
					// HE HAS A TREE
					if(woodMans[i].target != NULL){			
						float deltaX = woodMans[i].target->x - woodMans[i].x;
						float deltaY = woodMans[i].target->y - woodMans[i].y;
						float distance = sqrt(deltaX * deltaX + deltaY * deltaY);

						// HE IS ON TREE
						if(distance < WOODMAN_MAX_SPEED * delta_time){
							woodMans[i].x = woodMans[i].target->x;
							woodMans[i].y = woodMans[i].target->y;

							woodMans[i].speedX = 0;
							woodMans[i].speedY = 0;

							woodMans[i].state = ONTREE;
						}
						// HE IS GOING
						else {
							woodMans[i].speedX = (deltaX / distance) * WOODMAN_MAX_SPEED;
							woodMans[i].speedY = (deltaY / distance) * WOODMAN_MAX_SPEED;

							woodMans[i].x += woodMans[i].speedX * delta_time;
							woodMans[i].y += woodMans[i].speedY * delta_time;
						}
					}
					// FIND A TREE
					if(woodMans[i].target == NULL){
						float distance = 999;
						struct tree* index = NULL;
						for(size_t j = 0; j < sizeof(trees) / sizeof(trees[0]); j++){
							if(trees[j].reserve){
								if(!trees[j].owned){
									// FIND THE CLOSEST
									float deltaX = woodMans[i].home->x - trees[j].x;
									float deltaY = woodMans[i].home->y - trees[j].y;
									float tempDistance = sqrt(deltaX * deltaX + deltaY * deltaY);
									if(tempDistance < distance){
										index = &trees[j];
										distance = tempDistance;
									}
								}
							}
						}
						index->owned = TRUE;
						woodMans[i].target = index;
					}
				}
				else if(woodMans[i].state == ONTREE){
					// CUT THE TREE
					// TREE HAS A LITTLE HEALTH
					if(woodMans[i].target->health < WOODMAN_POWER * delta_time && woodMans[i].target->health != 0){
						woodMans[i].load += woodMans[i].target->health;
						woodMans[i].target->health = 0;
						woodMans[i].target->healthPercentage = 0;
						woodMans[i].target->reserve = FALSE;
						woodMans[i].target = NULL;
						woodMans[i].state = GOING;
						treeCount--;
					}
					// TREE IS HEALTY
					else if(woodMans[i].target->health > 0){
						woodMans[i].target->health -= WOODMAN_POWER * delta_time;

						woodMans[i].load += WOODMAN_POWER * delta_time;
					}
					if(woodMans[i].load >= WOODMAN_MAX_LOAD - WOODMAN_MAX_LOAD * delta_time){
						woodMans[i].load = WOODMAN_MAX_LOAD;
						woodMans[i].state = COMING;
					}
				}
				else if(woodMans[i].state == COMING){
					float deltaX = woodMans[i].home->x - woodMans[i].x;
					float deltaY = woodMans[i].home->y - woodMans[i].y;
					float distance = sqrt(deltaX * deltaX + deltaY * deltaY);

					// HE IS AT HOME
					if(distance < WOODMAN_MAX_SPEED * delta_time){
						woodMans[i].x = woodMans[i].home->x;
						woodMans[i].y = woodMans[i].home->y;

						woodMans[i].speedX = 0;
						woodMans[i].speedY = 0;
						
						empire.money += (int)(woodMans[i].load * WOOD_PRICE);
						woodMans[i].load = 0;
						updateMoney();
						woodMans[i].state = GOING;
					}
					// HE IS COMING
					else {
						woodMans[i].speedX = (deltaX / distance) * WOODMAN_MAX_SPEED;
						woodMans[i].speedY = (deltaY / distance) * WOODMAN_MAX_SPEED;

						woodMans[i].x += woodMans[i].speedX * delta_time;
						woodMans[i].y += woodMans[i].speedY * delta_time;
					}
				}
			}
		}

		// ENEMIES
		for(size_t i = 0; i < sizeof(enemies) / sizeof(enemies[0]); i++){
			if(enemies[i].reserve){
				if(enemies[i].health > 0){
					// HE IS GOING
					if(enemies[i].state == GOING){
						// HE HAS A TARGET
						if(enemies[i].target != NULL){
							if(enemies[i].target->reserve){
								float deltaX = enemies[i].target->x - enemies[i].x;
								float deltaY = enemies[i].target->y - enemies[i].y;
								float distance = sqrt(deltaX * deltaX + deltaY * deltaY);

								// HE IS AT A BUILDING
								if(distance <= ENEMY_MAX_SPEED * delta_time){
									enemies[i].x = enemies[i].target->x;
									enemies[i].y = enemies[i].target->y;

									enemies[i].speedX = 0;
									enemies[i].speedY = 0;

									enemies[i].state = ATTACKING;
								}
								// HE IS GOING
								else {
									enemies[i].speedX = (deltaX / distance) * ENEMY_MAX_SPEED;
									enemies[i].speedY = (deltaY / distance) * ENEMY_MAX_SPEED;

									enemies[i].x += enemies[i].speedX * delta_time;
									enemies[i].y += enemies[i].speedY * delta_time;
								}
							}
							else
								enemies[i].target = NULL;
						}
						// FIND A TARGET
						else{
							// FIND CLOSEST BUILDING
							float deltaX;
							float deltaY;
							float distance = 999;

							for(size_t j = 0; j < sizeof(builds) / sizeof(builds[0]); j++){
								if(builds[j].reserve){
									deltaX = builds[j].x - enemies[i].x;
									deltaY = builds[j].y - enemies[i].y;
									if(distance > sqrt(deltaX * deltaX + deltaY * deltaY)){
										distance = sqrt(deltaX * deltaX + deltaY * deltaY);
										enemies[i].target = &builds[j];
									}
								}
							}
							if(enemies[i].target == NULL)
								printf("GAME OVER");
						}
					}
					else if(enemies[i].state == ATTACKING){
						if(!enemies[i].target->reserve){
							enemies[i].state =  GOING;
						}
						else{
							if(enemies[i].target->health <= enemies[i].demage * delta_time){
								enemies[i].target->reserve = FALSE;
								
								// CLEAN WOODMAN
								for(size_t j = 0; j < sizeof(woodMans) / sizeof(woodMans[0]); j++){
									if(enemies[i].target == woodMans[j].home){
										woodMans[j].reserve = FALSE;
										break;
									}
								}
							}
								
							else
								enemies[i].target->health -= enemies[i].demage * delta_time;

						}
					}
				}
				else{
					// CLEAN ARROWS
					for(size_t a = 0; a < sizeof(arrows) / sizeof(arrows[0]); a++){
						if(arrows[a].target == &enemies[i])
							arrows[a].reserve = FALSE;
					}
					// CLEAN MAGICS
					for(size_t a = 0; a < sizeof(magics) / sizeof(magics[0]); a++){
						if(magics[a].target == &enemies[i])
							magics[a].reserve = FALSE;
					}
					enemies[i].reserve = FALSE;
				}
			}
		}

		// BUILDING BY MOUSE CLICK
		if(key.left == RELEASED){
			if(mouse.x >= SLOT_LEFT_MARGIN && mouse.x <= SLOT_LEFT_MARGIN + SLOT_SIZE && mouse.y >= BUILD_SLOTS_TOP_MARGIN && mouse.y <= BUILD_SLOTS_TOP_MARGIN + SLOT_SIZE){
				isBuilding = TRUE;
				currentBuilding = ARCHERTOWER;
			}
			else if(mouse.x >= SLOT_LEFT_MARGIN && mouse.x <= SLOT_LEFT_MARGIN + SLOT_SIZE && mouse.y >= BUILD_SLOTS_TOP_MARGIN + SLOT_SIZE + SLOT_TOP_MARGIN && mouse.y <= BUILD_SLOTS_TOP_MARGIN + 2 * SLOT_SIZE + SLOT_TOP_MARGIN){
				isBuilding = TRUE;
				currentBuilding = WIZARDTOWER;
			}
			else if(mouse.x >= SLOT_LEFT_MARGIN && mouse.x <= SLOT_LEFT_MARGIN + SLOT_SIZE && mouse.y >= BUILD_SLOTS_TOP_MARGIN + 2 * (SLOT_SIZE + SLOT_TOP_MARGIN) && mouse.y <= BUILD_SLOTS_TOP_MARGIN + 2 * (SLOT_SIZE + SLOT_TOP_MARGIN) + SLOT_SIZE) {
				isBuilding = TRUE;
				currentBuilding = WOODMANTOWER;
			}
			else{
				isBuilding = FALSE;
			}
		}
		else if(key.right == RELEASED)
			isBuilding = FALSE;
		
		// ZOOM
		if((tileSize < tileMaxSize && key.ctrl == TRUE && key.plus == TRUE) || key.scroll > 0){ 
			tileSize += 1;
			mapWidth = (int)(tileSize * MAP_WIDTH);
			mapHeight = (int)(tileSize * MAP_HEIGHT);

			map.width = mapWidth;
			map.height = mapHeight;

			key.scroll = 0;
		}
		if((tileSize > tileMinSize && key.ctrl == TRUE && key.minus == TRUE) || key.scroll < 0){ 
			tileSize -= 1;
			mapWidth = (int)(tileSize * MAP_WIDTH);
			mapHeight = (int)(tileSize * MAP_HEIGHT);
			
			map.width = mapWidth;
			map.height = mapHeight;

			key.scroll = 0;
		}

		// CAMERA MOVEMENT
		if(map.x < horMargin && key.a){
			map.x += tileSize + key.shift * tileSize * 3;
		}
		if((WINDOW_WIDTH - horMargin) < (map.x + map.width) && key.d){
			map.x -= tileSize + key.shift * tileSize * 3;
		}
		if((WINDOW_HEIGHT - verMargin) < (map.y + map.height) && key.s && !key.ctrl){
			map.y -= tileSize + key.shift * tileSize * 3;
		}
		if(map.y < verMargin && key.w){
			map.y += tileSize + key.shift * tileSize * 5;
		}
	}

	// PAUSE
	if(key.space == RELEASED)
		currentGameState = LOADSCREEN;
}

void render(){
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	if(currentGameState == LOADSCREEN){
		SDL_Rect loadScreen2render = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

		SDL_RenderCopy(renderer, TEXTURES_Texture_loadScreen, &_1725x1078, &loadScreen2render);

		SDL_SetRenderDrawColor(renderer, 40, 40, 40, 230);
		SDL_RenderFillRect(renderer, &loadScreen2render);

		SDL_Rect load2render = {(int)(WINDOW_WIDTH / 2 - loadTextSurface->w / 2), (int)(WINDOW_HEIGHT / 2 - loadTextSurface->h / 2), loadTextSurface->w, loadTextSurface->h};
		SDL_RenderCopy(renderer, loadTextTexture, NULL, &load2render);
	}

	if(currentGameState == GAME){		
		// MAP
		SDL_Rect map2render = {
			(int)map.x,
			(int)map.y,
			(int)map.width,
			(int)map.height
		};
		
		SDL_Rect b = {0,0,192,108};

		SDL_RenderCopy(renderer, TEXTURES_Texture_Map, &b, &map2render);

		// BUILDING SCRATCH
		if(buildingScratch.visible){
			SDL_Rect buildingScratch2render = {
				(int)((buildingScratch.x) * tileSize + map.x - buildingScratch.width * tileSize * .5),
				(int)((buildingScratch.y) * tileSize + map.y - buildingScratch.height * tileSize * .5),
				(int)(buildingScratch.width * tileSize),
				(int)(buildingScratch.height * tileSize)
			};

			SDL_SetRenderDrawColor(renderer, 150, 150, 150, 100);
			if(buildingScratch.isOnAnotherBuild || buildingScratch.isOutside || !buildingScratch.enoughMoney)
				SDL_SetRenderDrawColor(renderer, 250, 0, 0, 100);
			SDL_RenderFillRect(renderer, &buildingScratch2render);
		}

		// WOODMAN
		for(size_t i = 0; i < sizeof(woodMans) / sizeof(woodMans[0]); i++){
			if(woodMans[i].reserve != TRUE) continue;
			SDL_Rect woodMan2render = {
				(int)((woodMans[i].x - .5) * tileSize + map.x),
				(int)((woodMans[i].y - .5) * tileSize + map.y),
				(int)(tileSize),
				(int)(tileSize)
			};
			SDL_RenderCopy(renderer, TEXTURES_Texture_woodMan, &_256x256, &woodMan2render);
		}
		
		// BUILDS
		for(size_t i = 0; i < sizeof(builds) / sizeof(builds[0]); i++){
			if(builds[i].reserve != TRUE) continue;

			SDL_Rect build2render = {
				(int)((builds[i].x) * tileSize + map.x - builds[i].width * tileSize * .5),
				(int)((builds[i].y) * tileSize + map.y - builds[i].height * tileSize * .5),
				(int)(builds[i].width * tileSize),
				(int)(builds[i].height * tileSize)};
			
			if(builds[i].type == ARCHERTOWER) TEXTURES_Texture_allPropBuild = TEXTURES_Texture_archerTower;
			if(builds[i].type == WIZARDTOWER) TEXTURES_Texture_allPropBuild = TEXTURES_Texture_wizardTower;
			if(builds[i].type == WOODMANTOWER) TEXTURES_Texture_allPropBuild = TEXTURES_Texture_woodManTower;
			
			if(builds[i].isHover){
				if(builds[i].range > 0){
					SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
					drawCircle(renderer, (int)(builds[i].x* tileSize) + map.x, (int)(builds[i].y * tileSize) + map.y, builds[i].range * tileSize, (int)(tileSize / 8));
				}
				showHealthBar(builds[i]);

				SDL_SetTextureAlphaMod(TEXTURES_Texture_allPropBuild, 200);

				showSellText(builds[i]);
			}
			else{
				SDL_SetTextureAlphaMod(TEXTURES_Texture_allPropBuild, 255);
			}

			SDL_RenderCopy(renderer, TEXTURES_Texture_allPropBuild, &_256x256, &build2render);
		}

		// ENEMIES
		for(size_t i = 0; i < sizeof(enemies) / sizeof(enemies[0]); i++){
			if(enemies[i].reserve != TRUE) continue;
			SDL_Rect enemy2render = {
				(int)((enemies[i].x) * tileSize + map.x),
				(int)((enemies[i].y) * tileSize + map.y),
				(int)(tileSize),
				(int)(tileSize)
			};

			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderFillRect(renderer, &enemy2render);
		}

		// TREES
		for(size_t i = 0; i < sizeof(trees) / sizeof(trees[0]); i++){
			if(trees[i].reserve != TRUE) continue;
			SDL_Rect tree2render = {
				(int)((trees[i].x) * tileSize + map.x - trees[i].width * tileSize * .5),
				(int)((trees[i].y) * tileSize + map.y - trees[i].height * tileSize * .5),
				(int)(trees[i].width * tileSize),
				(int)(trees[i].height * tileSize)};

			SDL_RenderCopy(renderer, TEXTURES_Texture_tree, &_256x256, &tree2render);
		}
		
		// ARROWS
		for(size_t i = 0; i < sizeof(arrows) / sizeof(arrows[0]); i++){
			if(arrows[i].reserve){
				SDL_Rect arrow2render = {
				(int)((arrows[i].x) * tileSize + map.x),
				(int)((arrows[i].y) * tileSize + map.y),
				(int)(tileSize),
				(int)(tileSize)};

				SDL_Point center = { arrow2render.w / 2, arrow2render.h / 2 };

				SDL_RenderCopyEx(renderer, TEXTURES_Texture_arrow, &_256x256, &arrow2render, arrows[i].angle, &center, SDL_FLIP_NONE);
			}
		}

		// MAGIC
		for(size_t i = 0; i < sizeof(magics) / sizeof(magics[0]); i++){
			if(magics[i].reserve){
				SDL_Rect magic2render = {
				(int)((magics[i].x) * tileSize + map.x),
				(int)((magics[i].y) * tileSize + map.y),
				(int)(tileSize),
				(int)(tileSize)};

				SDL_RenderCopy(renderer, TEXTURES_Texture_magic, &_256x256, &magic2render);
			}
		}

		// DAY / NIGHT
		SDL_Rect dayNight2render = {
			(int)(map.x),
			(int)(map.y),
			(int)(map.x + map.width * tileSize),
			(int)(map.y + map.height * tileSize)
		};
		
		if(currentDayState == NIGHT){
			if(lightLevel > 255 - NIGHT_DARKNESS)
				lightLevel -= FADE_OUT_SPEED;
		}
		else
			if(lightLevel < 254)
				lightLevel += FADE_IN_SPEED;

	
		SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255 - (int)lightLevel);
		SDL_RenderFillRect(renderer, &dayNight2render);

		// PANEL
		SDL_Rect panel2render = {0, 0, (int)(WINDOW_WIDTH * PANEL_WIDTH), WINDOW_HEIGHT};
		SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
		SDL_RenderFillRect(renderer, &panel2render);
		
		// MONEY
		SDL_Rect money2render = {100 - moneyTextSurface->w / 2, 100 - moneyTextSurface->h / 2, moneyTextSurface->w, moneyTextSurface->h};
		SDL_RenderCopy(renderer, moneyTextTexture, NULL, &money2render);
		
		// CLOCK
		SDL_Rect clock2render = {100 - clockTextSurface->w / 2, 140 - clockTextSurface->h / 2, clockTextSurface->w, clockTextSurface->h};
		SDL_RenderCopy(renderer, clockTextTexture, NULL, &clock2render);
		
		// DAY
		SDL_Rect day2render = {100 - dayTextSurface->w / 2, 180 - dayTextSurface->h / 2, dayTextSurface->w, dayTextSurface->h};
		SDL_RenderCopy(renderer, dayTextTexture, NULL, &day2render);

		// COORDINATES
		SDL_Rect coordinates2render = {100 - coordinatesTextSurface->w / 2, 220 - coordinatesTextSurface->h / 2, coordinatesTextSurface->w, coordinatesTextSurface->h};
		SDL_RenderCopy(renderer, coordinatesTextTexture, NULL, &coordinates2render);
		
		// BUILDINGS
		if(currentBuilding == ARCHERTOWER) TEXTURES_Texture_allPropBuild = TEXTURES_Texture_archerTower;
		if(currentBuilding == WIZARDTOWER) TEXTURES_Texture_allPropBuild = TEXTURES_Texture_wizardTower;
		if(currentBuilding == WOODMANTOWER) TEXTURES_Texture_allPropBuild = TEXTURES_Texture_woodManTower;
			
		SDL_SetTextureAlphaMod(TEXTURES_Texture_archerTower, 150);
		SDL_SetTextureAlphaMod(TEXTURES_Texture_wizardTower, 150);
		SDL_SetTextureAlphaMod(TEXTURES_Texture_woodManTower, 150);
		SDL_SetTextureAlphaMod(TEXTURES_Texture_allPropBuild, 255);

		SDL_Rect buildSlot02render = {(int)(SLOT_LEFT_MARGIN), (int)(BUILD_SLOTS_TOP_MARGIN), (int)(SLOT_SIZE), (int)(SLOT_SIZE)};
		SDL_RenderCopy(renderer, TEXTURES_Texture_archerTower, &_256x256, &buildSlot02render);

		SDL_Rect archer2render = {SLOT_MID - archerTextSurface->w / 2, 1, archerTextSurface->w, archerTextSurface->h};
		archer2render.y = (int)(buildSlot02render.y + SLOT_SIZE);
		SDL_RenderCopy(renderer, archerTextTexture, NULL, &archer2render);
		
		SDL_Rect buildSlot12render = buildSlot02render;
		buildSlot12render.y += (int)(SLOT_SIZE + SLOT_TOP_MARGIN);
		SDL_RenderCopy(renderer, TEXTURES_Texture_wizardTower, &_256x256, &buildSlot12render);
		
		SDL_Rect wizard2render = {SLOT_MID - wizardTextSurface->w / 2, 1, wizardTextSurface->w, wizardTextSurface->h};
		wizard2render.y = (int)(buildSlot12render.y + SLOT_SIZE);
		SDL_RenderCopy(renderer, wizardTextTexture, NULL, &wizard2render);
		
		SDL_Rect buildSlot22render = buildSlot12render;
		buildSlot22render.y += (int)(SLOT_SIZE + SLOT_TOP_MARGIN);
		SDL_RenderCopy(renderer, TEXTURES_Texture_woodManTower, &_256x256, &buildSlot22render);
		
		SDL_Rect woodMan2render = {SLOT_MID - woodManTextSurface->w / 2, 1, woodManTextSurface->w, woodManTextSurface->h};
		woodMan2render.y = (int)(buildSlot22render.y + SLOT_SIZE);
		SDL_RenderCopy(renderer, woodManTextTexture, NULL, &woodMan2render);
	}

	SDL_RenderPresent(renderer);
}

void destroy_window(){
	TTF_CloseFont(font);
    TTF_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[]){
    game_is_running = initialize_window();
    
    setup();
    while (game_is_running) {
	    process_input();
	    update();
	    render();
	}

    destroy_window();

    return FALSE;
}
