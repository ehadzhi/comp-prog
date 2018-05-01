#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

void task();

typedef long long LL;

bool equals(FILE *f1, FILE *f2) {
    char f1c, f2c;
    while (true) {
        f1c = fgetc(f1);
        f2c = fgetc(f2);
        if (f1c == EOF || f2c == EOF)
            return f1c == f2c;
        if (f1c != f2c)
            return false;
    }
}

bool tests() {
    try {
        string profile = getenv("profile");
        if (profile == "dev") {
            string base = "./temp/t";
            int test_num = 1;
            FILE *in;
            do {
                auto path = base + to_string(test_num);
                auto *expected = (path + "e").c_str();
                auto *actual = (path + "a").c_str();

                in = freopen(path.c_str(), "r", stdin);
                if (in) {
                    freopen(actual, "w", stdout);

                    clock_t begin = clock();

                    task();

                    clock_t end = clock();
                    auto elapse = double(end - begin) / CLOCKS_PER_SEC;

                    fprintf(stderr, "Test %d took %f sec.\n", test_num, elapse);
                    if (!equals(fopen(expected, "r"), fopen(actual, "r"))) {
                        cerr << "Problem in test " << test_num << endl;
                    }
                }
                test_num++;
            } while (in);
            return true;
        }
    } catch (exception e) {

    }
    return false;
}

typedef double D;

class Point {
public:
    const D x;
    const D y;

    Point(const D x, D y) : x(x), y(y) {}
};

class Line {
public:
    const Point left;
    const Point right;
    const D m;
    const D b;

    Line(const Point &left, const Point &right) :
            right(right), left(left),
            m(-(right.y - left.y) / (left.x - right.x)),
            b(left.y - m * left.x) {
    }

    D eval(D x) const {
        return m * x + b;
    }

    bool includes(const Point &point) const {
        return left.x <= point.x && point.x <= right.x
               && point.y == eval(point.x);
    }

    D down(const Point &p) const {
        D y = this->eval(p.x);
        if (this->includes(Point(p.x, y))) {
            D down = p.y - y;
            return down;
        }
        return 0;
    }
};

class IntervalTree {

};

class Figure {
public:
    IntervalTree lines;

    Figure(const vector<Line> &lines) : lines(lines) {}

    D maxLift(const Point &p) const {
        D maxLift = 0;
        for (const auto &lowerLine : lines) {
            D y = lowerLine.eval(p.x);
            if (lowerLine.includes(Point(p.x, y))) {
                D lift = y - p.y;
                maxLift = max(maxLift, lift);
            }
        }
        return maxLift;
    }

    void stack(const Figure &other) {
        D lift = 0;

        lift = max(lift, maxLift(lines[0].left));
        for (const auto &line :other.lines) {
            lift = max(lift, maxLift(line.right));
            lift = max(lift, maxDown(line));
        }

        for (const auto &line :other.lines) {
            lines.emplace_back(
                    Point(line.left.x, line.left.y + lift),
                    Point(line.right.x, line.right.y + lift));
        }
    }

    D maxDown(const Line &line) const {
        D maxDown = 0;
        maxDown = max(maxDown, line.down(lines[0].left));
        for (const auto &underLine: lines) {
            maxDown = max(maxDown, line.down(underLine.right));
        }
        return maxDown;
    }

    D height() const {
        D height = 0;
        height = max(height, lines[0].left.y);
        for (const auto &line:lines) {
            height = max(height, line.right.y);
        }
        return height;
    }
};

void task() {

    LL n;
    cin >> n;

    vector<Figure> figuresToStack;
    figuresToStack.reserve(n);
    for (int i = 0; i < n; i++) {
        D height, lowerD, upperD;
        cin >> height >> lowerD >> upperD;
        vector<Line> lines;
        lines.reserve(2);
        const Point &p1 = Point(0, 0);
        const Point &p2 = Point(lowerD, 0);
        const Point &p3 = Point(upperD, height);
        lines.emplace_back(p1, p2);
        lines.emplace_back(p2, p3);
        figuresToStack.emplace_back(lines);
    }

    for (int i = 1; i < n; i++) {
        figuresToStack[0].stack(figuresToStack[i]);
    }
    D height = figuresToStack[0].height();
    cout << height << endl;
    //printf("%f\n", height);

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    if (tests())
        return 0;

    task();
    return 0;
}
