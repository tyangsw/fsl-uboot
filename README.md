# fsl-uboot 
your SDK installation has been placed in
/home/dev1/nxp/QorIQ-SDK-V2.0-20160527-yocto, please execute following steps to continue:
 
    $ cd /home/dev1/nxp/QorIQ-SDK-V2.0-20160527-yocto
    $ ./sources/meta-freescale/scripts/host-prepare.sh
      Install required host pkgs to run Yocto. Use option -f to run non-interactively.
    $ . ./fsl-setup-env -h
      Get help for creating build project
 
apply patch
$ tar -xjf SDK-V2.0-1703.tar.bz2  
$ ./SDK-V2.0-1703/install
 
build
bitbake <image-target>
 
Building u-boot from Freescale git
 
http://git.freescale.com/git/cgit.cgi/ppc/sdk/u-boot.git/
TAG fsl-sdk-v2.0-1703 
 
compile the PPC toolchain from yocto
 1028  cd build_t2080rdb 
 1029  bitbake fsl-toolchain
    
 
 
 Setup toolchain enviroment 
Source /nxp/fsl-qoriq/2.0
 Build U-boot source
export ARCH=powerpc
export CROSS_COMPILE=powerpc-fsl-linux-
 
#build T2028RDB target board 
make T2080RDB_defconfig
make
 
#build 68PPC2 target board
make NAI68PPC2_defconfig
make


Load uboot debug symobl
loadsym /home/dev1/nxp/u-boot-fsl-sdk-v2.0-1703/u-boot
setpicloadaddr 0xfff40000
