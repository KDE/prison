#ifndef prison_H
#define prison_H

#include <QWidget>

class BarcodeExampleWidget;

class QLineEdit;
class main_window : public QWidget {
  Q_OBJECT
  public:
    main_window();
  public Q_SLOTS:
    void data_changed();
  private:
    QLineEdit* m_lineedit;
    BarcodeExampleWidget* m_dmw;
    BarcodeExampleWidget* m_qrw;
    BarcodeExampleWidget* m_39w;
    BarcodeExampleWidget* m_93w;
    BarcodeExampleWidget* m_dmcolor;
    BarcodeExampleWidget* m_qrcolor;
    BarcodeExampleWidget* m_39color;
    BarcodeExampleWidget* m_93color;
    BarcodeExampleWidget* m_nullw;
    

};

#endif // prison_H
