# Generated file; do not modify.
subdir('Poke')
generated_others += custom_target(
    'com/meta/Poke__markdown'.underscorify(),
    input: [ '../../../yaml/com/meta/Poke.interface.yaml',  ],
    output: [ 'Poke.md' ],
    depend_files: sdbusplusplus_depfiles,
    command: [
        sdbuspp_gen_meson_prog, '--command', 'markdown',
        '--output', meson.current_build_dir(),
        '--tool', sdbusplusplus_prog,
        '--directory', meson.current_source_dir() / '../../../yaml',
        'com/meta/Poke',
    ],
)

