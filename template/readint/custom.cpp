#include <bits/stdc++.h>

using namespace std;

// char gc() {
// #ifdef _WIN32
//     return _getchar_nolock();
// #else
//     return getchar_unlocked();
// #endif
// }
struct GC {
    char buf[1 << 16 | 1];
    int bc = 0, be = 0;
    char operator()() {
        if (bc >= be) {
            be = fread(buf, 1, sizeof(buf) - 1, stdin);
            buf[be] = bc = 0;
        }
        return buf[bc++];
    }
};
GC gc;
void read_int() {}
template <class T, class... S> inline void read_int(T &a, S &... b) {
    char c, s = 1;
    while (isspace(c = gc()))
        ;
    if (c == '-')
        s = -1, c = gc();
    for (a = c - '0'; isdigit(c = gc()); a = a * 10 + c - '0')
        ;
    a *= s;
    read_int(b...);
}

template <class T> struct is_iterator {
    template <class U, typename enable_if<!is_convertible<U, const char *>::value, int>::type = 0>
    constexpr static auto has_indirection(int) -> decltype(*declval<U>(), bool()) {
        return true;
    }
    template <class> constexpr static bool has_indirection(long) { return false; }
    constexpr static bool value = has_indirection<T>(0);
};

using uint = unsigned int;
// Buffer size should be 2^12 or 2^13 for optimal performance with files.
const uint BUFFER_SIZE = 1 << 12;
// Maximum possible length of a string representing primitive type
// assuming we won't encounter huge double values.
const uint MAX_LENGTH = 1 << 7;

namespace Detail {
struct Width {
    uint value;
};
struct Fill {
    char value;
};
struct Base {
    uint value;
};
struct Precision {
    uint value;
};
struct Delimiter {
    const char *value;
};
} // namespace Detail

Detail::Width setWidth(uint value = 0) { return {value}; }
Detail::Fill setFill(char value = ' ') { return {value}; }
Detail::Base setBase(uint value = 10) {
    assert(2 <= value && value <= 36);
    return {value};
}
Detail::Precision setPrecision(uint value = 9) {
    assert(value < MAX_LENGTH);
    return {value};
}
Detail::Delimiter setDelimiter(const char *value = " ") { return {value}; }
class OutputDevice {
  protected:
    char buffer[BUFFER_SIZE + MAX_LENGTH];
    char *output;
    char *end;
    bool separate;

    OutputDevice()
        : output(buffer), end(buffer + BUFFER_SIZE + MAX_LENGTH), separate(false), width(setWidth().value),
          fill(setFill().value), base(setBase().value), precision(setPrecision().value),
          delimiter(setDelimiter().value) {
        computeBasePower();
    }

    virtual void writeToDevice(uint count) = 0;

    inline void flushMaybe() {
        if (__builtin_expect(output >= buffer + BUFFER_SIZE, false)) {
            writeToDevice(BUFFER_SIZE);
            output = copy(buffer + BUFFER_SIZE, output, buffer);
        }
    }

    void computeBasePower() {
        basePower = 1;
        for (uint i = 0; i < precision; ++i)
            basePower *= base;
    }

    template <class I> inline char *writeUnsignedInt(I arg, char *last) {
        if (__builtin_expect(arg == 0, false))
            *--last = '0';
        if (__builtin_expect(base == 10, true)) {
            for (; arg; arg /= 10)
                *--last = '0' + arg % 10;
        } else
            for (; arg; arg /= base) {
                I digit = arg % base;
                *--last = digit < 10 ? '0' + digit : 'A' - 10 + digit;
            }
        return last;
    }

    template <class I> inline char *writeSignedInt(I arg, char *last) {
        auto unsignedArg = static_cast<typename make_unsigned<I>::type>(arg);
        if (arg < 0) {
            last = writeUnsignedInt(~unsignedArg + 1, last);
            *--last = '-';
            return last;
        }
        return writeUnsignedInt(unsignedArg, last);
    }

    template <class F> char *writeFloatingPoint(F arg, char *last) {
        bool negative = signbit(arg);
        if (negative)
            arg = -arg;
        if (isnan(arg))
            for (int i = 0; i < 3; ++i)
                *--last = i["NaN"];
        else if (isinf(arg))
            for (int i = 0; i < 3; ++i)
                *--last = i["fnI"];
        else {
            auto integerPart = static_cast<unsigned long long>(arg);
            auto fractionalPart = static_cast<unsigned long long>((arg - integerPart) * basePower + F(0.5));
            if (fractionalPart >= basePower)
                ++integerPart, fractionalPart = 0;
            char *point = last - precision;
            if (precision > 0) {
                ::fill(point, writeUnsignedInt(fractionalPart, last), '0');
                *--point = '.';
            }
            last = writeUnsignedInt(integerPart, point);
        }
        if (negative)
            *--last = '-';
        return last;
    }

    inline int writeT(char *first) {
        int delimiterLenght = separate ? writeDelimiter() : 0;
        separate = true;
        uint charsWritten = static_cast<uint>(end - first);
        if (__builtin_expect(charsWritten < width, false))
            charsWritten += writeFill(width - charsWritten);
        output = copy(first, end, output);
        flushMaybe();
        return delimiterLenght + static_cast<int>(charsWritten);
    }

    inline int writeFill(uint count) {
        int charsWritten = static_cast<int>(count);
        if (__builtin_expect(output + count + MAX_LENGTH < end, true)) {
            if (count == 1)
                *output++ = fill;
            else
                output = fill_n(output, count, fill);
        } else
            for (uint chunkSize = static_cast<uint>(buffer + BUFFER_SIZE - output);; chunkSize = BUFFER_SIZE) {
                if (chunkSize > count)
                    chunkSize = count;
                output = fill_n(output, chunkSize, fill);
                flushMaybe();
                if ((count -= chunkSize) == 0)
                    break;
            }
        return charsWritten;
    }

  public:
    uint width;
    char fill;
    uint base;
    uint precision;
    unsigned long long basePower;
    string delimiter;

    OutputDevice(OutputDevice const &) = delete;
    OutputDevice &operator=(OutputDevice const &) = delete;
    virtual ~OutputDevice(){};

    inline int writeChar(char arg) {
        separate = false;
        *output++ = arg;
        flushMaybe();
        return 1;
    }

    inline int writeString(const char *arg, size_t length, bool checkWidth = true) {
        separate = false;
        uint count = static_cast<uint>(length);
        int charsWritten = static_cast<int>(count) + (checkWidth && count < width ? writeFill(width - count) : 0);
        if (__builtin_expect(output + count + MAX_LENGTH < end, true)) {
            if (count == 1)
                *output++ = *arg;
            else
                output = copy_n(arg, count, output);
        } else
            for (uint chunkSize = static_cast<uint>(buffer + BUFFER_SIZE - output);; chunkSize = BUFFER_SIZE) {
                if (chunkSize > count)
                    chunkSize = count;
                output = copy_n(arg, chunkSize, output);
                flushMaybe();
                if ((count -= chunkSize) == 0)
                    break;
                arg += chunkSize;
            }
        return charsWritten;
    }

    inline int writeDelimiter() { return writeString(delimiter.c_str(), delimiter.size(), false); }

    inline void flush() {
        writeToDevice(static_cast<uint>(output - buffer));
        output = buffer;
    }

    // property setters
    inline int write(Detail::Width newWidth) {
        width = newWidth.value;
        return 0;
    }
    inline int write(Detail::Fill newFill) {
        fill = newFill.value;
        return 0;
    }
    inline int write(Detail::Base newBase) {
        base = newBase.value;
        computeBasePower();
        return 0;
    }
    inline int write(Detail::Precision newPrecision) {
        precision = newPrecision.value;
        computeBasePower();
        return 0;
    }
    inline int write(Detail::Delimiter newDelimiter) {
        delimiter = newDelimiter.value;
        return 0;
    }
    // primitive types
    inline int write() { return 0; }
    inline int write(char arg) { return writeChar(arg); }
    template <class I>
    inline typename enable_if<is_integral<I>::value && is_unsigned<I>::value, int>::type write(I arg) {
        return writeT(writeUnsignedInt(arg, end));
    }
    template <class I> inline typename enable_if<is_integral<I>::value && is_signed<I>::value, int>::type write(I arg) {
        return writeT(writeSignedInt(arg, end));
    }
    template <class F> inline typename enable_if<is_floating_point<F>::value, int>::type write(F arg) {
        return writeT(writeFloatingPoint(arg, end));
    }
    // complex types
    inline int write(const char *arg) { return writeString(arg, strlen(arg)); }
    template <int N> inline int write(char (&arg)[N]) { return writeString(arg, strlen(arg)); }
    inline int write(const string &arg) { return writeString(arg.c_str(), arg.size()); }
    template <class T1, class T2> inline int write(const pair<T1, T2> &arg) {
        int charsWritten = write(arg.first);
        charsWritten += writeDelimiter();
        return charsWritten + write(arg.second);
    }
    template <class T> inline int write(const complex<T> &arg) { return write(real(arg), imag(arg)); }
    // ranges
    template <class Iterator, class... Ts>
    inline typename enable_if<is_iterator<Iterator>::value, int>::type write(Iterator first, Iterator last,
                                                                             Ts &&... args) {
        int charsWritten = 0;
        for (; first != last; charsWritten += ++first == last ? 0 : writeDelimiter())
            charsWritten += write(*first);
        return charsWritten + write(forward<Ts>(args)...);
    }
    template <class Iterator, class I, class... Ts>
    inline typename enable_if<is_iterator<Iterator>::value && is_integral<I>::value, int>::type
    write(Iterator first, I count, Ts &&... args) {
        return write(first, first + count, forward<Ts>(args)...);
    }
    // generic forwarding
    template <class T> inline auto write(const T &arg) -> decltype(arg.write(*this)) { return arg.write(*this); }
    template <class T0, class T1, class... Ts>
    inline typename enable_if<!is_iterator<T0>::value, int>::type write(T0 &&arg0, T1 &&arg1, Ts &&... args) {
        int charsWritten = write(forward<T0>(arg0));
        return charsWritten + write(forward<T1>(arg1), forward<Ts>(args)...);
    }
};

class OutputFile : public OutputDevice {
    FILE *file;
    bool owner;

    void writeToDevice(uint count) override {
        fwrite(buffer, 1, count, file);
        fflush(file);
    }

  public:
    OutputFile(FILE *file = stdout, bool takeOwnership = false) : file(file), owner(takeOwnership) {}
    OutputFile(const char *fileName) : OutputFile(fopen(fileName, "w"), true) {}
    ~OutputFile() override {
        flush();
        if (owner)
            fclose(file);
    }
};

class OutputString : public OutputDevice {
    string &str;

    void writeToDevice(uint count) override { str.append(buffer, count); }

  public:
    OutputString(string &str) : OutputDevice(), str(str) {}
    ~OutputString() override { flush(); }
};
unique_ptr<OutputDevice> output;

template <class... Ts> inline int write(Ts &&... args) { return output->write(forward<Ts>(args)...); }
template <class... Ts> inline int writeln(Ts &&... args) { return write(forward<Ts>(args)..., '\n'); }
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    output.reset(new OutputFile());
    int N;
    read_int(N);
    // cin >> N;
    for (int i = 0; i < N; i++) {
        int a, b;
        read_int(a, b);
        // cin >> a >> b;
        writeln(a * b);
    }
}