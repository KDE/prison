#include "prison.h"

#include <QLineEdit>
#include <QPushButton>
#include "prison/BarcodeItem"
#include "prison/BarcodeWidget"
#include "prison/DataMatrixBarcode"
#include "prison/QRCodeBarcode"
#include <QHBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsLinearLayout>
#include <QSplitter>

void main_window::data_changed() {
  QString result = m_lineedit->text();
  m_dmi->setData(result);
  m_dmw->setData(result);
  m_qri->setData(result);
  m_qrw->setData(result);
  m_nulli->setData(result);
  m_nullw->setData(result);
  
}

main_window::main_window() {
  QHBoxLayout* lay = new QHBoxLayout();
  m_lineedit = new QLineEdit(this);
  QPushButton* but = new QPushButton(this);
  connect(but,SIGNAL(clicked()),SLOT(data_changed()));
  lay->addWidget(m_lineedit);
  lay->addWidget(but);

  QVBoxLayout* mainlay = new QVBoxLayout();

  m_dmw = new prison::BarcodeWidget(new prison::DataMatrixBarcode(),this);
  m_qrw = new prison::BarcodeWidget(new prison::QRCodeBarcode(),this);

  QGraphicsScene* scene = new QGraphicsScene(this);

  m_dmi = new prison::BarcodeItem(new prison::DataMatrixBarcode());
  m_qri = new prison::BarcodeItem(new prison::QRCodeBarcode());

  m_nulli = new prison::BarcodeItem();
  m_nullw = new prison::BarcodeWidget();

  scene->addItem(m_dmi);
  m_dmi->setPos(0,0);
  scene->addItem(m_qri);
  m_qri->setPos(200,200);
  scene->addItem(m_nulli);
  m_nulli->setPos(0,200);

  prison::BarcodeItem* with_value = new prison::BarcodeItem();
  with_value->setBarcode(new prison::QRCodeBarcode());
  with_value->setData("hello");
  scene->addItem(with_value);
  with_value->setPos(200,0);
  
  QGraphicsView* v = new QGraphicsView(this);
  v->setScene(scene);

  QSplitter* splitter = new QSplitter(Qt::Vertical);
  splitter->addWidget(v);
  splitter->addWidget(m_dmw);
  splitter->addWidget(m_qrw);
  splitter->addWidget(m_nullw);

  mainlay->addLayout(lay);
  mainlay->addWidget(splitter);
  setLayout(mainlay);
}




#include "prison.moc"
