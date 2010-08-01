#ifndef prison_H
#define prison_H

#include <QWidget>

namespace prison {
  class AbstractBarcodeWidget;
  class AbstractBarcodeItem;
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
    prison::AbstractBarcodeWidget* m_dmw;
    prison::AbstractBarcodeWidget* m_qrw;
    prison::AbstractBarcodeItem* m_dmi;
    prison::AbstractBarcodeItem* m_qri;

};

#endif // prison_H
