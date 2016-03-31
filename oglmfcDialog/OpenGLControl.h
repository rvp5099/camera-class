#pragma once
#include "afxwin.h"
#include "camera.h"
#include <gl\GL.h>
#include <gl\GLU.h>

class CCamera;

class COpenGLControl : public CWnd
{
public:
	COpenGLControl(void);
	virtual ~COpenGLControl(void);

	UINT_PTR m_unpTimer;  // Timer
	CWnd	*hWnd;
	HDC		hdc;
	HGLRC	hrc;
	int		m_nPixelFormat;
	CRect	m_rect;
	CRect	m_oldWindow;
	CRect	m_originalRect;

	float	m_fLastX;		// last known mouse X position
	float	m_fLastY;		// last known mouse Y position
	
	float	m_fPosX;		// X position of the model in camera View
	float	m_fPosY;		// Y position of the model in camera View
	float	m_fZoom;		// Zoom on model in camera View
	float	m_fRotX;		// X Rotation in camera View
	float	m_fRotY;		// Y Rotation in camera View

	float	pitchSensitivity;// Controls how sensitive mouse movements affect looking up and down
	float	yawSensitivity;// Controls how sensitive mouse movements affect looking left and right
	// Window size in pixels and where the midpoint of it falls
	int		windowWidth;
	int		windowHeight;
	int		windowMidX;
	int		windowMidY;

	BOOL	m_bIsMaximized;

	void    oglInitialize(void);
	void	oglDrawScene(void);
	void	oglCreate(CRect rect, CWnd *parent);
	
	//WPARAM wParam;
	//mouse_controls mouse;

	//cam_controls cam;
	CCamera cam;

	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDraw(CDC *pDC);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
};

