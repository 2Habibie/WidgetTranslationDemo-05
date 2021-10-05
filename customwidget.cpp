#include "customwidget.h"
#include "ui_customwidget.h"

CustomWidget::CustomWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CustomWidget)
{
    ui->setupUi(this);

    indexColor = staticMetaObject.indexOfEnumerator("Color");
    metaEnumColor = staticMetaObject.enumerator(indexColor);
    init();

    connect(ui->languageSelectorCmbBox,SIGNAL(currentIndexChanged(int)),this, SLOT(languageChanged(int)));
    qApp->installTranslator(&m_translator);
}

CustomWidget::~CustomWidget()
{
    delete ui;
}

void CustomWidget::init()
{
    int counter = metaEnumColor.keyCount();
    qDebug() << "[" << __func__ << "]: counter =" << counter;

    for(int i=0; i<counter; i++)
    {
        QString colorKey = tr(metaEnumColor.key(i));
        enumColorKeys << colorKey;
        qDebug() << "[" << __func__ << "]:" << colorKey << "color added to enum";
    }

    ui->comboBoxColor->addItems(enumColorKeys);
}

void CustomWidget::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
    QWidget::changeEvent(event);
}

void CustomWidget::switchTranslator(const QString& filename)
{
    qApp->removeTranslator(&m_translator);
    if(m_translator.load(filename))
    {
        qApp->installTranslator(&m_translator);
    }
}

void CustomWidget::languageChanged(int index)
{
    switch(index)
    {
    case 0: //English
        switchTranslator(":/i18n/WidgetTranslationDemo_en_US.qm");
        break;
    case 1: //German
        switchTranslator(":/i18n/WidgetTranslationDemo_de_DE.qm");
        break;
    case 2: //Spanish
        switchTranslator(":/i18n/WidgetTranslationDemo_es_ES.qm");
        break;
    }
}
