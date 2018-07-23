#
# This file was derived from the 'Hello World!' example recipe in the
# Yocto Project Development Manual.
#

DESCRIPTION = "Simple helloworld application"
SECTION = "examples"
DEPENDS = ""
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://echoprint;md5=6bd021b27ff7ae3a9adb22f8a462889e"

# This tells bitbake where to find the files we're providing on the local filesystem
FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}-${PV}:"

# Use local tarball
SRC_URI = "file://echoprint-${PV}.tar.gz"

# Make sure our source directory (for the build) matches the directory structure in the tarball
#S = "${WORKDIR}/echoprint-${PV}"

#inherit autotools

# The autotools configuration I am basing this on seems to have a problem with a race condition when parallel make is enabled
PARALLEL_MAKE = ""

do_install() {
  dst="/usr/bin"
  install -d $dst
}
