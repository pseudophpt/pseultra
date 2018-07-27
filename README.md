# pseultra ![Download total](https://img.shields.io/github/downloads/pseudophpt/pseultra/total.svg) ![Contributors](https://img.shields.io/github/contributors/pseudophpt/pseultra.svg) ![License](https://img.shields.io/github/license/pseudophpt/pseultra.svg)
`pseultra` is a collection of tools used to develop software for the N64 that is simple to use, extensive in nature, and does not infringe the copyright of Nintendo's intellectual property. Currently, pseultra comes with the following tools:

- `boot`: Custom IPL2 bootcode that can be implemented in replacement of Nintendo's original bootcode
- `bootcsum`: Tools for calculating and finding collisions for the checksum used on the IPL3 bootcode
- `makerom`: Tool to create an N64 rom file given object files

## Getting started

### Prerequisites

To use `pseultra`, you need a native C toolchain, as well as a toolchain for compiling for the MIPS VR4300 architecture 

### Installing

To install `pseultra`, just `make` inside the root directory, or to install individual tools, `make` inside their respective directories

## Testing

To test `pseultra`, first make the tool you'd like to test from the root directory using `make -C <tool_name>`, and then test it from the root directory with `<tool_name>/unit-tests/test`

## Contributing

Please read [CONTRIBUTING.md](CONTRIBUTING.md) details on our code of conduct, and the process for submitting pull requests to us.

## Authors

- **pseudophpt**

See also the list of [contributors](https://github.com/pseudophpt/pseultra/graphs/contributors) who participated in this project.

## Versioning

`pseultra` uses the following version specification:

`<major>.<minor>-<year>.<month>.<day>`

Major releases are for large changes, additions, or removals of functionality. Minor releases are for bug fixes, code organization, and removal of deprecated functionality.

## License

This project is licensed under the BSD-3-Clause License - see the LICENSE.md file for details

## Acknowledgements

- **Nabile Rahmani** and **fraser** for their help with regards to various PIF ROM related questions
- **glankk** for helping me with general N64 and `gcc` related questions

