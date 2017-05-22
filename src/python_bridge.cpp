#include "python_bridge.hpp"

#include <string>
#include <map>

#include <Python.h>

namespace jubatus {
namespace plugin {
namespace fv_converter {
namespace python {

void initialize() {
  if (Py_IsInitialized()) {
    return;
  }

  Py_Initialize();
  PyEval_InitThreads();

  // TODO remove me, only for debugging.
  PyRun_SimpleString("import sys");
  PyRun_SimpleString("sys.path.append('.')");

  // Release GIL in main thread.
  PyEval_SaveThread();
}

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
