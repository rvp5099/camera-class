#pragma once
#include <vector>
#include "include\glm\glm.hpp"

// CLK III you should never put using namespace std
// in an include file. it can bloat the entire standard library
// into your program regardless of if you are using it or not
// you should always namespace std::(function) when you can

// it helps to keep compile time short and file size small.

// CCamera
//struct xyz{
//    float x, y, z;
//};

typedef struct vector_s
{
	float x, y, z;
} vector_t;

//typedef struct vertex_s
//{
//	float x, y, z;
//	std::vector<vector_t> fNrmls; // dynamic array for storing face normals
//	vector_t vNrml;				  // static type to store this vertex's normal
//} vertex_t;

//typedef struct cam_controls
//{
//	
//} cam_controls;

typedef struct mouse_controls
{
	float m_fZoom, m_fPosX, m_fPosY, m_fRotX, m_fRotY, m_fLastX, m_fLastY;
	int diffX, diffY;
} mouse_controls;

class CCamera : public CWnd
{
	DECLARE_DYNAMIC(CCamera)

public:
	//CCamera(float windowWidth, float windowHeight);
	CCamera();
	virtual ~CCamera();

	void IdentityMatrix();
	void CameraView();

	//mouse_controls mouse;	
	void MouseZoomCamera(CPoint point);
	void MouseMoveCamera(CPoint point);
	void MouseRotateCamera(CPoint point);

	void setMatrix();				// builds a new matrix
	void SetPoint( CPoint point);	// sets current mouse position
	void setPerspective(float fovy, float aspect, float zNear, float zFar);

	void display();				// displays built view matrix
	void displayProjection();   // displays built projection matrix

protected:
	
	CPoint		m_MovePos;

	float	m_fPosX;		// X Translation in camera View
	float	m_fPosY;		// Y Translation in camera View
	float   m_fPosZ;		// Z Translation in camera view
	
	float	m_fRotX;		// X Rotation in camera View
	float	m_fRotY;		// Y Rotation in camera View
	float   m_fRotZ;		// Z Rotation in camera view

	const float		*m_pProjMatrx;
	const float		*m_pViewMatrix;
	glm::mat4		m_ProjMatrix;
	glm::mat4		m_ViewMatrix;

	DECLARE_MESSAGE_MAP()
};


