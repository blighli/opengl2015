/************************************************************************/
/* time   : 2015-12-02                                                  */
/* author : 谭锦志                                                       */
/* email  : apanoo@126.com                                              */
/************************************************************************/

#define WIN32_LEAN_AND_MEAN
#include "Main.h"
#include "../GLWindow/Global.h"
#include "../GLWindow/QWndApp.h"

//link to libraries
//#pragma comment(lib, "opengl32.lib")
//#pragma comment(lib, "glu32.lib")
//#pragma comment(lib, "winmm.lib")

// WinMain 入口函数
int WINAPI _tWinMain(	HINSTANCE	hInstance,			//Instance
						HINSTANCE	hPrevInstance,		//Previous Instance
						LPSTR		lpCmdLine,			//Command line params
						int			nShowCmd)			//Window show state
{
	QWndApp *pWndApp = GlbGetApp();
	assert(pWndApp);

	pWndApp->InitInstance();
	pWndApp->run();
	pWndApp->ExitInstance();

	return true;
}
