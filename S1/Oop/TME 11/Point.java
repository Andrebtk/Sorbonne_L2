public class Point {
	public int x,y;
	public Point(int x, int y) { this.x=x; this.y=y; }
	
	public Point() {
		this((int)(Math.random()*500),(int)(Math.random()*500));
	}
	
	public String toString() {
		return "("+ x + "," + y + ") "; 
	}
	
	public double distanceTo(Point p) {
		int dx = p.x-x;
		int dy = p.y-y;
		return Math.sqrt(dx*dx+dy*dy);
	}

}	
