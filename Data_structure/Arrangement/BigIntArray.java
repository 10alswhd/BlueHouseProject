public class BigIntArray {
    
  private long address;
    
  private final static int INT_BYTE_SIZE = 4;
    
  public BigIntArray(long size) {
    address = getUnsafe().allocateMemory(size * INT_BYTE_SIZE);
  }
    
  public void set(long idx, int val) {
    getUnsafe().putInt(address + idx * INT_BYTE_SIZE, val);
  }
    
  public int get(long idx) {
    return getUnsafe().getInt(address + idx * INT_BYTE_SIZE);   
  }
    
  public void free() {
    getUnsafe().freeMemory(address);
  }
}
