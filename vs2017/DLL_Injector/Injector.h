///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 16 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __injector__
#define __injector__

#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/statbmp.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/filepicker.h>
#include <wx/combobox.h>
#include <wx/statbox.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/statusbr.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MainWindow
///////////////////////////////////////////////////////////////////////////////
class MainWindow : public wxFrame 
{
	private:
		//**Extra methods
		void OnComboSel(wxCommandEvent& event);
		void OnSaveClick(wxCommandEvent& event);
		void OnLoadClick(wxCommandEvent& event);
		void OnExecuteClick(wxCommandEvent& event);
		//**End of Extra code
	protected:
		wxStaticBitmap* bitmap_viewer;
		wxStaticText* staticdll;
		wxFilePickerCtrl* InDllFile;
		wxStaticText* pidstatic;
		wxComboBox* procComboBox;
		wxStaticText* proctext;
		wxTextCtrl* titleppID;
		wxButton* load_button;
		wxButton* save_button;
		wxButton* exec_button;
		wxStatusBar* mainStatusBar;
	
	public:
		MainWindow( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Dll injector by bitware"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,344 ), long style = wxCLOSE_BOX|wxDEFAULT_FRAME_STYLE|wxICONIZE|wxMINIMIZE_BOX|wxTAB_TRAVERSAL );
		~MainWindow();

		//**Extra methods
		void DisableControls(void);
		void SetUpStatus(void);
		//**End of Extra code
};


#endif //__injector__


//Added Extra code