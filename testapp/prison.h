#ifndef prison_H
#define prison_H

#include <QWidget>

namespace prison {
  class BarcodeWidget;
  class BarcodeItem;
}

class QLineEdit;
class main_window : public QWidget {
  Q_OBJECT
  public:
    main_window();
  public Q_SLOTS:
    void data_changed();
  private:
    QLineEdit* m_lineedit;
    prison::BarcodeWidget* m_dmw;
    prison::BarcodeWidget* m_qrw;
    prison::BarcodeWidget* m_39w;
    prison::BarcodeWidget* m_93w;
    prison::BarcodeWidget* m_dmcolor;
    prison::BarcodeWidget* m_qrcolor;
    prison::BarcodeWidget* m_39color;
    prison::BarcodeWidget* m_93color;
    prison::BarcodeItem* m_dmi;
    prison::BarcodeItem* m_qri;
    prison::BarcodeItem* m_39i;
    prison::BarcodeItem* m_93i;
    prison::BarcodeItem* m_nulli;
    prison::BarcodeWidget* m_nullw;
    

};

#endif // prison_H
