#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSave();
    void onLoadFromTxt();
    void onClear();

private:
    void saveToJson();

    QLineEdit* m_nameEdit;
    QLineEdit* m_descEdit;
    QSpinBox* m_slotsSpin;
    QDoubleSpinBox* m_weightSpin;
};

#endif
