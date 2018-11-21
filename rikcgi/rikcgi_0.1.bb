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
	   file://server_on.sh \
	   file://setfans.sh \
	   file://sensors_get.sh \
	   file://sensors_get2log.sh \
	   file://autofan.sh \
	   file://fanmode.sh \
	   file://netconfig.sh \
	   file://power.sh \
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
  install -m 777 server_on.sh ${dst}/
  install -m 777 setfans.sh ${dst}/
  install -m 777 sensors_get.sh ${dst}/
  install -m 777 sensors_get2log.sh ${dst}/
  install -m 777 autofan.sh ${dst}/
  install -m 777 fanmode.sh ${dst}/
  install -m 777 netconfig.sh ${dst}/
  install -m 777 power.sh ${dst}/
  ln -snf ${dst}/httpd_test.cgi ${bin}/rikcgi
}

FBPACKAGEDIR = "/www/pages"

FILES_${PN} = "${FBPACKAGEDIR} /www/bin"

