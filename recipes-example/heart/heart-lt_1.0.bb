#
# This file was derived from the 'Hello World!' example recipe in the
# Yocto Project Development Manual.
#

DESCRIPTION = "LED blink application"
SECTION = "examples"
DEPENDS = ""
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://heart-1.0;md5=27d75c24fdea14bc2c2b75d536f26709"

# This tells bitbake where to find the files we're providing on the local filesystem
FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}-${PV}:"

# Use local tarball
SRC_URI = "file://heart-${PV}"

# Make sure our source directory (for the build) matches the directory structure in the tarball
S = "${WORKDIR}"

do_install_append() {
	install -d ${D}${sysconfdir}/init.d
	install -m 755 heart-1.0 ${D}${sysconfdir}/init.d/heart-1.0
	update-rc.d -r ${D} heart-1.0 start 92 S .
}

