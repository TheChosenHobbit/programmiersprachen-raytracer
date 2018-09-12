import java.io.FileNotFoundException;
import java.io.PrintWriter;

public class animator{
	public static void main(String args[]) throws FileNotFoundException {

		for(int i =0; i<120; i++){
			PrintWriter out = new PrintWriter("animation" + (i+1) + ".txt");
			int currentx1 = -60+i;
			int currentx2 = -30+i;
		String animationOut = "define material red 1 0 0 1 0 0 1 0 0 0\n"+
							"define material blue 0 0 1 0 0 1 0 0 1 0\n"+
							"define material green 0 1 0 0 1 0 0 1 0 0\n"+
							"define shape box bottomplate -300 -40 0 300 -40 -400 green\n"+
							"define shape box movingbox "+ currentx1 +" -35 -100 "+ currentx2 +" -15 -70 red\n"+
							"define shape sphere bsphere 30 20 -100 15 green\n"+
							"define shape sphere bsphere1 0 0 -70 10 red\n"+
							"define light sun -40 50 0 .4 .4 .4 100\n"+
							"define camera cam 45 0 0 0 0 0 -1 0 1 0\n"+
							"render eye image.ppm 800 800\n"+
							"define backgroundcolor 0.0 0.1 0.6\n";
			out.write(animationOut);
        	out.flush();
        	out.close();
		}
	}	
}
