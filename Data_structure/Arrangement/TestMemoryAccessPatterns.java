public class TestMemoryAccessPatterns {
  private static final int LONG_SIZE = 8;
  private static final int PAGE_SIZE = 2 * 1024 * 1024;
  private static final int ONE_GIG = 1024 * 1024 * 1024;

  private static final int ARRAY_SIZE = (int) (ONE_GIG / LONG_SIZE);
  private static final int WORDS_PER_PAGE = PAGE_SIZE / LONG_SIZE;

  private static final int ARRAY_MASK = ARRAY_SIZE - 1;
  private static final int PAGE_MASK = WORDS_PER_PAGE - 1;

  private static final int PRIME_INC = 514229;

  private static final long[] memory = new long[ARRAY_SIZE];

  static {
    for (int i = 0; i < ARRAY_SIZE; i++) {
      memory[i] = 777;
    }
  }

  public enum StrideType {
    LINEAR_WALK {
      public int
          next(final int pageOffset, final int wordOffset, final int pos) {
        return (pos + 1) & ARRAY_MASK;
      }
    },

    RANDOM_PAGE_WALK {
      public int
          next(final int pageOffset, final int wordOffset, final int pos) {
        return pageOffset + ((pos + PRIME_INC) & PAGE_MASK);
      }
    },

    RANDOM_HEAP_WALK {
      public int
          next(final int pageOffset, final int wordOffset, final int pos) {
        return (pos + PRIME_INC) & ARRAY_MASK;
      }
    };

    public abstract int next(int pageOffset, int wordOffset, int pos);
  }

  public static void main(final String[] args) {
    final StrideType strideType;
    switch (Integer.parseInt(args[0])) {
    case 1:
      strideType = StrideType.LINEAR_WALK;
      break;

    case 2:
      strideType = StrideType.RANDOM_PAGE_WALK;
      break;

    case 3:
      strideType = StrideType.RANDOM_HEAP_WALK;
      break;

    default:
      throw new IllegalArgumentException("Unknown StrideType");
    }

    for (int i = 0; i < 5; i++) {
      perfTest(i, strideType);
    }
  }

  private static void
      perfTest(final int runNumber, final StrideType strideType) {
    final long start = System.nanoTime();

    int pos = -1;
    long result = 0;
    for (int pageOffset = 0; pageOffset < ARRAY_SIZE; pageOffset +=
        WORDS_PER_PAGE) {
      for (int wordOffset = pageOffset, limit = pageOffset + WORDS_PER_PAGE; wordOffset < limit; wordOffset++) {
        pos = strideType.next(pageOffset, wordOffset, pos);
        result += memory[pos];
      }
    }

    final long duration = System.nanoTime() - start;
    final double nsOp = duration / (double) ARRAY_SIZE;

    if (104287174656L != result) {
      throw new IllegalStateException();
    }

    System.out.format("%d - %.2fns %s\n", Integer.valueOf(runNumber),
        Double.valueOf(nsOp), strideType);
  }
}
