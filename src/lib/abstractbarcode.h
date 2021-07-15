/*
    SPDX-FileCopyrightText: 2010-2016 Sune Vuorela <sune@vuorela.dk>

    SPDX-License-Identifier: MIT
*/

#ifndef PRISON_ABSTRACTBARCODE_H
#define PRISON_ABSTRACTBARCODE_H
#include <QImage>
#include <QSizeF>
#include <QString>

#include "prison_export.h"

#include <memory>

class QColor;

namespace Prison
{
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
class PRISON_EXPORT AbstractBarcode
{
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
     * Textual content encoded in this barcode.
     * This returns an empty QString if binary content is set.
     * @see byteArrayData()
     */
    QString data() const;
    /**
     * Binary data encoded in this barcode.
     * This returns an empty QByteArray if textual content is set.
     * @see data()
     * @since 5.85
     */
    QByteArray byteArrayData() const;
    /**
     * Sets textual data to be drawn as a barcode.
     * Only use this function if your content is textual, use the QByteArray overload
     * when your content contains non-textual binary content.
     * Calling this function does not do any repaints of anything, they are
     * your own responsibility.
     * @param data textual barcode content
     */
    void setData(const QString &data);
    /**
     * Sets binary data to be drawn as a barcode.
     * Prefer the QString overload if your content is purely textual, to reduce
     * the risk of encoding issues for non-ASCII content.
     * Calling this function does not do any repaints of anything, they are
     * your own responsibility.
     * @param data binary barcode content
     * @since 5.85
     */
    void setData(const QByteArray &data);
    /**
     * Creates a image with a barcode on
     * @return QImage with a barcode on, trying to match the requested \param size
     *
     * If one of the dimensions of @param size is smaller than the matching dimension in \ref minimumSize,
     * a null QImage will be returned
     */
    QImage toImage(const QSizeF &size);

#if PRISON_ENABLE_DEPRECATED_SINCE(5, 72)
    /**
     * The minimal size of this barcode.
     * @note This isn't the absolute minimum, but closer to the result of preferredSize(1).
     * @return the minimal size for this barcode.
     * @deprecated Since 5.69, use preferredSize() or trueMinimumSize().
     */
    PRISON_DEPRECATED_VERSION_BELATED(5, 72, 5, 69, "Use preferredSize() or trueMinimumSize()")
    QSizeF minimumSize() const;
#endif

    /**
     * The minimal amount of pixels needed to represent this barcode without loss of information.
     * That is, the size of the barcode image if each line or dot is just one pixel wide.
     * On normal screens that is not enough for barcode scanners to reliably detect the barcode
     * though.
     * @see preferredSize
     * @since 5.69
     */
    QSizeF trueMinimumSize() const; // TODO KF6: rename to minimumSize

    /**
     * The recommended size for this barcode when shown on a screen.
     * This is typically significantly larger than trueMinimumSize() so that
     * barcode scanners tend to reliably detect the code. As this depends
     * on the physical resolution of the output, you have to pass the device
     * pixel ration of the output screen here.
     * @param devicePixelRatio The device pixel ratio of the screen this is shown on.
     * @see trueMinimumSize
     * @since 5.69
     */
    QSizeF preferredSize(qreal devicePixelRatio) const;

    /**
     * @return the foreground color (by default black) to be used for the barcode.
     */
    const QColor &foregroundColor() const;
    /**
     * @return the background color (by default white) to be used for the barcode.
     */
    const QColor &backgroundColor() const;
    /**
     * sets the foreground color
     * @param foregroundcolor - the new foreground color
     */
    void setForegroundColor(const QColor &foregroundcolor);
    /**
     * sets the background color
     * @param backgroundcolor - the new background color
     */
    void setBackgroundColor(const QColor &backgroundcolor);

    /** Dimensions of the barcode.
     *  @since 5.69
     */
    enum Dimensions : uint8_t {
        NoDimensions, ///< Null barcode.
        OneDimension, ///< One-dimensional barcode.
        TwoDimensions, ///< 2D matrix code.
    };

    /** Returns the amount of dimensions of the barcode.
     *  @since 5.69
     */
    Dimensions dimensions() const;

protected:
    ///@cond internal
    explicit AbstractBarcode(Dimensions dim);
    ///@endcond

#if PRISON_ENABLE_DEPRECATED_SINCE(5, 69)
    /**
     * Sets the minimum size for this barcode.
     * Some barcodes have minimum sizes for when they are readable and such
     * @param minimumSize QSizeF holding the minimum size for this barcode
     * @deprecated since 5.69, function is a no-op, no need to call this anymore.
     */
    PRISON_DEPRECATED_VERSION(5, 69, "no need to call this anymore")
    void setMinimumSize(const QSizeF &minimumSize);
#endif

    /**
     * Doing the actual painting of the image
     * @param size unused - will be removed in KF6
     * @return image with barcode, or null image
     */
    // TODO KF6: remove the size argument
    virtual QImage paintImage(const QSizeF &size) = 0;

private:
    friend class AbstractBarcodePrivate;
    /**
     * d-pointer
     */
    std::unique_ptr<class AbstractBarcodePrivate> const d;
};
} // namespace

#endif // PRISON_ABSTRACTBARCODE_H
