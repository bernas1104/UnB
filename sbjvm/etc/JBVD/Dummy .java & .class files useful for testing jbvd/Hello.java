package javassist.javassistextended;
public class Hello{

	protected int w;
	private int l;
	private int m;
	long ln;
	double d;
	float f;
	short s=4;
	byte b;
	boolean bool;
	char c;
	String str;
	int in = 1;
	String[] arr;
	int[] a;

	public Hello(int x){
		this.l = x;
	}

	private Hello(){
	}
	
	Hello(int x, byte g){
	}

     public void say() {
         int i=5;
         int j=10;
         int y=i+j;

     }

    public int calc(){
      return 5+3;
    }

    public int sw(int i){
		int j = 5;
		switch (i) {
        		case 0:
				j=0;
				break;
        		case 1:
				j=1;
				break;
        		case 2: case 3:
				j=2;
				break;
        		default:
				j=-1;
		}
		return j;
    }
}
