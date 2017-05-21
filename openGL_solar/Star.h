#pragma once
#include <GL\glut.h>  


class Star
{
private:
	float spec[4];
	float amb_and_diff[4];
	float shininess[1];
	float color[3];
	bool is_planet;
	void apply_material();
	float pos[3];
	float sun_pos[3];
	float axis[3];
	float radius;
	int texture;
	GLUquadricObj* g_text;
public:
	float year;
	float day;
	Star();
	~Star();
	void set_text_buffer(GLUquadricObj* g_text);
	void set_texture(int texture);
	int get_texture();
	void set_sun_pos(float sun_pos[]);
	void set_axis(float axis[]);
	void set_radius(float radius);
	void set_pos(float pos[]);
	void set_material(float specular[], 
		float ambient_and_diffuse[], 
		float shininess[], 
		float color[]);
	void draw(int mode,int id);

};

