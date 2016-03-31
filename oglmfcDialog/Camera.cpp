// Camera.cpp : implementation file
//

#include "stdafx.h"
#include "oglmfcDialog.h"
#include "Camera.h"
#include <gl\GL.h>
#include <gl\GLU.h>

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
	m_fPosX  = 0.0f;
	m_fPosY  = 0.0f;
	m_fZoom  = 0.0f;
	m_fRotX  = 0.0f;
	m_fRotY  = 0.0f;
	diffX    = 0;
	diffY    = 0;
	m_fLastX = 0.0f;
	m_fLastY = 0.0f;
	m_RightDownPos.x = 0;
	m_RightDownPos.y = 0;
}

CCamera::~CCamera()
{
}

//void CCamera::SetCamera(vector<float> cPosition, float horizontal, float vertical)
//{
//
//}

void CCamera::RotateCamera(float angle)
{
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
}

void CCamera::MoveCamera(vector_t move)
{
	glTranslatef(move.x, move.y, 0.0f);
}

void CCamera::IdentityMatrix()
{
	glLoadIdentity();
}

//void CCamera::MoveCamera(float distance)
//{
//
//}

void CCamera::ZoomCamera(float zoom)
{
	glTranslatef(0.0f, 0.0f, -zoom);
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


