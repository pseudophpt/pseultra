env = Environment ()

prefix = env.GetOption('prefix')
path = Dir('.').abspath

env.Install(
    target = prefix + '/include',
    source = [
        path + '/include/n64.sx',
        path + '/include/mips.sx',
        path + '/include/n64.h',
        path + '/include/util.h'
    ]
)

SConscript('#/tools/SConscript')
SConscript('#/n64/SConscript')
