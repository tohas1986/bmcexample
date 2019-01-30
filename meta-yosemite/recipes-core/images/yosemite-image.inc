# Copyright 2018-present Facebook. All Rights Reserved.

inherit aspeed_uboot_image

require recipes-core/images/fb-openbmc-image.bb

# Changing the image compression from gz to lzma achieves 30% saving (~3M).
IMAGE_FSTYPES += "cpio.lzma.u-boot"
UBOOT_IMAGE_ENTRYPOINT = "0x40008000"

# Include modules in rootfs
IMAGE_INSTALL += " \
  packagegroup-openbmc-base \
  openbmc-utils \
  sensor-setup \
  rikgpio \
  lighttpd \
  rikcgi \
  rikfans \
  riknet \
  i2c-tools \
  fan-ctrl \
  rikor-fru \
  dscan \
  "

IMAGE_FEATURES += " \
  "

DISTRO_FEATURES += " \
  "
