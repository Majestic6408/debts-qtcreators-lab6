#include "Bag.h"

Bag::Bag()
{
    m_name = "";
    m_description = "";
    m_slotCount = 0;
    m_maxWeight = 0.0;
}

Bag::Bag(QString name, QString description, int slotCount, double maxWeight)
{
    m_name = name;
    m_description = description;
    m_slotCount = slotCount;
    m_maxWeight = maxWeight;
}

QString Bag::getName()
{
    return m_name;
}

QString Bag::getDescription()
{
    return m_description;
}

int Bag::getSlotCount()
{
    return m_slotCount;
}

double Bag::getMaxWeight()
{
    return m_maxWeight;
}

void Bag::setName(QString name)
{
    m_name = name;
}

void Bag::setDescription(QString description)
{
    m_description = description;
}

void Bag::setSlotCount(int slotCount)
{
    m_slotCount = slotCount;
}

void Bag::setMaxWeight(double maxWeight)
{
    m_maxWeight = maxWeight;
}

QJsonObject Bag::toJson()
{
    QJsonObject obj;
    obj["name"] = m_name;
    obj["description"] = m_description;
    obj["slotCount"] = m_slotCount;
    obj["maxWeight"] = m_maxWeight;
    return obj;
}

void Bag::fromJson(QJsonObject obj)
{
    m_name = obj["name"].toString();
    m_description = obj["description"].toString();
    m_slotCount = obj["slotCount"].toInt();
    m_maxWeight = obj["maxWeight"].toDouble();
}

bool Bag::isValid()
{
    if(m_name.isEmpty()) return false;
    if(m_description.isEmpty()) return false;
    if(m_slotCount <= 0) return false;
    if(m_maxWeight <= 0.0) return false;
    return true;
}
