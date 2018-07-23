#
# This file was derived from the 'Hello World!' example recipe in the
# Yocto Project Development Manual.
#

DESCRIPTION = "LED blink application"
SECTION = "examples"
DEPENDS = ""
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://sysup-1.0;md5=4bebd1e95c010cb58972e31ed19e8206"

# This tells bitbake where to find the files we're providing on the local filesystem
FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}-${PV}:"

# Use local tarball
SRC_URI = "file://sysup-${PV}"

# Make sure our source directory (for the build) matches the directory structure in the tarball
S = "${WORKDIR}"

do_install() {
	install -d ${D}${bindir}
	install -m 0775 sysup-${PV} ${D}${bindir}
}

