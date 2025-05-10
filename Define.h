#ifndef _DEFINE_H_
#define _DEFINE_H_

#define	RES_X			352
#define	RES_Y			240
#define COLOR_BLACK		0
#define COLOR_WHITE		255
#define INTENSITY_WHITE 0
#define INTENSITY_GRAY  1
#define INTENSITY_BLACK 2
/*
#define TEMPLATE_WIDTH 8
#define TEMPLATE_HEIGHT 8
*/
#define TEMPLATE_SIZE_MAX	16
#define FRAME_NUMBER_MAX	1200	// FRAME_NUMBER_MAX x PARTICLE_NUMBER_MAX <= 24000
#define PARTICLE_NUMBER_MAX 10
#define	ROD_LENGTH_MAX		150
#define PI					3.141592
#define TYPE_ROD_CARGO		0
#define TYPE_ROD			1
#define TYPE_SPHERE			2
#define SAVE_ALL_W_MP		0
#define SAVE_ALL_WO_MP		1
#define SAVE_DIST			2
#define EXCLUDED_AREAS_MAX	10
#define PARTICLE_DIST_MAX	2.0		// 0.5
#define PIXEL_X				0.279	// um
#define PIXEL_Y				0.303	// um

struct PARTICLE{
	float x;
	float y;
	float angle;
	float i_ratio;
//	short black;
//	short white;
	short pixel;
	short id;
};

struct FPOINT{		// Point structure with float type members
	float x;
	float y;
};

struct INERTIA{		
	float angle;
	float i_ratio;	// I2 / I1
};

#endif