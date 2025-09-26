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

static void safeSetData(BarcodeExampleWidget *w, const QString &data)
{
    if (w) {
        w->setData(data);
    }
}

void main_window::data_changed()
{
    QString result = m_lineedit->text();
    safeSetData(m_dmw, result);
    safeSetData(m_qrw, result);
    safeSetData(m_39w, result);
    safeSetData(m_93w, result);
    safeSetData(m_dmcolor, result);
    safeSetData(m_qrcolor, result);
    safeSetData(m_39color, result);
    safeSetData(m_93color, result);
    safeSetData(m_nullw, result);
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

    QSplitter *splitter = new QSplitter(Qt::Vertical);

    m_dmw = new BarcodeExampleWidget(Prison::DataMatrix, this);
    splitter->addWidget(m_dmw);
    m_qrw = new BarcodeExampleWidget(Prison::QRCode, this);
    splitter->addWidget(m_qrw);
    m_39w = new BarcodeExampleWidget(Prison::Code39, this);
    splitter->addWidget(m_39w);
    m_93w = new BarcodeExampleWidget(Prison::Code93, this);
    splitter->addWidget(m_93w);
    {
        auto dmcolorcode = Prison::Barcode::create(Prison::DataMatrix);
        if (dmcolorcode) {
            dmcolorcode->setForegroundColor(Qt::red);
            dmcolorcode->setBackgroundColor(Qt::darkBlue);
            m_dmcolor = new BarcodeExampleWidget(std::move(dmcolorcode), this);
            splitter->addWidget(m_dmcolor);
        }
    }
    {
        auto qrcolorcode = Prison::Barcode::create(Prison::QRCode);
        if (qrcolorcode) {
            qrcolorcode->setForegroundColor(Qt::red);
            qrcolorcode->setBackgroundColor(Qt::darkBlue);
        }
        m_qrcolor = new BarcodeExampleWidget(std::move(qrcolorcode), this);
        splitter->addWidget(m_qrcolor);
    }
    {
        auto c39colorcode = Prison::Barcode::create(Prison::Code39);
        if (c39colorcode) {
            c39colorcode->setForegroundColor(Qt::red);
            c39colorcode->setBackgroundColor(Qt::darkBlue);
        }
        m_39color = new BarcodeExampleWidget(std::move(c39colorcode), this);
        splitter->addWidget(m_39color);
    }
    {
        auto c93colorcode = Prison::Barcode::create(Prison::Code93);
        if (c93colorcode) {
            c93colorcode->setForegroundColor(Qt::red);
            c93colorcode->setBackgroundColor(Qt::darkBlue);
        }
        m_93color = new BarcodeExampleWidget(std::move(c93colorcode), this);
        splitter->addWidget(m_93color);
    }

    m_nullw = new BarcodeExampleWidget(std::nullopt, this);
    splitter->addWidget(m_nullw);

    mainlay->addLayout(lay);
    mainlay->addWidget(splitter);

    m_lineedit->setText(QStringLiteral("AOEUIAOEUIAOEUI"));
    data_changed();
}

#include "moc_prisontest.cpp"
