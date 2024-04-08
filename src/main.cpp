#include <iostream>
#include <fstream>
#include <cinttypes>
#include <memory>
#include <vector>
#include <algorithm>
#include <string>
#include <thread>
#include <cinttypes>

#include <nlohmann/json.hpp>

#include <logic.hpp>
#include <gui.hpp>

using position = std::vector<std::vector<uint8_t>>;

position setupPosition() 
{
  nlohmann::json jsonObject{
      nlohmann::json::parse(std::ifstream("/home/carmelo/Escritorio/C++/Conway-s-Life-Game/positions/random.json"))
  };
  // use absolute path for debuging, I don't understand why 
  // it gives a "file not found" error when executing

  position currentGen = jsonObject[0].template get<position>();

  uint16_t maxSize = jsonObject[0].size();
  for (nlohmann::json &row : jsonObject[0])
  {
    uint16_t rowSize = jsonObject[0].size();
    maxSize = rowSize > maxSize ? rowSize : maxSize;
  }

  for (std::vector<uint8_t> &row : currentGen)
  {
    row.reserve(maxSize);
  }

  currentGen.shrink_to_fit();

  return currentGen;
}

std::string posToString(const position &toPrint, const uint16_t width, 
const uint16_t height)
{
  std::string posString = "";

  for (uint16_t i = 0; i < height; i++)
  {
    for (uint16_t j = 0; j < width; j++)
    {
      posString += toPrint[i][j] ? " #" : " -"; 
    }

    posString += "\n";
  }

  return posString;
} 


inline uint getCurrentTime()
{
  return 
  std::chrono::duration_cast<std::chrono::milliseconds>(
  std::chrono::system_clock::now().time_since_epoch()).count();
}

nt main() 
{

  position currentGen;

  currentGen = setupPosition();

  const uint16_t height = currentGen.size();
  const uint16_t width = currentGen[0].size();

  size_t genCount = 1;

  std::cout << posToString(currentGen, width, height) << "\n"
  << "Generation 0\n"
  << "there are " << countCells(currentGen) << " live cells\n\n";

  std::cin.get();

  for (size_t i = 0; i < 1000; i++)
  {
    system("clear");

    uint startTime = getCurrentTime();

    currentGen = advanceGen(currentGen, width, height);

    std::cout << posToString(currentGen, width, height) << "\n"
    << "Generation " << genCount << "\n"
    << "there are " << countCells(currentGen) << " live cells\n\n";

    genCount++;

    startTime = getCurrentTime() - startTime;

    if (50 - startTime > 0)
    std::this_thread::sleep_for(static_cast<std::chrono::milliseconds>(50 - startTime));
  }

  return 0;
}


