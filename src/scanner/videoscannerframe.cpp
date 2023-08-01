/*
    SPDX-FileCopyrightText: 2022 Volker Krause <vkrause@kde.org>
    SPDX-License-Identifier: MIT
*/

#include "videoscannerframe_p.h"

#include <QAbstractVideoBuffer>

#include <cstring>

using namespace Prison;

VideoScannerFrame::VideoScannerFrame() = default;

VideoScannerFrame::VideoScannerFrame(const QVideoFrame &frame, bool isVerticallyFlipped, Format::BarcodeFormats formats)
    : m_frame(frame)
    , m_formats(formats)
    , m_verticallyFlipped(isVerticallyFlipped)
{
}

VideoScannerFrame::~VideoScannerFrame() = default;

int VideoScannerFrame::width() const
{
    return m_frame.width();
}

int VideoScannerFrame::height() const
{
    return m_frame.height();
}

int VideoScannerFrame::bytesPerLine() const
{
    return m_frame.bytesPerLine();
}

QVideoFrame::PixelFormat VideoScannerFrame::pixelFormat() const
{
    return m_frame.pixelFormat();
}

void VideoScannerFrame::map()
{
    if (!m_frameData && m_image.isNull()) {
        m_frame.map(QAbstractVideoBuffer::ReadOnly);
    }
}

void VideoScannerFrame::unmap()
{
    if (m_frame.isMapped()) {
        m_frame.unmap();
    }
}

const uint8_t *VideoScannerFrame::bits() const
{
    if (m_frameData) {
        return m_frameData;
    }
    if (!m_image.isNull()) {
        return m_image.bits();
    }

    Q_ASSERT(m_frame.isMapped());
    return m_frame.bits();
}

bool VideoScannerFrame::copyRequired() const
{
    return m_frame.handleType() == QAbstractVideoBuffer::GLTextureHandle;
}

void VideoScannerFrame::copyFrameData(QByteArray &buffer)
{
    Q_ASSERT(m_frame.isMapped());

    const auto size = frameDataSize();
    if (buffer.size() != size) {
        buffer.resize(size);
    }
    std::memcpy(buffer.data(), m_frame.bits(), size);
    m_frameData = reinterpret_cast<const uint8_t *>(buffer.constData());
}

int VideoScannerFrame::frameDataSize() const
{
    Q_ASSERT(m_frame.isMapped());

    switch (m_frame.pixelFormat()) {
    case QVideoFrame::Format_YUV420P:
    case QVideoFrame::Format_YUV422P:
    case QVideoFrame::Format_YV12:
    case QVideoFrame::Format_NV12:
    case QVideoFrame::Format_NV21:
    case QVideoFrame::Format_IMC1:
    case QVideoFrame::Format_IMC2:
    case QVideoFrame::Format_IMC3:
    case QVideoFrame::Format_IMC4:
        return m_frame.mappedBytes() / 2;
    default:
        return m_frame.mappedBytes();
    }
}

bool VideoScannerFrame::needsConversion() const
{
    switch (m_frame.pixelFormat()) {
    case QVideoFrame::Format_RGB565:
    case QVideoFrame::Format_RGB555:
    case QVideoFrame::Format_ARGB8565_Premultiplied:
    case QVideoFrame::Format_BGR565:
    case QVideoFrame::Format_BGR555:
    case QVideoFrame::Format_BGRA5658_Premultiplied:
    case QVideoFrame::Format_Jpeg:
    case QVideoFrame::Format_CameraRaw:
    case QVideoFrame::Format_AdobeDng:
    case QVideoFrame::Format_User:
        return true;
    default:
        return false;
    }
}

void VideoScannerFrame::convertToImage()
{
    if (!m_image.isNull()) {
        return;
    }

    Q_ASSERT(m_frame.isMapped());
    m_image = m_frame.image();
    m_image.convertTo(QImage::Format_Grayscale8);
}

bool VideoScannerFrame::isVerticallyFlipped() const
{
#ifdef Q_OS_ANDROID
    return true;
#endif
    return m_verticallyFlipped;
}

Format::BarcodeFormats VideoScannerFrame::formats() const
{
    return m_formats;
}
