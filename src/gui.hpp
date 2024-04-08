#include <wx/wx.h>

using position = std::vector<std::vector<uint8_t>>;

class PositionCanvas : wxPanel 
{
  public:
  PositionCanvas(wxWindow* parent)
    : wxPanel(parent) 
    {
      this->drawPosition();
    };

  void drawPosition(const position &toDraw)
  {
    wxPaintDC dc {this};
    dc.SetBrush(*wxBLUE_BRUSH); 
    dc.SetPen(*wxBLACK_PEN);
    dc.DrawCircle(100, 100, 50);
  }
};

class mainFrame : public wxFrame 
{
public:
    mainFrame(const wxString& title)
        : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(250, 150)) 
      {
        PositionCanvas* canvas = new PositionCanvas(this);
      }
};

