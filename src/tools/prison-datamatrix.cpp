/*
    Copyright (c) 2010-2016 Sune Vuorela <sune@vuorela.dk>

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

#include <QCoreApplication>
#include "prison.h"
#include "abstractbarcode.h"
#include <qstringlist.h>
#include <QImageWriter>
#include <QDebug>

#include <iostream>
#include <qtextstream.h>

void error(const QString& error, const QString& errormessage) {
  QTextStream str(stdout);
  str << error << ": " << errormessage << endl;
  exit(0);
}

int main(int argc, char* argv[]) {
  QCoreApplication app(argc,argv);

  QString size;
  QString outputfile;
  QString outputformat;
  QStringList arguments = app.arguments();

  QString appname = arguments.takeFirst();
  while(!arguments.isEmpty()) {
    QString argument = arguments.takeFirst();
    if(argument==QLatin1String("--")) {
      break; //rest is data
    } else if(argument==QLatin1String("--size")||argument==QLatin1String("-s")) {
      size=arguments.takeFirst();
    } else if(argument==QLatin1String("--outputfile") || argument==QLatin1String("--output-file") || argument==QLatin1String("-o")) {
      outputfile = arguments.takeFirst();
    } else if(argument==QLatin1String("--output-format") || argument==QLatin1String("--output-format") || argument==QLatin1String("-f")) {
      outputformat = arguments.takeFirst();
    } else if(argument.startsWith(QLatin1String("-"))) {
      error(QLatin1String("unknown argument"),argument);
    } else {
      break;
    }
  }

  if(outputformat.isEmpty()) {
    outputformat=QLatin1String("png");
  }

  if(!QImageWriter::supportedImageFormats().contains(outputformat.toLocal8Bit())) {
    error(QLatin1String("unsupported output format"), outputformat);
  }
  
  if(outputfile.isEmpty()) {
    error(QLatin1String("outputfile is missing"),QString());
  }

  bool ok=false;
  int intsize = size.toInt(&ok);
  if(!ok) {
    error(QLatin1String("size not a int"),size);
  }
  if(intsize < 10) {
    error(QLatin1String("needs a larger output size"),size);
  }

  
  
  QString data = arguments.join(QLatin1String(" "));
  if(data.size()==0) {
    QTextStream in(stdin);
    data = in.readAll();
    if(data.size()==0) {
      error(QLatin1String("No data, neither on commandline nor on stdin"),QString());
    }
  }

  QScopedPointer<Prison::AbstractBarcode> barcode;
  barcode.reset(Prison::createBarcode(Prison::DataMatrix));
  if(!barcode) {
    error(QLatin1String("unsupported barcode type"), QString());
  }

  barcode->setData(data);
  QImage result = barcode->toImage(QSizeF(intsize,intsize));
  QImageWriter w(outputfile,outputformat.toLocal8Bit());
  if(!w.write(result)) {
    error(QLatin1String("writing failed"),w.errorString());
  }
  
}
