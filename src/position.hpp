#include <vector>
#include <cinttypes>

#include <nlohmann/json.hpp>

#pragma once

  class Position
{
public:
  using row_t = std::vector<uint8_t>;
  using data_t = std::vector<std::vector<uint8_t>>;

  Position():
    height {},
    width {},
    __data {}
  {};

  Position(nlohmann::json toCopy) :
    height {toCopy.size()},
    width {toCopy[0].size()},
    __data {toCopy.template get<data_t>()}
  {};

  Position(data_t toCopy) :
    height {toCopy.size()},
    width {toCopy[0].size()},
    __data {toCopy}
  {};

  const uint32_t countCells()
  {
    uint32_t cellsQuantity = 0;

    for (const row_t &row : __data)
      cellsQuantity += std::count(row.begin(), row.end(), true);

    return cellsQuantity;
  }

  void advanceGen() // pending refactoring
  {
    data_t nextGen;

    std::copy(__data.begin(), __data.end(), std::back_inserter(nextGen));

    for (uint32_t posY = 0; posY < height; posY++)
    {
      for (uint32_t posX = 0; posX < width; posX++)
      {
        if (!__data[posY][posX]) 
        continue;

        uint8_t sorroundingCells = 0;

        for (int32_t cellY = -1; cellY < 2; cellY++)
        {
          if (isOutOfBounds(posY + cellY, height))
          continue;

          for (int32_t cellX = -1; cellX < 2; cellX++)
          {
            if (isOutOfBounds(posX + cellX, width)) 
            continue;

            sorroundingCells += __data[posY + cellY][posX + cellX];

            if (__data[posY + cellY][posX + cellX])
            continue;

            uint8_t sorroundingDeadCell = 0;
            for (int8_t deadCellY = -1; deadCellY < 2; deadCellY++)
            {
              if (isOutOfBounds(posY + cellY + deadCellY, height)) 
              continue;

              for (int8_t deadCellX = -1; deadCellX < 2; deadCellX++)
              {
                if (isOutOfBounds(posX + cellX + deadCellX, width))
                continue;

                sorroundingDeadCell += 
                __data[posY + cellY + deadCellY][posX + cellX + deadCellX];
              }
            }

            if (sorroundingDeadCell == 3)
            {
              nextGen[posY + cellY][posX + cellX] = true;
            }
          }
        }

        if (sorroundingCells == 4)
        {
          nextGen[posY][posX] = true;
        }
        else if (sorroundingCells != 3)
        {
          nextGen[posY][posX] = false;
        }
      }
    }

  __data = nextGen;
  }

  const uint16_t getWidth()
  {
    return width;
  };

  const uint16_t getHeight()
  {
    return height;
  }

  const bool getCellAt(uint16_t coordX, uint16_t coordY)
  {
    return static_cast<bool>(__data[coordY][coordX]);
  };

private:
  const bool isOutOfBounds(const uint16_t cellCoord, const uint16_t maxCoord)
  {
    return cellCoord < 0 || cellCoord >= maxCoord;
  }

  const size_t width, height;

  data_t __data;  
};