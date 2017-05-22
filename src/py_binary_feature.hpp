#ifndef JUBATUS_PLUGIN_FV_CONVERTER_PYTHON_PY_BINARY_FEATURE_HPP_
#define JUBATUS_PLUGIN_FV_CONVERTER_PYTHON_PY_BINARY_FEATURE_HPP_

#include <jubatus/core/fv_converter/binary_feature.hpp>

#include <Python.h>
#include "python_bridge.hpp"

namespace jubatus {
namespace plugin {
namespace fv_converter {
namespace python {

class py_binary_feature
    : public jubatus::core::fv_converter::binary_feature {
 public:
  explicit py_binary_feature(PyObject* ins)
      : name_("extract"),
        ins_(ins),
        method_(PyString_FromStringAndSize(name_.c_str(), name_.length())) {};

  void add_feature(
      const std::string& key,
      const std::string& value,
      std::vector<std::pair<std::string, float> >& ret_fv) const;

 private:
   std::string name_;
   PyObject* ins_;
   PyObject* method_;
};

}  // namespace python
}  // namespace fv_converter
}  // namespace plugin
}  // namespace jubatus

#endif  // JUBATUS_PLUGIN_FV_CONVERTER_PYTHON_PY_BINARY_FEATURE_HPP_
