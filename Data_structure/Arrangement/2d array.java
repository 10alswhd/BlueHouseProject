// Added a double array to keep values from each column
        double[] day = new double[4];
        int[][] temperatures = new int[4][7];
        temperatures[0][0] = 73;
        temperatures[0][1] = 71; temperatures[0][2] = 68; temperatures[0][3] = 69; temperatures[0][4] = 75; temperatures[0][5] = 77; temperatures[0][6] = 78;
        temperatures[1][0] = 76; temperatures[1][1] = 73; temperatures[1][2] = 72; temperatures[1][3] = 72; temperatures[1][4] = 75; temperatures[1][5] = 79; temperatures[1][6] = 76;
        temperatures[2][0] = 79; temperatures[2][1] = 82; temperatures[2][2] = 84; temperatures[2][3] = 84; temperatures[2][4] = 81; temperatures[2][5] = 78; temperatures[2][6] = 78;
        temperatures[3][0] = 75; temperatures[3][1] = 72; temperatures[3][2] = 68; temperatures[3][3] = 69; temperatures[3][4] = 65; temperatures[3][5] = 63; temperatures[3][6] = 65;
        for (int row = 0; row < 4; row++){
            // moved sum here to reset to zero after each iteration
            int sum = 0;
            // fixed column > 7 to column < 7 --- You had it set to greater than thus it will not iterate.
            for (int column = 0; column < 7; column++) {
                sum = sum + temperatures[row][column];
            }
            day[row] = sum / 4;
            // cleaned up the output
            System.out.println("Day " + row + ": " + day[row]);
        }
