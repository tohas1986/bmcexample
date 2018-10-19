#
# This file was derived from the 'Hello World!' example recipe in the
# Yocto Project Development Manual.
#

PR = "r1"

DESCRIPTION = "ADC scanner"
SECTION = "examples"
DEPENDS = ""
LICENSE = "GPL-2"
LIC_FILES_CHKSUM = "file://LICENSE;md5=8264535c0c4e9c6c335635c4026a8022"

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}-${PV}:"

SRCREV = "${AUTOREV}"
#SRC_URI = "git://10.10.0.158/heartd.git;branch=master;protocol=ssh;user=git"
SRC_URI = "file://fadc \
          "

S = "${WORKDIR}/fadc"

export SINC = "${STAGING_INCDIR}"
export SLIB = "${STAGING_LIBDIR}"

# DEPENDS =+ "glib-2.0"

inherit cmake

BBCLASSEXTEND = "native"

# The autotools configuration I am basing this on seems to have a problem with a race condition when parallel make is enabled
PARALLEL_MAKE = ""

# Следующие строки отсюда:
# https://stackoverflow.com/questions/49748528/yocto-files-directories-were-installed-but-not-shipped-in-any-package
# https://lists.yoctoproject.org/pipermail/yocto/2016-January/028127.html
FILES_${PN} += "/etc/fadc/fadc.conf"
FILES_${PN} += "/usr/lib/systemd/system/forking-fadc.service"
FILES_${PN} += "/usr/lib/systemd/system/simple-fadc.service"

do_install_append() {
	install -d ${D}${sysconfdir}/init.d
	install -m 755 ${S}/fadc.init ${D}${sysconfdir}/init.d/fadc.init
	update-rc.d -r ${D} fadc.init defaults
}

