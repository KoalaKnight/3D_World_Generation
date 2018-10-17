#ifndef MULTIPLE_MODELS_H_INCLUDED
#define MULTIPLE_MODELS_H_INCLUDED

#include <vector>
#include <string>

#include "Model.h"

class Multiple_Models
{
public:
    Multiple_Models(std::string fileName, std::vector<Vector3> positions, float scale);

    std::vector<Vector3> m_positions;
    Model model;
};

#endif // MULTIPLE_MODELS_H_INCLUDED
