#.rst:
# FindDmtx
# --------
#
# Try to find the DataMatrix library.
#
# This will define the following variables:
#
# ``Dmtx_FOUND``
#     True if the datamatrix library is available.
#
# ``Dmtx_INCLUDE_DIRS``
#     the datamatrix library include dirs.
#     This variable shall be passed to target_include_libraries() calls if
#     the target is not used for linking.
#
# ``Dmtx_LIBRARIES``
#     the libraries used to link datamatrix.
#     This can be passed to target_link_libraries instead of
#     the ``Dmtx::Dmtx`` target.
#
# If ``Dmtx_FOUND`` is TRUE, the following imported target
# will be available:
#
# ``Dmtx::Dmtx``
#     The datamatrix library.
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

find_path(Dmtx_INCLUDE_DIRS dmtx.h)

find_library(Dmtx_LIBRARIES NAMES dmtx)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(Dmtx
    FOUND_VAR Dmtx_FOUND
    REQUIRED_VARS Dmtx_LIBRARIES Dmtx_INCLUDE_DIRS
)

if(Dmtx_FOUND AND NOT TARGET Dmtx::Dmtx)
  add_library(Dmtx::Dmtx UNKNOWN IMPORTED)
  set_target_properties(Dmtx::Dmtx PROPERTIES
  IMPORTED_LOCATION "${Dmtx_LIBRARIES}"
  INTERFACE_INCLUDE_DIRECTORIES "${Dmtx_INCLUDE_DIRS}")
endif()

mark_as_advanced(Dmtx_INCLUDE_DIRS Dmtx_LIBRARIES)

include(FeatureSummary)
set_package_properties(Dmtx PROPERTIES
  URL "https://github.com/dmtx/libdmtx"
  DESCRIPTION "The Datamatrix library"
)

