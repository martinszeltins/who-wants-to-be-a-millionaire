millionaire_sources = [
  'main.c',
  'millionaire-application.c',
  'millionaire-window.c',
]

millionaire_deps = [
  dependency('gtk4'),
  dependency('libadwaita-1'),
]

millionaire_sources += gnome.compile_resources('millionaire-resources',
  'millionaire.gresource.xml',
  c_name: 'millionaire'
)

executable('millionaire', millionaire_sources,
  dependencies: millionaire_deps,
       install: true,
)
