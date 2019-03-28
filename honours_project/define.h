// SOC10101 - Honours Project (40 Credits)
// Snake Prototype 3
// Version 0.x.x
// Alexander Barker 
// 40333139
// Last Updated on 26th March 2019
// define.h - XXX.

// Window Configuragtion
#define W_WIDTH			1504
#define W_HEIGHT		846

// Sprite display size.
#define S_SIZE			32

// Game Configuration.
#define G_WIDTH			(3*W_WIDTH/(4*S_SIZE))
#define G_HEIGHT		(W_HEIGHT/S_SIZE)
#define SEED			time(NULL)			
#define NB_PLAYER1		1
#define NB_CRYSTAL1		1
#define NB_PLAYER10		10
#define NB_CRYSTAL10	2
#define NB_PLAYER50		50
#define NB_CRYSTAL50	3

// Maximum weight of a node, weight of snake body parts.
#define WEIGHT_REF		(G_WIDTH+G_HEIGHT)

// Snake Directions.
#define NONE			0
#define LEFT			-1
#define RIGHT			1
#define DOWN			-2
#define UP				2

// Controls.
#define M_ADD_OBS		Mouse::Left
#define M_DEL_OBS		Mouse::Right
#define K_PAUSE			Keyboard::Space
#define K_UP_FPS		Keyboard::M
#define K_DOWN_FPS		Keyboard::N
#define K_FPS_CAP		Keyboard::B
#define K_TOGGLE_BFS	Keyboard::V
#define K_SHOW_COST		Keyboard::C
#define K_SHOW_WEIGHT	Keyboard::X
#define K_SHOW_PATH		Keyboard::Z

// Resources.
#define FONT_TITLE		"res/fonts/RobotoMono-Regular.ttf"
#define FONT_SCORE		"res/fonts/RobotoMono-Regular.ttf"
#define T_SNAKE			"res/img/snakebody.png"
#define T_CRYSTAL		"res/img/snakefood.png"
#define TITLEIMG		"res/img/title.png"

// Tile size on the image.png.
#define T_SIZE			32