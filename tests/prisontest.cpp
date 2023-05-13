/*
    SPDX-FileCopyrightText: 2010-2016 Sune Vuorela <sune@vuorela.dk>

    SPDX-License-Identifier: MIT
*/

#include "prisontest.h"

#include "barcodeexamplewidget.h"
// Prison
#include <Prison/Barcode>
// Qt
#include <QDebug>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QSplitter>

void main_window::data_changed()
{
    QString result = m_lineedit->text();
    m_dmw->setData(result);
    m_qrw->setData(result);
    m_39w->setData(result);
    m_93w->setData(result);
    m_nullw->setData(result);
    m_dmcolor->setData(result);
    m_qrcolor->setData(result);
    m_39color->setData(result);
    m_93color->setData(result);
}

main_window::main_window()
{
    QHBoxLayout *lay = new QHBoxLayout();
    m_lineedit = new QLineEdit(this);
    QPushButton *but = new QPushButton(this);
    connect(but, &QPushButton::clicked, this, &main_window::data_changed);
    lay->addWidget(m_lineedit);
    lay->addWidget(but);

    QVBoxLayout *mainlay = new QVBoxLayout(this);

    {
        auto barcode = Prison::Barcode(Prison::DataMatrix);
        if (barcode.format() == Prison::Null) {
            qDebug() << "unsupported barcode, showing a black square";
        }
        m_dmw = new BarcodeExampleWidget(std::move(barcode), this);
    }
    {
        auto barcode = Prison::Barcode(Prison::QRCode);
        if (barcode.format() == Prison::Null) {
            qDebug() << "unsupported barcode, showing a black square";
        }
        m_qrw = new BarcodeExampleWidget(std::move(barcode), this);
    }
    {
        auto barcode = Prison::Barcode(Prison::Code39);
        if (barcode.format() == Prison::Null) {
            qDebug() << "unsupported barcode, showing a black square";
        }
        m_39w = new BarcodeExampleWidget(std::move(barcode), this);
    }
    {
        auto barcode = Prison::Barcode(Prison::Code93);
        if (barcode.format() == Prison::Null) {
            qDebug() << "unsupported barcode, showing a black square";
        }
        m_93w = new BarcodeExampleWidget(std::move(barcode), this);
    }
    {
        auto dmcolorcode = Prison::Barcode(Prison::DataMatrix);
        if (dmcolorcode.format() != Prison::Null) {
            dmcolorcode.setForegroundColor(Qt::red);
            dmcolorcode.setBackgroundColor(Qt::darkBlue);
        } else {
            qDebug() << "unsupported barcode, showing a black square";
        }
        m_dmcolor = new BarcodeExampleWidget(std::move(dmcolorcode), this);
    }
    {
        auto qrcolorcode = Prison::Barcode(Prison::QRCode);
        if (qrcolorcode.format() != Prison::Null) {
            qrcolorcode.setForegroundColor(Qt::red);
            qrcolorcode.setBackgroundColor(Qt::darkBlue);
        } else {
            qDebug() << "unsupported barcode, showing a black square";
        }
        m_qrcolor = new BarcodeExampleWidget(std::move(qrcolorcode), this);
    }
    {
        auto c39colorcode = Prison::Barcode(Prison::Code39);
        if (c39colorcode.format() != Prison::Null) {
            c39colorcode.setForegroundColor(Qt::red);
            c39colorcode.setBackgroundColor(Qt::darkBlue);
        } else {
            qDebug() << "unsupported barcode, showing a black square";
        }
        m_39color = new BarcodeExampleWidget(std::move(c39colorcode), this);
    }
    {
        auto c93colorcode = Prison::Barcode(Prison::Code93);
        if (c93colorcode.format() != Prison::Null) {
            c93colorcode.setForegroundColor(Qt::red);
            c93colorcode.setBackgroundColor(Qt::darkBlue);
        } else {
            qDebug() << "unsupported barcode, showing a black square";
        }
        m_93color = new BarcodeExampleWidget(std::move(c93colorcode), this);
    }

    m_nullw = new BarcodeExampleWidget(Prison::Barcode(Prison::Null), this);

    QSplitter *splitter = new QSplitter(Qt::Vertical);
    splitter->addWidget(m_dmw);
    splitter->addWidget(m_qrw);
    splitter->addWidget(m_39w);
    splitter->addWidget(m_93w);
    splitter->addWidget(m_dmcolor);
    splitter->addWidget(m_qrcolor);
    splitter->addWidget(m_39color);
    splitter->addWidget(m_93color);
    splitter->addWidget(m_nullw);

    mainlay->addLayout(lay);
    mainlay->addWidget(splitter);

    m_lineedit->setText(QStringLiteral("AOEUIAOEUIAOEUI"));
    data_changed();
}
