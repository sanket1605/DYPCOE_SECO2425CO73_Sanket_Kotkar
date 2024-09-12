#include <graphics.h> // Make sure to link with the graphics library
#include <iostream>

using namespace std;

// Define constants for region codes
#define INSIDE 0  // 0000
#define LEFT 1    // 0001
#define RIGHT 2   // 0010
#define BOTTOM 4   // 0100
#define TOP 8      // 1000

// Function to compute the region code for a point (x, y)
int computeCode(int x, int y, int x_min, int y_min, int x_max, int y_max) {
    int code = INSIDE;

    if (x < x_min)       // to the left of rectangle
        code |= LEFT;
    else if (x > x_max)  // to the right of rectangle
        code |= RIGHT;
    if (y < y_min)       // below the rectangle
        code |= BOTTOM;
    else if (y > y_max)  // above the rectangle
        code |= TOP;

    return code;
}

// Cohen-Sutherland line clipping algorithm
void cohenSutherlandLineClip(int &x1, int &y1, int &x2, int &y2, int x_min, int y_min, int x_max, int y_max) {
    int code1 = computeCode(x1, y1, x_min, y_min, x_max, y_max);
    int code2 = computeCode(x2, y2, x_min, y_min, x_max, y_max);
    bool accept = false;

    while (true) {
        if (!(code1 | code2)) { // Both points inside
            accept = true;
            break;
        } else if (code1 & code2) { // Both points outside
            break;
        } else { // Some portion of line must be inside
            int code_out;
            if (code1 != INSIDE) 
                code_out = code1; // Choose an outside point
            else 
                code_out = code2;

            // Find intersection point
            int x, y;
            if (code_out & TOP) { // point is above the clip rectangle
                x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1);
                y = y_max;
            } else if (code_out & BOTTOM) { // point is below the clip rectangle
                x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1);
                y = y_min;
            } else if (code_out & RIGHT) { // point is to the right of clip rectangle
                y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1);
                x = x_max;
            } else if (code_out & LEFT) { // point is to the left of clip rectangle
                y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1);
                x = x_min;
            }

            // Replace the outside point with the intersection point
            if (code_out == code1) {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1, x_min, y_min, x_max, y_max);
            } else {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2, x_min, y_min, x_max, y_max);
            }
        }
    }

    if (accept) {
        // Draw the accepted line
        setcolor(GREEN); // Color for accepted lines
        line(x1, y1, x2, y2);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, ""); // Initialize graphics mode

    // Define the clipping rectangle
    int x_min = 100, y_min = 100, x_max = 400, y_max = 400;

    // Draw the clipping rectangle
    setcolor(WHITE);
    rectangle(x_min, y_min, x_max, y_max);

    // Define three lines
    // 1. Partially inside
    int line1_x1 = 50, line1_y1 = 150, line1_x2 = 450, line1_y2 = 250;

    // 2. Completely inside
    int line2_x1 = 150, line2_y1 = 150, line2_x2 = 350, line2_y2 = 350;

    // 3. Completely outside
    int line3_x1 = 50, line3_y1 = 50, line3_x2 = 80, line3_y2 = 80;

    // Draw all lines initially
    setcolor(RED); // Default color for lines
    line(line1_x1, line1_y1, line1_x2, line1_y2); // Partially inside
    line(line2_x1, line2_y1, line2_x2, line2_y2); // Completely inside
    line(line3_x1, line3_y1, line3_x2, line3_y2); // Completely outside

    int choice;
    do {
        cout << "Enter the line number to clip (1: Partially inside, 2: Completely inside, 3: Completely outside, 0: Exit): ";
        cin >> choice;

        switch (choice) {
            case 1:
                // Clip the first line (partially inside)
                cohenSutherlandLineClip(line1_x1, line1_y1, line1_x2, line1_y2, x_min, y_min, x_max, y_max);
                break;
            case 2:
                // Clip the second line (completely inside)
                cohenSutherlandLineClip(line2_x1, line2_y1, line2_x2, line2_y2, x_min, y_min, x_max, y_max);
                break;
            case 3:
                // Clip the third line (completely outside)
                cohenSutherlandLineClip(line3_x1, line3_y1, line3_x2, line3_y2, x_min, y_min, x_max, y_max);
                break;
            case 0:
                break; // Exit the loop
            default:
                cout << "Invalid choice. Please enter a number between 0 and 3." << endl;
        }
    } while (choice != 0);

    getch(); // Wait for a key press
    closegraph(); // Close the graphics mode
    return 0;
}

