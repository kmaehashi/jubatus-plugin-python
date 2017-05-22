#ifndef JUBATUS_PLUGIN_FV_CONVERTER_PYTHON_PYTHON_BRIDGE_HPP_
#define JUBATUS_PLUGIN_FV_CONVERTER_PYTHON_PYTHON_BRIDGE_HPP_

#include <Python.h>

#include <string>
#include <map>

namespace jubatus {
namespace plugin {
namespace fv_converter {
namespace python {

void initialize();
PyObject* setup(const std::map<std::string, std::string>&);

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
