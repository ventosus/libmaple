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
As some peripherals were extended and others completely redesigned from the F1 to the F3 series, the F3-port of the libmaple peripheral API had to be changed and/or extended accordingly. Find the changes followingly. Peripherals with no API changes are not listed below and can be used as ever.

##### GPIO peripheral
(under construction)

The F3 GPIO peripheral is the same as on the F2 series, but different from the F1 series. There are 4 general modes, a pin can be in INPUT, OUTPUT, ANALOG or ALTERNATE-FUNCTION mode. There are 3 additional parameters which can affect a pin's configuration: push/pull vs open-drain and low-medium-high speed for output configurations, weak push-up and push-down resistors for both output and input configurations.

To set all this modes, there is a new function:

    void gpio_set_modef(struct gpio_dev *dev, uint8 bit, gpio_pin_mode mode, unsigned flags);

Mode can be set to:

- GPIO\_MODE\_INPUT // digital input mode
- GPIO\_MODE\_OUTPUT // digital output mode
- GPIO\_MODE\_AF // alternate function mode
- GPIO\_MODE\_ANALOG // analog input/output mode

Flags can be set to a combination of individual flags for output type, output speed and pull-up/pull-down (pupd):

- GPIO\_MODEF\_TYPE\_PP // push-pull
- GPIO\_MODEF\_TYPE\_OD // open-drain
- GPIO\_MODEF\_SPEED\_LOW // 2MHz
- GPIO\_MODEF\_SPEED\_MED // 10MHz
- GPIO\_MODEF\_SPEED\_HIGH // 50MHz
- GPIO\_MODEF\_PUPD\_NONE // neither pull-up nor pull-down
- GPIO\_MODEF\_PUPD\_PU // pull-up
- GPIO\_MODEF\_PUPD\_PD // pull-down

There is also a compatibility function, which sets a pins mode to high speed as its only flag:

    static inline void gpio_set_mode(struct gpio_dev *dev, uint8 bit, gpio_pin_mode mode) {
			gpio_set_modef(dev, bit, mode, GPIO_MODEF_SPEED_HIGH);
		}

Apart from the extended modes, the alternate functions system was changed, too. A dedicated alternate function multiplexer was introduced. To enable an alternate function for a given pin (e.g. hardware SPI), the pin's mode firstly has to be set to the ALTERNATE-FUNCTION mode (with additional extended types, like push-pull and speed), and then the right alternate function channel needs to be activated.

    void gpio_set_af(struct gpio_dev *dev, uint8 bit, gpio_af af);

The alternate function can be set to one of 16 channels:

- GPIO\_AF\_0
- GPIO\_AF\_1
- GPIO\_AF\_2
- GPIO\_AF\_3
- GPIO\_AF\_4
- GPIO\_AF\_5
- GPIO\_AF\_6
- GPIO\_AF\_7
- GPIO\_AF\_8
- GPIO\_AF\_9
- GPIO\_AF\_10
- GPIO\_AF\_11
- GPIO\_AF\_12
- GPIO\_AF\_13
- GPIO\_AF\_14
- GPIO\_AF\_15

Upon code migration from libmaple F1 to F3, you need to migrate all GPIO code concerning the setting of the mode and alternate function of a given pin. Some peripherals have a handy function PERIPHERAL\_config\_gpios which does this for you transparently.

##### ADC peripheral
(under construction)

The ADC peripheral is new and has been written from scratch. It is the part of the F3-port with the most changes and incompatibilities. If you want to migrate ADC code from the F1 series, you will have to adapt most of it, especially if you used DMA and dual sample mode.

The STM32F302xx have two 2 ADCs (ADC1, ADC2), whereas the STM32F303xx have 4 ADCs (ADC1, ADC2, ADC3, ADC4). The ADCs are grouped into a master (ADC1, ADC3) and its slave (ADC2, ADC4), each. Each ADC can be configured independently by manipulating the individual registers. Or a master and slave can be put in one of the dual modes and configured by manipulating a special master-slave common register.

The F3 series know no SCAN flag, the adc\_scan\_enable and adc\_scan\_disable functions therefore do nothing. There are separate end-of-conversion (EOC) and an end-of-sequence (EOS) interrupt flags instead, that can be masked.

The new ADCs can be run in different bit resolutions, there is a new API function to set these, to be called when the ADC is disabled.

    void adc_set_resolution(const adc_dev *dev, adc_resolution res);

These are the four possible resolutions:

- ADC\_RESOLUTION\_12\_BIT
- ADC\_RESOLUTION\_10\_BIT
- ADC\_RESOLUTION\_8\_BIT
- ADC\_RESOLUTION\_6\_BIT
	
Before the ADCs can be enabled, first their voltage regulators have to be enabled, this is checked-for and done automatically for you by libmaple. Nevertheless, there are two new functions for doing this manually.

		void adc_regulator_enable(const adc_dev *dev);
		void adc_regulator_disable(const adc_dev *dev);

There is a convenience function to set up conversion sequences.

    void adc_set_conv_seq(const adc_dev *dev, const uint8 *channels, uint8 len);

The ADC peripherals can be configured in two main clock modes, asynchronous or synchronous. In asynchronous mode, the ADC peripherals are driven by PCLK, in synchronous mode, they are driven by the ADC bus clock AHBCLK.

In asynchronous mode, the prescaler can be set to:

- ADC\_PRE\_PCLK\_DIV\_1 	
- ADC\_PRE\_PCLK\_DIV\_2 	
- ADC\_PRE\_PCLK\_DIV\_4 	
- ADC\_PRE\_PCLK\_DIV\_6 	
- ADC\_PRE\_PCLK\_DIV\_8 	
- ADC\_PRE\_PCLK\_DIV\_10 
- ADC\_PRE\_PCLK\_DIV\_12 
- ADC\_PRE\_PCLK\_DIV\_16 
- ADC\_PRE\_PCLK\_DIV\_32 
- ADC\_PRE\_PCLK\_DIV\_64 
- ADC\_PRE\_PCLK\_DIV\_128
- ADC\_PRE\_PCLK\_DIV\_256

In synchronous mode, the prescaler can be set to:

- ADC\_PRE\_AHBCLK\_DIV\_1
- ADC\_PRE\_AHBCLK\_DIV\_2
- ADC\_PRE\_AHBCLK\_DIV\_4

The function to do so (it will put the ADC in asynchronous or synchronous mode automatically, according to the argument):

    void adc_set_prescaler(adc_prescaler pre);

In it's default configuration, the F3-port makes use of the asynchronous mode with prescaler ADC\_PRE\_PCLK\_DIV\_1 (set in libmaple/wirish/stm32f3/boards\_setup.cpp).

The sample rates are expressed relative to the clock source and prescalers used, by default it is set to 181.5 (again in libmaple/wirish/stm32f3/boards\_setup.cpp).

- ADC\_SMPR\_1\_5 
- ADC\_SMPR\_2\_5 
- ADC\_SMPR\_4\_5 
- ADC\_SMPR\_7\_5 
- ADC\_SMPR\_19\_5
- ADC\_SMPR\_61\_5
- ADC\_SMPR\_181\_5
- ADC\_SMPR\_601\_5

They are set with:

    void adc_set_sample_rate(const adc_dev *dev, adc_smp_rate smp_rate);

The ADC can be triggered by software or external signals:

- ADC\_EXTTRIG\_MODE\_SOFTWARE
- ADC\_EXTTRIG\_MODE\_HARDWARE\_RISING
- ADC\_EXTTRIG\_MODE\_HARDWARE\_FALLING
- ADC\_EXTTRIG\_MODE\_HARDWARE\_BOTH

The mode is set with:

    void adc_set_exttrig(const adc_dev *dev, adc_exttrig_mode mode);

The various hardware triggers (TIMERx or EXTIx), can be selected with:

    void adc_set_extsel(const adc_dev *dev, adc_extsel_event event);

When using DMA in individual mode, you want to enable DMA and run the ADC in circular mode:

    ADC3_BASE->CFGR |= ADC_CFGR_DMAEN; // enable DMA mode
    ADC3_BASE->CFGR |= ADC_CFGR_DMACFG; // enable DMA circular mode

When ADCs are used in dual mode, DMA must be configured specially in the master-slave common register

- ADC\_MDMA\_MODE\_DISABLE
- ADC\_MDMA\_MODE\_ENABLE\_12\_10\_BIT
- ADC\_MDMA\_MODE\_ENABLE\_8\_6\_BIT

e.g. set dual DMA mode for 10 or 12-bit conversions:

    ADC12_BASE->CCR |= ADC_MDMA_MODE_ENABLE_12_10_BIT; // enable DMA in 10/12-bit dual mode

Dual mode itself offers a variety of conversion schemes, choose the right one for you.

- ADC\_MODE\_INDEPENDENT
- ADC\_MODE\_DUAL\_REGULAR\_INJECTED
- ADC\_MODE\_DUAL\_REGULAR\_ALTERNATE\_TRIGGER
- ADC\_MODE\_DUAL\_INJECTED\_ONLY
- ADC\_MODE\_DUAL\_REGULAR\_ONLY
- ADC\_MODE\_DUAL\_INTERLEAVED\_ONLY
- ADC\_MODE\_DUAL\_ALTERNATE\_TRIGGER\_ONLY

e.g. sample only regular channels of master and slave concurrently:

    ADC12_BASE->CCR |= ADC_MODE_DUAL_REGULAR_ONLY;

Of course, there still is a simple function to read out a single channel:

    uint16 adc_read(const adc_dev *dev, uint8 channel);

By default, the ADCs of the F3-port are brought up in single software mode, the corresponding function that does so is:

    void adc_enable_single_swstart(const adc_dev *dev);

The pins, the analog signal is sampled on, needs to be put into ANALOG mode, there is a convenience function to do so:

    void adc_config_gpio(const adc_dev *ignored, gpio_dev *gdev, uint8 bit);

##### SPI peripheral
(under construction)

The SPI peripheral on the F3 series has been extended in its functionality. It supports an arbitrary data size from 4 to 16 bits. It does so by introducing a 32-bit FIFO for both the transmitting and receiving endpoints. The handling of the FIFO needs some more control logic, which has been added to the F3-port. However, if you want to port F1-SPI-DMA code, you need to add this logic yourself.

This is the additional API function to set the data size (to be called before spi\_enable):

    void spi_data_size(struct spi_dev *, spi_ds);

Where the data size can be set to the following values:

- SPI\_DATA\_SIZE\_DEFAULT // 8 BIT
- SPI\_DATA\_SIZE\_4\_BIT
- SPI\_DATA\_SIZE\_5\_BIT
- SPI\_DATA\_SIZE\_6\_BIT
- SPI\_DATA\_SIZE\_7\_BIT
- SPI\_DATA\_SIZE\_8\_BIT
- SPI\_DATA\_SIZE\_9\_BIT
- SPI\_DATA\_SIZE\_10\_BIT
- SPI\_DATA\_SIZE\_11\_BIT
- SPI\_DATA\_SIZE\_12\_BIT
- SPI\_DATA\_SIZE\_13\_BIT
- SPI\_DATA\_SIZE\_14\_BIT
- SPI\_DATA\_SIZE\_15\_BIT
- SPI\_DATA\_SIZE\_16\_BIT

##### I2C peripheral
(under construction)

The F3 series have gotten a new I2C peripheral. It is much cleaner in design compared to the F1 series. An implementation for master mode has been written from scratch. The new implementation did not introduce any API changes, you can use the peripheral as ever, but it should be regarded as _experimental_, that's why it's listed here. It is planned to add a slave mode, too.

##### CCM: core coupled memory
(under construction)

The F3 series have 8kB of core coupled memory. This is memory that is only accessible from the CPU, not from DMA. This memory can either be used to store data or code, bot not both at the same time. Storing data simply extends your RAM. Storing data can considerably speed up code execution, as core coupled memory exihibits zero wait-state compared to flash memory that has a wait-state of 2 (at the maximal 72MHz). This therefore is the right place to put interrupts and other critical code to get a considerable performance increase. You can tell the linker to put data or code into the core coupled memory with GCC's section attributes or use the already predefined convenience macro \_\_CCM\_\_. To mark code to be put into a given memory section, you have to set the attributes for its prototype definition.

    #define __CCM__ __attribute__((section(".CCM")))

    // put this data into core coupled memory
    uint16_t my_vec [0x400] __CCM__;
    uint16_t my_var __CCM__ = 34U;

    // put this code into core coupled memory for fastest (zero wait-state) execution
    void my_irq(void *dat) __CCM__;
    void my_rq(void *dat) {
        ...
    }

##### OpAmp peripheral
(under construction)

##### Comparator peripheral
(under construction)

## Who?
_... is to blame for all bugs ..._

The author of this port is in no way associated with LeafLabs. The author thinks that libmaple is one of few projects that excel at providing the embedded developer with a clean library usable at different levels of abstraction.

As the author moved to the F3 series of chips and wanted to use libmaple there, too, the creation of this port was only logical. The author's code additions to libmaple are put here in the hope that they will be useful to somebody else and released under the same terms as libmaple proper (MIT license).
