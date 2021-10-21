#include "framework.h"
#include "MainFrm.h"
#include "Handmade.h"
#include "HandmadeDoc.h"
#include "HandmadeView.h"

CHandmadeApp theApp;
//======================================================================================================
BEGIN_MESSAGE_MAP(CHandmadeApp, CWinApp)
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()
//======================================================================================================
CHandmadeApp::CHandmadeApp()
{
	m_nAppLook = 0;

	//TODO: replace application ID string below with unique ID string; recommended
	//format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("Handmade.AppID.NoVersion"));
}
//======================================================================================================
BOOL CHandmadeApp::InitInstance()
{
	CWinApp::InitInstance();

	if (!AfxOleInit())
	{
		return FALSE;
	}

	AfxEnableControlContainer();
	EnableTaskbarInteraction(FALSE);

	//TODO - Standard initialization
	//If you are not using these features and wish to reduce the size
	//of your final executable, you should remove from the following
	//the specific initialization routines you do not need
	//Change the registry key under which our settings are stored
	//You should modify this string to be something appropriate
	//such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)

	//TODO - Register the application's document templates. Document templates
	//serve as the connection between documents, frame windows and views
	CSingleDocTemplate* pDocTemplate;

	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CHandmadeDoc),
		RUNTIME_CLASS(CMainFrame),
		RUNTIME_CLASS(CHandmadeView));

	if (!pDocTemplate)
	{
		return FALSE;
	}

	AddDocTemplate(pDocTemplate);

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	//Dispatch commands specified on the command line. Will return FALSE if
	//app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
	{
		return FALSE;
	}

	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}
//======================================================================================================
int CHandmadeApp::ExitInstance()
{
	AfxOleTerm(FALSE);
	return CWinApp::ExitInstance();
}