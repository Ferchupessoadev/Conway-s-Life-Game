#include <fstream>
#include <cinttypes>
#include <vector>
#include <string>
#include <cinttypes>

#include <gui.hpp>
#include <position.hpp>

Position setupPosition() 
{
  std::ifstream jsonFile {"./positions/random.json"};

  nlohmann::json jsonObject {nlohmann::json::parse(jsonFile)};

  Position currentGen {jsonObject[0]};

  return currentGen;
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
    virtual bool OnInit() {
        mainFrame *frame = new mainFrame("Conway");
        frame->Show(true);

        Position currentGen {setupPosition()};

        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
