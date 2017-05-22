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

  // Import the module.
  PyObject* module = PyImport_ImportModule(params.at("module").c_str());
  assert(module != NULL);  // TODO raise

  // Get the class.
  PyObject* clazz = PyObject_GetAttrString(module, params.at("class").c_str());
  assert(clazz != NULL);  // TODO raise
  // TODO check if it is a class

  // Get the create method.
  PyObject* create_func = PyObject_GetAttrString(clazz, "create");
  assert(create_func != NULL);  // TODO raise

  // Call create method and create the instance.
  // TODO convert params into dict and pass it.
  PyObject* ins = PyObject_CallFunctionObjArgs(create_func, Py_None, NULL);
  assert(ins != NULL);  // TODO raise

  // Release objects no longer needed.
  Py_DECREF(module);
  Py_DECREF(clazz);
  Py_DECREF(create_func);

  return ins;
}

}  // namespace python
}  // namespace fv_converter
}  // namespace plugin
}  // namespace jubatus
