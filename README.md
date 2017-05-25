# Badgerloop Controls: STM32 Development

*Contributors: Vaughn Kottler*

This repository is primarily for work with the STM32 Nucleo 144 F767ZI microcontroller development board.

## Boards Supported

* [Nucleo 144 F767ZI](http://www.mouser.com/ProductDetail/STMicroelectronics/NUCLEO-F767ZI/?qs=7UaJ5Mrpeu0%2F%252bMRranB3%2Fw%3D%3D)

## Environments Supported

* [Keil uVision 5 IDE](http://www2.keil.com/mdk5/uvision/)

## Dependencies

* [ARM's CMSIS (CORE only)](https://www.arm.com/products/processors/cortex-m/cortex-microcontroller-software-interface-standard.php)

Currently the repository does not include dependency source but instead leverages Keil's internal dependency management.

## Development Instructions

Video coming soon.

Note, current executable size is less than 32kB and the free version of Keil can still be used.

1. [Install Keil](https://www.keil.com/demo/eval/arm.htm). You will need to fill out a form to be able to download it, and what you are downloading is a trial version of the software.
2. Open *Edit -> Configurations* and set all tab sizes to 4 spaces.
3. Follow the [instructions](https://kb.wisc.edu/cae/page.php?id=32730) to connect to UW-Madison's Engineering License VPN.
  + If you already have Cisco AnyConnect or another VPN app, connect to `dept-ra-cssc.vpn.wisc.edu` and use the group `ENGINEERING_LICENSING`.
4. Open *File -> License Management* and navigate to the FlexLM License tab. Edit the Flex Server field and enter `8224@license-2.cae.wisc.edu` (this isn't sensitive information as you must already have an active CAE account and authenticate through the VPN).
5. Check *Use Flex Server*, and close the window.
6. Clone this git repository. Open Git Bash or cmd/Terminal (if git is on your path), navigate to a directory that you keep git repositories (i.e. `~/Documents/gitRepos/`) and run `git clone https://github.com/badgerloop-software/st32.git st32dev` (you can name it anything you want).
7. Open `keil/badgerloop.uvprojx` (should be associated with Keil) and attempt to build. If you are successfully authenticated to the licensing server it should build extremely quickly. There should not be any errors.
8. Begin contributing! (:

## Notes on committing

Keil uses a number of project configuration related files, notably `PROJ.uvoptx`, `PROJ.uvprojx` and `RTE/_TARGET/RTE_Components.h`.

It's not always necessary to commit to \*.uv\*\* files as they store information about what files the user has open. Make sure to commit your changes to these files only when you make a change to the project configurations.

## Important Documentation

All useful documentation is kept in a Subversion repository. To download it, simply install Subversion (svn) and run  
`svn co http://svn.badgerloop.com/st32 st32docs`.

## Build Info

Compiler Arguments:

```
--c99 -c --cpu Cortex-M7.fp.dp -D__EVAL -g -O0 --apcs=interwork --split_sections
-I./RTE/_Nucleo144-STM32F767ZI
-IC:/Keil_v5/ARM/PACK/Keil/STM32F7xx_DFP/2.9.0/Drivers/CMSIS/Device/ST/STM32F7xx/Include
-IC:/Keil_v5/ARM/CMSIS/Include
-D__UVISION_VERSION="523" -DSTM32F767xx
-o .\Objects\*.o --omf_browse .\Objects\*.crf --depend .\Objects\*.d
```

Assembler Arguments:

```
--cpu Cortex-M7.fp.dp --pd "__EVAL SETA 1" -g --apcs=interwork 
-I .\RTE\_Nucleo144-STM32F767ZI 
-I C:\Keil_v5\ARM\PACK\Keil\STM32F7xx_DFP\2.9.0\Drivers\CMSIS\Device\ST\STM32F7xx\Include 
-I C:\Keil_v5\ARM\CMSIS\Include 
--pd "__UVISION_VERSION SETA 523" --pd "STM32F767xx SETA 1" --list ".\Listings\*.lst" --xref -o "*.o" --depend "*.d" 
```

Linker Arguments:

```
--cpu Cortex-M7.fp.dp *.o 
--ro-base 0x08000000 --entry 0x08000000 --rw-base 0x20020000 --entry Reset_Handler --first __Vectors --strict --summary_stderr --info summarysizes --map --xref --callgraph --symbols 
--info sizes --info totals --info unused --info veneers 
 --list ".\Listings\badgerloop.map" 
-o .\Objects\badgerloop.axf 
```

