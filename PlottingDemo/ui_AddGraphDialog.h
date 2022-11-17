/********************************************************************************
** Form generated from reading ui file 'AddGraphDialog.ui'
**
** Created: Thu 21. Jan 03:14:33 2010
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_ADDGRAPHDIALOG_H
#define UI_ADDGRAPHDIALOG_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AddGraphDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *tfPlotTitle;
    QLabel *label_2;
    QLineEdit *tfPlotFooter;
    QLabel *label_3;
    QComboBox *cbGraphType;
    QLabel *label_4;
    QPlainTextEdit *pteGraphData;
    QLabel *label_5;
    QLineEdit *tfXAxisLabel;
    QLabel *label_6;
    QLineEdit *tfYAxisLabel;
    QLabel *label_7;
    QLineEdit *tfZAxisLabel;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;

    void setupUi(QDialog *AddGraphDialog)
    {
        if (AddGraphDialog->objectName().isEmpty())
            AddGraphDialog->setObjectName(QString::fromUtf8("AddGraphDialog"));
        AddGraphDialog->setWindowModality(Qt::NonModal);
        AddGraphDialog->resize(400, 394);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AddGraphDialog->sizePolicy().hasHeightForWidth());
        AddGraphDialog->setSizePolicy(sizePolicy);
        AddGraphDialog->setMaximumSize(QSize(16777215, 500));
        AddGraphDialog->setWindowFilePath(QString::fromUtf8(""));
        AddGraphDialog->setModal(true);
        verticalLayout = new QVBoxLayout(AddGraphDialog);
        verticalLayout->setSpacing(0);
        verticalLayout->setMargin(5);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setMargin(5);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout->setRowWrapPolicy(QFormLayout::DontWrapRows);
        formLayout->setHorizontalSpacing(5);
        formLayout->setVerticalSpacing(5);
        label = new QLabel(AddGraphDialog);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label);

        tfPlotTitle = new QLineEdit(AddGraphDialog);
        tfPlotTitle->setObjectName(QString::fromUtf8("tfPlotTitle"));

        formLayout->setWidget(1, QFormLayout::FieldRole, tfPlotTitle);

        label_2 = new QLabel(AddGraphDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_2);

        tfPlotFooter = new QLineEdit(AddGraphDialog);
        tfPlotFooter->setObjectName(QString::fromUtf8("tfPlotFooter"));

        formLayout->setWidget(2, QFormLayout::FieldRole, tfPlotFooter);

        label_3 = new QLabel(AddGraphDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_3);

        cbGraphType = new QComboBox(AddGraphDialog);
        cbGraphType->setObjectName(QString::fromUtf8("cbGraphType"));

        formLayout->setWidget(6, QFormLayout::FieldRole, cbGraphType);

        label_4 = new QLabel(AddGraphDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(7, QFormLayout::LabelRole, label_4);

        pteGraphData = new QPlainTextEdit(AddGraphDialog);
        pteGraphData->setObjectName(QString::fromUtf8("pteGraphData"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pteGraphData->sizePolicy().hasHeightForWidth());
        pteGraphData->setSizePolicy(sizePolicy1);
        pteGraphData->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        formLayout->setWidget(7, QFormLayout::FieldRole, pteGraphData);

        label_5 = new QLabel(AddGraphDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_5);

        tfXAxisLabel = new QLineEdit(AddGraphDialog);
        tfXAxisLabel->setObjectName(QString::fromUtf8("tfXAxisLabel"));

        formLayout->setWidget(3, QFormLayout::FieldRole, tfXAxisLabel);

        label_6 = new QLabel(AddGraphDialog);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_6);

        tfYAxisLabel = new QLineEdit(AddGraphDialog);
        tfYAxisLabel->setObjectName(QString::fromUtf8("tfYAxisLabel"));

        formLayout->setWidget(4, QFormLayout::FieldRole, tfYAxisLabel);

        label_7 = new QLabel(AddGraphDialog);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_7);

        tfZAxisLabel = new QLineEdit(AddGraphDialog);
        tfZAxisLabel->setObjectName(QString::fromUtf8("tfZAxisLabel"));

        formLayout->setWidget(5, QFormLayout::FieldRole, tfZAxisLabel);


        verticalLayout->addLayout(formLayout);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(-1, -1, 5, -1);
        horizontalSpacer = new QSpacerItem(100, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);

        pushButton = new QPushButton(AddGraphDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMaximumSize(QSize(60, 16777215));

        gridLayout->addWidget(pushButton, 0, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

#ifndef QT_NO_SHORTCUT
        label->setBuddy(tfPlotTitle);
        label_2->setBuddy(tfPlotFooter);
        label_3->setBuddy(cbGraphType);
        label_4->setBuddy(pteGraphData);
        label_5->setBuddy(tfXAxisLabel);
        label_6->setBuddy(tfYAxisLabel);
        label_7->setBuddy(tfZAxisLabel);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(tfPlotTitle, tfPlotFooter);
        QWidget::setTabOrder(tfPlotFooter, tfXAxisLabel);
        QWidget::setTabOrder(tfXAxisLabel, tfYAxisLabel);
        QWidget::setTabOrder(tfYAxisLabel, tfZAxisLabel);
        QWidget::setTabOrder(tfZAxisLabel, cbGraphType);
        QWidget::setTabOrder(cbGraphType, pteGraphData);
        QWidget::setTabOrder(pteGraphData, pushButton);

        retranslateUi(AddGraphDialog);

        cbGraphType->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(AddGraphDialog);
    } // setupUi

    void retranslateUi(QDialog *AddGraphDialog)
    {
        AddGraphDialog->setWindowTitle(QApplication::translate("AddGraphDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("AddGraphDialog", "Title:", 0, QApplication::UnicodeUTF8));
        tfPlotTitle->setText(QApplication::translate("AddGraphDialog", "Some Title", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("AddGraphDialog", "Footer:", 0, QApplication::UnicodeUTF8));
        tfPlotFooter->setText(QApplication::translate("AddGraphDialog", "Some Footer", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("AddGraphDialog", "Type:", 0, QApplication::UnicodeUTF8));
        cbGraphType->clear();
        cbGraphType->insertItems(0, QStringList()
         << QApplication::translate("AddGraphDialog", "Line Graph", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("AddGraphDialog", "2D Scatter Plot", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("AddGraphDialog", "3D Scatter Plot", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("AddGraphDialog", "3D Scatter Plot with Contour Map", 0, QApplication::UnicodeUTF8)
        );
        label_4->setText(QApplication::translate("AddGraphDialog", "Data:", 0, QApplication::UnicodeUTF8));
        pteGraphData->setPlainText(QApplication::translate("AddGraphDialog", "10 0 10\n"
"20 10 30\n"
"30 0 40\n"
"40 20 10\n"
"50 5 10\n"
"60 15 20\n"
"70 0 30\n"
"80 20 10\n"
"90 0 10\n"
"100 10 0", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("AddGraphDialog", "X Axis Label:", 0, QApplication::UnicodeUTF8));
        tfXAxisLabel->setText(QApplication::translate("AddGraphDialog", "X", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("AddGraphDialog", "Y Axis Label:", 0, QApplication::UnicodeUTF8));
        tfYAxisLabel->setText(QApplication::translate("AddGraphDialog", "Y", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("AddGraphDialog", "Z Axis Label:", 0, QApplication::UnicodeUTF8));
        tfZAxisLabel->setText(QApplication::translate("AddGraphDialog", "Z", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("AddGraphDialog", "Done", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(AddGraphDialog);
    } // retranslateUi

};

namespace Ui {
    class AddGraphDialog: public Ui_AddGraphDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDGRAPHDIALOG_H
