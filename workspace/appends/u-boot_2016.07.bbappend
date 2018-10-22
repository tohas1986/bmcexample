FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
FILESPATH_prepend := "/home/tohas/fbook_openbmc/openBMC_rev2/openbmc/build/workspace/sources/u-boot/oe-local-files:"

inherit externalsrc
# NOTE: We use pn- overrides here to avoid affecting multiple variants in the case where the recipe uses BBCLASSEXTEND
EXTERNALSRC_pn-u-boot = "/home/tohas/fbook_openbmc/openBMC_rev2/openbmc/build/workspace/sources/u-boot"
EXTERNALSRC_BUILD_pn-u-boot = "/home/tohas/fbook_openbmc/openBMC_rev2/openbmc/build/workspace/sources/u-boot"

# initial_rev: 6d56928097495d43215c112ba90a71ecbc105cf7
