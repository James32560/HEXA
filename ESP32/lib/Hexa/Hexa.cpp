#include "Hexa.h"

Hexa::Hexa() {}

void Hexa::begin()
{
    pca1.begin(), pca2.begin();
    pca1.setPWMFreq(50), pca2.setPWMFreq(50);

    for(int i = 0;i < 6;i++) legs[i].setdPosition({0, 0, 0});
}

void Hexa::gaitGenerate()
{
    if(gait == "Stance")
    {
        for(int i = 0;i < 6;i++) legs[i].setdPosition({0, 0, 0});
    }
    else if(gait == "Tripod")
    {
        this->gaitOffset = {0, 0.5, 0, 0.5, 0, 0.5};
        this->stancePropotion = 0.5;
    }

    float propotion = timer / duration;
    for(int i = 0;i < 6;i++)
    {
        legs[i].setdPosition(gaitFormula(propotion + gaitOffset[i]));
    }
}

std::vector<float> Hexa::gaitFormula(float timePropotion)
{
    timePropotion = timePropotion > 1 ? timePropotion - 1 : timePropotion;

    // stright
    float x = 0, y = 0, z = 0;
    if(timePropotion <= stancePropotion / 2)
    {
        y = -sin(timePropotion * PI / stancePropotion);
    }
    else if(timePropotion <= (2 - stancePropotion) / 2)
    {
        y = sin((timePropotion - 0.5) * PI / (1 - stancePropotion));
        z = sin((timePropotion - (stancePropotion / 2)) * PI / (1 - stancePropotion));
    }
    else if(timePropotion <= 1)
    {
        y = sin((timePropotion + stancePropotion - 1) * PI / stancePropotion);
    }

    // rotate
    float rx = 0, ry = 0;

    return std::vector<float> {x, y * this->width, z * this->height};
}