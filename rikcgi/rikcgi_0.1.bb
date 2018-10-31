# Copyright 2014-present Facebook. All Rights Reserved.
#
# This program file is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the
# Free Software Foundation; version 2 of the License.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
# for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program in a file named COPYING; if not, write to the
# Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor,
# Boston, MA 02110-1301 USA
#

SUMMARY = "Terminal Multiplexer"
DESCRIPTION = "Functions for httpd requests server"
SECTION = "base"
PR = "r1"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://Makefile;md5=dab47dd8221aba77db5cbfd76dbff5eb"

SRC_URI = "file://httpd_test.c \
           file://Makefile \
	   file://httpd_wellcome.sh \
          "

S = "${WORKDIR}"

pkgdir = "rikcgi"

do_install() {
  dst="${D}/www/pages"
  bin="${D}/www/bin"
  install -d $dst
  install -d $bin
  install -m 755 httpd_test.cgi ${dst}/
  install -m 777 httpd_wellcome.sh ${dst}/
  ln -snf ${dst}/httpd_test.cgi ${bin}/rikcgi
}

FBPACKAGEDIR = "/www/pages"

FILES_${PN} = "${FBPACKAGEDIR} /www/bin"
