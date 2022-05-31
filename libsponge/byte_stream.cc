#include "byte_stream.hh"
#include <iostream>
// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity) {
    this->_capacity = capacity;
}

size_t ByteStream::write(const string &data) {
    size_t data_size = data.size();
    size_t remain_space = remaining_capacity();
    int writable_bytes = remain_space - data_size;

    if (writable_bytes >= 0) {
        buffer.append(data);
        _bytes_written += data_size;
    } else {
        for (size_t i = 0; i < remain_space; i++) {
            buffer.push_back(data[i]);
        }
        _bytes_written += remain_space;
    }

    return writable_bytes <= 0 ? remain_space : data_size;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    if (len >= _capacity) {
        return buffer;
    }

    return buffer.substr(0, len);
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    if (len >= _capacity) {
        _bytes_read += _capacity;
        buffer.clear();
        return;
    }
    
    _bytes_read += len;
    buffer = buffer.substr(len);
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    string r = peek_output(len);
    pop_output(len);
    return r;
}

void ByteStream::end_input() {
    _input_ended = true;
}

bool ByteStream::input_ended() const { return this->_input_ended; }

size_t ByteStream::buffer_size() const { return this->buffer.size(); }

bool ByteStream::buffer_empty() const { return this->buffer.empty(); }

bool ByteStream::eof() const { return input_ended() & (_bytes_read == _bytes_written); }

size_t ByteStream::bytes_written() const { return _bytes_written; }

size_t ByteStream::bytes_read() const { return _bytes_read; }

size_t ByteStream::remaining_capacity() const { return this->_capacity - buffer.size(); }
