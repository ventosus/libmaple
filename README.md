# Inofficial F3-port of _LeafLabs libmaple_

## What?
_... is this repository all about ..._

This is an inofficial port of [LeafLabs libmaple](http://leaflabs.com/docs/libmaple.html) to the [F3 series](http://www.st.com/web/catalog/mmc/FM141/FM141/SC1169/SS1576) of STM32 ARM Cortex M4 microcontrollers of ST Microelectronics.

It introduces support to libmaple for the STM32F30xxx variants, namely:

- STM32F302CB
- STM32F302CC
- STM32F302RB
- STM32F302RC
- STM32F302VB
- STM32F302VC
- STM32F303CB
- STM32F303CC
- STM32F303RB
- STM32F303RC
- STM32F303VB
- STM32F303VC

Have a look at the README in this very folder to learn more about libmaple proper in general.

## Why?
_... does this port exist ..._

libmaple initially supported only the F1 series (ARM Cortex M3), later official and inofficial ports for the F2 and F4 series were added. In the meantime, ST has released the F3 series (ARM Cortex M4). Nice thing about the F3 series is that they are pin compatible with the F1 series, share most of the peripherals with the latter, have a dedicated floating-point-unit, the M4 core comes with an arsenal of DSP and SIMD instructions, faster (and up to twice as many) ADCs, a DAC also on the low-density chips, additionally has onchip OpAmps and comparators and generally has more RAM and FLASH memory for the same package.

From a hardware perspective, a given chip from the F3 series therefore can be used as a drop-in replacement in a design which was based on the F1 series (and offers a lot more possibilities).

Open designs compatible with the F3 series can be found in the [openstm32hw](https://github.com/gbulmer/openstm32hw) repository and their discussion at the LeafLabs [forum](http://forums.leaflabs.com/topic.php?id=10410).

From the software perspective, however, a couple of peripheral drivers of libmaple needed to be adapted slightly, some even written from scratch to be compatible with the F3 series. And an inofficial F3-port of libmaple was born...

There is a corresponding thread about the port at the LeafLabs [forum](http://forums.leaflabs.com/topic.php?id=11883), too.

## How?
_... is this library set-up ..._

The F3-port of libmaple can be used as a drop-in replacemont of libmaple proper. Use it with the [Linux/OS-X](http://leaflabs.com/docs/unix-toolchain.html) or [Windows](http://static.leaflabs.com/pub/leaflabs/maple-docs/snapshots/2012-09-04/unix-toolchain-win-setup.html) unix toolchain with the following modifications:

- use the [lauchpad gcc-arm-embedded](https://launchpad.net/gcc-arm-embedded) toolchain instead
- check out the F3 branch of the author's libmaple fork (this very repository)
- use a recent version (0.7) of [dfu-util](http://dfu-util.gnumonks.org/) with support for DfuSe (ST's extended DFU protocol)

##### Clone from scratch:

    git clone https://github.com/ventosus/libmaple.git libmaple
    cd libmaple
    git checkout F3

##### Or add F3 branch to an already cloned libmaple proper:

    $ cd libmaple
    $ git remote add ventosus https://github.com/ventosus/libmaple.git
    $ git checkout -b F3 ventosus/F3

##### Build for a given F3 chip variant
    $ cd libmaple
    $ export BOARD=F303CC
    $ export MEMORY_TARGET=jtag
    $ make

The default memory target of libmaple proper is the _flash_ target, which adds a code offset to not overwrite the custom boot loader used for the F1 series. As the F3 series come with an embedded boot loader, the _flash_ target is of no use here, build for the _jtag_ target instead.

##### Add udev rule on Linux to give users access to the DfuSe boot loader
    /etc/udev/rules.d/46-DfuSe.rules
    --------------------------------
    ATTRS{idProduct}=="df11", ATTRS{idVendor}=="0483", MODE="664", GROUP="uucp", SYMLINK+="DfuSe"

##### The [zadig tool](http://zadig.akeo.ie/) has been shown to be valuable to install all neded USB drivers on Windows.

##### Get your device into DfuSe bootloader mode by doing this at boot:
- pull-up Boot0 pin (will select system memory as boot space and start the bootloader)
- pull-up USB\_DP pin with 1.5 kOhm (will select DfuSe bootloader instead of Serial bootloader)

This should get the device into DfuSe bootloader mode and the device enumerated on the host:

    $ lsusb
    Bus 003 Device 020: ID 0483:df11 STMicroelectronics STM Device in DFU ModeBus 003 Device 020: ID 0483:df11 STMicroelectronics STM Device in DFU Mode

##### Download to the microcontroller via the embedded DfuSe boot loader
    $ cd libmaple
    $ dfu-util -a 0 -d 0483:df11 -s 0x08000000:leave -D build/F303CC.bin

The F3 series use an extended DFU protocol (DfuSe). DfuSe needs an explicit target memory address the built sketch is destined for. This address needs to be provided to dfu-util (-s). The _:leave_ hook triggers a jump to user code after flashing, without it, the device will remain in bootoader mode.

## Where?
_... are the incompatibilities to libmaple proper ..._

### Wirish
The F3-port is fully compatible with libmaple's high-abstraction (aka Arduino-compatibility) layer called _Wirish_.

### libmaple
As some peripherals were extended and others completely redesigned from the F1 to the F3 series, the F3-port of the libmaple peripheral API had to be changed and/or extended accordingly. Find the changes followingly.

##### GPIO peripheral
(under construction)

##### ADC peripheral
(under construction)

##### SPI peripheral
(under construction)

##### I2C peripheral
(under construction)

Peripherals with no API changes are not listed above and can be used as ever.

## Who?
_... is to blame for all bugs ..._

The author of this port is in no way associated with LeafLabs. The author thinks that libmaple is one of few projects that excel at providing the embedded developer with a clean library usable at different levels of abstraction.

As the author moved to the F3 series of chips and wanted to use libmaple there, too, the creation of this port was only logical. The author's code additions to libmaple are put here in the hope that they will be useful to somebody else and released under the same license as libmaple proper (MIT).
