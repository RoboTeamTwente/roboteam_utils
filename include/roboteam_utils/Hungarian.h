#ifndef HUNGARIAN_H
#define HUNGARIAN_H

#include <iostream>
#include <vector>
#include <bits/stdc++.h>

namespace rtt {
    using namespace std;
    using Matrix = vector<vector<int>>;

    class MunkresAssignment {
    public:
        MunkresAssignment() = default;
        ~MunkresAssignment() = default;

        vector<int> runMunkres(const vector<vector<int>>& cost) {
            initVariables(cost);
            //printCost();
            while (!optimal) {
                switch (step) {
                    case 1:
                        rowSubtraction();
                        break;
                    case 2:
                        starZeros();
                        break;
                    case 3:
                        coverStars();
                        break;
                    case 4:
                        primeUncoveredZeros();
                        break;
                    case 5:
                        starPrimes();
                        break;
                    case 6:
                        findMinCost();
                        break;
                    case 7:
                        optimal = true;
                        returnAssignments();
                        break;
                    default:
                        break;
                }
            }
            //printMask();
            //hcout << endl;
            printAssignment();
            return m_assignment;
        }

    private:
        void initVariables(const Matrix& cost){
            step = 1;
            optimal = false;
            size= static_cast<int>(cost.size()); // !assumes matrix is square

            RowCover.resize(size);
            ColCover.resize(size);

            path.resize(size*2, vector<int>(size*2));
            mask.resize(size, vector<int>(size));
            m_cost.resize(size, vector<int>(size));
            m_cost = cost;

            m_assignment.resize(size);

//            mask.resize(size);
//            for (int r{ 0 }; r < size; ++r) {
//                mask[r].reserve(size);
//                for (int c{ 0 }; c < size; ++c) {
//                    mask[r][c] = 0;
//                }
//            }
        }

        void printCost(){
            for (auto row{0}; row < size; ++row) {
                for (auto col{0}; col < size; ++col) {
                    std::cout << m_cost[row][col] << " ";
                }
                std::cout << std::endl;
            }
        }

        void printMask() {
            for (auto row{0}; row < size; ++row) {
                for (auto col{0}; col < size; ++col) {
                    std::cout << mask[row][col] << " ";
                }
                std::cout << std::endl;
            }
        }

        void printAssignment(){
            for(auto i{0}; i<size; ++i){
                cout << m_assignment[i] << " ";
            }
            cout << endl;
        }

        void rowSubtraction() {
            double min_in_row{};
            for (auto row{ 0 }; row < size; ++row) {
                // find the lowest cost in a row
                min_in_row = m_cost[row][0];
                for (auto col{ 1 }; col < size; ++col) {
                    if (m_cost[row][col] < min_in_row) min_in_row = m_cost[row][col];
                }
                // then subtract it from all other cost in the same row
                for (auto col{ 0 }; col < size; ++col) {
                    m_cost[row][col] -= min_in_row;
                }
            }
            step = 2;
        }

        void starZeros() {
            // search for zero costs and mark them in the mask matrix if the row and column has not been covered yet
            for (int row{ 0 }; row < size; ++row) {
                for (int col{ 0 }; col < size; ++col) {
                    if (m_cost[row][col] == 0 && !RowCover[row] && !ColCover[col]) {
                        mask[row][col] = 1;  // star
                        RowCover[row] = true;
                        ColCover[col] = true;
                    }
                }
            }
            clearCovers();
            step = 3;
        }

        void coverStars() {
            // check if all columns are assigned to a row in the mask matrix (i.e. if every role has a robot assigned)
            for (int row{ 0 }; row < size; ++row) {
                for (int col{ 0 }; col < size; ++col) {
                    if (mask[row][col] == 1) ColCover[col] = true;
                }
            }
            int colcount{ 0 };
            for (int col{ 0 }; col < size; ++col) {
                if (ColCover[col]) ++colcount;
            }
            if (colcount == size)
                step = 7;  // successfully optimized assignment
            else
                step = 4;
        }

        void primeUncoveredZeros() {
            int row{ -1 };
            int col{ -1 };
            bool primed{ false };

            while (!primed) {
                findZero(row, col);
                if (row == -1) {  // if no zeros were found there is nothing left to prime
                    primed = true;
                    step = 6;
                } else {
                    mask[row][col] = 2;  // mark as primed in mask matrix
                    if (starRow(row)) {  // if there is a stared zero in the same row as the primed zero
                        // change the stared zero's cover to overlap with the primed zero's cover
                        findStarCol(row, col);
                        RowCover[row] = true;
                        ColCover[col] = false;
                    } else {
                        // save the smallest uncovered value and move on
                        path_row_0 = row;
                        path_col_0 = col;
                        primed = true;
                        step = 5;
                    }
                }
            }
        }

        void findZero(int& row, int& col) {
            int r{ 0 };
            int c{ 0 };
            bool found{ false };
            // reset input in case this is not the first while(!primed) iteration
            row = -1;
            col = -1;
            // return the coordinates of the first uncovered zero found in the cost matrix
            for (int r{ 0 }; r < size; ++r) {
                for (int c{ 0 }; c < size; ++c) {
                    if (m_cost[r][c] == 0 && !RowCover[r] && !ColCover[c]) {
                        row = r;
                        col = c;
                        found = true;
                        break;
                    }
                }
                if (found) break;
            }
        }

        bool starRow(int row) {
            // returns whether the mask matrix has a star in a given row
            bool found{ false };
            for (int c{ 0 }; c < size; ++c) {
                if (mask[row][c] == 1) found = true;
            }
            return found;
        }

        void findStarCol(int row, int& col) {
            // returns the column of a stared zero in a given row
            col = -1;
            for (int c{ 0 }; c < size; ++c) {
                if (mask[row][c] == 1) col = c;
            }
        }

        void starPrimes() {
            bool done{ false };
            int r{ -1 };
            int c{ -1 };

            pathCount = 1;
            path[pathCount - 1][0] = path_row_0;
            path[pathCount - 1][1] = path_col_0;

            while (!done) {
                findStarRow(path[pathCount - 1][1], r);
                if (r > -1) {
                    ++pathCount;
                    path[pathCount - 1][0] = r;
                    path[pathCount - 1][1] = path[pathCount - 2][1];
                } else
                    done = true;
                if (!done) {
                    findPrimeCol(path[pathCount - 1][0], c);
                    ++pathCount;
                    path[pathCount - 1][0] = path[pathCount - 2][0];
                    path[pathCount - 1][1] = c;
                }
            }
            augmentPath();
            clearCovers();
            clearPrimes();
            step = 3;
        }

        void findStarRow(int col, int& row) {
            // returns the row of a stared zero in a given column
            row = -1;
            for (int r{ 0 }; r < size; ++r) {
                if (mask[r][col] == 1) row = r;
            }
        }

        void findPrimeCol(int row, int& col) {
            // returns the column of a primed zero in a given row
            for (int c{ 0 }; c < size; ++c) {
                if (mask[row][c] == 2) col = c;
            }
        }

        void augmentPath() {
            for (int p{ 0 }; p < pathCount; ++p) {
                if (mask[path[p][0]][path[p][1]] == 1)
                    mask[path[p][0]][path[p][1]] = 0;
                else
                    mask[path[p][0]][path[p][1]] = 1;
            }
        }

        void clearCovers() {
            // reset all covered rows and columns
            for (int row{ 0 }; row < size; ++row) {
                RowCover[row] = false;
            }
            for (int col{ 0 }; col < size; ++col) {
                ColCover[col] = false;
            }
        }

        void clearPrimes() {
            // reset all primes stored in the mask matrix
            for (int r{ 0 }; r < size; ++r) {
                for (int c{ 0 }; c < size; ++c) {
                    if (mask[r][c] == 2) mask[r][c] = 0;
                }
            }
        }

        void findMinCost() {
            // find the lowest uncovered cost
            int minCost{ INT_MAX };
            for (int r{ 0 }; r < size; ++r) {
                for (int c{ 0 }; c < size; ++c) {
                    if (!RowCover[r] && !ColCover[c] && minCost > m_cost[r][c]) minCost = m_cost[r][c];
                }
            }
            for (int r{ 0 }; r < size; ++r) {
                for (int c{ 0 }; c < size; ++c) {
                    // add the lowest cost to all covered rows
                    if (RowCover[r]) m_cost[r][c] += minCost;
                    // subtract the lowest cost from all uncovered columns
                    if (!ColCover[c]) m_cost[r][c] -= minCost;
                }
            }
            step = 4;
        }

        void returnAssignments() {
            m_assignment.resize(size);
            for (int r{ 0 }; r < size; ++r) {
                for (int c{ 0 }; c < size; ++c) {
                    if (mask[r][c] == 1) m_assignment[c] = r;
                }
            }
        }

        int step;
        bool optimal;

        int size;
        Matrix m_cost;

        vector<bool> RowCover;
        vector<bool> ColCover;
        Matrix mask;

        int path_row_0;
        int path_col_0;
        int pathCount;
        vector<vector<int>> path; // SHOULD NOT BE SQUARE

        vector<int> m_assignment;
    };
} // namespace rtt
#endif