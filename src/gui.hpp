#include <wx/wx.h>
#include <position.hpp>

class PosCanvas : public wxPanel
{
public:
  PosCanvas(wxWindow *parent) :
    wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(500, 300))
   {
    SetBackgroundColour(wxColour(0, 0, 0));
   }

   void showPosition(Position *toShow)
   {
    position_ptr = toShow;
    Refresh();
   }

   void onPaint(wxPaintEvent &event)
   {
    wxClientDC dc {this};
    dc.SetPen(*wxWHITE_PEN);

    for (uint16_t y = 0; y < position_ptr->getHeight(); y++)
    { 
      for (size_t x = 0; x < position_ptr->getWidth(); x++)
      {
        if (position_ptr->getCellAt(x, y))
        {
          dc.DrawRectangle(x * 10, y * 10, 10, 10);
        }
      }
    }
   }

  wxDECLARE_EVENT_TABLE();

private:
  Position* position_ptr;
};

class MainFrame : public wxFrame 
{
public:
  MainFrame(const wxString& title) : 
    wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(1000, 700)),
    positionCanvas {this}
  {}
  
  PosCanvas *getPosCanvas()
  {
    return &positionCanvas;
  };

private:
  PosCanvas positionCanvas;
};

wxBEGIN_EVENT_TABLE(PosCanvas, wxPanel)
  EVT_PAINT(PosCanvas::onPaint)
wxEND_EVENT_TABLE()
