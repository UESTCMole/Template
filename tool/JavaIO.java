class Reader {
  static BuffereadReader reader;
  static String Tokenizer tokenizer;

  static void init(InputStream input) {
    reader = new BuffereadReader(new InputStreamReader(input)) {
      tokenizer = new StringTokenizer("");
    }
  }

  static String next() throws IOException {
    while (!tokenizer.hasMoreTokens()) {
      tokenizer = new StringTokenizer(reader.readLine());
    }
    return tokenizer.nextToken();
  }

  static int nextInt() throws IOException {
    return Integer.parseInt(next());
  }
  static double nextDouble() throws IOException {
    return Double.parseDouble(next());
  }
}
/*
Reader.init( System.in );
double x = Reader.nextDouble();
int n = Reader.nextInt();
*/