#pragma once
#include <cstdint>
#include <memory>
#include <exception>
#include <string>


class Matrix {
public:
    explicit Matrix(std::unique_ptr<uint8_t[]> raw_image, size_t side)
        :raw_image_(std::move(raw_image)), side_(side) {
    }

    size_t size() {
        return side_ * side_;
    }

    size_t side() {
        return side_;
    }

    uint8_t operator() (size_t row, size_t col) {
        validate(row, col);
        return getPixel(row, col);
    }

    void rot90() {
        if (side_ == 0 || side_ == 1) {
            return;
        }

        size_t half = side_ / 2, i1, j1, i2, j2, i3, j3;
        size_t last = side_ - 1;
        uint8_t tmp;

        for (size_t i0 = 0; i0 < half; ++i0) {
            for (size_t j0 = i0; j0 < side_ - i0 - 1; ++j0) {
                i1 = j0;
                j1 = last - i0;

                i2 = last - i0;
                j2 = last - j0;

                i3 = last - j0;
                j3 = i0;

                tmp = getPixel(i3, j3);

                setPixel(i3, j3, getPixel(i2, j2));
                setPixel(i2, j2, getPixel(i1, j1));
                setPixel(i1, j1, getPixel(i0, j0));
                setPixel(i0, j0, tmp);
            }
        }
    }

    class Exception : public std::exception {
    protected:
        std::string msg_;
    public:
        explicit Exception(const char* msg)
            :msg_(msg) {}

        explicit Exception(const std::string& msg)
            :msg_(msg) {}
        
        virtual ~Exception() {}

        virtual const char* what() const noexcept {
            return msg_.c_str();
        }
    };

private:
    std::unique_ptr<uint8_t[]> raw_image_;
    size_t side_;

    inline void validate(size_t row, size_t col) {
        if (row >= side_) {
            throw Matrix::Exception("row is out of bounds");
        }
        if (col >= side_) {
            throw Matrix::Exception("col is out of bounds");
        }
    }

    uint8_t getPixel(size_t row, size_t col) {
        return getContinious(row * side_ + col);
    }

    void setPixel(size_t  row, size_t col, uint8_t value) {
        setContinious(row * side_ + col, value);
    }

    uint8_t getContinious(size_t index) {
        uint8_t pair =  raw_image_[index / 2];
        // oddity check
        return (index & 1) ? (pair & 0xF) : (pair >> 4);
    }

    void setContinious(size_t index, uint8_t value) {
        // sanity check, just in case
        value = 0xF & value;
        uint8_t pair =  raw_image_[index / 2];
        // oddity check
        if (index & 1) {
            raw_image_[index / 2] = (pair & 0xF0) | value;
        } else {
            raw_image_[index / 2] = (pair & 0xF) | (value << 4);
        }
    }

};

