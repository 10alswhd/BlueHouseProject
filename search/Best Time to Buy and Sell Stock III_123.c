class Solution {
public:
    int maxProfit(vector<int> &prices) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int buy, sell, min, i;
        int maxpro = 0, pro = 0;
        int prohit = 0;
        if(prices.size() < 2) return 0;
        min = 0;
        buy = 0;
        sell = 0;
        for(i = 1; i < prices.size(); ++i){
            if(prices[min] >= prices[i])min = i;
            if(prohit < prices[i] - prices[min]){
                prohit = prices[i] - prices[min];
                sell = i;
                buy = min;
            }
        }
        min = 0;
        for(pro = 0, i = 1; i < buy; ++i){
            if(prices[min] >= prices[i])min = i;
            if(pro < prices[i] - prices[min]){
                pro = prices[i] - prices[min];
            }
        }
        maxpro = pro;
        for(pro = 0, min = sell + 1, i = sell + 2; i < prices.size(); ++i){
            if(prices[min] >= prices[i])min = i;
            if(pro < prices[i] - prices[min]){
                pro = prices[i] - prices[min];
            }
        }
        maxpro = max(maxpro, pro);
        for(pro = 0, min = sell - 1, i = sell - 2; i > buy; --i){
            if(prices[min] >= prices[i])min = i;
            if(pro < prices[i] - prices[min]){
                pro = prices[i] - prices[min];
            }
        }
        maxpro = max(maxpro, pro);
        return maxpro + prohit;
    }
};
