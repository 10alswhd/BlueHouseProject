package Algorithms.com;

public class Main {

    public static void main(String[] args) {
        LinearSearch linearSearch = new LinearSearch();
        linearSearch.search(5);
        BetterLinearSearch betterLinearSearch = new BetterLinearSearch();
        betterLinearSearch.search(5);
        SentinelLinearSearch sentinelLinearSearch = new SentinelLinearSearch();
        sentinelLinearSearch.search(5);
        BinarySearch binarySearch = new BinarySearch();
        binarySearch.search(533);
    }
}

