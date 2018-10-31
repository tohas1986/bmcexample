

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI += " \
           file://linux-aspeed_dev-i2c.patch \
           file://linux-aspeed_faraday.patch \
           "

