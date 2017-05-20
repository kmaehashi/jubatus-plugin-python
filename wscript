subdirs = 'src'

def options(opt):
  opt.load('compiler_cxx')
  opt.recurse(subdirs)

def configure(conf):
  conf.env.CXXFLAGS += ['-O2', '-Wall', '-g', '-pipe']
  conf.load('compiler_cxx')

  conf.check_cfg(package = 'jubatus_core', args = '--cflags --libs')
  conf.check_cfg(package = 'python', args = '--cflags --libs')

  conf.recurse(subdirs)

def build(bld):
  bld.recurse(subdirs)
