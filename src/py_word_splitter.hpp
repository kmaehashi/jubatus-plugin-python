#ifndef JUBATUS_PLUGIN_FV_CONVERTER_PYTHON_PY_WORD_SPLITTER_HPP_
#define JUBATUS_PLUGIN_FV_CONVERTER_PYTHON_PY_WORD_SPLITTER_HPP_

#include <jubatus/core/fv_converter/word_splitter.hpp>

#include <Python.h>

namespace jubatus {
namespace plugin {
namespace fv_converter {
namespace python {

class py_word_splitter
    : public jubatus::core::fv_converter::word_splitter {
 public:
  explicit py_word_splitter(PyObject* ins)
      : name_("split"),
        ins_(ins),
        method_(PyString_FromStringAndSize(name_.c_str(), name_.length())) {};

  void split(
      const std::string& string,
      std::vector<std::pair<size_t, size_t> >& ret_boundaries) const;

 private:
   std::string name_;
   PyObject* ins_;
   PyObject* method_;
};

}  // namespace python
}  // namespace fv_converter
}  // namespace plugin
}  // namespace jubatus

#endif  // JUBATUS_PLUGIN_FV_CONVERTER_PYTHON_PY_WORD_SPLITTER_HPP_
