package conwaygame;
import java.util.ArrayList;
/**
 * Conway's Game of Life Class holds various methods that will
 * progress the state of the game's board through it's many iterations/generations.
 *
 * Rules 
 * Alive cells with 0-1 neighbors die of loneliness.
 * Alive cells with >=4 neighbors die of overpopulation.
 * Alive cells with 2-3 neighbors survive.
 * Dead cells with exactly 3 neighbors become alive by reproduction.

 * @author Seth Kelley 
 * @author Maxwell Goldberg
 */
public class GameOfLife {

    // Instance variables
    private static final boolean ALIVE = true;
    private static final boolean  DEAD = false;

    private boolean[][] grid;    // The board has the current generation of cells
    private int totalAliveCells; // Total number of alive cells in the grid (board)

    /**
    * Default Constructor which creates a small 5x5 grid with five alive cells.
    * This variation does not exceed bounds and dies off after four iterations.
    */
    public GameOfLife() {
        grid = new boolean[5][5];
        totalAliveCells = 5;
        grid[1][1] = ALIVE;
        grid[1][3] = ALIVE;
        grid[2][2] = ALIVE;
        grid[3][2] = ALIVE;
        grid[3][3] = ALIVE;
    }

    /**
    * Constructor used that will take in values to create a grid with a given number
    * of alive cells
    * @param file is the input file with the initial game pattern formatted as follows:
    * An integer representing the number of grid rows, say r
    * An integer representing the number of grid columns, say c
    * Number of r lines, each containing c true or false values (true denotes an ALIVE cell)
    */
    public GameOfLife (String file) {
        StdIn.setFile(file);
        int r = StdIn.readInt();
        int c = StdIn.readInt();
        grid = new boolean[r][c];
       
        for(int i = 0; i < r; i++) {
            for(int j = 0; j < c; j++){
                grid[i][j] = StdIn.readBoolean();
            }
        }
        
      
    } 

    /**
     * Returns grid
     * @return boolean[][] for current grid
     */
    public boolean[][] getGrid () {
        return grid;
    }
    
    /**
     * Returns totalAliveCells
     * @return int for total number of alive cells in grid
     */
    public int getTotalAliveCells () {
        return totalAliveCells;
    }

    /**
     * Returns the status of the cell at (row,col): ALIVE or DEAD
     * @param row row position of the cell
     * @param col column position of the cell
     * @return true or false value "ALIVE" or "DEAD" (state of the cell)
     */
    public boolean getCellState (int row, int col) {

        if(grid[row][col] == true){
            return true;
        }
        return false;  // update this line, provided so that code compiles
    }

    /**
     * Returns true if there are any alive cells in the grid
     * @return true if there is at least one cell alive, otherwise returns false
     */
    public boolean isAlive () {
        int count = 0;
        for(int i = 0; i < grid.length; i++) {
            for(int j = 0; j < grid[0].length; j++) {
                if(grid[i][j] == ALIVE){
                    count++;
                } 
                }
            }
        
        
        if(count > 1){
        return true;
        } else{
            return false;
        }
    }

    /**
     * Determines the number of alive cells around a given cell.
     * Each cell has 8 neighbor cells which are the cells that are 
     * horizontally, vertically, or diagonally adjacent.
     * 
     * @param col column position of the cell
     * @param row row position of the cell
     * @return neighboringCells, the number of alive cells (at most 8).
     */
     private int checkOOB (int target){

        if(target >= grid.length){
            // System.out.println("FIRST IF");
            target = 0;
        } else if(target < 0){
            // System.out.println("SECOND IF:" + grid.length);
            target = grid.length - 1;
            // System.out.println("TARGET: " + target);
        }

        return target;
     }
   
   
     public int numOfAliveNeighbors (int row, int col) {
       int count = 0;
      
        
       
        for(int i = row-1; i <= row+1; i++) {
            for(int j = col - 1; j <= col+1; j++) {
                // System.out.println("checkOOB(i)" + checkOOB(i));
                // System.out.println("Length: " + grid.length);
                // System.out.println("checkOOB(j)" + checkOOB(j));
                boolean selected = grid[checkOOB(i)][checkOOB(j)];
                //System.out.println(selected);
                if(checkOOB(i) != row || checkOOB(j) != col){
                    if(selected == ALIVE && grid[checkOOB(i)][checkOOB(j)] == ALIVE){
                        count++;
                    }
                }
            }
        }
        return count;// update this line, provided so that code compiles
    }

    /**
     * Creates a new grid with the next generation of the current grid using 
     * the rules for Conway's Game of Life.
     * 
     * @return boolean[][] of new grid (this is a new 2D array)
     */
    public boolean[][] computeNewGrid () {
        //create new array
        boolean[][] newGrid = new boolean[grid.length][grid[0].length];
        //transfer everything to new array
        for(int i = 0; i < grid.length; i++){
            for(int j = 0; j < grid[0].length; j++){
                newGrid[i][j] = grid[i][j];
            }
        }
        //rule 1 Alive cells with no neighbors or one neighbor die of loneliness.
            for(int i = 0; i < grid.length; i++){
                for(int j = 0; j < grid[0].length; j++){
                    if(numOfAliveNeighbors(i,j) <= 1){
                        newGrid[i][j] = DEAD;
                        // System.out.println("Rule 1: dead cell pos [" + i + "]" + "[" + j + "]" + newGrid[i][j]);
                    }
                }
            }
        
       
        //rule 2 Dead cells with exactly three neighbors become alive by reproduction.
       
            //traverse thru the entire array
        for(int i = 0; i < grid.length; i++){
            for(int j = 0; j < grid[0].length; j++){
                if(grid[i][j] == DEAD){
                    if(numOfAliveNeighbors(i, j) == 3){
                        newGrid[i][j] = ALIVE;
                        // System.out.println("Rule 2: alive cell pos [" + i + "]" + "[" + j +  "]" + newGrid[i][j]);
                    
                    }
                }
        
            }
        }
    

        //rule 3 alive cells w/ 2 or 3 neighbors survive
       
            for(int i = 0; i < grid.length; i++){
                for(int j = 0; j < grid[0].length; j++){
                        if(numOfAliveNeighbors(i, j) == 2 || numOfAliveNeighbors(i, j) == 3 && newGrid[i][j] == ALIVE){
                            newGrid[i][j] = newGrid[i][j];;
                            // System.out.println("Rule 2: alive cell pos [" + i + "]" + "[" + j + "]" + newGrid[i][j]);
                        }
                    }
            
                }
            
        
        
        //rule 4 cells w/ 4 or more neighbors die
            for(int i = 0; i < grid.length; i++){
                for(int j = 0; j < grid[0].length; j++){
                        if(numOfAliveNeighbors(i, j) >= 4){
                            newGrid[i][j] = DEAD;
                            // System.out.println("Rule 2: dead cell pos [" + i + "]" + "[" + j + "]" + newGrid[i][j]);
                        }
                }
            }
        

        return newGrid;// update this line, provided so that code compiles
    }

    /**
     * Updates the current grid (the grid instance variable) with the grid denoting
     * the next generation of cells computed by computeNewGrid().
     * 
     * Updates totalAliveCells instance variable
     */
    public void nextGeneration () {
        this.grid = computeNewGrid();

        //update totalAliveCells instance variable
        int count = 0;
        for(int i = 0; i < grid.length; i++){
            for(int j = 0; j < grid[0].length; j++){
                if(grid[i][j] == ALIVE){
                    count++;
                    // System.out.println(count);
                }
            }
        }
        totalAliveCells = count;
        
    }

    /**
     * Updates the current grid with the grid computed after multiple (n) generations. 
     * @param n number of iterations that the grid will go through to compute a new grid
     */
    public void nextGeneration (int n) {
        int i = 0;
        while(i != n){
            nextGeneration();
            i++;
        }
        
    }

    /**
     * Determines the number of separate cell communities in the grid
     * @return the number of communities in the grid, communities can be formed from edges
     */
    public int numOfCommunities() {
       WeightedQuickUnionUF tree = new WeightedQuickUnionUF(grid.length, grid[0].length);
       //array list implemented in order to return an size of integer
       ArrayList<Integer> children = new ArrayList<Integer>();
       
       //debug this loop
       for(int i = 0; i < grid.length; i++){
        for(int j = 0; j < grid[0].length; j++){
            // ^traverses through the rows and cols
                if(grid[i][j] == ALIVE){
                //^ finds alive cells
            for(int r = i-1; r <= i+1; r++) {
                for(int c = j - 1; c <= j+1; c++) {
                    // ^ checks for neighbors next to cell (right, left, above, below)

                    //  System.out.println("checkOOB(r)" + checkOOB(r));
                    //  System.out.println("Length: " + grid.length);
                    //  System.out.println("checkOOB(c)" + checkOOB(c));
                   
                    boolean selected2 = grid[checkOOB(r)][checkOOB(c)];
                    //System.out.println(selected);
                    // System.out.println("check r: " + checkOOB(r));
                    // System.out.println("check c: " + checkOOB(c));
                    
                    if(checkOOB(r) != i || checkOOB(c) != j){
                        if(selected2 == ALIVE){
                            tree.union(i, j, r, c);
                        }
                    }
                }
            }
        
                }
        }
       }
       //finds alive cells's roots and adds them to the array list
        for(int i=0; i < grid.length; i++){
            for(int j = 0; j < grid[0].length; j++){
                if(grid[i][j] == ALIVE && !(children.contains(tree.find(i,j)))){
                    children.add(tree.find(i,j));
                }
            }
        }


        return children.size(); // update this line, provided so that code compiles
    }
}
