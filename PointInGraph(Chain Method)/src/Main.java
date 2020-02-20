import java.awt.*;
import java.io.*;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {

  public static int checkIfPointIsRightFromEdge(Point a, Point b, Point middle) {
    int D = (middle.x - a.x) * (b.y - a.y) - (middle.y - a.y) * (b.x - a.x);
    System.out.println(D);
    if (D == 0) {
      if (b.y == a.y) { // horizontal line
        if (a.x < middle.x) return 1;
        if (b.x > middle.x) return -1;
      }
    }
    return Long.signum(D);
  }

  @SuppressWarnings("empty-statement")
  public static int checkIfPointIsRightFromChain(Point z, ArrayList<Point> chain, ArrayList<Point> figure) {
    int n = chain.size();
    int mid = n / 2;
    int r = n - 1;
    int l = 0;
    boolean wasChange = true;

    while (wasChange) {
      if (figure.get(chain.get(mid).x).y > z.y) {
        if (r == mid)
          return checkIfPointIsRightFromEdge(figure.get(chain.get(mid).x), figure.get(chain.get(mid).y), z);
        r = mid;
        mid = l + (r - l) / 2;
        wasChange = true;
      } else if (figure.get(chain.get(mid).y).y < z.y) {
        if (l == mid && r != mid) {
          mid = r;
          wasChange = true;
        } else {
          l = mid;
          mid = l + (r - l) / 2;
          wasChange = true;
        }
      } else return checkIfPointIsRightFromEdge(figure.get(chain.get(mid).x), figure.get(chain.get(mid).y), z);
    }

    return checkIfPointIsRightFromEdge(figure.get(chain.get(mid).x), figure.get(chain.get(mid).y), z);
  }

  public static ArrayList<Point> readInputData(String filename) throws FileNotFoundException {
    ArrayList<Point> arr = new ArrayList<>();

    Scanner scFile = new Scanner(new File(filename));
    while (scFile.hasNextInt()) {
      Point tmp = new Point();
      tmp.x = scFile.nextInt();
      tmp.y = scFile.nextInt();
      arr.add(tmp);
    }
    return arr;
  }

  public static void main(String[] args) throws FileNotFoundException {

    ArrayList<Point> vertex = readInputData("vertex.txt");
    ArrayList<Point> edges = readInputData("edges.txt");

    ArrayList<ArrayList<Point>> chains = buildChains(vertex, edges);

    while (true) {
      Scanner sc = new Scanner(System.in);

      Point z = new Point(0, 0);
      z.x = sc.nextInt();
      z.y = sc.nextInt();

      Point p = findSector(chains, z, vertex);
      if (p.y == 0) System.out.println("line " + p.x);
      else System.out.println("sector " + p.x);
    }
  }

  public static Point findSector(ArrayList<ArrayList<Point>> chains, Point z, ArrayList<Point> figure) {
    int n = chains.size();
    int mid = n / 2;
    int r = n - 1;
    int l = 0;

    //point is upper figure
    if (figure.get(chains.get(0).get(chains.get(0).size() - 1).y).y < z.y) return new Point(-1, 1);
    //point is under figure
    if (figure.get(chains.get(0).get(0).x).y > z.y) return new Point(-1, 1);

    //point on the highest vertex
    if (z.equals(figure.get(chains.get(0).get(chains.get(0).size() - 1).y)))
      return new Point(mid, 0);
    //point is outside
    if (z.y == figure.get(chains.get(0).get(chains.get(0).size() - 1).y).y) return new Point(-1, -1);

    System.out.println(checkIfPointIsRightFromChain(z, chains.get(l), figure));
    System.out.println(checkIfPointIsRightFromChain(z, chains.get(r), figure));

    //point is righter or lefter to the figure
    if (checkIfPointIsRightFromChain(z, chains.get(l), figure) == -1
        || (checkIfPointIsRightFromChain(z, chains.get(r), figure) == 1)) return new Point(-1, 1);


    int tempComp = checkIfPointIsRightFromChain(z, chains.get(mid), figure);
    while (tempComp != 0 && r - l > 1) {
      if (tempComp == 1) l = mid;
      else r = mid;
      mid = l + (r - l) / 2;
      tempComp = checkIfPointIsRightFromChain(z, chains.get(mid), figure);
    }

    if (tempComp == 0) return new Point(mid, 0);
    if (tempComp > 0) return new Point(mid, 1);
    else return new Point(mid - 1, 1);
  }

  public static int WeightIn(int[] Weight, ArrayList<Point> E, int index) {
    int counter = 0;
    for (int i = 0; i < E.size(); i++) {
      if (E.get(i).y == index) counter += Weight[i];
    }
    return counter;
  }

  public static int edgesOut(ArrayList<Point> E, int index) {
    int counter = 0;
    for (Point point : E) {
      if (point.x == index) counter++;
    }
    return counter;
  }

  public static int WeightOut(int[] Weight, ArrayList<Point> E, int index) {
    int counter = 0;
    for (int i = 0; i < E.size(); i++) {
      if (E.get(i).x == index) counter += Weight[i];
    }
    return counter;
  }

  public static int firstEdgeOut(int[] Weight, ArrayList<Point> E, int index) {
    for (int i = 0; i < E.size(); i++) {
      if (E.get(i).x == index && Weight[i] > 0) return i;
    }
    return -1;
  }

  public static int firstEdgeIn(int[] Weight, ArrayList<Point> E, int index) {
    for (int i = 0; i < E.size(); i++) {
      if (E.get(i).y == index && Weight[i] > 0) return i;
    }
    return -1;
  }

  public static ArrayList<ArrayList<Point>> buildChains(ArrayList<Point> V, ArrayList<Point> E) {
    ArrayList<ArrayList<Point>> arrayLines = new ArrayList<>();

    int[] Weight = new int[E.size()];

    for (int i = 0; i < E.size(); i++) {
      Weight[i] = 1;
    }
    for (int i = 1; i < V.size() - 1; i++) {
      int win = WeightIn(Weight, E, i);
      int d1 = firstEdgeOut(Weight, E, i);
      int vOut = edgesOut(E, i);
      if (win > vOut) Weight[d1] = win - vOut + 1;
    }
    for (int i = V.size() - 2; i > 0; i--) {
      int wout = WeightOut(Weight, E, i);
      int d2 = firstEdgeIn(Weight, E, i);
      int win = WeightIn(Weight, E, i);
      if (wout > win) Weight[d2] = wout - win + Weight[d2];
    }
    boolean flag = true;
    while (flag) {
      ArrayList<Point> line = new ArrayList<>();
      int nextV = 0;
      while (nextV != V.size() - 1) {
        int nextE = firstEdgeOut(Weight, E, nextV);
        Weight[nextE]--;
        nextV = E.get(nextE).y;
        line.add(E.get(nextE));
      }
      arrayLines.add(line);
      flag = firstEdgeOut(Weight, E, 0) != -1;
    }

    int n = arrayLines.size();
    for (int i = 0; i < n; i++) {
      int k = arrayLines.get(i).size();
      System.out.println("Chain " + i);
      for (int j = 0; j < k; j++) {
        System.out.println(arrayLines.get(i).get(j).x + "  " + arrayLines.get(i).get(j).y);
      }
    }

    return arrayLines;
  }
}
