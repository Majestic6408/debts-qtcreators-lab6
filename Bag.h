#ifndef BAG_H
#define BAG_H

#include <QString>
#include <QJsonObject>

class Bag
{
public:
    Bag();
    Bag(QString name, QString description, int slotCount, double maxWeight);

    QString getName();
    QString getDescription();
    int getSlotCount();
    double getMaxWeight();

    void setName(QString name);
    void setDescription(QString description);
    void setSlotCount(int slotCount);
    void setMaxWeight(double maxWeight);

    QJsonObject toJson();
    void fromJson(QJsonObject obj);

    bool isValid();

private:
    QString m_name;
    QString m_description;
    int m_slotCount;
    double m_maxWeight;
};

#endif
