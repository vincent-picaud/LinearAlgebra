doxygen = find_program('doxygen', required : false)
if not doxygen.found()
  message('Skip doc, doxygen not found.')
  subdir_done()
endif

cdata = configuration_data()
cdata.set('VERSION', meson.project_version())

if find_program('dot', required : false).found()
  # In the real world this would set the variable
  # to YES. However we set it to NO so that the
  # list of generated files is always the same
  # so tests always pass.
  cdata.set('HAVE_DOT', 'NO')
else
  cdata.set('HAVE_DOT', 'NO')
endif

cdata.set('TOP_SRCDIR', meson.source_root())
cdata.set('TOP_BUILDDIR', meson.build_root())

doxyfile = configure_file(input: 'Doxyfile.in',
                          output: 'Doxyfile',
                          configuration: cdata,
                          install: false)

datadir = join_paths(get_option('datadir'), 'doc', 'spede')

html_target = custom_target('doc',
                            input: doxyfile,
			    # depends: Optimize_lib,
                            output: 'html',
                            command: [doxygen, doxyfile],
                            install: true,
                            install_dir: datadir)
