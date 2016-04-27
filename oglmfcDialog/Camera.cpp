// Camera.cpp : implementation file
//

#include "stdafx.h"
#include "oglmfcDialog.h"
#include "Camera.h"
#include <gl\GL.h>
#include <gl\GLU.h>

#include "include/glm/gtc/type_ptr.hpp"
#include "include/glm/gtc/matrix_transform.hpp"

// CCamera

IMPLEMENT_DYNAMIC(CCamera, CWnd)

//	const float CCamera::TO_RADS = 3.141592654 / 180.0; // The value of 1 degree in radians

/*
CCamera::CCamera(float thewindowWidth, float thewindowHeight)
{
	radius = 1;
	moveDist = 1;
}
*/
CCamera::CCamera()
{
	m_fPosX = 0.0f;		// X Translation in camera View
	m_fPosY = 0.0f;		// Y Translation in camera View
	m_fPosZ = 0.0f;		// Z Translation in camera view
	
	m_fRotX = 0.0f;		// X Rotation in camera View
	m_fRotY = 0.0f;		// Y Rotation in camera View
	m_fRotZ = 0.0f;		// Z Rotation in camera view
	
	m_fScaleX = 1.0f;		// X Scale in camera View
	m_fScaleY = 1.0f;		// Y Scale in camera View
	m_fScaleZ = 1.0f;		// Z Scale in camera view

	diffX    = 0;
	diffY    = 0;
	m_fLastX = 0.0f;
	m_fLastY = 0.0f;

	m_StartPos.x = 0;
	m_StartPos.y = 0;

	m_pProjMatrx = (const float*)glm::value_ptr(m_ProjMatrix);
	m_pViewMatrix = (const float*)glm::value_ptr(m_ViewMatrix);
}

CCamera::~CCamera()
{
}

//void CCamera::SetCamera(vector<float> cPosition, float horizontal, float vertical)
//{
//
//}


void CCamera::IdentityMatrix()
{
	glLoadIdentity();
	m_ViewMatrix = glm::mat4();
}

void CCamera::display()
{
	glMultMatrixf(m_pViewMatrix);
}

void CCamera::setPerspective(float fovy, float aspect, float zNear, float zFar)
{
	m_ProjMatrix = glm::perspective(fovy, aspect, zNear, zFar);
}

void CCamera::setMatrix()
{
	m_ViewMatrix = glm::scale(glm::mat4(), glm::vec3( m_fScaleX, m_fScaleY, m_fScaleZ));
	m_ViewMatrix = glm::translate(m_ViewMatrix, glm::vec3(m_fPosX, m_fPosY, m_fPosY));
	// construct the rotation positioning matrix
	m_ViewMatrix = glm::rotate(m_ViewMatrix, glm::radians( m_fRotX ), glm::vec3(1.0f, 0.0f, 0.0f));
	m_ViewMatrix = glm::rotate(m_ViewMatrix, glm::radians( m_fRotY ), glm::vec3(0.0f, 1.0f, 0.0f));
	m_ViewMatrix = glm::rotate(m_ViewMatrix, glm::radians( m_fRotZ ), glm::vec3(0.0f, 0.0f, 1.0f));	
}

void CCamera::CameraView()
{
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -m_fZoom);
	glTranslatef(m_fPosX, m_fPosY, 0.0f);
	glRotatef(m_fRotX, 1.0f, 0.0f, 0.0f);
	glRotatef(m_fRotY, 0.0f, 1.0f, 0.0f);
}



void CCamera::MouseZoomCamera(CPoint point)
{
	//NewPoint(point);
	//diffX = (int)(point.x - m_fLastX);
	//diffY = (int)(point.y - m_fLastY);
	//m_fLastX  = (float)point.x; 
	//m_fLastY  = (float)point.y;
	m_fZoom += 0.1f;
	
	TRACE("Zoom MOUSE: %f \n", m_fZoom);
}

void CCamera::MouseMoveCamera(CPoint point)
{
	// CLK III This is a very interesting problem

	// it looks like the last position move to move is not getting saved, or on the start of a new move
	// it tries to figure out the diff in the mouse positions. this creates a little number difference for the 
	// first move. which only gets worse as you move more and more. I wonder why this doesn't happen when you are
	// moving the camera in our software. we do the same thing as this. almost exactly. 


	// I'm still not entirely sure why this is happening. it would be ideal if we could get this to work in some other
	// way that is not based off the little jump from the start. I think the same 
	// thing was happening with the notes and I made it so that you couldn't move them
	// if you werent close enough to the note. perhaps you could make it such that the 
	// x, y positions are recorded regardless of what is happening.

	// this way when you start actually moving the mouse the default last position
	// is actually something that exists in the screen space.

	TRACE("point.x: %li \n", point.x);
	TRACE("point.y: %li \n", point.y);
	TRACE("mouse.m_fPosX: %f \n", m_fPosX);
	TRACE("mouse.m_fPosY: %f \n", m_fPosY);
	TRACE("Last X: %f \n", m_RightDownPos.x);
	TRACE("Last Y: %f \n", m_RightDownPos.x);
	//NewPoint(point);
	//TRACE("point.x: %li \n", point.x);
	//TRACE("point.y: %li \n", point.y);
	//m_fPosX += diffX * 0.01f;
	//m_fPosY -= diffY * 0.01f;
	
	m_fPosX -= (float)(m_RightDownPos.x - point.x) * 0.005f;
	m_fPosY += (float)(m_RightDownPos.y - point.y) * 0.005f;
	TRACE("mouse.m_fPosX: %f \n", m_fPosX);
	TRACE("mouse.m_fPosY: %f \n", m_fPosY);
	m_RightDownPos = point;
}


void CCamera::NewPoint(CPoint point)
{
	diffX = 0;
	diffY = 0;
	diffX = (int)(point.x - m_fLastX);
	diffY = (int)(point.y - m_fLastY);
	m_fLastX  = (float)point.x;
	m_fLastY  = (float)point.y;

	TRACE("\nX NewPoint: %li \n", point.x);
	TRACE("Y NewPoint: %li \n", point.y);
	TRACE("X diff NewPoint: %i \n", diffX);
	TRACE("Y diff NewPoint: %i \n", diffY);
	TRACE("X last NewPoint: %f \n", m_fLastX);
	TRACE("Y last NewPoint: %f \n", m_fLastY);
}

void CCamera::MouseRotateCamera(CPoint point)
{
	NewPoint(point);
	//mouse_controls mouse;

	//diffX = (int)(point.x - m_fLastX);
	//diffY = (int)(point.y - m_fLastY);
	//m_fLastX  = (float)point.x;
	//m_fLastY  = (float)point.y;

	m_fRotX += (float) 0.5f * diffY;

	if ((m_fRotX > 360.0f) || (m_fRotX < -360.0f))
	{
		m_fRotX = 0.0f;
	}

	m_fRotY += (float)0.5f * diffX;

	if((m_fRotY > 360.0f)||(m_fRotY < -360.0f))
	{
		m_fRotY = 0.0f;
	}
	
	TRACE("\nX rotation: %f \n", m_fRotX);
	TRACE("Y rotation: %f \n", m_fRotY);

	//return mouse;
}

BEGIN_MESSAGE_MAP(CCamera, CWnd)
END_MESSAGE_MAP()



// CCamera message handlers


