#ifndef JUBATUS_PLUGIN_FV_CONVERTER_PYTHON_PYTHON_BRIDGE_HPP_
#define JUBATUS_PLUGIN_FV_CONVERTER_PYTHON_PYTHON_BRIDGE_HPP_

#include <string>
#include <map>

#include <Python.h>

namespace jubatus {
namespace plugin {
namespace fv_converter {
namespace python {

/**
 * Initializes the Python interpreter.  This function must be called
 * from main thread, before calling ``setup`` or any other CPython-related
 * things.  It is safe to call this function for multiple times.
 */
void initialize();

/**
 * Instantiate the plugin class specified in the param.
 */
PyObject* setup(const std::map<std::string, std::string>&);

/**
 * Provides RAII interface for Python GIL.
 */
class scoped_gil {
 public:
  scoped_gil()
      : gstate_(PyGILState_Ensure()) {};

  ~scoped_gil() {
      PyGILState_Release(gstate_);
  };

 private:
  PyGILState_STATE gstate_;
};

}  // namespace python
}  // namespace fv_converter
}  // namespace plugin
}  // namespace jubatus

#endif  // JUBATUS_PLUGIN_FV_CONVERTER_PYTHON_PYTHON_BRIDGE_HPP_
