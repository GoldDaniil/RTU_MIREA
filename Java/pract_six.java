RoadBike.java:
  
package bikeproject;

public class RoadBike extends Bike {
    private int tyreWidth;
    private int postHeight;

    public RoadBike() {
        this("drop", "racing", "tread less", "razor", 19, 20, 22);
    }

    public RoadBike(int postHeight) {
        this("drop", "racing", "tread less", "razor", 19, 20, postHeight);
    }

    public RoadBike(String handleBars, String frame, String tyres, String seatType, int numGears, int tyreWidth, int postHeight) {
        super(handleBars, frame, tyres, seatType, numGears);
        this.tyreWidth = tyreWidth;
        this.postHeight = postHeight;
    }

    @Override
    public void printDescription() {
        super.printDescription();
        System.out.println("this Roadbike bike has " + this.tyreWidth + "mm tyres and a post height of " + this.postHeight);
    }
}




BikeDriver.java:

package bikeproject;

public class BikeDriver {
    public static void main(String[] args) {
        RoadBike bike1 = new RoadBike();
        RoadBike bike2 = new RoadBike("drop", "tourer", "semi-grip", "comfort", 14, 25, 18);
        MountainBike bike3 = new MountainBike();
        Bike bike4 = new Bike();
        bike1.printDescription();
        bike2.printDescription();
        bike3.printDescription();
        bike4.printDescription();
    }
}


Bike.java:

package bikeproject;

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




MountainBike.java:

package bikeproject;

public class MountainBike extends Bike {
    private String suspension;
    private String type;
    private int frameSize;

    public MountainBike() {
        this("Bull Horn", "Hardtail", "Maxxis", "dropper", 27, "RockShox XC32", "Pro", 19);
    }

    public MountainBike(String handleBars, String frame, String tyres, String seatType, int numGears, String suspension, String type, int frameSize) {
        super(handleBars, frame, tyres, seatType, numGears);
        this.suspension = suspension;
        this.type = type;
        this.frameSize = frameSize;
    }

    @Override
    public void printDescription() {
        super.printDescription();
        System.out.println("this mountain bike is a " + this.type + " bike and has a " + this.suspension + " suspension and a frame size of " + this.frameSize + " inches");
    }
}
