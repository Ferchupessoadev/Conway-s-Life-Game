#include <wx/wx.h>
#include <vector>

using position = std::vector<std::vector<uint8_t>>;

class mainFrame : public wxFrame 
{
public:
  mainFrame(const wxString& title)
      : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(400, 400)) 
    {};
  
    void onPaint(wxPaintEvent &event)
    {
      wxClientDC dc {this};
      dc.SetBrush(*wxRED_BRUSH); 
      dc.SetPen(*wxRED_PEN);
      dc.SetBackground(*wxWHITE_BRUSH);
      dc.DrawCircle(100, 100, 100);
    }

    wxDECLARE_EVENT_TABLE();

};

wxBEGIN_EVENT_TABLE(mainFrame,wxFrame)
   EVT_PAINT(mainFrame::onPaint)
wxEND_EVENT_TABLE()
