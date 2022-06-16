#pragma once

#include <vector>

#include "FastRectangle.hpp"
#include "LazyRectangle.hpp"

namespace rtt {

class InvalidCellLocation : private std::exception {
public:
    explicit InvalidCellLocation(const std::string& message);
    const char* what() const noexcept override;
private:
    const std::string message;
};
class InvalidGridSizeException : private std::exception {
public:
    explicit InvalidGridSizeException(const std::string& message);
    const char* what() const noexcept override;
private:
    const std::string message;
};

template <typename T>
class Grid : virtual public Rectangle {
public:
    virtual ~Grid() = default;

    // Gets the cell at the specified location, can throw InvalidCellLocation
    virtual const T& getCell(unsigned int row, unsigned int column) const = 0;
    // A list of all cells, from left to right, top to bottom
    virtual const std::vector<T>& getCells() const = 0;

    virtual int getRowSize() const = 0;
    virtual int getColumnSize() const = 0;
};

// Fast implementation of a grid. It calculates all properties first, so accessing later takes little time
template <int X, int Y, typename T>
class FastGrid : public Grid<T>, public FastRectangle {
public:
    explicit FastGrid(const Rectangle& r) : FastRectangle(r) {
        if (X < 1 || Y < 1) throw InvalidGridSizeException("Invalid grid size, cannot be lower than 1");

        double cellWidth = this->width() / X;
        double cellHeight = this->height() / Y;

        for (int row = 0; row < Y; row++) {
            for (int column = 0; column < X; column++) {
                // Calculate the rectangle of the cell
                double cellTop = this->top() - row * cellHeight;
                double cellBottom = cellTop - cellHeight;
                double cellLeft = this->left() + column * cellWidth;
                double cellRight = cellLeft + cellWidth;

                // Now create the cell of the correct type and add it
                LazyRectangle cellBoundary({cellRight, cellTop}, {cellLeft, cellBottom});
                auto cell = T(cellBoundary);
                this->cells.push_back(cell);
            }
        }
    }

    const T& getCell(unsigned int x, unsigned int y) const override {
        if (y >= Y || x >= X) throw InvalidCellLocation("This cell does not exist");
        return this->cells[x + y * X];
    }
    const std::vector<T>& getCells() const override {
        return this->cells;
    }
    void addPoints(std::vector<Vector2>& v) const override {
        for (const auto& cell : this->cells) {
            cell.addPoints(v);
        }
    }
    int getRowSize() const override { return X; }
    int getColumnSize() const override { return Y; }
private:
    std::vector<T> cells;
};

// 3 by 3 version of a fast grid. Adds some easy accessibility functions.
template <typename T>
class Grid3x3 : public FastGrid<3, 3, T> {
public:
    explicit Grid3x3(const Rectangle& r) : FastGrid<3, 3, T>(r) {}

    const T& topLeftCell() { return this->getCell(0, 0); }
    const T& topMiddleCell() { return this->getCell(1, 0); }
    const T& topRightCell() { return this->getCell(2, 0); }
    const T& middleLeftCell() { return this->getCell(0, 1); }
    const T& middleMiddleCell() { return this->getCell(1, 1); }
    const T& middleRightCell() { return this->getCell(2, 1); }
    const T& bottomLeftCell() { return this->getCell(0, 2); }
    const T& bottomMiddleCell() { return this->getCell(1, 2); }
    const T& bottomRightCell() { return this->getCell(2, 2); }
};

} // namespace rtt
