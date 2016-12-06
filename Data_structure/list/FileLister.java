package sample.filelist;

import java.io.File;
import java.io.IOException;
import java.util.Arrays;
import java.util.List;
import java.util.Random;

public class FileLister {

	public static void main(String[] args) throws IOException {
		File dir = new File("./temp");

		long s = System.currentTimeMillis();
		initialize(dir);
		long e = System.currentTimeMillis();
		long d = e - s;
		System.out.println("initialized in " + d + " ms");

		s = System.currentTimeMillis();
		List<File> files = list(dir);
		e = System.currentTimeMillis();
		d = e - s;
		System.out.println("listed in " + d + " ms");

		s = System.currentTimeMillis();
		delete(files);
		e = System.currentTimeMillis();
		d = e - s;
		System.out.println("deleted in " + d + " ms");
	}

	private static List<File> list(File dir) {
		List<File> files = Arrays.asList(dir.listFiles());
		System.out.println("file count: " + files.size());

		for (File file : files) {
			StringBuilder builder = new StringBuilder();
			builder.append("{name=").append(file.getName()).append(", length=")
					.append(file.length()).append(", lastModified=")
					.append(file.lastModified()).append(", directory=")
					.append(file.isDirectory()).append(", file=")
					.append(file.isFile()).append(", hidden=")
					.append(file.isHidden()).append(", execuable=")
					.append(file.canExecute()).append(", readable=")
					.append(file.canRead()).append(", writable=")
					.append(file.canWrite()).append("}");
			System.out.println("file: " + builder.toString());
		}

		return files;
	}

	public static void delete(List<File> files) {
		for (File file : files) {
			file.delete();
		}
	}

	public static void initialize(File dir) throws IOException {
		Random r = new Random();
		dir.mkdirs();

		for (int i = 0; i < 10; i++) {
			File file = File.createTempFile("file-", "", dir);
			file.setLastModified(System.currentTimeMillis() - r.nextInt(600000));
			file.setExecutable(r.nextBoolean());
			file.setReadable(r.nextBoolean());
			file.setWritable(r.nextBoolean());
		}
	}

}
