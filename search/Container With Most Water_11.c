int maxArea(vector<int> &height) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    int left = 0;
    int right = height.size() - 1;
    int maxarea = 0;
    int area;
    while (left < right){
        area = min(height[left], height[right]) * (right - left);
        maxarea = max(maxarea, area);
        if (height[left] < height[right])
            ++left;
        else
            --right;
    }
    return maxarea;
}
