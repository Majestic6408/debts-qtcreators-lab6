#include "MainWindow.h"
#include "Bag.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Program 1 - Create Bag");
    resize(450, 300);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QFormLayout* formLayout = new QFormLayout();

    m_nameEdit = new QLineEdit();
    m_descEdit = new QLineEdit();
    m_slotsSpin = new QSpinBox();
    m_weightSpin = new QDoubleSpinBox();

    m_slotsSpin->setMinimum(1);
    m_slotsSpin->setMaximum(100);
    m_weightSpin->setMinimum(0.1);
    m_weightSpin->setMaximum(100.0);
    m_weightSpin->setSingleStep(0.5);

    formLayout->addRow("Name:", m_nameEdit);
    formLayout->addRow("Description:", m_descEdit);
    formLayout->addRow("Number of slots:", m_slotsSpin);
    formLayout->addRow("Max weight (kg):", m_weightSpin);

    mainLayout->addLayout(formLayout);

    QHBoxLayout* buttonLayout = new QHBoxLayout();

    QPushButton* loadBtn = new QPushButton("Load from .txt");
    QPushButton* saveBtn = new QPushButton("Save to JSON");
    QPushButton* clearBtn = new QPushButton("Clear");

    buttonLayout->addWidget(loadBtn);
    buttonLayout->addWidget(saveBtn);
    buttonLayout->addWidget(clearBtn);

    mainLayout->addLayout(buttonLayout);

    connect(loadBtn, &QPushButton::clicked, this, &MainWindow::onLoadFromTxt);
    connect(saveBtn, &QPushButton::clicked, this, &MainWindow::onSave);
    connect(clearBtn, &QPushButton::clicked, this, &MainWindow::onClear);
}

MainWindow::~MainWindow() {}

void MainWindow::onClear()
{
    m_nameEdit->clear();
    m_descEdit->clear();
    m_slotsSpin->setValue(0);
    m_weightSpin->setValue(0.0);
}

void MainWindow::onLoadFromTxt()
{
    QString filename = QFileDialog::getOpenFileName(this, "Select .txt file", "", "Text files (*.txt)");

    if(filename.isEmpty()) return;

    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "Error", "Cannot open file!");
        return;
    }

    QTextStream in(&file);
    QString line = in.readLine();
    file.close();

    if(line.isEmpty())
    {
        QMessageBox::warning(this, "Error", "File is empty!");
        return;
    }

    QStringList parts = line.split("|");

    if(parts.size() < 4)
    {
        QMessageBox::warning(this, "Error", "Wrong format! Use: Name|Description|Slots|Weight");
        return;
    }

    m_nameEdit->setText(parts[0].trimmed());
    m_descEdit->setText(parts[1].trimmed());
    m_slotsSpin->setValue(parts[2].toInt());
    m_weightSpin->setValue(parts[3].toDouble());

    QMessageBox::information(this, "Success", "Data loaded from .txt file!");
}

void MainWindow::onSave()
{
    saveToJson();

    onClear();
}

void MainWindow::saveToJson()
{
    QFile file("bags.json");
    QJsonArray jsonArray;

    if(file.exists() && file.open(QIODevice::ReadOnly))
    {
        QByteArray data = file.readAll();
        file.close();

        QJsonDocument doc = QJsonDocument::fromJson(data);
        if(doc.isArray())
        {
            jsonArray = doc.array();
        }
    }

    Bag bag;
    bag.setName(m_nameEdit->text().trimmed());
    bag.setDescription(m_descEdit->text().trimmed());
    bag.setSlotCount(m_slotsSpin->value());
    bag.setMaxWeight(m_weightSpin->value());

    jsonArray.append(bag.toJson());

    if(file.open(QIODevice::WriteOnly))
    {
        QJsonDocument doc(jsonArray);
        file.write(doc.toJson());
        file.close();
    }
}
