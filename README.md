# pseultra
`pseultra` is a collection of tools used to develop software for the N64 that is simple to use, extensive in nature, and does not infringe the copyright of Nintendo's intellectual property. Currently, pseultra comes with the following tools:

- `boot`: Custom IPL2 bootcode that can be implemented in replacement of Nintendo's original bootcode
- `bootcsum`: Tools for calculating and finding collisions for the checksum used on the IPL3 bootcode

## Getting started

### Prerequisites

To use `pseultra`, you need a native C toolchain, as well as a toolchain for compiling for the MIPS VR4300 architecture. 

### Installing

To install `pseultra`, just `make` inside the root directory, or to install individual tools, `make` inside their respective directories

## License

This project is licensed under the BSD-3-Clause License - see the LICENSE.md file for details

