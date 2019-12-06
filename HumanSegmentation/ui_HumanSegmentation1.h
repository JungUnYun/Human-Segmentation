/********************************************************************************
** Form generated from reading UI file 'HumanSegmentation1.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HUMANSEGMENTATION1_H
#define UI_HUMANSEGMENTATION1_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HumanSegmentation1Class
{
public:
    QWidget *centralWidget;
    QLabel *label_input;
    QGroupBox *groupBox;
    QLabel *label_9;
    QLabel *label_ser_2;
    QLabel *label_ser_3;
    QPushButton *pushButton_info;
    QTextBrowser *textBrowser_h;
    QTextBrowser *textBrowser_w;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pause;
    QLabel *label_10;
    QTextBrowser *textBrowser_fps_s;
    QTextBrowser *textBrowser_fps_c;
    QLabel *label_ser_6;
    QLabel *label_ser_4;
    QPushButton *shape_sz;
    QPushButton *input_z;
    QPushButton *input_save;
    QPushButton *shape_saveserial;
    QLabel *label_shapeserial;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_shapeCUDA;
    QPushButton *shape_saveCUDA;
    QLabel *label_4;
    QPushButton *shape_cz;
    QLabel *label_2;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *HumanSegmentation1Class)
    {
        if (HumanSegmentation1Class->objectName().isEmpty())
            HumanSegmentation1Class->setObjectName(QStringLiteral("HumanSegmentation1Class"));
        HumanSegmentation1Class->resize(1147, 504);
        HumanSegmentation1Class->setStyleSheet(QStringLiteral("background-color: rgb(161, 161, 161);"));
        centralWidget = new QWidget(HumanSegmentation1Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label_input = new QLabel(centralWidget);
        label_input->setObjectName(QStringLiteral("label_input"));
        label_input->setGeometry(QRect(30, 40, 216, 384));
        label_input->setStyleSheet(QStringLiteral("background-color: rgb(161, 161, 161);"));
        label_input->setAlignment(Qt::AlignCenter);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(810, 20, 311, 451));
        QFont font;
        font.setFamily(QStringLiteral("Calibri"));
        font.setPointSize(17);
        font.setBold(true);
        font.setWeight(75);
        groupBox->setFont(font);
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(10, 50, 71, 31));
        QFont font1;
        font1.setFamily(QStringLiteral("Calibri"));
        font1.setPointSize(12);
        font1.setBold(false);
        font1.setWeight(50);
        label_9->setFont(font1);
        label_ser_2 = new QLabel(groupBox);
        label_ser_2->setObjectName(QStringLiteral("label_ser_2"));
        label_ser_2->setGeometry(QRect(40, 160, 101, 31));
        label_ser_2->setLayoutDirection(Qt::RightToLeft);
        label_ser_3 = new QLabel(groupBox);
        label_ser_3->setObjectName(QStringLiteral("label_ser_3"));
        label_ser_3->setGeometry(QRect(40, 200, 101, 31));
        pushButton_info = new QPushButton(groupBox);
        pushButton_info->setObjectName(QStringLiteral("pushButton_info"));
        pushButton_info->setGeometry(QRect(260, 400, 31, 31));
        QFont font2;
        font2.setPointSize(11);
        font2.setBold(true);
        font2.setWeight(75);
        pushButton_info->setFont(font2);
        textBrowser_h = new QTextBrowser(groupBox);
        textBrowser_h->setObjectName(QStringLiteral("textBrowser_h"));
        textBrowser_h->setGeometry(QRect(130, 200, 51, 31));
        QFont font3;
        font3.setPointSize(12);
        font3.setBold(true);
        font3.setWeight(75);
        textBrowser_h->setFont(font3);
        textBrowser_h->setLayoutDirection(Qt::RightToLeft);
        textBrowser_h->setFrameShape(QFrame::NoFrame);
        textBrowser_w = new QTextBrowser(groupBox);
        textBrowser_w->setObjectName(QStringLiteral("textBrowser_w"));
        textBrowser_w->setGeometry(QRect(130, 160, 51, 31));
        textBrowser_w->setFont(font3);
        textBrowser_w->setLayoutDirection(Qt::RightToLeft);
        textBrowser_w->setFrameShape(QFrame::NoFrame);
        textBrowser_w->setLineWidth(0);
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(20, 100, 101, 31));
        QFont font4;
        font4.setFamily(QStringLiteral("Calibri"));
        font4.setPointSize(11);
        font4.setBold(true);
        font4.setWeight(75);
        pushButton->setFont(font4);
        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(140, 100, 101, 31));
        pushButton_2->setFont(font4);
        pause = new QPushButton(groupBox);
        pause->setObjectName(QStringLiteral("pause"));
        pause->setGeometry(QRect(260, 100, 31, 31));
        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(10, 260, 71, 31));
        label_10->setFont(font1);
        textBrowser_fps_s = new QTextBrowser(groupBox);
        textBrowser_fps_s->setObjectName(QStringLiteral("textBrowser_fps_s"));
        textBrowser_fps_s->setGeometry(QRect(130, 310, 70, 31));
        textBrowser_fps_s->setFont(font1);
        textBrowser_fps_s->setLayoutDirection(Qt::RightToLeft);
        textBrowser_fps_s->setFrameShape(QFrame::NoFrame);
        textBrowser_fps_s->setLineWidth(0);
        textBrowser_fps_c = new QTextBrowser(groupBox);
        textBrowser_fps_c->setObjectName(QStringLiteral("textBrowser_fps_c"));
        textBrowser_fps_c->setGeometry(QRect(130, 360, 70, 31));
        textBrowser_fps_c->setFont(font1);
        textBrowser_fps_c->setLayoutDirection(Qt::RightToLeft);
        textBrowser_fps_c->setFrameShape(QFrame::NoFrame);
        textBrowser_fps_c->setLineWidth(0);
        label_ser_6 = new QLabel(groupBox);
        label_ser_6->setObjectName(QStringLiteral("label_ser_6"));
        label_ser_6->setGeometry(QRect(40, 310, 101, 31));
        label_ser_6->setLayoutDirection(Qt::RightToLeft);
        label_ser_4 = new QLabel(groupBox);
        label_ser_4->setObjectName(QStringLiteral("label_ser_4"));
        label_ser_4->setGeometry(QRect(40, 360, 101, 31));
        label_9->raise();
        label_ser_2->raise();
        label_ser_3->raise();
        pushButton_info->raise();
        textBrowser_h->raise();
        textBrowser_w->raise();
        pushButton->raise();
        pushButton_2->raise();
        pause->raise();
        label_10->raise();
        label_ser_6->raise();
        textBrowser_fps_s->raise();
        label_ser_4->raise();
        textBrowser_fps_c->raise();
        shape_sz = new QPushButton(centralWidget);
        shape_sz->setObjectName(QStringLiteral("shape_sz"));
        shape_sz->setGeometry(QRect(440, 440, 21, 21));
        input_z = new QPushButton(centralWidget);
        input_z->setObjectName(QStringLiteral("input_z"));
        input_z->setGeometry(QRect(190, 440, 21, 21));
        input_save = new QPushButton(centralWidget);
        input_save->setObjectName(QStringLiteral("input_save"));
        input_save->setGeometry(QRect(220, 440, 21, 21));
        shape_saveserial = new QPushButton(centralWidget);
        shape_saveserial->setObjectName(QStringLiteral("shape_saveserial"));
        shape_saveserial->setGeometry(QRect(470, 440, 21, 21));
        label_shapeserial = new QLabel(centralWidget);
        label_shapeserial->setObjectName(QStringLiteral("label_shapeserial"));
        label_shapeserial->setGeometry(QRect(280, 40, 216, 384));
        label_shapeserial->setStyleSheet(QStringLiteral("background-color: rgb(161, 161, 161);"));
        label_shapeserial->setAlignment(Qt::AlignCenter);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(90, 440, 71, 31));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(300, 440, 121, 31));
        label_shapeCUDA = new QLabel(centralWidget);
        label_shapeCUDA->setObjectName(QStringLiteral("label_shapeCUDA"));
        label_shapeCUDA->setGeometry(QRect(530, 40, 216, 384));
        label_shapeCUDA->setStyleSheet(QStringLiteral("background-color: rgb(161, 161, 161);"));
        label_shapeCUDA->setAlignment(Qt::AlignCenter);
        shape_saveCUDA = new QPushButton(centralWidget);
        shape_saveCUDA->setObjectName(QStringLiteral("shape_saveCUDA"));
        shape_saveCUDA->setGeometry(QRect(720, 440, 21, 21));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(550, 440, 121, 31));
        shape_cz = new QPushButton(centralWidget);
        shape_cz->setObjectName(QStringLiteral("shape_cz"));
        shape_cz->setGeometry(QRect(690, 440, 21, 21));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 20, 761, 461));
        label_2->setStyleSheet(QStringLiteral("background-color: rgb(161, 161, 161);"));
        label_2->setFrameShape(QFrame::Box);
        label_2->setFrameShadow(QFrame::Sunken);
        HumanSegmentation1Class->setCentralWidget(centralWidget);
        label_2->raise();
        label_input->raise();
        groupBox->raise();
        shape_sz->raise();
        input_z->raise();
        input_save->raise();
        shape_saveserial->raise();
        label_shapeserial->raise();
        label->raise();
        label_3->raise();
        label_shapeCUDA->raise();
        shape_saveCUDA->raise();
        label_4->raise();
        shape_cz->raise();
        statusBar = new QStatusBar(HumanSegmentation1Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        HumanSegmentation1Class->setStatusBar(statusBar);

        retranslateUi(HumanSegmentation1Class);
        QObject::connect(pushButton, SIGNAL(clicked()), HumanSegmentation1Class, SLOT(LoadSource()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), HumanSegmentation1Class, SLOT(LoadSourceVideo()));
        QObject::connect(pause, SIGNAL(clicked()), HumanSegmentation1Class, SLOT(checkpause()));
        QObject::connect(input_z, SIGNAL(clicked()), HumanSegmentation1Class, SLOT(inputzoom()));
        QObject::connect(pushButton_info, SIGNAL(clicked()), HumanSegmentation1Class, SLOT(show_info()));
        QObject::connect(shape_sz, SIGNAL(clicked()), HumanSegmentation1Class, SLOT(shapezoom_s()));
        QObject::connect(shape_cz, SIGNAL(clicked()), HumanSegmentation1Class, SLOT(shapezoom_c()));
        QObject::connect(input_save, SIGNAL(clicked()), HumanSegmentation1Class, SLOT(save_input()));
        QObject::connect(shape_saveserial, SIGNAL(clicked()), HumanSegmentation1Class, SLOT(save_serial()));
        QObject::connect(shape_saveCUDA, SIGNAL(clicked()), HumanSegmentation1Class, SLOT(save_cuda()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), HumanSegmentation1Class, SLOT(Hsegmentation_CUDA()));

        QMetaObject::connectSlotsByName(HumanSegmentation1Class);
    } // setupUi

    void retranslateUi(QMainWindow *HumanSegmentation1Class)
    {
        HumanSegmentation1Class->setWindowTitle(QApplication::translate("HumanSegmentation1Class", "HumanSegmentation1", Q_NULLPTR));
        label_input->setText(QString());
        groupBox->setTitle(QApplication::translate("HumanSegmentation1Class", "Human segmentation", Q_NULLPTR));
        label_9->setText(QApplication::translate("HumanSegmentation1Class", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt; font-weight:600;\">Load</span></p></body></html>", Q_NULLPTR));
        label_ser_2->setText(QApplication::translate("HumanSegmentation1Class", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:600;\">width  :</span></p></body></html>", Q_NULLPTR));
        label_ser_3->setText(QApplication::translate("HumanSegmentation1Class", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:600;\">height :</span></p></body></html>", Q_NULLPTR));
        pushButton_info->setText(QString());
        pushButton->setText(QApplication::translate("HumanSegmentation1Class", "Load Image", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("HumanSegmentation1Class", "Load Video", Q_NULLPTR));
        pause->setText(QString());
        label_10->setText(QApplication::translate("HumanSegmentation1Class", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt; font-weight:600;\">fps</span></p></body></html>", Q_NULLPTR));
        label_ser_6->setText(QApplication::translate("HumanSegmentation1Class", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:600;\">Serial :</span></p></body></html>", Q_NULLPTR));
        label_ser_4->setText(QApplication::translate("HumanSegmentation1Class", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:600;\">CUDA :</span></p></body></html>", Q_NULLPTR));
        shape_sz->setText(QString());
        input_z->setText(QString());
        input_save->setText(QString());
        shape_saveserial->setText(QString());
        label_shapeserial->setText(QString());
        label->setText(QApplication::translate("HumanSegmentation1Class", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">Input</span></p></body></html>", Q_NULLPTR));
        label_3->setText(QApplication::translate("HumanSegmentation1Class", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">Shape_serial</span></p></body></html>", Q_NULLPTR));
        label_shapeCUDA->setText(QString());
        shape_saveCUDA->setText(QString());
        label_4->setText(QApplication::translate("HumanSegmentation1Class", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">Shape_CUDA</span></p></body></html>", Q_NULLPTR));
        shape_cz->setText(QString());
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class HumanSegmentation1Class: public Ui_HumanSegmentation1Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HUMANSEGMENTATION1_H
