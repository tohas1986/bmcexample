


PR = "r1"

DESCRIPTION = "FRU base board"
SECTION = "examples"

DEPENDS += " glibc "

LICENSE = "GPL-2"
LIC_FILES_CHKSUM = "file://LICENSE;md5=8264535c0c4e9c6c335635c4026a8022"

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRCREV = "${AUTOREV}"

SRC_URI = " file://rikor-fru "

S = "${WORKDIR}/rikor-fru"

export SINC = "${STAGING_INCDIR}"
export SLIB = "${STAGING_LIBDIR}"

inherit cmake

BBCLASSEXTEND = "native"

# The autotools configuration I am basing this on seems to have a problem with a race condition when parallel make is enabled
PARALLEL_MAKE = ""

# RDEPENDS += " glibc "

