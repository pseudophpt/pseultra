#
# pseultra/headers/n64.s.h
# N64 definitions for assembler
# 
# (C) pseudophpt 2018
#

#
# Coprocessor 0 (COP0) Registers
#

.set Index,	$0
.set Random, $1
.set EntryLo0, $2
.set EntryLo1, $3
.set Context, $4
.set PageMask, $5
.set Wired,	$6
# 7 reserved
.set BadVAddr, $8
.set Count, $9
.set EntryHi, $10
.set Compare, $11
.set Status, $12
.set Cause, $13
.set EPC, $14
.set PRId, $15
.set Config, $16
.set LLAddr, $17
.set WatchLo, $18
.set WatchHi, $19
.set XContext, $20
# 21 - 26 reserved
.set CacheErr, $27
.set TagLo, $28
.set TagHi, $29
.set ErrorEPC, $30
# 31 Reserved
