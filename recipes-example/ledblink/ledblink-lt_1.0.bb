#
# This file was derived from the 'Hello World!' example recipe in the
# Yocto Project Development Manual.
#

DESCRIPTION = "LED blink application"
SECTION = "examples"
DEPENDS = ""
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://ledblink-1.0;md5=c8873ca97bf943388a19a1732ea308ca"

# This tells bitbake where to find the files we're providing on the local filesystem
FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}-${PV}:"

# Use local tarball
SRC_URI = "file://ledblink-${PV}"

# Make sure our source directory (for the build) matches the directory structure in the tarball
S = "${WORKDIR}"

do_install() {
	install -d ${D}${bindir}
	install -m 0775 ledblink-${PV} ${D}${bindir}
}

