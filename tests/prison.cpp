/*
    SPDX-FileCopyrightText: 2010-2016 Sune Vuorela <sune@vuorela.dk>

    SPDX-License-Identifier: MIT
*/

#include "prison.h"

#include "barcodeexamplewidget.h"
// Prison
#include <prison/abstractbarcode.h>
#include <prison/prison.h>
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
        Prison::AbstractBarcode *barcode = Prison::createBarcode(Prison::DataMatrix);
        if (!barcode) {
            qDebug() << "unsupported barcode, showing a black square";
        }
        m_dmw = new BarcodeExampleWidget(barcode, this);
    }
    {
        Prison::AbstractBarcode *barcode = Prison::createBarcode(Prison::QRCode);
        if (!barcode) {
            qDebug() << "unsupported barcode, showing a black square";
        }
        m_qrw = new BarcodeExampleWidget(barcode, this);
    }
    {
        Prison::AbstractBarcode *barcode = Prison::createBarcode(Prison::Code39);
        if (!barcode) {
            qDebug() << "unsupported barcode, showing a black square";
        }
        m_39w = new BarcodeExampleWidget(barcode, this);
    }
    {
        Prison::AbstractBarcode *barcode = Prison::createBarcode(Prison::Code93);
        if (!barcode) {
            qDebug() << "unsupported barcode, showing a black square";
        }
        m_93w = new BarcodeExampleWidget(barcode, this);
    }
    {
        Prison::AbstractBarcode *dmcolorcode = Prison::createBarcode(Prison::DataMatrix);
        if (dmcolorcode) {
            dmcolorcode->setForegroundColor(Qt::red);
            dmcolorcode->setBackgroundColor(Qt::darkBlue);
        } else {
            qDebug() << "unsupported barcode, showing a black square";
        }
        m_dmcolor = new BarcodeExampleWidget(dmcolorcode, this);
    }
    {
        Prison::AbstractBarcode *qrcolorcode = Prison::createBarcode(Prison::QRCode);
        if (qrcolorcode) {
            qrcolorcode->setForegroundColor(Qt::red);
            qrcolorcode->setBackgroundColor(Qt::darkBlue);
        } else {
            qDebug() << "unsupported barcode, showing a black square";
        }
        m_qrcolor = new BarcodeExampleWidget(qrcolorcode, this);
    }
    {
        Prison::AbstractBarcode *c39colorcode = Prison::createBarcode(Prison::Code39);
        if (c39colorcode) {
            c39colorcode->setForegroundColor(Qt::red);
            c39colorcode->setBackgroundColor(Qt::darkBlue);
        } else {
            qDebug() << "unsupported barcode, showing a black square";
        }
        m_39color = new BarcodeExampleWidget(c39colorcode, this);
    }
    {
        Prison::AbstractBarcode *c93colorcode = Prison::createBarcode(Prison::Code93);
        if (c93colorcode) {
            c93colorcode->setForegroundColor(Qt::red);
            c93colorcode->setBackgroundColor(Qt::darkBlue);
        } else {
            qDebug() << "unsupported barcode, showing a black square";
        }
        m_93color = new BarcodeExampleWidget(c93colorcode, this);
    }

    m_nullw = new BarcodeExampleWidget(nullptr, this);

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
