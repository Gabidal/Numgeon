project(
  'Numgeon', 'cpp',
  version : '0.1.1',
  default_options : ['warning_level=3', 'cpp_std=c++20']
)

sources = [
  'Campaing.cpp', 
  'Construct.cpp',
  'Initialize_Utils.cpp',
  'Map.cpp',
  'Object.cpp',
  'Parser.cpp',
  'Teller.cpp',

  'main.cpp',
]

incdir = include_directories('C:/Users/Quanf/source/repos/Numgeon_GGUI/GGUI/')

cpp = meson.get_compiler('cpp')

GGUI = cpp.find_library('C:/Users/Quanf/source/repos/Numgeon_GGUI/GGUI/GGUI')

executable(
  'Numgeon',
  sources,
  install : true,
  include_directories : incdir,
  dependencies : GGUI
)

