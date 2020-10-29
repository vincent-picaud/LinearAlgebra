doxygen = find_program('doxygen', required : false)

if doxygen.found()

  cdata = configuration_data()
  cdata.set('VERSION', meson.project_version())

  if find_program('dot', required : false).found()
    cdata.set('HAVE_DOT', 'YES')
  else 
    cdata.set('HAVE_DOT', 'NO')
  endif

  cdata.set('PROJECT_NAME',meson.project_name())
  cdata.set('PROJECT_SRCDIR', join_paths(meson.current_source_dir(),'..','src',meson.project_name()))
  cdata.set('PROJECT_BINDIR', join_paths(meson.current_source_dir(),'..','bin'))
  cdata.set('PROJECT_SANDBOXDIR', join_paths(meson.current_source_dir(),'..','sandbox'))
  cdata.set('PROJECT_EXAMPLESDIR', join_paths(meson.current_source_dir(),'..','examples'))
  cdata.set('PROJECT_DOCDIR', meson.current_source_dir())
  cdata.set('PROJECT_TESTDIR', join_paths(meson.current_source_dir(),'..','test'))
  cdata.set('PROJECT_BUILDDIR', meson.build_root())
			     
  doxyfile = configure_file(input: 'Doxyfile.in',
                            output: 'Doxyfile',
                            configuration: cdata, 
                            install: false)

  datadir = join_paths(get_option('datadir'), 'doc','Distributions')

  html_target = custom_target('doc',
			      build_always_stale : not meson.is_subproject(),
                              input: doxyfile,
                              output: 'html',
                              command: [doxygen, doxyfile],
                              install: not meson.is_subproject(),
                              install_dir: datadir)

endif
