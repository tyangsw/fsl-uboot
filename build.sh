#!/bin/sh

set -o nounset                                  # Treat unset variables as an error

export CCACHE_PATH=
source /opt/fsl-qoriq/2.0/environment-setup-ppce6500-fsl-linux

export BIN_OUT=6XPPC2
export ARCH=powerpc
export CROSS_COMPILE=powerpc-fsl-linux-

make O=$BIN_OUT mrproper
make O=$BIN_OUT NAI6XPPC2_defconfig 
make O=$BIN_OUT

