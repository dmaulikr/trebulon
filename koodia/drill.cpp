#include "game.hpp"
#include "drill.hpp"
#include "water.hpp"
#include "datastorage.hpp"

Drill::Drill(sf::Vector2f coords)
{
    position = coords;
    sprite = game.getDataStorage()->getSprite("drill");
    installTime = game.getTime();
    waterHarvested = 0;
    transferRate = 5;
    waterDeposit = nullptr;
    radius = 300.0;
}

Drill::~Drill()
{
}

void Drill::update()
{
    if (waterDeposit != nullptr && waterDeposit->getSize() > 0)
        sprite = game.getDataStorage()->getSprite("drill_active");
    else
        sprite = game.getDataStorage()->getSprite("drill");

    if (waterDeposit != nullptr)
    {
        waterHarvested += waterDeposit->giveWater(transferRate);
    }
}

void Drill::render()
{
    sprite->setPosition(position.x, position.y);
    game.getRenderWindow()->draw((*sprite));
}

long Drill::getInstallTime()
{
    return installTime;
}

long Drill::transferWater()
{
    if (waterHarvested > transferRate)
    {
        waterHarvested -= transferRate;
        return transferRate;
    }
    else
    {
        long out = waterHarvested;
        waterHarvested = 0;
        return out;
    }
}

void Drill::setWater(std::shared_ptr<Water> w)
{
    waterDeposit = w;
}

float Drill::getRadius()
{
    return radius;
}
