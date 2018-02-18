# Prison

A barcode abstraction layer providing uniform access to generation of barcodes with data

## Introduction

Prison has a Prison::AbstractBarcode, which is the base class for the actual
barcode generators, currently Prison::QRCodeBarcode and Prison::DataMatrixBarcode
are the two implemented barcode generators.

Prison currently ships a BarcodeWidget, which is a QWidget with a barcode
painted upon, as well as a BarcodeItem, which is a QGraphicsItem with a
barcode painted upon.

## Supported Barcode types

There are basically two types of barcodes:
* barcodes that carry the data
* barcodes that carry a lookup number, and require a specific server to
  look up the actual data.

Prison isn't as such designed for the latter, it will probably work, but
patches implementing barcode support for such barcodes will not be accepted.
An example is [EZCode](https://en.wikipedia.org/wiki/EZcode).

Prison is currently using [libdmtx](https://github.com/dmtx/libdmtx) for generation of
[DataMatrix](https://en.wikipedia.org/wiki/Datamatrix) barcodes and
[libqrencode](https://fukuchi.org/works/qrencode/) for generation
of [QRCode](https://en.wikipedia.org/wiki/QR_Code) barcodes.

