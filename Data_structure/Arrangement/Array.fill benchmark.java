@Setup
public void setup() {
  length = 1 << pow2size;
  arrayB = new byte[length];
  arrayC = new char[length/2];
  arrayS = new short[length/2];
  arrayI = new int[length/4];
  arrayF = new float[length/4];
  arrayL = new long[length/8];
  arrayD = new double[length/8];
  arrayO = new Object[length/4];
}

@Benchmark
public void fillBytes() {
  Arrays.fill(arrayB, b);
}
@Benchmark
public void fillChars() {
  Arrays.fill(arrayC, c);
}

@Benchmark
public void fillShorts() {
  Arrays.fill(arrayS, s);
}

@Benchmark
public void fillInts() {
  Arrays.fill(arrayI, i);
}

@Benchmark
public void fillFloats() {
  Arrays.fill(arrayF, f);
}

@Benchmark
public void fillLongs() {
  Arrays.fill(arrayL, l);
}
@Benchmark
public void fillDoubles() {
  Arrays.fill(arrayD, d);
}

@Benchmark
public void fillObjects() {
  Arrays.fill(arrayO, o);
}
