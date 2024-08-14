///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 16 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "Injector.h"

///////////////////////////////////////////////////////////////////////////

MainWindow::MainWindow(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
	this->SetBackgroundColour(wxColour(60, 60, 60));
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* mainbSizer;
	mainbSizer = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* iconbSize;
	iconbSize = new wxBoxSizer(wxVERTICAL);

	bitmap_viewer = new wxStaticBitmap(this, wxID_ANY, wxBitmap(wxT("RC_ICON"), wxBITMAP_TYPE_RESOURCE), wxDefaultPosition, wxSize(480, 100), 0);
	iconbSize->Add(bitmap_viewer, 0, wxALL | wxEXPAND | wxALIGN_CENTER_HORIZONTAL, 5);

	mainbSizer->Add(iconbSize, 1, wxRIGHT | wxLEFT | wxEXPAND, 5);

	wxStaticBoxSizer* input;
	input = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, wxT("Input")), wxVERTICAL);

	wxBoxSizer* dll;
	dll = new wxBoxSizer(wxHORIZONTAL);

	staticdll = new wxStaticText(this, wxID_ANY, wxT("Choose  a dll to inject:  "), wxDefaultPosition, wxDefaultSize, 0);
	staticdll->Wrap(-1);
	staticdll->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHTTEXT));
	dll->Add(staticdll, 0, wxTOP | wxRIGHT | wxLEFT, 5);

	InDllFile = new wxFilePickerCtrl(this, wxID_ANY, wxEmptyString, wxT("Choose a file to inject"), wxT("*.*"), wxPoint(-1, -1), wxSize(-1, -1), wxFLP_DEFAULT_STYLE);
	dll->Add(InDllFile, 1, wxALIGN_RIGHT, 5);

	input->Add(dll, 0, wxEXPAND, 5);

	wxBoxSizer* selectproccombo;
	selectproccombo = new wxBoxSizer(wxHORIZONTAL);

	pidstatic = new wxStaticText(this, wxID_ANY, wxT("Select process with:      "), wxDefaultPosition, wxDefaultSize, 0);
	pidstatic->Wrap(-1);
	pidstatic->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHTTEXT));
	selectproccombo->Add(pidstatic, 0, wxTOP | wxRIGHT | wxLEFT, 5);

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer(wxVERTICAL);

	procComboBox = new wxComboBox(this, wxID_ANY, wxT("Select an option."), wxDefaultPosition, wxDefaultSize, 0, NULL, 0);
	procComboBox->Append(wxT("Select from PID"));
	procComboBox->Append(wxT("Select from window title"));
	bSizer5->Add(procComboBox, 0, wxALIGN_BOTTOM | wxEXPAND, 5);

	selectproccombo->Add(bSizer5, 1, wxEXPAND, 5);

	input->Add(selectproccombo, 0, wxEXPAND | wxTOP, 5);

	mainbSizer->Add(input, 0, wxALL | wxEXPAND, 5);

	wxStaticBoxSizer* proc;
	proc = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, wxT("Process")), wxVERTICAL);

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer(wxHORIZONTAL);

	proctext = new wxStaticText(this, wxID_ANY, wxT("Enter the PID/Window title of the process:"), wxDefaultPosition, wxDefaultSize, 0);
	proctext->Wrap(-1);
	proctext->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHTTEXT));
	bSizer7->Add(proctext, 0, wxTOP | wxRIGHT | wxLEFT, 5);

	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer(wxVERTICAL);

	titleppID = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer8->Add(titleppID, 1, wxLEFT | wxALIGN_CENTER_VERTICAL | wxEXPAND, 5);

	bSizer7->Add(bSizer8, 1, wxEXPAND, 5);

	proc->Add(bSizer7, 1, wxEXPAND, 5);

	mainbSizer->Add(proc, 0, wxEXPAND | wxALL, 5);

	wxStaticBoxSizer* execsbSizer;
	execsbSizer = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, wxT("Load/Execute")), wxHORIZONTAL);

	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer(wxVERTICAL);

	load_button = new wxButton(this, wxID_ANY, wxT("Load From File"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer9->Add(load_button, 0, wxALIGN_CENTER_VERTICAL | wxEXPAND, 5);

	execsbSizer->Add(bSizer9, 1, wxRIGHT | wxLEFT, 5);

	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer(wxVERTICAL);

	save_button = new wxButton(this, wxID_ANY, wxT("Save to File"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer12->Add(save_button, 0, wxALIGN_CENTER_VERTICAL | wxEXPAND, 5);

	execsbSizer->Add(bSizer12, 1, wxRIGHT | wxLEFT, 5);

	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer(wxVERTICAL);

	exec_button = new wxButton(this, wxID_ANY, wxT("Execute/Inject"), wxDefaultPosition, wxDefaultSize, 0);
	exec_button->SetBackgroundColour(wxColour(0, 255, 0));
	bSizer13->Add(exec_button, 0, wxALIGN_CENTER_VERTICAL | wxEXPAND, 5);

	execsbSizer->Add(bSizer13, 1, wxRIGHT | wxLEFT, 5);

	mainbSizer->Add(execsbSizer, 0, wxEXPAND | wxALL, 5);

	this->SetSizer(mainbSizer);
	this->Layout();
	mainStatusBar = this->CreateStatusBar(1, wxST_SIZEGRIP, wxID_ANY);
	mainStatusBar->SetBackgroundColour(wxColour(145, 200, 200));
	mainStatusBar->SetStatusText(wxT("[*] Ready "));
	//*********Extra code for event handling
	procComboBox->Bind(wxEVT_COMBOBOX, &MainWindow::OnComboSel, this);
	load_button->Bind(wxEVT_BUTTON, &MainWindow::OnLoadClick, this);
	save_button->Bind(wxEVT_BUTTON, &MainWindow::OnSaveClick, this);
	exec_button->Bind(wxEVT_BUTTON, &MainWindow::OnExecuteClick, this);

	wxIconBundle icons;
	icons.AddIcon(wxICON(ID_ICON));
	wxIcon icon = icons.GetIcon(wxSize(16, 16)); // Get a 16x16 icon
	this->SetIcon(icon);
	//*********End of extra code
}

MainWindow::~MainWindow()
{
}
