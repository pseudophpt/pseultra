# Changelog

## [Unreleased](https://github.com/pseudophpt/pseultra/compare/master...develop)

### Added
- Debug functionality

### Fixed
- Bug involving a coprocessor 0 delay slot which would cause arbitrary kernel reg data to be written to cop0 status reg, and usually an xtlb exception

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
