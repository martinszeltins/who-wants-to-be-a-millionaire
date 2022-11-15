# Generate UI files from blueprint files.
blueprints = custom_target('blueprints',
    input: files(
        'ui/millionaire-window.blp',
    ),
    output: '.',
    command: [find_program('blueprint-compiler'), 'batch-compile', '@OUTPUT@', '@CURRENT_SOURCE_DIR@', '@INPUT@'],
)

milresources += gnome.compile_resources('millionaire-resources',
    'millionaire.gresource.xml',
    dependencies: blueprints,
    c_name: 'millionaire',
)