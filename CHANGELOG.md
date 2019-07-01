# Changelog

## [Unreleased](https://github.com/pseudophpt/pseultra/compare/master...develop)

## [1.4.0](https://github.com/pseudophpt/pseultra/compare/v1.3.0...v1.4.0) - 2019-07-01

### Added
- Shaded triangles
- Ambient lighting
- Diffuse lighting

### Fixed
- Bug in which DzDx was written to DzDy

## [1.3.0](https://github.com/pseudophpt/pseultra/compare/v1.2.0...v1.3.0) - 2019-06-09

### Added
- PSM3D PopMtx command
- Math library
- PSM3D Z-buffered triangles
- PSM3D Textured triangles
- Triangle backface culling
- Triangle clipping

### Changed
- PSM3D matrix stack pointer to be stored in register instead of DMEM
- Vertex cache (x, y) pair is now aligned to the integer, saving calculation time

### Fixed
- Bug in sign extension of RSP load/store offsets
- Bug in VMOV instructions using incorrect element index type
- Fix matrix size

### Removed
- Newton-Raphson iteration for textured rectangles

## [1.2.0](https://github.com/pseudophpt/pseultra/compare/v1.1.0...v1.2.0) - 2018-09-02

### Added
- Debug functionality
- RSP vector load/store fixer
- PSM3D microcode

### Fixed
- Bug involving a coprocessor 0 delay slot which would cause arbitrary kernel reg data to be written to cop0 status reg, and usually an xtlb exception
- Bug in util.h where the macro input to endian switchers isn't wrapped

## [1.1.0](https://github.com/pseudophpt/pseultra/compare/v1.0.1...v1.1.0) - 2018-08-18

### Added
- Memory zeroing functionality (see osZeroMemory())
- Interrupt handling for RCP DP interrupts
- PI functionality (DMA)
- VI functionality (buffer swapping)
- Timer interrupt handler
- PIF initialization in OS
- Caching operations

### Changed
- Improve documentation on N64 constants and prepend N64_

### Fixed
- Bug involving the use of an incorrect kernel register, which causes unknown behavior (usually an XTLB exception) in the exception unmasking routine
- Bug involving exception handlers being stored only in DCache at vector locations, causing any exception to not reach its handler

### Removed
-  Documentation build from `scons` (users may do it manually now by running `doxygen`)

## [1.0.1](https://github.com/pseudophpt/pseultra/compare/v1.0.0...v1.0.1) - 2018-08-02

### Added
- C Preprocessing for assembly
- Documentation using `doxygen`

### Changed
- SemVer for versioning
- SConstruct files are now more flexible to allow building from any directory
- Stack size is now 16kb

### Fixed
- Destination pointer is now checked for alignment in osCopyMemory()

## 1.0.0 - 2018-08-01

### Added
- Tools for calculating and colliding the checksum used in the n64 PIF ROM code to verify bootcode
- A tool for generating ROM images given object files and a specification file
- Bootcode to replace Nintendo's default IPL3 bootcode
- An OS providing functionality with the N64 hardware
