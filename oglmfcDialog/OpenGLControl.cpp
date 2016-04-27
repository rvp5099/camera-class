#include "stdafx.h"
#include "OpenGLControl.h"
#include "Camera.h"


float pitch = 0, roll = 0, heading = 0;
float posX = 0, posY = 0, posZ = 0;
//CCamera camera;

BEGIN_MESSAGE_MAP(COpenGLControl, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

COpenGLControl::COpenGLControl(void)
{
	//CCamera camera;
	m_fPosX  = 0.0f;
	m_fPosY  = 0.0f;
	m_fZoom  = 0.0f;
	m_fRotX  = 0.0f;
	m_fRotY  = 0.0f;
}

COpenGLControl::~COpenGLControl(void)
{
}

void COpenGLControl::oglCreate(CRect rect, CWnd *parent)
{
	CString	className = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_OWNDC, NULL,
		(HBRUSH)GetStockObject(BLACK_BRUSH), NULL);

	CString oglName = CString(_T("OpenGL"));

	CreateEx(0, className, oglName, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, rect, parent, 0);

	// Set initial variables values
	m_oldWindow		= rect;
	m_originalRect	= rect;

	hWnd = parent;
}

int COpenGLControl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	oglInitialize();

	return 0;
}

void COpenGLControl::oglInitialize(void)
{
	// Initial Setup
	//
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,		// bit depth
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		16, // z-buffer depth
		0, 0, 0, 0, 0, 0, 0
	};

	// Get device context only once.
	hdc = GetDC()->m_hDC;

	// Pixel format.
	m_nPixelFormat = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, m_nPixelFormat, &pfd);

	// Create the OpenGL Rendering Context.
	hrc = wglCreateContext(hdc);
	wglMakeCurrent(hdc, hrc);

	// Basic Setup:
	//
	// Set color to use when clearing the background.
	glClearColor(0.4f, 0.7f, 0.8f, 1.0f);
	glClearDepth(1.0f);


	glFrontFace(GL_CW);	// set the winding order to clockwise
	glCullFace(GL_BACK);	// Turn on backface culling

	//Turn on depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// Send draw request
	OnDraw(NULL);
}

void COpenGLControl::OnPaint()
{
	//CPaintDC dc(this);	//device context for painting
	ValidateRect(NULL);
}

void COpenGLControl::OnDraw(CDC *pDC)
{
	//CCamera camera;
	glLoadIdentity();
	//cam.IdentityMatrix();

	float ambient[]  = {0.2f, 0.2f, 0.2f, 1.0f};
	float diffuse[]  = {1.0f, 1.0f, 1.0f, 1.0f};
	float specular[] = {0.803f, 0.952f, 0.995f, 1.0f};
	float position[] = {20.0f, 20.0f, 10.0f, 1.0f};

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	glLoadIdentity();

	//camera control
	//cam_controls cam;
	//cam.m_fZoom = m_fZoom;
	//cam.m_fPosX = m_fPosX;
	//cam.m_fPosY = m_fPosY;
	cam.m_fRotX = m_fRotX;
	cam.m_fRotY = m_fRotY;
	cam.CameraView();
	//camera.RotateCamera(45.0f);
	//
	//glLoadIdentity();
	//glTranslatef(0.0f, 0.0f, -m_fZoom);
	//glTranslatef(m_fPosX, m_fPosY, 0.0f);
	//glRotatef(m_fRotX, 1.0f, 0.0f, 0.0f);
	//glRotatef(m_fRotY, 0.0f, 1.0f, 0.0f);
	/////////////////
}

void COpenGLControl::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case 1:
		{
			// Clear color and depth buffer bits
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Draw OpenGL Scene
			oglDrawScene();

			// Swap Buffers
			SwapBuffers(hdc);

			break;
		}
	default:
		break;
	}

	CWnd::OnTimer(nIDEvent);
}

void COpenGLControl::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	if ( 0 >= cx || 0 >= cy || nType == SIZE_MINIMIZED) 
		return;

	// Map the OpenGL coordinates.
	glViewport(0, 0, cx, cy);

	//Projection view
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	cam.setPerspective(35.0f, (float)cx / (float)cy, 0.01f, 2000.0f);

	//gluPerspective(35.0f, (float)cx / (float)cy, 0.01f, 2000.0f);
	glMultMatrixf(cam.m_pProjMatrx);

	// Model view
	glMatrixMode(GL_MODELVIEW);

}

void COpenGLControl::oglDrawScene(void)
{
	// Wireframe Mode
	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_FRONT, GL_FILL);

	// CLK III - I would call a routine to position the camera in the draw loop instead of relying on 
	// setting the matrix in the mouse controls

	glPushMatrix();
	cam.display();

	glBegin(GL_QUADS);
	glColor4ub( 000, 155, 255, 255);

	float objectLength = 4.0f;

	// Top Side
	glNormal3f(  0.0f,  1.0f,  0.0f);

	glVertex3f( -1*objectLength,  1.0f, -1.0f);
	glVertex3f( -1*objectLength,  1.0f,  1.0f);
	glVertex3f(  objectLength,  1.0f,  1.0f);
	glVertex3f(  objectLength,  1.0f, -1.0f);

	// Bottom Side
	glNormal3f(  0.0f, -1.0f,  0.0f);

	glVertex3f( -1*objectLength, -1.0f, -1.0f);
	glVertex3f(  objectLength, -1.0f, -1.0f);
	glVertex3f(  objectLength, -1.0f,  1.0f);
	glVertex3f( -1*objectLength, -1.0f,  1.0f);

	// Front Side
	glNormal3f(  0.0f,  0.0f,  1.0f);

	glVertex3f(  objectLength,  1.0f,  1.0f);
	glVertex3f( -1*objectLength,  1.0f,  1.0f);
	glVertex3f( -1*objectLength, -1.0f,  1.0f);
	glVertex3f(  objectLength, -1.0f,  1.0f);

	// Back Side
	glNormal3f(  0.0f,  0.0f, -1.0f);

	glVertex3f( -1*objectLength, -1.0f, -1.0f);
	glVertex3f( -1*objectLength,  1.0f, -1.0f);
	glVertex3f(  objectLength,  1.0f, -1.0f);
	glVertex3f(  objectLength, -1.0f, -1.0f);

	// Left Side
	glNormal3f( -1.0f,  0.0f,  0.0f);

	glVertex3f( -1*objectLength, -1.0f, -1.0f);
	glVertex3f( -1*objectLength, -1.0f,  1.0f);
	glVertex3f( -1*objectLength,  1.0f,  1.0f);
	glVertex3f( -1*objectLength,  1.0f, -1.0f);

	// Right Side
	glNormal3f(  1.0f,  0.0f,  0.0f);

	glVertex3f(  objectLength,  1.0f,  1.0f);
	glVertex3f(  objectLength, -1.0f,  1.0f);
	glVertex3f(  objectLength, -1.0f, -1.0f);
	glVertex3f(  objectLength,  1.0f, -1.0f);
	glEnd();

	glPopMatrix();
}

void COpenGLControl::OnMouseMove(UINT nFlags, CPoint point)
{
	float turnRate = 0.001f;

	int diffX = (int)(point.x - m_fLastX);
	int diffY = (int)(point.y - m_fLastY);
	m_fLastX  = (float)point.x;
	m_fLastY  = (float)point.y;
	
	// Left Mouse Button
	if (nFlags & MK_LBUTTON)
	{
		cam.MouseMoveCamera(point);	
	}
	// Middle Mouse Button
	else if ( nFlags & MK_MBUTTON)
	{
		cam.MouseRotateCamera(point);
		
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
		
	}
	// Right Mouse Button
	else if ( nFlags & MK_RBUTTON)
	{
		//camera.MouseMoveCamera(point);
		//m_fPosX += (float)0.05f * diffX;
		//m_fPosY -= (float)0.05f * diffY;
		//TRACE("\nX position: %f \n", m_fPosX);
		//TRACE("Y position: %f \n", m_fPosY);
	}
	else if (nFlags & MK_CONTROL)
	{
		cam.MouseZoomCamera(point);
	}

	cam.m_RightDownPos = point;
	OnDraw(NULL);

	CWnd::OnMouseMove(nFlags, point);
}