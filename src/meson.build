millionaire_deps = [
    dependency('gtk4'),
    dependency('libadwaita-1'),
]

millionaire_sources = millionaire_resources
millionaire_sources += [
    'main.c',
    'millionaire-application.c',
    'millionaire-window.c',
]

exec = executable('millionaire', millionaire_sources,
    dependencies: millionaire_deps,
    install: true,
)
