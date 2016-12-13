/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */

class Solution {
public:
    vector<Interval> insert(vector<Interval> &intervals, Interval newInterval) {
        vector<Interval>::iterator iter = intervals.begin();
        vector<Interval> res;
        for(; iter != intervals.end() && iter->end < newInterval.start; ++iter){
            res.push_back(*iter);
        }
        if(iter == intervals.end()){
            res.push_back(newInterval);
            return res;
        }
        newInterval.start = min(newInterval.start, iter->start);
        for(; iter != intervals.end() && iter->start <= newInterval.end; ++iter){
            newInterval.end = max(newInterval.end, iter->end);
        }
        res.push_back(newInterval);
        for(; iter != intervals.end(); ++iter){
            res.push_back(*iter);
        }
        return res;
    }
};

class Solution {
public:
    vector<Interval> insert(vector<Interval> &intervals, Interval newInterval) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if(intervals.size() == 0 || newInterval.start > intervals[intervals.size() - 1].end){ 
            intervals.push_back(newInterval);
            return intervals;
        }else if(newInterval.end < intervals[0].start){
            intervals.insert(intervals.begin(), newInterval);
            return intervals;
        }
        
        vector<Interval> res;
        int i = 0;
        for(; i<intervals.size() && intervals[i].end < newInterval.start; ++i){
            res.push_back(intervals[i]);
        }
        if(i == intervals.size()){
            res.push_back(newInterval);
            return res;
        }
        newInterval.start = min(intervals[i].start, newInterval.start);
        for(; i<intervals.size() && intervals[i].start <= newInterval.end; ++i);
        newInterval.end = max(intervals[i-1].end, newInterval.end);
        res.push_back(newInterval);
        for(; i<intervals.size(); ++i){
            res.push_back(intervals[i]);
        }
        return res;
    }
};
