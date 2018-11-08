# Copyright 2018-present Facebook. All Rights Reserved.

inherit aspeed_uboot_image

require recipes-core/images/fb-openbmc-image.bb

# Changing the image compression from gz to lzma achieves 30% saving (~3M).
IMAGE_FSTYPES += "cpio.lzma.u-boot"
UBOOT_IMAGE_ENTRYPOINT = "0x40008000"

# Include modules in rootfs
IMAGE_INSTALL += " packagegroup-openbmc-base"
# IMAGE_INSTALL += " healthd"
# IMAGE_INSTALL += " fbutils"
# IMAGE_INSTALL += " fan-util"
# IMAGE_INSTALL += " fscd"
IMAGE_INSTALL += " watchdog-ctrl"
IMAGE_INSTALL += " sensor-setup"
# IMAGE_INSTALL += " ipmid"
# IMAGE_INSTALL += " packagegroup-openbmc-net"
# IMAGE_INSTALL += " packagegroup-openbmc-python3"
# IMAGE_INSTALL += " packagegroup-openbmc-rest3"
# IMAGE_INSTALL += " fruid"
# IMAGE_INSTALL += " ipmbd"
# IMAGE_INSTALL += " bic-cached"
# IMAGE_INSTALL += " bic-util"
# IMAGE_INSTALL += " yosemite-sensors"
# IMAGE_INSTALL += " sensor-util"
# IMAGE_INSTALL += " sensor-mon"
# IMAGE_INSTALL += " gpiod"
# IMAGE_INSTALL += " gpiointrd"
# IMAGE_INSTALL += " front-paneld"
# IMAGE_INSTALL += " power-util"
# IMAGE_INSTALL += " mterm"
# IMAGE_INSTALL += " cfg-util"
# IMAGE_INSTALL += " fw-util"
# IMAGE_INSTALL += " fpc-util"
# IMAGE_INSTALL += " me-util"
# IMAGE_INSTALL += " log-util"
# IMAGE_INSTALL += " lldp-util"
# IMAGE_INSTALL += " spatula"
# IMAGE_INSTALL += " openbmc-utils"
# IMAGE_INSTALL += " conf-util"
# IMAGE_INSTALL += " ncsi-util"

# IMAGE_FEATURES += " ssh-server-openssh"
# IMAGE_FEATURES += " tools-debug"


# DISTRO_FEATURES += " ext2"
# DISTRO_FEATURES += " ipv6"
# DISTRO_FEATURES += " nfs"
# DISTRO_FEATURES += " usbgadget"
# DISTRO_FEATURES += " usbhost"
 

###################################
# Свои проекты
##################################
# IMAGE_INSTALL += " tprint-lt"
# IMAGE_INSTALL += " heart-lt" 
# IMAGE_INSTALL += " bbhello" 
# IMAGE_INSTALL += " heartd"
# IMAGE_INSTALL += " rikor-sensors"



###################################
### Исходная последовательность
###################################

# # Include modules in rootfs
# IMAGE_INSTALL += " \
#  packagegroup-openbmc-base \
#  healthd \
#  fbutils \
#  fan-util \
#  fscd \
#  watchdog-ctrl \
#  sensor-setup \
#  ipmid \
#  packagegroup-openbmc-net \
#  packagegroup-openbmc-python3 \
#  packagegroup-openbmc-rest3 \
#  fruid \
#  ipmbd \
#  bic-cached \
#  bic-util \
#  yosemite-sensors \
#  sensor-util \
#  sensor-mon \
#  gpiod \
#  gpiointrd \
#  front-paneld \
#  power-util \
#  mterm\
#  cfg-util \
#  fw-util \
#  fpc-util \
#  me-util \
#  log-util \
#  lldp-util \
#  spatula \
#  openbmc-utils \
#  conf-util \
#  ncsi-util \
#  "

# IMAGE_FEATURES += " \
#  ssh-server-openssh \
#  tools-debug \
#  "

# DISTRO_FEATURES += " \
#  ext2 \
#  ipv6 \
#  nfs \
#  usbgadget \
#  usbhost \
#  "

