#include "prison.h"

#include <QLineEdit>
#include <QPushButton>
#include <prison/datamatrixbarcode.h>
#include <prison/qrcodebarcode.h>
#include <prison/code39barcode.h>
#include <prison/code93barcode.h>
#include <QHBoxLayout>
#include <QSplitter>
#include "barcodeexamplewidget.h"

void main_window::data_changed() {
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

main_window::main_window() {
  QHBoxLayout* lay = new QHBoxLayout();
  m_lineedit = new QLineEdit(this);
  QPushButton* but = new QPushButton(this);
  connect(but,SIGNAL(clicked()),SLOT(data_changed()));
  lay->addWidget(m_lineedit);
  lay->addWidget(but);

  QVBoxLayout* mainlay = new QVBoxLayout();

  m_dmw = new BarcodeExampleWidget(new prison::DataMatrixBarcode(),this);
  m_qrw = new BarcodeExampleWidget(new prison::QRCodeBarcode(),this);
  m_39w = new BarcodeExampleWidget(new prison::Code39Barcode(),this);
  m_93w = new BarcodeExampleWidget(new prison::Code93Barcode(),this);
  {
    prison::DataMatrixBarcode* dmcolorcode = new prison::DataMatrixBarcode();
    dmcolorcode->setForegroundColor(Qt::red);
    dmcolorcode->setBackgroundColor(Qt::darkBlue);
    m_dmcolor = new BarcodeExampleWidget(dmcolorcode,this);
  }
  {
    prison::QRCodeBarcode* qrcolorcode =  new prison::QRCodeBarcode();
    qrcolorcode->setForegroundColor(Qt::red);
    qrcolorcode->setBackgroundColor(Qt::darkBlue);
    m_qrcolor = new BarcodeExampleWidget(qrcolorcode,this);
  }
  {
    prison::Code39Barcode* c39colorcode =  new prison::Code39Barcode();
    c39colorcode->setForegroundColor(Qt::red);
    c39colorcode->setBackgroundColor(Qt::darkBlue);
    m_39color = new BarcodeExampleWidget(c39colorcode,this);
  }
  {
    prison::Code93Barcode* c93colorcode =  new prison::Code93Barcode();
    c93colorcode->setForegroundColor(Qt::red);
    c93colorcode->setBackgroundColor(Qt::darkBlue);
    m_93color = new BarcodeExampleWidget(c93colorcode,this);
  }

  m_nullw = new BarcodeExampleWidget(0,this);

  QSplitter* splitter = new QSplitter(Qt::Vertical);
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
  setLayout(mainlay);

  m_lineedit->setText(QLatin1String("AOEUIAOEUIAOEUI"));
  data_changed();
}
