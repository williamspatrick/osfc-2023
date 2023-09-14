project('asg-2023', 'cpp', 'c',
    meson_version: '>=1.1.1',
    default_options: [
        'cpp_std=c++23',
    ],
    version: '1.0.0',
)

sdbusplus_dep = dependency('sdbusplus')
sdbusplusplus_prog = find_program('sdbus++', native: true)
sdbuspp_gen_meson_prog = find_program('sdbus++-gen-meson', native: true)
sdbusplusplus_depfiles = files()
if sdbusplus_dep.type_name() == 'internal'
    sdbusplusplus_depfiles = subproject('sdbusplus').get_variable('sdbusplusplus_depfiles')
endif

generated_sources = []
generated_others = []
yaml_sources = []

subdir('gen')
subdir('gen/com')

client = executable(
    'client',
    'client.cpp',
    generated_sources,
    include_directories: include_directories('gen'),
    dependencies: [
        sdbusplus_dep,
    ],
)

server = executable(
    'server',
    'server.cpp',
    generated_sources,
    include_directories: include_directories('gen'),
    dependencies: [
        sdbusplus_dep,
    ],
)

