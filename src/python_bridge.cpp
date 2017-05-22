#include "python_bridge.hpp"

#include <map>
#include <string>

#include <Python.h>

namespace jubatus {
namespace plugin {
namespace fv_converter {
namespace python {

/**
 * Initializes the Python interpreter.  Must be called from
 * main thread.  It is safe to call this multiple times.
 */
void initialize() {
  if (Py_IsInitialized()) {
    return;
  }

  Py_Initialize();
  PyEval_InitThreads();

  // TODO for debugging
  PyRun_SimpleString("print('interpreter initialized')");
  PyRun_SimpleString("import sys");
  PyRun_SimpleString("sys.path.append('.')");

  // Release GIL.
  PyEval_SaveThread();
}

/**
 * Instantiate the plugin class specified in the param.
 */
PyObject* setup(const std::map<std::string, std::string>& params) {
  scoped_gil lk;

  // import the module
  PyObject* module = PyImport_ImportModule(params.at("module").c_str());
  assert(module != NULL);  // TODO raise

  // call class constructor
  PyObject* ins = PyObject_CallMethodObjArgs(module, PyString_FromString(params.at("class").c_str()), NULL);
  assert(ins != NULL);  // TODO raise

  return ins;
}

}  // namespace python
}  // namespace fv_converter
}  // namespace plugin
}  // namespace jubatus
