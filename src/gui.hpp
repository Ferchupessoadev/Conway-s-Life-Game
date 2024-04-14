#include <wx/wx.h>
#include <position.hpp>

class mainFrame : public wxFrame 
{
public:
  mainFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(1000, 700)) 
  {
  };
  
  wxDECLARE_EVENT_TABLE();

};

wxBEGIN_EVENT_TABLE(mainFrame, wxFrame)
wxEND_EVENT_TABLE()
