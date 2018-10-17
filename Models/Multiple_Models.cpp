#include "Multiple_Models.h"

Multiple_Models::Multiple_Models(std::string fileName, std::vector<Vector3> positions, float scale)
:   model(fileName, {0, 0, 0}, scale)
{
    m_positions = positions;
}
