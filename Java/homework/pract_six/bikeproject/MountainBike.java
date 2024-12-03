package bikeproject;

public class MountainBike extends Bike {
    private String suspension;
    private String type;
    private int frameSize;

    public MountainBike() {
        this("bull", "hardtail", "max", "dropper", 27, "XC32", "pro", 19);
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
