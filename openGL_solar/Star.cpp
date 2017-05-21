#include "Star.h"



Star::Star()
{
	this->year = 0;
	this->day = 0;
}


Star::~Star()
{
}

void Star::set_text_buffer(GLUquadricObj * g_text)
{
	this->g_text = g_text;
}

void Star::set_texture(int texture)
{
	this->texture = texture;
}

int Star::get_texture()
{
	return this->texture;
}

void Star::set_sun_pos(float sun_pos[])
{
	memcpy(this->sun_pos, sun_pos, 3 * sizeof(sun_pos));
}

void Star::set_axis(float axis[])
{
	memcpy(this->axis, axis, 3 * sizeof(axis));
}

void Star::set_radius(float radius)
{
	this->radius = radius;
}

void Star::set_pos(float pos[])
{
	memcpy(this->pos, pos, 3 * sizeof(pos));
}

void Star::set_material(float specular[],float ambient_and_diffuse[],float shininess[],float color[]){
	memcpy(this->color, color, 3*sizeof(color));
	memcpy(this->shininess, shininess, sizeof(shininess));
	memcpy(this->amb_and_diff, ambient_and_diffuse, 4*sizeof(ambient_and_diffuse));
	memcpy(this->spec, specular, 4 * sizeof(specular));
}
void Star::draw(int mode,int id) {
	if (mode == 1)glPushName(id);
	glPushMatrix();
	apply_material();
	
	glTranslatef(sun_pos[0], sun_pos[1], sun_pos[2]);
	glRotatef(this->year,this->axis[0], this->axis[1], this->axis[2]);
	glTranslatef(-this->sun_pos[0],this->sun_pos[1],this->sun_pos[2]);
	
	glTranslatef(this->pos[0],this->pos[1],this->pos[2]);
	glRotatef(this->day, 0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, this->texture);
	
	gluSphere(this->g_text, this->radius, 20, 16);
	
	glPopMatrix();
}
void Star::apply_material() {

	glMaterialfv(GL_FRONT, GL_SPECULAR, this->spec);
	glMaterialfv(GL_FRONT, GL_SHININESS, this->shininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, this->amb_and_diff);
}