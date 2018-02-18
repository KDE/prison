#.rst:
# FindQRencode
# ------------
#
# Try to find the qrencode library.
#
# This will define the following variables:
#
# ``QRencode_FOUND``
#     True if the QRencode library is available.
#
# ``QRencode_INCLUDE_DIRS``
#     the QRencode library include dirs.
#     This variable shall be passed to target_include_libraries() calls if
#     the target is not used for linking.
#
# ``QRencode_LIBRARIES``
#     the libraries used to link QRencode.
#     This can be passed to target_link_libraries instead of
#     the ``QRencode::QRencode`` target.
#
# If ``QRencode_FOUND`` is TRUE, the following imported target
# will be available:
#
# ``QRencode::QRencode``
#     The QRencode library.
#
# Imported target since 5.27.0
#
#=============================================================================
# Copyright (C) 2010 Sune Vuorela <sune@debian.org>
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# 1. Redistributions of source code must retain the copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 3. The name of the author may not be used to endorse or promote products
#    derived from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
# OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
# IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
# NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
# THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#=============================================================================

find_library(QRencode_LIBRARIES NAMES qrencode qrencoded)

find_path(QRencode_INCLUDE_DIRS qrencode.h)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(QRencode
    FOUND_VAR QRencode_FOUND
    REQUIRED_VARS QRencode_LIBRARIES QRencode_INCLUDE_DIRS
)

if(QRencode_FOUND AND NOT TARGET QRencode::QRencode)
  add_library(QRencode::QRencode UNKNOWN IMPORTED)
  set_target_properties(QRencode::QRencode PROPERTIES
  IMPORTED_LOCATION "${QRencode_LIBRARIES}"
  INTERFACE_INCLUDE_DIRECTORIES "${QRencode_INCLUDE_DIRS}")
endif()

mark_as_advanced(QRencode_LIBRARIES QRencode_INCLUDE_DIRS)

include(FeatureSummary)
set_package_properties(QRencode PROPERTIES
  URL "https://fukuchi.org/works/qrencode/"
  DESCRIPTION "The QRencode library"
)
