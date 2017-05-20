#include <jubatus/core/fv_converter/word_splitter.hpp>

#include <Python.h>

namespace jubatus {
namespace plugin {
namespace fv_converter {
namespace python {

class py_word_splitter
    : public jubatus::core::fv_converter::word_splitter {
 public:
  py_word_splitter(PyObject* ins)
      : ins_(ins),
        method_(PyString_FromString("split")) {};

  void split(
      const std::string& string,
      std::vector<std::pair<size_t, size_t> >& ret_boundaries) const;

 private:
   PyObject* ins_;
   PyObject* method_;
};

}  // namespace python
}  // namespace fv_converter
}  // namespace plugin
}  // namespace jubatus
