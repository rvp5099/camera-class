#pragma once
#include <vector>
using namespace std;

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

	//WPARAM wParam; 

	//void SetCamera(vector<float> cPosition, float horizontal, float vertical);
	//Setting the Camera consists of giving its position and angles that it is rotated in the x-z plane and in the y direction (horizontal and vertical).

	void RotateCamera(float angle);
	//Rotating the Camera is possible in both the horizontal and vertical directions, and the function takes these as parameters.

	//void SlideCamera(float slideX, float slideY, float slideZ);
	void MoveCamera(vector_t move);
	//SlideCamera can occur in both directions as well.

	//void MoveCamera(float distance);
	//Since moving the Camera occurs with all of the current angles and the distance in each direction can be calculated all we need is a distance forward or back at the current angle.

	void ZoomCamera(float zoom);

	void IdentityMatrix();

	//void CameraView(float zoom, float translateX, float translateY, float rotateX, float rotateY);
	void CameraView();

	float	m_fRotX;		// X Rotation in camera View
	float	m_fRotY;		// Y Rotation in camera View

	//float zoom;
	//float translateX;
	//float translateY;
	//float rotateX;
	//float rotateY;

	//void MouseMove(UINT nFlags, CPoint point, float zoom, float translateX, float translateY, float LastX, float LastY,  int diffX, int diffY, WPARAM wParam);

	void MouseZoomCamera(CPoint point);
	//mouse_controls mouse;

	void MouseMoveCamera(CPoint point);
	void MouseRotateCamera(CPoint point);

	//vector<float> cameraPosition;
	//vector<float> cameraTarget;
	//vector<float> cameraUpVector;

	//float radius;
	//float moveDist;

	//void cameraInit();
	//void set(float posX, float posY, float posZ,
	//	float lookX, float lookY, float lookZ,
	//	float upX, float upY, float upZ);
 
    //xyz getPos();
    //xyz getLook();
    //xyz getUp();
	
	//xyz pos;
    //xyz look;
	//xyz up;
	
	/* depth of field */
	//float focaldistance;
	//float aperturesize;
	//UINT blades;
	//float bladesrotation;
protected:

	float	m_fPosX;		// X position of the model in camera View
	float	m_fPosY;		// Y position of the model in camera View
	float	m_fZoom;		// Zoom on model in camera View

	float	m_fLastX;		// last known mouse X position
	float	m_fLastY;		// last known mouse Y position
	int diffX;
	int diffY;
	void NewPoint(CPoint point);


	DECLARE_MESSAGE_MAP()
};


