#pragma once
#include <string>
enum SOLAR {
	sun = 0,
	mercury,
	hesper,
	earth,
	mars,
	jupiter,
	saturn,
	uranus,
	neptune
};
std::string star_name[9] = {
	"sun",
	"mercury",
	"hesper",
	"earth",
	"mars",
	"jupiter",
	"saturn",
	"uranus",
	"neptune"
};

float month = 0;
float light_angle = 0;
float light_radius = 8.0;
double x = 0, y = 0;

float  axis[3] = { 0,0,15 };



float color[9][3] = {
	{ 1.0, 0.0, 0.0 },
	{ 1.0,1.0,0.2 },
	{ 0.1,0.2,0.6 },
	{ 1.0, 0.0, 0.0 },
	{ 1.0,0.1,0.0 },
	{ 0.8,0.7,0.0 },
	{ 0.6,0.6,0.0 },
	{ 0.3,0.3,0.7 },
	{ 0.0,0.1,1.0 } 
};

float spec_amb_diff[9][4] = {
	{ 1.0, 0.0, 0.0,1.0 } ,
	{ 1.0,1.0,0.2,1.0 } ,
	{ 0.1,0.2,0.6,1.0 } ,
	{ 1.0, 0.0, 0.0,1.0 } ,
	{ 1.0,0.1,0.0,1.0 } ,
	{ 0.8,0.7,0.0,1.0 } ,
	{ 0.6,0.6,0.0,1.0 } ,
	{ 0.3,0.3,0.7,1.0 } ,
	{ 0.0,0.1,1.0,1.0 }
};

float shininess[9][1] = {
	{ 100 } ,
	{ 100 } ,
	{ 100 } ,
	{ 100 } ,
	{ 100 } ,
	{ 100 } ,
	{ 100 } ,
	{ 100 } ,
	{ 100 } ,
};
float pos[9][3] = { 
	{ -15, 0, 0 } ,
	{ 0.5, 0, 0 } ,
	{ 4.0, 0, 0 } ,
	{ 9.0, 0, 0 } ,
	{ 14.0, 0, 0 } ,
	{ 17.0, 0, 0 } ,
	{ 20.0, 0, 0 } ,
	{ 24.0, 0, 0 } ,
	{ 30.0, 0, 0 } 
};

float radius[9] = { 10,1,0.5,1,1,2,1.5,2,1 };

float delta_day[9] = { 1, 1, 2, 1, 3, 5, 7, 6, 8 };

float delta_year[9] = { 0, 0.12, 0.1, 0.08, 0.06, 0.05, 0.04, 0.03, 0.01 };