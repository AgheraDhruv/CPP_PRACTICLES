#include <iostream>
using namespace std;

class Rectangle {
private:
    double length, width;

public:
    void set(double l, double w) {
        length = l;
        width = w;
    }

    void update(double l, double w) {
        length = l;
        width = w;
    }

    double area() {
        return length * width;
    }

    double perimeter() {
        return 2 * (length + width);
    }

    void display(int i) {
        cout << "\nRectangle " << i + 1 << ":";
        cout << "\nLength     : " << length;
        cout << "\nWidth      : " << width;
        cout << "\nArea       : " << area();
        cout << "\nPerimeter  : " << perimeter() << "\n";
    }
};

int main() {
    int n;
    cout << "Enter number of rectangles: ";
    cin >> n;

    Rectangle r[n];

    for (int i = 0; i < n; i++) {
        double l, w;
        cout << "\nEnter length and width for rectangle " << i + 1 << ": ";
        cin >> l >> w;
        r[i].set(l, w);
    }

    cout << "\n--- Rectangle Details ---\n";
    for (int i = 0; i < n; i++) {
        r[i].display(i);
    }

    char ch;
    cout << "\nDo you want to update any rectangle? (y/n): ";
    cin >> ch;

    if (ch == 'y' || ch == 'Y') {
        int index;
        double nl, nw;

        cout << "Enter rectangle number to update: ";
        cin >> index;

        cout << "Enter new length and width: ";
        cin >> nl >> nw;

        r[index - 1].update(nl, nw);

        cout << "\nUpdated Rectangle:\n";
        r[index - 1].display(index - 1);
    }

    return 0;
}


