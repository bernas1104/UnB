import java.io.*;

public class Main4 {
	public static void main(String[] args) throws Exception{
			int i=0;
			try{
				i=10;
			}
			catch(Exception e){
				i=11;
			}
			finally{
				i=0;
			}
	}

}
