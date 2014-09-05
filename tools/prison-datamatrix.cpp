#include <QCoreApplication>
#include <prison/DataMatrixBarcode>
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
      error("unknown argument",argument);
    } else {
      break;
    }
  }

  if(outputformat.isEmpty()) {
    outputformat=QLatin1String("png");
  }

  if(!QImageWriter::supportedImageFormats().contains(outputformat.toLocal8Bit())) {
    error("unsupported output format", outputformat);
  }
  
  if(outputfile.isEmpty()) {
    error("outputfile is missing",QString());
  }

  bool ok=false;
  int intsize = size.toInt(&ok);
  if(!ok) {
    error("size not a int",size);
  }
  if(intsize < 10) {
    error("needs a larger output size",size);
  }

  
  
  QString data = arguments.join(QLatin1String(" "));
  if(data.size()==0) {
    QTextStream in(stdin);
    data = in.readAll();
    if(data.size()==0) {
      error("No data, neither on commandline nor on stdin",QString());
    }
  }

  prison::DataMatrixBarcode barcode;
  barcode.setData(data);
  QImage result = barcode.toImage(QSizeF(intsize,intsize));
  QImageWriter w(outputfile,outputformat.toLocal8Bit());
  if(!w.write(result)) {
    error("writing failed",w.errorString());
  }
  
}
