package complete;

public class FindNumberofIsland {

	private static final int[][] M = null;

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub

		int M[][] = { { 1, 1, 0, 0, 0 }, { 0, 1, 0, 0, 1 }, { 1, 0, 0, 1, 1 },
				{ 0, 0, 0, 0, 0 }, { 1, 0, 1, 0, 1 } };
		System.out.println(countIslands(M));

	}

	public static boolean isSafe(int M[][], int row, int col,
			boolean visited[][]) {
		return (row >= 0) && (row < M.length) && (col >= 0)
				&& (col < M[0].length)
				&& ((M[row][col] == 1) && !visited[row][col]); // value is 1
																// and
		// not yet
		// visited
	}

	// A utility function to do DFS for a 2D boolean matrix. It only considers
	// the 8 neighbors as adjacent vertices
	public static void DFS(int M[][], int row, int col, boolean visited[][]) {
		int rowNbr[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
		int colNbr[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

		// Mark this cell as visited
		visited[row][col] = true;

		// Recur for all connected neighbours
		for (int k = 0; k < 8; ++k) {
			if (isSafe(M, row + rowNbr[k], col + colNbr[k], visited))
				DFS(M, (row + rowNbr[k]), (col + colNbr[k]), visited);
		}
	}

	public static int countIslands(int M[][]) {
		// Make a bool array to mark visited cells.
		// Initially all cells are unvisited
		boolean visited[][] = new boolean[M.length][M[0].length];

		// Initialize count as 0 and travese through the all cells of
		// given matrix
		int count = 0;
		for (int i = 0; i < M.length; ++i)
			for (int j = 0; j < M[0].length; ++j)
				if (M[i][j] == 1 && !visited[i][j]) // If a cell with value 1 is
				// not
				{ // visited yet, then new island found
					DFS(M, i, j, visited); // Visit all cells in this island.
					++count; // and increment island count
				}

		return count;
	}

}
