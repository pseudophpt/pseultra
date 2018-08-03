# Changelog

## [Unreleased](https://github.com/pseudophpt/pseultra/compare/master...develop)

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
