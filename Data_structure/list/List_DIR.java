public static void main(String[] args)
	{
		File dir = new File("d:\\Sublime Text Install");
		long z = System.currentTimeMillis();
		showDir(dir,0);
		long y = System.currentTimeMillis();
		System.out.println("所用时间："+(y-z));
	}
	public static String showLevel(int level)
	{
		StringBuilder sb = new StringBuilder();
		for(int x=0;x<level;x++)
		{
			//sb.append("  ");
			sb.insert(0,"  ");
		}
		return sb.toString();
	}
	public static void showDir(File dir,int level)
	{
		System.out.println(showLevel(level)+dir.getName());
		level++;
		File[] files = dir.listFiles();
		for(int x=0;x<files.length;x++)
		{
			if(files[x].isDirectory())
				showDir(files[x],level);
			else
				System.out.println(files[x]);
		}
	}
