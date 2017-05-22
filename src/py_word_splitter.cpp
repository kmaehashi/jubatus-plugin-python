#include "py_word_splitter.hpp"

#include <string>
#include <vector>
#include <map>
#include <utility>

#include <Python.h>
#include "python_bridge.hpp"

namespace jubatus {
namespace plugin {
namespace fv_converter {
namespace python {

void py_word_splitter::split(
    const std::string& text,
    std::vector<std::pair<size_t, size_t> >& ret_boundaries) const {
  scoped_gil lk;

  PyObject* ret = PyObject_CallMethodObjArgs(
      ins_,
      method_,
      PyString_FromString(text.c_str()),
      NULL);

  // TODO raise instead of assert
  assert(ret != NULL);
  assert(PyList_CheckExact(ret));

  size_t size = PyList_Size(ret);
  for (size_t i = 0; i < size; ++i) {
      PyObject* bound = PyList_GetItem(ret, i);

      // TODO
      assert(bound != NULL);
      assert(PyTuple_CheckExact(bound));
      assert(PyTuple_Size(bound) == 2);

      PyObject* begin = PyTuple_GetItem(bound, 0);
      PyObject* length = PyTuple_GetItem(bound, 1);

      // TODO
      assert(PyInt_CheckExact(begin));
      assert(PyInt_CheckExact(length));

      ret_boundaries.push_back(std::make_pair(PyInt_AsLong(begin), PyInt_AsLong(length)));
  }

  Py_DECREF(ret);
}

extern "C" {

jubatus::core::fv_converter::word_splitter* word_splitter(
    const std::map<std::string, std::string>& params) {
  initialize();
  return new py_word_splitter(setup(params));
}

}  // extern "C"

}  // namespace python
}  // namespace fv_converter
}  // namespace plugin
}  // namespace jubatus
