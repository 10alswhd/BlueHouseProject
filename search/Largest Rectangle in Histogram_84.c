/*O(n)时间O(n)空间*/
class Solution {
public:
    int largestRectangleArea(vector<int> &height) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        stack<int > st;
        int index = 0;
        int res = 0;
        st.push(-1);
        for(; index <= height.size(); ++index){
            for(; st.top() != -1 && (index == height.size() || height[st.top()] > height[index]); ){
                int tmp = st.top();
                st.pop();
                res = max(res, height[tmp] * (index - st.top() - 1));
            }
            st.push(index);
        }
        return res;
    }
};
