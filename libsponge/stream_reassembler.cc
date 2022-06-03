#include "stream_reassembler.hh"

// Dummy implementation of a stream reassembler.

// For Lab 1, please replace with a real implementation that passes the
// automated checks run by `make check_lab1`.

// You will need to add private members to the class declaration in `stream_reassembler.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

StreamReassembler::StreamReassembler(const size_t capacity) : _output(capacity), _capacity(capacity) {}

//! \details This function accepts a substring (aka a segment) of bytes,
//! possibly out-of-order, from the logical stream, and assembles any newly
//! contiguous substrings and writes them into the output stream in order.
void StreamReassembler::push_substring(const string &data, const uint64_t index, const bool eof) {
    size_t assembled_bytes = _output.write(data);
    _in_bytes += data.size();
    _assembled_bytes += assembled_bytes;

    if (eof) {
        _output.end_input();
    }
}

size_t StreamReassembler::unassembled_bytes() const { _in_bytes - _assembled_bytes; }

bool StreamReassembler::empty() const { 
    _output.buffer_empty();
}
