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
    prison::BarcodeItem* m_dmi;
    prison::BarcodeItem* m_qri;
    prison::BarcodeItem* m_nulli;
    prison::BarcodeWidget* m_nullw;
    

};

#endif // prison_H
