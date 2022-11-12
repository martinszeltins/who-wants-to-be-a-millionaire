millionaire_sources = [
    'main.c',
    'millionaire-application.c',
    'millionaire-gameplay.c',
    'millionaire-window.c',
]

millionaire_deps = [
    dependency('gtk4'),
    dependency('libadwaita-1'),
]

# Generate UI files from blueprint files.
blueprints = custom_target('blueprints',
    input: files(
        'millionaire-window.blp',
    ),
    output: '.',
    command: [find_program('blueprint-compiler'), 'batch-compile', '@OUTPUT@', '@CURRENT_SOURCE_DIR@', '@INPUT@'],
)

millionaire_sources += gnome.compile_resources('millionaire-resources',
    'millionaire.gresource.xml',
    dependencies: blueprints,
    c_name: 'millionaire'
)

executable('millionaire', millionaire_sources,
    dependencies: millionaire_deps,
    install: true,
)
