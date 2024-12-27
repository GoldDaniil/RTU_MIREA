public class Bike {
    private String handleBars;
    private String frame;
    private String tyres;
    private String seatType;
    private int NumGears;
    private final String make;

    public Bike() {
        this.handleBars = "default handlebars";
        this.frame = "default frame";
        this.tyres = "default tyres";
        this.seatType = "default seat";
        this.NumGears = 1;
        this.make = "Oracle Cycles";
    }


    public Bike(String handleBars, String frame, String tyres, String seatType, int numGears) {
        this.handleBars = handleBars;
        this.frame = frame;
        this.tyres = tyres;
        this.seatType = seatType;
        this.NumGears = numGears;
        this.make = "Oracle Cycles";
    }

    protected void printDescription() {
        System.out.println("\n" + this.make + "\n" + "this bike has " + this.handleBars + " handlebars on a " + this.frame + " frame with " + this.NumGears + " gears." + "\nIt has a " + this.seatType + " seat with " + this.tyres + " tyres");
    }
}
