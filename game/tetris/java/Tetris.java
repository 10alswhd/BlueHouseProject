import java.util.Arrays;
import java.util.Random;
import java.util.Scanner;
public class Tetris {
	/* Definitions of Data structures */
	public static final boolean O = true;
	public static final boolean X = false;
	public static final int SIZE = 10;
	/**
	 * Block Bar
	 */
	static final int BLOCK_TAG_I = 0;
	static final boolean[][] BLOCK_I = new boolean[][] {
		{ O },
		{ O },
		{ O },
		{ O }
	};
	static final boolean[][] BLOCK_I_ROTATED = new boolean[][] {
		{ O, O, O, O }
	};

	/**
	 * Block O
	 */
	static final int BLOCK_TAG_O = 1;
	static final boolean[][] BLOCK_O = new boolean[][] {
		{ O, O },
		{ O, O } 
	};

	/**
	 * Block T
	 */
	static final int BLOCK_TAG_T = 2;
	static final boolean[][] BLOCK_T = new boolean[][] {
		{ X, O, X },
		{ O, O, O }
	};
	static final boolean[][] BLOCK_T_ROTATED = new boolean[][] {
		{ O, O, O },
		{ X, O, X }
	};

	/**
	 * Block J
	 */
	static final int BLOCK_TAG_J = 3;
	static final boolean[][] BLOCK_J = new boolean[][] {
		{ O, X, X },
		{ O, O, O } 
	};
	static final boolean[][] BLOCK_J_ROTATED = new boolean[][] {
		{ O, O, O },
		{ X, X, O }
	};
	/**
	 * Block Z
	 */
	static final int BLOCK_TAG_Z = 4;
	static final boolean[][] BLOCK_Z = new boolean[][] {
		{ O, X },
		{ O, O },
		{ X, O }
	};
	static final boolean[][] BLOCK_Z_ROTATED = new boolean[][] {
		{ O, O, X },
		{ X, O, O }
	};

	static final int BLOCK_COUNT = 5;
	// Use it like BLOCK_MAP[blockTag][rotote?1:0]
	static final boolean[][][][] BLOCK_MAP = new boolean[][][][] {
			{ BLOCK_I, BLOCK_I_ROTATED },
			{ BLOCK_O, BLOCK_O },
			{ BLOCK_T, BLOCK_T_ROTATED },
			{ BLOCK_J, BLOCK_J_ROTATED },
			{ BLOCK_Z, BLOCK_Z_ROTATED }, };

	/* Logics */
	public static Scanner scanner = new Scanner(System.in);
	public static int getTop(boolean[][] map, boolean[][] block, int idx, int current, int row, int col){
		return (row < block.length) ? ((col < block[row].length) ? ((row + current >= 0 && block[row][col] && map[row + current][col + idx]) ? current-1 : getTop(map,block,idx,current,row,col+1)) : getTop(map,block,idx,current,row+1,0)) : ((current < SIZE-block.length) ? getTop(map, block, idx, current + 1, 0, 0) : (SIZE - block.length));
	}
	public static int execute(boolean[][] map, boolean[][] block, int idx) {
		int originalTop = getTop(map,block,idx,-block.length,0,0), top = getTop(map,block,idx,-block.length,0,0), l = block.length;
		for (int row = l - 1; row >= 0; row--) {
			for (int col = 0; (col < block[row].length)&&((row + top < 0) ? X : (map[row + top][col + idx] |= block[row][col])?true:true); col++);
			if (row + top >= 0) {
				Boolean[] line = new Boolean[SIZE];
				for (int i = 0; i < SIZE; i++) {
					line[i] = map[row + top][i];
				}
				if (!Arrays.asList(line).contains(false)) {
					for (int r = row + top++; r >= 0; r--) {
						map[r] = r==0?new boolean[SIZE]:map[r - 1];
					}
				}
			}
		}
		return top - originalTop;
	}
	public static String blockToString(boolean[][] block, boolean withidx, int i, int j) {
		return i < block.length ? (j<block[i].length ? (withidx ? (i==0&&j==0?("   0 1 2 3 4 5 6 7 8 9".substring(0, (block[0].length + 1) * 2) + "\n"):"") + (j==0?" " + i : ""):"") + (block[i][j] ? " $" : (withidx ? " ." : "  ")) + (j+1 == block[i].length?"\n":"") + blockToString(block, withidx, i, j+1) : blockToString(block, withidx, i+1, 0)) : "";
	}
	public static boolean isEnd(boolean[][] map, int i) {
		return i < SIZE ? (map[0][i]?true:isEnd(map,i+1)): false;
	}
	public static void main(String[] args) {
		boolean map[][] = new boolean[SIZE][SIZE], block[][], rotate;
		String score = "0", s;
		while (!isEnd(map, 0)) {
			int blockTag = Math.abs(new Random().nextInt()) % BLOCK_COUNT, idx = -1, flag=0;
			while (flag==0||!((rotate=(s=scanner.nextLine().trim()).equalsIgnoreCase("y"))||s.equalsIgnoreCase("n"))||((block = BLOCK_MAP[blockTag+(flag=0)][rotate ? 1 : 0])==null?false:false)) {
				System.out.print((flag==0?"Current Block\n" + blockToString(BLOCK_MAP[blockTag][0], false, 0,0) + "Rotated\n" + blockToString(BLOCK_MAP[blockTag][1], false, 0,0) + "\n" + blockToString(map, true, 0,0):"")+"Rotate Block?(y/n) : " + (((flag=1)==0?"":"")));
			}
			while (flag==0||!((s=scanner.nextLine().trim()).matches("-?\\d+(\\.\\d+)?"))||!(0 <= (idx=Integer.parseInt(s)) && idx <= SIZE - block[0].length)) {
				System.out.print("Index (0 ~ " + (SIZE - block[0].length) + ") : " + (((flag=1)==0?"":"")));
			}
			System.out.println("Score : " + (score=""+((Integer.parseInt(score) + execute(map, block, idx)))) + (isEnd(map,0)?("\n" + blockToString(map, true, 0,0) + "\nGame Over! 20125012"):""));
		}
	}
}
