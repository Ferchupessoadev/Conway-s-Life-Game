#include <algorithm>
#include <vector>

using position = std::vector<std::vector<uint8_t>>;

uint32_t countCells(position &toCount)
{
  uint32_t cellsQuantity = 0;

  for (std::vector<uint8_t> &row : toCount)
  {
    cellsQuantity += std::count(row.begin(), row.end(), true);
  }

  return cellsQuantity;
}

inline bool isOutOfBounds(const int32_t cellCoord, const uint32_t maxCoord)
{
  return cellCoord < 0 || cellCoord >= maxCoord;
}

 position advanceGen(const position &generation, const uint32_t width, 
const uint32_t height)
{
  position nextGen;

  std::copy(generation.begin(), generation.end(), std::back_inserter(nextGen));

  for (uint32_t posY = 0; posY < height; posY++)
  {
    for (uint32_t posX = 0; posX < width; posX++)
    {
      if (!generation[posY][posX]) 
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

          sorroundingCells += generation[posY + cellY][posX + cellX];

          if (generation[posY + cellY][posX + cellX])
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
              generation[posY + cellY + deadCellY][posX + cellX + deadCellX];
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

  return nextGen;
}