#include <math.h>
#include <string.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <random>
#include <vector>

using namespace std;

typedef struct point {
    int x;
    int y;
    char c;
};

typedef struct line {
    point p1;
    point p2;
};

point polygon[100];

float ComputeAngle(point p1, point p2) {
    int dx, dy, ax, ay;
    float angle;
    dx = p2.x - p1.x;
    ax = abs(dx);
    dy = p2.y - p1.y;
    ay = abs(dy);
    angle = (ax + ay == 0) ? 0.0 : (float)dy / (ax + ay);
    if (dx < 0)
        angle = 2.0 - angle;
    else if (dy < 0)
        angle = 4.0 + angle;
    return angle * 90.0;
}

// compute a dot is in a polygonVec or not
int crossPointCount = 0;
bool IsInsidePoint(point p, vector<point> polygonVec) {
    int i, j, size = polygonVec.size();
    bool c = false;
    for (i = 0, j = size - 1; i < size; j = i++) {  // i, j is index / j = i - 1 (when i = 0, j = size - 1)
        if (((polygonVec[i].y > p.y) != (polygonVec[j].y > p.y)) &&
            // ���а� ���� y��ǥ�� ���� ���� x��ǥ�� p.x���� ���� ��츸 ������ ����
            // ���: ������ ���� * (p.y - ������ �������� y��ǥ) + ������ �������� x��ǥ
            (p.x < (polygonVec[j].x - polygonVec[i].x) * (p.y - polygonVec[i].y) / (polygonVec[j].y - polygonVec[i].y) + polygonVec[i].x)) {
            c = !c;  // toggle c - ������ Ȧ������ true, ¦������ false
            crossPointCount++;
        }
    }
    return c;
}

int main() {
    // ----------------------------------------------------------------------------
    // ------------------ 9-1. �־��� ���鿡 ���� �ܼ� �ٰ��� ���� �� ��� ------------------
    // ----------------------------------------------------------------------------
    point poly[8];
    //--
    poly[0].x = 3;
    poly[0].y = 4;
    poly[0].c = 'A';
    poly[1].x = 1;
    poly[1].y = 2;
    poly[1].c = 'B';
    poly[2].x = 2;
    poly[2].y = 5;
    poly[2].c = 'C';
    poly[3].x = 2;
    poly[3].y = 6;
    poly[3].c = 'D';
    poly[4].x = 9;
    poly[4].y = 3;
    poly[4].c = 'E';
    poly[5].x = 5;
    poly[5].y = 3;
    poly[5].c = 'F';
    poly[6].x = 6;
    poly[6].y = 4;
    poly[6].c = 'G';
    poly[7].x = 8;
    poly[7].y = 4;
    poly[7].c = 'H';
    //--

    float polyAngle[8];
    // ������ : B
    // compute Anlges of poly - with respect to B
    for (int i = 0; i < 8; i++) {
        polyAngle[i] = ComputeAngle(poly[1], poly[i]);
    }

    // make map of poly and its angles
    map<char, float> polyMap;
    for (int i = 0; i < 8; i++) {
        polyMap.insert(pair<char, float>(poly[i].c, polyAngle[i]));
    }
    // sort map by value with Insertion sort
    vector<pair<char, float>> polyVec;
    for (auto &p : polyMap) {
        polyVec.push_back(p);
    }
    for (int i = 1; i < polyVec.size(); i++) {
        for (int j = 0; j < i; j++) {
            if (polyVec[i].second < polyVec[j].second) {
                polyVec.insert(polyVec.begin() + j, polyVec[i]);
                polyVec.erase(polyVec.begin() + i + 1);
                break;
            }
        }
    }

    // vector<pair<char, float>> polyVec(polyMap.begin(), polyMap.end());
    // sort(polyVec.begin(), polyVec.end(),
    //      [](const pair<char, float> &l, const pair<char, float> &r) {
    //          return l.second < r.second;
    //      });

    // print sorted map
    cout << "------------------ 9-1. �־��� ���鿡 ���� �ܼ� �ٰ��� ���� �� ��� ------------------" << endl;
    cout << "�־��� ������ ����: " << endl;
    for (auto &p : polyVec) {
        cout << p.first << " - " << p.second << endl;
    }
    // ������ �ܼ� �ٰ��� ��� (print sorted map)
    cout << "�־��� ������ ������ �ܼ� �ٰ���: ";
    for (auto &p : polyVec) {
        cout << p.first << " - ";
    }
    cout << polyVec[0].first << endl
         << endl
         << endl;

    // ---------------------------------------------------------------------------------------------------------
    // ------------------ 9-1. N���� random�� ���� ���� Polygon ����, ���� ��� ȸ��, ���� �� ȸ�� ��� ------------------
    // ---------------------------------------------------------------------------------------------------------

    vector<int> xList, yList;
    int N = 100;

    for (int i = 0; i < N; i++) {
        xList.push_back(i);
        yList.push_back(i);
    }

    // shuffle the vector
    random_device rd;
    default_random_engine rng(rd());
    shuffle(xList.begin(), xList.end(), rng);
    shuffle(yList.begin(), yList.end(), rng);

    // make random polygon
    for (int i = 0; i < N; i++) {
        polygon[i].x = xList[i];
        polygon[i].y = yList[i];
        polygon[i].c = i;
    }

    // compute angles of polygon
    float polygonAngle[N];
    // ������ : 0
    // compute Anlges of poly - with respect to point 0
    int computeAngleCount = 0;
    for (int i = 0; i < N; i++) {
        computeAngleCount++;
        polygonAngle[i] = ComputeAngle(polygon[0], polygon[i]);
    }
    // make map of poly and its angles
    map<char, float> polygonMap;
    for (int i = 0; i < N; i++) {
        polygonMap.insert(pair<char, float>(polygon[i].c, polygonAngle[i]));
    }
    // sort map by value with Insertion sort
    int compareCount = 0;
    vector<pair<char, float>> polygonVec;
    for (auto &p : polygonMap) {
        polygonVec.push_back(p);
    }
    for (int i = 1; i < polygonVec.size(); i++) {
        for (int j = 0; j < i; j++) {
            compareCount++;
            if (polygonVec[i].second < polygonVec[j].second) {
                polygonVec.insert(polygonVec.begin() + j, polygonVec[i]);
                polygonVec.erase(polygonVec.begin() + i + 1);
                break;
            }
        }
    }

    // print sorted map
    cout << "------------------ 9-1. 100���� random�� ���� ���� Polygon ����, ���� ��� ȸ��, ���� �� ȸ�� ��� ------------------" << endl;
    cout << "������ ������ ����: " << endl;
    for (auto &p : polygonVec) {
        cout << to_string(p.first) << " - " << p.second << " / ";
    }
    cout << endl
         << endl;
    // ������ �ܼ� �ٰ��� ��� (print sorted map), ���� ��� ȸ��, ���� �� ȸ�� ���
    cout << "������ ������ ������ �ܼ� �ٰ���: " << endl;
    for (auto &p : polygonVec) {
        cout << to_string(p.first) << " - ";
    }
    cout << to_string(polygonVec[0].first) << endl
         << endl;
    cout << "���� ��� ȸ��: " << computeAngleCount << endl;
    cout << "���� �� ȸ��: " << compareCount << endl;

    // ---------------------------------------------------------------------------------------------------------
    // -------------------------- 9-2. �Է��� �� Z(x,y)�� Polygon ���� �����ϴ� ���� �� ��� ----------------------------
    // ---------------------------------------------------------------------------------------------------------

    // input point Z
    cout << "-------------------------- 9-2. �Է��� �� Z(x,y)�� Polygon ���� �����ϴ� ���� �� ��� ----------------------------" << endl;
    point Z;
    cout << "�� Z(x,y)�� �Է��ϼ���:";
    cin >> Z.x >> Z.y;

    // make sorted polygon vector include x, y with polygonVec
    vector<point> sortedPolygon;
    for (auto &p : polygonVec) {
        sortedPolygon.push_back(polygon[p.first]);
    }

    // �Է� ���� �� Z�� Polygon ���� �����ϴ� ���� �� ���
    if (IsInsidePoint(Z, sortedPolygon)) {
        cout << "�Է¹��� �� Z(x,y)�� Polygon ���� �����մϴ�." << endl;
    } else {
        cout << "�Է¹��� �� Z(x,y)�� Polygon ���� �������� �ʽ��ϴ�." << endl;
    }

    // ������ ���� ���
    cout << "������ ����: " << crossPointCount << endl;
}
