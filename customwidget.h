#pragma once

#include <QDebug>
#include <QMetaEnum>
#include <QTranslator>
#include <QVariant>
#include <QWidget>
#include <QTranslator>

QT_BEGIN_NAMESPACE
namespace Ui { class CustomWidget; }
QT_END_NAMESPACE

class CustomWidget : public QWidget
{
    Q_OBJECT

public:
    CustomWidget(QWidget *parent = nullptr);
    ~CustomWidget();

    void init();

    enum Color
    {
        Blue,
        Green,
        Red
    };

    Q_ENUM(Color)

  public slots:
    void languageChanged(int index);
    void switchTranslator(const QString& filename);
    void changeEvent(QEvent *event);

private:
    Ui::CustomWidget *ui;
    QTranslator m_translator;

    const QMetaObject &metaObj = staticQtMetaObject;
    QMetaEnum metaEnumColor;
    QStringList enumColorKeys;
    int indexColor;
};
