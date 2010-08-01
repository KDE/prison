#include "prison.h"

#include <QLineEdit>
#include <QPushButton>
#include "prison/QRCodeWidget"
#include "prison/QRCodeItem"
#include "prison/DataMatrixWidget"
#include "prison/DataMatrixItem"
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
}

main_window::main_window() {
  QHBoxLayout* lay = new QHBoxLayout();
  m_lineedit = new QLineEdit(this);
  QPushButton* but = new QPushButton(this);
  connect(but,SIGNAL(clicked()),SLOT(data_changed()));
  lay->addWidget(m_lineedit);
  lay->addWidget(but);

  QVBoxLayout* mainlay = new QVBoxLayout();

  m_dmw = new prison::DataMatrixWidget();
  m_qrw = new prison::QRCodeWidget();

  QGraphicsScene* scene = new QGraphicsScene(this);

  m_dmi = new prison::DataMatrixItem();
  m_qri = new prison::QRCodeItem();

  scene->addItem(m_dmi);
  m_dmi->setPos(0,0);
  scene->addItem(m_qri);
  m_qri->setPos(200,200);
  QGraphicsView* v = new QGraphicsView(this);
  v->setScene(scene);

  QSplitter* splitter = new QSplitter(Qt::Vertical);
  splitter->addWidget(v);
  splitter->addWidget(m_dmw);
  splitter->addWidget(m_qrw);

  mainlay->addLayout(lay);
  mainlay->addWidget(splitter);
  setLayout(mainlay);
}




#include "prison.moc"
