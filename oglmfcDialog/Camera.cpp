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

CCamera::CCamera()
{
	m_fPosX = 0.0f;		// X Translation in camera View
	m_fPosY = 0.0f;		// Y Translation in camera View
	m_fPosZ = -10.0f;		// Z Translation in camera view
	
	m_fRotX = 0.0f;		// X Rotation in camera View
	m_fRotY = 0.0f;		// Y Rotation in camera View
	m_fRotZ = 0.0f;		// Z Rotation in camera view
	
	m_MovePos.x = 0;
	m_MovePos.y = 0;

	m_pProjMatrx = (const float*)glm::value_ptr(m_ProjMatrix);
	m_pViewMatrix = (const float*)glm::value_ptr(m_ViewMatrix);
}

CCamera::~CCamera()
{
}

void CCamera::IdentityMatrix()
{
	glLoadIdentity();
	m_ViewMatrix = glm::mat4();
}

void CCamera::display()
{
	glMatrixMode(GL_MODELVIEW);
	glMultMatrixf(m_pViewMatrix);
}

void CCamera::displayProjection()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMultMatrixf(m_pProjMatrx);
}

void CCamera::setPerspective(float fovy, float aspect, float zNear, float zFar)
{
	m_ProjMatrix = glm::perspective(fovy, aspect, zNear, zFar);
}

void CCamera::setMatrix()
{
	m_ViewMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, m_fPosZ));
	m_ViewMatrix = glm::translate(m_ViewMatrix, glm::vec3(m_fPosX, m_fPosY, 0.0f));
	// construct the rotation positioning matrix
	m_ViewMatrix = glm::rotate(m_ViewMatrix, glm::radians( m_fRotX ), glm::vec3(1.0f, 0.0f, 0.0f));
	m_ViewMatrix = glm::rotate(m_ViewMatrix, glm::radians( m_fRotY ), glm::vec3(0.0f, 1.0f, 0.0f));
	m_ViewMatrix = glm::rotate(m_ViewMatrix, glm::radians( m_fRotZ ), glm::vec3(0.0f, 0.0f, 1.0f));	
}

void CCamera::MouseZoomCamera(CPoint point)
{
	m_fPosZ -= 0.5;

	TRACE("Zoom MOUSE: %f \n", m_fPosZ);
	setMatrix();
}

void CCamera::MouseMoveCamera(CPoint point)
{

	TRACE("point.x: %li \n", point.x);
	TRACE("point.y: %li \n", point.y);
	TRACE("mouse.m_fPosX: %f \n", m_fPosX);
	TRACE("mouse.m_fPosY: %f \n", m_fPosY);
	TRACE("Last X: %f \n", m_MovePos.x);
	TRACE("Last Y: %f \n", m_MovePos.y);
	
	m_fPosX -= (float)(point.x - m_MovePos.x) * 0.005f;
	m_fPosY += (float)(point.y - m_MovePos.y) * 0.005f;
	TRACE("mouse.m_fPosX: %f \n", m_fPosX);
	TRACE("mouse.m_fPosY: %f \n", m_fPosY);
	m_MovePos = point;

	setMatrix();
}

void CCamera::MouseRotateCamera(CPoint point)
{
	
	m_fRotX += (float) 0.5f * (point.y - m_MovePos.y);

	if ((m_fRotX > 360.0f) || (m_fRotX < -360.0f))
	{
		m_fRotX = 0.0f;
	}

	m_fRotY += (float)0.5f * (point.x - m_MovePos.x);

	if((m_fRotY > 360.0f)||(m_fRotY < -360.0f))
	{
		m_fRotY = 0.0f;
	}
	m_MovePos = point;

	setMatrix();
}

void CCamera::SetPoint( CPoint point)
{
	m_MovePos = point;
}

BEGIN_MESSAGE_MAP(CCamera, CWnd)
END_MESSAGE_MAP()



// CCamera message handlers


