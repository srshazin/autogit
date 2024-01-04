project('autogit', 'c')

# Configuration
executable_name = 'autogit'

# Directories
src_dir = 'src'
inc_dir = 'includes'

# Sources
sources = files(src_dir/'args_parser.c', src_dir/'loop.c', src_dir/'main.c', src_dir/'text_parser.c', src_dir/'utils.c')

# Include directories
inc = include_directories(inc_dir)

# Executable
exe = executable(executable_name, sources, include_directories: inc, install: true)

# # Install rules
# install_dir = get_option('prefix', '/usr/local')  # Change this as needed

# bindir = join_paths(install_dir, get_option('bindir', 'bin'))
# libdir = join_paths(install_dir, get_option('libdir', 'lib'))

# install_data(exe, bindir)
# install_data(inc_dir, join_paths(libdir, 'include'))
