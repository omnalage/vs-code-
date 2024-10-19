import java.util.*;

public class Solution {

    static int[] dx = {1, -1, 0, 0};
    static int[] dy = {0, 0, 1, -1};
    
    public static int minimumEnergy(String[] river, int initial_x, int initial_y, int final_x, int final_y) {
        int n = river.length;
        int m = river[0].length();
        
        PriorityQueue<int[]> pq = new PriorityQueue<>(Comparator.comparingInt(a -> a[0]));
        pq.add(new int[]{0, initial_x, initial_y});
        
        int[][] energy = new int[n][m];
        for (int i = 0; i < n; i++) {
            Arrays.fill(energy[i], Integer.MAX_VALUE);
        }
        energy[initial_x][initial_y] = 0;
        
        while (!pq.isEmpty()) {
            int[] current = pq.poll();
            int currEnergy = current[0];
            int x = current[1];
            int y = current[2];
            
            if (x == final_x && y == final_y) {
                return currEnergy;
            }
            
            if (currEnergy > energy[x][y]) {
                continue;
            }
            
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                
                if (nx >= 0 && nx < n && ny >= 0 && ny < m && river[nx].charAt(ny) != '#') {
                    int newEnergy = currEnergy + (i == 1 || i == 3 ? 1 : 0);
                    
                    if (newEnergy < energy[nx][ny]) {
                        energy[nx][ny] = newEnergy;
                        pq.add(new int[]{newEnergy, nx, ny});
                    }
                }
            }
        }
        
        return -1;
    }

    public static void main(String[] args) {
        String[] river = {
            "...#.",
            "..#..",
            "#....",
            ".#..."
        };
        int initial_x = 2;
        int initial_y = 3;
        int final_x = 1;
        int final_y = 4;
        
        int result = minimumEnergy(river, initial_x, initial_y, final_x, final_y);
        System.out.println(result); // Output: 5
    }
}
