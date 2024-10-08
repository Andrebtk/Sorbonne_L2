public class Bouteille {
    private double volume;

    public Bouteille (double volume) {
        this.volume = volume;
    }
    
    public Bouteille () {
        this (1.5);
    }
    
    public void remplir (Bouteille b) {
        volume += b.volume; 
        b.volume = 0;
    }

	public void remplir (double volume) {
		this.volume += volume; 
	}

    public String toString () {
        return "Volume = " + volume;
    }

}