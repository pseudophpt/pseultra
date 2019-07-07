import os

env = Environment (ENV = os.environ)

prefix = env.GetOption('prefix')
path = Dir('.').abspath

env.Install(
    target = prefix + '/include',
    source = [
        path + '/include/n64.sx',
        path + '/include/mips.sx',
        path + '/include/n64.h',
        path + '/include/util.h',
        path + '/include/elf.h',
        path + '/include/ints.h',
    ]
)

SConscript('#/tools/SConscript')
SConscript('#/n64/SConscript')
