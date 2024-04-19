#include <fstream>
#include <cinttypes>
#include <vector>
#include <cinttypes>
#include <memory>

#include <gui.hpp>
#include <position.hpp>

Position* setupPosition() 
{
  std::ifstream jsonFile {"./positions/random.json"};

  const nlohmann::json jsonObject {nlohmann::json::parse(jsonFile)};

  uint16_t maxWidth {};
  for (auto &&row : jsonObject[0])
    for (auto &&cell : row)
      maxWidth = maxWidth > row.size() ? maxWidth : row.size();

  return new Position(jsonObject[0]);
}

inline uint getCurrentTime()
{
  return 
  std::chrono::duration_cast<std::chrono::milliseconds>(
  std::chrono::system_clock::now().time_since_epoch()).count();
}

class MyApp : public wxApp 
{
public:
  virtual bool OnInit() 
  {
    MainFrame *frame = new MainFrame("Conway");
    frame->Show(true);

    Position* currentGen {setupPosition()};

    frame->getPosCanvas()->showPosition(currentGen);

    return true;
  }
};

wxIMPLEMENT_APP(MyApp);
