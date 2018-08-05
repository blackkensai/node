package pkg;

public class Test {

    // --- Native methods
    public native void node_embed_execute_with(String script, Object object);

    public String sayHello(String name) {
    	return String.format("hello, %s", name);
    }

    public int plus(int a, int b) {
    	return a + b;
    }

    // --- Main method to test our native library
    public static void main(String[] args) {
        System.loadLibrary("Test");
        Test sample = new Test();
        sample.node_embed_execute_with("test-java.js", sample);
    }
}