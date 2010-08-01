# - Try to find the qrencode library
# Once done this will define
#
#  QRENCODE_FOUND - system has the qrencode library
#  QRENCODE_INCLUDE_DIR - the qrencode library include dir
#  QRENCODE_LIBRARIES - the libraries used to link qrencode

# Copyright (C) 2010 Sune Vuorela <sune@debian.org>

# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

if (QRENCODE_INCLUDE_DIR AND QRENCODE_LIBRARIES)
  # in cache already
  set(QRENCODE_FOUND TRUE)
else (QRENCODE_INCLUDE_DIR AND QRENCODE_LIBRARIES)

  find_path(QRENCODE_INCLUDE_DIR qrencode.h)

  find_library(QRENCODE_LIBRARIES NAMES qrencode)

  if (QRENCODE_INCLUDE_DIR AND QRENCODE_LIBRARIES)
     set(QRENCODE_FOUND TRUE)
  else (QRENCODE_INCLUDE_DIR AND QRENCODE_LIBRARIES)
     message("QRencode library not found, please see http://megaui.net/fukuchi/works/qrencode/index.en.html")
  endif (QRENCODE_INCLUDE_DIR AND QRENCODE_LIBRARIES)

  mark_as_advanced(QRENCODE_INCLUDE_DIR QRENCODE_LIBRARIES)

endif (QRENCODE_INCLUDE_DIR AND QRENCODE_LIBRARIES)
