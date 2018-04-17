/*
    Copyright (c) 2011 Geoffry Song <goffrie@gmail.com>

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.

*/

#include "code39barcode.h"
#include <QChar>
#include <QColor>

using namespace Prison;
/**
@cond PRIVATE
*/
class Code39Barcode::Private {
  public:
    static QList<bool> barSequence(const char* str) {
      Q_ASSERT(strlen(str)==9); // this is a internal helper tool, only called with fixed strings in here, all 9 chars long
      QList<bool> ret;
      for(int i = 0 ; i < 9 ; i++) {
        ret.append(str[i] == '1');
        Q_ASSERT(str[i] == '0' || str[i] == '1');
      }
      return ret;
    }
    static QList<bool> sequenceForChar(ushort c) {
      switch(QChar::toUpper(c)) {
        case '0': return barSequence("000110100");
        case '1': return barSequence("100100001");
        case '2': return barSequence("001100001");
        case '3': return barSequence("101100000");
        case '4': return barSequence("000110001");
        case '5': return barSequence("100110000");
        case '6': return barSequence("001110000");
        case '7': return barSequence("000100101");
        case '8': return barSequence("100100100");
        case '9': return barSequence("001100100");
        case 'A': return barSequence("100001001");
        case 'B': return barSequence("001001001");
        case 'C': return barSequence("101001000");
        case 'D': return barSequence("000011001");
        case 'E': return barSequence("100011000");
        case 'F': return barSequence("001011000");
        case 'G': return barSequence("000001101");
        case 'H': return barSequence("100001100");
        case 'I': return barSequence("001001100");
        case 'J': return barSequence("000011100");
        case 'K': return barSequence("100000011");
        case 'L': return barSequence("001000011");
        case 'M': return barSequence("101000010");
        case 'N': return barSequence("000010011");
        case 'O': return barSequence("100010010");
        case 'P': return barSequence("001010010");
        case 'Q': return barSequence("000000111");
        case 'R': return barSequence("100000110");
        case 'S': return barSequence("001000110");
        case 'T': return barSequence("000010110");
        case 'U': return barSequence("110000001");
        case 'V': return barSequence("011000001");
        case 'W': return barSequence("111000000");
        case 'X': return barSequence("010010001");
        case 'Y': return barSequence("110010000");
        case 'Z': return barSequence("011010000");
        case '-': return barSequence("010000101");
        case '.': return barSequence("110000100");
        case ' ': return barSequence("011000100");
        case '$': return barSequence("010101000");
        case '/': return barSequence("010100010");
        case '+': return barSequence("010001010");
        case '%': return barSequence("000101010");
        default: return QList<bool>(); // unknown character
      }
    }
};
/**
@endcond
*/

Code39Barcode::Code39Barcode() : AbstractBarcode(), d(nullptr){
}

Code39Barcode::~Code39Barcode() {
  delete d;
}

QImage Code39Barcode::paintImage(const QSizeF& size) {
  if(size.height() == 0.0) return QImage();
  QList<bool> barcode;
  // convert text into sequences of wide/narrow bars
  {
    // the guard sequence that goes on each end
    const QList<bool> endSequence = Private::barSequence("010010100");
    barcode += endSequence;
    barcode += false;
    // translate the string
    const QString str = data();
    for(int i = 0 ; i < str.size(); i++) {
      QList<bool> b = Private::sequenceForChar(str.at(i).unicode());
      if(!b.empty()) {
        barcode += b;
        barcode += false; // add a narrow space between each character
      }
    }
    // ending guard
    barcode += endSequence;
  }

  /*
   calculate integer bar widths that fit inside `size'
   each character has 6 narrow bars and 3 wide bars and there is a narrow bar between characters
   restrictions:
     *) smallWidth * 2 <= largeWidth <= smallWidth * 3
        - in other words, the ratio largeWidth:smallWidth is between 3:1 and 2:1
     *) wide * largeWidth + narrow * smallWidth <= size.width()
        - the barcode has to fit within the given size
   */
  const int w = size.width();
  const int wide = barcode.count(true);
  const int narrow = barcode.count(false);
  // maximize wide bar width
  int largeWidth = 2*w / (2*wide + narrow);
  // then maximize narrow bar width
  int smallWidth = (w - largeWidth*wide) / narrow;
  // if the requested size was too small return a null image
  setMinimumSize(QSize(2* wide + narrow, 10));
  if(largeWidth<2) {
      return QImage();
  }
  if(smallWidth<1) {
        return QImage();
  }
  Q_ASSERT(largeWidth > smallWidth);

  // one line of the result image
  QVector<QRgb> line;
  line.reserve(wide * largeWidth + narrow * smallWidth);
  for(int i = 0 ; i < barcode.size() ; i++) {
    const QRgb color = (((i&1) == 0) ? foregroundColor() : backgroundColor()).rgba(); // alternate between foreground and background color
    const int width = barcode.at(i) ? largeWidth : smallWidth;
    for(int j = 0 ; j < width ; j++) {
      line.append(color);
    }
  }

  // build the complete barcode
  QImage ret(line.size(), size.height(), QImage::Format_ARGB32);
  // just repeat the line to make the image
  for(int y = 0 ; y < ret.height() ; y++) {
    memcpy(ret.scanLine(y), line.data(), line.size() * sizeof(QRgb));
  }
  return ret;
}

