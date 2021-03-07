#include "Projection.h"

Projection::Projection(float _aspect, float _fovy, float _zNear, float _zFar)
{
	aspect = _aspect;
	fovy = _fovy;
	zNear = _zNear;
	zFar = _zFar;
    projection = glm::perspective(fovy, aspect, zNear, zFar);
}

glm::mat4 Projection::getProjection()
{
	return projection;
}

void Projection::setProgection(float _aspect)
{
	aspect = _aspect;
	projection = glm::perspective(fovy, aspect, zNear, zFar);
}

void Projection::setProjection(float _aspect, float _fovy)
{
	fovy = _fovy;
	aspect = _aspect;
	projection = glm::perspective(fovy, aspect, zNear, zFar);
}

void Projection::setProjection(float _aspect, float _fovy, float _zNear, float _zFar)
{
	aspect = _aspect;
	fovy = _fovy;
	zNear = _zNear;
	zFar = _zFar;
	projection = glm::perspective(fovy, aspect, zNear, zFar);
}
