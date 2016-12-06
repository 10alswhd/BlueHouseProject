class SampleComparator implements Comparator<Sample> {
  public int compare(Sample s1, Sample s2) {
    // e.g. Compare name
    return s1.getName().compareTo(s2.getName());
  }
}

// samples is list of Sample class
Collections.sort(samples, new SampleComparator())
