package ceng.ceng351.carpoolingdb;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class CarPoolingSystem implements ICarPoolingSystem {

    private static String url = "jdbc:h2:mem:carpoolingdb;DB_CLOSE_DELAY=-1"; // In-memory database
    private static String user = "sa";          // H2 default username
    private static String password = "";        // H2 default password

    private Connection connection;

    private static final String CREATE_TABLE_PARTICIPANTS =
            "CREATE TABLE Participants (" +
                    "PIN INT," +
                    "p_name VARCHAR(30)," +
                    "age INT," +
                    "PRIMARY KEY (PIN)" +
                    ");";

    private static final String CREATE_TABLE_PASSENGERS =
            "CREATE TABLE Passengers (" +
                    "PIN INT," +
                    "membership_status VARCHAR(30)," +
                    "PRIMARY KEY (PIN)," +
                    "FOREIGN KEY (PIN) REFERENCES Participants (PIN)" +
                    ");";

    private static final String CREATE_TABLE_DRIVERS =
            "CREATE TABLE Drivers (" +
                    "PIN INT," +
                    "rating FLOAT," +
                    "PRIMARY KEY (PIN)," +
                    "FOREIGN KEY (PIN) REFERENCES Participants (PIN)" +
                    ");";

    private static final String CREATE_TABLE_CARS =
            "CREATE TABLE Cars (" +
                    "CarID INT," +
                    "PIN INT," +
                    "color VARCHAR(20)," +
                    "brand VARCHAR(20)," +
                    "PRIMARY KEY (CarId)," +
                    "FOREIGN KEY (PIN) REFERENCES Drivers (PIN)" +
                    ");";

    private static final String CREATE_TABLE_TRIPS =
            "CREATE TABLE Trips (" +
                    "TripID INT," +
                    "CarID INT," +
                    "date DATE," +
                    "departure VARCHAR(30)," +
                    "destination VARCHAR(30)," +
                    "num_seats_available INT," +
                    "PRIMARY KEY (TripID)," +
                    "FOREIGN KEY (CarID) REFERENCES Cars (CarID)" +
                    ");";

    private static final String CREATE_TABLE_BOOKINGS =
            "CREATE TABLE Bookings (" +
                    "TripID INT," +
                    "PIN INT," +
                    "booking_status VARCHAR(30)," +
                    "PRIMARY KEY (TripID, PIN)," +
                    "FOREIGN KEY (TripID) REFERENCES Trips (TripID)," +
                    "FOREIGN KEY (PIN) REFERENCES Passengers (PIN)" +
                    ");";

    private static final String[] CREATE_TABLE_LIST = new String[]{
            CREATE_TABLE_PARTICIPANTS,
            CREATE_TABLE_PASSENGERS,
            CREATE_TABLE_DRIVERS,
            CREATE_TABLE_CARS,
            CREATE_TABLE_TRIPS,
            CREATE_TABLE_BOOKINGS
    };

    private static final String[] DROP_TABLE_LIST = new String[]{
            "Bookings",
            "Trips",
            "Cars",
            "Drivers",
            "Passengers",
            "Participants"
    };

    public void initialize(Connection connection) { this.connection = connection; }

    //Given: getAllDrivers()
    //Testing 5.16: All Drivers after Updating the Ratings
    @Override
    public Driver[] getAllDrivers() {
        List<Driver> drivers = new ArrayList<>();

        String query = "SELECT PIN, rating FROM Drivers ORDER BY PIN ASC;";

        try {
            PreparedStatement ps = this.connection.prepareStatement(query);
            ResultSet rs = ps.executeQuery();
            while (rs.next()) {
                int PIN = rs.getInt("PIN");
                double rating = rs.getDouble("rating");

                // Create a Driver object with only PIN and rating
                Driver driver = new Driver(PIN, rating);
                drivers.add(driver);
            }
            rs.close();
            ps.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        
        return drivers.toArray(new Driver[0]); 
    }

    
    //5.1 Task 1 Create tables
    @Override
    public int createTables() {
        int tableCount = 0;

        for (String createTableQuery : CREATE_TABLE_LIST) {
            try {
                connection.prepareStatement(createTableQuery).execute();
                tableCount += 1;
            }   catch (SQLException e) {
                e.printStackTrace();
            }
        }

        return tableCount;
    }


    //5.17 Task 17 Drop tables
    @Override
    public int dropTables() {
        int tableCount = 0;
        for (String tableName : DROP_TABLE_LIST) {
            try {
                String dropTableQuery = "DROP TABLE " + tableName + ";";

                connection.prepareStatement(dropTableQuery).execute();

                tableCount += 1;
            } catch (SQLException ignored) {
                
            }
        }
        return tableCount;
    }
    
    
    //5.2 Task 2 Insert Participants
    @Override
    public int insertParticipants(Participant[] participants) {
        int rowsInserted = 0;

        for (Participant participant : participants) {
            try {
                String insertionQuery = "INSERT INTO Participants (PIN, p_name, age) VALUES (?, ?, ?);";
                PreparedStatement insertionStatement = this.connection.prepareStatement(insertionQuery);

                insertionStatement.setInt(1, participant.getPIN());
                insertionStatement.setString(2, participant.getP_name());
                insertionStatement.setInt(3, participant.getAge());
                insertionStatement.execute();

                rowsInserted += 1;
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }

        return rowsInserted;
    }

    
    //5.2 Task 2 Insert Passengers
    @Override
    public int insertPassengers(Passenger[] passengers) {
        int rowsInserted = 0;

        for (Passenger passenger : passengers) {
            try {
                String insertionQuery = "INSERT INTO Passengers (PIN, membership_status) VALUES (?, ?);";
                PreparedStatement insertionStatement = this.connection.prepareStatement(insertionQuery);

                insertionStatement.setInt(1, passenger.getPIN());
                insertionStatement.setString(2, passenger.getMembership_status());
                insertionStatement.execute();

                rowsInserted += 1;
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        
        return rowsInserted;
    }


    //5.2 Task 2 Insert Drivers
    @Override
    public int insertDrivers(Driver[] drivers) {
        int rowsInserted = 0;

        for (Driver driver : drivers) {
            try {
                String insertionQuery = "INSERT INTO Drivers (PIN, rating) VALUES (?, ?);";
                PreparedStatement insertionStatement = this.connection.prepareStatement(insertionQuery);

                insertionStatement.setInt(1, driver.getPIN());
                insertionStatement.setDouble(2, driver.getRating());
                insertionStatement.execute();

                rowsInserted += 1;
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }

        return rowsInserted;
    }

    
    //5.2 Task 2 Insert Cars
    @Override
    public int insertCars(Car[] cars) {
        int rowsInserted = 0;

        for (Car car : cars) {
            try {
                String insertionQuery = "INSERT INTO Cars (CarID, PIN, color, brand) VALUES (?, ?, ?, ?);";
                PreparedStatement insertionStatement = this.connection.prepareStatement(insertionQuery);

                insertionStatement.setInt(1, car.getCarID());
                insertionStatement.setInt(2, car.getPIN());
                insertionStatement.setString(3, car.getColor());
                insertionStatement.setString(4, car.getBrand());

                insertionStatement.execute();

                rowsInserted += 1;
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }

        return rowsInserted;
    }


    //5.2 Task 2 Insert Trips
    @Override
    public int insertTrips(Trip[] trips) {
        int rowsInserted = 0;

        for (Trip trip : trips) {
            try {
                String insertionQuery = "INSERT INTO Trips (TripID, CarID, date, departure, destination, num_seats_available) VALUES (?, ?, ?, ?, ?, ?);";
                PreparedStatement insertionStatement = this.connection.prepareStatement(insertionQuery);

                insertionStatement.setInt(1, trip.getTripID());
                insertionStatement.setInt(2, trip.getCarID());
                insertionStatement.setString(3, trip.getDate());
                insertionStatement.setString(4, trip.getDeparture());
                insertionStatement.setString(5, trip.getDestination());
                insertionStatement.setInt(6, trip.getNum_seats_available());

                insertionStatement.execute();

                rowsInserted += 1;
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        
        return rowsInserted;
    }

    //5.2 Task 2 Insert Bookings
    @Override
    public int insertBookings(Booking[] bookings) {
        int rowsInserted = 0;

        for (Booking booking : bookings) {
            try {
                String insertionQuery = "INSERT INTO Bookings (TripID, PIN, booking_status) VALUES (?, ?, ?);";
                PreparedStatement insertionStatement = this.connection.prepareStatement(insertionQuery);

                insertionStatement.setInt(1, booking.getTripID());
                insertionStatement.setInt(2, booking.getPIN());
                insertionStatement.setString(3, booking.getBooking_status());

                insertionStatement.execute();

                rowsInserted += 1;
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }

        return rowsInserted;
    }

    
    //5.3 Task 3 Find all participants who are recorded as both drivers and passengers
    @Override
    public Participant[] getBothPassengersAndDrivers() {
        String query = "SELECT DISTINCT Par.PIN, Par.p_name, Par.age " +
                "FROM Participants Par, Passengers Pas, Drivers D " +
                "WHERE Pas.PIN = D.PIN AND Pas.PIN = Par.PIN " +
                "ORDER BY Par.PIN ASC;";

        try {
            PreparedStatement statement = this.connection.prepareStatement(query);

            ResultSet resultSet =  statement.executeQuery();
            ArrayList<Participant> results = new ArrayList<>();

            while (resultSet.next()) {
                results.add(new Participant(
                        resultSet.getInt("PIN"),
                        resultSet.getString("p_name"),
                        resultSet.getInt("age")
                ));
            }

            return results.toArray(new Participant[0]);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    	
    	return new Participant[0];
    }

 
    //5.4 Task 4 Find the PINs, names, ages, and ratings of drivers who do not own any cars
    @Override
    public QueryResult.DriverPINNameAgeRating[] getDriversWithNoCars() {
        String query = "SELECT P.PIN, P.p_name, P.age, D.rating FROM Drivers D, Participants P " +
                "WHERE D.PIN NOT IN (SELECT C.PIN FROM Cars C) " +
                "AND P.PIN = D.PIN " +
                "ORDER BY D.PIN ASC;";

        try {
            PreparedStatement statement = this.connection.prepareStatement(query);

            ResultSet resultSet =  statement.executeQuery();
            ArrayList<QueryResult.DriverPINNameAgeRating> results = new ArrayList<>();

            while (resultSet.next()) {
                results.add(new QueryResult.DriverPINNameAgeRating(
                        resultSet.getInt("PIN"),
                        resultSet.getString("p_name"),
                        resultSet.getInt("age"),
                        resultSet.getDouble("rating")
                ));
            }

            return results.toArray(new QueryResult.DriverPINNameAgeRating[0]);
        } catch (SQLException e) {
            e.printStackTrace();
        }

    	
    	return new QueryResult.DriverPINNameAgeRating[0];
    }
 
    
    //5.5 Task 5 Delete Drivers who do not own any cars
    @Override
    public int deleteDriversWithNoCars() {
        int rowsDeleted = 0;
        String query = "DELETE FROM Drivers D " +
                "WHERE D.PIN NOT IN (SELECT C.PIN FROM Cars C);";

        try {
            PreparedStatement statement = connection.prepareStatement(query);
            rowsDeleted = statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        
        return rowsDeleted;  
    }

    
    //5.6 Task 6 Find all cars that are not taken part in any trips
    @Override
    public Car[] getCarsWithNoTrips() {
        String query = "SELECT C.CarID, C.PIN, C.color, C.brand FROM Cars C " +
                "WHERE C.CarID NOT IN (SELECT T.CarID FROM Trips T) " +
                "ORDER BY C.CarID ASC;";

        try {
            PreparedStatement statement = this.connection.prepareStatement(query);

            ResultSet resultSet =  statement.executeQuery();
            ArrayList<Car> results = new ArrayList<>();

            while (resultSet.next()) {
                results.add(new Car(
                        resultSet.getInt("CarID"),
                        resultSet.getInt("PIN"),
                        resultSet.getString("color"),
                        resultSet.getString("brand")
                ));
            }

            return results.toArray(new Car[0]);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    	
        return new Car[0];
    }
    
    
    //5.7 Task 7 Find all passengers who didn't book any trips
    @Override
    public Passenger[] getPassengersWithNoBooks() {
        String query = "SELECT P.PIN, P.membership_status FROM Passengers P " +
                "WHERE P.PIN NOT IN (SELECT B.PIN FROM Bookings B) " +
                "ORDER BY P.PIN ASC;";

        try {
            PreparedStatement statement = this.connection.prepareStatement(query);

            ResultSet resultSet =  statement.executeQuery();
            ArrayList<Passenger> results = new ArrayList<>();

            while (resultSet.next()) {
                results.add(new Passenger(
                        resultSet.getInt("PIN"),
                        resultSet.getString("membership_status")
                ));
            }

            return results.toArray(new Passenger[0]);
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return new Passenger[0];
    }


    //5.8 Task 8 Find all trips that depart from the specified city to specified destination city on specific date
    @Override
    public Trip[] getTripsFromToCitiesOnSpecificDate(String departure, String destination, String date) {
        String query = "SELECT T.TripID, T.CarID, T.date, T.departure, T.destination, T.num_seats_available FROM Trips T " +
                "WHERE T.departure = ? AND T.destination = ? AND T.date = ? " +
                "ORDER BY T.TripID ASC;";

        try {
            PreparedStatement statement = this.connection.prepareStatement(query);

            statement.setString(1, departure);
            statement.setString(2, destination);
            statement.setString(3, date);

            ResultSet resultSet =  statement.executeQuery();
            ArrayList<Trip> results = new ArrayList<>();

            while (resultSet.next()) {
                results.add(new Trip(
                        resultSet.getInt("TripID"),
                        resultSet.getInt("CarID"),
                        resultSet.getString("date"),
                        resultSet.getString("departure"),
                        resultSet.getString("destination"),
                        resultSet.getInt("num_seats_available")
                ));
            }

            return results.toArray(new Trip[0]);
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return new Trip[0]; 
    }


    //5.9 Task 9 Find the PINs, names, ages, and membership_status of passengers who have bookings on all trips destined at a particular city
    @Override
    public QueryResult.PassengerPINNameAgeMembershipStatus[] getPassengersWithBookingsToAllTripsForCity(String city) {
        String query = "SELECT Par.PIN, Par.p_name, Par.age, Pas.membership_status " +
                "FROM Passengers Pas, Participants Par " +
                "WHERE Pas.PIN = Par.PIN AND NOT EXISTS (" +
                "SELECT T.TripID FROM Trips T " +
                "WHERE T.destination = ? EXCEPT " +
                "SELECT B.TripID FROM Bookings B " +
                "WHERE B.PIN = Pas.PIN)" +
                "ORDER BY Par.PIN ASC;";

        try {
            PreparedStatement statement = this.connection.prepareStatement(query);

            statement.setString(1, city);

            ResultSet resultSet =  statement.executeQuery();
            ArrayList<QueryResult.PassengerPINNameAgeMembershipStatus> results = new ArrayList<>();

            while (resultSet.next()) {
                results.add(new QueryResult.PassengerPINNameAgeMembershipStatus(
                        resultSet.getInt("PIN"),
                        resultSet.getString("p_name"),
                        resultSet.getInt("age"),
                        resultSet.getString("membership_status")
                ));
            }

            return results.toArray(new QueryResult.PassengerPINNameAgeMembershipStatus[0]);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    	
        return new QueryResult.PassengerPINNameAgeMembershipStatus[0];
    }

    
    //5.10 Task 10 For a given driver PIN, find the CarIDs that the driver owns and were booked at most twice.    
    @Override
    public Integer[] getDriverCarsWithAtMost2Bookings(int driverPIN) {
        String query = "SELECT C.CarID " +
                "FROM Cars C, Bookings B, Trips T " +
                "WHERE C.PIN = ? AND B.TripID = T.TripID AND T.CarID = C.CarID " +
                "GROUP BY C.CarID " +
                "HAVING COUNT(*) <= 2" +
                "ORDER BY C.CarID ASC;";

        try {
            PreparedStatement statement = this.connection.prepareStatement(query);

            statement.setInt(1, driverPIN);

            ResultSet resultSet =  statement.executeQuery();
            ArrayList<Integer> results = new ArrayList<>();

            while (resultSet.next()) {
                results.add(resultSet.getInt("CarID"));
            }

            return results.toArray(new Integer[0]);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    	
        return new Integer[0];
    }


    //5.11 Task 11 Find the average age of passengers with "Confirmed" bookings (i.e., booking_status is ”Confirmed”) on trips departing from a given city and within a specified date range
    @Override
    public Double getAvgAgeOfPassengersDepartFromCityBetweenTwoDates(String city, String start_date, String end_date) {
        Double averageAge = null;
        String query = "SELECT AVG(Par.age) FROM Passengers Pas, Participants Par, Trips T, Bookings B " +
                "WHERE B.PIN = Pas.PIN AND T.TripID = B.TripID AND Pas.PIN = Par.PIN " +
                "AND B.booking_status = 'Confirmed' " +
                "AND T.departure = ? AND T.date >= ? AND T.date <= ?";

        try {
            PreparedStatement statement = connection.prepareStatement(query);

            statement.setString(1, city);
            statement.setString(2, start_date);
            statement.setString(3, end_date);

            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                averageAge = resultSet.getDouble(1);
                if (resultSet.wasNull()) {
                    averageAge = null;
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return averageAge;
    }


    //5.12 Task 12 Find Passengers in a Given Trip.
    @Override
    public QueryResult.PassengerPINNameAgeMembershipStatus[] getPassengerInGivenTrip(int TripID) {
        String query = "SELECT Pas.PIN, Par.p_name, Par.age, Pas.membership_status FROM Passengers Pas, Participants Par, Bookings B " +
                "WHERE B.TripID = ? AND Pas.PIN = Par.PIN AND B.PIN = Pas.PIN " +
                "ORDER BY Pas.PIN ASC;";

        try {
            PreparedStatement statement = this.connection.prepareStatement(query);

            statement.setInt(1, TripID);

            ResultSet resultSet =  statement.executeQuery();
            ArrayList<QueryResult.PassengerPINNameAgeMembershipStatus> results = new ArrayList<>();

            while (resultSet.next()) {
                results.add(new QueryResult.PassengerPINNameAgeMembershipStatus(
                        resultSet.getInt("PIN"),
                        resultSet.getString("p_name"),
                        resultSet.getInt("age"),
                        resultSet.getString("membership_status")
                ));
            }

            return results.toArray(new QueryResult.PassengerPINNameAgeMembershipStatus[0]);
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return new QueryResult.PassengerPINNameAgeMembershipStatus[0];
    }


    //5.13 Task 13 Find Drivers’ Scores
    @Override
    public QueryResult.DriverScoreRatingNumberOfBookingsPIN[] getDriversScores() {
        String query = "SELECT (D.rating * COUNT(B.TripID)) AS driver_score, D.rating, " +
                "COUNT(B.TripID) AS number_of_bookings, D.PIN AS driver_PIN " +
                "FROM Drivers D, Cars C, Trips T, Bookings B " +
                "WHERE D.PIN = C.PIN " +
                "AND C.CarID = T.CarID " +
                "AND T.TripID = B.TripID " +
                "GROUP BY D.PIN, D.rating " +
                "ORDER BY driver_score DESC, driver_PIN ASC";

        try {
            PreparedStatement statement = this.connection.prepareStatement(query);

            ResultSet resultSet =  statement.executeQuery();
            ArrayList<QueryResult.DriverScoreRatingNumberOfBookingsPIN> results = new ArrayList<>();

            while (resultSet.next()) {
                results.add(new QueryResult.DriverScoreRatingNumberOfBookingsPIN(
                        resultSet.getDouble("driver_score"),
                        resultSet.getDouble("rating"),
                        resultSet.getInt("number_of_bookings"),
                        resultSet.getInt("driver_PIN")
                ));
            }

            return results.toArray(new QueryResult.DriverScoreRatingNumberOfBookingsPIN[0]);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    	
        return new QueryResult.DriverScoreRatingNumberOfBookingsPIN[0];
    }

    
    //5.14 Task 14 Find average ratings of drivers who have trips destined to each city
    @Override
    public QueryResult.CityAndAverageDriverRating[] getDriversAverageRatingsToEachDestinatedCity() {
        String query = "SELECT T.destination AS destination_city, AVG(D.rating) AS average_rating_of_drivers " +
                "FROM Trips T, Cars C, Drivers D " +
                "WHERE T.CarID = C.CarID AND C.PIN = D.PIN " +
                "GROUP BY T.destination";

        try {
            PreparedStatement statement = this.connection.prepareStatement(query);

            ResultSet resultSet =  statement.executeQuery();
            ArrayList<QueryResult.CityAndAverageDriverRating> results = new ArrayList<>();

            while (resultSet.next()) {
                results.add(new QueryResult.CityAndAverageDriverRating(
                        resultSet.getString("destination_city"),
                        resultSet.getDouble("average_rating_of_drivers")
                ));
            }

            return results.toArray(new QueryResult.CityAndAverageDriverRating[0]);
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return new QueryResult.CityAndAverageDriverRating[0];
    }


    //5.15 Task 15 Find total number of bookings of passengers for each membership status
    @Override
    public QueryResult.MembershipStatusAndTotalBookings[] getTotalBookingsEachMembershipStatus() {
        String query = "SELECT P.membership_status, COUNT(*) AS total_number_of_bookings " +
                "FROM Passengers P, Bookings B " +
                "WHERE P.PIN = B.PIN " +
                "GROUP BY P.membership_status";

        try {
            PreparedStatement statement = this.connection.prepareStatement(query);

            ResultSet resultSet =  statement.executeQuery();
            ArrayList<QueryResult.MembershipStatusAndTotalBookings> results = new ArrayList<>();

            while (resultSet.next()) {
                results.add(new QueryResult.MembershipStatusAndTotalBookings(
                        resultSet.getString("membership_status"),
                        resultSet.getInt("total_number_of_bookings")
                ));
            }

            return results.toArray(new QueryResult.MembershipStatusAndTotalBookings[0]);
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return new QueryResult.MembershipStatusAndTotalBookings[0];
    }

    
    //5.16 Task 16 For the drivers' ratings, if rating is smaller than 2.0 or equal to 2.0, update the rating by adding 0.5.
    @Override
    public int updateDriverRatings() {
        int rowsUpdated = 0;
        String updateQuery = "UPDATE Drivers D "+
                "SET D.rating = D.rating + 0.5" +
                "WHERE rating <= 2.0;";

        try {
            PreparedStatement statement = connection.prepareStatement(updateQuery);
            rowsUpdated = statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return rowsUpdated;
    }
    

    //6.1 (Optional) Task 18 Find trips departing from the given city
    @Override
    public Trip[] getTripsFromCity(String city) {
        
    	/*****************************************************/
        /*****************************************************/
        /*****************  TODO  (Optional)   ***************/
        /*****************************************************/
        /*****************************************************/
    	
        return new Trip[0];
    }
    
    
    //6.2 (Optional) Task 19 Find all trips that have never been booked
    @Override
    public Trip[] getTripsWithNoBooks() {
        
    	/*****************************************************/
        /*****************************************************/
        /*****************  TODO  (Optional)   ***************/
        /*****************************************************/
        /*****************************************************/
    	
        return new Trip[0];
    }
    
    
    //6.3 (Optional) Task 20 For each driver, find the trip(s) with the highest number of bookings
    @Override
    public QueryResult.DriverPINandTripIDandNumberOfBookings[] getTheMostBookedTripsPerDriver() {
        
    	/*****************************************************/
        /*****************************************************/
        /*****************  TODO  (Optional)   ***************/
        /*****************************************************/
        /*****************************************************/
    	
        return new QueryResult.DriverPINandTripIDandNumberOfBookings[0];
    }
    
    
    //6.4 (Optional) Task 21 Find Full Cars
    @Override
    public QueryResult.FullCars[] getFullCars() {
        
    	/*****************************************************/
        /*****************************************************/
        /*****************  TODO  (Optional)   ***************/
        /*****************************************************/
        /*****************************************************/
    	
        return new QueryResult.FullCars[0];
    }

}
