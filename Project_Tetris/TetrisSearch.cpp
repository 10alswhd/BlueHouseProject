// TetrisSearch.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

struct Point {
	int r;
	int c;

	Point(int r, int c) : r(r), c(c) {};
	~Point() = default;
	
	Point Offset(Point offset) const {
		return Point(r + offset.r, c + offset.c);
	}

	bool Bound(int rmin, int rmax, int cmin, int cmax) const {
		return rmin <= r && r < rmax &&
			cmin <= c && c < cmax;
	}
};
using Cell = int;
using Table = vector<vector<Cell>>;
using Shape = vector<Point>;
using ShapeGroup = vector<Shape>;
const Cell EMPTY = -1;

const ShapeGroup Line = {
	{ { 0,0 },{ 0,1 },{ 0,2 },{ 0,3 } },
	{ { 0,0 },{ 1,0 },{ 2,0 },{ 3,0 } }
};
const ShapeGroup Square = {
	{ { 0,0 },{0,1}, {1,0}, {1,1} }
};
const ShapeGroup Cross = {
	{ { 0,0 },{ 0,1 },{ 0,2 },{ 1,1 } },
	{ { 0,0 },{ 0,1 },{ 0,2 },{ -1,1 } },
	{ { 0,0 },{ 1,0 },{ 2,0 },{ 1,1 } },
	{ { 0,0 },{ 1,0 },{ 2,0 },{ 1,-1 } },
};
const ShapeGroup S = {
	{ { 0,0 },{ 1,0 },{ 0,1 },{ -1,1 } },
	{ { 0,0 },{ 0,1 },{ 1,1 },{ 1,2 } },
};
const ShapeGroup ReverseS = {
	{ { 0,0 },{ 1,0 },{ 1,1 },{ 2,1 } }, 
	{ { 0,0 },{ 0,1 },{ -1,1 },{ -1,2 } }, 
};
const ShapeGroup L = {
	{ { 0,0 },{ 1,0 },{ 2,0 },{ 2,1 } }, 
	{ { 0,0 },{ 0,1 },{ 0,2 },{ -1,2 } }, 
	{ { 0,0 },{ 0,1 },{ 1,1 },{ 2,1 } }, 
	{ { 0,0 },{ 1,0 },{ 0,1 },{ 0,2 } }, 
};
const ShapeGroup ReverseL = {
	{ { 0,0 },{ 1,0 },{ 2,0 },{ 2,-1 } }, 
	{ { 0,0 },{ 0,1 },{ 0,2 },{ 1,2 } }, 
	{ { 0,0 },{ 0,1 },{ 1,0 },{ 2,0 } },
	{ { 0,0 },{ 1,0 },{ 1,1 },{ 1,2 } }, 
};

ostream& operator<<(ostream& os, const Point& point) {
	return os << '(' << point.r << "," << point.c << ')';
}

ostream& operator<<(ostream& os, const Shape& shape) {
	os << "{ ";
	for (auto& point : shape) {
		os << point << " ";
	}
	os << "}";
	return os;
}

ostream& operator<<(ostream& os, const ShapeGroup& shapeGroup) {
	os << "ShapeGroup( " << endl;
	for (auto& shape : shapeGroup) {
		os << " - " << shape << endl;
	}
	os << ")";
	return os;
}

ostream& operator<<(ostream& os, const Table& table) {
	os << " - TABLE - " << endl;
	for (int i = 0; i < table.size(); i++) {
		for (int j = 0; j < table[i].size(); j++) {
			os << table[i][j] << ' ';
		}
		os << endl;
	}
	os << " - /TABLE - " << endl;
	return os;
}

bool fits(Table& table, Point& offset, const Shape& shape) {
	for (auto point : shape) {
		Point target = point.Offset(offset);
		if (!target.Bound(0, table.size(), 0, table[0].size()))
			return false;
		if (table[target.r][target.c] != EMPTY)
			return false;
	}
	return true;
}

void place(Table& table, Point& offset, Shape& shape, Cell mark) {
	for_each(shape.begin(), shape.end(), [&](const Point point) -> void {
		Point targeted = point.Offset(offset);
		table[targeted.r][targeted.c] = mark;
	});
}

bool recurse(Table& table, list<ShapeGroup>& shapeGroups) {
	if (shapeGroups.empty())
		return true;

	ShapeGroup shapeGroup = shapeGroups.front();
	shapeGroups.pop_front();
	Cell mark = shapeGroups.size();
	for (int r = 0; r < table.size(); r++) {
		for (int c = 0; c < table[r].size(); c++) {
			for (Shape &shape : shapeGroup) {
				Point offset(r, c);
				if (fits(table, offset, shape)) {
					place(table, offset, shape, mark);
					if (recurse(table, shapeGroups)) {
						return true;
					}
					place(table, offset, shape, EMPTY);
				}
			}
		}
	}
	shapeGroups.push_front(shapeGroup);
	return false;
}

int main()
{
	cout << "Hello!" << endl;
	int c = 5;
	int r = 5;
	Table table(r, vector<Cell>(c, EMPTY));

	Point point(0,1);
	cout << point << endl;

	list<ShapeGroup> shapes = { Line, Line, Line, Line, Line, Line, Line };

	cout << "Searching for " << shapes.size() << " items" << endl;
	bool result = recurse(table, shapes);
	cout << table;

	cin >> c;
    return 0;
}
