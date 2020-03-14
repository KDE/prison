/*
    SPDX-FileCopyrightText: 2010-2016 Sune Vuorela <sune@vuorela.dk>

    SPDX-License-Identifier: MIT
*/

#ifndef PRISON_ABSTRACTBARCODE_H
#define PRISON_ABSTRACTBARCODE_H
#include <QString>
#include <QSizeF>
#include <QImage>

#include "prison_export.h"

class QColor;
class QPainter;

namespace Prison {
  /**
   * base class for barcode generators
   * To add your own barcode generator, subclass this class
   * and reimplement toImage(const QSizeF&) to do the actual
   * work of generating the barcode.
   *
   * The barcode is cached in AbstractBarcode when painting and
   * the size and the data doesn't change. Using the same AbstractBarcode
   * to paint on several surfaces, if they aren't of the exact same size
   * will break the caching
   */
class PRISON_EXPORT AbstractBarcode {
  public:
#if PRISON_ENABLE_DEPRECATED_SINCE(5, 69)
    /**
     * creates a barcode generator without any data
     * @deprecated since 5.69 Use Prison::createBarcode instead.
     */
    PRISON_DEPRECATED_VERSION(5, 69, "Use Prison::createBarcode()")
    AbstractBarcode();
#endif

    virtual ~AbstractBarcode();
    /**
     * @return the QString encoded in this barcode.
     */
    QString data() const;
    /**
     * sets the data to be drawn by this function
     * calling this function does not do any repaints of anything, they are
     * your own responsibility. If you are using the barcodes thru BarcodeWidget or BarcodeItem, you
     * should rather use their setData function, as they handle the relevant updates.
     * @param data QString containing the data
     */
    void setData(const QString& data);
    /**
     * Creates a image with a barcode on
     * @return QImage with a barcode on, trying to match the requested \param size
     *
     * The image function is cached and painted on demand.
     *
     * if one of the dimensions of @param size is smaller than the matching dimension in \ref minimumSize,
     * a null QImage will be returned
     */
    QImage toImage(const QSizeF& size) ;
    /**
     * Note! minimalSize() doesn't work as expected if this is not painting on something.
     * @return the minimal size for this barcode.
     */
    QSizeF minimumSize() const;
    /**
     * @return the foreground color (by default black) to be used for the barcode.
     */
    const QColor& foregroundColor() const;
    /**
     * @return the background color (by default white) to be used for the barcode.
     */
    const QColor& backgroundColor() const;
    /**
     * sets the foreground color
     * @param foregroundcolor - the new foreground color
     */
    void setForegroundColor(const QColor& foregroundcolor);
    /**
     * sets the background color
     * @param backgroundcolor - the new background color
     */
    void setBackgroundColor(const QColor& backgroundcolor);

    /** Dimensions of the barcode.
     *  @since 5.69
     */
    enum Dimensions : uint8_t {
        NoDimensions, ///< Null barcode.
        OneDimension, ///< One-dimensional barcode.
        TwoDimensions ///< 2D matrix code.
    };

    /** Returns the amount of dimensions of the barcode.
     *  @since 5.69
     */
    Dimensions dimensions() const;

  protected:
    ///@cond internal
    explicit AbstractBarcode(Dimensions dim);
    ///@endcond

    /**
     * Sets the minimum size for this barcode.
     * Some barcodes have minimum sizes for when they are readable and such
     * @param minimumSize QSizeF holding the minimum size for this barcode
     */
    void setMinimumSize(const QSizeF& minimumSize);
    /**
     * Doing the actual painting of the image
     * @param size requested size of the miage
     * @return image with barcode, or null image
     */
    virtual QImage paintImage(const QSizeF& size) = 0;
  private:
   class Private;
   /**
    * d-pointer
    */
   Private* d;

};
} //namespace

#endif // PRISON_ABSTRACTBARCODE_H
