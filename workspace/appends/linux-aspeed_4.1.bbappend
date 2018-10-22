FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
FILESPATH_prepend := "/home/tohas/fbook_openbmc/openBMC_rev2/openbmc/build/workspace/sources/linux-aspeed/oe-local-files:"

inherit externalsrc
# NOTE: We use pn- overrides here to avoid affecting multiple variants in the case where the recipe uses BBCLASSEXTEND
EXTERNALSRC_pn-linux-aspeed = "/home/tohas/fbook_openbmc/openBMC_rev2/openbmc/build/workspace/sources/linux-aspeed"
SRCTREECOVEREDTASKS = "do_validate_branches do_kernel_checkout do_fetch do_unpack do_patch do_kernel_configme do_kernel_configcheck"

do_configure_append() {
    cp ${B}/.config ${S}/.config.baseline
    ln -sfT ${B}/.config ${S}/.config.new
}

# initial_rev: 2224480c97852fda29bbd0c5eb6effbcfe46ef7a
